PetalburgCity_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, PetalburgCity_OnTransition
	map_script MAP_SCRIPT_ON_FRAME_TABLE, PetalburgCity_OnFrame
	.byte 0

PetalburgCity_OnTransition:
	setflag FLAG_VISITED_PETALBURG_CITY
	setflag FLAG_HIDE_PETALBURG_CITY_BIRCH
	call_if_eq VAR_PETALBURG_CITY_STATE, 0, PetalburgCity_EventScript_MoveGymBoyToWestEntrance
	call_if_eq VAR_PETALBURG_CITY_STATE, 2, PetalburgCity_EventScript_DisableMapNameAndMusic
	call_if_eq VAR_PETALBURG_CITY_STATE, 4, PetalburgCity_EventScript_DisableMapNameAndMusic
	call_if_eq VAR_PETALBURG_GYM_STATE, 8, PetalburgCity_EventScript_SetGymDoorsUnlocked
	end

PetalburgCity_EventScript_MoveGymBoyToWestEntrance::
	setobjectxyperm LOCALID_GYM_BOY, 36, 17
	return

PetalburgCity_EventScript_DisableMapNameAndMusic::
	setflag FLAG_HIDE_MAP_NAME_POPUP
	savebgm MUS_FOLLOW_ME
	return

PetalburgCity_EventScript_SetGymDoorsUnlocked::
	setvar VAR_PETALBURG_GYM_STATE, 7
	return

PetalburgCity_OnFrame:
	map_script_2 VAR_PETALBURG_CITY_STATE, 2, PetalburgCity_EventScript_WallyTutorial
	map_script_2 VAR_PETALBURG_CITY_STATE, 4, PetalburgCity_EventScript_WalkToWallyHouse
	.2byte 0

PetalburgCity_EventScript_WallyTutorial::
	lockall
	special SavePlayerParty
	special LoadWallyZigzagoon
	applymovement LOCALID_PETALBURG_WALLY, PetalburgCity_Movement_WallyTutorialWally
	applymovement LOCALID_PLAYER, PetalburgCity_Movement_WallyTutorialPlayer
	waitmovement 0
	msgbox Route102_Text_WatchMeCatchPokemon, MSGBOX_DEFAULT
	special StartWallyTutorialBattle
	waitstate
	msgbox Route102_Text_WallyIDidIt, MSGBOX_DEFAULT
	applymovement LOCALID_PETALBURG_WALLY, Common_Movement_WalkInPlaceFasterLeft, MAP_PETALBURG_CITY
	waitmovement LOCALID_PETALBURG_WALLY, MAP_PETALBURG_CITY
	msgbox Route102_Text_LetsGoBack, MSGBOX_DEFAULT
	closemessage
	clearflag FLAG_HIDE_MAP_NAME_POPUP
	setvar VAR_PETALBURG_CITY_STATE, 3
	fadedefaultbgm
	clearflag FLAG_DONT_TRANSITION_MUSIC
	special LoadPlayerParty
	setvar VAR_PETALBURG_GYM_STATE, 1
	warp MAP_PETALBURG_CITY_GYM, 4, 108
	waitstate
	releaseall
	end

PetalburgCity_EventScript_WalkToWallyHouse::
	lockall
	setflag FLAG_HIDE_MAP_NAME_POPUP
	applymovement LOCALID_PETALBURG_WALLYS_DAD, PetalburgCity_Movement_WalkToWallyHouseWallysDad
	applymovement LOCALID_PLAYER, PetalburgCity_Movement_WalkToWallyHousePlayer
	waitmovement 0
	setvar VAR_0x8004, 7
	setvar VAR_0x8005, 5
	opendoor VAR_0x8004, VAR_0x8005
	waitdooranim
	applymovement LOCALID_PETALBURG_WALLYS_DAD, PetalburgCity_Movement_WalkInsideHouseWallysDad
	applymovement LOCALID_PLAYER, PetalburgCity_Movement_WalkInsideHousePlayer
	waitmovement 0
	setflag FLAG_HIDE_PETALBURG_CITY_WALLYS_DAD
	hideobjectat LOCALID_PLAYER, MAP_PETALBURG_CITY
	closedoor VAR_0x8004, VAR_0x8005
	waitdooranim
	clearflag FLAG_HIDE_MAP_NAME_POPUP
	fadedefaultbgm
	clearflag FLAG_DONT_TRANSITION_MUSIC
	warp MAP_PETALBURG_CITY_WALLYS_HOUSE, 2, 4
	waitstate
	releaseall
	end

