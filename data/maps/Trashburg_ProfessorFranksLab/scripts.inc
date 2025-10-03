Trashburg_ProfessorFranksLab_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, Trashburg_ProfessorFranksLab_OnTransition
	map_script MAP_SCRIPT_ON_WARP_INTO_MAP_TABLE, Trashburg_ProfessorFranksLab_OnWarp
	map_script MAP_SCRIPT_ON_FRAME_TABLE, Trashburg_ProfessorFranksLab_OnFrame
	.byte 0

	@ State descriptions for VAR_DEX_UPGRADE_JOHTO_STARTER_STATE
	@ 1: Beat Elite Four, Dex upgrade ready
	@ 2: Received National Dex
	@ 3: Left lab after receiving National Dex
	@ 4: Entered lab after catching all Hoenn mons
	@ 5: Frank told player to choose Johto starter
	@ 6: Chose Johto starter

	@ State descriptions for VAR_FRANK_LAB_STATE
	@ 1: Never occurs
	@ 2: Chose starter
	@ 3: Received starter in lab
	@ 4: Defeated rival on Route 103
	@ 5: Received pokedex

Trashburg_ProfessorFranksLab_OnTransition:
	call Common_EventScript_SetupRivalGfxId
	call ProfFrank_EventScript_UpdateLocation
	goto_if_ge VAR_DEX_UPGRADE_JOHTO_STARTER_STATE, 6, Trashburg_ProfessorFranksLab_EventScript_SetAfterJohtoStarterLayout
	goto_if_ge VAR_DEX_UPGRADE_JOHTO_STARTER_STATE, 4, Trashburg_ProfessorFranksLab_EventScript_SetJohtoStarterLayout
	goto_if_eq VAR_DEX_UPGRADE_JOHTO_STARTER_STATE, 3, Trashburg_ProfessorFranksLab_EventScript_CheckReadyForJohtoStarter
	end

Trashburg_ProfessorFranksLab_EventScript_CheckReadyForJohtoStarter::
	specialvar VAR_RESULT, HasAllHoennMons
	goto_if_eq VAR_RESULT, TRUE, Trashburg_ProfessorFranksLab_EventScript_SetReadyForJohtoStarter
	setobjectmovementtype LOCALID_FRANKS_LAB_RIVAL, MOVEMENT_TYPE_WANDER_UP_AND_DOWN
	setobjectxyperm LOCALID_FRANKS_LAB_RIVAL, 5, 10
	end

Trashburg_ProfessorFranksLab_EventScript_SetReadyForJohtoStarter::
	setvar VAR_DEX_UPGRADE_JOHTO_STARTER_STATE, 4
	goto Trashburg_ProfessorFranksLab_EventScript_SetJohtoStarterLayout

Trashburg_ProfessorFranksLab_EventScript_SetJohtoStarterLayout::
	setmaplayoutindex LAYOUT_TRASHBURG_PROFESSOR_FRANKS_LAB_WITH_TABLE
	end

Trashburg_ProfessorFranksLab_EventScript_SetAfterJohtoStarterLayout::
	setmaplayoutindex LAYOUT_TRASHBURG_PROFESSOR_FRANKS_LAB_WITH_TABLE
	setobjectmovementtype LOCALID_FRANKS_LAB_RIVAL, MOVEMENT_TYPE_WANDER_UP_AND_DOWN
	setobjectxyperm LOCALID_FRANKS_LAB_RIVAL, 5, 10
	end

Trashburg_ProfessorFranksLab_OnWarp:
	map_script_2 VAR_FRANK_LAB_STATE, 2, Trashburg_ProfessorFranksLab_EventScript_SetPlayerPosForReceiveStarter
	map_script_2 VAR_DEX_UPGRADE_JOHTO_STARTER_STATE, 1, Trashburg_ProfessorFranksLab_EventScript_SetObjectPosForDexUpgrade
	map_script_2 VAR_DEX_UPGRADE_JOHTO_STARTER_STATE, 2, Trashburg_ProfessorFranksLab_EventScript_SetObjectPosForDexUpgrade
	map_script_2 VAR_DEX_UPGRADE_JOHTO_STARTER_STATE, 3, Trashburg_ProfessorFranksLab_EventScript_AddRivalObject
	map_script_2 VAR_DEX_UPGRADE_JOHTO_STARTER_STATE, 6, Trashburg_ProfessorFranksLab_EventScript_AddRivalObject
	map_script_2 VAR_DEX_UPGRADE_JOHTO_STARTER_STATE, 4, Trashburg_ProfessorFranksLab_EventScript_SetObjectPosForJohtoStarters
	map_script_2 VAR_DEX_UPGRADE_JOHTO_STARTER_STATE, 5, Trashburg_ProfessorFranksLab_EventScript_SetObjectPosForJohtoStarters
	.2byte 0

Trashburg_ProfessorFranksLab_EventScript_SetPlayerPosForReceiveStarter::
	turnobject LOCALID_PLAYER, DIR_NORTH
	end

Trashburg_ProfessorFranksLab_EventScript_SetObjectPosForDexUpgrade::
	turnobject LOCALID_PLAYER, DIR_NORTH
	addobject LOCALID_FRANKS_LAB_FRANK
	addobject LOCALID_FRANKS_LAB_RIVAL
	turnobject LOCALID_FRANKS_LAB_RIVAL, DIR_NORTH
	setobjectxy LOCALID_FRANKS_LAB_RIVAL, 5, 5
	turnobject LOCALID_FRANKS_LAB_FRANK, DIR_SOUTH
	setobjectxy LOCALID_FRANKS_LAB_FRANK, 6, 4
	turnobject LOCALID_FRANKS_LAB_AIDE, DIR_EAST
	setobjectxy LOCALID_FRANKS_LAB_AIDE, 10, 10
	end

Trashburg_ProfessorFranksLab_EventScript_AddRivalObject::
	addobject LOCALID_FRANKS_LAB_RIVAL
	end

Trashburg_ProfessorFranksLab_EventScript_SetObjectPosForJohtoStarters::
	addobject LOCALID_FRANKS_LAB_CYNDAQUIL_BALL
	addobject LOCALID_FRANKS_LAB_TOTODILE_BALL
	addobject LOCALID_FRANKS_LAB_CHIKORITA_BALL
	addobject LOCALID_FRANKS_LAB_RIVAL
	turnobject LOCALID_FRANKS_LAB_CYNDAQUIL_BALL, DIR_SOUTH
	setobjectxy LOCALID_FRANKS_LAB_CYNDAQUIL_BALL, 8, 4
	turnobject LOCALID_FRANKS_LAB_TOTODILE_BALL, DIR_SOUTH
	setobjectxy LOCALID_FRANKS_LAB_TOTODILE_BALL, 9, 4
	turnobject LOCALID_FRANKS_LAB_CHIKORITA_BALL, DIR_SOUTH
	setobjectxy LOCALID_FRANKS_LAB_CHIKORITA_BALL, 10, 4
	turnobject LOCALID_FRANKS_LAB_FRANK, DIR_SOUTH
	setobjectxy LOCALID_FRANKS_LAB_FRANK, 6, 4
	turnobject LOCALID_FRANKS_LAB_RIVAL, DIR_EAST
	setobjectxy LOCALID_FRANKS_LAB_RIVAL, 5, 5
	end

