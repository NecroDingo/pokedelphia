WawaPark_PokemonCenter_1F_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, WawaPark_PokemonCenter_1F_OnTransition
	map_script MAP_SCRIPT_ON_RESUME, CableClub_OnResume
	.byte 0

WawaPark_PokemonCenter_1F_OnTransition:
	setrespawn HEAL_LOCATION_WAWA_PARK
	call Common_EventScript_UpdateBrineyLocation
	end

WawaPark_PokemonCenter_1F_EventScript_Nurse::
	setvar VAR_0x800B, LOCALID_WAWA_PARK_NURSE
	call Common_EventScript_PkmnCenterNurse
	waitmessage
	waitbuttonpress
	release
	end

WawaPark_PokemonCenter_1F_EventScript_Man::
	msgbox WawaPark_PokemonCenter_1F_Text_PokemonHavePersonalities, MSGBOX_NPC
	end

WawaPark_PokemonCenter_1F_EventScript_Boy::
	msgbox WawaPark_PokemonCenter_1F_Text_MaleAndFemalePokemon, MSGBOX_NPC
	end

WawaPark_PokemonCenter_1F_EventScript_Girl::
	msgbox WawaPark_PokemonCenter_1F_Text_HMCutNextDoor, MSGBOX_NPC
	end

WawaPark_PokemonCenter_1F_Text_PokemonHavePersonalities:
	.string "My POKéMON has a NAIVE nature, and my\n"
	.string "friend's has a JOLLY nature.\p"
	.string "It's fascinating how POKéMON have\n"
	.string "personalities!$"

WawaPark_PokemonCenter_1F_Text_MaleAndFemalePokemon:
	.string "Just like people, there are male and\n"
	.string "female POKéMON.\p"
	.string "But no one seems to have any idea how\n"
	.string "they're different.$"

WawaPark_PokemonCenter_1F_Text_HMCutNextDoor:
	.string "The man next door gave me an HM!\p"
	.string "I used it to teach my POKéMON how to\n"
	.string "CUT down skinny trees.$"