PetalburgCity_EventScript_Boy::
	lock
	faceplayer
	msgbox PetalburgCity_Text_WaterReflection, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_PETALBURG_BOY, Common_Movement_FaceOriginalDirection
	waitmovement 0
	checkflag FLAG_HIDDEN_ITEM_PETALBURG_CITY_NUGGET
    goto_if TRUE, PetalburgCity_EventScript_NuggetBush_End
	checkflag FLAG_PETALBURG_CITY_CAN_SEARCH_BUSHES
	goto_if TRUE, PetalburgCity_EventScript_NuggetBush_End
	goto PetalburgCity_EventScript_NuggetQuestIntro
	end

PetalburgCity_EventScript_NuggetQuestIntro::
	applymovement LOCALID_PLAYER, Common_Movement_SelfText
	waitmovement 0
	msgbox PetalburgCity_Text_NuggetQuestIntro, MSGBOX_DEFAULT
	release
	setflag FLAG_PETALBURG_CITY_CAN_SEARCH_BUSHES
	end
	
PetalburgCity_EventScript_WallysMom::
	msgbox PetalburgCity_Text_WhereIsWally, MSGBOX_NPC
	end

PetalburgCity_Movement_WalkToWallyHousePlayer:
	delay_8
	walk_down
	walk_down
	walk_down
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	step_end

PetalburgCity_Movement_WalkInsideHousePlayer:
	walk_up
	walk_up
	step_end

PetalburgCity_Movement_WalkToWallyHouseWallysDad:
	delay_8
	walk_down
	walk_down
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	step_end

PetalburgCity_Movement_WalkInsideHouseWallysDad:
	walk_up
	set_invisible
	step_end

PetalburgCity_Movement_WallyTutorialPlayer:
	delay_8
	walk_down
	walk_down
	walk_down
	walk_down
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_up
	walk_up
	walk_up
	walk_in_place_faster_right
	step_end

PetalburgCity_Movement_WallyTutorialWally:
	delay_16
	delay_16
	walk_down
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_up
	walk_up
	walk_up
	walk_right
	delay_16
	walk_in_place_faster_left
	step_end

PetalburgCity_EventScript_GymSign::
	msgbox PetalburgCity_Text_GymSign, MSGBOX_SIGN
	end

PetalburgCity_EventScript_CitySign::
	msgbox PetalburgCity_Text_CitySign, MSGBOX_SIGN
	end

PetalburgCity_EventScript_Gentleman::
	msgbox PetalburgCity_Text_FullPartyExplanation, MSGBOX_NPC
	end

PetalburgCity_EventScript_WallyHouseSign::
	msgbox PetalburgCity_Text_WallyHouseSign, MSGBOX_SIGN
	end

PetalburgCity_EventScript_ShowGymToPlayer0::
	lockall
	setvar VAR_0x8008, 0
	goto PetalburgCity_EventScript_ShowGymToPlayer
	end

PetalburgCity_EventScript_ShowGymToPlayer1::
	lockall
	setvar VAR_0x8008, 1
	goto PetalburgCity_EventScript_ShowGymToPlayer
	end

PetalburgCity_EventScript_ShowGymToPlayer2::
	lockall
	setvar VAR_0x8008, 2
	goto PetalburgCity_EventScript_ShowGymToPlayer
	end

PetalburgCity_EventScript_ShowGymToPlayer3::
	lockall
	setvar VAR_0x8008, 3
	goto PetalburgCity_EventScript_ShowGymToPlayer
	end