Trashburg_ProfessorFranksLab_OnFrame:
	map_script_2 VAR_FRANK_LAB_STATE, 2, Trashburg_ProfessorFranksLab_EventScript_GiveStarterEvent
	map_script_2 VAR_FRANK_LAB_STATE, 4, Trashburg_ProfessorFranksLab_EventScript_GivePokedexEvent
	map_script_2 VAR_DEX_UPGRADE_JOHTO_STARTER_STATE, 1, Trashburg_ProfessorFranksLab_EventScript_UpgradeToNationalDex
	map_script_2 VAR_DEX_UPGRADE_JOHTO_STARTER_STATE, 4, Trashburg_ProfessorFranksLab_EventScript_ChooseJohtoStarter
	.2byte 0

@ The starter is technically given prior to this on Route 101 by special ChooseStarter
@ This is just where the game tells you its yours and lets you nickname it
Trashburg_ProfessorFranksLab_EventScript_GiveStarterEvent::
	lockall
	bufferleadmonspeciesname STR_VAR_1
	message Trashburg_ProfessorFranksLab_Text_LikeYouToHavePokemon
	waitmessage
	playfanfare MUS_OBTAIN_ITEM
	waitfanfare
	msgbox Trashburg_ProfessorFranksLab_Text_WhyNotGiveNicknameToMon, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, Trashburg_ProfessorFranksLab_EventScript_NicknameStarter
	goto_if_eq VAR_RESULT, NO, Trashburg_ProfessorFranksLab_EventScript_GoSeeRival
	end

Trashburg_ProfessorFranksLab_EventScript_NicknameStarter::
	setvar VAR_0x8004, 0
	call Common_EventScript_NameReceivedPartyMon
	goto Trashburg_ProfessorFranksLab_EventScript_GoSeeRival
	end

Trashburg_ProfessorFranksLab_EventScript_GoSeeRival::
	msgbox Trashburg_ProfessorFranksLab_Text_MightBeGoodIdeaToGoSeeRival, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, Trashburg_ProfessorFranksLab_EventScript_AgreeToSeeRival
	goto_if_eq VAR_RESULT, NO, Trashburg_ProfessorFranksLab_EventScript_DeclineSeeingRival
	end

Trashburg_ProfessorFranksLab_EventScript_AgreeToSeeRival::
	msgbox Trashburg_ProfessorFranksLab_Text_GetRivalToTeachYou, MSGBOX_DEFAULT
	clearflag FLAG_HIDE_ROUTE_101_BOY
	setvar VAR_FRANK_LAB_STATE, 3
	releaseall
	end

Trashburg_ProfessorFranksLab_EventScript_DeclineSeeingRival::
	msgbox Trashburg_ProfessorFranksLab_Text_DontBeThatWay, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, Trashburg_ProfessorFranksLab_EventScript_AgreeToSeeRival
	goto_if_eq VAR_RESULT, NO, Trashburg_ProfessorFranksLab_EventScript_DeclineSeeingRival
	end

Trashburg_ProfessorFranksLab_EventScript_GivePokedexEvent::
	lockall
	applymovement LOCALID_PLAYER, Trashburg_ProfessorFranksLab_Movement_PlayerEnterLabForPokedex
	waitmovement 0
	goto Trashburg_ProfessorFranksLab_EventScript_GivePokedex
	end

Trashburg_ProfessorFranksLab_Movement_PlayerEnterLabForPokedex:
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	step_end

Trashburg_ProfessorFranksLab_EventScript_UpgradeToNationalDex::
	lockall
	delay 30
	msgbox Trashburg_ProfessorFranksLab_Text_OtherRegionsUpgradeToNational, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_FRANKS_LAB_FRANK, Trashburg_ProfessorFranksLab_Movement_FrankRetrievePokedexes
	waitmovement 0
	delay 20
	playse SE_CLICK
	delay 10
	playse SE_CLICK
	delay 10
	playse SE_CLICK
	delay 10
	playse SE_CLICK
	delay 20
	applymovement LOCALID_FRANKS_LAB_RIVAL, Common_Movement_WalkInPlaceFasterRight
	applymovement LOCALID_PLAYER, Common_Movement_WalkInPlaceFasterLeft
	waitmovement 0
	checkplayergender
	call_if_eq VAR_RESULT, MALE, Trashburg_ProfessorFranksLab_EventScript_MayUpgradeComment
	call_if_eq VAR_RESULT, FEMALE, Trashburg_ProfessorFranksLab_EventScript_BrendanUpgradeComment
	playse SE_PC_ON
	waitse
	delay 20
	applymovement LOCALID_FRANKS_LAB_FRANK, Trashburg_ProfessorFranksLab_Movement_FrankReturnPokedex
	waitmovement 0
	applymovement LOCALID_FRANKS_LAB_RIVAL, Common_Movement_WalkInPlaceFasterUp
	applymovement LOCALID_PLAYER, Common_Movement_WalkInPlaceFasterUp
	waitmovement 0
	msgbox Trashburg_ProfessorFranksLab_Text_OkayAllDone, MSGBOX_DEFAULT
	playfanfare MUS_OBTAIN_ITEM
	message Trashburg_ProfessorFranksLab_Text_PokedexUpgradedToNational
	waitmessage
	waitfanfare
	setflag FLAG_SYS_NATIONAL_DEX
	special EnableNationalPokedex
	msgbox Trashburg_ProfessorFranksLab_Text_GrassyPatchWaiting2, MSGBOX_DEFAULT
	closemessage
	setflag FLAG_HIDE_TRASHBURG_FRANK
	setflag FLAG_HIDE_TRASHBURG_RIVAL
	setvar VAR_DEX_UPGRADE_JOHTO_STARTER_STATE, 2
	setvar VAR_SCOTT_BF_CALL_STEP_COUNTER, 0
	setflag FLAG_SCOTT_CALL_BATTLE_FRONTIER
	releaseall
	end

Trashburg_ProfessorFranksLab_EventScript_MayUpgradeComment::
	msgbox Trashburg_ProfessorFranksLab_Text_MayUpgradeSoCool, MSGBOX_DEFAULT
	closemessage
	return

Trashburg_ProfessorFranksLab_EventScript_BrendanUpgradeComment::
	msgbox Trashburg_ProfessorFranksLab_Text_BrendanYouCanThankMe, MSGBOX_DEFAULT
	closemessage
	return

Trashburg_ProfessorFranksLab_Movement_FrankRetrievePokedexes:
	walk_left
	walk_in_place_faster_down
	delay_16
	delay_16
	walk_right
	walk_in_place_faster_down
	delay_16
	delay_16
	walk_right
	walk_down
	walk_down
	walk_down
	walk_down
	walk_right
	walk_right
	walk_right
	walk_in_place_faster_up
	step_end

Trashburg_ProfessorFranksLab_Movement_FrankReturnPokedex:
	walk_left
	walk_left
	walk_left
	walk_up
	walk_up
	walk_up
	walk_up
	walk_left
	walk_in_place_faster_down
	step_end

Trashburg_ProfessorFranksLab_EventScript_ChooseJohtoStarter::
	lockall
	applymovement LOCALID_PLAYER, Trashburg_ProfessorFranksLab_Movement_PlayerEnterLabForJohtoStarter
	waitmovement 0
	msgbox Trashburg_ProfessorFranksLab_Text_CompletedDexChoosePokemon, MSGBOX_DEFAULT
	setvar VAR_DEX_UPGRADE_JOHTO_STARTER_STATE, 5
	releaseall
	end

