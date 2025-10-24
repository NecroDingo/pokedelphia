#include "global.h"
#include "nuzlocke.h"
#include "event_data.h"
#include "pokemon.h"
#include "constants/flags.h"
#include "constants/vars.h"
#include "constants/region_map_sections.h"
#include "pokemon_storage_system.h"
#include "sprite.h"
#include "battle.h"
#include "battle_interface.h"
#include "overworld.h"
#include "config/battle.h"

// Check if Nuzlocke mode is active
bool8 IsNuzlockeActive(void)
{
    return FlagGet(FLAG_NUZLOCKE);
}

// Location conversion for Nuzlocke tracking - adapted for pokeemerald-expansion
static u8 GetNuzlockeLocationId(u8 currLocation)
{
    switch (currLocation)
    {
    // Cities and towns that have encounters are treated as separate areas
    case MAPSEC_TRASHBURG:
    case MAPSEC_OLD_SCUMPORT:
    case MAPSEC_DEWFORD_TOWN:
    case MAPSEC_LAVARIDGE_TOWN:
    case MAPSEC_FALLARBOR_TOWN:
    case MAPSEC_VERDANTURF_TOWN:
    case MAPSEC_PACIFIDLOG_TOWN:
    case MAPSEC_GIANTS_REACH:
    case MAPSEC_SLATEPORT_CITY:
    case MAPSEC_MAUVILLE_CITY:
    case MAPSEC_WAWA_PARK:
    case MAPSEC_FORTREE_CITY:
    case MAPSEC_LILYCOVE_CITY:
    case MAPSEC_MOSSDEEP_CITY:
    case MAPSEC_SOOTOPOLIS_CITY:
    case MAPSEC_EVER_GRANDE_CITY:
        return currLocation;
        
    // Routes are separate areas
    case MAPSEC_ROUTE_101:
    case MAPSEC_ROUTE_102:
    case MAPSEC_ROUTE_103:
    case MAPSEC_ROUTE_104:
    case MAPSEC_ROUTE_105:
    case MAPSEC_ROUTE_106:
    case MAPSEC_ROUTE_107:
    case MAPSEC_ROUTE_108:
    case MAPSEC_ROUTE_109:
    case MAPSEC_ROUTE_110:
    case MAPSEC_ROUTE_111:
    case MAPSEC_ROUTE_112:
    case MAPSEC_ROUTE_113:
    case MAPSEC_ROUTE_114:
    case MAPSEC_ROUTE_115:
    case MAPSEC_ROUTE_116:
    case MAPSEC_ROUTE_117:
    case MAPSEC_ROUTE_118:
    case MAPSEC_ROUTE_119:
    case MAPSEC_ROUTE_120:
    case MAPSEC_ROUTE_121:
    case MAPSEC_ROUTE_122:
    case MAPSEC_ROUTE_123:
    case MAPSEC_ROUTE_124:
    case MAPSEC_ROUTE_125:
    case MAPSEC_ROUTE_126:
    case MAPSEC_ROUTE_127:
    case MAPSEC_ROUTE_128:
    case MAPSEC_ROUTE_129:
    case MAPSEC_ROUTE_130:
    case MAPSEC_ROUTE_131:
    case MAPSEC_ROUTE_132:
    case MAPSEC_ROUTE_133:
    case MAPSEC_ROUTE_134:
        return currLocation;
        
    // Caves and special areas
    case MAPSEC_GRANITE_CAVE:
    case MAPSEC_MT_CHIMNEY:
    case MAPSEC_SAFARI_ZONE:
    case MAPSEC_BATTLE_FRONTIER:
    case MAPSEC_SCRAPPLE_HOLLOW:
    case MAPSEC_RUSTURF_TUNNEL:
    case MAPSEC_ABANDONED_SHIP:
    case MAPSEC_NEW_MAUVILLE:
    case MAPSEC_METEOR_FALLS:
    case MAPSEC_MT_PYRE:
    case MAPSEC_SHOAL_CAVE:
    case MAPSEC_SEAFLOOR_CAVERN:
    case MAPSEC_VICTORY_ROAD:
    case MAPSEC_MIRAGE_ISLAND:
    case MAPSEC_CAVE_OF_ORIGIN:
    case MAPSEC_FIERY_PATH:
    case MAPSEC_JAGGED_PASS:
    case MAPSEC_SEALED_CHAMBER:
    case MAPSEC_SCORCHED_SLAB:
        return currLocation;
        
    // Underwater areas consolidated with their surface counterparts
    case MAPSEC_UNDERWATER_124:
        return MAPSEC_ROUTE_124;
    case MAPSEC_UNDERWATER_126:
        return MAPSEC_ROUTE_126;
    case MAPSEC_UNDERWATER_127:
        return MAPSEC_ROUTE_127;
    case MAPSEC_UNDERWATER_128:
        return MAPSEC_ROUTE_128;
    case MAPSEC_UNDERWATER_SOOTOPOLIS:
        return MAPSEC_SOOTOPOLIS_CITY;
    case MAPSEC_UNDERWATER_SEAFLOOR_CAVERN:
        return MAPSEC_SEAFLOOR_CAVERN;
    case MAPSEC_UNDERWATER_SEALED_CHAMBER:
        return MAPSEC_SEALED_CHAMBER;
    
    // Multiple areas consolidated
    case MAPSEC_METEOR_FALLS2:
        return MAPSEC_METEOR_FALLS;
    case MAPSEC_FIERY_PATH2:
        return MAPSEC_FIERY_PATH;
    case MAPSEC_JAGGED_PASS2:
        return MAPSEC_JAGGED_PASS;
    
    // Beach areas - remap to low IDs to fit in tracking variables (max 64 locations)
    case MAPSEC_ROUTE_104_BEACH:
        return 60;  // Use unused ID 60 for Route 104 Beach tracking
        
    // Default to the location itself if not handled above
    default:
        return currLocation;
    }
}