PetalburgCity_EventScript_ShowGymToPlayer::
	applymovement LOCALID_GYM_BOY, Common_Movement_FacePlayer
	waitmovement 0
	playbgm MUS_FOLLOW_ME, FALSE
	playse SE_PIN
	applymovement LOCALID_GYM_BOY, Common_Movement_ExclamationMark
	waitmovement 0
	applymovement LOCALID_GYM_BOY, Common_Movement_Delay48
	waitmovement 0
	call_if_eq VAR_0x8008, 0, PetalburgCity_EventScript_BoyApproachPlayer0
	call_if_eq VAR_0x8008, 1, PetalburgCity_EventScript_BoyApproachPlayer1
	call_if_eq VAR_0x8008, 2, PetalburgCity_EventScript_BoyApproachPlayer2
	call_if_eq VAR_0x8008, 3, PetalburgCity_EventScript_BoyApproachPlayer3
	msgbox PetalburgCity_Text_AreYouRookieTrainer, MSGBOX_DEFAULT
	closemessage
	call_if_eq VAR_0x8008, 0, PetalburgCity_EventScript_LeadPlayerToGym0
	call_if_eq VAR_0x8008, 1, PetalburgCity_EventScript_LeadPlayerToGym1
	call_if_eq VAR_0x8008, 2, PetalburgCity_EventScript_LeadPlayerToGym2
	call_if_eq VAR_0x8008, 3, PetalburgCity_EventScript_LeadPlayerToGym3
	msgbox PetalburgCity_Text_ThisIsPetalburgGym, MSGBOX_DEFAULT
	applymovement LOCALID_GYM_BOY, Common_Movement_WalkInPlaceFasterLeft
	waitmovement 0
	msgbox PetalburgCity_Text_ThisIsGymSign, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_GYM_BOY, Common_Movement_WalkInPlaceFasterDown
	waitmovement 0
	msgbox PetalburgCity_Text_ThisIsYourUncle, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_PLAYER, PetalburgCity_Movement_WalkToGym
	waitmovement 0
	setvar VAR_0x8004, 39
	setvar VAR_0x8005, 28
	opendoor VAR_0x8004, VAR_0x8005
	waitdooranim
	applymovement LOCALID_PLAYER, PetalburgCity_Movement_WalkInGym
	waitmovement 0
	setvar VAR_PETALBURG_GYM_STATE, 10
	warp MAP_PETALBURG_CITY_GYM, 4, 111
	waitstate
	closedoor VAR_0x8004, VAR_0x8005
	waitdooranim
	fadedefaultbgm
	releaseall
	end

PetalburgCity_EventScript_BoyApproachPlayer0::
	applymovement LOCALID_GYM_BOY, PetalburgCity_Movement_BoyApproachPlayer0
	waitmovement 0
	applymovement LOCALID_PLAYER, Common_Movement_WalkInPlaceFasterDown
	waitmovement 0
	return

PetalburgCity_EventScript_BoyApproachPlayer1::
	applymovement LOCALID_GYM_BOY, PetalburgCity_Movement_BoyApproachPlayer1
	waitmovement 0
	return

PetalburgCity_EventScript_BoyApproachPlayer2::
	applymovement LOCALID_GYM_BOY, PetalburgCity_Movement_BoyApproachPlayer2
	waitmovement 0
	applymovement LOCALID_PLAYER, Common_Movement_WalkInPlaceFasterUp
	waitmovement 0
	return

PetalburgCity_EventScript_BoyApproachPlayer3::
	applymovement LOCALID_GYM_BOY, PetalburgCity_Movement_BoyApproachPlayer3
	waitmovement 0
	applymovement LOCALID_PLAYER, Common_Movement_WalkInPlaceFasterUp
	waitmovement 0
	return

PetalburgCity_EventScript_LeadPlayerToGym0::
	applymovement LOCALID_GYM_BOY, PetalburgCity_Movement_BoyWalkToGym0
	applymovement LOCALID_PLAYER, PetalburgCity_Movement_PlayerWalkToGym0
	waitmovement 0
	return

PetalburgCity_EventScript_LeadPlayerToGym1::
	applymovement LOCALID_GYM_BOY, PetalburgCity_Movement_BoyWalkToGym1
	applymovement LOCALID_PLAYER, PetalburgCity_Movement_PlayerWalkToGym1
	waitmovement 0
	return

PetalburgCity_EventScript_LeadPlayerToGym2::
	applymovement LOCALID_GYM_BOY, PetalburgCity_Movement_BoyWalkToGym2
	applymovement LOCALID_PLAYER, PetalburgCity_Movement_PlayerWalkToGym2
	waitmovement 0
	return

