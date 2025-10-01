WawaPark_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, WawaPark_OnTransition
	map_script MAP_SCRIPT_ON_FRAME_TABLE, WawaPark_OnFrame
	.byte 0

WawaPark_OnTransition:
	setflag FLAG_VISITED_WAWA_PARK
	call Common_EventScript_SetupRivalGfxId
	call_if_eq VAR_WAWA_PARK_CITY_STATE, 6, WawaPark_EventScript_HideMapNamePopup
	getplayerxy VAR_TEMP_0, VAR_TEMP_1
	goto_if_eq VAR_WAWA_PARK_CITY_STATE, 6, WawaPark_EventScript_PositionScientistForExit
	end

WawaPark_EventScript_PositionScientistForExit::
	goto_if_eq VAR_TEMP_0, 11, WawaPark_EventScript_PositionScientistLeftExit
	setobjectxyperm LOCALID_WAWA_PARK_SCIENTIST, 12, 15
	end

WawaPark_EventScript_PositionScientistLeftExit::
	setobjectxyperm LOCALID_WAWA_PARK_SCIENTIST, 11, 15
	end

WawaPark_EventScript_HideMapNamePopup::
	setflag FLAG_HIDE_MAP_NAME_POPUP
	return

WawaPark_OnFrame:
	map_script_2 VAR_WAWA_PARK_CITY_STATE, 6, WawaPark_EventScript_ScientistAddMatchCall
	.2byte 0

WawaPark_EventScript_ScientistAddMatchCall::
	lockall
	setvar VAR_ROUTE104_STATE, 1
	applymovement LOCALID_PLAYER, WawaPark_Movement_PlayerWalkDown
	waitmovement 0
	playse SE_EXIT
	delay 10
	addobject LOCALID_WAWA_PARK_SCIENTIST
	applymovement LOCALID_WAWA_PARK_SCIENTIST, WawaPark_Movement_ScientistApproachPlayer
	waitmovement 0
	playse SE_PIN
	applymovement LOCALID_WAWA_PARK_SCIENTIST, Common_Movement_ExclamationMark
	waitmovement 0
	applymovement LOCALID_WAWA_PARK_SCIENTIST, Common_Movement_Delay48
	waitmovement 0
	applymovement LOCALID_PLAYER, Common_Movement_WalkInPlaceFasterUp
	waitmovement 0
	applymovement LOCALID_WAWA_PARK_SCIENTIST, WawaPark_Movement_ScientistWalkInPlaceDown
	waitmovement 0
	msgbox WawaPark_Text_DevelopedNewPokenavFeature, MSGBOX_DEFAULT
	closemessage
	setflag FLAG_HAS_MATCH_CALL
	applymovement LOCALID_WAWA_PARK_SCIENTIST, Common_Movement_WalkInPlaceFasterLeft
	waitmovement 0
	playse SE_CLICK
	delay 10
	playse SE_CLICK
	delay 10
	playse SE_CLICK
	delay 10
	playse SE_CLICK
	delay 20
	applymovement LOCALID_WAWA_PARK_SCIENTIST, Common_Movement_WalkInPlaceFasterDown
	waitmovement 0
	msgbox WawaPark_Text_AddedMatchCallPleaseCallMrStone, MSGBOX_DEFAULT
	closemessage
	delay 20
	goto WawaPark_EventScript_MatchCallTutorial

WawaPark_EventScript_PleaseSelectPokenav::
	msgbox WawaPark_Text_PleaseSelectPokenav, MSGBOX_DEFAULT
	closemessage
	delay 10
	goto WawaPark_EventScript_MatchCallTutorial

WawaPark_EventScript_MatchCallTutorial::
	setflag FLAG_ADDED_MATCH_CALL_TO_POKENAV
	special ScriptMenu_CreateStartMenuForPokenavTutorial
	waitstate
	switch VAR_RESULT
	case 0, WawaPark_EventScript_PleaseSelectPokenav
	case 1, WawaPark_EventScript_PleaseSelectPokenav
	case 2, WawaPark_EventScript_PleaseSelectPokenav
	case 4, WawaPark_EventScript_PleaseSelectPokenav
	case 5, WawaPark_EventScript_PleaseSelectPokenav
	case 6, WawaPark_EventScript_PleaseSelectPokenav
	case 7, WawaPark_EventScript_PleaseSelectPokenav
	case MULTI_B_PRESSED, WawaPark_EventScript_PleaseSelectPokenav
	special OpenPokenavForTutorial
	waitstate
	delay 20
	msgbox WawaPark_Text_IdBetterGetBackToWork, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_WAWA_PARK_SCIENTIST, WawaPark_Movement_ScientistLeave
	waitmovement 0
	playse SE_EXIT
	removeobject LOCALID_WAWA_PARK_SCIENTIST
	setflag FLAG_HIDE_WAWA_PARK_SCIENTIST
	setvar VAR_WAWA_PARK_CITY_STATE, 7
	clearflag FLAG_HIDE_MAP_NAME_POPUP
	releaseall
	end

WawaPark_Movement_ScientistWalkInPlaceDown:
	walk_in_place_down
	step_end

WawaPark_Movement_PlayerWalkDown:
	walk_down
	step_end

WawaPark_Movement_ScientistApproachPlayer:
	walk_down
	delay_16
	step_end

@ Unused
WawaPark_Movement_ScientistWalkAroundPlayer:
	delay_16
	walk_left
	walk_down
	walk_down
	walk_right
	walk_in_place_faster_up
	delay_16
	step_end

WawaPark_Movement_ScientistLeave:
	walk_up
	step_end

WawaPark_EventScript_FatMan::
	lock
	faceplayer
	goto_if_set FLAG_DEVON_GOODS_STOLEN, WawaPark_EventScript_FatManSawGrunt
	msgbox WawaPark_Text_WeShortenItToDevon, MSGBOX_DEFAULT
	release
	end

WawaPark_EventScript_FatManSawGrunt::
	msgbox WawaPark_Text_SneakyLookingManWentAroundCorner, MSGBOX_DEFAULT
	release
	end

WawaPark_EventScript_DevonEmployee2::
	lock
	faceplayer
	msgbox WawaPark_Text_YoureNewAroundHere, MSGBOX_DEFAULT
	release
	end

