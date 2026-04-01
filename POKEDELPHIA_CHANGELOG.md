# Pokedelphia Changelog

---

## Session — Upstream Sync & Merge into Development
**Date:** 2026-04-01
**Upstream versions integrated:** expansion 1.14.0 → 1.15.1
**Pre-merge snapshot:** `Pokedelphia-v0.1` (branch, commit `5abb4d1e69`)

---

### What Was Done

1. **Fetched and merged upstream into `master`** — fast-forward from expansion 1.13.x to 1.15.1 (7 new version tags: 1.14.0 through 1.15.1).
2. **Created `Pokedelphia-v0.1` branch** from the tip of `development` before merging, as a pre-merge snapshot.
3. **Merged `master` into `development`** — resolved 27 conflicts, clean build confirmed.

---

### New Features Integrated from Upstream

#### FRLG Content
- ~55 FireRed/LeafGreen map layouts added to `data/layouts/layouts.json`.
- 40+ FRLG heal locations added to `src/data/heal_locations.json`.
- `IS_FRLG` conditional block in `include/constants/flags.h` — includes `constants/flags_frlg.h` for FRLG builds.
- FRLG placeholder and badge name strings added to `src/strings.c`.
- `gText_ExpandedPlaceholder_Red/Green` added for FRLG-side dialogue.

#### Starting Statuses System
- New mechanic: Pokémon can enter battle with a pre-applied status condition.
- Script command `setstartingstatus` added (opcode `0xE9` in Pokedelphia — follows quest commands at `0xE5–0xE8`).
- `SetStartingStatus()` / `ResetStartingStatuses()` implementations in `src/battle_util.c`.

#### Ghost Battle Scope Check
- Battle UI now hides the caught-ball indicator during ghost battles (when player lacks the Silph Scope) before showing it for other checks.

#### Berry Colors
- `OW_BERRY_COLORS = GEN_6_ORAS` added to `include/config/overworld.h`.

#### AI Switching Improvements
- `AI_FLAG_RANDOMIZE_SWITCHIN` added to `include/constants/battle_ai.h`.
- Six new AI config options in `include/config/ai.h`:
  - `ALL_MOVES_BAD_NEEDS_GOOD_SWITCHIN`
  - `ALL_SCORES_BAD_NEEDS_GOOD_SWITCHIN`
  - `AI_DEFENSIVE_KO_THRESHOLD = 3`
  - `AI_TYPE_MATCHUP_THRESHOLD`
  - `AI_WISH_HEAL_THRESHOLD = 4`
  - `AI_SWITCHIN_DAMAGE_THRESHOLD = 0`

#### New Script Commands
- `textcolor` — change text color mid-script.
- `setworldmapflag` — set world map region flags.
- `getbraillestringwidth` — braille text width utility.
- `EARLY_RIVAL` battle type (`14`) added to `include/constants/battle_setup.h`.

#### Misc Upstream Additions
- `I_SHOW_NO_ID_TRAINER = DISABLED_ON_RELEASE` added to `include/config/item.h`.
- `LAYOUT_ROUTE104_PROTOTYPE` layout added.
- Partner difficulty tests added to `test/battle/trainer_control.c`.

---

### API Changes Applied (Upstream Breaking Changes)

| Old | New | Files Updated |
|---|---|---|
| `CreateMon(&mon, species, lvl, ivs, fixedIV, personality, otIdType, fixedOtId)` | `CreateMon(&mon, species, lvl, personality, otId)` | `src/battle_main.c`, `src/battle_controllers.c` |
| `CreateMonWithGenderNatureLetter(...)` / `CreateMonWithNature(...)` | `GetMonPersonality(...) + CreateMonWithIVs(...)` | `src/wild_encounter.c` |
| `PickWildMonNature(void)` | `PickWildMonNature(u32 species)` | `src/wild_encounter.c` |
| `IsTextPrinterActive(windowId)` | `IsTextPrinterActiveOnWindow(windowId)` | `src/main_menu.c` |
| `FunctionCallOption` enum | `ResultOption` enum | `src/battle_util.c` |
| `u32 battlerId` params | `enum BattlerId battlerId` params | `src/battle_util.c` |