PetalburgCity_EventScript_LeadPlayerToGym3::
	applymovement LOCALID_GYM_BOY, PetalburgCity_Movement_BoyWalkToGym3
	applymovement LOCALID_PLAYER, PetalburgCity_Movement_PlayerWalkToGym3
	waitmovement 0
	return

@ Unused
PetalburgCity_Movement_Delay48::
	delay_16
	delay_16
	delay_16
	step_end

PetalburgCity_Movement_BoyApproachPlayer0:
	walk_right
	walk_right
	walk_right
	walk_in_place_faster_up
	step_end

PetalburgCity_Movement_BoyApproachPlayer1:
	walk_right
	walk_right
	step_end

PetalburgCity_Movement_BoyApproachPlayer2:
	walk_right
	walk_right
	walk_right
	walk_in_place_faster_down
	step_end

PetalburgCity_Movement_BoyApproachPlayer3:
	walk_right
	walk_right
	walk_right
	walk_down
	step_end

PetalburgCity_Movement_BoyWalkToGym0:
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_up
	walk_up
	walk_in_place_faster_down
	step_end

PetalburgCity_Movement_BoyWalkToGym1:
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_up
	walk_up
	walk_in_place_faster_down
	step_end

PetalburgCity_Movement_BoyWalkToGym2:
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_up
	walk_up
	walk_in_place_faster_down
	step_end

PetalburgCity_Movement_BoyWalkToGym3:
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_up
	walk_up
	walk_in_place_faster_down
	step_end

PetalburgCity_Movement_WalkToGym:
	walk_right
	walk_up
	walk_up
	walk_up
	step_end

PetalburgCity_Movement_WalkInGym::
	walk_up
	step_end

PetalburgCity_Movement_PlayerWalkToGym0:
	delay_16
	walk_down
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_up
	step_end

PetalburgCity_Movement_PlayerWalkToGym1:
	delay_16
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_up
	step_end

PetalburgCity_Movement_PlayerWalkToGym2:
	delay_16
	walk_up
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_up
	step_end

PetalburgCity_Movement_PlayerWalkToGym3:
	delay_16
	walk_up
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_up
	step_end

PetalburgCity_EventScript_Scott1::
	lockall
	addobject LOCALID_PETALBURG_SCOTT
	setvar VAR_0x8008, 1
	setobjectxy LOCALID_PETALBURG_SCOTT, 27, 13
	goto PetalburgCity_EventScript_Scott
	end

PetalburgCity_EventScript_Scott2::
	lockall
	addobject LOCALID_PETALBURG_SCOTT
	setvar VAR_0x8008, 2
	setobjectxy LOCALID_PETALBURG_SCOTT, 27, 14
	goto PetalburgCity_EventScript_Scott
	end

PetalburgCity_EventScript_Scott3::
	lockall
	addobject LOCALID_PETALBURG_SCOTT
	setvar VAR_0x8008, 3
	setobjectxy LOCALID_PETALBURG_SCOTT, 27, 15
	goto PetalburgCity_EventScript_Scott
	end

PetalburgCity_EventScript_Scott::
	applymovement LOCALID_PETALBURG_SCOTT, PetalburgCity_Movement_ScottStartWalkLeft
	waitmovement 0
	playse SE_PIN
	applymovement LOCALID_PETALBURG_SCOTT, Common_Movement_ExclamationMark
	waitmovement 0
	applymovement LOCALID_PETALBURG_SCOTT, Common_Movement_Delay48
	waitmovement 0
	applymovement LOCALID_PETALBURG_SCOTT, PetalburgCity_Movement_ScottApproachPlayer
	waitmovement 0
	applymovement LOCALID_PLAYER, Common_Movement_WalkInPlaceFasterRight
	waitmovement 0
	setvar VAR_SCOTT_STATE, 1
	msgbox PetalburgCity_Text_AreYouATrainer, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_PETALBURG_SCOTT, Common_Movement_WalkInPlaceFasterRight
	waitmovement 0
	delay 30
	msgbox PetalburgCity_Text_WellMaybeNot, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_PETALBURG_SCOTT, Common_Movement_WalkInPlaceFasterLeft
	waitmovement 0
	delay 30
	msgbox PetalburgCity_Text_ImLookingForTalentedTrainers, MSGBOX_DEFAULT
	closemessage
	call_if_eq VAR_0x8008, 1, PetalburgCity_EventScript_ScottExit1
	call_if_eq VAR_0x8008, 2, PetalburgCity_EventScript_ScottExit2
	call_if_eq VAR_0x8008, 3, PetalburgCity_EventScript_ScottExit3
	setvar VAR_SCOTT_PETALBURG_ENCOUNTER, 1
	removeobject LOCALID_PETALBURG_SCOTT
	releaseall
	end

