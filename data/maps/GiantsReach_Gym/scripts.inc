GiantsReach_Gym_MapScripts::
	map_script MAP_SCRIPT_ON_LOAD, GiantsReach_Gym_OnLoad
	map_script MAP_SCRIPT_ON_TRANSITION, GiantsReach_Gym_OnTransition
	map_script MAP_SCRIPT_ON_WARP_INTO_MAP_TABLE, GiantsReach_Gym_OnWarp
	map_script MAP_SCRIPT_ON_FRAME_TABLE, GiantsReach_Gym_OnFrame
	.byte 0

GiantsReach_Gym_OnLoad:
	goto_if_eq VAR_GIANTS_REACH_GYM_STATE, 6, GiantsReach_Gym_EventScript_OpenUnlockedDoors
	call_if_ge VAR_GIANTS_REACH_GYM_STATE, 7, GiantsReach_Gym_EventScript_UnlockAllDoors
	end

@ NOTE: Strength and OHKO rooms are misleading. Both are more accurately Critical-Hit
GiantsReach_Gym_EventScript_OpenUnlockedDoors::
	setvar VAR_0x8005, 1
	call GiantsReach_Gym_EventScript_OpenGymEntranceDoors
	call_if_defeated TRAINER_RANDALL, GiantsReach_Gym_EventScript_OpenSpeedRoomDoors
	call_if_defeated TRAINER_MARY, GiantsReach_Gym_EventScript_OpenAccuracyRoomDoors
	call_if_defeated TRAINER_PARKER, GiantsReach_Gym_EventScript_OpenConfusionRoomDoors
	call_if_defeated TRAINER_ALEXIA, GiantsReach_Gym_EventScript_OpenDefenseRoomDoors
	call_if_defeated TRAINER_GEORGE, GiantsReach_Gym_EventScript_OpenRecoveryRoomDoors
	call_if_defeated TRAINER_JODY, GiantsReach_Gym_EventScript_OpenStrengthRoomDoors
	call_if_defeated TRAINER_BERKE, GiantsReach_Gym_EventScript_OpenOHKORoomDoors
	end

GiantsReach_Gym_EventScript_UnlockAllDoors::
	setvar VAR_0x8005, 1
	call GiantsReach_Gym_EventScript_OpenGymEntranceDoors
	call GiantsReach_Gym_EventScript_OpenSpeedRoomDoors
	call GiantsReach_Gym_EventScript_OpenAccuracyRoomDoors
	call GiantsReach_Gym_EventScript_OpenConfusionRoomDoors
	call GiantsReach_Gym_EventScript_OpenDefenseRoomDoors
	call GiantsReach_Gym_EventScript_OpenRecoveryRoomDoors
	call GiantsReach_Gym_EventScript_OpenStrengthRoomDoors
	call GiantsReach_Gym_EventScript_OpenOHKORoomDoors
	return

GiantsReach_Gym_OnTransition:
	call_if_eq VAR_GIANTS_REACH_GYM_STATE, 1, GiantsReach_Gym_EventScript_MoveMatthewToEntrance
	call_if_lt VAR_GIANTS_REACH_GYM_STATE, 6, GiantsReach_Gym_EventScript_MoveNormanToEntrance
	call_if_set FLAG_SYS_GAME_CLEAR, GiantsReach_Gym_EventScript_CheckNormanForRematch
	end

GiantsReach_Gym_EventScript_MoveMatthewToEntrance::
	setobjectxyperm LOCALID_GIANTSREACH_GYM_MATTHEW, 5, 108
	return

GiantsReach_Gym_EventScript_MoveNormanToEntrance::
	setobjectxyperm LOCALID_GIANTSREACH_GYM_NORMAN, 4, 107
	return

GiantsReach_Gym_EventScript_CheckNormanForRematch::
	setorcopyvar VAR_TRAINER_BATTLE_OPPONENT_A, TRAINER_NORMAN_1
	specialvar VAR_RESULT, IsTrainerReadyForRematch
	goto_if_eq VAR_RESULT, TRUE, GiantsReach_Gym_EventScript_DontMoveNormanToFront
	goto_if_eq VAR_GIANTS_REACH_GYM_STATE, 8, GiantsReach_Gym_EventScript_DontMoveNormanToFront
	setobjectxyperm LOCALID_GIANTSREACH_GYM_NORMAN, 4, 107
	return

GiantsReach_Gym_EventScript_DontMoveNormanToFront::
	setvar VAR_GIANTS_REACH_GYM_STATE, 8
	end

GiantsReach_Gym_OnWarp:
	map_script_2 VAR_GIANTS_REACH_GYM_STATE, 1, GiantsReach_Gym_EventScript_TurnPlayerNorth
	.2byte 0

GiantsReach_Gym_EventScript_TurnPlayerNorth::
	turnobject LOCALID_PLAYER, DIR_NORTH
	end

GiantsReach_Gym_OnFrame:
	map_script_2 VAR_GIANTS_REACH_GYM_STATE, 1, GiantsReach_Gym_EventScript_ReturnFromMatthewTutorial
	.2byte 0

GiantsReach_Gym_EventScript_ReturnFromMatthewTutorial::
	lockall
	msgbox GiantsReach_Gym_Text_DadSoDidItWorkOut, MSGBOX_DEFAULT
	msgbox GiantsReach_Gym_Text_MatthewThankYouBye, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_PLAYER, Common_Movement_WalkInPlaceFasterDown
	applymovement LOCALID_GIANTSREACH_GYM_MATTHEW, GiantsReach_Gym_Movement_MatthewExitGym
	waitmovement 0
	playse SE_EXIT
	removeobject LOCALID_GIANTSREACH_GYM_MATTHEW
	setflag FLAG_HIDE_GIANTS_REACH_MATTHEW
	delay 30
	applymovement LOCALID_PLAYER, Common_Movement_WalkInPlaceFasterUp
	waitmovement 0
	msgbox GiantsReach_Gym_Text_DadGoCollectBadges, MSGBOX_DEFAULT
	setvar VAR_GIANTS_REACH_GYM_STATE, 2
	releaseall
	end

GiantsReach_Gym_Movement_MatthewExitGym:
	walk_down
	walk_down
	walk_down
	delay_16
	step_end

GiantsReach_Gym_EventScript_Norman::
	lock
	faceplayer
	switch VAR_GIANTS_REACH_GYM_STATE
	case 2, GiantsReach_Gym_EventScript_NormanNoBadges
	case 3, GiantsReach_Gym_EventScript_NormanOneBadge
	case 4, GiantsReach_Gym_EventScript_NormanTwoBadges
	case 5, GiantsReach_Gym_EventScript_NormanThreeBadges
	case 6, GiantsReach_Gym_EventScript_NormanBattle
	case 7, GiantsReach_Gym_EventScript_NormanPostBattle
	case 8, GiantsReach_Gym_EventScript_NormanRematch
	msgbox GiantsReach_Gym_Text_DadYoureHereWithYourPokemon, MSGBOX_DEFAULT
	closemessage
	switch VAR_FACING
	case DIR_SOUTH, GiantsReach_Gym_EventScript_BeginMatthewTutorialSouth
	case DIR_NORTH, GiantsReach_Gym_EventScript_BeginMatthewTutorialNorth
	case DIR_WEST, GiantsReach_Gym_EventScript_BeginMatthewTutorialWest
	case DIR_EAST, GiantsReach_Gym_EventScript_BeginMatthewTutorialEast
	end

GiantsReach_Gym_EventScript_BeginMatthewTutorialSouth::
	setvar VAR_0x8008, 0
	goto GiantsReach_Gym_EventScript_BeginMatthewTutorial
	end

GiantsReach_Gym_EventScript_BeginMatthewTutorialNorth::
	setvar VAR_0x8008, 1
	goto GiantsReach_Gym_EventScript_BeginMatthewTutorial
	end

GiantsReach_Gym_EventScript_BeginMatthewTutorialWest::
	setvar VAR_0x8008, 2
	goto GiantsReach_Gym_EventScript_BeginMatthewTutorial
	end

GiantsReach_Gym_EventScript_BeginMatthewTutorialEast::
	setvar VAR_0x8008, 3
	goto GiantsReach_Gym_EventScript_BeginMatthewTutorial
	end

