#include "global.h"
#include "wild_encounter.h"
#include "pokemon.h"
#include "metatile_behavior.h"
#include "fieldmap.h"
#include "follower_npc.h"
#include "random.h"
#include "field_player_avatar.h"
#include "event_data.h"
#include "safari_zone.h"
#include "overworld.h"
#include "pokeblock.h"
#include "battle_setup.h"
#include "roamer.h"
#include "tv.h"
#include "link.h"
#include "script.h"
#include "battle_pike.h"
#include "battle_pyramid.h"
#include "constants/abilities.h"
#include "constants/game_stat.h"
#include "constants/item.h"
#include "constants/items.h"
#include "constants/layouts.h"
#include "constants/weather.h"
#include "constants/pokemon.h"
#include "rtc.h"
#include "caps.h"
#include "nuzlocke.h"

// Global variable to track if current wild Pokemon is catchable in Nuzlocke
static bool8 gWildPokemonIsCatchableInNuzlocke = FALSE;

bool8 IsWildPokemonCatchableInNuzlocke(void)
{
    return gWildPokemonIsCatchableInNuzlocke;
}

// Evolution method constants (define these if not present elsewhere)
#define EVO_LEVEL_DAY     0x1001
#define EVO_LEVEL_NIGHT   0x1002
#define EVO_LEVEL_MALE    0x1003
#define EVO_LEVEL_FEMALE  0x1004

// Time of day constants (define these if not present elsewhere)
#define TIME_OF_DAY_DAY     0
#define TIME_OF_DAY_NIGHT   1

static u16 GetWildEvolvedSpecies(u16 species, u8 level, u8 gender, enum TimeOfDay timeOfDay);

extern const u8 EventScript_SprayWoreOff[];

#define MAX_ENCOUNTER_RATE 2880

#define NUM_FEEBAS_SPOTS 6

// Number of accessible fishing spots in each section of Route 119
// Each section is an area of the route between the y coordinates in sRoute119WaterTileData
#define NUM_FISHING_SPOTS_1 131
#define NUM_FISHING_SPOTS_2 167
#define NUM_FISHING_SPOTS_3 149
#define NUM_FISHING_SPOTS (NUM_FISHING_SPOTS_1 + NUM_FISHING_SPOTS_2 + NUM_FISHING_SPOTS_3)

#define WILD_CHECK_REPEL    (1 << 0)
#define WILD_CHECK_KEEN_EYE (1 << 1)

static u16 FeebasRandom(void);
static void FeebasSeedRng(u16 seed);
static void UpdateChainFishingStreak();
static bool8 IsWildLevelAllowedByRepel(u8 level);
static void ApplyFluteEncounterRateMod(u32 *encRate);
static void ApplyCleanseTagEncounterRateMod(u32 *encRate);
#ifdef BUGFIX
static bool8 TryGetAbilityInfluencedWildMonIndex(const struct WildPokemon *wildMon, u8 type, u16 ability, u8 *monIndex, u32 size);
#else
static bool8 TryGetAbilityInfluencedWildMonIndex(const struct WildPokemon *wildMon, u8 type, u16 ability, u8 *monIndex);
#endif
static bool8 IsAbilityAllowingEncounter(u8 level);

EWRAM_DATA static u8 sWildEncountersDisabled = 0;
EWRAM_DATA static u32 sFeebasRngValue = 0;
EWRAM_DATA bool8 gIsFishingEncounter = 0;
EWRAM_DATA bool8 gIsSurfingEncounter = 0;
EWRAM_DATA u8 gChainFishingDexNavStreak = 0;

// Cache for wild encounter header lookup to avoid repeated linear searches
// Note: EWRAM variables are zero-initialized, cache is marked invalid by sCacheValid flag
EWRAM_DATA static u16 sCachedWildHeaderId;
EWRAM_DATA static u8 sCachedMapGroup;
EWRAM_DATA static u8 sCachedMapNum;
EWRAM_DATA static bool8 sCachedNuzlockeMode;
EWRAM_DATA static bool8 sCacheValid;

#include "data/wild_encounters.h"
#include "nuzlocke.h"

// Helper function to get the appropriate wild mon headers
static const struct WildPokemonHeader *GetWildMonHeaders(void)
{
    // Always return the main wild mon headers now since we have both normal and Nuzlocke encounters in one file
    return gWildMonHeaders;
}

// Helper function to get wild mon header by ID
static const struct WildPokemonHeader *GetWildMonHeaderById(u32 headerId)
{
    return &GetWildMonHeaders()[headerId];
    }
    
static const struct WildPokemon sWildFeebas = {20, 25, SPECIES_FEEBAS};

static const u16 sRoute119WaterTileData[] =
{
//yMin, yMax, numSpots in previous sections
     0,  45,  0,
    46,  91,  NUM_FISHING_SPOTS_1,
    92, 139,  NUM_FISHING_SPOTS_1 + NUM_FISHING_SPOTS_2,
};

void DisableWildEncounters(bool8 disabled)
{
    sWildEncountersDisabled = disabled;
}

void InvalidateWildHeaderCache(void)
{
    sCacheValid = FALSE;
}

// Each fishing spot on Route 119 is given a number between 1 and NUM_FISHING_SPOTS inclusive.
// The number is determined by counting the valid fishing spots left to right top to bottom.
// The map is divided into three sections, with each section having a pre-counted number of
// fishing spots to start from to avoid counting a large number of spots at the bottom of the map.
// Note that a spot is considered valid if it is surfable and not a waterfall. To exclude all
// of the inaccessible water metatiles (so that they can't be selected as a Feebas spot) they
// use a different metatile that isn't actually surfable because it has MB_NORMAL instead.
// This function is given the coordinates and section of a fishing spot and returns which number it is.
static u16 GetFeebasFishingSpotId(s16 targetX, s16 targetY, u8 section)
{
    u16 x, y;
    u16 yMin = sRoute119WaterTileData[section * 3 + 0];
    u16 yMax = sRoute119WaterTileData[section * 3 + 1];
    u16 spotId = sRoute119WaterTileData[section * 3 + 2];

    for (y = yMin; y <= yMax; y++)
    {
        for (x = 0; x < gMapHeader.mapLayout->width; x++)
        {
            u8 behavior = MapGridGetMetatileBehaviorAt(x + MAP_OFFSET, y + MAP_OFFSET);
            if (MetatileBehavior_IsSurfableAndNotWaterfall(behavior) == TRUE)
            {
                spotId++;
                if (targetX == x && targetY == y)
                    return spotId;
            }
        }
    }
    return spotId + 1;
}

static bool8 CheckFeebas(void)
{
    u8 i;
    u16 feebasSpots[NUM_FEEBAS_SPOTS];
    s16 x, y;
    u8 route119Section = 0;
    u16 spotId;

    if (gSaveBlock1Ptr->location.mapGroup == MAP_GROUP(MAP_ROUTE119)
     && gSaveBlock1Ptr->location.mapNum == MAP_NUM(MAP_ROUTE119))
    {
        GetXYCoordsOneStepInFrontOfPlayer(&x, &y);
        x -= MAP_OFFSET;
        y -= MAP_OFFSET;

        // Get which third of the map the player is in
        if (y >= sRoute119WaterTileData[3 * 0 + 0] && y <= sRoute119WaterTileData[3 * 0 + 1])
            route119Section = 0;
        if (y >= sRoute119WaterTileData[3 * 1 + 0] && y <= sRoute119WaterTileData[3 * 1 + 1])
            route119Section = 1;
        if (y >= sRoute119WaterTileData[3 * 2 + 0] && y <= sRoute119WaterTileData[3 * 2 + 1])
            route119Section = 2;

        // 50% chance of encountering Feebas (assuming this is a Feebas spot)
        if (Random() % 100 > 49)
            return FALSE;

        FeebasSeedRng(gSaveBlock1Ptr->dewfordTrends[0].rand);

        // Assign each Feebas spot to a random fishing spot.
        // Randomness is fixed depending on the seed above.
        for (i = 0; i != NUM_FEEBAS_SPOTS;)
        {
            feebasSpots[i] = FeebasRandom() % NUM_FISHING_SPOTS;
            if (feebasSpots[i] == 0)
                feebasSpots[i] = NUM_FISHING_SPOTS;

            // < 1 below is a pointless check, it will never be TRUE.
            // >= 4 to skip fishing spots 1-3, because these are inaccessible
            // spots at the top of the map, at (9,7), (7,13), and (15,16).
            // The first accessible fishing spot is spot 4 at (18,18).
            if (feebasSpots[i] < 1 || feebasSpots[i] >= 4)
                i++;
        }

        // Check which fishing spot the player is at, and see if
        // it matches any of the Feebas spots.
        spotId = GetFeebasFishingSpotId(x, y, route119Section);
        for (i = 0; i < NUM_FEEBAS_SPOTS; i++)
        {
            if (spotId == feebasSpots[i])
                return TRUE;
        }
    }
    return FALSE;
}