PetalburgCity_EventScript_ScottExit1::
	applymovement LOCALID_PLAYER, PetalburgCity_Movement_PlayerWatchScottExit1
	applymovement LOCALID_PETALBURG_SCOTT, PetalburgCity_Movement_ScottExit1
	waitmovement 0
	return

PetalburgCity_EventScript_ScottExit2::
	applymovement LOCALID_PLAYER, PetalburgCity_Movement_PlayerWatchScottExit2
	applymovement LOCALID_PETALBURG_SCOTT, PetalburgCity_Movement_ScottExit2
	waitmovement 0
	return

PetalburgCity_EventScript_ScottExit3::
	applymovement LOCALID_PLAYER, PetalburgCity_Movement_PlayerWatchScottExit3
	applymovement LOCALID_PETALBURG_SCOTT, PetalburgCity_Movement_ScottExit3
	waitmovement 0
	return

PetalburgCity_Movement_ScottStartWalkLeft:
	walk_left
	walk_left
	walk_left
	step_end

PetalburgCity_Movement_ScottApproachPlayer:
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	step_end

PetalburgCity_Movement_ScottExit0:
	walk_down
	walk_left
	walk_left
	walk_left
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	step_end

PetalburgCity_Movement_PlayerWatchScottExit0:
	delay_16
	walk_in_place_faster_down
	delay_16
	delay_16
	delay_8
	walk_in_place_faster_left
	step_end

PetalburgCity_Movement_ScottExit1:
	walk_down
	walk_left
	walk_left
	walk_left
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	step_end

PetalburgCity_Movement_PlayerWatchScottExit1:
	delay_16
	walk_in_place_faster_down
	delay_16
	delay_8
	walk_in_place_faster_left
	step_end

PetalburgCity_Movement_ScottExit2:
	walk_up
	walk_left
	walk_left
	walk_left
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	step_end

PetalburgCity_Movement_PlayerWatchScottExit2:
	delay_16
	walk_in_place_faster_up
	delay_16
	delay_8
	walk_in_place_faster_left
	step_end

PetalburgCity_Movement_ScottExit3:
	walk_up
	walk_left
	walk_left
	walk_left
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	step_end

PetalburgCity_Movement_PlayerWatchScottExit3:
	delay_16
	walk_in_place_faster_up
	delay_16
	delay_8
	walk_in_place_faster_left
	step_end

PetalburgCity_EventScript_GymBoy::
	msgbox PetalburgCity_Text_GymBoy2, MSGBOX_NPC
	end

PetalburgCity_Text_WhereIsWally:
	.string "Where did Matthew dip off to?\p"
	.string "We've gotta head to Verdanturf soon,\n"
	.string "no time for slacking.$"

PetalburgCity_Text_AreYouRookieTrainer:
	.string "Hey, you a rookie TRAINER or just\n"
	.string "playin’ dress-up?\p"
	.string "Listen up.\p"
	.string "When you hit a new town, first thing\n"
	.string "you do is check out the GYM.\p"
	.string "That’s how you know who’s boss around\n"
	.string "here.$"

PetalburgCity_Text_ThisIsPetalburgGym:
	.string "Welcome to GIANT'S REACH GYM.\p"
	.string "This is where Jack throws down.$"

PetalburgCity_Text_ThisIsGymSign:
	.string "That sign? That’s the GYM’s mark.\p"
	.string "If you see it, you know thats where\n"
	.string "you need to go for a great fight!$"

PetalburgCity_Text_ThisIsYourUncle:
	.string "..................\p"
	.string "Oh, this is your Uncle's GYM?\n"
	.string "Head on inside!$"

