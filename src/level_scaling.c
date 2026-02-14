#include "global.h"
#include "level_scaling.h"
#include "pokemon.h"
#include "data.h"
#include "caps.h"
#include "random.h"
#include "pokemon_storage_system.h"
#include "constants/trainers.h"
#include "constants/pokemon.h"
#include "constants/weather.h"
#include "overworld.h"
#include "rtc.h"
#include "field_weather.h"

#if B_LEVEL_SCALING_ENABLED

#include "data/level_scaling_rules.h"
#include "data/level_scaling_evolution_overrides.h"

// Party level cache for performance
static struct {
    u8 partyAverage;
    u8 partyHighest;
    u8 partyLowest;
    bool8 cached;
} sPartyLevelCache = {0};

// ============================================================================
// Internal Helper Functions - Party Level Calculation
// ============================================================================

static u8 GetPlayerPartyAverageLevel(bool8 excludeFainted)
{
    u32 totalLevel = 0;
    u32 count = 0;
    u32 i;

    for (i = 0; i < PARTY_SIZE; i++)
    {
        struct Pokemon *mon = &gPlayerParty[i];
        if (GetMonData(mon, MON_DATA_SPECIES) == SPECIES_NONE)
            break;

        if (excludeFainted && GetMonData(mon, MON_DATA_HP) == 0)
            continue;

        totalLevel += GetMonData(mon, MON_DATA_LEVEL);
        count++;
    }

    if (count == 0)
        return 1; // Fallback if no valid mons

    return totalLevel / count;
}

static u8 GetPlayerPartyHighestLevel(bool8 excludeFainted)
{
    u8 highest = 1;
    u32 i;

    for (i = 0; i < PARTY_SIZE; i++)
    {
        struct Pokemon *mon = &gPlayerParty[i];
        if (GetMonData(mon, MON_DATA_SPECIES) == SPECIES_NONE)
            break;

        if (excludeFainted && GetMonData(mon, MON_DATA_HP) == 0)
            continue;

        u8 level = GetMonData(mon, MON_DATA_LEVEL);
        if (level > highest)
            highest = level;
    }

    return highest;
}

static u8 GetPlayerPartyLowestLevel(bool8 excludeFainted)
{
    u8 lowest = MAX_LEVEL;
    u32 i;
    bool8 foundMon = FALSE;

    for (i = 0; i < PARTY_SIZE; i++)
    {
        struct Pokemon *mon = &gPlayerParty[i];
        if (GetMonData(mon, MON_DATA_SPECIES) == SPECIES_NONE)
            break;

        if (excludeFainted && GetMonData(mon, MON_DATA_HP) == 0)
            continue;

        u8 level = GetMonData(mon, MON_DATA_LEVEL);
        if (level < lowest)
        {
            lowest = level;
            foundMon = TRUE;
        }
    }

    return foundMon ? lowest : 1;
}


// ============================================================================
// Internal Helper Functions - Level Manipulation
// ============================================================================

static u8 ApplyLevelVariation(u8 baseLevel, u8 variation)
{
    if (variation == 0)
        return baseLevel;

    // Randomly reduce level by 0 to variation
    u8 reduction = Random() % (variation + 1);
    if (baseLevel > reduction)
        return baseLevel - reduction;

    return 1; // Never go below 1
}

static u8 ClampLevel(u8 level, u8 minLevel, u8 maxLevel)
{
    // Apply minimum
    if (minLevel > 0 && level < minLevel)
        level = minLevel;

    // Apply maximum
    if (maxLevel > 0 && level > maxLevel)
        level = maxLevel;

    // Ensure level is always valid
    if (level < 1)
        level = 1;
    if (level > MAX_LEVEL)
        level = MAX_LEVEL;

    return level;
}

// ============================================================================
// Internal Helper Functions - Evolution Management
// ============================================================================