GiantsReach_Gym_EventScript_BeginMatthewTutorial::
	addobject LOCALID_GIANTSREACH_GYM_MATTHEW
	playse SE_DOOR
	call_if_eq VAR_0x8008, 0, GiantsReach_Gym_EventScript_MatthewArriveSouth
	call_if_eq VAR_0x8008, 1, GiantsReach_Gym_EventScript_MatthewArriveNorth
	call_if_eq VAR_0x8008, 2, GiantsReach_Gym_EventScript_MatthewArriveWestEast
	call_if_eq VAR_0x8008, 3, GiantsReach_Gym_EventScript_MatthewArriveWestEast
	msgbox GiantsReach_Gym_Text_MatthewIdLikeAPokemon, MSGBOX_DEFAULT
	msgbox GiantsReach_Gym_Text_DadOhYoureMatthewRight, MSGBOX_DEFAULT
	msgbox GiantsReach_Gym_Text_MatthewIveNeverCaughtAPokemon, MSGBOX_DEFAULT
	msgbox GiantsReach_Gym_Text_DadHmISee, MSGBOX_DEFAULT
	call_if_eq VAR_0x8008, 0, GiantsReach_Gym_EventScript_NormanAddressPlayerSouth
	call_if_eq VAR_0x8008, 1, GiantsReach_Gym_EventScript_NormanAddressPlayerNorth
	call_if_eq VAR_0x8008, 2, GiantsReach_Gym_EventScript_NormanAddressPlayerWest
	call_if_eq VAR_0x8008, 3, GiantsReach_Gym_EventScript_NormanAddressPlayerEast
	msgbox GiantsReach_Gym_Text_DadPlayerGoWithMatthew, MSGBOX_DEFAULT
	call_if_eq VAR_0x8008, 0, GiantsReach_Gym_EventScript_NormanAddressMatthewSouth
	call_if_eq VAR_0x8008, 1, GiantsReach_Gym_EventScript_NormanAddressMatthewNorth
	call_if_eq VAR_0x8008, 2, GiantsReach_Gym_EventScript_NormanAddressMatthewWest
	call_if_eq VAR_0x8008, 3, GiantsReach_Gym_EventScript_NormanAddressMatthewEast
	msgbox GiantsReach_Gym_Text_IllLoanYouMyZigzagoon, MSGBOX_DEFAULT
	msgbox GiantsReach_Gym_Text_MatthewThankYouAndDadGivesPokeBall, MSGBOX_DEFAULT
	msgbox GiantsReach_Gym_Text_MatthewOhWowThankYou, MSGBOX_DEFAULT
	call_if_eq VAR_0x8008, 0, GiantsReach_Gym_EventScript_NormanFaceDoorSouth
	call_if_eq VAR_0x8008, 1, GiantsReach_Gym_EventScript_NormanFaceDoorNorth
	call_if_eq VAR_0x8008, 2, GiantsReach_Gym_EventScript_NormanFaceDoorWest
	call_if_eq VAR_0x8008, 3, GiantsReach_Gym_EventScript_NormanFaceDoorEast
	call_if_eq VAR_0x8008, 0, GiantsReach_Gym_EventScript_MatthewFacePlayer
	call_if_eq VAR_0x8008, 1, GiantsReach_Gym_EventScript_MatthewFaceDown
	call_if_eq VAR_0x8008, 2, GiantsReach_Gym_EventScript_MatthewFacePlayer
	call_if_eq VAR_0x8008, 3, GiantsReach_Gym_EventScript_MatthewFacePlayer
	msgbox GiantsReach_Gym_Text_WouldYouReallyComeWithMe, MSGBOX_DEFAULT
	closemessage
	setflag FLAG_DONT_TRANSITION_MUSIC
	playbgm MUS_FOLLOW_ME, FALSE
	call_if_eq VAR_0x8008, 0, GiantsReach_Gym_EventScript_ExitGymWithMatthewSouth
	call_if_eq VAR_0x8008, 1, GiantsReach_Gym_EventScript_ExitGymWithMatthewNorth
	call_if_eq VAR_0x8008, 2, GiantsReach_Gym_EventScript_ExitGymWithMatthewWest
	call_if_eq VAR_0x8008, 3, GiantsReach_Gym_EventScript_ExitGymWithMatthewEast
	removeobject LOCALID_GIANTSREACH_GYM_MATTHEW
	setflag FLAG_HIDE_GIANTS_REACH_MATTHEWS_MOM
	setvar VAR_GIANTS_REACH_GYM_STATE, 1
	setvar VAR_GIANTS_REACH_CITY_STATE, 2
	clearflag FLAG_HIDE_GIANTS_REACH_MATTHEW
	clearflag FLAG_HIDE_GIANTSREACH_GYM_MATTHEW
	setflag FLAG_HIDE_TRASHBURG_FRANKS_LAB_RIVAL
	special InitFrankState
	warp MAP_GIANTS_REACH, 39, 29
	waitstate
	release
	end

GiantsReach_Gym_EventScript_MatthewArriveSouth::
	applymovement LOCALID_GIANTSREACH_GYM_NORMAN, Common_Movement_WalkInPlaceFasterDown
	applymovement LOCALID_GIANTSREACH_GYM_MATTHEW, GiantsReach_Gym_Movement_MatthewArrive
	waitmovement 0
	return

GiantsReach_Gym_EventScript_MatthewArriveNorth::
	applymovement LOCALID_GIANTSREACH_GYM_MATTHEW, GiantsReach_Gym_Movement_MatthewArriveNorth
	waitmovement 0
	applymovement LOCALID_GIANTSREACH_GYM_NORMAN, Common_Movement_WalkInPlaceFasterRight
	applymovement LOCALID_PLAYER, Common_Movement_WalkInPlaceFasterRight
	waitmovement 0
	return

GiantsReach_Gym_EventScript_MatthewArriveWestEast::
	applymovement LOCALID_GIANTSREACH_GYM_NORMAN, Common_Movement_WalkInPlaceFasterDown
	applymovement LOCALID_PLAYER, Common_Movement_WalkInPlaceFasterDown
	applymovement LOCALID_GIANTSREACH_GYM_MATTHEW, GiantsReach_Gym_Movement_MatthewArrive
	waitmovement 0
	return

GiantsReach_Gym_EventScript_ExitGymWithMatthewSouth::
	applymovement LOCALID_GIANTSREACH_GYM_NORMAN, Common_Movement_WalkInPlaceFasterDown
	applymovement LOCALID_GIANTSREACH_GYM_MATTHEW, GiantsReach_Gym_Movement_MatthewExitSouthWest
	applymovement LOCALID_PLAYER, GiantsReach_Gym_Movement_PlayerExitWithMatthewSouth
	waitmovement 0
	return

GiantsReach_Gym_EventScript_ExitGymWithMatthewNorth::
	applymovement LOCALID_GIANTSREACH_GYM_MATTHEW, GiantsReach_Gym_Movement_MatthewExitNorth
	applymovement LOCALID_PLAYER, GiantsReach_Gym_Movement_PlayerExitWithMatthewNorth
	waitmovement 0
	return

GiantsReach_Gym_EventScript_ExitGymWithMatthewWest::
	applymovement LOCALID_GIANTSREACH_GYM_MATTHEW, GiantsReach_Gym_Movement_MatthewExitSouthWest
	applymovement LOCALID_PLAYER, GiantsReach_Gym_Movement_PlayerExitWithMatthewWest
	waitmovement 0
	return

GiantsReach_Gym_EventScript_ExitGymWithMatthewEast::
	applymovement LOCALID_GIANTSREACH_GYM_MATTHEW, GiantsReach_Gym_Movement_MatthewExitEast
	applymovement LOCALID_PLAYER, GiantsReach_Gym_Movement_PlayerExitWithMatthewEast
	waitmovement 0
	return

GiantsReach_Gym_EventScript_NormanAddressPlayerSouth::
	applymovement LOCALID_GIANTSREACH_GYM_NORMAN, Common_Movement_WalkInPlaceFasterUp
	waitmovement 0
	return

GiantsReach_Gym_EventScript_NormanAddressPlayerNorth::
	applymovement LOCALID_GIANTSREACH_GYM_NORMAN, Common_Movement_WalkInPlaceFasterDown
	applymovement LOCALID_PLAYER, Common_Movement_WalkInPlaceFasterUp
	waitmovement 0
	return

GiantsReach_Gym_EventScript_NormanAddressPlayerWest::
	applymovement LOCALID_GIANTSREACH_GYM_NORMAN, Common_Movement_WalkInPlaceFasterRight
	applymovement LOCALID_PLAYER, Common_Movement_WalkInPlaceFasterLeft
	waitmovement 0
	return

GiantsReach_Gym_EventScript_NormanAddressPlayerEast::
	applymovement LOCALID_GIANTSREACH_GYM_NORMAN, Common_Movement_WalkInPlaceFasterLeft
	applymovement LOCALID_PLAYER, Common_Movement_WalkInPlaceFasterRight
	waitmovement 0
	return

GiantsReach_Gym_EventScript_NormanAddressMatthewSouth::
	applymovement LOCALID_GIANTSREACH_GYM_NORMAN, Common_Movement_WalkInPlaceFasterDown
	waitmovement 0
	return

GiantsReach_Gym_EventScript_NormanAddressMatthewNorth::
	applymovement LOCALID_GIANTSREACH_GYM_NORMAN, Common_Movement_WalkInPlaceFasterRight
	waitmovement 0
	return

GiantsReach_Gym_EventScript_NormanAddressMatthewWest::
	applymovement LOCALID_GIANTSREACH_GYM_NORMAN, Common_Movement_WalkInPlaceFasterDown
	waitmovement 0
	return

GiantsReach_Gym_EventScript_NormanAddressMatthewEast::
	applymovement LOCALID_GIANTSREACH_GYM_NORMAN, Common_Movement_WalkInPlaceFasterDown
	waitmovement 0
	return

GiantsReach_Gym_EventScript_MatthewFacePlayer::
	applymovement LOCALID_GIANTSREACH_GYM_MATTHEW, Common_Movement_FacePlayer
	waitmovement 0
	return

GiantsReach_Gym_EventScript_MatthewFaceDown::
	applymovement LOCALID_GIANTSREACH_GYM_MATTHEW, Common_Movement_WalkInPlaceFasterDown
	waitmovement 0
	return

GiantsReach_Gym_EventScript_NormanNoBadges::
	msgbox GiantsReach_Gym_Text_NormanGoToRustboro, MSGBOX_DEFAULT
	release
	end

GiantsReach_Gym_EventScript_NormanOneBadge::
	msgbox GiantsReach_Gym_Text_NormanGoToDewford, MSGBOX_DEFAULT
	release
	end

GiantsReach_Gym_EventScript_NormanTwoBadges::
	msgbox GiantsReach_Gym_Text_YouHaveGottenStronger, MSGBOX_DEFAULT
	release
	end

GiantsReach_Gym_EventScript_NormanThreeBadges::
	msgbox GiantsReach_Gym_Text_YouHaveGottenStronger, MSGBOX_DEFAULT
	release
	end

GiantsReach_Gym_EventScript_NormanFaceDoorSouth::
	return

@ For all other NormanFaceDoorX, Norman is already facing the door from NormanAddressMatthewX
GiantsReach_Gym_EventScript_NormanFaceDoorNorth::
	applymovement LOCALID_GIANTSREACH_GYM_NORMAN, Common_Movement_WalkInPlaceFasterDown
	waitmovement 0
	return

GiantsReach_Gym_EventScript_NormanFaceDoorWest::
	return

GiantsReach_Gym_EventScript_NormanFaceDoorEast::
	return