Trashburg_ProfessorFranksLab_Movement_PlayerEnterLabForJohtoStarter:
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	step_end

Trashburg_ProfessorFranksLab_EventScript_Aide::
	lock
	faceplayer
	goto_if_ge VAR_FRANK_LAB_STATE, 3, Trashburg_ProfessorFranksLab_EventScript_AideReceivedStarter
	goto_if_set FLAG_FRANK_AIDE_MET, Trashburg_ProfessorFranksLab_EventScript_AideAlreadyMet
	msgbox Trashburg_ProfessorFranksLab_Text_FrankAwayOnFieldwork, MSGBOX_DEFAULT
	setflag FLAG_FRANK_AIDE_MET
	release
	end

Trashburg_ProfessorFranksLab_EventScript_AideAlreadyMet::
	msgbox Trashburg_ProfessorFranksLab_Text_FrankIsntOneForDeskWork, MSGBOX_DEFAULT
	release
	end

Trashburg_ProfessorFranksLab_EventScript_AideReceivedStarter::
	msgbox Trashburg_ProfessorFranksLab_Text_FrankEnjoysRivalsHelpToo, MSGBOX_DEFAULT
	release
	end

Trashburg_ProfessorFranksLab_EventScript_Cyndaquil::
	release
	goto_if_ge VAR_DEX_UPGRADE_JOHTO_STARTER_STATE, 6, Trashburg_ProfessorFranksLab_EventScript_AlreadyChoseJohtoStarter
	applymovement LOCALID_FRANKS_LAB_FRANK, Common_Movement_WalkInPlaceFasterRight
	waitmovement 0
	showmonpic SPECIES_CYNDAQUIL, 10, 3
	msgbox Trashburg_ProfessorFranksLab_Text_YoullTakeCyndaquil, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, Trashburg_ProfessorFranksLab_EventScript_TakeYourTime
	goto Trashburg_ProfessorFranksLab_EventScript_GiveCyndaquil
	end

Trashburg_ProfessorFranksLab_EventScript_Totodile::
	release
	goto_if_ge VAR_DEX_UPGRADE_JOHTO_STARTER_STATE, 6, Trashburg_ProfessorFranksLab_EventScript_AlreadyChoseJohtoStarter
	applymovement LOCALID_FRANKS_LAB_FRANK, Common_Movement_WalkInPlaceFasterRight
	waitmovement 0
	showmonpic SPECIES_TOTODILE, 10, 3
	msgbox Trashburg_ProfessorFranksLab_Text_YoullTakeTotodile, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, Trashburg_ProfessorFranksLab_EventScript_TakeYourTime
	goto Trashburg_ProfessorFranksLab_EventScript_GiveTotodile
	end

Trashburg_ProfessorFranksLab_EventScript_Chikorita::
	release
	goto_if_ge VAR_DEX_UPGRADE_JOHTO_STARTER_STATE, 6, Trashburg_ProfessorFranksLab_EventScript_AlreadyChoseJohtoStarter
	applymovement LOCALID_FRANKS_LAB_FRANK, Common_Movement_WalkInPlaceFasterRight
	waitmovement 0
	showmonpic SPECIES_CHIKORITA, 10, 3
	msgbox Trashburg_ProfessorFranksLab_Text_YoullTakeChikorita, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, Trashburg_ProfessorFranksLab_EventScript_TakeYourTime
	goto Trashburg_ProfessorFranksLab_EventScript_GiveChikorita
	end

Trashburg_ProfessorFranksLab_EventScript_AlreadyChoseJohtoStarter::
	msgbox Trashburg_ProfessorFranksLab_Text_BetterLeaveOthersAlone, MSGBOX_DEFAULT
	releaseall
	end

Trashburg_ProfessorFranksLab_EventScript_TakeYourTime::
	hidemonpic
	msgbox Trashburg_ProfessorFranksLab_Text_TakeYourTimeAllInvaluable, MSGBOX_DEFAULT
	releaseall
	end

Trashburg_ProfessorFranksLab_EventScript_GiveCyndaquil::
	bufferspeciesname STR_VAR_1, SPECIES_CYNDAQUIL
	setvar VAR_TEMP_TRANSFERRED_SPECIES, SPECIES_CYNDAQUIL
	givemon SPECIES_CYNDAQUIL, 5
	goto_if_eq VAR_RESULT, MON_GIVEN_TO_PARTY, Trashburg_ProfessorFranksLab_EventScript_SendCyndaquilToParty
	goto_if_eq VAR_RESULT, MON_GIVEN_TO_PC, Trashburg_ProfessorFranksLab_EventScript_SendCyndaquilToPC
	hidemonpic
	goto Common_EventScript_NoMoreRoomForPokemon
	end

Trashburg_ProfessorFranksLab_EventScript_SendCyndaquilToParty::
	call Trashburg_ProfessorFranksLab_EventScript_ReceivedJohtoStarter
	removeobject LOCALID_FRANKS_LAB_CYNDAQUIL_BALL
	msgbox gText_NicknameThisPokemon, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, Trashburg_ProfessorFranksLab_EventScript_ReceivedCyndaquil
	call Common_EventScript_GetGiftMonPartySlot
	call Common_EventScript_NameReceivedPartyMon
	goto Trashburg_ProfessorFranksLab_EventScript_ReceivedCyndaquil
	end

Trashburg_ProfessorFranksLab_EventScript_SendCyndaquilToPC::
	call Trashburg_ProfessorFranksLab_EventScript_ReceivedJohtoStarter
	removeobject LOCALID_FRANKS_LAB_CYNDAQUIL_BALL
	msgbox gText_NicknameThisPokemon, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, Trashburg_ProfessorFranksLab_EventScript_CyndaquilTransferredToPC
	call Common_EventScript_NameReceivedBoxMon
	goto Trashburg_ProfessorFranksLab_EventScript_CyndaquilTransferredToPC
	end

Trashburg_ProfessorFranksLab_EventScript_CyndaquilTransferredToPC::
	call Common_EventScript_TransferredToPC
	goto Trashburg_ProfessorFranksLab_EventScript_ReceivedCyndaquil
	end

Trashburg_ProfessorFranksLab_EventScript_ReceivedCyndaquil::
	hidemonpic
	msgbox Trashburg_ProfessorFranksLab_Text_GrassyPatchWaiting, MSGBOX_DEFAULT
	setvar VAR_DEX_UPGRADE_JOHTO_STARTER_STATE, 6
	releaseall
	end

Trashburg_ProfessorFranksLab_EventScript_GiveTotodile::
	bufferspeciesname STR_VAR_1, SPECIES_TOTODILE
	setvar VAR_TEMP_TRANSFERRED_SPECIES, SPECIES_TOTODILE
	givemon SPECIES_TOTODILE, 5
	goto_if_eq VAR_RESULT, MON_GIVEN_TO_PARTY, Trashburg_ProfessorFranksLab_EventScript_SendTotodileToParty
	goto_if_eq VAR_RESULT, MON_GIVEN_TO_PC, Trashburg_ProfessorFranksLab_EventScript_SendTotodileToPC
	hidemonpic
	goto Common_EventScript_NoMoreRoomForPokemon
	end