WawaPark_EventScript_Woman::
	msgbox WawaPark_Text_GymLeaderIsntEasyWithFire, MSGBOX_NPC
	end

WawaPark_EventScript_Man1::
	lock
	faceplayer
	goto_if_set FLAG_BADGE01_GET, WawaPark_EventScript_Man1HaveBadge
	msgbox WawaPark_Text_HaveYouChallengedGym, MSGBOX_DEFAULT
	release
	end

WawaPark_EventScript_Man1HaveBadge::
	msgbox WawaPark_Text_HeyThatsWawaParksGymBadge, MSGBOX_DEFAULT
	release
	end

WawaPark_EventScript_Boy2::
	lock
	faceplayer
	goto_if_set FLAG_RECEIVED_POKENAV, WawaPark_EventScript_Boy2BrineyLeftTunnel
	msgbox WawaPark_Text_MrBrineyWalksInTheTunnel, MSGBOX_DEFAULT
	release
	end

WawaPark_EventScript_Boy2BrineyLeftTunnel::
	msgbox WawaPark_Text_MrBrineyLovesPeeko, MSGBOX_DEFAULT
	release
	end

WawaPark_EventScript_Twin::
	msgbox WawaPark_Text_WowYouHavePokemon, MSGBOX_NPC
	end

WawaPark_EventScript_NinjaBoy::
	msgbox WawaPark_Text_CatchRarePokemonIfIGoToSchool, MSGBOX_SIGN
	end

WawaPark_EventScript_TunnelSign::
	msgbox WawaPark_Text_TunnelNearingCompletion, MSGBOX_SIGN
	end

WawaPark_EventScript_DevonCorpSign::
	msgbox WawaPark_Text_DevonCorpSign, MSGBOX_SIGN
	end

WawaPark_EventScript_GymSign::
	msgbox WawaPark_Text_GymSign, MSGBOX_SIGN
	end

@ Unused
WawaPark_EventScript_DevonCorpBranchOfficeSign::
	msgbox WawaPark_Text_DevonCorpBranchOfficeSign, MSGBOX_SIGN
	end

WawaPark_EventScript_CitySign::
	msgbox WawaPark_Text_CitySign, MSGBOX_SIGN
	end

WawaPark_EventScript_TrainersSchoolSign::
	msgbox WawaPark_Text_TrainersSchoolSign, MSGBOX_SIGN
	end

WawaPark_EventScript_CuttersHouseSign::
	msgbox WawaPark_Text_CuttersHouse, MSGBOX_SIGN
	end

WawaPark_EventScript_LittleBoy::
	lock
	faceplayer
	msgbox WawaPark_Text_PokemonCanChangeLookFromExp, MSGBOX_DEFAULT
	applymovement LOCALID_WAWA_PARK_LITTLE_BOY, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

WawaPark_EventScript_LittleGirl::
	lock
	faceplayer
	msgbox WawaPark_Text_PokemonChangeShape, MSGBOX_DEFAULT
	applymovement LOCALID_WAWA_PARK_LITTLE_GIRL, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

WawaPark_EventScript_Man2::
	lock
	faceplayer
	msgbox WawaPark_Text_TradePokemonGrowFast, MSGBOX_DEFAULT
	release
	end

WawaPark_EventScript_StolenGoodsTrigger0::
	lockall
	setobjectxyperm LOCALID_WAWA_PARK_DEVON_EMPLOYEE, 14, 21
	setobjectmovementtype LOCALID_WAWA_PARK_DEVON_EMPLOYEE, MOVEMENT_TYPE_FACE_RIGHT
	setvar VAR_0x8004, 0
	goto WawaPark_EventScript_StolenGoodsScene
	end

WawaPark_EventScript_StolenGoodsTrigger1::
	lockall
	setobjectxyperm LOCALID_WAWA_PARK_DEVON_EMPLOYEE, 14, 21
	setobjectmovementtype LOCALID_WAWA_PARK_DEVON_EMPLOYEE, MOVEMENT_TYPE_FACE_RIGHT
	setvar VAR_0x8004, 1
	goto WawaPark_EventScript_StolenGoodsScene
	end

WawaPark_EventScript_StolenGoodsTrigger2::
	lockall
	setobjectxyperm LOCALID_WAWA_PARK_DEVON_EMPLOYEE, 14, 21
	setobjectmovementtype LOCALID_WAWA_PARK_DEVON_EMPLOYEE, MOVEMENT_TYPE_FACE_RIGHT
	setvar VAR_0x8004, 2
	goto WawaPark_EventScript_StolenGoodsScene
	end

WawaPark_EventScript_StolenGoodsTrigger3::
	lockall
	setobjectxyperm LOCALID_WAWA_PARK_DEVON_EMPLOYEE, 14, 21
	setobjectmovementtype LOCALID_WAWA_PARK_DEVON_EMPLOYEE, MOVEMENT_TYPE_FACE_RIGHT
	setvar VAR_0x8004, 3
	goto WawaPark_EventScript_StolenGoodsScene
	end

WawaPark_EventScript_StolenGoodsTrigger4::
	lockall
	setobjectxyperm LOCALID_WAWA_PARK_DEVON_EMPLOYEE, 14, 21
	setobjectmovementtype LOCALID_WAWA_PARK_DEVON_EMPLOYEE, MOVEMENT_TYPE_FACE_RIGHT
	setvar VAR_0x8004, 4
	goto WawaPark_EventScript_StolenGoodsScene
	end

