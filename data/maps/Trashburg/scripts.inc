Trashburg_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, Trashburg_OnTransition
	map_script MAP_SCRIPT_ON_FRAME_TABLE, Trashburg_OnFrame
	map_script MAP_SCRIPT_ON_WARP_INTO_MAP_TABLE, Trashburg_OnWarp
	.byte 0

	@ State descriptions for VAR_TRASHBURG_STATE
	@ 1: Met Rival
	@ 2: Saving Frank
	@ 3: Received Pokedex
	@ 4: Received Running Shoes

	@ State descriptions for VAR_TRASHBURG_INTRO_STATE
	@ 1: In truck male
	@ 2: In truck female
	@ 3: Entered house
	@ 4: Told to go set clock
	@ 5: Entered 2F to set clock
	@ 6: Set clock
	@ 7: Told to go meet rival

	@ State descriptions for VAR_TRASHBURG_HOUSES_STATE_MAY
	@                    and VAR_TRASHBURG_HOUSES_STATE_BRENDAN
	@ 1: On Truck (and is corresponding gender)
	@ 2: Met Rival's Mom (and is corresponding gender)
	@ 3: Entered Hall of Fame
	@ 4: Completed Lati TV / SS Ticket event
	@ 5: Exited house after above event

	@ State descriptions for VAR_TRASHBURG_RIVAL_STATE
	@ 1: Never occurs
	@ 2: Entered Rival's bedroom
	@ 3: Met Rival
	@ 4: Received Pokedex


Trashburg_OnTransition:
	setflag FLAG_VISITED_TRASHBURG
	setflag FLAG_HIDE_DAYNIGHT_SCIENCEGUY
	call Common_EventScript_SetupRivalGfxId
	call_if_eq VAR_TRASHBURG_INTRO_STATE, 2, Trashburg_EventScript_MoveMomToMaysDoor
	call_if_unset FLAG_RESCUED_FRANK, Trashburg_EventScript_SetTwinPos
	call_if_eq VAR_TRASHBURG_STATE, 3, Trashburg_EventScript_SetMomStandingInFrontOfDoorPos
	call_if_eq VAR_TRASHBURG_HOUSES_STATE_BRENDAN, 4, Trashburg_EventScript_SetExitedHouseAfterLatiSSTicketEvent
	call_if_eq VAR_OLD_SCUMPORT_RIVAL_STATE, 1, Trashburg_EventScript_MoveRivalFromOldScumport
	call_if_eq VAR_TRASHBURG_RIVAL_STATE, 3, Trashburg_EventScript_SetRivalLeftForRoute103
	call_if_eq VAR_DEX_UPGRADE_JOHTO_STARTER_STATE, 1, Trashburg_EventScript_HideMapNamePopup
	call_if_eq VAR_DEX_UPGRADE_JOHTO_STARTER_STATE, 2, Trashburg_EventScript_LeftLabAfterDexUpgrade
	end

Trashburg_EventScript_LeftLabAfterDexUpgrade::
	setvar VAR_DEX_UPGRADE_JOHTO_STARTER_STATE, 3
	return

Trashburg_EventScript_HideMapNamePopup::
	setflag FLAG_HIDE_MAP_NAME_POPUP
	return

Trashburg_EventScript_SetRivalLeftForRoute103::
	setflag FLAG_RIVAL_LEFT_FOR_ROUTE103
	return

Trashburg_EventScript_MoveRivalFromOldScumport::
	setvar VAR_OLD_SCUMPORT_RIVAL_STATE, 2
	setflag FLAG_HIDE_OLD_SCUMPORT_RIVAL
	return

Trashburg_EventScript_SetExitedHouseAfterLatiSSTicketEvent::
	setvar VAR_TRASHBURG_HOUSES_STATE_BRENDAN, 5
	return

Trashburg_EventScript_MoveMomToMaysDoor::
	setobjectxyperm LOCALID_TRASHBURG_MOM, 14, 8
	return

Trashburg_EventScript_SetTwinPos::
	goto_if_eq VAR_TRASHBURG_STATE, 0, Trashburg_EventScript_SetTwinGuardingRoutePos
	setobjectxyperm LOCALID_TRASHBURG_TWIN, 10, 1
	setobjectmovementtype LOCALID_TRASHBURG_TWIN, MOVEMENT_TYPE_FACE_UP
	return

Trashburg_EventScript_SetTwinGuardingRoutePos::
	setobjectxyperm LOCALID_TRASHBURG_TWIN, 8, 2
	setobjectmovementtype LOCALID_TRASHBURG_TWIN, MOVEMENT_TYPE_FACE_DOWN
	return