GiantsReach_Gym_EventScript_NormanPostBattle::
	call GiantsReach_Gym_EventScript_ShouldGiveEnigmaBerry
	goto_if_eq VAR_RESULT, TRUE, GiantsReach_Gym_EventScript_GiveEnigmaBerry
	goto_if_unset FLAG_RECEIVED_TM_FACADE, GiantsReach_Gym_EventScript_GiveFacade2
	goto_if_set FLAG_SYS_GAME_CLEAR, GiantsReach_Gym_EventScript_NoAmountOfTrainingIsEnough
	msgbox GiantsReach_Gym_Text_DadGoingToKeepTraining, MSGBOX_DEFAULT
	release
	end

GiantsReach_Gym_EventScript_GiveFacade2::
	call GiantsReach_Gym_EventScript_GiveFacade
	release
	end

GiantsReach_Gym_EventScript_NormanRematch::
	trainerbattle_rematch_double TRAINER_NORMAN_1, GiantsReach_Gym_Text_NormanPreRematch, GiantsReach_Gym_Text_NormanRematchDefeat, GiantsReach_Gym_Text_NormanRematchNeedTwoMons
	msgbox GiantsReach_Gym_Text_NormanPostRematch, MSGBOX_AUTOCLOSE
	end

GiantsReach_Gym_EventScript_ShouldGiveEnigmaBerry::
	specialvar VAR_RESULT, IsEnigmaBerryValid
	goto_if_eq VAR_RESULT, FALSE, GiantsReach_Gym_EventScript_DontGiveEnigmaBerry
	checkitem ITEM_ENIGMA_BERRY_E_READER
	goto_if_eq VAR_RESULT, TRUE, GiantsReach_Gym_EventScript_DontGiveEnigmaBerry
	checkpcitem ITEM_ENIGMA_BERRY_E_READER
	goto_if_eq VAR_RESULT, TRUE, GiantsReach_Gym_EventScript_DontGiveEnigmaBerry
	goto_if_eq VAR_ENIGMA_BERRY_AVAILABLE, 0, GiantsReach_Gym_EventScript_DontGiveEnigmaBerry
	msgbox GiantsReach_Gym_Text_GiveEnigmaBerry, MSGBOX_DEFAULT
	setvar VAR_RESULT, TRUE
	return

GiantsReach_Gym_EventScript_DontGiveEnigmaBerry::
	setvar VAR_RESULT, FALSE
	return

GiantsReach_Gym_EventScript_GiveEnigmaBerry::
	giveitem ITEM_ENIGMA_BERRY_E_READER
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_ShowBagIsFull
	setvar VAR_ENIGMA_BERRY_AVAILABLE, 0
	release
	end

GiantsReach_Gym_EventScript_NormanBattle::
	msgbox GiantsReach_Gym_Text_NormanIntro, MSGBOX_DEFAULT
	trainerbattle_no_intro TRAINER_NORMAN_1, GiantsReach_Gym_Text_NormanDefeat
	message GiantsReach_Gym_Text_ReceivedBalanceBadge
	waitmessage
	call Common_EventScript_PlayGymBadgeFanfare
	msgbox GiantsReach_Gym_Text_ExplainBalanceBadgeTakeThis, MSGBOX_DEFAULT
	setflag FLAG_DEFEATED_GIANTSREACH_GYM
	setvar VAR_GIANTS_REACH_GYM_STATE, 7
	setflag FLAG_BADGE05_GET
	special ResetHealLocationFromDewford
	call EventScript_HideMrBriney
	setflag FLAG_HIDE_MAUVILLE_GYM_WATTSON
	clearflag FLAG_HIDE_MAUVILLE_CITY_WATTSON
	setvar VAR_0x8008, 5
	call Common_EventScript_SetGymTrainers
	clearflag FLAG_HIDE_DEWFORD_HALL_SLUDGE_BOMB_MAN
	call GiantsReach_Gym_EventScript_UnlockAllDoors
	special DrawWholeMapView
	call GiantsReach_Gym_EventScript_GiveFacade
	delay 30
	msgbox GiantsReach_Gym_Text_DadHappyAndSad, MSGBOX_DEFAULT
	closemessage
	delay 40
	playse SE_DOOR
	delay 10
	addobject LOCALID_GIANTSREACH_GYM_MATTHEWS_DAD
	switch VAR_FACING
	case DIR_NORTH, GiantsReach_Gym_EventScript_MatthewsDadArrivesNorth
	case DIR_WEST, GiantsReach_Gym_EventScript_MatthewsDadArrivesWest
	case DIR_EAST, GiantsReach_Gym_EventScript_MatthewsDadArrivesEast
	end

GiantsReach_Gym_EventScript_GiveFacade::
	giveitem ITEM_TM_FACADE
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_BagIsFull
	setflag FLAG_RECEIVED_TM_FACADE
	msgbox GiantsReach_Gym_Text_ExplainFacade, MSGBOX_DEFAULT
	return

GiantsReach_Gym_EventScript_MatthewsDadArrivesNorth::
	setvar VAR_0x8008, 1
	goto GiantsReach_Gym_EventScript_MatthewsDadArrives

GiantsReach_Gym_EventScript_MatthewsDadArrivesEast::
	setvar VAR_0x8008, 2
	goto GiantsReach_Gym_EventScript_MatthewsDadArrives

GiantsReach_Gym_EventScript_MatthewsDadArrivesWest::
	setvar VAR_0x8008, 3
	goto GiantsReach_Gym_EventScript_MatthewsDadArrives

GiantsReach_Gym_EventScript_MatthewsDadArrives::
	applymovement LOCALID_GIANTSREACH_GYM_MATTHEWS_DAD, GiantsReach_Gym_Movement_MatthewsDadEnterGym
	waitmovement 0
	playse SE_PIN
	applymovement LOCALID_GIANTSREACH_GYM_MATTHEWS_DAD, Common_Movement_ExclamationMark
	waitmovement 0
	applymovement LOCALID_GIANTSREACH_GYM_MATTHEWS_DAD, Common_Movement_Delay48
	waitmovement 0
	delay 10
	call_if_eq VAR_0x8008, 1, GiantsReach_Gym_EventScript_MatthewsDadApproachPlayerNorth
	call_if_eq VAR_0x8008, 2, GiantsReach_Gym_EventScript_MatthewsDadApproachPlayerEast
	call_if_eq VAR_0x8008, 3, GiantsReach_Gym_EventScript_MatthewsDadApproachPlayerWest
	msgbox GiantsReach_Gym_Text_PleaseComeWithMe, MSGBOX_DEFAULT
	closemessage
	delay 20
	call_if_eq VAR_0x8008, 1, GiantsReach_Gym_EventScript_MatthewsDadFaceNormanNorth
	call_if_eq VAR_0x8008, 2, GiantsReach_Gym_EventScript_MatthewsDadFaceNormanEast
	call_if_eq VAR_0x8008, 3, GiantsReach_Gym_EventScript_MatthewsDadFaceNormanWest
	msgbox GiantsReach_Gym_Text_LetMeBorrowPlayer, MSGBOX_DEFAULT
	closemessage
	setflag FLAG_DONT_TRANSITION_MUSIC
	playbgm MUS_FOLLOW_ME, FALSE
	call_if_eq VAR_0x8008, 1, GiantsReach_Gym_EventScript_ExitGymWithMatthewsDadNorth
	call_if_eq VAR_0x8008, 2, GiantsReach_Gym_EventScript_ExitGymWithMatthewsDadEast
	call_if_eq VAR_0x8008, 3, GiantsReach_Gym_EventScript_ExitGymWithMatthewsDadWest
	removeobject LOCALID_GIANTSREACH_GYM_MATTHEWS_DAD
	setvar VAR_GIANTS_REACH_CITY_STATE, 4
	clearflag FLAG_HIDE_GIANTS_REACH_MATTHEWS_DAD
	warp MAP_GIANTS_REACH, 39, 32
	waitstate
	release
	end

GiantsReach_Gym_EventScript_MatthewsDadFaceNormanNorth::
	applymovement LOCALID_GIANTSREACH_GYM_MATTHEWS_DAD, Common_Movement_WalkInPlaceFasterUp
	waitmovement 0
	return

GiantsReach_Gym_EventScript_MatthewsDadFaceNormanEast::
	applymovement LOCALID_GIANTSREACH_GYM_MATTHEWS_DAD, Common_Movement_WalkInPlaceFasterRight
	waitmovement 0
	return

GiantsReach_Gym_EventScript_MatthewsDadFaceNormanWest::
	applymovement LOCALID_GIANTSREACH_GYM_MATTHEWS_DAD, Common_Movement_WalkInPlaceFasterLeft
	waitmovement 0
	return

GiantsReach_Gym_EventScript_MatthewsDadApproachPlayerNorth::
	applymovement LOCALID_GIANTSREACH_GYM_MATTHEWS_DAD, GiantsReach_Gym_Movement_MatthewsDadApproachPlayerNorth
	waitmovement 0
	applymovement LOCALID_PLAYER, Common_Movement_WalkInPlaceFasterLeft
	applymovement LOCALID_GIANTSREACH_GYM_NORMAN, Common_Movement_WalkInPlaceFasterLeft
	waitmovement 0
	return

GiantsReach_Gym_EventScript_MatthewsDadApproachPlayerEast::
	applymovement LOCALID_GIANTSREACH_GYM_MATTHEWS_DAD, GiantsReach_Gym_Movement_MatthewsDadApproachPlayerEast
	waitmovement 0
	applymovement LOCALID_PLAYER, Common_Movement_WalkInPlaceFasterDown
	applymovement LOCALID_GIANTSREACH_GYM_NORMAN, Common_Movement_WalkInPlaceFasterDown
	waitmovement 0
	return

GiantsReach_Gym_EventScript_MatthewsDadApproachPlayerWest::
	applymovement LOCALID_GIANTSREACH_GYM_MATTHEWS_DAD, GiantsReach_Gym_Movement_MatthewsDadApproachPlayerWest
	waitmovement 0
	applymovement LOCALID_PLAYER, Common_Movement_WalkInPlaceFasterDown
	applymovement LOCALID_GIANTSREACH_GYM_NORMAN, Common_Movement_WalkInPlaceFasterDown
	waitmovement 0
	return