WawaPark_EventScript_StolenGoodsScene::
	msgbox WawaPark_Text_OutOfTheWay, MSGBOX_DEFAULT
	closemessage
	playbgm MUS_ENCOUNTER_AQUA, FALSE
	addobject LOCALID_WAWA_PARK_GRUNT
	addobject LOCALID_WAWA_PARK_DEVON_EMPLOYEE
	applymovement LOCALID_WAWA_PARK_GRUNT, WawaPark_Movement_GruntEscape
	waitmovement 0
	removeobject LOCALID_WAWA_PARK_GRUNT
	applymovement LOCALID_WAWA_PARK_DEVON_EMPLOYEE, WawaPark_Movement_EmployeeChaseGrunt1
	waitmovement 0
	msgbox WawaPark_Text_WaitDontTakeMyGoods, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_WAWA_PARK_DEVON_EMPLOYEE, WawaPark_Movement_EmployeeChaseGrunt2
	waitmovement 0
	fadedefaultbgm
	removeobject LOCALID_WAWA_PARK_DEVON_EMPLOYEE
	setobjectxyperm LOCALID_WAWA_PARK_DEVON_EMPLOYEE, 30, 10
	clearflag FLAG_HIDE_WAWA_PARK_DEVON_EMPLOYEE_1
	setflag FLAG_DEVON_GOODS_STOLEN
	setvar VAR_WAWA_PARK_CITY_STATE, 2
	setvar VAR_RUSTURF_TUNNEL_STATE, 2
	setvar VAR_ROUTE116_STATE, 1
	clearflag FLAG_HIDE_ROUTE_116_MR_BRINEY
	clearflag FLAG_HIDE_RUSTURF_TUNNEL_PEEKO
	clearflag FLAG_HIDE_RUSTURF_TUNNEL_AQUA_GRUNT
	setflag FLAG_HIDE_BRINEYS_HOUSE_MR_BRINEY
	setflag FLAG_HIDE_BRINEYS_HOUSE_PEEKO
	releaseall
	end

@ Unused
WawaPark_EventScript_ShadyCharacterTookOff::
	msgbox WawaPark_Text_ShadyCharacterTookOffTowardsTunnel, MSGBOX_DEFAULT
	return

@ Unused
WawaPark_EventScript_YouGotItThankYou::
	msgbox WawaPark_Text_YouGotItThankYou, MSGBOX_DEFAULT
	return

@ Unknown, unused employee movements. Based on the differences in movement theyre for approaching an object (probably the player) in different positions
WawaPark_EventScript_EmployeeApproachUp::
	applymovement LOCALID_WAWA_PARK_DEVON_EMPLOYEE, WawaPark_Movement_EmployeeApproachUp
	waitmovement 0
	return

@ Unused, see above
WawaPark_EventScript_EmployeeApproachLeft::
	applymovement LOCALID_WAWA_PARK_DEVON_EMPLOYEE, WawaPark_Movement_EmployeeApproachLeft
	waitmovement 0
	return

@ Unused, see above
WawaPark_EventScript_EmployeeApproachRight::
	applymovement LOCALID_WAWA_PARK_DEVON_EMPLOYEE, WawaPark_Movement_EmployeeApproachRight
	waitmovement 0
	return

@ Unused, see above
WawaPark_EventScript_EmployeeApproachDown::
	applymovement LOCALID_WAWA_PARK_DEVON_EMPLOYEE, WawaPark_Movement_EmployeeApproachDown
	waitmovement 0
	return

@ Unused, similar movement to the above scripts
WawaPark_EventScript_EmployeeApproachPlayerFar::
	applymovement LOCALID_WAWA_PARK_DEVON_EMPLOYEE, WawaPark_Movement_EmployeeApproachPlayerFar
	waitmovement 0
	applymovement LOCALID_PLAYER, Common_Movement_WalkInPlaceFasterUp
	waitmovement 0
	return

@ Unused
WawaPark_Movement_GruntEscapeExtended:
	walk_faster_right
	walk_faster_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	step_end

WawaPark_Movement_GruntEscape:
	walk_faster_right
	walk_faster_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	step_end

WawaPark_Movement_EmployeeChaseGrunt1:
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_in_place_faster_up
	step_end

WawaPark_Movement_EmployeeChaseGrunt2:
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	step_end

@ Functionally unused
WawaPark_Movement_EmployeeApproachUp:
	walk_down
	walk_right
	walk_right
	step_end

@ Functionally unused
WawaPark_Movement_EmployeeApproachLeft:
	walk_down
	walk_down
	walk_right
	walk_right
	step_end

@ Functionally unused
WawaPark_Movement_EmployeeApproachRight:
	walk_down
	walk_down
	walk_right
	walk_right
	step_end

@ Functionally unused
WawaPark_Movement_EmployeeApproachDown:
	walk_down
	walk_down
	walk_down
	walk_right
	walk_right
	step_end

@ Functionally unused
WawaPark_Movement_EmployeeApproachPlayerFar:
	walk_down
	walk_down
	walk_down
	walk_right
	walk_right
	walk_right
	walk_in_place_faster_down
	step_end

WawaPark_EventScript_DevonEmployee1::
	lock
	faceplayer
	goto_if_set FLAG_RECOVERED_DEVON_GOODS, WawaPark_EventScript_ReturnGoodsSpokeToEmployee
	msgbox WawaPark_Text_ShadyCharacterTookOffTowardsTunnel, MSGBOX_DEFAULT
	release
	end

WawaPark_EventScript_ReturnGoodsSpokeToEmployee::
	waitse
	setvar VAR_TEMP_1, 4
	goto WawaPark_EventScript_ReturnGoods
	end

WawaPark_EventScript_HelpGetGoodsTrigger0::
	lockall
	setvar VAR_TEMP_1, 0
	goto WawaPark_EventScript_EmployeeAskToGetGoods
	end

WawaPark_EventScript_HelpGetGoodsTrigger1::
	lockall
	setvar VAR_TEMP_1, 1
	goto WawaPark_EventScript_EmployeeAskToGetGoods
	end

WawaPark_EventScript_HelpGetGoodsTrigger2::
	lockall
	setvar VAR_TEMP_1, 2
	goto WawaPark_EventScript_EmployeeAskToGetGoods
	end

WawaPark_EventScript_HelpGetGoodsTrigger3::
	lockall
	setvar VAR_TEMP_1, 3
	goto WawaPark_EventScript_EmployeeAskToGetGoods
	end