static u16 FeebasRandom(void)
{
    sFeebasRngValue = ISO_RANDOMIZE2(sFeebasRngValue);
    return sFeebasRngValue >> 16;
}

static void FeebasSeedRng(u16 seed)
{
    sFeebasRngValue = seed;
}

// LAND_WILD_COUNT (6 slots)
u32 ChooseWildMonIndex_Land(void)
{
    u8 wildMonIndex = 0;
    bool8 swap = FALSE;
    
    // In Nuzlocke mode, use equal distribution for all 6 slots
    if (IsNuzlockeActive())
    {
        u8 rand = Random() % 100;
        
        // Equal distribution: ~16.67% per slot (100 / 6)
        // We'll use 17% for slots 0-3 and 16% for slots 4-5 to total 100%
        if (rand < 17)
            wildMonIndex = 0;
        else if (rand < 34)
            wildMonIndex = 1;
        else if (rand < 51)
            wildMonIndex = 2;
        else if (rand < 68)
            wildMonIndex = 3;
        else if (rand < 84)
            wildMonIndex = 4;
        else
            wildMonIndex = 5;
    }
    else
    {
        // Normal mode: use standard encounter distribution
        // Rates: [35, 30, 20, 10, 3, 2] = 100 total
        u8 rand = Random() % ENCOUNTER_CHANCE_LAND_MONS_TOTAL;

        if (rand < ENCOUNTER_CHANCE_LAND_MONS_SLOT_0)
            wildMonIndex = 0;
        else if (rand >= ENCOUNTER_CHANCE_LAND_MONS_SLOT_0 && rand < ENCOUNTER_CHANCE_LAND_MONS_SLOT_1)
            wildMonIndex = 1;
        else if (rand >= ENCOUNTER_CHANCE_LAND_MONS_SLOT_1 && rand < ENCOUNTER_CHANCE_LAND_MONS_SLOT_2)
            wildMonIndex = 2;
        else if (rand >= ENCOUNTER_CHANCE_LAND_MONS_SLOT_2 && rand < ENCOUNTER_CHANCE_LAND_MONS_SLOT_3)
            wildMonIndex = 3;
        else if (rand >= ENCOUNTER_CHANCE_LAND_MONS_SLOT_3 && rand < ENCOUNTER_CHANCE_LAND_MONS_SLOT_4)
            wildMonIndex = 4;
        else // rand >= ENCOUNTER_CHANCE_LAND_MONS_SLOT_4 (which includes SLOT_5)
            wildMonIndex = 5;
    }

    if (LURE_STEP_COUNT != 0 && (Random() % 10 < 2))
        swap = TRUE;

    if (swap)
        wildMonIndex = 5 - wildMonIndex;

    return wildMonIndex;
}

// WATER_WILD_COUNT
u32 ChooseWildMonIndex_Water(void)
{
    u32 wildMonIndex = 0;
    bool8 swap = FALSE;
    
    // In Nuzlocke mode, use equal distribution for all 5 slots
    if (IsNuzlockeActive())
    {
        u8 rand = Random() % 100;
        
        // Equal distribution: each slot gets 20% chance
        if (rand < 20)
            wildMonIndex = 0;
        else if (rand < 40)
            wildMonIndex = 1;
        else if (rand < 60)
            wildMonIndex = 2;
        else if (rand < 80)
            wildMonIndex = 3;
        else
            wildMonIndex = 4;
    }
    else
    {
        // Normal mode: use standard encounter distribution
        u8 rand = Random() % ENCOUNTER_CHANCE_WATER_MONS_TOTAL;

        if (rand < ENCOUNTER_CHANCE_WATER_MONS_SLOT_0)
            wildMonIndex = 0;
        else if (rand >= ENCOUNTER_CHANCE_WATER_MONS_SLOT_0 && rand < ENCOUNTER_CHANCE_WATER_MONS_SLOT_1)
            wildMonIndex = 1;
        else if (rand >= ENCOUNTER_CHANCE_WATER_MONS_SLOT_1 && rand < ENCOUNTER_CHANCE_WATER_MONS_SLOT_2)
            wildMonIndex = 2;
        else if (rand >= ENCOUNTER_CHANCE_WATER_MONS_SLOT_2 && rand < ENCOUNTER_CHANCE_WATER_MONS_SLOT_3)
            wildMonIndex = 3;
        else
            wildMonIndex = 4;
    }

    if (LURE_STEP_COUNT != 0 && (Random() % 10 < 2))
        swap = TRUE;

    if (swap)
        wildMonIndex = 4 - wildMonIndex;

    return wildMonIndex;
}

// ROCK_WILD_COUNT
u32 ChooseWildMonIndex_Rocks(void)
{
    u32 wildMonIndex = 0;
    bool8 swap = FALSE;
    
    // In Nuzlocke mode, use equal distribution for all 5 slots
    if (IsNuzlockeActive())
    {
        u8 rand = Random() % 100;
        
        // Equal distribution: each slot gets 20% chance
        if (rand < 20)
            wildMonIndex = 0;
        else if (rand < 40)
            wildMonIndex = 1;
        else if (rand < 60)
            wildMonIndex = 2;
        else if (rand < 80)
            wildMonIndex = 3;
        else
            wildMonIndex = 4;
    }
    else
    {
        // Normal mode: use standard encounter distribution
        u8 rand = Random() % ENCOUNTER_CHANCE_ROCK_SMASH_MONS_TOTAL;

        if (rand < ENCOUNTER_CHANCE_ROCK_SMASH_MONS_SLOT_0)
            wildMonIndex = 0;
        else if (rand >= ENCOUNTER_CHANCE_ROCK_SMASH_MONS_SLOT_0 && rand < ENCOUNTER_CHANCE_ROCK_SMASH_MONS_SLOT_1)
            wildMonIndex = 1;
        else if (rand >= ENCOUNTER_CHANCE_ROCK_SMASH_MONS_SLOT_1 && rand < ENCOUNTER_CHANCE_ROCK_SMASH_MONS_SLOT_2)
            wildMonIndex = 2;
        else if (rand >= ENCOUNTER_CHANCE_ROCK_SMASH_MONS_SLOT_2 && rand < ENCOUNTER_CHANCE_ROCK_SMASH_MONS_SLOT_3)
            wildMonIndex = 3;
        else
            wildMonIndex = 4;
    }

    if (LURE_STEP_COUNT != 0 && (Random() % 10 < 2))
        swap = TRUE;

    if (swap)
        wildMonIndex = 4 - wildMonIndex;

    return wildMonIndex;
}

