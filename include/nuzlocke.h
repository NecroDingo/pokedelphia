#ifndef GUARD_NUZLOCKE_H
#define GUARD_NUZLOCKE_H

#include "pokemon.h"

// Check if Nuzlocke mode is active
bool8 IsNuzlockeActive(void);

// Official location-based encounter tracking (from pokeemerald guide)
bool8 HasWildPokemonBeenSeenInLocation(u8 location, bool8 setEncounteredIfFirst);
bool8 HasWildPokemonBeenCaughtInLocation(u8 location, bool8 setCaughtIfCaught);

// Dead Pokemon functions
bool8 IsMonDead(struct Pokemon *mon);
bool8 IsBoxMonDead(struct BoxPokemon *boxMon);
void SetMonDead(struct Pokemon *mon, bool8 isDead);
void SetBoxMonDead(struct BoxPokemon *boxMon, bool8 isDead);

// Legacy encounter tracking functions (for compatibility)
bool8 HasEncounteredInArea(u16 mapGroup, u16 mapNum);
void SetEncounteredInArea(u16 mapGroup, u16 mapNum);
bool8 IsFirstEncounterInArea(u16 mapGroup, u16 mapNum);

// Legacy catch tracking functions (for compatibility)
bool8 HasCaughtInArea(u16 mapGroup, u16 mapNum);
void SetCaughtInArea(u16 mapGroup, u16 mapNum);

// Species checking for duplicate clause
bool8 PlayerOwnsSpecies(u16 species);

// Healing functions (modified for Nuzlocke)
void NuzlockeHealPokemon(struct Pokemon *mon);
void NuzlockeHealBoxPokemon(struct BoxPokemon *boxMon);

// Faint handling functions
void NuzlockeHandleFaint(struct Pokemon *mon);
void NuzlockeHandleBoxFaint(struct BoxPokemon *boxMon);

// Whiteout handling
void NuzlockeHandleWhiteout(void);

// Catching restrictions
bool8 NuzlockeCanCatchPokemon(u16 species, u32 personality, u32 otId);

// Battle end handling
void NuzlockeOnBattleEnd(void);

// Additional utility functions
void MarkAreaEncountered(u8 area);
bool8 DoesPlayerOwnSpeciesInEvolutionLine(u16 species);

#endif // GUARD_NUZLOCKE_H