WawaPark_EventScript_EmployeeAskToGetGoods::
	call_if_eq VAR_TEMP_1, 0, WawaPark_EventScript_EmployeeFacePlayerUp1
	call_if_eq VAR_TEMP_1, 1, WawaPark_EventScript_EmployeeFacePlayerLeft1
	call_if_eq VAR_TEMP_1, 2, WawaPark_EventScript_EmployeeFacePlayerDown1
	call_if_eq VAR_TEMP_1, 3, WawaPark_EventScript_EmployeeApproachPlayerDown1
	setflag FLAG_INTERACTED_WITH_DEVON_EMPLOYEE_GOODS_STOLEN
	setvar VAR_WAWA_PARK_CITY_STATE, 3
	copyobjectxytoperm LOCALID_WAWA_PARK_DEVON_EMPLOYEE
	msgbox WawaPark_Text_HelpMeIWasRobbed, MSGBOX_DEFAULT
	releaseall
	end

@ The below movement scripts are either partially or fully duplicated by the movement scripts when the player returns the goods
WawaPark_EventScript_EmployeeFacePlayerUp1::
	applymovement LOCALID_WAWA_PARK_DEVON_EMPLOYEE, Common_Movement_WalkInPlaceFasterUp
	waitmovement 0
	playse SE_PIN
	applymovement LOCALID_WAWA_PARK_DEVON_EMPLOYEE, Common_Movement_ExclamationMark
	waitmovement 0
	applymovement LOCALID_WAWA_PARK_DEVON_EMPLOYEE, Common_Movement_Delay48
	waitmovement 0
	applymovement LOCALID_PLAYER, Common_Movement_WalkInPlaceFasterDown
	waitmovement 0
	return

WawaPark_EventScript_EmployeeFacePlayerLeft1::
	applymovement LOCALID_WAWA_PARK_DEVON_EMPLOYEE, Common_Movement_WalkInPlaceFasterLeft
	waitmovement 0
	playse SE_PIN
	applymovement LOCALID_WAWA_PARK_DEVON_EMPLOYEE, Common_Movement_ExclamationMark
	waitmovement 0
	applymovement LOCALID_WAWA_PARK_DEVON_EMPLOYEE, Common_Movement_Delay48
	waitmovement 0
	applymovement LOCALID_PLAYER, Common_Movement_FaceRight
	waitmovement 0
	return

WawaPark_EventScript_EmployeeFacePlayerDown1::
	applymovement LOCALID_WAWA_PARK_DEVON_EMPLOYEE, Common_Movement_WalkInPlaceFasterDown
	waitmovement 0
	playse SE_PIN
	applymovement LOCALID_WAWA_PARK_DEVON_EMPLOYEE, Common_Movement_ExclamationMark
	waitmovement 0
	applymovement LOCALID_WAWA_PARK_DEVON_EMPLOYEE, Common_Movement_Delay48
	waitmovement 0
	applymovement LOCALID_PLAYER, Common_Movement_WalkInPlaceFasterUp
	waitmovement 0
	return

WawaPark_EventScript_EmployeeApproachPlayerDown1::
	applymovement LOCALID_WAWA_PARK_DEVON_EMPLOYEE, Common_Movement_WalkInPlaceFasterDown
	waitmovement 0
	playse SE_PIN
	applymovement LOCALID_WAWA_PARK_DEVON_EMPLOYEE, Common_Movement_ExclamationMark
	waitmovement 0
	applymovement LOCALID_WAWA_PARK_DEVON_EMPLOYEE, Common_Movement_Delay48
	waitmovement 0
	applymovement LOCALID_WAWA_PARK_DEVON_EMPLOYEE, WawaPark_Movement_EmployeeApproachPlayerDown
	waitmovement 0
	applymovement LOCALID_PLAYER, Common_Movement_WalkInPlaceFasterUp
	waitmovement 0
	return

WawaPark_Movement_EmployeeApproachPlayerDown:
	walk_down
	step_end

WawaPark_EventScript_ReturnGoodsTrigger0::
	lockall
	setvar VAR_TEMP_1, 0
	goto WawaPark_EventScript_ReturnGoods
	end

WawaPark_EventScript_ReturnGoodsTrigger1::
	lockall
	setvar VAR_TEMP_1, 1
	goto WawaPark_EventScript_ReturnGoods
	end

WawaPark_EventScript_ReturnGoodsTrigger2::
	lockall
	setvar VAR_TEMP_1, 2
	goto WawaPark_EventScript_ReturnGoods
	end

WawaPark_EventScript_ReturnGoodsTrigger3::
	lockall
	setvar VAR_TEMP_1, 3
	goto WawaPark_EventScript_ReturnGoods
	end

WawaPark_EventScript_ReturnGoods::
	call_if_eq VAR_TEMP_1, 0, WawaPark_EventScript_EmployeeFacePlayerUp2
	call_if_eq VAR_TEMP_1, 1, WawaPark_EventScript_EmployeeFacePlayerLeft2
	call_if_eq VAR_TEMP_1, 2, WawaPark_EventScript_EmployeeFacePlayerDown2
	call_if_eq VAR_TEMP_1, 3, WawaPark_EventScript_EmployeeApproachPlayerDown2
	call_if_eq VAR_TEMP_1, 4, WawaPark_EventScript_EmployeeFacePlayerRight
	msgbox WawaPark_Text_YouGotItThankYou, MSGBOX_DEFAULT
	giveitem ITEM_GREAT_BALL
	call_if_eq VAR_RESULT, FALSE, WawaPark_EventScript_BagFull
	msgbox WawaPark_Text_PleaseComeWithMe, MSGBOX_DEFAULT
	closemessage
	setflag FLAG_RETURNED_DEVON_GOODS
	setflag FLAG_HIDE_WAWA_PARK_DEVON_EMPLOYEE_1
	setvar VAR_WAWA_PARK_CITY_STATE, 5
	delay 30
	warp MAP_WAWA_PARK_DEVON_CORP_3F, 2, 2
	waitstate
	releaseall
	end

WawaPark_EventScript_BagFull::
	msgbox WawaPark_Text_YoureLoadedWithItems, MSGBOX_DEFAULT
	return

WawaPark_EventScript_EmployeeFacePlayerUp2::
	applymovement LOCALID_WAWA_PARK_DEVON_EMPLOYEE, Common_Movement_WalkInPlaceFasterUp
	waitmovement 0
	playse SE_PIN
	applymovement LOCALID_WAWA_PARK_DEVON_EMPLOYEE, Common_Movement_ExclamationMark
	waitmovement 0
	applymovement LOCALID_WAWA_PARK_DEVON_EMPLOYEE, Common_Movement_Delay48
	waitmovement 0
	applymovement LOCALID_PLAYER, Common_Movement_WalkInPlaceFasterDown
	waitmovement 0
	return