// Official Nuzlocke location tracking functions - much more robust than our map-based approach
bool8 HasWildPokemonBeenSeenInLocation(u8 location, bool8 setEncounteredIfFirst)
{
    u8 varToCheck, bitToCheck;
    u16 varValue;
    const u16 pokemonSeenVars[] = {
        VAR_NUZLOCKE_ENCOUNTERS_1,
        VAR_NUZLOCKE_ENCOUNTERS_2,
        VAR_NUZLOCKE_ENCOUNTERS_3,
        VAR_NUZLOCKE_ENCOUNTERS_4,
    };
    
    location = GetNuzlockeLocationId(location);
    
    if (!FlagGet(FLAG_NUZLOCKE) || !FlagGet(FLAG_SYS_POKEDEX_GET))
    {
        // Clear all encounter tracking if Nuzlocke not active
        VarSet(VAR_NUZLOCKE_ENCOUNTERS_1, 0);
        VarSet(VAR_NUZLOCKE_ENCOUNTERS_2, 0);
        VarSet(VAR_NUZLOCKE_ENCOUNTERS_3, 0);
        VarSet(VAR_NUZLOCKE_ENCOUNTERS_4, 0);
        VarSet(VAR_NUZLOCKE_CATCHES_1, 0);
        VarSet(VAR_NUZLOCKE_CATCHES_2, 0);
        VarSet(VAR_NUZLOCKE_CATCHES_3, 0);
        VarSet(VAR_NUZLOCKE_CATCHES_4, 0);
        return 0;
    }
    
    // Map location to variable index and bit position
    varToCheck = location / 16;  // Each variable stores 16 locations (16 bits)
    bitToCheck = location % 16;
    
    if (varToCheck >= 4)  // Safety check - we only have 4 variables
        return 0;
    
    varValue = VarGet(pokemonSeenVars[varToCheck]);
    
    if ((varValue & (1 << bitToCheck)) != 0)
    {
        // Already encountered in this location
        return 1;
    }
    else if (setEncounteredIfFirst)
    {
        // First encounter - mark it
        VarSet(pokemonSeenVars[varToCheck], varValue | (1 << bitToCheck));
    }
    
    return 0;
}

bool8 HasWildPokemonBeenCaughtInLocation(u8 location, bool8 setCaughtIfCaught)
{
    u8 varToCheck, bitToCheck;
    u16 varValue;
    const u16 pokemonCaughtVars[] = {
        VAR_NUZLOCKE_CATCHES_1,
        VAR_NUZLOCKE_CATCHES_2,
        VAR_NUZLOCKE_CATCHES_3,
        VAR_NUZLOCKE_CATCHES_4,
    };
    
    location = GetNuzlockeLocationId(location);
    
    if (!FlagGet(FLAG_NUZLOCKE) || !FlagGet(FLAG_SYS_POKEDEX_GET))
        return 0;
    
    // Map location to variable index and bit position
    varToCheck = location / 16;  // Each variable stores 16 locations (16 bits)
    bitToCheck = location % 16;
    
    if (varToCheck >= 4)  // Safety check - we only have 4 variables
        return 0;
    
    varValue = VarGet(pokemonCaughtVars[varToCheck]);
    
    if ((varValue & (1 << bitToCheck)) != 0)
    {
        // Already caught in this location
        return 1;
    }
    else if (setCaughtIfCaught)
    {
        // Mark as caught
        VarSet(pokemonCaughtVars[varToCheck], varValue | (1 << bitToCheck));
    }
    
    return 0;
}