Trashburg_ProfessorFranksLab_EventScript_SendTotodileToParty::
	call Trashburg_ProfessorFranksLab_EventScript_ReceivedJohtoStarter
	removeobject LOCALID_FRANKS_LAB_TOTODILE_BALL
	msgbox gText_NicknameThisPokemon, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, Trashburg_ProfessorFranksLab_EventScript_ReceivedTotodile
	call Common_EventScript_GetGiftMonPartySlot
	call Common_EventScript_NameReceivedPartyMon
	goto Trashburg_ProfessorFranksLab_EventScript_ReceivedTotodile
	end

Trashburg_ProfessorFranksLab_EventScript_SendTotodileToPC::
	call Trashburg_ProfessorFranksLab_EventScript_ReceivedJohtoStarter
	removeobject LOCALID_FRANKS_LAB_TOTODILE_BALL
	msgbox gText_NicknameThisPokemon, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, Trashburg_ProfessorFranksLab_EventScript_TotodileTransferredToPC
	call Common_EventScript_NameReceivedBoxMon
	goto Trashburg_ProfessorFranksLab_EventScript_TotodileTransferredToPC
	end

Trashburg_ProfessorFranksLab_EventScript_TotodileTransferredToPC::
	call Common_EventScript_TransferredToPC
	goto Trashburg_ProfessorFranksLab_EventScript_ReceivedTotodile
	end

Trashburg_ProfessorFranksLab_EventScript_ReceivedTotodile::
	hidemonpic
	msgbox Trashburg_ProfessorFranksLab_Text_GrassyPatchWaiting, MSGBOX_DEFAULT
	setvar VAR_DEX_UPGRADE_JOHTO_STARTER_STATE, 6
	releaseall
	end

Trashburg_ProfessorFranksLab_EventScript_GiveChikorita::
	bufferspeciesname STR_VAR_1, SPECIES_CHIKORITA
	setvar VAR_TEMP_TRANSFERRED_SPECIES, SPECIES_CHIKORITA
	givemon SPECIES_CHIKORITA, 5
	goto_if_eq VAR_RESULT, MON_GIVEN_TO_PARTY, Trashburg_ProfessorFranksLab_EventScript_SendChikoritaToParty
	goto_if_eq VAR_RESULT, MON_GIVEN_TO_PC, Trashburg_ProfessorFranksLab_EventScript_SendChikoritaToPC
	hidemonpic
	goto Common_EventScript_NoMoreRoomForPokemon
	end

Trashburg_ProfessorFranksLab_EventScript_SendChikoritaToParty::
	call Trashburg_ProfessorFranksLab_EventScript_ReceivedJohtoStarter
	removeobject LOCALID_FRANKS_LAB_CHIKORITA_BALL
	msgbox gText_NicknameThisPokemon, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, Trashburg_ProfessorFranksLab_EventScript_ReceivedChikorita
	call Common_EventScript_GetGiftMonPartySlot
	call Common_EventScript_NameReceivedPartyMon
	goto Trashburg_ProfessorFranksLab_EventScript_ReceivedChikorita
	end

Trashburg_ProfessorFranksLab_EventScript_SendChikoritaToPC::
	call Trashburg_ProfessorFranksLab_EventScript_ReceivedJohtoStarter
	removeobject LOCALID_FRANKS_LAB_CHIKORITA_BALL
	msgbox gText_NicknameThisPokemon, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, Trashburg_ProfessorFranksLab_EventScript_ChikoritaTransferredToPC
	call Common_EventScript_NameReceivedBoxMon
	goto Trashburg_ProfessorFranksLab_EventScript_ChikoritaTransferredToPC
	end

Trashburg_ProfessorFranksLab_EventScript_ChikoritaTransferredToPC::
	call Common_EventScript_TransferredToPC
	goto Trashburg_ProfessorFranksLab_EventScript_ReceivedChikorita
	end

Trashburg_ProfessorFranksLab_EventScript_ReceivedChikorita::
	hidemonpic
	msgbox Trashburg_ProfessorFranksLab_Text_GrassyPatchWaiting, MSGBOX_DEFAULT
	setvar VAR_DEX_UPGRADE_JOHTO_STARTER_STATE, 6
	releaseall
	end

Trashburg_ProfessorFranksLab_EventScript_ReceivedJohtoStarter::
	playfanfare MUS_OBTAIN_ITEM
	message Trashburg_ProfessorFranksLab_Text_ReceivedJohtoStarter
	waitmessage
	waitfanfare
	return

Trashburg_ProfessorFranksLab_EventScript_Frank::
	lock
	faceplayer
	goto_if_eq VAR_DEX_UPGRADE_JOHTO_STARTER_STATE, 5, Trashburg_ProfessorFranksLab_EventScript_CanHaveAnyOneOfRarePokemon
	goto_if_eq VAR_DEX_UPGRADE_JOHTO_STARTER_STATE, 2, Trashburg_ProfessorFranksLab_EventScript_GrassyPatchWaiting
	goto_if_unset FLAG_HAS_MATCH_CALL, Trashburg_ProfessorFranksLab_EventScript_TryRatePokedexOrRegister
	goto_if_unset FLAG_ENABLE_PROF_FRANK_MATCH_CALL, EventScript_RegisterProfFrank
	goto Trashburg_ProfessorFranksLab_EventScript_TryRatePokedexOrRegister
	end

Trashburg_ProfessorFranksLab_EventScript_CanHaveAnyOneOfRarePokemon::
	msgbox Trashburg_ProfessorFranksLab_Text_CanHaveAnyOneOfRarePokemon, MSGBOX_DEFAULT
	release
	end

Trashburg_ProfessorFranksLab_EventScript_GrassyPatchWaiting::
	msgbox Trashburg_ProfessorFranksLab_Text_GrassyPatchWaiting2, MSGBOX_DEFAULT
	release
	end

Trashburg_ProfessorFranksLab_EventScript_TryRatePokedexOrRegister::
	goto_if_unset FLAG_HIDE_TRASHBURG_FRANKS_LAB_UNKNOWN_0x380, ProfFrank_EventScript_RatePokedexOrRegister
	goto_if_eq VAR_DEX_UPGRADE_JOHTO_STARTER_STATE, 3, ProfFrank_EventScript_RatePokedexOrRegister
	goto_if_ge VAR_DEX_UPGRADE_JOHTO_STARTER_STATE, 6, ProfFrank_EventScript_RatePokedexOrRegister
	goto_if_eq VAR_FRANK_LAB_STATE, 5, Trashburg_ProfessorFranksLab_EventScript_PokemonAwait
	msgbox Trashburg_ProfessorFranksLab_Text_FrankRivalGoneHome, MSGBOX_DEFAULT
	release
	end

EventScript_RegisterProfFrank::
	msgbox MatchCall_Text_FrankRegisterCall, MSGBOX_DEFAULT
	closemessage
	delay 30
	playfanfare MUS_REGISTER_MATCH_CALL
	msgbox MatchCall_Text_RegisteredFrank, MSGBOX_DEFAULT
	waitfanfare
	closemessage
	delay 30
	setflag FLAG_ENABLE_PROF_FRANK_MATCH_CALL
	setvar VAR_REGISTER_FRANK_STATE, 2
	release
	end