GiantsReach_Gym_EventScript_ExitGymWithMatthewsDadNorth::
	applymovement LOCALID_GIANTSREACH_GYM_MATTHEWS_DAD, GiantsReach_Gym_Movement_MatthewsDadExitNorth
	applymovement LOCALID_GIANTSREACH_GYM_NORMAN, Common_Movement_WalkInPlaceFasterDown
	applymovement LOCALID_PLAYER, GiantsReach_Gym_Movement_PlayerExitWithMatthewsDadNorth
	waitmovement 0
	return

GiantsReach_Gym_EventScript_ExitGymWithMatthewsDadEast::
	applymovement LOCALID_GIANTSREACH_GYM_MATTHEWS_DAD, GiantsReach_Gym_Movement_MatthewsDadExitEast
	applymovement LOCALID_PLAYER, GiantsReach_Gym_Movement_PlayerExitWithMatthewsDadEast
	waitmovement 0
	return

GiantsReach_Gym_EventScript_ExitGymWithMatthewsDadWest::
	applymovement LOCALID_GIANTSREACH_GYM_MATTHEWS_DAD, GiantsReach_Gym_Movement_MatthewsDadExitWest
	applymovement LOCALID_PLAYER, GiantsReach_Gym_Movement_PlayerExitWithMatthewsDadWest
	waitmovement 0
	return

GiantsReach_Gym_Movement_MatthewsDadExitNorth:
	walk_down
	walk_down
	walk_left
	walk_left
	walk_down
	walk_down
	walk_in_place_faster_up
	delay_8
	walk_in_place_down
	set_invisible
	step_end

GiantsReach_Gym_Movement_MatthewsDadExitEast:
	walk_down
	walk_down
	walk_left
	walk_left
	walk_down
	walk_down
	walk_in_place_faster_up
	delay_8
	walk_in_place_down
	set_invisible
	step_end

GiantsReach_Gym_Movement_MatthewsDadExitWest:
	walk_down
	walk_down
	walk_left
	walk_left
	walk_left
	walk_left
	walk_down
	walk_down
	walk_in_place_faster_up
	delay_8
	walk_in_place_down
	set_invisible
	step_end

GiantsReach_Gym_Movement_PlayerExitWithMatthewsDadNorth:
	delay_16
	walk_down
	walk_down
	walk_left
	walk_left
	walk_down
	walk_down
	step_end

GiantsReach_Gym_Movement_PlayerExitWithMatthewsDadEast:
	delay_16
	walk_down
	walk_down
	walk_left
	walk_down
	walk_down
	walk_down
	step_end

GiantsReach_Gym_Movement_PlayerExitWithMatthewsDadWest:
	delay_16
	walk_down
	walk_down
	walk_down
	walk_left
	walk_left
	walk_left
	walk_down
	walk_down
	step_end

GiantsReach_Gym_Movement_MatthewsDadEnterGym:
	walk_up
	delay_8
	walk_in_place_faster_right
	delay_8
	walk_in_place_faster_left
	delay_16
	walk_in_place_faster_up
	step_end

GiantsReach_Gym_Movement_MatthewsDadApproachPlayerNorth:
	walk_right
	walk_right
	walk_up
	walk_up
	walk_up
	walk_in_place_faster_right
	step_end

GiantsReach_Gym_Movement_MatthewsDadApproachPlayerEast:
	walk_right
	walk_right
	walk_up
	walk_up
	walk_up
	step_end

GiantsReach_Gym_Movement_MatthewsDadApproachPlayerWest:
	walk_right
	walk_right
	walk_up
	walk_up
	walk_right
	walk_right
	walk_up
	step_end

GiantsReach_Gym_Movement_Unused:
	walk_in_place_faster_up
	delay_16
	delay_16
	delay_16
	delay_16
	delay_16
	delay_8
	walk_in_place_faster_down
	step_end

GiantsReach_Gym_Movement_MatthewArriveNorth:
	delay_16
	walk_up
	delay_16
	delay_8
	walk_up
	walk_right
	walk_up
	walk_up
	walk_in_place_faster_left
	step_end

GiantsReach_Gym_Movement_MatthewArrive:
	delay_16
	walk_up
	delay_16
	delay_8
	walk_up
	walk_up
	step_end

GiantsReach_Gym_Movement_MatthewExitNorth:
	walk_down
	walk_down
	walk_down
	walk_down
	walk_in_place_faster_up
	delay_16
	walk_in_place_down
	step_end

GiantsReach_Gym_Movement_MatthewExitEast:
	walk_down
	walk_down
	walk_right
	walk_down
	walk_in_place_faster_up
	delay_16
	walk_in_place_down
	step_end

GiantsReach_Gym_Movement_MatthewExitSouthWest:
	walk_down
	walk_down
	walk_down
	walk_in_place_faster_up
	delay_16
	walk_in_place_down
	step_end

GiantsReach_Gym_Movement_PlayerExitWithMatthewNorth:
	delay_16
	delay_16
	delay_16
	walk_down
	walk_down
	walk_down
	delay_8
	step_end

GiantsReach_Gym_Movement_PlayerExitWithMatthewSouth:
	delay_16
	delay_16
	walk_right
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	delay_8
	step_end

GiantsReach_Gym_Movement_PlayerExitWithMatthewWest:
	delay_16
	delay_16
	walk_down
	walk_down
	walk_down
	walk_down
	delay_8
	step_end

GiantsReach_Gym_Movement_PlayerExitWithMatthewEast:
	walk_in_place_faster_down
	delay_16
	delay_16
	walk_down
	walk_down
	walk_down
	walk_right
	walk_down
	delay_8
	step_end

GiantsReach_Gym_EventScript_NoAmountOfTrainingIsEnough::
	msgbox GiantsReach_Gym_Text_DadNoAmountOfTrainingIsEnough, MSGBOX_DEFAULT
	release
	end

GiantsReach_Gym_EventScript_SpeedRoomDoor::
	lockall
	goto_if_lt VAR_GIANTS_REACH_GYM_STATE, 6, GiantsReach_Gym_EventScript_DoorLocked
	setvar VAR_0x8008, 7
	setvar VAR_0x8009, 85
	msgbox GiantsReach_Gym_Text_EnterSpeedRoom, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, GiantsReach_Gym_EventScript_EnterRoom
	goto_if_eq VAR_RESULT, NO, GiantsReach_Gym_EventScript_DontEnterRoom
	end

GiantsReach_Gym_EventScript_EnterRoom::
	closemessage
	delay 30
	warpdoor MAP_GIANTS_REACH_GYM, VAR_0x8008, VAR_0x8009
	waitstate
	releaseall
	end

GiantsReach_Gym_EventScript_DontEnterRoom::
	releaseall
	end

GiantsReach_Gym_EventScript_DoorLocked::
	msgbox GiantsReach_Gym_Text_DoorAppearsLocked, MSGBOX_DEFAULT
	releaseall
	end

@ VAR_0x8008 and VAR_0x8009 below are the x and y coordinates of the warp
GiantsReach_Gym_EventScript_AccuracyRoomDoor::
	lockall
	goto_if_lt VAR_GIANTS_REACH_GYM_STATE, 6, GiantsReach_Gym_EventScript_DoorLocked
	setvar VAR_0x8008, 1
	setvar VAR_0x8009, 98
	msgbox GiantsReach_Gym_Text_EnterAccuracyRoom, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, GiantsReach_Gym_EventScript_EnterRoom
	goto_if_eq VAR_RESULT, NO, GiantsReach_Gym_EventScript_DontEnterRoom
	end

GiantsReach_Gym_EventScript_ConfusionRoomDoor::
	lockall
	goto_if_not_defeated TRAINER_RANDALL, GiantsReach_Gym_EventScript_DoorLocked
	setvar VAR_0x8008, 7
	setvar VAR_0x8009, 46
	msgbox GiantsReach_Gym_Text_EnterConfusionRoom, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, GiantsReach_Gym_EventScript_EnterRoom
	goto_if_eq VAR_RESULT, NO, GiantsReach_Gym_EventScript_DontEnterRoom
	end

GiantsReach_Gym_EventScript_LeftDefenseRoomDoor::
	lockall
	goto_if_not_defeated TRAINER_RANDALL, GiantsReach_Gym_EventScript_DoorLocked
	setvar VAR_0x8008, 1
	setvar VAR_0x8009, 59
	msgbox GiantsReach_Gym_Text_EnterDefenseRoom, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, GiantsReach_Gym_EventScript_EnterRoom
	goto_if_eq VAR_RESULT, NO, GiantsReach_Gym_EventScript_DontEnterRoom
	end

GiantsReach_Gym_EventScript_RightDefenseRoomDoor::
	lockall
	goto_if_not_defeated TRAINER_MARY, GiantsReach_Gym_EventScript_DoorLocked
	setvar VAR_0x8008, 7
	setvar VAR_0x8009, 59
	msgbox GiantsReach_Gym_Text_EnterDefenseRoom, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, GiantsReach_Gym_EventScript_EnterRoom
	goto_if_eq VAR_RESULT, NO, GiantsReach_Gym_EventScript_DontEnterRoom
	end

GiantsReach_Gym_EventScript_RecoveryRoomDoor::
	lockall
	goto_if_not_defeated TRAINER_MARY, GiantsReach_Gym_EventScript_DoorLocked
	setvar VAR_0x8008, 1
	setvar VAR_0x8009, 72
	msgbox GiantsReach_Gym_Text_EnterRecoveryRoom, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, GiantsReach_Gym_EventScript_EnterRoom
	goto_if_eq VAR_RESULT, NO, GiantsReach_Gym_EventScript_DontEnterRoom
	end

GiantsReach_Gym_EventScript_LeftStrengthRoomDoor::
	lockall
	goto_if_not_defeated TRAINER_PARKER, GiantsReach_Gym_EventScript_DoorLocked
	setvar VAR_0x8008, 1
	setvar VAR_0x8009, 20
	msgbox GiantsReach_Gym_Text_EnterStrengthRoom, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, GiantsReach_Gym_EventScript_EnterRoom
	goto_if_eq VAR_RESULT, NO, GiantsReach_Gym_EventScript_DontEnterRoom
	end