WawaPark_EventScript_EmployeeFacePlayerLeft2::
	applymovement LOCALID_WAWA_PARK_DEVON_EMPLOYEE, Common_Movement_WalkInPlaceFasterRight
	waitmovement 0
	playse SE_PIN
	applymovement LOCALID_WAWA_PARK_DEVON_EMPLOYEE, Common_Movement_ExclamationMark
	waitmovement 0
	applymovement LOCALID_WAWA_PARK_DEVON_EMPLOYEE, Common_Movement_Delay48
	waitmovement 0
	applymovement LOCALID_PLAYER, Common_Movement_FaceLeft
	waitmovement 0
	return

WawaPark_EventScript_EmployeeFacePlayerDown2::
	applymovement LOCALID_WAWA_PARK_DEVON_EMPLOYEE, Common_Movement_WalkInPlaceFasterDown
	waitmovement 0
	playse SE_PIN
	applymovement LOCALID_WAWA_PARK_DEVON_EMPLOYEE, Common_Movement_ExclamationMark
	waitmovement 0
	applymovement LOCALID_WAWA_PARK_DEVON_EMPLOYEE, Common_Movement_Delay48
	waitmovement 0
	applymovement LOCALID_PLAYER, Common_Movement_WalkInPlaceFasterUp
	waitmovement 0
	return

WawaPark_EventScript_EmployeeApproachPlayerDown2::
	applymovement LOCALID_WAWA_PARK_DEVON_EMPLOYEE, Common_Movement_WalkInPlaceFasterDown
	waitmovement 0
	playse SE_PIN
	applymovement LOCALID_WAWA_PARK_DEVON_EMPLOYEE, Common_Movement_ExclamationMark
	waitmovement 0
	applymovement LOCALID_WAWA_PARK_DEVON_EMPLOYEE, Common_Movement_Delay48
	waitmovement 0
	applymovement LOCALID_WAWA_PARK_DEVON_EMPLOYEE, WawaPark_Movement_EmployeeApproachPlayerDown
	waitmovement 0
	applymovement LOCALID_PLAYER, Common_Movement_WalkInPlaceFasterUp
	waitmovement 0
	return

WawaPark_EventScript_EmployeeFacePlayerRight::
	applymovement LOCALID_WAWA_PARK_DEVON_EMPLOYEE, Common_Movement_WalkInPlaceFasterLeft
	waitmovement 0
	playse SE_PIN
	applymovement LOCALID_WAWA_PARK_DEVON_EMPLOYEE, Common_Movement_ExclamationMark
	waitmovement 0
	applymovement LOCALID_WAWA_PARK_DEVON_EMPLOYEE, Common_Movement_Delay48
	waitmovement 0
	return

WawaPark_EventScript_Rival::
	lockall
	call_if_unset FLAG_MET_RIVAL_RUSTBORO, WawaPark_EventScript_PlayRivalMusic
	applymovement LOCALID_WAWA_PARK_RIVAL, Common_Movement_FacePlayer
	waitmovement 0
	goto WawaPark_EventScript_RivalEncounter

WawaPark_EventScript_PlayRivalMusic::
	checkplayergender
	goto_if_eq VAR_RESULT, MALE, WawaPark_EventScript_PlayMayMusic
	goto_if_eq VAR_RESULT, FEMALE, WawaPark_EventScript_PlayMayMusic
	return

WawaPark_EventScript_PlayMayMusic::
	playbgm MUS_ENCOUNTER_MAY, TRUE
	return


WawaPark_EventScript_RivalTrigger0::
	lockall
	call WawaPark_EventScript_PlayRivalMusic
	applymovement LOCALID_WAWA_PARK_RIVAL, Common_Movement_WalkInPlaceFasterDown
	waitmovement 0
	playse SE_PIN
	applymovement LOCALID_WAWA_PARK_RIVAL, Common_Movement_ExclamationMark
	waitmovement 0
	applymovement LOCALID_WAWA_PARK_RIVAL, Common_Movement_Delay48
	waitmovement 0
	applymovement LOCALID_WAWA_PARK_RIVAL, WawaPark_Movement_RivalApproachPlayer0
	waitmovement 0
	applymovement LOCALID_PLAYER, Common_Movement_WalkInPlaceFasterUp
	waitmovement 0
	goto WawaPark_EventScript_RivalEncounter

WawaPark_EventScript_RivalTrigger1::
	lockall
	call WawaPark_EventScript_PlayRivalMusic
	applymovement LOCALID_WAWA_PARK_RIVAL, Common_Movement_WalkInPlaceFasterDown
	waitmovement 0
	playse SE_PIN
	applymovement LOCALID_WAWA_PARK_RIVAL, Common_Movement_ExclamationMark
	waitmovement 0
	applymovement LOCALID_WAWA_PARK_RIVAL, Common_Movement_Delay48
	waitmovement 0
	applymovement LOCALID_WAWA_PARK_RIVAL, WawaPark_Movement_RivalApproachPlayer1
	waitmovement 0
	applymovement LOCALID_PLAYER, Common_Movement_WalkInPlaceFasterUp
	waitmovement 0
	goto WawaPark_EventScript_RivalEncounter

WawaPark_EventScript_RivalTrigger2::
	lockall
	call WawaPark_EventScript_PlayRivalMusic
	applymovement LOCALID_WAWA_PARK_RIVAL, Common_Movement_WalkInPlaceFasterDown
	waitmovement 0
	playse SE_PIN
	applymovement LOCALID_WAWA_PARK_RIVAL, Common_Movement_ExclamationMark
	waitmovement 0
	applymovement LOCALID_WAWA_PARK_RIVAL, Common_Movement_Delay48
	waitmovement 0
	applymovement LOCALID_WAWA_PARK_RIVAL, WawaPark_Movement_RivalApproachPlayer2
	waitmovement 0
	applymovement LOCALID_PLAYER, Common_Movement_WalkInPlaceFasterUp
	waitmovement 0
	goto WawaPark_EventScript_RivalEncounter

