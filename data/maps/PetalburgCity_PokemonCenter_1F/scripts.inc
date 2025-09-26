PetalburgCity_PokemonCenter_1F_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, PetalburgCity_PokemonCenter_1F_OnTransition
	map_script MAP_SCRIPT_ON_FRAME_TABLE, PetalburgCity_PokemonCenter_1F_OnFrame
	map_script MAP_SCRIPT_ON_RESUME, CableClub_OnResume
	.byte 0

PetalburgCity_PokemonCenter_1F_OnFrame:
	map_script_2 VAR_TEMP_0, 1, PetalburgCity_PokemonCenter_EventScript_NurseIntro
	.2byte 0

PetalburgCity_PokemonCenter_1F_OnTransition:
	setrespawn HEAL_LOCATION_PETALBURG_CITY
	call Common_EventScript_UpdateBrineyLocation
	goto_if_set FLAG_PETALBURG_NURSE_INTRO_DONE, PetalburgCity_PokemonCenter_1F_SkipNurseIntro
	setvar VAR_TEMP_0, 1
	end

PetalburgCity_PokemonCenter_EventScript_NurseIntro::
	lock
	delay 50
	playbgm MUS_CONTEST_WINNER, TRUE
	waitse
	msgbox PetalburgCity_PokemonCenter_Text_NurseIntro1, MSGBOX_DEFAULT
	closemessage
	call PetalburgCity_PokemonCenter_EventScript_NurseIntroMovement
	msgbox PetalburgCity_PokemonCenter_Text_NurseIntro2, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_PETALBURG_NURSE, Common_Movement_WalkInPlaceFasterUp
	waitmovement 0
	delay 180
	applymovement LOCALID_PETALBURG_NURSE, Common_Movement_WalkInPlaceFasterDown
	waitmovement 0
	msgbox PetalburgCity_PokemonCenter_Text_NurseIntro3, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_PETALBURG_NURSE, Common_Movement_WalkInPlaceFasterLeft
	waitmovement 0
	call EventScript_PkmnCenterNurse_TakeAndHealPkmn
	waitmovement 0
	applymovement LOCALID_PETALBURG_NURSE, Common_Movement_WalkInPlaceFasterDown
	waitmovement 0
	msgbox gText_ThankYouForWaiting, MSGBOX_DEFAULT
	closemessage
	setflag FLAG_PETALBURG_NURSE_INTRO_DONE
	setvar VAR_TEMP_0, 0
	fadedefaultbgm
	release
	end

PetalburgCity_PokemonCenter_1F_SkipNurseIntro:
	end		

PetalburgCity_PokemonCenter_Text_NurseIntro1:
	.string "Charlie, seriously?\n"
	.string "You’re stalking me now?\p"
	.string "What, you got nothing better to do?$"

PetalburgCity_PokemonCenter_EventScript_NurseIntroMovement:
	applymovement LOCALID_PLAYER, OldaleTown_PokemonCenter_Movement_NurseIntroMovement
	waitmovement 0
	return

PetalburgCity_PokemonCenter_Movement_NurseIntroMovement:
	walk_up
	walk_up
	walk_up
	walk_up
	step_end


PetalburgCity_PokemonCenter_Text_NurseIntro2:
	.string "WAITRESS: Look, I’m the Nurse of every\n"
	.string "damn town now. I got a promotion.\p"
	.string "If you think I’m gonna fall for your\n"
	.string "weird little obsession? Get real.\p"
	.string "..... ....... ...... ........\p"
	.string "Do you think this is some kind of game?\p"
	.string "Shit… I gotta keep it professional.\p"
	.string "Trust me, I’m way too broke to lose\n"
	.string "this gig.\p"
	.string "It’s the only thing that’s actually\n"
	.string "paying me decent money for once.\p"
	.string "Do us both a favor and keep your creepy\n"
	.string "antics to yourself, alright?\p"
	.string "I’m here to heal Pokémon,\n"
	.string "not babysit you.$"

PetalburgCity_PokemonCenter_Text_NurseIntro3:
	.string "WAITRESS: Well, what are you waiting\n"
	.string "for? Give me your POKéMON...$"

PetalburgCity_PokemonCenter_1F_EventScript_Nurse::
	setvar VAR_0x800B, LOCALID_PETALBURG_NURSE
	call Common_EventScript_PkmnCenterNurse
	waitmessage
	waitbuttonpress
	release
	end