Trashburg_EventScript_SetMomStandingInFrontOfDoorPos::
	clearflag FLAG_HIDE_TRASHBURG_MOM_OUTSIDE
	setobjectmovementtype LOCALID_TRASHBURG_MOM, MOVEMENT_TYPE_FACE_DOWN
	checkplayergender
	call_if_eq VAR_RESULT, MALE, Trashburg_EventScript_SetMomInFrontOfDoorMale
	call_if_eq VAR_RESULT, FEMALE, Trashburg_EventScript_SetMomInFrontOfDoorFemale
	return

Trashburg_EventScript_SetMomInFrontOfDoorMale::
	setobjectxyperm LOCALID_TRASHBURG_MOM, 5, 9
	return

Trashburg_EventScript_SetMomInFrontOfDoorFemale::
	setobjectxyperm LOCALID_TRASHBURG_MOM, 14, 9
	return

Trashburg_OnFrame:
	map_script_2 VAR_TRASHBURG_INTRO_STATE, 1, Trashburg_EventScript_StepOffTruckMale
	map_script_2 VAR_DEX_UPGRADE_JOHTO_STARTER_STATE, 1, Trashburg_EventScript_BeginDexUpgradeScene
	.2byte 0

Trashburg_EventScript_StepOffTruckMale::
	lockall
	setvar VAR_0x8004, 5
	setvar VAR_0x8005, 8
	call Trashburg_EventScript_GoInsideWithMom
	setflag FLAG_HIDE_TRASHBURG_BRENDANS_HOUSE_TRUCK
	warpsilent MAP_TRASHBURG_TOWN_BRENDANS_HOUSE_1F, 8, 8
	waitstate
	releaseall
	end


Trashburg_EventScript_GoInsideWithMom::
	delay 15
	playse SE_LEDGE
	applymovement LOCALID_PLAYER, Trashburg_Movement_PlayerStepOffTruck
	waitmovement 0
	opendoor VAR_0x8004, VAR_0x8005
	waitdooranim
	addobject LOCALID_TRASHBURG_MOM
	applymovement LOCALID_TRASHBURG_MOM, Trashburg_Movement_MomExitHouse
	waitmovement 0
	closedoor VAR_0x8004, VAR_0x8005
	waitdooranim
	delay 10
	applymovement LOCALID_TRASHBURG_MOM, Trashburg_Movement_MomApproachPlayerAtTruck
	waitmovement 0
	msgbox Trashburg_Text_OurNewHomeLetsGoInside, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_TRASHBURG_MOM, Trashburg_Movement_MomApproachDoor
	applymovement LOCALID_PLAYER, Trashburg_Movement_PlayerApproachDoor
	waitmovement 0
	opendoor VAR_0x8004, VAR_0x8005
	waitdooranim
	applymovement LOCALID_TRASHBURG_MOM, Trashburg_Movement_MomEnterHouse
	applymovement LOCALID_PLAYER, Trashburg_Movement_PlayerEnterHouse
	waitmovement 0
	setflag FLAG_HIDE_TRASHBURG_MOM_OUTSIDE
	setvar VAR_TRASHBURG_INTRO_STATE, 3
	hideobjectat LOCALID_PLAYER, 0
	closedoor VAR_0x8004, VAR_0x8005
	waitdooranim
	clearflag FLAG_HIDE_TRASHBURG_FAT_MAN
	clearflag FLAG_HIDE_MAP_NAME_POPUP
	return

Trashburg_Movement_MomExitHouse:
	walk_down
	step_end

Trashburg_Movement_MomApproachPlayerAtTruck:
	walk_down
	walk_in_place_faster_left
	step_end

Trashburg_Movement_MomApproachDoor:
	delay_16
	delay_8
	walk_up
	step_end

Trashburg_Movement_MomEnterHouse:
	walk_up
	set_invisible
	step_end

Trashburg_Movement_PlayerApproachDoor:
	delay_16
	delay_8
	walk_right
	walk_in_place_faster_up
	step_end

Trashburg_Movement_PlayerEnterHouse:
	walk_up
	walk_up
	step_end

Trashburg_Movement_PlayerStepOffTruck:
	jump_right
	delay_16
	delay_16
	delay_16
	step_end