Trashburg_ProfessorFranksLab_EventScript_GivePokedex::
	msgbox Trashburg_ProfessorFranksLab_Text_HeardYouBeatRivalTakePokedex, MSGBOX_DEFAULT
	call Trashburg_ProfessorFranksLab_EventScript_ReceivePokedex
	msgbox Trashburg_ProfessorFranksLab_Text_ExplainPokedex, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_FRANKS_LAB_RIVAL, Trashburg_ProfessorFranksLab_Movement_RivalApproachPlayer
	waitmovement 0
	applymovement LOCALID_PLAYER, Common_Movement_WalkInPlaceFasterRight
	waitmovement 0
	checkplayergender
	call_if_eq VAR_RESULT, MALE, Trashburg_ProfessorFranksLab_EventScript_MayGivePokeBalls
	call_if_eq VAR_RESULT, FEMALE, Trashburg_ProfessorFranksLab_EventScript_BrendanGivePokeBalls
	setvar VAR_FRANK_LAB_STATE, 5
	setflag FLAG_ADVENTURE_STARTED
	setvar VAR_TRASHBURG_RIVAL_STATE, 4
	setvar VAR_TRASHBURG_STATE, 3
	applymovement LOCALID_PLAYER, Common_Movement_WalkInPlaceFasterUp
	waitmovement 0
	msgbox Trashburg_ProfessorFranksLab_Text_EggScamQuest1
	giveegg SPECIES_RATTATA_ALOLA
	goto_if_eq VAR_RESULT, MON_GIVEN_TO_PARTY, Trashburg_ProfessorFranksLab_EventScript_CharlieEggToParty
	goto_if_eq VAR_RESULT, MON_GIVEN_TO_PC, Trashburg_ProfessorFranksLab_EventScript_CharlieEggToPC
	msgbox Trashburg_ProfessorFranksLab_Text_NoRoomForEgg, MSGBOX_DEFAULT
	releaseall
	end

Trashburg_ProfessorFranksLab_EventScript_MayGivePokeBalls::
	msgbox Trashburg_ProfessorFranksLab_Text_MayGotPokedexTooTakeThese, MSGBOX_DEFAULT
	giveitem ITEM_POKE_BALL, 20
	call_if_eq VAR_RESULT, FALSE, Trashburg_ProfessorFranksLab_EventScript_MayNoRoomForPokeBalls
	msgbox Trashburg_ProfessorFranksLab_Text_CatchCutePokemonWithPokeBalls, MSGBOX_DEFAULT
	setvar VAR_RESULT, 0
	return

Trashburg_ProfessorFranksLab_EventScript_BrendanGivePokeBalls::
	msgbox Trashburg_ProfessorFranksLab_Text_BrendanGotPokedexTooTakeThese, MSGBOX_DEFAULT
	giveitem ITEM_POKE_BALL, 20
	call_if_eq VAR_RESULT, FALSE, Trashburg_ProfessorFranksLab_EventScript_BrendanNoRoomForPokeBalls
	msgbox Trashburg_ProfessorFranksLab_Text_CatchCoolPokemonWithPokeBalls, MSGBOX_DEFAULT
	setvar VAR_RESULT, 1
	return

Trashburg_ProfessorFranksLab_EventScript_ReceivePokedex::
	playfanfare MUS_OBTAIN_ITEM
	message Trashburg_ProfessorFranksLab_Text_ReceivedPokedex
	waitfanfare
	setflag FLAG_SYS_POKEDEX_GET
	special SetUnlockedPokedexFlags
	setflag FLAG_RECEIVED_POKEDEX_FROM_FRANK
	setvar VAR_CABLE_CLUB_TUTORIAL_STATE, 1
	return

Trashburg_ProfessorFranksLab_EventScript_PokemonAwait::
	lock
	faceplayer
	questmenu QUEST_MENU_CHECK_REWARD, QUEST_2_EGG_SCAM
	goto_if_ne VAR_RESULT, TRUE, Trashburg_ProfessorFranksLab_EventScript_PokemonAwait_AlreadyCompleted
	msgbox Trashburg_ProfessorFranksLab_Text_EggScamTurnInGreeting, MSGBOX_DEFAULT
	waitmessage
	completequest QUEST_2_EGG_SCAM
	setvar VAR_OLD_SCUMPORT_TOWN_STATE, 1
	applymovement LOCALID_PLAYER, Common_Movement_WalkInPlaceFasterUp
	waitmovement 0
	msgbox Trashburg_ProfessorFranksLab_Text_GoAdventure, MSGBOX_DEFAULT
	waitmessage
	release
	end

Trashburg_ProfessorFranksLab_EventScript_PokemonAwait_AlreadyCompleted::
	msgbox Trashburg_ProfessorFranksLab_Text_CountlessPokemonAwait, MSGBOX_DEFAULT
	release
	end

Trashburg_ProfessorFranksLab_EventScript_MayNoRoomForPokeBalls::
	msgbox Trashburg_ProfessorFranksLab_Text_OhYourBagsFull, MSGBOX_DEFAULT
	return

Trashburg_ProfessorFranksLab_EventScript_BrendanNoRoomForPokeBalls::
	msgbox Trashburg_ProfessorFranksLab_Text_HeyYourBagsFull, MSGBOX_DEFAULT
	return

Trashburg_ProfessorFranksLab_Movement_RivalApproachPlayer:
	walk_down
	walk_in_place_faster_left
	step_end

Trashburg_ProfessorFranksLab_EventScript_Machine::
	msgbox Trashburg_ProfessorFranksLab_Text_SeriousLookingMachine, MSGBOX_SIGN
	end

Trashburg_ProfessorFranksLab_EventScript_Rival::
	lock
	faceplayer
	goto_if_eq VAR_DEX_UPGRADE_JOHTO_STARTER_STATE, 5, Trashburg_ProfessorFranksLab_EventScript_RivalFuturePlans
	goto_if_ge VAR_DEX_UPGRADE_JOHTO_STARTER_STATE, 6, Trashburg_ProfessorFranksLab_EventScript_RivalHaveYouGoneToBattleFrontier
	goto_if_ge VAR_DEX_UPGRADE_JOHTO_STARTER_STATE, 2, Trashburg_ProfessorFranksLab_EventScript_RivalTakeBreakFromFieldwork
	checkplayergender
	call_if_eq VAR_RESULT, MALE, Trashburg_ProfessorFranksLab_EventScript_MayWhereShouldIGoNext
	call_if_eq VAR_RESULT, FEMALE, Trashburg_ProfessorFranksLab_EventScript_BrendanWhereShouldIGoNext
	release
	end

Trashburg_ProfessorFranksLab_EventScript_MayWhereShouldIGoNext::
	msgbox Trashburg_ProfessorFranksLab_Text_MayWhereShouldIGoNext, MSGBOX_DEFAULT
	return

Trashburg_ProfessorFranksLab_EventScript_BrendanWhereShouldIGoNext::
	msgbox Trashburg_ProfessorFranksLab_Text_BrendanWhereShouldIGoNext, MSGBOX_DEFAULT
	return

Trashburg_ProfessorFranksLab_EventScript_RivalFuturePlans::
	checkplayergender
	call_if_eq VAR_RESULT, MALE, Trashburg_ProfessorFranksLab_EventScript_MayWhatNextImStayingHere
	call_if_eq VAR_RESULT, FEMALE, Trashburg_ProfessorFranksLab_EventScript_BrendanPreferCollectingSlowly
	release
	end