GiantsReach_Gym_EventScript_RightStrengthRoomDoor::
	lockall
	goto_if_not_defeated TRAINER_ALEXIA, GiantsReach_Gym_EventScript_DoorLocked
	setvar VAR_0x8008, 7
	setvar VAR_0x8009, 20
	msgbox GiantsReach_Gym_Text_EnterStrengthRoom, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, GiantsReach_Gym_EventScript_EnterRoom
	goto_if_eq VAR_RESULT, NO, GiantsReach_Gym_EventScript_DontEnterRoom
	end

GiantsReach_Gym_EventScript_LeftOHKORoomDoor::
	lockall
	goto_if_not_defeated TRAINER_ALEXIA, GiantsReach_Gym_EventScript_DoorLocked
	setvar VAR_0x8008, 1
	setvar VAR_0x8009, 33
	msgbox GiantsReach_Gym_Text_EnterOHKORoom, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, GiantsReach_Gym_EventScript_EnterRoom
	goto_if_eq VAR_RESULT, NO, GiantsReach_Gym_EventScript_DontEnterRoom
	end

GiantsReach_Gym_EventScript_RightOHKORoomDoor::
	lockall
	goto_if_not_defeated TRAINER_GEORGE, GiantsReach_Gym_EventScript_DoorLocked
	setvar VAR_0x8008, 7
	setvar VAR_0x8009, 33
	msgbox GiantsReach_Gym_Text_EnterOHKORoom, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, GiantsReach_Gym_EventScript_EnterRoom
	goto_if_eq VAR_RESULT, NO, GiantsReach_Gym_EventScript_DontEnterRoom
	end

GiantsReach_Gym_EventScript_LeftGymLeadersRoomDoor::
	lockall
	goto_if_not_defeated TRAINER_JODY, GiantsReach_Gym_EventScript_DoorLocked
	setvar VAR_0x8008, 1
	setvar VAR_0x8009, 7
	msgbox GiantsReach_Gym_Text_EnterGymLeadersRoom, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, GiantsReach_Gym_EventScript_EnterRoom
	goto_if_eq VAR_RESULT, NO, GiantsReach_Gym_EventScript_DontEnterRoom
	end

GiantsReach_Gym_EventScript_RightGymLeadersRoomDoor::
	lockall
	goto_if_not_defeated TRAINER_BERKE, GiantsReach_Gym_EventScript_DoorLocked
	setvar VAR_0x8008, 7
	setvar VAR_0x8009, 7
	msgbox GiantsReach_Gym_Text_EnterGymLeadersRoom, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, GiantsReach_Gym_EventScript_EnterRoom
	goto_if_eq VAR_RESULT, NO, GiantsReach_Gym_EventScript_DontEnterRoom
	end

GiantsReach_Gym_EventScript_Randall::
	trainerbattle_single TRAINER_RANDALL, GiantsReach_Gym_Text_RandallIntro, GiantsReach_Gym_Text_RandallDefeat, GiantsReach_Gym_EventScript_SlideOpenSpeedRoomDoors
	goto_if_set FLAG_DEFEATED_GIANTSREACH_GYM, GiantsReach_Gym_EventScript_RandallPostBadge
	msgbox GiantsReach_Gym_Text_RandallPostBattle, MSGBOX_AUTOCLOSE
	end

GiantsReach_Gym_EventScript_SlideOpenSpeedRoomDoors::
	setvar VAR_0x8005, 0
	call GiantsReach_Gym_EventScript_OpenSpeedRoomDoors
	special DrawWholeMapView
	release
	end

GiantsReach_Gym_EventScript_RandallPostBadge::
	msgbox GiantsReach_Gym_Text_RandallPostBadge, MSGBOX_NPC
	end

GiantsReach_Gym_EventScript_Parker::
	trainerbattle_single TRAINER_PARKER, GiantsReach_Gym_Text_ParkerIntro, GiantsReach_Gym_Text_ParkerDefeat, GiantsReach_Gym_EventScript_SlideOpenConfusionRoomDoors
	goto_if_set FLAG_DEFEATED_GIANTSREACH_GYM, GiantsReach_Gym_EventScript_ParkerPostBadge
	msgbox GiantsReach_Gym_Text_ParkerPostBattle, MSGBOX_AUTOCLOSE
	end

GiantsReach_Gym_EventScript_SlideOpenConfusionRoomDoors::
	setvar VAR_0x8005, 0
	call GiantsReach_Gym_EventScript_OpenConfusionRoomDoors
	special DrawWholeMapView
	release
	end

GiantsReach_Gym_EventScript_ParkerPostBadge::
	msgbox GiantsReach_Gym_Text_ParkerPostBadge, MSGBOX_NPC
	end

GiantsReach_Gym_EventScript_George::
	trainerbattle_single TRAINER_GEORGE, GiantsReach_Gym_Text_GeorgeIntro, GiantsReach_Gym_Text_GeorgeDefeat, GiantsReach_Gym_EventScript_SlideOpenRecoveryRoomDoors
	goto_if_set FLAG_DEFEATED_GIANTSREACH_GYM, GiantsReach_Gym_EventScript_GeorgePostBadge
	msgbox GiantsReach_Gym_Text_GeorgePostBattle, MSGBOX_AUTOCLOSE
	end

GiantsReach_Gym_EventScript_SlideOpenRecoveryRoomDoors::
	setvar VAR_0x8005, 0
	call GiantsReach_Gym_EventScript_OpenRecoveryRoomDoors
	special DrawWholeMapView
	release
	end

GiantsReach_Gym_EventScript_GeorgePostBadge::
	msgbox GiantsReach_Gym_Text_GeorgePostBadge, MSGBOX_NPC
	end

GiantsReach_Gym_EventScript_Berke::
	trainerbattle_single TRAINER_BERKE, GiantsReach_Gym_Text_BerkeIntro, GiantsReach_Gym_Text_BerkeDefeat, GiantsReach_Gym_EventScript_SlideOpenOHKORoomDoors
	goto_if_set FLAG_DEFEATED_GIANTSREACH_GYM, GiantsReach_Gym_EventScript_BerkePostBadge
	msgbox GiantsReach_Gym_Text_BerkePostBattle, MSGBOX_AUTOCLOSE
	end

GiantsReach_Gym_EventScript_SlideOpenOHKORoomDoors::
	setvar VAR_0x8005, 0
	call GiantsReach_Gym_EventScript_OpenOHKORoomDoors
	special DrawWholeMapView
	release
	end

GiantsReach_Gym_EventScript_BerkePostBadge::
	msgbox GiantsReach_Gym_Text_BerkePostBadge, MSGBOX_NPC
	end

GiantsReach_Gym_EventScript_Mary::
	trainerbattle_single TRAINER_MARY, GiantsReach_Gym_Text_MaryIntro, GiantsReach_Gym_Text_MaryDefeat, GiantsReach_Gym_EventScript_SlideOpenAccuracyRoomDoors
	goto_if_set FLAG_DEFEATED_GIANTSREACH_GYM, GiantsReach_Gym_EventScript_MaryPostBadge
	msgbox GiantsReach_Gym_Text_MaryPostBattle, MSGBOX_AUTOCLOSE
	end

GiantsReach_Gym_EventScript_SlideOpenAccuracyRoomDoors::
	setvar VAR_0x8005, 0
	call GiantsReach_Gym_EventScript_OpenAccuracyRoomDoors
	special DrawWholeMapView
	release
	end

GiantsReach_Gym_EventScript_MaryPostBadge::
	msgbox GiantsReach_Gym_Text_MaryPostBadge, MSGBOX_NPC
	end

GiantsReach_Gym_EventScript_Alexia::
	trainerbattle_single TRAINER_ALEXIA, GiantsReach_Gym_Text_AlexiaIntro, GiantsReach_Gym_Text_AlexiaDefeat, GiantsReach_Gym_EventScript_SlideOpenDefenseRoomDoors
	goto_if_set FLAG_DEFEATED_GIANTSREACH_GYM, GiantsReach_Gym_EventScript_AlexiaPostBadge
	msgbox GiantsReach_Gym_Text_AlexiaPostBattle, MSGBOX_AUTOCLOSE
	end

GiantsReach_Gym_EventScript_SlideOpenDefenseRoomDoors::
	setvar VAR_0x8005, 0
	call GiantsReach_Gym_EventScript_OpenDefenseRoomDoors
	special DrawWholeMapView
	release
	end

GiantsReach_Gym_EventScript_AlexiaPostBadge::
	msgbox GiantsReach_Gym_Text_AlexiaPostBadge, MSGBOX_NPC
	end

GiantsReach_Gym_EventScript_Jody::
	trainerbattle_single TRAINER_JODY, GiantsReach_Gym_Text_JodyIntro, GiantsReach_Gym_Text_JodyDefeat, GiantsReach_Gym_EventScript_SlideOpenStrengthRoomDoors
	goto_if_set FLAG_DEFEATED_GIANTSREACH_GYM, GiantsReach_Gym_EventScript_JodyPostBadge
	msgbox GiantsReach_Gym_Text_JodyPostBattle, MSGBOX_AUTOCLOSE
	end

GiantsReach_Gym_EventScript_SlideOpenStrengthRoomDoors::
	setvar VAR_0x8005, 0
	call GiantsReach_Gym_EventScript_OpenStrengthRoomDoors
	special DrawWholeMapView
	release
	end

GiantsReach_Gym_EventScript_JodyPostBadge::
	msgbox GiantsReach_Gym_Text_JodyPostBadge, MSGBOX_NPC
	end

@ VAR_0x8004 below is the room number
@ VAR_0x8005 below is 0 when the door should be slid open and 1 when it should be unlocked immediately
GiantsReach_Gym_EventScript_OpenGymEntranceDoors::
	setvar VAR_0x8004, 1
	call_if_eq VAR_0x8005, 0, GiantsReach_Gym_EventScript_SlideOpenRoomDoors
	call_if_eq VAR_0x8005, 1, GiantsReach_Gym_EventScript_UnlockRoomDoors
	call GiantsReach_Gym_EventScript_SetEntranceRoomDoorMetatiles
	return