// FISH_WILD_COUNT
static u32 ChooseWildMonIndex_Fishing(u8 rod)
{
    u8 wildMonIndex = 0;
    bool8 swap = FALSE;
    
    if (LURE_STEP_COUNT != 0 && (Random() % 10 < 2))
        swap = TRUE;

    // In Nuzlocke mode, use equal distribution
    if (IsNuzlockeActive())
    {
        u8 rand = Random() % 100;
        
        switch (rod)
        {
        case OLD_ROD:
            // 2 slots: 50% each
            if (rand < 50)
                wildMonIndex = 0;
            else
                wildMonIndex = 1;

            if (swap)
                wildMonIndex = 1 - wildMonIndex;
            break;
            
        case GOOD_ROD:
            // 3 slots (2, 3, 4): ~33% each
            if (rand < 33)
                wildMonIndex = 2;
            else if (rand < 66)
                wildMonIndex = 3;
            else
                wildMonIndex = 4;

            if (swap)
                wildMonIndex = 6 - wildMonIndex;
            break;
            
        case SUPER_ROD:
            // 5 slots (5, 6, 7, 8, 9): 20% each
            if (rand < 20)
                wildMonIndex = 5;
            else if (rand < 40)
                wildMonIndex = 6;
            else if (rand < 60)
                wildMonIndex = 7;
            else if (rand < 80)
                wildMonIndex = 8;
            else
                wildMonIndex = 9;

            if (swap)
                wildMonIndex = 14 - wildMonIndex;
            break;
        }
    }
    else
    {
        // Normal mode: use standard encounter distribution
        u8 rand = Random() % max(max(ENCOUNTER_CHANCE_FISHING_MONS_OLD_ROD_TOTAL, ENCOUNTER_CHANCE_FISHING_MONS_GOOD_ROD_TOTAL),
                                 ENCOUNTER_CHANCE_FISHING_MONS_SUPER_ROD_TOTAL);

        switch (rod)
        {
        case OLD_ROD:
            if (rand < ENCOUNTER_CHANCE_FISHING_MONS_OLD_ROD_SLOT_0)
                wildMonIndex = 0;
            else
                wildMonIndex = 1;

            if (swap)
                wildMonIndex = 1 - wildMonIndex;
            break;
        case GOOD_ROD:
            if (rand < ENCOUNTER_CHANCE_FISHING_MONS_GOOD_ROD_SLOT_2)
                wildMonIndex = 2;
            if (rand >= ENCOUNTER_CHANCE_FISHING_MONS_GOOD_ROD_SLOT_2 && rand < ENCOUNTER_CHANCE_FISHING_MONS_GOOD_ROD_SLOT_3)
                wildMonIndex = 3;
            if (rand >= ENCOUNTER_CHANCE_FISHING_MONS_GOOD_ROD_SLOT_3 && rand < ENCOUNTER_CHANCE_FISHING_MONS_GOOD_ROD_SLOT_4)
                wildMonIndex = 4;

            if (swap)
                wildMonIndex = 6 - wildMonIndex;
            break;
        case SUPER_ROD:
            if (rand < ENCOUNTER_CHANCE_FISHING_MONS_SUPER_ROD_SLOT_5)
                wildMonIndex = 5;
            if (rand >= ENCOUNTER_CHANCE_FISHING_MONS_SUPER_ROD_SLOT_5 && rand < ENCOUNTER_CHANCE_FISHING_MONS_SUPER_ROD_SLOT_6)
                wildMonIndex = 6;
            if (rand >= ENCOUNTER_CHANCE_FISHING_MONS_SUPER_ROD_SLOT_6 && rand < ENCOUNTER_CHANCE_FISHING_MONS_SUPER_ROD_SLOT_7)
                wildMonIndex = 7;
            if (rand >= ENCOUNTER_CHANCE_FISHING_MONS_SUPER_ROD_SLOT_7 && rand < ENCOUNTER_CHANCE_FISHING_MONS_SUPER_ROD_SLOT_8)
                wildMonIndex = 8;
            if (rand >= ENCOUNTER_CHANCE_FISHING_MONS_SUPER_ROD_SLOT_8 && rand < ENCOUNTER_CHANCE_FISHING_MONS_SUPER_ROD_SLOT_9)
                wildMonIndex = 9;

            if (swap)
                wildMonIndex = 14 - wildMonIndex;
            break;
        }
    }
    
    return wildMonIndex;
}

u8 GetAveragePartyLevel(void)
{
    u8 i, count = 0, totalLevel = 0;
    for (i = 0; i < PARTY_SIZE; i++)
    {
        if (!GetMonData(&gPlayerParty[i], MON_DATA_SANITY_IS_EGG))
        {
            u8 level = GetMonData(&gPlayerParty[i], MON_DATA_LEVEL);
            if (level > 0)
            {
                totalLevel += level;
                count++;
            }
        }
    }
    if (count == 0)
        return 2; // Failsafe: minimum wild level
    return (totalLevel + count / 2) / count; // Rounded average
}

u8 GetHighestPartyLevel(void)
{
    u8 i, highest = 0;
    for (i = 0; i < PARTY_SIZE; i++)
    {
        if (!GetMonData(&gPlayerParty[i], MON_DATA_SANITY_IS_EGG))
        {
            u8 level = GetMonData(&gPlayerParty[i], MON_DATA_LEVEL);
            if (level > highest)
                highest = level;
        }
    }
    return highest;
}

static u8 ChooseWildMonLevel(const struct WildPokemon *wildPokemon, u8 wildMonIndex, u8 area)
{
    u8 avgLevel = GetAveragePartyLevel();
    u8 highestLevel = GetHighestPartyLevel();
    u8 wildMin = 2, wildMax = 100;
    u8 minLevel, maxLevel;
    u32 levelCap = GetCurrentLevelCap();
    u8 difficultyBuffer = 3; // Wilds can be up to 3 above average, and 5 below highest

    // Handle early-game balance
    if (highestLevel <= 15)
    {
        minLevel = avgLevel > 2 ? avgLevel - 2 : wildMin;
        maxLevel = avgLevel + 1;
    }
    else
    {
        minLevel = avgLevel > 3 ? avgLevel - 3 : wildMin;
        maxLevel = avgLevel + difficultyBuffer;
    }

    // Clamp so that wilds aren't more than 5 below your highest level
    u8 minAllowed = highestLevel > 5 ? highestLevel - 5 : wildMin;
    if (minLevel < minAllowed)
        minLevel = minAllowed;

    // Final clamping to bounds and level cap
    if (minLevel < wildMin)
        minLevel = wildMin;
    if (maxLevel > wildMax)
        maxLevel = wildMax;
    if (maxLevel > levelCap)
        maxLevel = levelCap;
    if (minLevel > maxLevel)
        minLevel = maxLevel;

    return minLevel + (Random() % (maxLevel - minLevel + 1));
}

u16 GetCurrentMapWildMonHeaderId(void)
{
    u8 currentMapGroup = gSaveBlock1Ptr->location.mapGroup;
    u8 currentMapNum = gSaveBlock1Ptr->location.mapNum;
    bool8 useNuzlockeEncounters = IsNuzlockeActive();
    
    // Check if cached value is still valid
    if (sCacheValid &&
        sCachedMapGroup == currentMapGroup && 
        sCachedMapNum == currentMapNum && 
        sCachedNuzlockeMode == useNuzlockeEncounters)
    {
        // Handle altering cave special case (it can change without map change)
        if (currentMapGroup == MAP_GROUP(MAP_ALTERING_CAVE) &&
            currentMapNum == MAP_NUM(MAP_ALTERING_CAVE))
        {
            u16 alteringCaveId = VarGet(VAR_ALTERING_CAVE_WILD_SET);
            if (alteringCaveId >= NUM_ALTERING_CAVE_TABLES)
                alteringCaveId = 0;
            return sCachedWildHeaderId + alteringCaveId;
        }
        return sCachedWildHeaderId;
    }
    
    // Cache miss - need to search for the header
    u16 i;
    const struct WildPokemonHeader *wildHeaders = GetWildMonHeaders();
    u16 currentTime = GetTimeOfDay();
    u16 normalHeaderId = HEADER_NONE;
    u16 nuzlockeHeaderId = HEADER_NONE;

    // Single pass through headers
    for (i = 0; ; i++)
    {
        const struct WildPokemonHeader *wildHeader = &wildHeaders[i];
        if (wildHeader->mapGroup == MAP_GROUP(MAP_UNDEFINED))
            break;

        if (wildHeaders[i].mapGroup == currentMapGroup &&
            wildHeaders[i].mapNum == currentMapNum)
        {
            // Check if this header has encounter data for current time
            const struct WildPokemonInfo *landMonsInfo = wildHeader->encounterTypes[currentTime].landMonsInfo;
            
            if (landMonsInfo != NULL)
            {
                // Determine if this is a Nuzlocke entry by checking the pattern in the generated header
                // In the generated header, normal entries come first, then Nuzlocke entries
                // We can identify Nuzlocke entries by checking if we already found a normal entry
                if (normalHeaderId == HEADER_NONE)
                {
                    // This is the first entry we found for this map - assume it's normal
                    normalHeaderId = i;
                }
                else
                {
                    // This is a subsequent entry for the same map - assume it's Nuzlocke
                    nuzlockeHeaderId = i;
                    break; // We found both, no need to continue searching
                }
            }
        }
    }

    // Select the appropriate header
    u16 targetHeaderId = HEADER_NONE;
    if (useNuzlockeEncounters && nuzlockeHeaderId != HEADER_NONE)
    {
        targetHeaderId = nuzlockeHeaderId;
    }
    else if (normalHeaderId != HEADER_NONE)
    {
        targetHeaderId = normalHeaderId;
    }

    // Update cache (store base header ID, without altering cave offset)
    sCachedWildHeaderId = targetHeaderId;
    sCachedMapGroup = currentMapGroup;
    sCachedMapNum = currentMapNum;
    sCachedNuzlockeMode = useNuzlockeEncounters;
    sCacheValid = TRUE;

    // Handle altering cave special case
    if (targetHeaderId != HEADER_NONE)
    {
        if (currentMapGroup == MAP_GROUP(MAP_ALTERING_CAVE) &&
            currentMapNum == MAP_NUM(MAP_ALTERING_CAVE))
        {
            u16 alteringCaveId = VarGet(VAR_ALTERING_CAVE_WILD_SET);
            if (alteringCaveId >= NUM_ALTERING_CAVE_TABLES)
                alteringCaveId = 0;

            targetHeaderId += alteringCaveId;
        }
    }

    return targetHeaderId;
}