WawaPark_EventScript_RivalTrigger3::
	lockall
	call WawaPark_EventScript_PlayRivalMusic
	applymovement LOCALID_WAWA_PARK_RIVAL, Common_Movement_WalkInPlaceFasterDown
	waitmovement 0
	playse SE_PIN
	applymovement LOCALID_WAWA_PARK_RIVAL, Common_Movement_ExclamationMark
	waitmovement 0
	applymovement LOCALID_WAWA_PARK_RIVAL, Common_Movement_Delay48
	waitmovement 0
	applymovement LOCALID_WAWA_PARK_RIVAL, WawaPark_Movement_RivalApproachPlayer3
	waitmovement 0
	applymovement LOCALID_PLAYER, Common_Movement_WalkInPlaceFasterUp
	waitmovement 0
	goto WawaPark_EventScript_RivalEncounter

WawaPark_EventScript_RivalTrigger4::
	lockall
	call WawaPark_EventScript_PlayRivalMusic
	applymovement LOCALID_WAWA_PARK_RIVAL, Common_Movement_WalkInPlaceFasterDown
	waitmovement 0
	playse SE_PIN
	applymovement LOCALID_WAWA_PARK_RIVAL, Common_Movement_ExclamationMark
	waitmovement 0
	applymovement LOCALID_WAWA_PARK_RIVAL, Common_Movement_Delay48
	waitmovement 0
	applymovement LOCALID_WAWA_PARK_RIVAL, WawaPark_Movement_RivalApproachPlayer4
	waitmovement 0
	applymovement LOCALID_PLAYER, Common_Movement_WalkInPlaceFasterUp
	waitmovement 0
	goto WawaPark_EventScript_RivalEncounter

WawaPark_EventScript_RivalTrigger5::
	lockall
	call WawaPark_EventScript_PlayRivalMusic
	applymovement LOCALID_WAWA_PARK_RIVAL, Common_Movement_WalkInPlaceFasterDown
	waitmovement 0
	playse SE_PIN
	applymovement LOCALID_WAWA_PARK_RIVAL, Common_Movement_ExclamationMark
	waitmovement 0
	applymovement LOCALID_WAWA_PARK_RIVAL, Common_Movement_Delay48
	waitmovement 0
	applymovement LOCALID_WAWA_PARK_RIVAL, WawaPark_Movement_RivalApproachPlayer5
	waitmovement 0
	applymovement LOCALID_PLAYER, Common_Movement_WalkInPlaceFasterUp
	waitmovement 0
	goto WawaPark_EventScript_RivalEncounter

WawaPark_EventScript_RivalTrigger6::
	lockall
	call WawaPark_EventScript_PlayRivalMusic
	applymovement LOCALID_WAWA_PARK_RIVAL, Common_Movement_WalkInPlaceFasterDown
	waitmovement 0
	playse SE_PIN
	applymovement LOCALID_WAWA_PARK_RIVAL, Common_Movement_ExclamationMark
	waitmovement 0
	applymovement LOCALID_WAWA_PARK_RIVAL, Common_Movement_Delay48
	waitmovement 0
	applymovement LOCALID_WAWA_PARK_RIVAL, WawaPark_Movement_RivalApproachPlayer6
	waitmovement 0
	applymovement LOCALID_PLAYER, Common_Movement_WalkInPlaceFasterUp
	waitmovement 0
	goto WawaPark_EventScript_RivalEncounter

WawaPark_EventScript_RivalTrigger7::
	lockall
	call WawaPark_EventScript_PlayRivalMusic
	applymovement LOCALID_WAWA_PARK_RIVAL, Common_Movement_WalkInPlaceFasterDown
	waitmovement 0
	playse SE_PIN
	applymovement LOCALID_WAWA_PARK_RIVAL, Common_Movement_ExclamationMark
	waitmovement 0
	applymovement LOCALID_WAWA_PARK_RIVAL, Common_Movement_Delay48
	waitmovement 0
	applymovement LOCALID_WAWA_PARK_RIVAL, WawaPark_Movement_RivalApproachPlayer7
	waitmovement 0
	applymovement LOCALID_PLAYER, Common_Movement_WalkInPlaceFasterUp
	waitmovement 0
	goto WawaPark_EventScript_RivalEncounter

WawaPark_EventScript_RivalEncounter::
	checkplayergender
	goto_if_eq VAR_RESULT, MALE, WawaPark_EventScript_MayEncounter
	goto_if_eq VAR_RESULT, FEMALE, WawaPark_EventScript_MayEncounter
	end

WawaPark_EventScript_MayEncounter::
	goto_if_set FLAG_DEFEATED_RIVAL_RUSTBORO, WawaPark_EventScript_MayBrineyHint
	goto_if_set FLAG_MET_RIVAL_RUSTBORO, WawaPark_EventScript_MayAskToBattle
	setflag FLAG_MET_RIVAL_RUSTBORO
	msgbox WawaPark_Text_MayHiLetsRegister, MSGBOX_DEFAULT
	closemessage
	delay 30
	playfanfare MUS_REGISTER_MATCH_CALL
	msgbox WawaPark_Text_RegisteredMay, MSGBOX_DEFAULT
	waitfanfare
	closemessage
	delay 30
	setflag FLAG_ENABLE_RIVAL_MATCH_CALL
	setvar VAR_WAWA_PARK_CITY_STATE, 8
	setvar VAR_ROUTE104_STATE, 2
	setvar VAR_0x8008, 0
	msgbox WawaPark_Text_MayPassedBrineyWantToBattle, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, WawaPark_EventScript_BattleMay
	msgbox WawaPark_Text_MayOhHaventRaisedPokemonEnough, MSGBOX_DEFAULT
	call WawaPark_EventScript_RestoreBgm
	releaseall
	end

WawaPark_EventScript_MayAskToBattle::
	setvar VAR_0x8008, 1
	msgbox WawaPark_Text_MayWantToBattle, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, WawaPark_EventScript_BattleMay
	msgbox WawaPark_Text_MayOhHaventRaisedPokemonEnough, MSGBOX_DEFAULT
	releaseall
	end