GiantsReach_Gym_EventScript_OpenSpeedRoomDoors::
	setvar VAR_0x8004, 2
	call_if_eq VAR_0x8005, 0, GiantsReach_Gym_EventScript_SlideOpenRoomDoors
	call_if_eq VAR_0x8005, 1, GiantsReach_Gym_EventScript_UnlockRoomDoors
	call GiantsReach_Gym_EventScript_SetSpeedRoomDoorMetatiles
	return

GiantsReach_Gym_EventScript_OpenAccuracyRoomDoors::
	setvar VAR_0x8004, 3
	call_if_eq VAR_0x8005, 0, GiantsReach_Gym_EventScript_SlideOpenRoomDoors
	call_if_eq VAR_0x8005, 1, GiantsReach_Gym_EventScript_UnlockRoomDoors
	call GiantsReach_Gym_EventScript_SetAccuracyRoomDoorMetatiles
	return

GiantsReach_Gym_EventScript_OpenConfusionRoomDoors::
	setvar VAR_0x8004, 4
	call_if_eq VAR_0x8005, 0, GiantsReach_Gym_EventScript_SlideOpenRoomDoors
	call_if_eq VAR_0x8005, 1, GiantsReach_Gym_EventScript_UnlockRoomDoors
	call GiantsReach_Gym_EventScript_SetConfusionRoomDoorMetatiles
	return

GiantsReach_Gym_EventScript_OpenDefenseRoomDoors::
	setvar VAR_0x8004, 5
	call_if_eq VAR_0x8005, 0, GiantsReach_Gym_EventScript_SlideOpenRoomDoors
	call_if_eq VAR_0x8005, 1, GiantsReach_Gym_EventScript_UnlockRoomDoors
	call GiantsReach_Gym_EventScript_SetDefenseRoomDoorMetatiles
	return

GiantsReach_Gym_EventScript_OpenRecoveryRoomDoors::
	setvar VAR_0x8004, 6
	call_if_eq VAR_0x8005, 0, GiantsReach_Gym_EventScript_SlideOpenRoomDoors
	call_if_eq VAR_0x8005, 1, GiantsReach_Gym_EventScript_UnlockRoomDoors
	call GiantsReach_Gym_EventScript_SetRecoveryRoomDoorMetatiles
	return

GiantsReach_Gym_EventScript_OpenStrengthRoomDoors::
	setvar VAR_0x8004, 7
	call_if_eq VAR_0x8005, 0, GiantsReach_Gym_EventScript_SlideOpenRoomDoors
	call_if_eq VAR_0x8005, 1, GiantsReach_Gym_EventScript_UnlockRoomDoors
	call GiantsReach_Gym_EventScript_SetStrengthRoomDoorMetatiles
	return

GiantsReach_Gym_EventScript_OpenOHKORoomDoors::
	setvar VAR_0x8004, 8
	call_if_eq VAR_0x8005, 0, GiantsReach_Gym_EventScript_SlideOpenRoomDoors
	call_if_eq VAR_0x8005, 1, GiantsReach_Gym_EventScript_UnlockRoomDoors
	call GiantsReach_Gym_EventScript_SetOHKORoomDoorMetatiles
	return

GiantsReach_Gym_EventScript_SetEntranceRoomDoorMetatiles::
	setmetatile 6, 85, METATILE_PetalburgGym_RoomEntrance_Left, FALSE
	setmetatile 7, 85, METATILE_PetalburgGym_RoomEntrance_Right, FALSE
	setmetatile 1, 98, METATILE_PetalburgGym_RoomEntrance_Left, FALSE
	setmetatile 2, 98, METATILE_PetalburgGym_RoomEntrance_Right, FALSE
	return

GiantsReach_Gym_EventScript_SetSpeedRoomDoorMetatiles::
	setmetatile 6, 46, METATILE_PetalburgGym_RoomEntrance_Left, FALSE
	setmetatile 7, 46, METATILE_PetalburgGym_RoomEntrance_Right, FALSE
	setmetatile 1, 59, METATILE_PetalburgGym_RoomEntrance_Left, FALSE
	setmetatile 2, 59, METATILE_PetalburgGym_RoomEntrance_Right, FALSE
	return

GiantsReach_Gym_EventScript_SetAccuracyRoomDoorMetatiles::
	setmetatile 6, 59, METATILE_PetalburgGym_RoomEntrance_Left, FALSE
	setmetatile 7, 59, METATILE_PetalburgGym_RoomEntrance_Right, FALSE
	setmetatile 1, 72, METATILE_PetalburgGym_RoomEntrance_Left, FALSE
	setmetatile 2, 72, METATILE_PetalburgGym_RoomEntrance_Right, FALSE
	return

GiantsReach_Gym_EventScript_SetConfusionRoomDoorMetatiles::
	setmetatile 1, 20, METATILE_PetalburgGym_RoomEntrance_Left, FALSE
	setmetatile 2, 20, METATILE_PetalburgGym_RoomEntrance_Right, FALSE
	return

GiantsReach_Gym_EventScript_SetDefenseRoomDoorMetatiles::
	setmetatile 6, 20, METATILE_PetalburgGym_RoomEntrance_Left, FALSE
	setmetatile 7, 20, METATILE_PetalburgGym_RoomEntrance_Right, FALSE
	setmetatile 1, 33, METATILE_PetalburgGym_RoomEntrance_Left, FALSE
	setmetatile 2, 33, METATILE_PetalburgGym_RoomEntrance_Right, FALSE
	return

GiantsReach_Gym_EventScript_SetRecoveryRoomDoorMetatiles::
	setmetatile 6, 33, METATILE_PetalburgGym_RoomEntrance_Left, FALSE
	setmetatile 7, 33, METATILE_PetalburgGym_RoomEntrance_Right, FALSE
	return

GiantsReach_Gym_EventScript_SetStrengthRoomDoorMetatiles::
	setmetatile 1, 7, METATILE_PetalburgGym_RoomEntrance_Left, FALSE
	setmetatile 2, 7, METATILE_PetalburgGym_RoomEntrance_Right, FALSE
	return

GiantsReach_Gym_EventScript_SetOHKORoomDoorMetatiles::
	setmetatile 6, 7, METATILE_PetalburgGym_RoomEntrance_Left, FALSE
	setmetatile 7, 7, METATILE_PetalburgGym_RoomEntrance_Right, FALSE
	return

GiantsReach_Gym_EventScript_SlideOpenRoomDoors::
	special PetalburgGymSlideOpenRoomDoors
	waitstate
	return

GiantsReach_Gym_EventScript_UnlockRoomDoors::
	special PetalburgGymUnlockRoomDoors
	return

GiantsReach_Gym_EventScript_GymGuide::
	lock
	faceplayer
	goto_if_set FLAG_DEFEATED_GIANTSREACH_GYM, GiantsReach_Gym_EventScript_GymGuidePostVictory
	msgbox GiantsReach_Gym_Text_GymGuideAdvice, MSGBOX_DEFAULT
	release
	end

GiantsReach_Gym_EventScript_GymGuidePostVictory::
	msgbox GiantsReach_Gym_Text_GymGuidePostVictory, MSGBOX_DEFAULT
	release
	end

GiantsReach_Gym_EventScript_LeftGymStatue::
	lockall
	goto_if_set FLAG_BADGE05_GET, GiantsReach_Gym_EventScript_GymStatueCertified
	goto GiantsReach_Gym_EventScript_GymStatue
	end

GiantsReach_Gym_EventScript_RightGymStatue::
	lockall
	goto_if_set FLAG_BADGE05_GET, GiantsReach_Gym_EventScript_GymStatueCertified
	goto GiantsReach_Gym_EventScript_GymStatue
	end

GiantsReach_Gym_EventScript_GymStatueCertified::
	msgbox GiantsReach_Gym_Text_GymStatueCertified, MSGBOX_DEFAULT
	releaseall
	end

GiantsReach_Gym_EventScript_GymStatue::
	msgbox GiantsReach_Gym_Text_GymStatue, MSGBOX_DEFAULT
	releaseall
	end

GiantsReach_Gym_Text_DadYoureHereWithYourPokemon:
	.string "UNCLE JACK: Oh, hey there, sport.\p"
	.string "Wow… look at you.\n"
	.string "You made it all the way here on your own.\l"
	.string "That’s... really impressive.\p"
	.string "No adult supervision or anything?\n"
	.string "You're totally unsupervised?\p"
	.string "That's cool. Totally cool.\p"
	.string "Oh, you’ve got a Pokémon with you.\n"
	.string "Even better.\p"
	.string "It’s important to have a companion,\n"
	.string "you know. Someone who… trusts you.\p"
	.string "So you wanna be a Trainer, huh?\n"
	.string "Just like your old Uncle Jack?\p"
	.string "That’s… that’s great. Real great.\p"
	.string "We should… hang out sometime. Just us.\n"
	.string "No pressure.\p"
	.string "You know I’ve always wanted to be a part\n"
	.string "of your journey....\p"
	.string "I’d love to...guide you. Like a mentor.\n"
	.string "Or like a... strong, supportive adult\l"
	.string "figure.$"

GiantsReach_Gym_Text_MatthewIdLikeAPokemon:
	.string "MATTHEW: Um… hey, excuse me…\p"
	.string "I was just wondering if maybe I could…\n"
	.string "get a POKéMON? Just a small one?\p"
	.string "I promise I’d take good care of it.\p"
	.string "Like, really good.\n"
	.string "Prayer and everything.$"

GiantsReach_Gym_Text_DadOhYoureMatthewRight:
	.string "UNCLE JACK: Hm? Who’s this little guy?\p"
	.string ".........................\p"
	.string "Oh. Right. You’re Matthew. Yeah.\p"
	.string "Sorry, I was… distracted. Thinking \n"
	.string "about mentorship.$"