enum TimeOfDay GetTimeOfDayForEncounters(u32 headerId, enum WildPokemonArea area)
{
    const struct WildPokemonInfo *wildMonInfo;
    const struct WildPokemonHeader *wildHeaders = GetWildMonHeaders();
    enum TimeOfDay timeOfDay = GetTimeOfDay();

    if (!OW_TIME_OF_DAY_ENCOUNTERS)
        return TIME_OF_DAY_DEFAULT;

    if (InBattlePike() || CurrentBattlePyramidLocation() != PYRAMID_LOCATION_NONE)
    {
        return OW_TIME_OF_DAY_FALLBACK;
    }
    else
    {
        switch (area)
        {
        default:
        case WILD_AREA_LAND:
            wildMonInfo = wildHeaders[headerId].encounterTypes[timeOfDay].landMonsInfo;
            break;
        case WILD_AREA_WATER:
            wildMonInfo = wildHeaders[headerId].encounterTypes[timeOfDay].waterMonsInfo;
            break;
        case WILD_AREA_ROCKS:
            wildMonInfo = wildHeaders[headerId].encounterTypes[timeOfDay].rockSmashMonsInfo;
            break;
        case WILD_AREA_FISHING:
            wildMonInfo = wildHeaders[headerId].encounterTypes[timeOfDay].fishingMonsInfo;
            break;
        case WILD_AREA_HIDDEN:
            wildMonInfo = wildHeaders[headerId].encounterTypes[timeOfDay].hiddenMonsInfo;
            break;
        }
    }

    if (wildMonInfo == NULL && !OW_TIME_OF_DAY_DISABLE_FALLBACK)
        return OW_TIME_OF_DAY_FALLBACK;
    else
        return timeOfDay;
}

u8 PickWildMonNature(void)
{
    u8 i;
    struct Pokeblock *safariPokeblock;
    u8 natures[NUM_NATURES];

    if (GetSafariZoneFlag() == TRUE && Random() % 100 < 80)
    {
        safariPokeblock = SafariZoneGetActivePokeblock();
        if (safariPokeblock != NULL)
        {
            for (i = 0; i < NUM_NATURES; i++)
                natures[i] = i;
            Shuffle(natures, NUM_NATURES, sizeof(natures[0]));
            for (i = 0; i < NUM_NATURES; i++)
            {
                if (PokeblockGetGain(natures[i], safariPokeblock) > 0)
                    return natures[i];
            }
        }
    }
    // check synchronize for a Pokémon with the same ability
    if (!GetMonData(&gPlayerParty[0], MON_DATA_SANITY_IS_EGG)
        && GetMonAbility(&gPlayerParty[0]) == ABILITY_SYNCHRONIZE
        && (OW_SYNCHRONIZE_NATURE >= GEN_8 || Random() % 2 == 0))
    {
        return GetMonData(&gPlayerParty[0], MON_DATA_PERSONALITY) % NUM_NATURES;
    }

    // random nature
    return Random() % NUM_NATURES;
}

void CreateWildMon(u16 species, u8 level)
{
    // Reset Nuzlocke indicator state
    gWildPokemonIsCatchableInNuzlocke = FALSE;
    
    // Nuzlocke encounter tracking - check status but don't mark yet
    if (IsNuzlockeActive() && FlagGet(FLAG_SYS_POKEDEX_GET))
    {
        u8 currentLocation = GetCurrentRegionMapSectionId();
        
        DebugPrintfLevel(MGBA_LOG_ERROR, "NUZLOCKE: CreateWildMon location=%d, species=%d", currentLocation, species);
        
        // Check if this location has already had its "real" encounter
        bool8 locationAlreadyUsed = HasWildPokemonBeenSeenInLocation(currentLocation, FALSE);
        
        DebugPrintfLevel(MGBA_LOG_ERROR, "NUZLOCKE: locationAlreadyUsed=%d", locationAlreadyUsed);
        
        if (locationAlreadyUsed)
        {
            // Location already used - not catchable
            DebugPrintfLevel(MGBA_LOG_ERROR, "NUZLOCKE: Location already used - NOT catchable");
        }
        else
        {
            // Location not used yet - check duplicate clause
            if (PlayerOwnsSpecies(species))
            {
                // Duplicate species - hunting continues
                DebugPrintfLevel(MGBA_LOG_ERROR, "NUZLOCKE: Duplicate species - hunting continues");
            }
            else
            {
                // New species - catchable!
                gWildPokemonIsCatchableInNuzlocke = TRUE;
                DebugPrintfLevel(MGBA_LOG_ERROR, "NUZLOCKE: New species - CATCHABLE!");
            }
        }
    }

    bool32 checkCuteCharm = TRUE;

    ZeroEnemyPartyMons();

    switch (gSpeciesInfo[species].genderRatio)
    {
    case MON_MALE:
    case MON_FEMALE:
    case MON_GENDERLESS:
        checkCuteCharm = FALSE;
        break;
    }

    if (checkCuteCharm
        && !GetMonData(&gPlayerParty[0], MON_DATA_SANITY_IS_EGG)
        && GetMonAbility(&gPlayerParty[0]) == ABILITY_CUTE_CHARM
        && Random() % 3 != 0)
    {
        u16 leadingMonSpecies = GetMonData(&gPlayerParty[0], MON_DATA_SPECIES);
        u32 leadingMonPersonality = GetMonData(&gPlayerParty[0], MON_DATA_PERSONALITY);
        u8 gender = GetGenderFromSpeciesAndPersonality(leadingMonSpecies, leadingMonPersonality);

        // misses mon is genderless check, although no genderless mon can have cute charm as ability
        if (gender == MON_FEMALE)
            gender = MON_MALE;
        else
            gender = MON_FEMALE;

        CreateMonWithGenderNatureLetter(&gEnemyParty[0], species, level, USE_RANDOM_IVS, gender, PickWildMonNature(), 0);
        return;
    }

    // Determine gender for wild mon (randomly, or use Cute Charm logic if needed)
    u8 gender = MON_MALE;
    u8 genderRatio = gSpeciesInfo[species].genderRatio;
    if (genderRatio == MON_MALE)
        gender = MON_MALE;
    else if (genderRatio == MON_FEMALE)
        gender = MON_FEMALE;
    else if (genderRatio == MON_GENDERLESS)
        gender = MON_GENDERLESS;
    else
        gender = (Random() % 254 < genderRatio) ? MON_FEMALE : MON_MALE;

    // Get time of day for wild encounter
    enum TimeOfDay timeOfDay = GetTimeOfDay();

    // Determine chance to evolve wild Pokémon
    u16 evolvedSpecies = species;
        if (Random() % 100 < 50) // 50% chance
    {
        evolvedSpecies = GetWildEvolvedSpecies(species, level, gender, timeOfDay);
    }

    // Now create the wild mon as usual
    CreateMonWithNature(&gEnemyParty[0], evolvedSpecies, level, USE_RANDOM_IVS, PickWildMonNature());
}
#ifdef BUGFIX
#define TRY_GET_ABILITY_INFLUENCED_WILD_MON_INDEX(wildPokemon, type, ability, ptr, count) TryGetAbilityInfluencedWildMonIndex(wildPokemon, type, ability, ptr, count)
#else
#define TRY_GET_ABILITY_INFLUENCED_WILD_MON_INDEX(wildPokemon, type, ability, ptr, count) TryGetAbilityInfluencedWildMonIndex(wildPokemon, type, ability, ptr)
#endif