// Legacy compatibility functions that redirect to the new location-based system
bool8 HasEncounteredInArea(u16 mapGroup, u16 mapNum)
{
    // For legacy compatibility, use current location
    if (!IsNuzlockeActive())
        return FALSE;
    
    u8 currentLocation = GetCurrentRegionMapSectionId();
    return HasWildPokemonBeenSeenInLocation(currentLocation, FALSE);
}

void SetEncounteredInArea(u16 mapGroup, u16 mapNum)
{
    // For legacy compatibility, use current location
    if (!IsNuzlockeActive())
        return;
    
    u8 currentLocation = GetCurrentRegionMapSectionId();
    HasWildPokemonBeenSeenInLocation(currentLocation, TRUE);
}

bool8 IsFirstEncounterInArea(u16 mapGroup, u16 mapNum)
{
    return IsNuzlockeActive() && !HasEncounteredInArea(mapGroup, mapNum);
}

bool8 HasCaughtInArea(u16 mapGroup, u16 mapNum)
{
    // For legacy compatibility, use current location
    if (!IsNuzlockeActive())
        return FALSE;
    
    u8 currentLocation = GetCurrentRegionMapSectionId();
    return HasWildPokemonBeenCaughtInLocation(currentLocation, FALSE);
}

void SetCaughtInArea(u16 mapGroup, u16 mapNum)
{
    // For legacy compatibility, use current location
    if (!IsNuzlockeActive())
        return;
    
    u8 currentLocation = GetCurrentRegionMapSectionId();
    HasWildPokemonBeenCaughtInLocation(currentLocation, TRUE);
}

// Dead Pokemon functions
bool8 IsMonDead(struct Pokemon *mon)
{
    if (!IsNuzlockeActive())
        return FALSE;
    
    return GetMonData(mon, MON_DATA_IS_DEAD);
}

bool8 IsBoxMonDead(struct BoxPokemon *boxMon)
{
    if (!IsNuzlockeActive())
        return FALSE;
    
    return GetBoxMonData(boxMon, MON_DATA_IS_DEAD);
}

void SetMonDead(struct Pokemon *mon, bool8 isDead)
{
    if (!IsNuzlockeActive())
        return;
    
    u32 deadFlag = isDead ? 1 : 0;
    SetMonData(mon, MON_DATA_IS_DEAD, &deadFlag);
}

void SetBoxMonDead(struct BoxPokemon *boxMon, bool8 isDead)
{
    if (!IsNuzlockeActive())
        return;
    
    u32 deadFlag = isDead ? 1 : 0;
    SetBoxMonData(boxMon, MON_DATA_IS_DEAD, &deadFlag);
}

// Species checking for duplicate clause
bool8 PlayerOwnsSpecies(u16 species)
{
    int i, j;
    
    if (!IsNuzlockeActive())
        return FALSE;
    
    // Check party
    for (i = 0; i < PARTY_SIZE; i++)
    {
        u16 partySpecies = GetMonData(&gPlayerParty[i], MON_DATA_SPECIES);
        if (partySpecies != SPECIES_NONE && partySpecies == species)
            return TRUE;
    }
    
    // Check PC boxes
    for (i = 0; i < TOTAL_BOXES_COUNT; i++)
    {
        for (j = 0; j < IN_BOX_COUNT; j++)
        {
            struct BoxPokemon *boxMon = GetBoxedMonPtr(i, j);
            u16 boxSpecies = GetBoxMonData(boxMon, MON_DATA_SPECIES);
            
            // Early exit if empty slot
            if (boxSpecies == SPECIES_NONE)
                continue;
            
            if (boxSpecies == species)
                return TRUE;
        }
    }
    
    return FALSE;
}

bool8 DoesPlayerOwnSpeciesInEvolutionLine(u16 species)
{
    if (!IsNuzlockeActive())
        return FALSE;
    
    // Simple check - just check the exact species for now
    // TODO: Could be extended to check full evolution lines
    return PlayerOwnsSpecies(species);
}

// Healing functions (modified for Nuzlocke)
void NuzlockeHealPokemon(struct Pokemon *mon)
{
    if (!IsNuzlockeActive() || !IsMonDead(mon))
    {
        // Normal healing if not Nuzlocke or Pokemon not dead
        u32 data = GetMonData(mon, MON_DATA_MAX_HP);
        SetMonData(mon, MON_DATA_HP, &data);
        
        data = STATUS1_NONE;
        SetMonData(mon, MON_DATA_STATUS, &data);
        
        MonRestorePP(mon);
    }
    // If Nuzlocke and Pokemon is dead, do nothing (no healing)
}