GiantsReach_Gym_Text_MatthewIveNeverCaughtAPokemon:
	.string "MATTHEW: I’m heading to VERDANTURF for\n"
	.string "some fresh air. Healing vibes.\l"
	.string "And, well, I thought I’d be lonely.\p"
	.string "So I wanted a POKéMON to keep me\n"
	.string "company.\p"
	.string "Problem is, I’ve never actually\n"
	.string "caught one before…\p"
	.string "Seminary didn’t exactly cover that.$"

GiantsReach_Gym_Text_DadHmISee:
	.string "UNCLE JACK: Yeah, okay.\n"
	.string "I see what’s going on.\p"
	.string "I’ve seen this kind of thing before.$"

GiantsReach_Gym_Text_DadPlayerGoWithMatthew:
	.string "UNCLE JACK: Hey {PLAYER},\n"
	.string "why don’t you go with him?\l"
	.string "Make sure he’s safe.\p"
	.string "Not unsafe. Not like the time I..\n"
	.string "…Never mind.\l"
	.string "Just… make sure he comes back.$"

GiantsReach_Gym_Text_IllLoanYouMyZigzagoon:
	.string "UNCLE JACK: Here, Matthew.\n"
	.string "I’ll loan you my Pokémon.\p"
	.string "He's real obedient. Like a good\n"
	.string "partner should be.\p"
	.string "Don’t worry, he won’t bite unless I tell\n"
	.string "him to.$"

GiantsReach_Gym_Text_MatthewThankYouAndDadGivesPokeBall:
	.string "MATTHEW: Whoa, seriously?!\n"
	.string "You're really giving me a POKéMON?\p"
	.string "UNCLE JACK: And here’s a Poké Ball.\n"
	.string "Grip it tight. Real tight and snug.\p"
	.string "MATTHEW: Uh… yeah, okay. Thanks?\p"
	.string "This feels… spiritual.$"

GiantsReach_Gym_Text_MatthewOhWowThankYou:
	.string "MATTHEW: Oh wow, thank you so much!\n"
	.string "This means a lot to me. Like, deeply.$"

GiantsReach_Gym_Text_WouldYouReallyComeWithMe:
	.string "MATTHEW: Uh, {PLAYER}?\p"
	.string "I know this is awkward…\n"
	.string "but would you maybe come with me?\p"
	.string "Just in case the wild POKéMON, you know,\n"
	.string "aren’t moved by my faith?$"

GiantsReach_Gym_Text_DadSoDidItWorkOut:
	.string "UNCLE JACK: So? Everything… go okay?\p"
	.string "Nobody got hurt, right?\n"
	.string "Everything’s… above board?$"

GiantsReach_Gym_Text_MatthewThankYouBye:
	.string "MATTHEW: It worked! I did it!\n"
	.string "And no bites! No scratches!\p"
	.string "Here’s your POKéMON back, Jack.\p"
	.string "He kind of growled at me,\n"
	.string "but I think he likes me.\p"
	.string "{PLAYER}, really.. thank you.\n"
	.string "I wouldn’t have done this without you.\p"
	.string "This might be the start of something\n"
	.string "big!\p"
	.string "Like… maybe I’ve got a calling after\n"
	.string "all!\p"
	.string "Anyway, I gotta go.\p"
	.string "Bye, {PLAYER}!$"

GiantsReach_Gym_Text_DadGoCollectBadges:
	.string "UNCLE JACK: Alright, {PLAYER}.\p"
	.string "If you really want to be a strong\n"
	.string "Trainer...Like me...With big hands..\p"
	.string "You gotta head to Wawa Park.\n"
	.string "There’s a Gym there.\p"
	.string "Challenge the Leader. Win a Badge.\n"
	.string "Then do it again. Over and over.\p"
	.string "Keep proving yourself to strangers.\n"
	.string "It’s the system.\p"
	.string "Eventually you’ll circle back here.\p"
	.string "And when you’re strong enough…\n"
	.string "You and me..we’ll battle.\p"
	.string "Just the two of us.\n"
	.string "With full consent.\p"
	.string "We can have so much fun foolin' around.\n"
	.string "..................\l"
	.string "Just be ready.$"

GiantsReach_Gym_Text_NormanGoToRustboro:
	.string "UNCLE JACK: Hm? Aren't you going to the\n"
	.string "POKéMON GYM in WAWA PARK?\p"
	.string "There's no challenge for me to\n"
	.string "battle a greenhorn TRAINER.\p"
	.string "{PLAYER}, I want you to challenge me\n"
	.string "when you become a lot stronger.\p"
	.string "I'll battle you, {PLAYER}, when you\n"
	.string "can show me four GYM BADGES, okay?$"

GiantsReach_Gym_Text_NormanGoToDewford:
	.string "UNCLE JACK: I see… So you’ve been out\n"
	.string "there, getting stronger.\l"
	.string "Good. Real good.\p"
	.string "There's this big, tan guy named BRAWLY\n"
	.string "across the sea in DEWFORD.\l"
	.string "You should go say hi.\p"
	.string "Test yourself. Get sweaty. Let him teach\n"
	.string "you a thing or two.\p"
	.string "Then come back, tell your old Uncle Jack\n"
	.string "all about it. I’ll be waitin’, {PLAYER}.$"

GiantsReach_Gym_Text_YouHaveGottenStronger:
	.string "UNCLE JACK: Hnn… You’ve been training.\n"
	.string "I can smell it on you.\l"
	.string "That effort. That grit.\p"
	.string "You’re growing up so fast…\p"
	.string "You remind me of myself...\n"
	.string "But hotter. Stronger. More dangerous.$"

GiantsReach_Gym_Text_NormanIntro:
	.string "UNCLE JACK: Four badges. You’ve really\n"
	.string "done it.\p"
	.string "A promise is a promise.\n"
	.string "We’re gonna battle, Charlie.\p"
	.string "You don’t know how long I’ve waited to\n"
	.string "go toe-to-toe with you.\p"
	.string "Like this. Just us. No distractions.\n"
	.string "Just fists and fury and ...\p"
	.string "Sorry... I just… missed you, man.\n"
	.string "Let’s make this count.$"

GiantsReach_Gym_Text_NormanDefeat:
	.string "UNCLE JACK: …\n"
	.string "That was… intense.\p"
	.string "You beat me. You beat me good, Charlie.\p"
	.string "I’m not even mad. Actually, I think…\n"
	.string "I’m proud.\p"
	.string "Also weirdly excited. Maybe too excited.\n"
	.string "When did my shorts get so tight...$"

GiantsReach_Gym_Text_ReceivedBalanceBadge:
	.string "{PLAYER} received the BALANCE BADGE\n"
	.string "from UNCLE JACK!$"

GiantsReach_Gym_Text_ExplainBalanceBadgeTakeThis:
	.string "UNCLE JACK: That BADGE’ll toughen up\n"
	.string "your whole squad.\p"
	.string "The Defense of your POKéMON will\n"
	.string "increase. Bulk ‘em up.\l"
	.string "Like a good protein shake.\p"
	.string "Also lets you SURF now.\n"
	.string "Water’s powerful, Charlie. Fluid. Deep.\p"
	.string "This here’s for you. I trust you with it.\n"
	.string "Just don’t use it in a hot tub.$"

GiantsReach_Gym_Text_ExplainFacade:
	.string "UNCLE JACK: TM42’s FACADE.\n"
	.string "Nasty little move.\p"
	.string "Gets meaner if your POKéMON’s all\n"
	.string "banged up, poisoned, paralyzed,\l"
	.string "tied down... You get the picture.\p"
	.string "Real metaphor for life, huh? Pain makes\n"
	.string "you stronger. You might be able to turn\l"
	.string "a bad situation into an advantage.$"

GiantsReach_Gym_Text_DadHappyAndSad:
	.string "UNCLE JACK: As a GYM LEADER,\n"
	.string "I hate losing. Really do.\p"
	.string "But as your Uncle Jack… man,\n"
	.string "it’s like my whole chest is doing\l"
	.string "jumping jacks. My whole body is excited.\p"
	.string "Happy. Sad. Sweaty. All at once.\n"
	.string "It’s a mess in here.$"

GiantsReach_Gym_Text_PleaseComeWithMe:
	.string "Ah, there you are, {PLAYER}{KUN}!\p"
	.string "Please come with me.\n"
	.string "I have something I want you to have.$"

GiantsReach_Gym_Text_LetMeBorrowPlayer:
	.string "NORMAN, you don't mind, do you?\p"
	.string "Let me borrow your {PLAYER}{KUN} for\n"
	.string "a minute or two.$"

GiantsReach_Gym_Text_DadGoingToKeepTraining:
	.string "UNCLE JACK: You should go visit your\n"
	.string "mom sometime. She worries, y’know.\p"
	.string "I’ll be stayin’ here. Gotta push myself\n"
	.string "harder. Get shredded. Get redemption.\p"
	.string "Gotta be ready if you ever wanna go\n"
	.string "another round.\p"
	.string "And I hope you do, Charlie.\n"
	.string "I really do.$"

GiantsReach_Gym_Text_DadNoAmountOfTrainingIsEnough:
	.string "UNCLE JACK: How’s it goin’\n"
	.string "out there, champ?\p"
	.string "This world… it’s so dang big.\n"
	.string "Deep. Mysterious.\p"
	.string "Sometimes I wonder if I’ll ever be\n"
	.string "strong enough.\p"
	.string "But that’s the thrill, ain’t it? The chase.$"

GiantsReach_Gym_Text_GymGuideAdvice:
	.string "Hey, how's it going, CHAMPION-\n"
	.string "bound {PLAYER}?\p"
	.string "The doors in this GYM open when you\n"
	.string "beat the awaiting TRAINERS.\p"
	.string "Whoops! The doors in this room are\n"
	.string "already open, so don't attack me!\p"
	.string "The TRAINERS of Giant's Reach GYM\n"
	.string "use all kinds of items.\p"
	.string "The door at the left leads to\n"
	.string "the SPEED ROOM.\p"
	.string "The door at the right leads to\n"
	.string "the ACCURACY ROOM.\p"
	.string "The room's name will be on\n"
	.string "the door, so choose carefully.\p"
	.string "Once you've chosen the door…\n"
	.string "Well, hey, go for it!$"