static bool8 TryGenerateWildMon(const struct WildPokemonInfo *wildMonInfo, enum WildPokemonArea area, u8 flags)
{
    u8 wildMonIndex = 0;
    u8 level;

    switch (area)
    {
    case WILD_AREA_LAND:
        if (TRY_GET_ABILITY_INFLUENCED_WILD_MON_INDEX(wildMonInfo->wildPokemon, TYPE_STEEL, ABILITY_MAGNET_PULL, &wildMonIndex, LAND_WILD_COUNT))
            break;
        if (TRY_GET_ABILITY_INFLUENCED_WILD_MON_INDEX(wildMonInfo->wildPokemon, TYPE_ELECTRIC, ABILITY_STATIC, &wildMonIndex, LAND_WILD_COUNT))
            break;
        if (OW_LIGHTNING_ROD >= GEN_8 && TRY_GET_ABILITY_INFLUENCED_WILD_MON_INDEX(wildMonInfo->wildPokemon, TYPE_ELECTRIC, ABILITY_LIGHTNING_ROD, &wildMonIndex, LAND_WILD_COUNT))
            break;
        if (OW_FLASH_FIRE >= GEN_8 && TRY_GET_ABILITY_INFLUENCED_WILD_MON_INDEX(wildMonInfo->wildPokemon, TYPE_FIRE, ABILITY_FLASH_FIRE, &wildMonIndex, LAND_WILD_COUNT))
            break;
        if (OW_HARVEST >= GEN_8 && TRY_GET_ABILITY_INFLUENCED_WILD_MON_INDEX(wildMonInfo->wildPokemon, TYPE_GRASS, ABILITY_HARVEST, &wildMonIndex, LAND_WILD_COUNT))
            break;
        if (OW_STORM_DRAIN >= GEN_8 && TRY_GET_ABILITY_INFLUENCED_WILD_MON_INDEX(wildMonInfo->wildPokemon, TYPE_WATER, ABILITY_STORM_DRAIN, &wildMonIndex, LAND_WILD_COUNT))
            break;

        wildMonIndex = ChooseWildMonIndex_Land();
        break;
    case WILD_AREA_WATER:
        if (TRY_GET_ABILITY_INFLUENCED_WILD_MON_INDEX(wildMonInfo->wildPokemon, TYPE_STEEL, ABILITY_MAGNET_PULL, &wildMonIndex, WATER_WILD_COUNT))
            break;
        if (TRY_GET_ABILITY_INFLUENCED_WILD_MON_INDEX(wildMonInfo->wildPokemon, TYPE_ELECTRIC, ABILITY_STATIC, &wildMonIndex, WATER_WILD_COUNT))
            break;
        if (OW_LIGHTNING_ROD >= GEN_8 && TRY_GET_ABILITY_INFLUENCED_WILD_MON_INDEX(wildMonInfo->wildPokemon, TYPE_ELECTRIC, ABILITY_LIGHTNING_ROD, &wildMonIndex, WATER_WILD_COUNT))
            break;
        if (OW_FLASH_FIRE >= GEN_8 && TRY_GET_ABILITY_INFLUENCED_WILD_MON_INDEX(wildMonInfo->wildPokemon, TYPE_FIRE, ABILITY_FLASH_FIRE, &wildMonIndex, WATER_WILD_COUNT))
            break;
        if (OW_HARVEST >= GEN_8 && TRY_GET_ABILITY_INFLUENCED_WILD_MON_INDEX(wildMonInfo->wildPokemon, TYPE_GRASS, ABILITY_HARVEST, &wildMonIndex, WATER_WILD_COUNT))
            break;
        if (OW_STORM_DRAIN >= GEN_8 && TRY_GET_ABILITY_INFLUENCED_WILD_MON_INDEX(wildMonInfo->wildPokemon, TYPE_WATER, ABILITY_STORM_DRAIN, &wildMonIndex, WATER_WILD_COUNT))
            break;

        wildMonIndex = ChooseWildMonIndex_Water();
        break;
    case WILD_AREA_ROCKS:
        wildMonIndex = ChooseWildMonIndex_Rocks();
        break;
    default:
    case WILD_AREA_FISHING:
    case WILD_AREA_HIDDEN:
        break;
    }

    level = ChooseWildMonLevel(wildMonInfo->wildPokemon, wildMonIndex, area);
    if (flags & WILD_CHECK_REPEL && !IsWildLevelAllowedByRepel(level))
        return FALSE;
    if (gMapHeader.mapLayoutId != LAYOUT_BATTLE_FRONTIER_BATTLE_PIKE_ROOM_WILD_MONS && flags & WILD_CHECK_KEEN_EYE && !IsAbilityAllowingEncounter(level))
        return FALSE;

    CreateWildMon(wildMonInfo->wildPokemon[wildMonIndex].species, level);
    return TRUE;
}

static u16 GenerateFishingWildMon(const struct WildPokemonInfo *wildMonInfo, u8 rod)
{
    u8 wildMonIndex = ChooseWildMonIndex_Fishing(rod);
    u16 wildMonSpecies = wildMonInfo->wildPokemon[wildMonIndex].species;
    u8 level = ChooseWildMonLevel(wildMonInfo->wildPokemon, wildMonIndex, WILD_AREA_FISHING);

    UpdateChainFishingStreak();
    CreateWildMon(wildMonSpecies, level);
    return wildMonSpecies;
}

static bool8 SetUpMassOutbreakEncounter(u8 flags)
{
    u16 i;

    if (flags & WILD_CHECK_REPEL && !IsWildLevelAllowedByRepel(gSaveBlock1Ptr->outbreakPokemonLevel))
        return FALSE;

    CreateWildMon(gSaveBlock1Ptr->outbreakPokemonSpecies, gSaveBlock1Ptr->outbreakPokemonLevel);
    for (i = 0; i < MAX_MON_MOVES; i++)
        SetMonMoveSlot(&gEnemyParty[0], gSaveBlock1Ptr->outbreakPokemonMoves[i], i);

    return TRUE;
}

static bool8 DoMassOutbreakEncounterTest(void)
{
    if (gSaveBlock1Ptr->outbreakPokemonSpecies != SPECIES_NONE
     && gSaveBlock1Ptr->location.mapNum == gSaveBlock1Ptr->outbreakLocationMapNum
     && gSaveBlock1Ptr->location.mapGroup == gSaveBlock1Ptr->outbreakLocationMapGroup)
    {
        if (Random() % 100 < gSaveBlock1Ptr->outbreakPokemonProbability)
            return TRUE;
    }
    return FALSE;
}

static bool8 EncounterOddsCheck(u16 encounterRate)
{
    if (Random() % MAX_ENCOUNTER_RATE < encounterRate)
        return TRUE;
    else
        return FALSE;
}

// Returns true if it will try to create a wild encounter.
static bool8 WildEncounterCheck(u32 encounterRate, bool8 ignoreAbility)
{
    encounterRate *= 16;
    if (TestPlayerAvatarFlags(PLAYER_AVATAR_FLAG_MACH_BIKE | PLAYER_AVATAR_FLAG_ACRO_BIKE))
        encounterRate = encounterRate * 80 / 100;
    ApplyFluteEncounterRateMod(&encounterRate);
    ApplyCleanseTagEncounterRateMod(&encounterRate);
    if (LURE_STEP_COUNT != 0)
        encounterRate *= 2;
    if (!ignoreAbility && !GetMonData(&gPlayerParty[0], MON_DATA_SANITY_IS_EGG))
    {
        u32 ability = GetMonAbility(&gPlayerParty[0]);

        if (ability == ABILITY_STENCH && gMapHeader.mapLayoutId == LAYOUT_BATTLE_FRONTIER_BATTLE_PYRAMID_FLOOR)
            encounterRate = encounterRate * 3 / 4;
        else if (ability == ABILITY_STENCH)
            encounterRate /= 2;
        else if (ability == ABILITY_ILLUMINATE)
            encounterRate *= 2;
        else if (ability == ABILITY_WHITE_SMOKE)
            encounterRate /= 2;
        else if (ability == ABILITY_ARENA_TRAP)
            encounterRate *= 2;
        else if (ability == ABILITY_SAND_VEIL && gSaveBlock1Ptr->weather == WEATHER_SANDSTORM)
            encounterRate /= 2;
        else if (ability == ABILITY_SNOW_CLOAK && gSaveBlock1Ptr->weather == WEATHER_SNOW)
            encounterRate /= 2;
        else if (ability == ABILITY_QUICK_FEET)
            encounterRate /= 2;
        else if (ability == ABILITY_INFILTRATOR && OW_INFILTRATOR >= GEN_8)
            encounterRate /= 2;
        else if (ability == ABILITY_NO_GUARD)
            encounterRate *= 2;
    }
    if (encounterRate > MAX_ENCOUNTER_RATE)
        encounterRate = MAX_ENCOUNTER_RATE;
    return EncounterOddsCheck(encounterRate);
}