Trashburg_EventScript_BeginDexUpgradeScene::
	lockall
	playse SE_PIN
	applymovement LOCALID_TRASHBURG_FRANK, Common_Movement_ExclamationMark
	waitmovement 0
	delay 80
	msgbox Trashburg_Text_FrankSomethingToShowYouAtLab, MSGBOX_DEFAULT
	closemessage
	clearflag FLAG_HIDE_TRASHBURG_RIVAL
	clearflag FLAG_HIDE_TRASHBURG_FRANK
	delay 20
	clearflag FLAG_HIDE_MAP_NAME_POPUP
	warp MAP_TRASHBURG_PROFESSOR_FRANKS_LAB, 6, 5
	waitstate
	releaseall
	end

Trashburg_OnWarp:
	map_script_2 VAR_DEX_UPGRADE_JOHTO_STARTER_STATE, 1, Trashburg_EventScript_SetRivalFrankPosForDexUpgrade
	.2byte 0

Trashburg_EventScript_SetRivalFrankPosForDexUpgrade::
	addobject LOCALID_TRASHBURG_FRANK
	addobject LOCALID_TRASHBURG_RIVAL
	checkplayergender
	goto_if_eq VAR_RESULT, MALE, Trashburg_EventScript_SetRivalFrankPosForDexUpgradeMale
	goto Trashburg_EventScript_SetRivalFrankPosForDexUpgradeFemale
	end

Trashburg_EventScript_SetRivalFrankPosForDexUpgradeMale::
	setobjectxy LOCALID_TRASHBURG_RIVAL, 6, 10
	setobjectxy LOCALID_TRASHBURG_FRANK, 5, 10
	end

Trashburg_EventScript_SetRivalFrankPosForDexUpgradeFemale::
	setobjectxy LOCALID_TRASHBURG_RIVAL, 5, 10
	setobjectxy LOCALID_TRASHBURG_FRANK, 6, 10
	end

Trashburg_EventScript_FatMan::
	msgbox Trashburg_Text_CanUsePCToStoreItems, MSGBOX_NPC
	end

Trashburg_EventScript_Boy::
	msgbox Trashburg_Text_FrankSpendsDaysInLab, MSGBOX_NPC
	end

Trashburg_EventScript_Twin::
	lock
	faceplayer
	goto_if_set FLAG_ADVENTURE_STARTED, Trashburg_EventScript_YouSavedFrank
	goto_if_set FLAG_RESCUED_FRANK, Trashburg_EventScript_YouSavedFrank
	goto_if_ne VAR_TRASHBURG_STATE, 0, Trashburg_EventScript_GoSaveFrank
	msgbox Trashburg_Text_IfYouGoInGrassPokemonWillJumpOut, MSGBOX_DEFAULT
	release
	end

Trashburg_EventScript_GoSaveFrank::
	special GetPlayerBigGuyGirlString
	msgbox Trashburg_Text_CanYouGoSeeWhatsHappening, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_TRASHBURG_TWIN, Common_Movement_FaceOriginalDirection
	waitmovement 0
	setvar VAR_TRASHBURG_STATE, 2
	release
	end

Trashburg_EventScript_YouSavedFrank::
	special GetPlayerBigGuyGirlString
	msgbox Trashburg_Text_YouSavedFrank, MSGBOX_DEFAULT
	release
	end

Trashburg_EventScript_NeedPokemonTriggerLeft::
	lockall
	applymovement LOCALID_TRASHBURG_TWIN, Trashburg_Movement_TwinApproachPlayerLeft
	waitmovement 0
	call Trashburg_EventScript_DangerousWithoutPokemon
	applymovement LOCALID_TRASHBURG_TWIN, Trashburg_Movement_TwinReturnLeft
	waitmovement 0
	releaseall
	end

Trashburg_EventScript_DangerousWithoutPokemon::
	msgbox Trashburg_Text_IfYouGoInGrassPokemonWillJumpOut, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_TRASHBURG_TWIN, Trashburg_Movement_TwinPushPlayerFromRoute
	applymovement LOCALID_PLAYER, Trashburg_Movement_PushPlayerBackFromRoute
	waitmovement 0
	msgbox Trashburg_Text_DangerousIfYouDontHavePokemon, MSGBOX_DEFAULT
	closemessage
	return

Trashburg_Movement_TwinApproachPlayerLeft:
	face_right
	delay_8
	disable_jump_landing_ground_effect
	jump_in_place_right
	delay_8
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_up
	walk_fast_up
	walk_fast_left
	face_down
	step_end

Trashburg_Movement_TwinPushPlayerFromRoute:
	walk_down
	step_end

Trashburg_Movement_TwinReturnLeft:
	walk_right
	walk_down
	walk_down
	walk_left
	walk_left
	walk_left
	walk_up
	walk_in_place_faster_down
	step_end

Trashburg_Movement_PushPlayerBackFromRoute:
	lock_facing_direction
	walk_down
	unlock_facing_direction
	step_end

