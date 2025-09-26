OldaleTown_PokemonCenter_1F_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, OldaleTown_PokemonCenter_1F_OnTransition
	map_script MAP_SCRIPT_ON_FRAME_TABLE, OldaleTown_PokemonCenter_1F_OnFrame
	map_script MAP_SCRIPT_ON_RESUME, CableClub_OnResume
	.byte 0

OldaleTown_PokemonCenter_1F_OnFrame:
	map_script_2 VAR_TEMP_0, 1, OldaleTown_PokemonCenter_EventScript_NurseIntro
	.2byte 0

OldaleTown_PokemonCenter_1F_OnTransition:
	setrespawn HEAL_LOCATION_OLDALE_TOWN
	call Common_EventScript_UpdateBrineyLocation
	goto_if_set FLAG_OLDALE_NURSE_INTRO_DONE, OldaleTown_PokemonCenter_1F_SkipNurseIntro
	setvar VAR_TEMP_0, 1
	end

OldaleTown_PokemonCenter_EventScript_NurseIntro::
	lock
	delay 50
	playbgm MUS_CONTEST_WINNER, TRUE
	waitse
	msgbox OldaleTown_PokemonCenter_Text_NurseIntro1, MSGBOX_DEFAULT
	closemessage
	call OldaleTown_PokemonCenter_EventScript_NurseIntroMovement
	msgbox OldaleTown_PokemonCenter_Text_NurseIntro2, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_OLDALE_NURSE, Common_Movement_WalkInPlaceFasterUp
	waitmovement 0
	delay 180
	applymovement LOCALID_OLDALE_NURSE, Common_Movement_WalkInPlaceFasterDown
	waitmovement 0
	msgbox OldaleTown_PokemonCenter_Text_NurseIntro3, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_OLDALE_NURSE, Common_Movement_WalkInPlaceFasterLeft
	waitmovement 0
	call EventScript_PkmnCenterNurse_TakeAndHealPkmn
	waitmovement 0
	applymovement LOCALID_OLDALE_NURSE, Common_Movement_WalkInPlaceFasterDown
	waitmovement 0
	msgbox gText_WeHopeToSeeYouAgain2, MSGBOX_DEFAULT
	closemessage
	setflag FLAG_OLDALE_NURSE_INTRO_DONE
	setvar VAR_TEMP_0, 0
	fadedefaultbgm
	release
	end

OldaleTown_PokemonCenter_1F_SkipNurseIntro:
	end	

OldaleTown_PokemonCenter_Text_NurseIntro1:
	.string "......\n"
	.string "Oh my god. No...\p"
	.string "Charlie? Are you serious right now?$"

OldaleTown_PokemonCenter_EventScript_NurseIntroMovement:
	applymovement LOCALID_PLAYER, OldaleTown_PokemonCenter_Movement_NurseIntroMovement
	waitmovement 0
	return

OldaleTown_PokemonCenter_Movement_NurseIntroMovement:
	walk_up
	walk_up
	walk_up
	walk_up
	step_end

OldaleTown_PokemonCenter_Text_NurseIntro2:
	.string "WAITRESS: You followed me here?\n"
	.string "You moved to TRASHBURG?!?\p"
	.string "This is harassment!\n"
	.string "I moved to a whole new region to get\l"
	.string "away from you.\p"
	.string "...... ...... ......\p"
	.string "WAITRESS: No.. Don’t say anything.\n"
	.string "I know what you’re gonna say...\p"
	.string "This is what you do, this is exactly it.\p"
	.string "You 'accidentally' run into me, then\n"
	.string "suddenly you’re in my POKéCENTER\l"
	.string "every day...\p"
	.string "I’m just here for the POKéMON. I've\n"
	.string "changed careers, I'm a Nurse now.\p"
	.string "And NO!\n"
	.string "You are NEVER getting a Pokémon\l"
	.string "physical from me... Ever!$"

OldaleTown_PokemonCenter_Text_NurseIntro3:
	.string "Well, come on. I have a job to do.\n"
	.string "Your POKéMON are more important...$"

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