Trashburg_ProfessorFranksLab_EventScript_MayWhatNextImStayingHere::
	msgbox Trashburg_ProfessorFranksLab_Text_MayWhatNextImStayingHere, MSGBOX_DEFAULT
	return

Trashburg_ProfessorFranksLab_EventScript_BrendanPreferCollectingSlowly:
	msgbox Trashburg_ProfessorFranksLab_Text_BrendanPreferCollectingSlowly, MSGBOX_DEFAULT
	return

Trashburg_ProfessorFranksLab_EventScript_RivalHaveYouGoneToBattleFrontier::
	checkplayergender
	call_if_eq VAR_RESULT, MALE, Trashburg_ProfessorFranksLab_EventScript_MayHaveYouGoneToBattleFrontier
	call_if_eq VAR_RESULT, FEMALE, Trashburg_ProfessorFranksLab_EventScript_BrendanHaveYouGoneToBattleFrontier
	release
	end

Trashburg_ProfessorFranksLab_EventScript_MayHaveYouGoneToBattleFrontier::
	msgbox Trashburg_ProfessorFranksLab_Text_MayHaveYouGoneToBattleFrontier, MSGBOX_DEFAULT
	return

Trashburg_ProfessorFranksLab_EventScript_BrendanHaveYouGoneToBattleFrontier::
	msgbox Trashburg_ProfessorFranksLab_Text_BrendanHaveYouGoneToBattleFrontier, MSGBOX_DEFAULT
	return

Trashburg_ProfessorFranksLab_EventScript_RivalTakeBreakFromFieldwork::
	checkplayergender
	call_if_eq VAR_RESULT, MALE, Trashburg_ProfessorFranksLab_EventScript_MayTakeBreakFromFieldwork
	call_if_eq VAR_RESULT, FEMALE, Trashburg_ProfessorFranksLab_EventScript_BrendanTakeBreakFromFieldwork
	release
	end

Trashburg_ProfessorFranksLab_EventScript_MayTakeBreakFromFieldwork::
	msgbox Trashburg_ProfessorFranksLab_Text_MayTakeBreakFromFieldwork, MSGBOX_DEFAULT
	return

Trashburg_ProfessorFranksLab_EventScript_BrendanTakeBreakFromFieldwork::
	msgbox Trashburg_ProfessorFranksLab_Text_BrendanTakeBreakFromFieldwork, MSGBOX_DEFAULT
	return

Trashburg_ProfessorFranksLab_EventScript_PC::
	msgbox Trashburg_ProfessorFranksLab_Text_PCUsedForResearch, MSGBOX_SIGN
	end

Trashburg_ProfessorFranksLab_EventScript_Bookshelf::
	msgbox Trashburg_ProfessorFranksLab_Text_CrammedWithBooksOnPokemon, MSGBOX_SIGN
	end

Trashburg_ProfessorFranksLab_EventScript_Book::
	msgbox Trashburg_ProfessorFranksLab_Text_BookTooHardToRead, MSGBOX_SIGN
	end

Trashburg_ProfessorFranksLab_EventScript_ScottAboardSSTidalCall::
	lockall
	pokenavcall Trashburg_ProfessorFranksLab_Text_ScottAboardSSTidalCall
	waitmessage
	clearflag FLAG_SCOTT_CALL_BATTLE_FRONTIER
	releaseall
	end

Trashburg_ProfessorFranksLab_Text_FrankAwayOnFieldwork:
	.string "Huh? PROF. FRANK?\p"
	.string "Yeah, he said something about\n"
	.string "'rat research' and ran off into\l"
	.string "the woods with a trash bag.\p"
	.string "Fieldwork, I guess. That's what he\n"
	.string "calls it.\p"
	.string "He hates desk stuff. Says it gives\n"
	.string "him 'mind cramps'.$"

Trashburg_ProfessorFranksLab_Text_FrankIsntOneForDeskWork:
	.string "The PROF hates standing still.\p"
	.string "He says desks are a\n"
	.string "'trap by the man'.\p"
	.string "He'd rather be out dumpster diving\n"
	.string "for data.\p"
	.string "Calls it his 'natural habitat.$"

Trashburg_ProfessorFranksLab_Text_FrankEnjoysRivalsHelpToo:
	.string "PROF. FRANK says Margaret helps\n"
	.string "sometimes.\p"
	.string "Mostly just stares, but he claims\n"
	.string "it 'opens up the mind'.\p"
	.string "Says her energy calms the\n"
	.string "squirrels in his head.\p"
	.string "That man has donkey brains for sure.$"

Trashburg_ProfessorFranksLab_Text_LikeYouToHavePokemon:
	.string "PROF. FRANK: So, {PLAYER}\p"
	.string "You’re weird, and honestly, that’s\n"
	.string "a plus.\p"
	.string "You handled that rat like a champ.\n"
	.string "Didn’t even scream. That’s rare.\p"
	.string "So here.\n"
	.string "Take the POKéMON you used.\p"
	.string "No refunds, no warranties.\p"
	.string "You have a connection.\p"
	.string "{PLAYER} received the {STR_VAR_1}!$"


Trashburg_ProfessorFranksLab_Text_WhyNotGiveNicknameToMon:
	.string "PROF. FRANK: Wanna give it a nickname?\n"
	.string "Named mine ‘Tooth Knife’ once.$"

Trashburg_ProfessorFranksLab_Text_MightBeGoodIdeaToGoSeeRival:
	.string "PROF. FRANK: Alright, listen up Charlie.\p"
	.string "This ain’t your little grandma’s\n"
	.string "Pokémon crap anymore.\p"
	.string "Your lead critter? Yeah, it’s gonna\n"
	.string "follow you around now. Real close.\l"
	.string "You can spin around, poke at it, whatever.\p"
	.string "But hey, watch yourself.\p"
	.string "You piss it off, it’s gonna\n"
	.string "take a chunk outta your ass.\p"
	.string "Anyways, you wanna go train?\n"
	.string "Go find Margaret.$"

Trashburg_ProfessorFranksLab_Text_GetRivalToTeachYou:
	.string "PROF. FRANK: Yeah, let Margaret show you\n"
	.string "the ropes.\p"
	.string "She is way up north on ROUTE 103\n"
	.string "doing some research.\p"
	.string "You'll have to pass through\n"
	.string "OLD SCUMPORT too.\p"
	.string "There's a POKéCENTER there. Be sure\n"
	.string "to stop in. I think you'll really enjoy\l"
	.string "it in there Charlie!\p"
	.string "Haha!$"


Trashburg_ProfessorFranksLab_Text_DontBeThatWay:
	.string "PROF. FRANK: What, nervous?\p"
	.string "Don’t be. Margaret rarely mauls people\n"
	.string "on weekdays.\p"
	.string "Just keep eye contact and never blink.$"

Trashburg_ProfessorFranksLab_Text_FrankRivalGoneHome:
	.string "PROF. FRANK: Margaret? Probably lurking\n"
	.string "somewhere. Maybe ROUTE 103?\p"
	.string "Last I saw her, she was staring at a\n"
	.string "tree stump giving it crazy eyes.\p"
	.string "Head north. Or don’t. Life’s about\n"
	.string "choices.$"