// Helper function to check if evolution conditions are met
static bool8 CheckEvolutionConditions(const struct EvolutionParam *params)
{
    u32 i;
    
    if (params == NULL)
        return TRUE; // No conditions means it can evolve
    
    RtcCalcLocalTime();
    enum TimeOfDay timeOfDay = GetTimeOfDay();
    u8 currentWeather = GetCurrentWeather();
    
    // Check all conditions - ALL must be met
    for (i = 0; params[i].condition != CONDITIONS_END; i++)
    {
        bool8 conditionMet = FALSE;
        
        switch (params[i].condition)
        {
            case IF_TIME:
                if (timeOfDay == params[i].arg1)
                    conditionMet = TRUE;
                break;
                
            case IF_NOT_TIME:
                if (timeOfDay != params[i].arg1)
                    conditionMet = TRUE;
                break;
                
            case IF_WEATHER:
                if (params[i].arg1 == WEATHER_RAIN)
                {
                    if (currentWeather == WEATHER_RAIN || currentWeather == WEATHER_RAIN_THUNDERSTORM || currentWeather == WEATHER_DOWNPOUR)
                        conditionMet = TRUE;
                }
                else if (params[i].arg1 == WEATHER_FOG)
                {
                    if (currentWeather == WEATHER_FOG_DIAGONAL || currentWeather == WEATHER_FOG_HORIZONTAL)
                        conditionMet = TRUE;
                }
                else if (currentWeather == params[i].arg1)
                {
                    conditionMet = TRUE;
                }
                break;
                
            default:
                // For other conditions we can't check in wild encounters (party composition, items, etc.),
                // we'll give a lower probability chance
                if ((Random() % 100) < 10)
                    conditionMet = TRUE;
                break;
        }
        
        // If any condition fails, the evolution cannot happen
        if (!conditionMet)
            return FALSE;
    }
    
    return TRUE;
}

// Get all possible evolutions for a species that can happen at a given level
static u32 GetPossibleEvolutions(u16 species, u8 level, u16 *outEvolutions, u32 maxEvolutions)
{
    const struct Evolution *evolutions = GetSpeciesEvolutions(species);
    u32 count = 0;
    u32 i;
    
    if (evolutions == NULL)
        return 0;
    
    for (i = 0; evolutions[i].method != EVOLUTIONS_END && count < maxEvolutions; i++)
    {
        bool8 canEvolve = FALSE;
        u16 targetSpecies = evolutions[i].targetSpecies;
        const struct EvolutionParam *params = evolutions[i].params;
        
        // Check if target species has a minimum level override
        #if B_SCALING_USE_OVERRIDES
        const struct EvolutionOverride *override = GetEvolutionOverride(targetSpecies);
        u8 minimumLevel = (override != NULL) ? override->minimumLevel : 30;
        #else
        u8 minimumLevel = 30;
        #endif
        
        // Check if this evolution can happen at this level
        switch (evolutions[i].method)
        {
            case EVO_LEVEL:
            case EVO_LEVEL_BATTLE_ONLY:
            {
                // For pure level evolutions with no conditions, use the param as the level
                // For evolutions with conditions (weather, time, etc.), check conditions and use minimum level
                bool8 hasConditions = (params != NULL && params[0].condition != CONDITIONS_END);
                
                if (!hasConditions)
                {
                    // Pure level evolution (e.g., Charmander -> Charmeleon at level 16)
                    if (level >= evolutions[i].param)
                        canEvolve = TRUE;
                }
                else
                {
                    // Conditional evolution - check level, conditions, and apply 20% chance
                    // This covers things like Goodra (needs rain), Espeon (needs day), etc.
                    if (level >= minimumLevel && CheckEvolutionConditions(params) && (Random() % 100) < 20)
                        canEvolve = TRUE;
                }
                break;
            }
            
            case EVO_ITEM:
            case EVO_TRADE:
                // Trade/stone evolutions - check conditions, use override minimum level, 20% chance
                if (level >= minimumLevel && CheckEvolutionConditions(params) && (Random() % 100) < 20)
                    canEvolve = TRUE;
                break;
                
            case EVO_BATTLE_END:
            case EVO_SCRIPT_TRIGGER:
            case EVO_SPIN:
                // Special trigger evolutions - 10% chance 
                if (level >= minimumLevel && (Random() % 100) < 10)
                    canEvolve = TRUE;
                break;
        }
        
        if (canEvolve)
        {
            outEvolutions[count] = targetSpecies;
            count++;
        }
    }
    
    return count;
}

// Count the number of evolution stages for a species (0 = base, 1 = stage 1, 2 = stage 2)
static u32 GetEvolutionStage(u16 species)
{
    u32 stage = 0;
    u16 currentSpecies = species;
    u32 maxIterations = 10; // Prevent infinite loops
    
    while (maxIterations-- > 0)
    {
        u32 i, j;
        u16 preEvo = SPECIES_NONE;
        
        // Search all species to find what evolves into currentSpecies
        for (i = 1; i < NUM_SPECIES; i++)
        {
            const struct Evolution *evolutions = GetSpeciesEvolutions(i);
            if (evolutions == NULL)
                continue;
            
            for (j = 0; evolutions[j].method != EVOLUTIONS_END; j++)
            {
                if (evolutions[j].targetSpecies == currentSpecies)
                {
                    preEvo = i;
                    break;
                }
            }
            
            if (preEvo != SPECIES_NONE)
                break;
        }
        
        if (preEvo == SPECIES_NONE)
            break; // No pre-evolution found, we're at the base
        
        stage++;
        currentSpecies = preEvo;
    }
    
    return stage;
}

// ============================================================================
// Public API Functions
// ============================================================================