// When you first step on a different type of metatile, there's a 40% chance it
// skips the wild encounter check entirely.
static bool8 AllowWildCheckOnNewMetatile(void)
{
    if (Random() % 100 >= 60)
        return FALSE;
    else
        return TRUE;
}

static bool8 AreLegendariesInSootopolisPreventingEncounters(void)
{
    if (gSaveBlock1Ptr->location.mapGroup != MAP_GROUP(MAP_SOOTOPOLIS_CITY)
     || gSaveBlock1Ptr->location.mapNum != MAP_NUM(MAP_SOOTOPOLIS_CITY))
    {
        return FALSE;
    }

    return FlagGet(FLAG_LEGENDARIES_IN_SOOTOPOLIS);
}

bool8 StandardWildEncounter(u16 curMetatileBehavior, u16 prevMetatileBehavior)
{
    u32 headerId;
    enum TimeOfDay timeOfDay;
    struct Roamer *roamer;
    const struct WildPokemonHeader *wildHeader;

    if (sWildEncountersDisabled == TRUE)
        return FALSE;

    headerId = GetCurrentMapWildMonHeaderId();
    if (headerId == HEADER_NONE)
    {
        if (gMapHeader.mapLayoutId == LAYOUT_BATTLE_FRONTIER_BATTLE_PIKE_ROOM_WILD_MONS)
        {
            if (prevMetatileBehavior != curMetatileBehavior && !AllowWildCheckOnNewMetatile())
                return FALSE;
            else if (!TryGenerateBattlePikeWildMon(TRUE))
                return FALSE;

            BattleSetup_StartBattlePikeWildBattle();
            return TRUE;
        }
        if (gMapHeader.mapLayoutId == LAYOUT_BATTLE_FRONTIER_BATTLE_PYRAMID_FLOOR)
        {
            if (prevMetatileBehavior != curMetatileBehavior && !AllowWildCheckOnNewMetatile())
                return FALSE;

            GenerateBattlePyramidWildMon();
            BattleSetup_StartWildBattle();
            return TRUE;
        }
    }
    else
    {
        // Cache the wild header pointer to avoid repeated lookups
        wildHeader = GetWildMonHeaderById(headerId);
        
        if (MetatileBehavior_IsLandWildEncounter(curMetatileBehavior) == TRUE)
        {
            timeOfDay = GetTimeOfDayForEncounters(headerId, WILD_AREA_LAND);
            const struct WildPokemonInfo *landMonsInfo = wildHeader->encounterTypes[timeOfDay].landMonsInfo;

            if (landMonsInfo == NULL)
                return FALSE;
            else if (prevMetatileBehavior != curMetatileBehavior && !AllowWildCheckOnNewMetatile())
                return FALSE;
            else if (WildEncounterCheck(landMonsInfo->encounterRate, FALSE) != TRUE)
                return FALSE;

            if (TryStartRoamerEncounter())
            {
                roamer = &gSaveBlock1Ptr->roamer[gEncounteredRoamerIndex];
                if (!IsWildLevelAllowedByRepel(roamer->level))
                    return FALSE;

                BattleSetup_StartRoamerBattle();
                return TRUE;
            }
            else
            {
                if (DoMassOutbreakEncounterTest() == TRUE && SetUpMassOutbreakEncounter(WILD_CHECK_REPEL | WILD_CHECK_KEEN_EYE) == TRUE)
                {
                    BattleSetup_StartWildBattle();
                    return TRUE;
                }

                // try a regular wild land encounter
                if (TryGenerateWildMon(landMonsInfo, WILD_AREA_LAND, WILD_CHECK_REPEL | WILD_CHECK_KEEN_EYE) == TRUE)
                {
                    if (TryDoDoubleWildBattle())
                    {
                        struct Pokemon mon1 = gEnemyParty[0];
                        TryGenerateWildMon(landMonsInfo, WILD_AREA_LAND, WILD_CHECK_KEEN_EYE);
                        gEnemyParty[1] = mon1;
                        BattleSetup_StartDoubleWildBattle();
                    }
                    else
                    {
                        BattleSetup_StartWildBattle();
                    }
                    return TRUE;
                }

                return FALSE;
            }
        }
        else if (MetatileBehavior_IsWaterWildEncounter(curMetatileBehavior) == TRUE
                 || (TestPlayerAvatarFlags(PLAYER_AVATAR_FLAG_SURFING) && MetatileBehavior_IsBridgeOverWater(curMetatileBehavior) == TRUE))
        {
            timeOfDay = GetTimeOfDayForEncounters(headerId, WILD_AREA_WATER);
            const struct WildPokemonInfo *waterMonsInfo = wildHeader->encounterTypes[timeOfDay].waterMonsInfo;

            if (AreLegendariesInSootopolisPreventingEncounters() == TRUE)
                return FALSE;
            else if (waterMonsInfo == NULL)
                return FALSE;
            else if (prevMetatileBehavior != curMetatileBehavior && !AllowWildCheckOnNewMetatile())
                return FALSE;
            else if (WildEncounterCheck(waterMonsInfo->encounterRate, FALSE) != TRUE)
                return FALSE;

            if (TryStartRoamerEncounter())
            {
                roamer = &gSaveBlock1Ptr->roamer[gEncounteredRoamerIndex];
                if (!IsWildLevelAllowedByRepel(roamer->level))
                    return FALSE;

                BattleSetup_StartRoamerBattle();
                return TRUE;
            }
            else // try a regular surfing encounter
            {
                if (TryGenerateWildMon(waterMonsInfo, WILD_AREA_WATER, WILD_CHECK_REPEL | WILD_CHECK_KEEN_EYE) == TRUE)
                {
                    gIsSurfingEncounter = TRUE;
                    if (TryDoDoubleWildBattle())
                    {
                        struct Pokemon mon1 = gEnemyParty[0];
                        TryGenerateWildMon(waterMonsInfo, WILD_AREA_WATER, WILD_CHECK_KEEN_EYE);
                        gEnemyParty[1] = mon1;
                        BattleSetup_StartDoubleWildBattle();
                    }
                    else
                    {
                        BattleSetup_StartWildBattle();
                    }
                    return TRUE;
                }

                return FALSE;
            }
        }
    }

    return FALSE;
}

void RockSmashWildEncounter(void)
{
    u32 headerId = GetCurrentMapWildMonHeaderId();
    enum TimeOfDay timeOfDay;

    if (headerId != HEADER_NONE)
    {
        timeOfDay = GetTimeOfDayForEncounters(headerId, WILD_AREA_ROCKS);

        const struct WildPokemonInfo *wildPokemonInfo = GetWildMonHeaderById(headerId)->encounterTypes[timeOfDay].rockSmashMonsInfo;

        if (wildPokemonInfo == NULL)
        {
            gSpecialVar_Result = FALSE;
        }
        else if (WildEncounterCheck(wildPokemonInfo->encounterRate, TRUE) == TRUE
         && TryGenerateWildMon(wildPokemonInfo, WILD_AREA_ROCKS, WILD_CHECK_REPEL | WILD_CHECK_KEEN_EYE) == TRUE)
        {
            if (TryDoDoubleWildBattle())
            {
                struct Pokemon mon1 = gEnemyParty[0];
                TryGenerateWildMon(wildPokemonInfo, WILD_AREA_ROCKS, WILD_CHECK_REPEL | WILD_CHECK_KEEN_EYE);
                gEnemyParty[1] = mon1;
                BattleSetup_StartDoubleWildBattle();
                gSpecialVar_Result = TRUE;
            }
            else {
                BattleSetup_StartWildBattle();
                gSpecialVar_Result = TRUE;
            }
        }
        else
        {
            gSpecialVar_Result = FALSE;
        }
    }
    else
    {
        gSpecialVar_Result = FALSE;
    }
}