GiantsReach_Gym_Text_GymGuidePostVictory:
	.string "{PLAYER}! Whoa! You've overcome even\n"
	.string "your own father!\p"
	.string "Like, whoa!\n"
	.string "What a stunning turn of events!$"

GiantsReach_Gym_Text_RandallIntro:
	.string "The ability to attack before the\n"
	.string "opponent…\p"
	.string "Just that alone puts me at a great\n"
	.string "advantage, don't you agree?$"

GiantsReach_Gym_Text_RandallDefeat:
	.string "That was a magnificent battle!$"

GiantsReach_Gym_Text_RandallPostBattle:
	.string "Go on to the next room where a new\n"
	.string "challenge awaits you.\p"
	.string "At the left is the CONFUSION ROOM.\p"
	.string "The right door leads to the DEFENSE\n"
	.string "ROOM.$"

GiantsReach_Gym_Text_RandallPostBadge:
	.string "Whomever you beat, and whomever you\n"
	.string "may lose to, you never shirk from\l"
	.string "training yourself and your POKéMON.\p"
	.string "That's what I think being a\n"
	.string "GYM LEADER is all about.$"

GiantsReach_Gym_Text_ParkerIntro:
	.string "This is the CONFUSION ROOM.\p"
	.string "Let me see how well bonded you are\n"
	.string "with your POKéMON!$"

GiantsReach_Gym_Text_ParkerDefeat:
	.string "I couldn't confuse your team enough…\n"
	.string "You share a strong bond together.$"

GiantsReach_Gym_Text_ParkerPostBattle:
	.string "The next room is the STRENGTH ROOM.\n"
	.string "Can you withstand brute force?$"

GiantsReach_Gym_Text_ParkerPostBadge:
	.string "After you beat our LEADER, the\n"
	.string "training has become a lot tougher.$"

GiantsReach_Gym_Text_GeorgeIntro:
	.string "Just when you think you're going to\n"
	.string "win, your opponent restores HP…\p"
	.string "Can you just imagine how awful that\n"
	.string "must feel?\p"
	.string "I'll show you exactly how awful it\n"
	.string "feels!$"

GiantsReach_Gym_Text_GeorgeDefeat:
	.string "I couldn't restore HP enough…\n"
	.string "What ATTACK power…$"

GiantsReach_Gym_Text_GeorgePostBattle:
	.string "I should have expected no less from\n"
	.string "our LEADER's kid.\p"
	.string "No, wait! A TRAINER's abilities are\n"
	.string "earned only through effort.\p"
	.string "I lost because my own efforts\n"
	.string "weren't enough.\p"
	.string "Go on! The ONE-HIT KO ROOM is next.$"

GiantsReach_Gym_Text_GeorgePostBadge:
	.string "I'm going to keep training at GYMS.\n"
	.string "One day, I'll become a LEADER.$"

GiantsReach_Gym_Text_BerkeIntro:
	.string "I'm not going to take it easy just\n"
	.string "because you're our LEADER's kid.\p"
	.string "I'll show you how horrid it is for\n"
	.string "a POKéMON to take a critical hit!$"

GiantsReach_Gym_Text_BerkeDefeat:
	.string "Your power…\n"
	.string "You're the real deal.$"

GiantsReach_Gym_Text_BerkePostBattle:
	.string "Your father really is strong.\n"
	.string "He's a TRAINER worth my respect.\p"
	.string "And, I sense the same glow coming\n"
	.string "from you as your father.\p"
	.string "I hope that you'll stage a terrific\n"
	.string "battle with your father!$"

GiantsReach_Gym_Text_BerkePostBadge:
	.string "Since your dad became the LEADER,\n"
	.string "the TRAINERS of GIANT'S REACH have\l"
	.string "become a lot tougher.$"

GiantsReach_Gym_Text_MaryIntro:
	.string "Giggle…\n"
	.string "This is the ACCURACY ROOM.\p"
	.string "It's pretty nasty when every attack\n"
	.string "lands without fail.$"

GiantsReach_Gym_Text_MaryDefeat:
	.string "You were a cut above me…$"

GiantsReach_Gym_Text_MaryPostBattle:
	.string "There are some even stronger\n"
	.string "TRAINERS waiting for you.\p"
	.string "The left is the DEFENSE ROOM, and\n"
	.string "the right is the RECOVERY ROOM.\p"
	.string "Your POKéMON's ATTACK power will be\n"
	.string "on trial either way.$"

GiantsReach_Gym_Text_MaryPostBadge:
	.string "Do you know what we're trying to\n"
	.string "achieve as TRAINERS?\p"
	.string "We're striving to become soul mates\n"
	.string "with our POKéMON.$"

GiantsReach_Gym_Text_AlexiaIntro:
	.string "The higher the DEFENSE, the more\n"
	.string "reckless I can be in attack.$"

GiantsReach_Gym_Text_AlexiaDefeat:
	.string "Our defenses weren't enough…$"

GiantsReach_Gym_Text_AlexiaPostBattle:
	.string "I think you've taught me a valuable\n"
	.string "lesson here.\p"
	.string "Now, go on! The left door goes to\n"
	.string "the STRENGTH ROOM.\p"
	.string "The right door opens to\n"
	.string "the ONE-HIT KO ROOM.\p"
	.string "Both of them have TRAINERS who are\n"
	.string "skilled at offense.$"

GiantsReach_Gym_Text_AlexiaPostBadge:
	.string "Hi! Have you tried using SURF?$"

GiantsReach_Gym_Text_JodyIntro:
	.string "Our GYM LEADER told us to go all out\n"
	.string "and beat you.\p"
	.string "Even if you happen to be the\n"
	.string "LEADER's kid!$"

GiantsReach_Gym_Text_JodyDefeat:
	.string "But… I went all out!$"

GiantsReach_Gym_Text_JodyPostBattle:
	.string "The way you use your POKéMON…\n"
	.string "It's like your father's style.\p"
	.string "Go on through! The GYM LEADER, your\n"
	.string "father, is waiting!$"

GiantsReach_Gym_Text_JodyPostBadge:
	.string "Sure, it's fine to make your POKéMON\n"
	.string "stronger.\p"
	.string "But what decides the winner?\p"
	.string "Why, it's the feelings TRAINERS have\n"
	.string "for their POKéMON.$"

GiantsReach_Gym_Text_DoorAppearsLocked:
	.string "This door appears to be locked\n"
	.string "right now…$"

GiantsReach_Gym_Text_EnterSpeedRoom:
	.string "“SPEED ROOM,” the sign says.\p"
	.string "Do you want to go through?$"

@ Unused
GiantsReach_Gym_Text_DoorAppearsLocked2:
	.string "This door appears to be locked\n"
	.string "right now…$"

GiantsReach_Gym_Text_EnterAccuracyRoom:
	.string "“ACCURACY ROOM,” the sign says.\p"
	.string "Do you want to go through?$"

GiantsReach_Gym_Text_EnterConfusionRoom:
	.string "“CONFUSION ROOM,” the sign says.\p"
	.string "Do you want to go through?$"

GiantsReach_Gym_Text_EnterDefenseRoom:
	.string "“DEFENSE ROOM,” the sign says.\p"
	.string "Do you want to go through?$"

GiantsReach_Gym_Text_EnterRecoveryRoom:
	.string "“RECOVERY ROOM,” the sign says.\p"
	.string "Do you want to go through?$"

GiantsReach_Gym_Text_EnterStrengthRoom:
	.string "“STRENGTH ROOM,” the sign says.\p"
	.string "Do you want to go through?$"

GiantsReach_Gym_Text_EnterOHKORoom:
	.string "“ONE-HIT KO ROOM,” the sign says.\p"
	.string "Do you want to go through?$"

GiantsReach_Gym_Text_EnterGymLeadersRoom:
	.string "“GYM LEADER'S ROOM\p"
	.string "“See for yourself what POKéMON await\n"
	.string "you!” the sign says.\p"
	.string "Do you want to go through?$"

GiantsReach_Gym_Text_GymStatue:
	.string "GIANT'S REACH POKéMON GYM$"

GiantsReach_Gym_Text_GymStatueCertified:
	.string "GIANT'S REACH POKéMON GYM\p"
	.string "NORMAN'S CERTIFIED TRAINERS:\n"
	.string "{PLAYER}$"

GiantsReach_Gym_Text_NormanPreRematch:
	.string "DAD: {PLAYER}…\n"
	.string "I had a feeling that you would come.\p"
	.string "I would never refuse to accept\n"
	.string "a challenge from you.\p"
	.string "You do understand, don't you?\p"
	.string "Inside a GYM, it doesn't matter that\n"
	.string "we are a parent and child.\p"
	.string "…No, because we are parent and child,\n"
	.string "we owe it to each other to do the best\l"
	.string "we can. Isn't that right, {PLAYER}?$"

GiantsReach_Gym_Text_NormanRematchDefeat:
	.string "Uh… Haha…\n"
	.string "Maybe that was going too hard…$"

GiantsReach_Gym_Text_NormanPostRematch:
	.string "DAD: {PLAYER}…\n"
	.string "What is your dream?\p"
	.string "My dream…\n"
	.string "Hahaha…\l"
	.string "It has already come true, actually.$"

GiantsReach_Gym_Text_NormanRematchNeedTwoMons:
	.string "DAD: {PLAYER}…\n"
	.string "I had a feeling that you would come.\p"
	.string "I would never refuse to accept\n"
	.string "a challenge from you.\p"
	.string "You do understand, don't you?\p"
	.string "Inside a GYM, it doesn't matter that\n"
	.string "we are a parent and child.\p"
	.string "Hm? Wait a second, {PLAYER}.\p"
	.string "Do you only have one POKéMON that is\n"
	.string "capable of battle?\p"
	.string "Sorry, but you'll have to come back\n"
	.string "with at least two POKéMON.$"