Trashburg_EventScript_NeedPokemonTriggerRight::
	lockall
	applymovement LOCALID_TRASHBURG_TWIN, Trashburg_Movement_TwinApproachPlayerRight
	waitmovement 0
	call Trashburg_EventScript_DangerousWithoutPokemon
	applymovement LOCALID_TRASHBURG_TWIN, Trashburg_Movement_TwinReturnRight
	waitmovement 0
	releaseall
	end

Trashburg_Movement_TwinApproachPlayerRight:
	face_right
	delay_8
	disable_jump_landing_ground_effect
	jump_in_place_right
	delay_8
	walk_fast_right
	walk_fast_right
	walk_fast_up
	walk_fast_up
	walk_fast_right
	face_down
	step_end

Trashburg_Movement_TwinReturnRight:
	walk_left
	walk_down
	walk_left
	walk_left
	walk_in_place_faster_down
	step_end

Trashburg_EventScript_GoSaveFrankTrigger::
	lockall
	applymovement LOCALID_TRASHBURG_TWIN, Common_Movement_WalkInPlaceFasterRight
	waitmovement 0
	applymovement LOCALID_PLAYER, Common_Movement_WalkInPlaceFasterLeft
	waitmovement 0
	special GetPlayerBigGuyGirlString
	msgbox Trashburg_Text_CanYouGoSeeWhatsHappening, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_TRASHBURG_TWIN, Common_Movement_FaceOriginalDirection
	waitmovement 0
	setvar VAR_TRASHBURG_STATE, 2
	releaseall
	end

Trashburg_EventScript_TownSign::
	msgbox Trashburg_Text_TownSign, MSGBOX_SIGN
	end

Trashburg_EventScript_FranksLabSign::
	msgbox Trashburg_Text_ProfFranksLab, MSGBOX_SIGN
	end

Trashburg_EventScript_BrendansHouseSign::
	lockall
	call Trashburg_EventScript_PlayersHouseSignMale
	releaseall
	end

Trashburg_EventScript_PlayersHouseSignMale::
	msgbox Trashburg_Text_PlayersHouse, MSGBOX_DEFAULT
	return

Trashburg_EventScript_MaysHouseSign::
	lockall
	call Trashburg_EventScript_FranksHouseSignMale
	releaseall
	end

Trashburg_EventScript_FranksHouseSignMale::
	msgbox Trashburg_Text_ProfFranksHouse, MSGBOX_DEFAULT
	return

Trashburg_EventScript_GiveRunningShoesTrigger0::
	lockall
	setvar VAR_0x8008, 0
	setobjectxy LOCALID_TRASHBURG_MOM, 10, 9
	goto Trashburg_EventScript_GiveRunningShoesTrigger
	end

Trashburg_EventScript_GiveRunningShoesTrigger1::
	lockall
	setvar VAR_0x8008, 1
	setobjectxy LOCALID_TRASHBURG_MOM, 11, 9
	goto Trashburg_EventScript_GiveRunningShoesTrigger
	end

Trashburg_EventScript_GiveRunningShoesTrigger2::
	lockall
	setvar VAR_0x8008, 2
	goto Trashburg_EventScript_GiveRunningShoesTrigger
	end

Trashburg_EventScript_GiveRunningShoesTrigger3::
	lockall
	setvar VAR_0x8008, 3
	goto Trashburg_EventScript_GiveRunningShoesTrigger
	end

Trashburg_EventScript_GiveRunningShoesTrigger4::
	lockall
	setvar VAR_0x8008, 4
	goto Trashburg_EventScript_GiveRunningShoesTrigger
	end

Trashburg_EventScript_GiveRunningShoesTrigger5::
	lockall
	setvar VAR_0x8008, 5
	goto Trashburg_EventScript_GiveRunningShoesTrigger
	end

Trashburg_EventScript_GiveRunningShoesTrigger::
	call  Trashburg_EventScript_MomNoticePlayerMale
	call  Trashburg_EventScript_SetHomeDoorCoordsMale
	msgbox Trashburg_Text_WaitPlayer, MSGBOX_DEFAULT
	closemessage
	call Trashburg_EventScript_MomApproachPlayerMale
	call Trashburg_EventScript_GiveRunningShoes
	call Trashburg_EventScript_MomReturnHomeMale
	goto Trashburg_EventScript_SetReceivedRunningShoes
	end

Trashburg_EventScript_SetHomeDoorCoordsMale::
	setvar VAR_0x8009, 5
	setvar VAR_0x800A, 8
	return