const struct EvolutionOverride *GetEvolutionOverride(u16 species)
{
    u32 i;

    for (i = 0; gEvolutionOverrides[i].species != SPECIES_NONE; i++)
    {
        if (gEvolutionOverrides[i].species == species)
            return &gEvolutionOverrides[i];
    }

    return NULL;
}

u16 ValidateSpeciesForLevel(u16 species, u8 targetLevel, bool8 manageEvolutions)
{
    u16 possibleEvolutions[10]; // Should be enough for any branching evolution
    u32 evolutionCount;
    u32 currentStage;
    u16 currentSpecies = species;
    u32 maxIterations = 3; // Max 3 evolution stages (base -> stage 1 -> stage 2)
    
    if (!manageEvolutions)
        return species;
    
    // Try to evolve up to 3 times (handles 3-stage evolution lines)
    while (maxIterations-- > 0)
    {
        // Get current evolution stage (0 = base, 1 = stage 1, 2 = stage 2)
        currentStage = GetEvolutionStage(currentSpecies);
        
        // Get all possible evolutions at this level
        evolutionCount = GetPossibleEvolutions(currentSpecies, targetLevel, possibleEvolutions, 10);
        
        if (evolutionCount == 0)
            break; // No more evolutions possible
        
        // Apply probability logic based on evolution stage
        u8 evolveChance;
        
        if (currentStage == 0)
        {
            // Base form (e.g., Charmander)
            // For 3-stage lines: 90% chance to NOT stay as base (10% stay, 90% evolve)
            // For 2-stage lines: 80% chance to evolve
            // Check if any evolution can evolve further
            bool8 hasThirdStage = FALSE;
            u32 i;
            for (i = 0; i < evolutionCount; i++)
            {
                u16 tempEvolutions[10];
                if (GetPossibleEvolutions(possibleEvolutions[i], targetLevel, tempEvolutions, 10) > 0)
                {
                    hasThirdStage = TRUE;
                    break;
                }
            }
            
            evolveChance = hasThirdStage ? 90 : 80;
        }
        else if (currentStage == 1)
        {
            // Stage 1 form (e.g., Charmeleon)
            // For 3-stage lines: 70% chance to evolve to final stage
            // For 2-stage lines: shouldn't happen, but use 70% if it does
            evolveChance = 70;
        }
        else
        {
            // Stage 2 or higher - don't evolve further
            break;
        }
        
        // Roll to see if we evolve
        if ((Random() % 100) < evolveChance)
        {
            // Select evolution
            if (evolutionCount == 1)
            {
                // Only one option
                currentSpecies = possibleEvolutions[0];
            }
            else
            {
                // Multiple options (branching evolution) - pick randomly
                currentSpecies = possibleEvolutions[Random() % evolutionCount];
            }
        }
        else
        {
            // Didn't evolve, stay at current species
            break;
        }
    }
    
    return currentSpecies;
}

void InvalidatePartyLevelCache(void)
{
    sPartyLevelCache.cached = FALSE;
}

u8 CalculatePlayerPartyBaseLevel(u8 mode, bool8 excludeFainted)
{
    u8 baseLevel = 1;

    // Use cache if available
    if (sPartyLevelCache.cached)
    {
        switch (mode)
        {
            case LEVEL_SCALING_PARTY_AVG:
                return sPartyLevelCache.partyAverage;
            case LEVEL_SCALING_PARTY_HIGHEST:
                return sPartyLevelCache.partyHighest;
            case LEVEL_SCALING_PARTY_LOWEST:
                return sPartyLevelCache.partyLowest;
        }
    }

    // Calculate based on mode
    switch (mode)
    {
        case LEVEL_SCALING_NONE:
            return 0; // Signal to use original level

        case LEVEL_SCALING_TO_LEVEL_CAP:
            baseLevel = GetCurrentLevelCap();
            break;

        case LEVEL_SCALING_PARTY_AVG:
            baseLevel = GetPlayerPartyAverageLevel(excludeFainted);
            sPartyLevelCache.partyAverage = baseLevel;
            break;

        case LEVEL_SCALING_PARTY_HIGHEST:
            baseLevel = GetPlayerPartyHighestLevel(excludeFainted);
            sPartyLevelCache.partyHighest = baseLevel;
            break;

        case LEVEL_SCALING_PARTY_LOWEST:
            baseLevel = GetPlayerPartyLowestLevel(excludeFainted);
            sPartyLevelCache.partyLowest = baseLevel;
            break;

        default:
            baseLevel = 1;
            break;
    }

    // Mark cache as valid after first calculation
    sPartyLevelCache.cached = TRUE;

    return baseLevel;
}