bool8 SweetScentWildEncounter(void)
{
    s16 x, y;
    u32 headerId;
    enum TimeOfDay timeOfDay;

    PlayerGetDestCoords(&x, &y);
    headerId = GetCurrentMapWildMonHeaderId();
    if (headerId == HEADER_NONE)
    {
        if (gMapHeader.mapLayoutId == LAYOUT_BATTLE_FRONTIER_BATTLE_PIKE_ROOM_WILD_MONS)
        {
            TryGenerateBattlePikeWildMon(FALSE);
            BattleSetup_StartBattlePikeWildBattle();
            return TRUE;
        }
        if (gMapHeader.mapLayoutId == LAYOUT_BATTLE_FRONTIER_BATTLE_PYRAMID_FLOOR)
        {
            GenerateBattlePyramidWildMon();
            BattleSetup_StartWildBattle();
            return TRUE;
        }
    }
    else
    {
        if (MetatileBehavior_IsLandWildEncounter(MapGridGetMetatileBehaviorAt(x, y)) == TRUE)
        {
            timeOfDay = GetTimeOfDayForEncounters(headerId, WILD_AREA_LAND);

            if (GetWildMonHeaderById(headerId)->encounterTypes[timeOfDay].landMonsInfo == NULL)
                return FALSE;

            if (TryStartRoamerEncounter())
            {
                BattleSetup_StartRoamerBattle();
                return TRUE;
            }

            if (DoMassOutbreakEncounterTest() == TRUE)
                SetUpMassOutbreakEncounter(0);
            else
                TryGenerateWildMon(GetWildMonHeaderById(headerId)->encounterTypes[timeOfDay].landMonsInfo, WILD_AREA_LAND, 0);

            BattleSetup_StartWildBattle();
            return TRUE;
        }
        else if (MetatileBehavior_IsWaterWildEncounter(MapGridGetMetatileBehaviorAt(x, y)) == TRUE)
        {
            timeOfDay = GetTimeOfDayForEncounters(headerId, WILD_AREA_WATER);

            if (AreLegendariesInSootopolisPreventingEncounters() == TRUE)
                return FALSE;
            if (GetWildMonHeaderById(headerId)->encounterTypes[timeOfDay].waterMonsInfo == NULL)
                return FALSE;

            if (TryStartRoamerEncounter())
            {
                BattleSetup_StartRoamerBattle();
                return TRUE;
            }

            TryGenerateWildMon(GetWildMonHeaderById(headerId)->encounterTypes[timeOfDay].waterMonsInfo, WILD_AREA_WATER, 0);
            BattleSetup_StartWildBattle();
            return TRUE;
        }
    }

    return FALSE;
}

bool8 DoesCurrentMapHaveFishingMons(void)
{
    u32 headerId = GetCurrentMapWildMonHeaderId();
    enum TimeOfDay timeOfDay = GetTimeOfDayForEncounters(headerId, WILD_AREA_FISHING);

    if (headerId != HEADER_NONE && GetWildMonHeaderById(headerId)->encounterTypes[timeOfDay].fishingMonsInfo != NULL)
        return TRUE;
    else
        return FALSE;
}

u32 CalculateChainFishingShinyRolls(void)
{
    return (2 * min(gChainFishingDexNavStreak, FISHING_CHAIN_SHINY_STREAK_MAX));
}

static void UpdateChainFishingStreak()
{
    if (!I_FISHING_CHAIN)
        return;

    if (gChainFishingDexNavStreak >= FISHING_CHAIN_LENGTH_MAX)
        return;

    gChainFishingDexNavStreak++;
}

void FishingWildEncounter(u8 rod)
{
    u16 species;
    u32 headerId;
    enum TimeOfDay timeOfDay;

    gIsFishingEncounter = TRUE;
    if (CheckFeebas() == TRUE)
    {
        u8 level = ChooseWildMonLevel(&sWildFeebas, 0, WILD_AREA_FISHING);

        species = sWildFeebas.species;
        CreateWildMon(species, level);
    }
    else
    {
        headerId = GetCurrentMapWildMonHeaderId();
        timeOfDay = GetTimeOfDayForEncounters(headerId, WILD_AREA_FISHING);
        species = GenerateFishingWildMon(GetWildMonHeaderById(headerId)->encounterTypes[timeOfDay].fishingMonsInfo, rod);
    }

    IncrementGameStat(GAME_STAT_FISHING_ENCOUNTERS);
    SetPokemonAnglerSpecies(species);
    BattleSetup_StartWildBattle();
}

u16 GetLocalWildMon(bool8 *isWaterMon)
{
    u32 headerId;
    enum TimeOfDay timeOfDay;
    const struct WildPokemonInfo *landMonsInfo;
    const struct WildPokemonInfo *waterMonsInfo;

    *isWaterMon = FALSE;
    headerId = GetCurrentMapWildMonHeaderId();
    if (headerId == HEADER_NONE)
        return SPECIES_NONE;
    
    timeOfDay = GetTimeOfDayForEncounters(headerId, WILD_AREA_LAND);
    landMonsInfo = GetWildMonHeaderById(headerId)->encounterTypes[timeOfDay].landMonsInfo;

    timeOfDay = GetTimeOfDayForEncounters(headerId, WILD_AREA_WATER);
    waterMonsInfo = GetWildMonHeaderById(headerId)->encounterTypes[timeOfDay].waterMonsInfo;

    // Neither
    if (landMonsInfo == NULL && waterMonsInfo == NULL)
        return SPECIES_NONE;
    // Land Pokémon
    else if (landMonsInfo != NULL && waterMonsInfo == NULL)
        return landMonsInfo->wildPokemon[ChooseWildMonIndex_Land()].species;
    // Water Pokémon
    else if (landMonsInfo == NULL && waterMonsInfo != NULL)
    {
        *isWaterMon = TRUE;
        return waterMonsInfo->wildPokemon[ChooseWildMonIndex_Water()].species;
    }
    // Either land or water Pokémon
    if ((Random() % 100) < 80)
    {
        return landMonsInfo->wildPokemon[ChooseWildMonIndex_Land()].species;
    }
    else
    {
        *isWaterMon = TRUE;
        return waterMonsInfo->wildPokemon[ChooseWildMonIndex_Water()].species;
    }
}

u16 GetLocalWaterMon(void)
{
    u32 headerId = GetCurrentMapWildMonHeaderId();
    enum TimeOfDay timeOfDay;

    if (headerId != HEADER_NONE)
    {
        timeOfDay = GetTimeOfDayForEncounters(headerId, WILD_AREA_WATER);

        const struct WildPokemonInfo *waterMonsInfo = GetWildMonHeaderById(headerId)->encounterTypes[timeOfDay].waterMonsInfo;

        if (waterMonsInfo)
            return waterMonsInfo->wildPokemon[ChooseWildMonIndex_Water()].species;
    }
    return SPECIES_NONE;
}

bool8 UpdateRepelCounter(void)
{
    u16 repelLureVar = VarGet(VAR_REPEL_STEP_COUNT);
    u16 steps = REPEL_LURE_STEPS(repelLureVar);
    bool32 isLure = IS_LAST_USED_LURE(repelLureVar);

    if (InBattlePike() || CurrentBattlePyramidLocation() != PYRAMID_LOCATION_NONE)
        return FALSE;
    if (InUnionRoom() == TRUE)
        return FALSE;

    if (steps != 0)
    {
        steps--;
        if (!isLure)
        {
            VarSet(VAR_REPEL_STEP_COUNT, steps);
            if (steps == 0)
            {
                ScriptContext_SetupScript(EventScript_SprayWoreOff);
                return TRUE;
            }
        }
        else
        {
            VarSet(VAR_REPEL_STEP_COUNT, steps | REPEL_LURE_MASK);
            if (steps == 0)
            {
                ScriptContext_SetupScript(EventScript_SprayWoreOff);
                return TRUE;
            }
        }

    }
    return FALSE;
}

static bool8 IsWildLevelAllowedByRepel(u8 wildLevel)
{
    u8 i;

    if (!REPEL_STEP_COUNT)
        return TRUE;

    for (i = 0; i < PARTY_SIZE; i++)
    {
        if (I_REPEL_INCLUDE_FAINTED == GEN_1 || I_REPEL_INCLUDE_FAINTED >= GEN_6 || GetMonData(&gPlayerParty[i], MON_DATA_HP))
        {
            if (!GetMonData(&gPlayerParty[i], MON_DATA_IS_EGG))
                return wildLevel >= GetMonData(&gPlayerParty[i], MON_DATA_LEVEL);
        }
    }

    return FALSE;
}

static bool8 IsAbilityAllowingEncounter(u8 level)
{
    u16 ability;

    if (GetMonData(&gPlayerParty[0], MON_DATA_SANITY_IS_EGG))
        return TRUE;

    ability = GetMonAbility(&gPlayerParty[0]);
    if (ability == ABILITY_KEEN_EYE || ability == ABILITY_INTIMIDATE)
    {
        u8 playerMonLevel = GetMonData(&gPlayerParty[0], MON_DATA_LEVEL);
        if (playerMonLevel > 5 && level <= playerMonLevel - 5 && !(Random() % 2))
            return FALSE;
    }

    return TRUE;
}