Trashburg_EventScript_MomNoticePlayerMale::
	applymovement LOCALID_TRASHBURG_MOM, Common_Movement_WalkInPlaceFasterRight
	waitmovement 0
	return

Trashburg_EventScript_MomApproachPlayerMale::
	call_if_eq VAR_0x8008, 0, Trashburg_EventScript_MomApproachPlayer0
	call_if_eq VAR_0x8008, 1, Trashburg_EventScript_MomApproachPlayer1
	call_if_eq VAR_0x8008, 2, Trashburg_EventScript_MomApproachPlayerMale2
	call_if_eq VAR_0x8008, 3, Trashburg_EventScript_MomApproachPlayerMale3
	call_if_eq VAR_0x8008, 4, Trashburg_EventScript_MomApproachPlayerMale4
	call_if_eq VAR_0x8008, 5, Trashburg_EventScript_MomApproachPlayerMale5
	return

Trashburg_EventScript_MomApproachPlayer0::
	applymovement LOCALID_PLAYER, Common_Movement_WalkInPlaceFasterDown
	waitmovement 0
	applymovement LOCALID_TRASHBURG_MOM, Trashburg_Movement_MomApproachPlayer0
	waitmovement 0
	return

Trashburg_EventScript_MomApproachPlayer1::
	applymovement LOCALID_PLAYER, Common_Movement_WalkInPlaceFasterDown
	waitmovement 0
	applymovement LOCALID_TRASHBURG_MOM, Trashburg_Movement_MomApproachPlayer1
	waitmovement 0
	return

Trashburg_EventScript_MomApproachPlayerMale2::
	applymovement LOCALID_PLAYER, Common_Movement_WalkInPlaceFasterLeft
	waitmovement 0
	applymovement LOCALID_TRASHBURG_MOM, Trashburg_Movement_MomApproachPlayerMale2
	waitmovement 0
	return

Trashburg_EventScript_MomApproachPlayerMale3::
	applymovement LOCALID_PLAYER, Common_Movement_WalkInPlaceFasterLeft
	waitmovement 0
	applymovement LOCALID_TRASHBURG_MOM, Trashburg_Movement_MomApproachPlayerMale3
	waitmovement 0
	return

Trashburg_EventScript_MomApproachPlayerMale4::
	applymovement LOCALID_PLAYER, Common_Movement_WalkInPlaceFasterLeft
	waitmovement 0
	applymovement LOCALID_TRASHBURG_MOM, Trashburg_Movement_MomApproachPlayerMale4
	waitmovement 0
	return

Trashburg_EventScript_MomApproachPlayerMale5::
	applymovement LOCALID_PLAYER, Common_Movement_WalkInPlaceFasterLeft
	waitmovement 0
	applymovement LOCALID_TRASHBURG_MOM, Trashburg_Movement_MomApproachPlayerMale5
	waitmovement 0
	return

Trashburg_EventScript_MomReturnHomeMale::
	call_if_eq VAR_0x8008, 0, Trashburg_EventScript_MomReturnHome0
	call_if_eq VAR_0x8008, 1, Trashburg_EventScript_MomReturnHome1
	call_if_eq VAR_0x8008, 2, Trashburg_EventScript_MomReturnHomeMale2
	call_if_eq VAR_0x8008, 3, Trashburg_EventScript_MomReturnHomeMale3
	call_if_eq VAR_0x8008, 4, Trashburg_EventScript_MomReturnHomeMale4
	call_if_eq VAR_0x8008, 5, Trashburg_EventScript_MomReturnHomeMale5
	return

Trashburg_EventScript_MomReturnHome0::
	applymovement LOCALID_TRASHBURG_MOM, Trashburg_Movement_MomReturnHome0
	waitmovement 0
	return

Trashburg_EventScript_MomReturnHome1::
	applymovement LOCALID_TRASHBURG_MOM, Trashburg_Movement_MomReturnHome1
	waitmovement 0
	return

Trashburg_EventScript_MomReturnHomeMale2::
	applymovement LOCALID_TRASHBURG_MOM, Trashburg_Movement_MomReturnHomeMale2
	waitmovement 0
	opendoor VAR_0x8009, VAR_0x800A
	waitdooranim
	applymovement LOCALID_TRASHBURG_MOM, Trashburg_Movement_MomExitThroughDoor
	waitmovement 0
	hideobjectat LOCALID_TRASHBURG_MOM, MAP_TRASHBURG
	closedoor VAR_0x8009, VAR_0x800A
	waitdooranim
	return