PetalburgCity_Text_GymBoy2:
	.string "I love this GYM.\n"
	.string "Jack’s the best.\p"
	.string "He’s got big hands, sharp mind,\n"
	.string "and a heart of gold.$"

PetalburgCity_Text_WaterReflection:
	.string "Lookin’ in the water, I only see\n"
	.string "my stupid face.\p"
	.string "Shoulda been a grin, but nah.\p"
	.string "Lost my damn Nugget in some bush,\n"
	.string "now I’m stuck here feelin’ like a chump.\p"
	.string "It’s gotta be around this jawn\n"
	.string "somewhere...$"

PetalburgCity_Text_NuggetQuestIntro:
	.string "Better search these bushes to\n"
	.string "find that Nugget before I go!$"

PetalburgCity_Text_FullPartyExplanation:
	.string "You got six POKéMON yet?\p"
	.string "Catch another? It ain’t joinin’ your\n"
	.string "crew.\p"
	.string "It gets tossed in the STORAGE BOX,\n"
	.string "chillin’ in the PC until you wanna\l"
	.string "deal with it.$"

PetalburgCity_Text_GymSign:
	.string "GIANT’S REACH POKéMON GYM\n"
	.string "LEADER: JACK\p"
	.string "Big hands. Sharp mind.\n"
	.string "Final verdict: defeat.$"

PetalburgCity_Text_CitySign:
	.string "GIANT'S REACH:\n"
	.string "Justice served with a giant’s grip.$"

PetalburgCity_Text_WallyHouseSign:
	.string "HOLY HOUSE$"

PetalburgCity_Text_AreYouATrainer:
	.string "Yo, hold up! Lemme guess.\p"
	.string "Lookin’ at how you’re\n"
	.string "dressed, you a POKéMON TRAINER or what?$"

PetalburgCity_Text_WellMaybeNot:
	.string "… … … … … …\p"
	.string "Eh, maybe not.\p"
	.string "Your clothes ain’t dirty enough to be\n"
	.string "a real trainer.\p"
	.string "You either new to this or just some kid\n"
	.string "playin’ at it.$"

PetalburgCity_Text_ImLookingForTalentedTrainers:
	.string "I’m huntin’ for real talent.\p"
	.string "Don’t waste my time if you ain’t\n"
	.string "serious.$"

PetalburgCity_Eventscript_NuggetBush::
	checkflag FLAG_PETALBURG_CITY_CAN_SEARCH_BUSHES
    goto_if FALSE, PetalburgCity_EventScript_NuggetBush_End
    checkflag FLAG_HIDDEN_ITEM_PETALBURG_CITY_NUGGET
    goto_if TRUE, PetalburgCity_EventScript_NuggetBush_End
    msgbox PetalburgCity_Text_FoundNugget, MSGBOX_SIGN
	waitmessage
	playfanfare MUS_OBTAIN_ITEM
	giveitem ITEM_NUGGET, 1
	setflag FLAG_HIDDEN_ITEM_PETALBURG_CITY_NUGGET
    msgbox PetalburgCity_Text_AfterFoundNugget, MSGBOX_SIGN
	goto PetalburgCity_EventScript_NuggetBush_End

PetalburgCity_EventScript_NuggetBush_End:
	release
    end

PetalburgCity_Text_FoundNugget:
	.string "You search the bush...\p"
    .string "You found a Nugget!$"

PetalburgCity_EventScript_EmptyBush::
    checkflag FLAG_PETALBURG_CITY_CAN_SEARCH_BUSHES
    goto_if FALSE, PetalburgCity_EventScript_EmptyBush_End
    checkflag FLAG_HIDDEN_ITEM_PETALBURG_CITY_NUGGET
    goto_if TRUE, PetalburgCity_EventScript_EmptyBush_End
    msgbox PetalburgCity_Text_EmptyBush, MSGBOX_SIGN
PetalburgCity_EventScript_EmptyBush_End:
    end

PetalburgCity_Text_EmptyBush:
	.string "You search the bush...\p"
	.string "No Nugget here...$"

PetalburgCity_Text_AfterFoundNugget:
	.string "One man's mistake is another man's\n"
	.string "treasure.$"