void NuzlockeHealBoxPokemon(struct BoxPokemon *boxMon)
{
    if (!IsNuzlockeActive() || !IsBoxMonDead(boxMon))
    {
        // Normal healing if not Nuzlocke or Pokemon not dead
        u32 data = 0;
        SetBoxMonData(boxMon, MON_DATA_HP_LOST, &data);
        
        data = STATUS1_NONE;
        SetBoxMonData(boxMon, MON_DATA_STATUS, &data);
        
        BoxMonRestorePP(boxMon);
    }
    // If Nuzlocke and Pokemon is dead, do nothing (no healing)
}

// Handle Pokemon fainting (mark as dead in Nuzlocke mode)
void NuzlockeHandleFaint(struct Pokemon *mon)
{
    if (!IsNuzlockeActive())
        return;
    
    // Don't mark as dead if no-whiteout flag is set (e.g., tutorial battles)
    if (FlagGet(B_FLAG_NO_WHITEOUT))
        return;
    
    // Check if the Pokemon's HP is 0 (just fainted)
    if (GetMonData(mon, MON_DATA_HP) == 0)
    {
        SetMonDead(mon, TRUE);
    }
}

void NuzlockeHandleBoxFaint(struct BoxPokemon *boxMon)
{
    if (!IsNuzlockeActive())
        return;
    
    // Check if the Pokemon's HP is 0 (just fainted)
    u32 hpLost = GetBoxMonData(boxMon, MON_DATA_HP_LOST);
    u32 maxHP = GetBoxMonData(boxMon, MON_DATA_MAX_HP);
    
    if (hpLost >= maxHP)
    {
        SetBoxMonDead(boxMon, TRUE);
    }
}

void NuzlockeHandleWhiteout(void)
{
    if (!IsNuzlockeActive())
        return;
    
    int i;
    
    // Mark all party Pokemon as dead
    for (i = 0; i < PARTY_SIZE; i++)
    {
        struct Pokemon *mon = &gPlayerParty[i];
        if (GetMonData(mon, MON_DATA_SPECIES) != SPECIES_NONE && 
            !GetMonData(mon, MON_DATA_SANITY_IS_EGG))
        {
            SetMonDead(mon, TRUE);
        }
    }
}

bool8 NuzlockeCanCatchPokemon(u16 species, u32 personality, u32 otId)
{
    u8 currentLocation;
    
    if (!IsNuzlockeActive())
    {
        return TRUE; // Not in Nuzlocke mode - always allow catching
    }
    
    currentLocation = GetCurrentRegionMapSectionId();
    
    // Shiny clause: always allow shiny Pokemon regardless of other rules
    u32 shinyValue = ((personality >> 16) ^ (personality & 0xFFFF)) ^ ((otId >> 16) ^ (otId & 0xFFFF));
    bool8 isShiny = (shinyValue < 8); // Shiny threshold
    
    if (isShiny)
    {
        return TRUE;
    }
    
    // Check if we've already had our "real" first encounter in this location
    // (an encounter of a species we don't own, which counts as the area's encounter)
    if (HasWildPokemonBeenSeenInLocation(currentLocation, FALSE))
    {
        return FALSE;
    }
    
    // This is a potential first encounter - check duplicate clause
    if (PlayerOwnsSpecies(species))
    {
        return FALSE; // Don't catch, but this encounter doesn't count - keep hunting
    }
    
    // We don't own this species - this is our "real" first encounter for this area
    return TRUE;
}

void NuzlockeOnBattleEnd(void)
{
    // Mark the current location as encountered when certain wild battles end
    if (IsNuzlockeActive() && !(gBattleTypeFlags & BATTLE_TYPE_TRAINER))
    {
        u8 currentLocation = GetCurrentRegionMapSectionId();
        
        // Check if this area has already been marked as encountered
        bool8 alreadyEncountered = HasWildPokemonBeenSeenInLocation(currentLocation, FALSE);
        
        if (!alreadyEncountered)
        {
            // This area hasn't been marked yet
            // We need to check if this was a "real" encounter (species we don't own)
            u16 wildSpecies = GetMonData(&gEnemyParty[0], MON_DATA_SPECIES);
            
            if (!PlayerOwnsSpecies(wildSpecies))
            {
                // This was a "real" first encounter (species we don't own)
                // Mark the area as encountered regardless of battle outcome
                HasWildPokemonBeenSeenInLocation(currentLocation, TRUE);
            }
            else
            {
                // This was a duplicate species - don't mark area as encountered
            }
        }
        else
        {
            // Already encountered this location
        }
    }
}