Trashburg_EventScript_MomReturnHomeMale3::
	applymovement LOCALID_TRASHBURG_MOM, Trashburg_Movement_MomReturnHomeMale3
	waitmovement 0
	opendoor VAR_0x8009, VAR_0x800A
	waitdooranim
	applymovement LOCALID_TRASHBURG_MOM, Trashburg_Movement_MomExitThroughDoor
	waitmovement 0
	hideobjectat LOCALID_TRASHBURG_MOM, MAP_TRASHBURG
	closedoor VAR_0x8009, VAR_0x800A
	waitdooranim
	return

Trashburg_EventScript_MomReturnHomeMale4::
	applymovement LOCALID_TRASHBURG_MOM, Trashburg_Movement_MomReturnHomeMale4
	waitmovement 0
	opendoor VAR_0x8009, VAR_0x800A
	waitdooranim
	applymovement LOCALID_TRASHBURG_MOM, Trashburg_Movement_MomExitThroughDoor
	waitmovement 0
	hideobjectat LOCALID_TRASHBURG_MOM, MAP_TRASHBURG
	closedoor VAR_0x8009, VAR_0x800A
	waitdooranim
	return

Trashburg_EventScript_MomReturnHomeMale5::
	applymovement LOCALID_TRASHBURG_MOM, Trashburg_Movement_MomReturnHomeMale5
	waitmovement 0
	opendoor VAR_0x8009, VAR_0x800A
	waitdooranim
	applymovement LOCALID_TRASHBURG_MOM, Trashburg_Movement_MomExitThroughDoor
	waitmovement 0
	hideobjectat LOCALID_TRASHBURG_MOM, MAP_TRASHBURG
	closedoor VAR_0x8009, VAR_0x800A
	waitdooranim
	return

Trashburg_Movement_MomApproachPlayer0:
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	step_end

Trashburg_Movement_MomApproachPlayer1:
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	step_end

Trashburg_Movement_MomApproachPlayerMale2:
	walk_right
	walk_right
	walk_right
	walk_right
	step_end

Trashburg_Movement_MomApproachPlayerMale3:
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	step_end

Trashburg_Movement_MomApproachPlayerMale4:
	walk_right
	walk_right
	step_end

Trashburg_Movement_MomApproachPlayerMale5:
	walk_right
	walk_right
	walk_right
	step_end

Trashburg_Movement_MomReturnHome0:
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	step_end

Trashburg_Movement_MomReturnHome1:
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	step_end

Trashburg_Movement_MomReturnHomeMale2:
	walk_left
	walk_left
	walk_left
	walk_left
	walk_in_place_faster_up
	step_end

Trashburg_Movement_MomReturnHomeMale3:
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_in_place_faster_up
	step_end

Trashburg_Movement_MomReturnHomeMale4:
	walk_left
	walk_left
	walk_in_place_faster_up
	step_end

Trashburg_Movement_MomReturnHomeMale5:
	walk_left
	walk_left
	walk_left
	walk_in_place_faster_up
	step_end

Trashburg_Movement_MomExitThroughDoor:
	walk_up
	step_end

Trashburg_EventScript_Mom::
	lock
	faceplayer
	call Trashburg_EventScript_SetHomeDoorCoordsMale
	call Trashburg_EventScript_GiveRunningShoes
	applymovement LOCALID_TRASHBURG_MOM, Common_Movement_WalkInPlaceFasterUp
	waitmovement 0
	opendoor VAR_0x8009, VAR_0x800A
	waitdooranim
	applymovement LOCALID_TRASHBURG_MOM, Trashburg_Movement_MomExitThroughDoor
	waitmovement 0
	hideobjectat LOCALID_TRASHBURG_MOM, MAP_TRASHBURG
	closedoor VAR_0x8009, VAR_0x800A
	waitdooranim
	goto Trashburg_EventScript_SetReceivedRunningShoes
	end

Trashburg_EventScript_SetReceivedRunningShoes::
	removeobject LOCALID_TRASHBURG_MOM
	setflag FLAG_SYS_B_DASH
	setvar VAR_TRASHBURG_STATE, 4
	release
	end

Trashburg_EventScript_GiveRunningShoes::
	msgbox Trashburg_Text_WearTheseRunningShoes, MSGBOX_DEFAULT
	playfanfare MUS_OBTAIN_ITEM
	message Trashburg_Text_SwitchShoesWithRunningShoes
	waitfanfare
	waitmessage
	setflag FLAG_RECEIVED_RUNNING_SHOES
	msgbox Trashburg_Text_ExplainRunningShoes, MSGBOX_DEFAULT
	msgbox Trashburg_Text_TakeThisToo, MSGBOX_DEFAULT
	playfanfare MUS_OBTAIN_ITEM
	giveitem ITEM_EXP_SHARE
	waitfanfare
	msgbox Trashburg_Text_EXPShare, MSGBOX_DEFAULT
	msgbox Trashburg_Text_ComeHomeIfAnythingHappens, MSGBOX_DEFAULT
	closemessage
	delay 30
	return

