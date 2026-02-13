OldaleTown_PokemonCenter_1F_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, OldaleTown_PokemonCenter_1F_OnTransition
	map_script MAP_SCRIPT_ON_RESUME, CableClub_OnResume
	.byte 0

OldaleTown_PokemonCenter_1F_OnTransition:
	setrespawn HEAL_LOCATION_OLDALE_TOWN
	call Common_EventScript_UpdateBrineyLocation
	end

OldaleTown_PokemonCenter_1F_EventScript_Nurse::
	setvar VAR_0x800B, LOCALID_OLDALE_NURSE
	call Common_EventScript_PkmnCenterNurse
	waitmessage
	waitbuttonpress
	release
	end

OldaleTown_PokemonCenter_1F_EventScript_Gentleman::
	msgbox OldaleTown_PokemonCenter_1F_Text_TrainersCanUsePC, MSGBOX_NPC
	end

OldaleTown_PokemonCenter_1F_EventScript_Boy::
	msgbox OldaleTown_PokemonCenter_1F_Text_PokemonCentersAreGreat, MSGBOX_NPC
	end

OldaleTown_PokemonCenter_1F_EventScript_Girl::
	lock
	faceplayer
	goto_if_set FLAG_SYS_POKEDEX_GET, OldaleTown_PokemonCenter_1F_EventScript_WirelessClubAvailable
	msgbox OldaleTown_PokemonCenter_1F_Text_WirelessClubNotAvailable, MSGBOX_DEFAULT
	release
	end

OldaleTown_PokemonCenter_1F_EventScript_WirelessClubAvailable::
	msgbox OldaleTown_PokemonCenter_1F_Text_TradedInWirelessClub, MSGBOX_DEFAULT
	release
	end

OldaleTown_PokemonCenter_1F_Text_TrainersCanUsePC:
	.string "That dusty old PC in the corner?\n"
	.string "You can use it. Everyone can.\p"
	.string "No password, no questions, no shame.$"

OldaleTown_PokemonCenter_1F_Text_PokemonCentersAreGreat:
	.string "This place? Totally Free.\n"
	.string "Unlimited healing, no judgment.\p"
	.string "Plus you get to stay here as long as you\n"
	.string "want and stare at this beautiful waitr..\l"
	.string "uhh, I mean Nurse.$"

OldaleTown_PokemonCenter_1F_Text_WirelessClubNotAvailable:
	.string "There’s a fancy setup upstairs now.\n"
	.string "Bunch of blinking lights and wires.\p"
	.string "Still not working. Classic.$"

OldaleTown_PokemonCenter_1F_Text_TradedInWirelessClub:
	.string "Went up there, made a trade, no questions asked.\p"
	.string "I might’ve given away something rare.\n"
	.string "No regrets. We vibe on instinct here.$"