WawaPark_EventScript_BattleMay::
	msgbox WawaPark_Text_MayImNotGoingToLose, MSGBOX_DEFAULT
	switch VAR_STARTER_MON
	case 0, WawaPark_EventScript_BattleMayBulbasaur
	case 1, WawaPark_EventScript_BattleMayGible
	case 2, WawaPark_EventScript_BattleMayAron
	end

WawaPark_EventScript_MayBrineyHint::
	msgbox WawaPark_Text_MayMrBrineyHint, MSGBOX_DEFAULT
	call_if_eq VAR_0x8008, 0, WawaPark_EventScript_RestoreBgm
	releaseall
	end

WawaPark_EventScript_RestoreBgm::
	savebgm MUS_DUMMY
	fadedefaultbgm
	return

WawaPark_EventScript_BattleMayBulbasaur::
	trainerbattle_no_intro TRAINER_MAY_RUSTBORO_BULBASAUR, WawaPark_Text_MayDefeat
	setflag FLAG_DEFEATED_RIVAL_RUSTBORO
	goto WawaPark_EventScript_MayBrineyHint
	end

WawaPark_EventScript_BattleMayGible::
	trainerbattle_no_intro TRAINER_MAY_RUSTBORO_GIBLE, WawaPark_Text_MayDefeat
	setflag FLAG_DEFEATED_RIVAL_RUSTBORO
	goto WawaPark_EventScript_MayBrineyHint
	end

WawaPark_EventScript_BattleMayAron::
	trainerbattle_no_intro TRAINER_MAY_RUSTBORO_ARON, WawaPark_Text_MayDefeat
	setflag FLAG_DEFEATED_RIVAL_RUSTBORO
	goto WawaPark_EventScript_MayBrineyHint
	end





WawaPark_Movement_RivalApproachPlayer0:
	walk_down
	walk_left
	walk_left
	walk_left
	walk_left
	walk_down
	step_end

WawaPark_Movement_RivalApproachPlayer1:
	walk_down
	walk_left
	walk_left
	walk_left
	walk_down
	step_end

WawaPark_Movement_RivalApproachPlayer2:
	walk_down
	walk_left
	walk_left
	walk_down
	step_end

WawaPark_Movement_RivalApproachPlayer3:
	walk_down
	walk_left
	walk_down
	step_end

WawaPark_Movement_RivalApproachPlayer4:
	walk_down
	walk_down
	step_end

WawaPark_Movement_RivalApproachPlayer5:
	walk_down
	walk_right
	walk_down
	step_end

WawaPark_Movement_RivalApproachPlayer6:
	walk_down
	walk_right
	walk_right
	walk_down
	step_end

WawaPark_Movement_RivalApproachPlayer7:
	walk_down
	walk_right
	walk_right
	walk_right
	walk_down
	step_end

WawaPark_EventScript_Boy1::
	msgbox WawaPark_Text_YouCanHave2On2Battle, MSGBOX_NPC
	end

WawaPark_Text_WeShortenItToDevon:
	.string "The DEVON CORPORATION…\n"
	.string "We all just shorten it to DEVON.\p"
	.string "That company makes all sorts of\n"
	.string "convenient products.$"

WawaPark_Text_SneakyLookingManWentAroundCorner:
	.string "Hm? A sneaky-looking man?\p"
	.string "Come to think of it, yes, a shady-\n"
	.string "looking guy went around the corner.$"

WawaPark_Text_HaveYouChallengedGym:
	.string "Have you taken the POKéMON GYM\n"
	.string "challenge?\p"
	.string "When you get that shiny GYM BADGE\n"
	.string "in hand, I guess TRAINERS begin to\l"
	.string "realize what is required of them.$"

WawaPark_Text_HeyThatsWawaParksGymBadge:
	.string "Hey, that's Wawa Park's GYM BADGE!\p"
	.string "Out of all the POKéMON GYM BADGES,\n"
	.string "Wawa Park's is the coolest, I'd say.$"

WawaPark_Text_YoureNewAroundHere:
	.string "Oh? Who might you be?\n"
	.string "You're a new face around these parts.\p"
	.string "Have you just transferred into the\n"
	.string "POKéMON TRAINER'S SCHOOL?$"

WawaPark_Text_GymLeaderIsntEasyWithFire:
	.string "I challenged the GYM LEADER, but…\p"
	.string "It's not going to be easy winning with\n"
	.string "my FIRE-type POKéMON…\p"
	.string "FIRE-type POKéMON don't match up\n"
	.string "well against ROCK-type POKéMON…$"

WawaPark_Text_MrBrineyWalksInTheTunnel:
	.string "The old sailor MR. BRINEY lives in\n"
	.string "a cottage by the sea.\p"
	.string "He goes for walks in the tunnel every\n"
	.string "so often.$"

WawaPark_Text_MrBrineyLovesPeeko:
	.string "The old sailor MR. BRINEY lives in\n"
	.string "a cottage by the sea.\p"
	.string "He said he was going shopping in\n"
	.string "SLATEPORT for his pet, PEEKO.\p"
	.string "That old sea dog, he must really love\n"
	.string "that PEEKO.$"

WawaPark_Text_WowYouHavePokemon:
	.string "Wow, you have POKéMON with you, too.\p"
	.string "When I get bigger, I'm going to go\n"
	.string "places with POKéMON, too.$"

WawaPark_Text_CatchRarePokemonIfIGoToSchool:
	.string "POKéMON TRAINER'S SCHOOL!\p"
	.string "If I go to this school, will I be able\n"
	.string "to catch rare POKéMON easily?$"

WawaPark_Text_PokemonCanChangeLookFromExp:
	.string "If a POKéMON gains experience in\n"
	.string "battles, it can sometimes change in\l"
	.string "the way it looks.$"

WawaPark_Text_PokemonChangeShape:
	.string "A POKéMON changes shape?\n"
	.string "If one did that, I would be shocked!$"

WawaPark_Text_TradePokemonGrowFast:
	.string "A POKéMON you get in a trade from\n"
	.string "someone grows fast.\p"
	.string "But if you don't have certain GYM\n"
	.string "BADGES, it may not obey you…$"

WawaPark_Text_OutOfTheWay:
	.string "Get out!\n"
	.string "Out of the way!$"