Trashburg_Text_OurNewHomeLetsGoInside:
	.string "MOM: Oh good, you're still alive.\p"
	.string "Frank swore tying you down was safe,\n"
	.string "but I had a FEELING, Charlie.\p"
	.string "You could've died. I had a dream.\p"
	.string "Anyway, this is our new place.\n"
	.string "It’s not full of mold. Yet.\p"
	.string "It rains constantly. That’s not good.\p"
	.string "I think there's a mattress inside, but\n"
	.string "don’t touch the corners.\p"
	.string "Let’s just go. I need to sit down before\n"
	.string "my heart gives out.$"

Trashburg_Text_WaitPlayer:
	.string "MOM: Oh, my Charlie, WAIT!$"

Trashburg_Text_WearTheseRunningShoes:
	.string "MOM: There you are, my sweet boy.\p"
	.string "Frank said you were outside again\n"
	.string "touching wild garbage animals.\p"
	.string "You have one now? Oh God.\n"
	.string "Did it bite you?\p"
	.string "Anyway, here. New shoes!\n"
	.string "For running away, I hope.\p"
	.string "They’re clean. I wiped them down.\n"
	.string "Twice. Just to be safe.$"


Trashburg_Text_SwitchShoesWithRunningShoes:
	.string "{PLAYER} switched shoes with the\n"
	.string "RUNNING SHOES.$"

Trashburg_Text_ExplainRunningShoes:
	.string "MOM: The shoes came with paper but I\n"
	.string "threw it out. It had a smell.\p"
	.string "It’s probably fine.\n"
	.string "Just be careful, okay?\p"
	.string "Running’s dangerous.\n"
	.string "So is standing still. Just… be alert.$"

Trashburg_Text_ComeHomeIfAnythingHappens:
	.string "… … … … … … … …\n"
	.string "… … … … … … … …\p"
	.string "MOM: My Charlie has a Pokémon now...\p"
	.string "It’s happening. You’re leaving me.\n"
	.string "Ohh Charlie!\p"
	.string "I’m so proud. And terrified.\p"
	.string "If you get hurt, or arrested, just\n"
	.string "come home. Right away!\p"
	.string "I’ll go in, light a candle, and spin\n"
	.string "around.\p"
	.string "You’ll be safe that way.$"


Trashburg_Text_CanUsePCToStoreItems:
	.string "PCs are great. You can store Pokémon,\n"
	.string "your regrets, your medical records…\p"
	.string "Just don't check the 'Trash' folder.\n"
	.string "That's where Frank keeps secrets.$"


Trashburg_Text_FrankSpendsDaysInLab:
	.string "PROF. Frank said he's 'training rats\n"
	.string "for street combat and science.'\p"
	.string "I haven’t slept since Tuesday.\n"
	.string "I've been standing here in the rain.\p"
	.string "Please send help.$"


Trashburg_Text_IfYouGoInGrassPokemonWillJumpOut:
	.string "Yo! Hey! Don’t go in the grass!\p"
	.string "Those wild jawns out there are jacked\n"
	.string "up and real bitey.\p"
	.string "Like... feral-level aggressive.$"


Trashburg_Text_DangerousIfYouDontHavePokemon:
	.string "It’s dangerous out there\n" 
	.string "without a Pokémon.\p"
	.string "One time, Frank got chased\n"
	.string "by a Linoone.\p"
	.string "It took his shoe and ripped it apart!\n"
	.string "He hasn’t walked right since.$"

Trashburg_Text_CanYouGoSeeWhatsHappening:
	.string "Yo, uh, hi! So like… there’s something\n"
	.string "screaming in the grass over there.\p"
	.string "Sounds wet. And angry.\n"
	.string "I don’t have a Pokémon, so…\p"
	.string "Would you mind checking it out?\n"
	.string "If you die, I’ll deny we spoke.$"


Trashburg_Text_YouSavedFrank:
	.string "You saved PROF. Frank!\n"
	.string "Man, that guy owes you… like, a sandwich.$"

Trashburg_Text_GoodLuckCatchingPokemon:
	.string "MOM: Good luck catching Pokémon out there!\p"
	.string "$"

Trashburg_Text_TownSign:
	.string "TRASHBURG\n"
	.string "“Officially condemned,\l"
	.string "spiritually thriving.”$"