static bool8 TryGetRandomWildMonIndexByType(const struct WildPokemon *wildMon, u8 type, u8 numMon, u8 *monIndex)
{
    u8 validIndexes[numMon]; // variable length array, an interesting feature
    u8 i, validMonCount;

    for (i = 0; i < numMon; i++)
        validIndexes[i] = 0;

    for (validMonCount = 0, i = 0; i < numMon; i++)
    {
        if (GetSpeciesType(wildMon[i].species, 0) == type || GetSpeciesType(wildMon[i].species, 1) == type)
            validIndexes[validMonCount++] = i;
    }

    if (validMonCount == 0 || validMonCount == numMon)
        return FALSE;

    *monIndex = validIndexes[Random() % validMonCount];
    return TRUE;
}

#include "data.h"

#ifdef BUGFIX
static bool8 TryGetAbilityInfluencedWildMonIndex(const struct WildPokemon *wildMon, u8 type, u16 ability, u8 *monIndex, u32 size)
#else
static bool8 TryGetAbilityInfluencedWildMonIndex(const struct WildPokemon *wildMon, u8 type, u16 ability, u8 *monIndex)
#endif
{
    if (GetMonData(&gPlayerParty[0], MON_DATA_SANITY_IS_EGG))
        return FALSE;
    else if (GetMonAbility(&gPlayerParty[0]) != ability)
        return FALSE;
    else if (Random() % 2 != 0)
        return FALSE;

#ifdef BUGFIX
    return TryGetRandomWildMonIndexByType(wildMon, type, size, monIndex);
#else
    return TryGetRandomWildMonIndexByType(wildMon, type, LAND_WILD_COUNT, monIndex);
#endif
}

static void ApplyFluteEncounterRateMod(u32 *encRate)
{
    if (FlagGet(FLAG_SYS_ENC_UP_ITEM) == TRUE)
        *encRate += *encRate / 2;
    else if (FlagGet(FLAG_SYS_ENC_DOWN_ITEM) == TRUE)
        *encRate = *encRate / 2;
}

static void ApplyCleanseTagEncounterRateMod(u32 *encRate)
{
    if (GetMonData(&gPlayerParty[0], MON_DATA_HELD_ITEM) == ITEM_CLEANSE_TAG)
        *encRate = *encRate * 2 / 3;
}

bool8 TryDoDoubleWildBattle(void)
{
    // Prevent double battles on first encounters in Nuzlocke mode
    if (IsNuzlockeActive())
    {
        u16 mapGroup = gSaveBlock1Ptr->location.mapGroup;
        u16 mapNum = gSaveBlock1Ptr->location.mapNum;
        if (IsFirstEncounterInArea(mapGroup, mapNum))
            return FALSE;
    }

    if (GetSafariZoneFlag()
      || (B_DOUBLE_WILD_REQUIRE_2_MONS == TRUE && GetMonsStateToDoubles() != PLAYER_HAS_TWO_USABLE_MONS))
        return FALSE;
    if (FollowerNPCIsBattlePartner() && FNPC_FLAG_PARTNER_WILD_BATTLES != 0
     && (FNPC_FLAG_PARTNER_WILD_BATTLES == FNPC_ALWAYS || FlagGet(FNPC_FLAG_PARTNER_WILD_BATTLES)) && FNPC_NPC_FOLLOWER_WILD_BATTLE_VS_2 == TRUE)
        return TRUE;
    else if (B_FLAG_FORCE_DOUBLE_WILD != 0 && FlagGet(B_FLAG_FORCE_DOUBLE_WILD))
        return TRUE;
    else if (B_DOUBLE_WILD_CHANCE != 0 && ((Random() % 100) + 1 <= B_DOUBLE_WILD_CHANCE))
        return TRUE;
    return FALSE;
}

bool8 StandardWildEncounter_Debug(void)
{
    u32 headerId = GetCurrentMapWildMonHeaderId();
    enum TimeOfDay timeOfDay = GetTimeOfDayForEncounters(headerId, WILD_AREA_LAND);

    if (TryGenerateWildMon(GetWildMonHeaderById(headerId)->encounterTypes[timeOfDay].landMonsInfo, WILD_AREA_LAND, 0) != TRUE)
        return FALSE;

    DoStandardWildBattle_Debug();
    return TRUE;
}

u32 ChooseHiddenMonIndex(void)
{
    #ifdef ENCOUNTER_CHANCE_HIDDEN_MONS_TOTAL
        u8 rand = Random() % ENCOUNTER_CHANCE_HIDDEN_MONS_TOTAL;

        if (rand < ENCOUNTER_CHANCE_HIDDEN_MONS_SLOT_0)
            return 0;
        else if (rand >= ENCOUNTER_CHANCE_HIDDEN_MONS_SLOT_0 && rand < ENCOUNTER_CHANCE_HIDDEN_MONS_SLOT_1)
            return 1;
        else
            return 2;
    #else
        return 0xFF;
    #endif
}

bool32 MapHasNoEncounterData(void)
{
    return (GetCurrentMapWildMonHeaderId() == HEADER_NONE);
}

// Returns TRUE if the species is banned from wild evolution (see WILD_MON_EVO_BANS).
static bool8 IsSpeciesBannedFromWildEvo(u16 species)
{
    static const u16 bans[] = WILD_MON_EVO_BANS;
    int i;
    for (i = 0; bans[i] != SPECIES_NONE; i++)
    {
        if (species == bans[i])
            return TRUE;
    }
    return FALSE;
}

// Returns TRUE if the wild mon meets the requirements for this evolution method.
static bool8 CanWildMonEvolveByMethod(const struct Evolution *evo, u8 level, u8 gender, enum TimeOfDay timeOfDay)
{
    switch (evo->method)
    {
    case EVO_LEVEL:
        return level >= evo->param;
    case EVO_LEVEL_DAY:
        #if WILD_MON_EVO_TIME_OF_DAY_REQUIRED
        return level >= evo->param && timeOfDay == TIME_OF_DAY_DAY;
        #else
        return level >= evo->param;
        #endif
    case EVO_LEVEL_NIGHT:
        #if WILD_MON_EVO_TIME_OF_DAY_REQUIRED
        return level >= evo->param && timeOfDay == TIME_OF_DAY_NIGHT;
        #else
        return level >= evo->param;
        #endif
    case EVO_LEVEL_MALE:
        return level >= evo->param && gender == MON_MALE;
    case EVO_LEVEL_FEMALE:
        return level >= evo->param && gender == MON_FEMALE;
    // Add more cases as needed for your project (e.g. item, trade, etc.)
    default:
        return FALSE;
    }
}

// Returns the final evolved species for a wild mon, or the original if no evolution occurs.
// Applies chance per evolution step, checks bans, and supports time/gender-based evolutions.
// Only allows evolution if the player's party is at a high enough level for that evolution.
static u16 GetWildEvolvedSpecies(u16 species, u8 level, u8 gender, enum TimeOfDay timeOfDay)
{
    const struct Evolution *evolutions;
    u16 evolvedSpecies = species;
    bool8 evolved = FALSE;
    int i;
    int maxEvolutions = 3; // Safety limit to prevent infinite loops
    u8 highestPartyLevel = GetHighestPartyLevel();

    // Check for per-species bans
    if (IsSpeciesBannedFromWildEvo(species))
        return species;

    // Loop: try to evolve as far as possible, but apply chance at each step
    while (maxEvolutions-- > 0)
    {
        evolutions = GetSpeciesEvolutions(evolvedSpecies);
        bool8 found = FALSE;

        // Early exit if no evolutions exist
        if (evolutions[0].method == EVOLUTIONS_END)
            break;

        for (i = 0; evolutions[i].method != EVOLUTIONS_END; i++)
        {
            // Check if this evolution method is satisfied
            if (CanWildMonEvolveByMethod(&evolutions[i], level, gender, timeOfDay))
            {
                // Only allow evolution if player's highest party level is high enough
                // This ensures wild encounters scale with player progression
                u8 requiredLevel = evolutions[i].param;
                if (highestPartyLevel < requiredLevel)
                {
                    // Player hasn't reached this evolution level yet - stop evolving
                    return evolvedSpecies;
                }
                
                // Apply random chance (e.g. 75%)
                if ((Random() & 0xFF) < WILD_MON_EVO_CHANCE)
                {
                    evolvedSpecies = evolutions[i].targetSpecies;
                    evolved = TRUE;
                    found = TRUE;
                    break; // Only evolve one step per loop
                }
            }
        }
        if (!found)
            break; // No further evolution possible
    }

    return evolved ? evolvedSpecies : species;
}