const struct LevelScalingConfig *GetTrainerLevelScalingConfig(u16 trainerId)
{
    // Default configuration from config file
    static const struct LevelScalingConfig sDefaultConfig = {
        .mode = B_TRAINER_SCALING_DEFAULT_MODE,
        .levelAugmentAdd = B_TRAINER_SCALING_LEVEL_AUGMENT,
        .levelVariation = B_TRAINER_SCALING_LEVEL_VARIATION,
        .minLevel = B_TRAINER_SCALING_MIN_LEVEL,
        .maxLevel = B_TRAINER_SCALING_MAX_LEVEL,
        .manageEvolutions = B_TRAINER_SCALING_MANAGE_EVOLUTIONS,
        .excludeFainted = B_TRAINER_SCALING_EXCLUDE_FAINTED,
    };

    // Check bounds
    if (trainerId >= ARRAY_COUNT(gTrainerLevelScalingRules))
        return &sDefaultConfig;

    // Get config from rules array
    const struct LevelScalingConfig *config = &gTrainerLevelScalingRules[trainerId];

    // If mode is 0 (LEVEL_SCALING_NONE), check if this is:
    // 1. An explicit opt-out (trainer has config with mode = NONE), OR
    // 2. An undefined entry (zero-initialized)
    //
    // We distinguish by checking if ANY field is non-zero
    // If all fields are zero, it's undefined and we use default
    // If mode is NONE but other fields are set, it's an explicit opt-out
    if (config->mode == LEVEL_SCALING_NONE)
    {
        // Check if any other field is non-zero (indicates explicit config)
        if (config->levelAugmentAdd == 0 &&
            config->levelVariation == 0 &&
            config->minLevel == 0 &&
            config->maxLevel == 0 &&
            config->manageEvolutions == FALSE &&
            config->excludeFainted == FALSE)
        {
            // All fields zero = undefined entry, use default
            return &sDefaultConfig;
        }
        // else: Explicit NONE config, return it
    }

    return config;
}

u8 CalculateScaledLevel(const struct LevelScalingConfig *config, u8 originalLevel)
{
    u8 baseLevel;
    s16 adjustedLevel;

    // Get base level from scaling mode
    baseLevel = CalculatePlayerPartyBaseLevel(config->mode, config->excludeFainted);

    // If mode is NONE, return original
    if (baseLevel == 0)
        return originalLevel;

    // Apply augmentation (can be positive or negative)
    adjustedLevel = (s16)baseLevel + (s16)config->levelAugmentAdd;

    // Ensure we don't go negative
    if (adjustedLevel < 1)
        adjustedLevel = 1;

    // Apply random variation
    adjustedLevel = ApplyLevelVariation((u8)adjustedLevel, config->levelVariation);

    // Clamp to configured min/max
    adjustedLevel = ClampLevel((u8)adjustedLevel, config->minLevel, config->maxLevel);

    if (B_SCALING_DEBUG_PRINT)
    {
        // Debug output would go here
    }

    return (u8)adjustedLevel;
}

u8 CalculateWildScaledLevel(u16 species, u8 minLevel, u8 maxLevel)
{
    #if B_WILD_SCALING_ENABLED
    static const struct LevelScalingConfig sWildConfig = {
        .mode = B_WILD_SCALING_DEFAULT_MODE,
        .levelAugmentAdd = B_WILD_SCALING_LEVEL_AUGMENT,
        .levelVariation = B_WILD_SCALING_LEVEL_VARIATION,
        .minLevel = B_WILD_SCALING_MIN_LEVEL,
        .maxLevel = B_WILD_SCALING_MAX_LEVEL,
        .manageEvolutions = B_WILD_SCALING_MANAGE_EVOLUTIONS,
        .excludeFainted = B_WILD_SCALING_EXCLUDE_FAINTED,
    };

    // Use the average of min and max as the base level for scaling
    u8 originalLevel = (minLevel + maxLevel) / 2;
    u8 newLevel = CalculateScaledLevel(&sWildConfig, originalLevel);

    // Hard cap: scaled level must be between the encounter table's min and max
    if (newLevel < minLevel)
        newLevel = minLevel;
    if (newLevel > maxLevel)
        newLevel = maxLevel;

    // Note: Species validation should happen in wild encounter code
    // as we can't modify the species from this function

    return newLevel;
    #else
    return (minLevel + maxLevel) / 2;
    #endif
}

// Calculate scaled species for wild encounters (called from wild_encounter.c)
u16 CalculateWildScaledSpecies(u16 species, u8 scaledLevel)
{
    #if B_WILD_SCALING_ENABLED && B_WILD_SCALING_MANAGE_EVOLUTIONS
    return ValidateSpeciesForLevel(species, scaledLevel, TRUE);
    #else
    return species;
    #endif
}

#endif // B_LEVEL_SCALING_ENABLED