Trashburg_Text_ProfFranksLab:
	.string "PROF. FRANK'S POKéMON LAB$"

Trashburg_Text_PlayersHouse:
	.string "{PLAYER}'s HOUSE$"

Trashburg_Text_ProfFranksHouse:
	.string "MCPOYLE HOUSE$"

Trashburg_Text_FrankSomethingToShowYouAtLab:
	.string "PROF. Frank: Well, well, {PLAYER}!\n"
	.string "That was some top-tier\l"
	.string "Pokémon handling!\p"
	.string "I knew you had that... weird spark\n"
	.string "in you when I first saw you diggin’\l"
	.string "through trash.\p"
	.string "Hey, do you still got that Pokédex I\n"
	.string "gave you?\p"
	.string "Try not to trade it for glue.\p"
	.string "C’mon, I got somethin’ to show you\n"
	.string "back at the lab.\p"
	.string "Bring snacks!$"

Trashburg_Text_TakeThisToo:
	.string "Oh, and Charlie!\n"
	.string "I got you a little gift.$"


Trashburg_Text_EXPShare:
	.string "It’s called an EXP SHARE.\p"
	.string "I don’t really know how it works.\n"
	.string "I think it’s magic.\p"
	.string "It makes your little creatures…\n"
	.string "smarter!\p"
	.string "The man at the Mart says it's a new\n"
	.string "version too!\p"
	.string "It goes in a special pocket in your\n"
	.string "backpack, and all you have to do is turn\l"
	.string "it on!\p"
	.string "The old ones only helped one Pokémon.\n"
	.string "This one helps them all!\p"
	.string "You just turn it on and suddenly\n"
	.string "they’re all winners! You could use that.$"

Trashburg_EventScript_GoodLuck1::
	lockall
	addobject LOCALID_SCIENCEGUY
	setobjectxy LOCALID_SCIENCEGUY, 10, 8
	applymovement LOCALID_PLAYER, Common_Movement_ExclamationMark
	delay 8
	applymovement LOCALID_PLAYER, Common_Movement_WalkInPlaceFasterDown
	waitmovement 0
	applymovement LOCALID_SCIENCEGUY, Trashburg_Movement_WalkToPlayer1
	waitmovement 0
	msgbox Trashburg_Text_DayNightInfo, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_SCIENCEGUY, Trashburg_Movement_WalkAway1
	waitmovement 0
	removeobject LOCALID_SCIENCEGUY
	setvar VAR_TRASHBURG_STATE, 5
	releaseall
	end

Trashburg_EventScript_GoodLuck2::
	lockall
	addobject LOCALID_SCIENCEGUY
	setobjectxy LOCALID_SCIENCEGUY, 11, 8
	applymovement LOCALID_PLAYER, Common_Movement_ExclamationMark
	delay 8
	applymovement LOCALID_PLAYER, Common_Movement_WalkInPlaceFasterDown
	waitmovement 0
	applymovement LOCALID_SCIENCEGUY, Trashburg_Movement_WalkToPlayer2
	waitmovement 0
	msgbox Trashburg_Text_DayNightInfo, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_SCIENCEGUY, Trashburg_Movement_WalkAway2
	waitmovement 0
	removeobject LOCALID_SCIENCEGUY
	setflag FLAG_HIDE_DAYNIGHT_SCIENCEGUY
	setvar VAR_TRASHBURG_STATE, 5
	releaseall
	end	

Trashburg_Movement_WalkToPlayer1:
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	step_end

Trashburg_Movement_WalkToPlayer2:
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	step_end	

Trashburg_Movement_WalkAway1:
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	step_end

Trashburg_Movement_WalkAway2:
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	step_end	

Trashburg_Text_DayNightInfo:
	.string "Hey there, {PLAYER}!\n"
	.string "Good luck filling that POKéDEX!\p"
	.string "Quick PSA since Frank forgot...\p"
	.string "Day is 7am-7pm, Night is 7pm-7am.\p"
	.string "When the clock flips the spawns swap.\n"
	.string "Different Pokémon like to come out\l"
	.string "after dark.\p"
	.string "The time also changes evolution for\n"
	.string "some species.\p"
	.string "Some evolve one way by day, another\n"
	.string "by night, and others need special\l"
	.string "triggers.\p"
	.string "Want a specific outcome?\n"
	.string "Check the species’ rules and\l"
	.string "time it right.\p"
	.string "..... ..... .....\p"
	.string "Anyway..have a fun time.\p"
	.string "Don't go dyin out there too quick.$"