PetalburgCity_PokemonCenter_1F_EventScript_FatMan::
	msgbox PetalburgCity_PokemonCenter_1F_Text_PCStorageSystem, MSGBOX_NPC
	end

PetalburgCity_PokemonCenter_1F_EventScript_Youngster::
	msgbox PetalburgCity_PokemonCenter_1F_Text_OranBerryRegainedHP, MSGBOX_NPC
	end

PetalburgCity_PokemonCenter_1F_EventScript_Woman::
	lock
	faceplayer
	msgbox PetalburgCity_PokemonCenter_1F_Text_ManyTypesOfPokemon, MSGBOX_DEFAULT
	specialvar VAR_RESULT, IsStarterInParty
	goto_if_eq VAR_RESULT, TRUE, PetalburgCity_PokemonCenter_1F_EventScript_SayStarterTypeInfo
	release
	end

PetalburgCity_PokemonCenter_1F_EventScript_SayStarterTypeInfo::
	call_if_eq VAR_STARTER_MON, 0, PetalburgCity_PokemonCenter_1F_EventScript_SayBulbasaurType
	call_if_eq VAR_STARTER_MON, 1, PetalburgCity_PokemonCenter_1F_EventScript_SayGibleType
	call_if_eq VAR_STARTER_MON, 2, PetalburgCity_PokemonCenter_1F_EventScript_SayAronType
	release
	end

PetalburgCity_PokemonCenter_1F_EventScript_SayBulbasaurType::
	msgbox PetalburgCity_PokemonCenter_1F_Text_BulbasaurIsGrassType, MSGBOX_DEFAULT
	return

PetalburgCity_PokemonCenter_1F_EventScript_SayGibleType::
	msgbox PetalburgCity_PokemonCenter_1F_Text_GibleIsDragonType, MSGBOX_DEFAULT
	return

PetalburgCity_PokemonCenter_1F_EventScript_SayAronType::
	msgbox PetalburgCity_PokemonCenter_1F_Text_AronIsSteelType, MSGBOX_DEFAULT
	return

PetalburgCity_PokemonCenter_1F_Text_PCStorageSystem:
	.string "This PC-based POKéMON Storage\n"
	.string "System, huh…\p"
	.string "Gotta say, whoever cooked this up\n"
	.string "is one heck of a science whiz!$"

PetalburgCity_PokemonCenter_1F_Text_OranBerryRegainedHP:
	.string "Check it out! When my POKéMON\n"
	.string "munches an ORAN BERRY,\l"
	.string "it bounces back some HP!\p"
	.string "I wonder if I can teach a thing or\n"
	.string "two about berries to this hot Nurse.\p"
	.string "Maybe she can teach me a thing or two\n"
	.string "about Nursing...$"

PetalburgCity_PokemonCenter_1F_Text_ManyTypesOfPokemon:
	.string "There are many types of POKéMON.\p"
	.string "All types have their strengths and\n"
	.string "weaknesses against other types.\p"
	.string "Depending on the types of POKéMON,\n"
	.string "a battle could be easy or hard.$"

PetalburgCity_PokemonCenter_1F_Text_BulbasaurIsGrassType:
	.string "For example, your BULBASAUR is a\n"
	.string "GRASS and POISON type.\p"
	.string "It’s strong against WATER, ROCK, and\n"
	.string "GROUND types.\p"
	.string "But it’s weak to FIRE, FLYING, and\n"
	.string "ICE-type POKéMON.$"


PetalburgCity_PokemonCenter_1F_Text_GibleIsDragonType:
	.string "For example, your GIBLE is a DRAGON\n"
	.string "and GROUND type.\p"
	.string "It’s strong against FIRE, ELECTRIC,\n"
	.string "POISON, ROCK, and STEEL types.\p"
	.string "But it’s weak to ICE, DRAGON, and\n"
	.string "FAIRY-type POKéMON.$"


PetalburgCity_PokemonCenter_1F_Text_AronIsSteelType:
	.string "For example, your ARON is a STEEL and\n"
	.string "ROCK type.\p"
	.string "It’s strong against NORMAL, FLYING,\n"
	.string "ROCK, BUG, STEEL, GRASS, and ICE types.\p"
	.string "But it’s weak to FIGHTING, GROUND,\n"
	.string "WATER, and FIRE-type POKéMON.$"

 