WawaPark_Text_WaitDontTakeMyGoods:
	.string "Wait! Pleeeaaase!\p"
	.string "Don't take my GOODS!$"

WawaPark_Text_HelpMeIWasRobbed:
	.string "Oh, it's you!\p"
	.string "You're that fantastic TRAINER who\n"
	.string "helped me in SCRAPPLE HOLLOW!\p"
	.string "Help me! I was robbed by TEAM AQUA!\n"
	.string "I have to get the DEVON GOODS back!\p"
	.string "If I don't…\n"
	.string "I'm going to be in serious trouble.$"

WawaPark_Text_ShadyCharacterTookOffTowardsTunnel:
	.string "That shady character, I think he took\n"
	.string "off towards the tunnel over there.$"

WawaPark_Text_YouGotItThankYou:
	.string "Oh! How did it go?\n"
	.string "The DEVON GOODS?\p"
	.string "You did!\n"
	.string "You got them back!\p"
	.string "You really are a great TRAINER!\p"
	.string "I know! As my thanks, I'll give you\n"
	.string "another GREAT BALL!$"

WawaPark_Text_YoureLoadedWithItems:
	.string "You're loaded with items.\n"
	.string "I can't give you this GREAT BALL.$"

WawaPark_Text_PleaseComeWithMe:
	.string "Excuse me, please!\n"
	.string "Please come with me!$"

WawaPark_Text_MayHiLetsRegister:
	.string "MAY: Oh, hi, {PLAYER}{KUN}!\p"
	.string "You had a MATCH CALL feature put\n"
	.string "on your POKéNAV!\p"
	.string "Let's register each other so we can\n"
	.string "contact one another anytime!\p"
	.string "… … … … … …$"

WawaPark_Text_RegisteredMay:
	.string "Registered MAY\n"
	.string "in the POKéNAV.$"

WawaPark_Text_MayPassedBrineyWantToBattle:
	.string "MAY: Oh, by the way, I passed\n"
	.string "MR. BRINEY in SCRAPPLE HOLLOW.\p"
	.string "I guess he's on his way home to his\n"
	.string "cottage by the sea.\p"
	.string "How's your POKéDEX coming along,\n"
	.string "{PLAYER}{KUN}? Mine's looking pretty decent!\p"
	.string "So…\n"
	.string "How about a little battle?$"

WawaPark_Text_MayOhHaventRaisedPokemonEnough:
	.string "MAY: Oh, what's the matter?\p"
	.string "Haven't you caught or raised your\n"
	.string "POKéMON very much?\p"
	.string "That's not very good for a TRAINER!$"

WawaPark_Text_MayWantToBattle:
	.string "MAY: So, what do you think?\n"
	.string "How about a little battle here?$"

WawaPark_Text_MayImNotGoingToLose:
	.string "MAY: You just became a TRAINER,\n"
	.string "{PLAYER}{KUN}. I'm not going to lose!$"

WawaPark_Text_MayDefeat:
	.string "Yikes!\n"
	.string "You're better than I expected!$"

WawaPark_Text_MayMrBrineyHint:
	.string "MAY: Oh, by the way, MR. BRINEY, who\n"
	.string "I just passed…\p"
	.string "{PLAYER}{KUN}, you just moved here so you\n"
	.string "might not know this, but MR. BRINEY\l"
	.string "was once a revered seafarer.$"


WawaPark_Text_TunnelNearingCompletion:
	.string "“Timesaving tunnel nearing\n"
	.string "completion!”\p"
	.string "…Is what it says on the sign, but\n"
	.string "there's also a big “X” splashed\l"
	.string "across it in red paint…$"

WawaPark_Text_DevonCorpSign:
	.string "DEVON CORPORATION\p"
	.string "“For all your living needs, we make\n"
	.string "it all.”$"

WawaPark_Text_GymSign:
	.string "WAWA PARK POKéMON GYM\n"
	.string "LEADER: ROXANNE\p"
	.string "“The ROCK-loving honors student!”$"

WawaPark_Text_DevonCorpBranchOfficeSign:
	.string "DEVON CORP. BRANCH OFFICE\p"
	.string "“Access limited to DEVON employees\n"
	.string "and authorized personnel.”$"

WawaPark_Text_CitySign:
	.string "WAWA PARK\p"
	.string "“The city probing the integration of\n"
	.string "nature and science.”$"

WawaPark_Text_TrainersSchoolSign:
	.string "POKéMON TRAINER'S SCHOOL\p"
	.string "“We'll teach you anything about\n"
	.string "POKéMON!”$"

WawaPark_Text_CuttersHouse:
	.string "CUTTER'S HOUSE$"

WawaPark_Text_DevelopedNewPokenavFeature:
	.string "I've been developing an added feature\n"
	.string "for the POKéNAV…\p"
	.string "And it turned out great!\p"
	.string "{PLAYER}, may I see that POKéNAV?\n"
	.string "The one our PRESIDENT gave you?$"

WawaPark_Text_AddedMatchCallPleaseCallMrStone:
	.string "There you go, {PLAYER}!\p"
	.string "I added a new feature named\n"
	.string "MATCH CALL to your POKéNAV.\p"
	.string "Using the MATCH CALL feature,\n"
	.string "you can chat with people who have\l"
	.string "been registered in your POKéNAV.\p"
	.string "{PLAYER}, our PRESIDENT STONE should\n"
	.string "be registered in your POKéNAV.\p"
	.string "Test it out.\n"
	.string "Please give our PRESIDENT a call.$"

WawaPark_Text_PleaseSelectPokenav:
	.string "Please select the POKéNAV.$"

WawaPark_Text_IdBetterGetBackToWork:
	.string "Okay, I'd better get back to work.\n"
	.string "Please take care, {PLAYER}!$"

WawaPark_Text_YouCanHave2On2Battle:
	.string "Did you know this?\p"
	.string "You can have a 2-on-2 battle even\n"
	.string "if you're not with another TRAINER.\p"
	.string "If you catch the eyes of two TRAINERS\n"
	.string "when you have two or more POKéMON,\l"
	.string "they'll both challenge you.\p"
	.string "Don't you think it'd be cool if you\n"
	.string "could beat two TRAINERS by yourself?$"