---

### Conflict Resolutions

All Pokedelphia custom features were preserved. Key decisions per file:

| File | Decision |
|---|---|
| `include/config/ai.h` | Kept dev thresholds (80/110); added 6 upstream AI config options |
| `include/config/item.h` | Kept `FLAG_VS_SEEKER_ENABLE` reference; added `I_SHOW_NO_ID_TRAINER` |
| `include/config/overworld.h` | Kept `OW_BERRY_IMMORTAL TRUE`; added `OW_BERRY_COLORS` |
| `include/constants/battle_ai.h` | Added `AI_FLAG_RANDOMIZE_SWITCHIN`; kept `AI_FLAG_EXPERT_TRAINER` |
| `include/constants/battle_setup.h` | Renumbered — `EARLY_RIVAL=14`, dev's `NO_WHITEOUT=15`, `SINGLE_NO_INTRO_NO_WHITEOUT=16` |
| `include/constants/battle_string_ids.h` | Kept dev Nuzlocke strings + upstream new strings |
| `include/constants/field_effects.h` | `FLDEFF_QUEST_ICON=75` preserved; upstream additions shifted to `79/80/81` |
| `include/constants/flags.h` | Kept `FLAG_NUZLOCKE=0x20`, `FLAG_VS_SEEKER_ENABLE=0x21`; added FRLG conditional |
| `include/strings.h` | Kept both dev + upstream declarations |
| `include/wild_encounter.h` | Kept `InvalidateWildHeaderCache`; removed `PickWildMonNature` (now file-static) |
| `data/layouts/layouts.json` | Kept dev custom layouts + `LAYOUT_ROUTE104BEACH`, `LAYOUT_PETALBURG_WOODS_SHORTCUT`; added FRLG block |
| `data/maps/.../BrendansHouse_2F/scripts.inc` | Kept dev's custom "weird stain on Trashburg" text |
| `data/script_cmd_table.inc` | Dev opcodes `0xE5–0xE8` kept; upstream `getbraillestringwidth` added at `0xE9` |
| `data/scripts/movement.inc` | Kept `Common_Movement_SelfText` |
| `src/data/heal_locations.json` | Kept `HEAL_LOCATION_PETALBURG_WOODS`; added 40+ FRLG locations |
| `src/battle_controllers.c` | Kept Rattata first-battle logic; updated `CreateMon` to new API |
| `src/battle_interface.c` | Ghost scope check (upstream) runs before Nuzlocke caught-indicator (dev) |
| `src/battle_main.c` | Kept level scaling block; updated `CreateMon` to new API |
| `src/battle_script_commands.c` | Nuzlocke tracking moved into `FinalizeCapture()` for both capture paths |
| `src/battle_setup.c` | Kept forfeit handler (`DidPlayerForfeitNormalTrainerBattle` → `CB2_WhiteOut`) |
| `src/battle_util.c` | Kept `caps.c` prototypes; added `SetStartingStatus`/`ResetStartingStatuses` |
| `src/main_menu.c` | Kept name-confirm skip; fixed all 4 `IsTextPrinterActiveOnWindow` calls |
| `src/pokedex_area_screen.c` | Kept async `FindMapsWithMonAsync`; removed unused `currentRegionMapType` variable |
| `src/scrcmd.c` | Kept quest commands; added upstream commands; fixed missing closing brace |
| `src/starter_choose.c` | Kept Bagon / Dratini / Trapinch |
| `src/strings.c` | Kept Nuzlocke + quest strings; added FRLG strings |
| `src/wild_encounter.c` | Kept level scaling + Nuzlocke tracking; migrated to new Pokémon creation API |
| `test/battle/trainer_control.c` | Kept dev difficulty-system tests; added upstream partner difficulty tests |

---

### Build Result

- **Command:** `make -j$(nproc)`
- **Output:** `pokeemerald.gba`
- **ROM usage:** 78.24% (26,253,220 / 33,554,432 bytes)
- **Status:** ✅ Clean — zero errors or warnings