Trashburg_ProfessorFranksLab_Text_HeardYouBeatRivalTakePokedex:
	.string "PROF. FRANK: You beat Margaret?\n"
	.string "Impressive.\p"
	.string "She once stared down a Tauros\n"
	.string "into submission.\p"
	.string "Here, take this POKéDEX.\n"
	.string "It’s not booby-trapped...$"

Trashburg_ProfessorFranksLab_Text_ReceivedPokedex:
	.string "{PLAYER} received the POKéDEX!$"

Trashburg_ProfessorFranksLab_Text_ExplainPokedex:
	.string "PROF. FRANK: That thing records all of\n"
	.string "the POKéMON you see and catch.\p"
	.string "Also glows in the dark.\n"
	.string "Don’t ask why.\p"
	.string "Margaret uses hers like a mirror.\n"
	.string "For what, I can’t say. She’s an enigma.$"

Trashburg_ProfessorFranksLab_Text_CountlessPokemonAwait:
	.string "PROF. FRANK: There’s a whole world\n"
	.string "of POKéMON.\p"
	.string "Most bite.\p"
	.string "Some explode.\p"
	.string "All magical.\p"
	.string "Go roll around in the weirdness, kid.$"

Trashburg_ProfessorFranksLab_Text_MayGotPokedexTooTakeThese:
	.string "MARGARET stares into your soul.\p"
	.string "She hands you POKé BALLS without\n"
	.string "blinking.\p"
	.string "You feel judged and strangely empowered.$"

Trashburg_ProfessorFranksLab_Text_CatchCutePokemonWithPokeBalls:
	.string "Margaret raises an eyebrow,\n"
	.string "and points at her POKé BALLS.\p"
	.string "It’s either a warning,\n"
	.string "or an invitation to a duel.\p"
	.string "Interpret freely.$"

Trashburg_ProfessorFranksLab_Text_OhYourBagsFull:
	.string "Ah c'mon. Your BAG's full.$"

Trashburg_ProfessorFranksLab_Text_MayWhereShouldIGoNext:
	.string "Margaret nods slightly at the horizon.\n"
	.string "You suddenly feel the weight of destiny.$"

Trashburg_ProfessorFranksLab_Text_BrendanGotPokedexTooTakeThese:
	.string "BRENDAN: Huh…\n"
	.string "So you got a POKéDEX, too.\p"
	.string "Well then, here.\n"
	.string "I'll give you these.$"

Trashburg_ProfessorFranksLab_Text_CatchCoolPokemonWithPokeBalls:
	.string "BRENDAN: You know it's more fun to\n"
	.string "have a whole bunch of POKéMON.\p"
	.string "I'm going to explore all over the place\n"
	.string "to find different POKéMON.\p"
	.string "If I find any cool POKéMON, you bet\n"
	.string "I'll try to get them with POKé BALLS.$"

Trashburg_ProfessorFranksLab_Text_HeyYourBagsFull:
	.string "Hey, your BAG's full.$"

Trashburg_ProfessorFranksLab_Text_BrendanWhereShouldIGoNext:
	.string "BRENDAN: Where should I look for\n"
	.string "POKéMON next…$"

Trashburg_ProfessorFranksLab_Text_SeriousLookingMachine:
	.string "It's a serious-looking machine.\n"
	.string "The PROF must use this for research.$"

Trashburg_ProfessorFranksLab_Text_PCUsedForResearch:
	.string "It's a PC used for research.\n"
	.string "Better not mess around with it.$"

Trashburg_ProfessorFranksLab_Text_CrammedWithBooksOnPokemon:
	.string "It's crammed with books on POKéMON.$"

Trashburg_ProfessorFranksLab_Text_BookTooHardToRead:
	.string "It's a book that's too hard to read.$"

Trashburg_ProfessorFranksLab_Text_OtherRegionsUpgradeToNational:
	.string "PROF. FRANK: Now…\p"
	.string "{PLAYER}{KUN} and {RIVAL}, I've had the two\n"
	.string "of you help me study POKéMON.\p"
	.string "Thanks to your help, new facts\n"
	.string "are coming to light.\p"
	.string "It appears that in the HOENN region,\n"
	.string "there are also POKéMON from other\l"
	.string "regions.\p"
	.string "It goes to show how rich and varied\n"
	.string "the natural environments of HOENN\l"
	.string "happen to be.\p"
	.string "That's why I think it's necessary for\n"
	.string "me to upgrade your POKéDEX to\l"
	.string "the NATIONAL Mode.\p"
	.string "Here, let me see your POKéDEX units.$"

Trashburg_ProfessorFranksLab_Text_MayUpgradeSoCool:
	.string "MAY: Eheheh!\p"
	.string "It's so cool that even my POKéDEX\n"
	.string "is getting updated!\p"
	.string "It's because you went out and caught\n"
	.string "so many POKéMON, {PLAYER}{KUN}!$"

Trashburg_ProfessorFranksLab_Text_BrendanYouCanThankMe:
	.string "BRENDAN: I went out all over HOENN\n"
	.string "and checked out POKéMON.\p"
	.string "You can thank me for getting\n"
	.string "the NATIONAL Mode POKéDEX.\p"
	.string "Yep, you're lucky, {PLAYER}!$"

Trashburg_ProfessorFranksLab_Text_OkayAllDone:
	.string "PROF. FRANK: Okay, all done!$"

Trashburg_ProfessorFranksLab_Text_PokedexUpgradedToNational:
	.string "{PLAYER}'s POKéDEX was upgraded\n"
	.string "to the NATIONAL Mode!$"

Trashburg_ProfessorFranksLab_Text_GrassyPatchWaiting2:
	.string "PROF. FRANK: But listen.\n"
	.string "You've become the CHAMPION,\l"
	.string "but your POKéMON journey isn't over.\p"
	.string "There is no end to the road\n"
	.string "that is POKéMON.\p"
	.string "Somewhere, there is a grassy patch\n"
	.string "that's waiting for you!$"

Trashburg_ProfessorFranksLab_Text_MayTakeBreakFromFieldwork:
	.string "MAY: I think I'll take a short break\n"
	.string "from fieldwork.\p"
	.string "I think I'll help the PROF here for\n"
	.string "a while.$"

Trashburg_ProfessorFranksLab_Text_BrendanTakeBreakFromFieldwork:
	.string "BRENDAN: For the time being,\n"
	.string "I'm taking a break from fieldwork.\p"
	.string "I'll be helping out the PROF here\n"
	.string "for a while.$"

Trashburg_ProfessorFranksLab_Text_CompletedDexChoosePokemon:
	.string "PROF. FRANK: Oh, {PLAYER}{KUN}!\n"
	.string "Let's have a look at your POKéDEX.\p"
	.string "… … … … … …\n"
	.string "… … … … … …\p"
	.string "Yes, there's no doubt about it.\p"
	.string "You really have completed the HOENN\n"
	.string "region's POKéDEX.\p"
	.string "That's more than just impressive.\p"
	.string "I have a gift for you.\p"
	.string "Consider it my show of appreciation\n"
	.string "for the fantastic work you've done.\p"
	.string "My gift is a rare POKéMON only found\n"
	.string "in another region!\p"
	.string "You can have any one of these\n"
	.string "three POKéMON!$"