PetalburgCity_EventScript_Birch0::
	lockall
	questmenu QUEST_MENU_CHECK_ACTIVE, QUEST_3_ROOT_FOSSIL
	goto_if_eq VAR_RESULT, TRUE, PetalburgCity_EventScript_Birch_AlreadyActive
	addobject LOCALID_PETALBURG_BIRCH
	setobjectxy LOCALID_PETALBURG_BIRCH, 15, 21
	goto PetalburgCity_EventScript_Birch_Quest3
	end	

PetalburgCity_EventScript_Birch1::
	lockall
	questmenu QUEST_MENU_CHECK_ACTIVE, QUEST_3_ROOT_FOSSIL
	goto_if_eq VAR_RESULT, TRUE, PetalburgCity_EventScript_Birch_AlreadyActive
	addobject LOCALID_PETALBURG_BIRCH
	setobjectxy LOCALID_PETALBURG_BIRCH, 16, 21
	goto PetalburgCity_EventScript_Birch_Quest3
	end

PetalburgCity_EventScript_Birch_AlreadyActive::
	releaseall
	end

PetalburgCity_EventScript_Birch_Quest3::
	playse SE_PIN
	applymovement LOCALID_PLAYER, Common_Movement_ExclamationMark
	delay 8
	applymovement LOCALID_PLAYER, Common_Movement_WalkInPlaceFasterUp
	waitmovement 0
	applymovement LOCALID_PETALBURG_BIRCH, PetalburgCity_Movement_BirchStartWalkDown
	waitmovement 0
	playse SE_PIN
	applymovement LOCALID_PETALBURG_BIRCH, Common_Movement_ExclamationMark
	waitmovement 0
	applymovement LOCALID_PETALBURG_BIRCH, Common_Movement_Delay48
	waitmovement 0
	applymovement LOCALID_PETALBURG_BIRCH, PetalburgCity_Movement_BirchApproachPlayer
	waitmovement 0
	msgbox PetalburgCity_Text_Birch_Quest3_Start1, MSGBOX_DEFAULT
	closemessage
	delay 30
	msgbox PetalburgCity_Text_Birch_Quest3_Start2, MSGBOX_DEFAULT
	closemessage
	delay 30
	goto PetalburgCity_EventScript_BirchExit
	end
	
	PetalburgCity_EventScript_BirchExit::
	applymovement LOCALID_PETALBURG_BIRCH, PetalburgCity_Movement_BirchExit
	waitmovement 0
	removeobject LOCALID_PETALBURG_BIRCH
	startquest QUEST_3_ROOT_FOSSIL
	setvar VAR_PETALBURG_CITY_QUEST_3, 1
	releaseall
	end	

PetalburgCity_Movement_BirchStartWalkDown:
	walk_down
	walk_down
	walk_down
	walk_down
	step_end

PetalburgCity_Movement_BirchApproachPlayer:
	walk_down
	step_end	

PetalburgCity_Movement_BirchExit:	
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	step_end

PetalburgCity_Text_Birch_Quest3_Start1:
	.string "Hey-o, Charlie.\p"
	.string "Listen, I been tailin’ you around\n"
	.string "‘cause I wanna play a little game.\p"
	.string "Yeah, a game.\p"
	.string "I got a riddle for ya.\p"
	.string "And no, it ain’t one’a those\n"
	.string "kid crap riddles...\p"
	.string "This one’s got stakes.\p"
	.string "I stashed somethin’ in this town.\n"
	.string "You find it, it’s yours.\p"
	.string "Don’t ask me where I got it.\p"
	.string "Alright, here we go:\p"
	.string "A little vase with leafy hair,\n"
	.string "got somethin’ juicy hid in there.\l"
	.string "Don’t go screw around in the grass,\l"
	.string "the prize sits where trainers pass.$"

PetalburgCity_Text_Birch_Quest3_Start2:
	.string "Now, I’m gonna head up to the\n"
	.string "church house, or whatever the hell\l"
	.string "it is.\p"
	.string "I got some questions for the priests.\p"
	.string "Wanna see just how much I can\n"
	.string "do before the big man upstairs blows\l"
	.string "a gasket.\p"
	.string "Come see me when you find it.$"