Trashburg_ProfessorFranksLab_Text_CanHaveAnyOneOfRarePokemon:
	.string "PROF. FRANK: These are rare POKéMON\n"
	.string "only found in another region!\p"
	.string "You can have any one of these\n"
	.string "three POKéMON!$"

Trashburg_ProfessorFranksLab_Text_YoullTakeCyndaquil:
	.string "PROF. FRANK: The FIRE POKéMON\n"
	.string "CYNDAQUIL caught your eye!\p"
	.string "You're as sharp as ever!\p"
	.string "So the CYNDAQUIL is your choice?$"

Trashburg_ProfessorFranksLab_Text_YoullTakeTotodile:
	.string "PROF. FRANK: The WATER POKéMON\n"
	.string "TOTODILE is your choice!\p"
	.string "You know how to pick a good one.\p"
	.string "So, you'll take the TOTODILE?$"

Trashburg_ProfessorFranksLab_Text_YoullTakeChikorita:
	.string "PROF. FRANK: The GRASS POKéMON\n"
	.string "CHIKORITA is your choice!\p"
	.string "You sure know what you're doing.\p"
	.string "So, you'll take the CHIKORITA?$"

Trashburg_ProfessorFranksLab_Text_TakeYourTimeAllInvaluable:
	.string "PROF. FRANK: Take your time before\n"
	.string "you decide.\p"
	.string "They're all invaluable POKéMON.$"

@ Unused
Trashburg_ProfessorFranksLab_Text_PickedFinePokemon:
	.string "PROF. FRANK: I see!\n"
	.string "You picked a fine POKéMON!$"

Trashburg_ProfessorFranksLab_Text_ReceivedJohtoStarter:
	.string "{PLAYER} received the {STR_VAR_1}\n"
	.string "from PROF. FRANK!$"

@ Unused
Trashburg_ProfessorFranksLab_Text_NicknameJohtoStarter:
	.string "Want to give a nickname to\n"
	.string "the {STR_VAR_1} you received?$"

Trashburg_ProfessorFranksLab_Text_GrassyPatchWaiting:
	.string "PROF. FRANK: Listen, {PLAYER}{KUN}.\n"
	.string "You've completed the HOENN POKéDEX,\l"
	.string "but your POKéMON journey isn't over.\p"
	.string "There is no end to the road\n"
	.string "that is POKéMON.\p"
	.string "Somewhere, there is a grassy patch\n"
	.string "that's waiting for you!$"

Trashburg_ProfessorFranksLab_Text_BetterLeaveOthersAlone:
	.string "You received the promised POKéMON.\n"
	.string "Better leave the others alone.$"

@ Unused
Trashburg_ProfessorFranksLab_Text_DontHaveAnyRoomForPokemon:
	.string "Oh, you don't have any room for\n"
	.string "this POKéMON.$"

Trashburg_ProfessorFranksLab_Text_MayWhatNextImStayingHere:
	.string "MAY: {PLAYER}{KUN}, after this…\n"
	.string "What are you going to do?\p"
	.string "Are you going to keep battling\n"
	.string "and sharpening your skills?\p"
	.string "Or are you going to try filling\n"
	.string "the NATIONAL POKéDEX?\p"
	.string "I'm staying here to help the PROF.$"

Trashburg_ProfessorFranksLab_Text_BrendanPreferCollectingSlowly:
	.string "BRENDAN: Rather than collecting\n"
	.string "POKéMON, I prefer slowly and \l"
	.string "steadily raising the one I chose.$"

Trashburg_ProfessorFranksLab_Text_MayHaveYouGoneToBattleFrontier:
	.string "MAY: Oh, hi, {PLAYER}{KUN}!\n"
	.string "Have you gone to that place,\l"
	.string "the BATTLE FRONTIER?$"

Trashburg_ProfessorFranksLab_Text_BrendanHaveYouGoneToBattleFrontier:
	.string "BRENDAN: Hey, {PLAYER}!\n"
	.string "Have you gone out to that place,\l"
	.string "the BATTLE FRONTIER?$"

Trashburg_ProfessorFranksLab_Text_ScottAboardSSTidalCall:
	.string "… … … … … …\n"
	.string "… … … … … Beep!\p"
	.string "SCOTT: Hi, hi, {PLAYER}!\n"
	.string "It's me, SCOTT.\p"
	.string "I'm aboard the S.S. TIDAL now.\n"
	.string "It feels great to be on the sea!\p"
	.string "By the way…\p"
	.string "There's this place that I'd like to\n"
	.string "invite you to for a visit.\p"
	.string "If you're interested, board a ferry\n"
	.string "at either SLATEPORT or LILYCOVE.\p"
	.string "I'll fill you in on the details when\n"
	.string "we meet. I'll be waiting!\p"
	.string "… … … … … …\n"
	.string "… … … … … Click!$"

Trashburg_ProfessorFranksLab_Text_EggScamQuest1:
	.string "PROF. FRANK: Oh, before you go,\n"
	.string "I found this egg.\p"
	.string "It must be a special egg. It smells\n"
	.string "like a dumpster behind a seafood joint.\p"
	.string "Around here, we don't get eggs that\n"
	.string "smell this ripe.\p"
	.string "Do me a favor will ya. Bring this egg\n"
	.string "over to the mart in OLD SCUMPORT and\l"
	.string "see how much you can get for it.\p"
	.string "Come back and let me know what happens.\n"
	.string "I'll give you a cut of the profit!$"

Trashburg_ProfessorFranksLab_Text_ReceivedEgg:
	.string "Charlie received a smelly EGG from\n"
	.string "PROF. FRANK!$"

Trashburg_ProfessorFranksLab_Text_NoRoomForEgg:
	.string "Oh, you don’t have any room for\n"
	.string "this EGG.$"

Trashburg_ProfessorFranksLab_EventScript_CharlieEggToParty::
	playfanfare MUS_OBTAIN_ITEM
	msgbox Trashburg_ProfessorFranksLab_Text_ReceivedEgg, MSGBOX_DEFAULT
	waitfanfare
	startquest QUEST_2_EGG_SCAM
	release
	end

Trashburg_ProfessorFranksLab_EventScript_CharlieEggToPC::
	playfanfare MUS_OBTAIN_ITEM
	msgbox Trashburg_ProfessorFranksLab_Text_ReceivedEgg, MSGBOX_DEFAULT
	waitfanfare
	call Common_EventScript_TransferredToPC
	startquest QUEST_2_EGG_SCAM
	release
	end

Trashburg_ProfessorFranksLab_Text_EggScamTurnInGreeting:
	.string "..... ..... ..... .....\p"
	.string "The clerk said what?!?\p"
	.string "Aw crap, I guess he figured it out...\p"
	.string "Thats fine, I've got plenty of other\n"
	.string "tricks up my sleeve.$"

Trashburg_ProfessorFranksLab_Text_GoAdventure:
	.string "Go ahead and keep that egg. I can\n"
	.string "smell it from here.\p"
	.string "That's your reward. No profit,\n"
	.string "no money. You understand the\l"
	.string "business.\p"
	.string "You're welcome, Charlie.\p"
	.string "Now, Go out and adventure!\p"
	.string "If you go back to OLD SCUMPORT,\n"
	.string "make a left before the mart.\p"
	.string "There will be a little area\n"
	.string "to run through before the next town.$"
