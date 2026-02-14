Route103_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, Route103_OnTransition
	map_script MAP_SCRIPT_ON_LOAD, Route103_OnLoad
	.byte 0

Route103_OnTransition:
	call Common_EventScript_SetupRivalGfxId
	call ProfBirch_EventScript_UpdateLocation
	end

Route103_OnLoad:
	call_if_set FLAG_SYS_GAME_CLEAR, Route103_EventScript_OpenAlteringCave
	end

Route103_EventScript_OpenAlteringCave::
	setmetatile 45, 5, METATILE_General_CaveEntrance_Top, TRUE
	setmetatile 45, 6, METATILE_General_CaveEntrance_Bottom, FALSE
	return

Route103_EventScript_Rival::
	lockall
	checkplayergender
	goto_if_eq VAR_RESULT, MALE, Route103_EventScript_RivalMay
	goto_if_eq VAR_RESULT, FEMALE, Route103_EventScript_RivalMay
	end

Route103_EventScript_RivalMay::
	msgbox Route103_Text_MayRoute103Pokemon, MSGBOX_DEFAULT
	closemessage
	playbgm MUS_ENCOUNTER_MAY, TRUE
	applymovement LOCALID_ROUTE103_RIVAL, Common_Movement_FacePlayer
	waitmovement 0
	applymovement LOCALID_ROUTE103_RIVAL, Common_Movement_ExclamationMark
	waitmovement 0
	applymovement LOCALID_ROUTE103_RIVAL, Common_Movement_Delay48
	waitmovement 0
	switch VAR_STARTER_MON
	case 0, Route103_EventScript_StartMayBattleBulbasaur
	case 1, Route103_EventScript_StartMayBattleGible
	case 2, Route103_EventScript_StartMayBattleAron
	end


Route103_EventScript_StartMayBattleBulbasaur::
	trainerbattle_no_whiteout_continue TRAINER_MAY_ROUTE_103_BULBASAUR, Route103_Text_MayLetsBattle, Route103_Text_MayDefeated
	goto Route103_EventScript_AfterMayBattle
	end

Route103_EventScript_StartMayBattleGible::
	trainerbattle_no_whiteout_continue TRAINER_MAY_ROUTE_103_GIBLE, Route103_Text_MayLetsBattle, Route103_Text_MayDefeated
	goto Route103_EventScript_AfterMayBattle
	end

Route103_EventScript_StartMayBattleAron::
	trainerbattle_no_whiteout_continue TRAINER_MAY_ROUTE_103_ARON, Route103_Text_MayLetsBattle, Route103_Text_MayDefeated
	goto Route103_EventScript_AfterMayBattle
	end

Route103_EventScript_AfterMayBattle::
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_eq VAR_RESULT, B_OUTCOME_LOST, Route103_EventScript_MayHealsAfterLoss
	msgbox Route103_Text_MayTimeToHeadBack, MSGBOX_DEFAULT
	goto Route103_EventScript_RivalExit
	end

Route103_EventScript_MayHealsAfterLoss::
	msgbox Route103_Text_MayDefeated, MSGBOX_DEFAULT
	msgbox Route103_Text_MayHealsParty, MSGBOX_DEFAULT
	call Common_EventScript_OutOfCenterPartyHeal
	msgbox Route103_Text_MayTimeToHeadBack, MSGBOX_DEFAULT
	goto Route103_EventScript_RivalExit
	end


Route103_EventScript_RivalExit::
	closemessage
	switch VAR_FACING
	case DIR_SOUTH, Route103_EventScript_RivalExitFacingSouth
	case DIR_NORTH, Route103_EventScript_RivalExitFacingNorth
	case DIR_WEST, Route103_EventScript_RivalExitFacingEastOrWest
	case DIR_EAST, Route103_EventScript_RivalExitFacingEastOrWest
	end

Route103_EventScript_RivalExitFacingNorth::
	applymovement LOCALID_PLAYER, Route103_Movement_WatchRivalExitFacingNorth
	applymovement LOCALID_ROUTE103_RIVAL, Route103_Movement_RivalExitFacingNorth1
	waitmovement 0
	playse SE_LEDGE
	applymovement LOCALID_ROUTE103_RIVAL, Route103_Movement_RivalExitFacingNorth2
	waitmovement 0
	goto Route103_EventScript_RivalEnd
	end

Route103_EventScript_RivalExitFacingEastOrWest::
	applymovement LOCALID_PLAYER, Route103_Movement_WatchRivalExitFacingEastOrWest
	applymovement LOCALID_ROUTE103_RIVAL, Route103_Movement_RivalExit1
	waitmovement 0
	playse SE_LEDGE
	applymovement LOCALID_ROUTE103_RIVAL, Route103_Movement_RivalExit2
	waitmovement 0
	goto Route103_EventScript_RivalEnd
	end

Route103_EventScript_RivalExitFacingSouth::
	applymovement LOCALID_ROUTE103_RIVAL, Route103_Movement_RivalExit1
	waitmovement 0
	playse SE_LEDGE
	applymovement LOCALID_ROUTE103_RIVAL, Route103_Movement_RivalExit2
	waitmovement 0
	goto Route103_EventScript_RivalEnd
	end

Route103_EventScript_RivalEnd::
	removeobject LOCALID_ROUTE103_RIVAL
	setvar VAR_BIRCH_LAB_STATE, 4
	clearflag FLAG_HIDE_LITTLEROOT_TOWN_BIRCHS_LAB_RIVAL
	setflag FLAG_DEFEATED_RIVAL_ROUTE103
	setvar VAR_OLDALE_RIVAL_STATE, 1
	clearflag FLAG_HIDE_OLDALE_TOWN_RIVAL
	savebgm MUS_DUMMY
	fadedefaultbgm
	releaseall
	end

Route103_Movement_RivalExitFacingNorth1:
	walk_left
	walk_down
	step_end

Route103_Movement_RivalExitFacingNorth2:
	walk_down
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	step_end

Route103_Movement_WatchRivalExitFacingNorth:
	delay_16
	delay_4
	walk_in_place_faster_left
	delay_16
	walk_in_place_faster_down
	step_end

Route103_Movement_RivalExit1:
	walk_down
	step_end

Route103_Movement_RivalExit2:
	delay_16
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	step_end

Route103_Movement_WatchRivalExitFacingEastOrWest:
	delay_16
	walk_in_place_down
	delay_16
	delay_16
	walk_in_place_faster_left
	step_end

Route103_EventScript_Boy::
	msgbox Route103_Text_ShouldHaveBroughtPotion, MSGBOX_NPC
	end

Route103_EventScript_Man::
	msgbox Route103_Text_ShortcutToOldale, MSGBOX_NPC
	end

Route103_EventScript_RouteSign::
	msgbox Route103_Text_RouteSign, MSGBOX_SIGN
	end

Route103_EventScript_Daisy::
	trainerbattle_single TRAINER_DAISY, Route103_Text_DaisyIntro, Route103_Text_DaisyDefeated
	msgbox Route103_Text_DaisyPostBattle, MSGBOX_AUTOCLOSE
	end

Route103_EventScript_Amy::
	trainerbattle_double TRAINER_AMY_AND_LIV_1, Route103_Text_AmyIntro, Route103_Text_AmyDefeated, Route103_Text_AmyNotEnoughPokemon, Route102_EventScript_AmyRegisterMatchCallAfterBattle
	specialvar VAR_RESULT, ShouldTryRematchBattle
	goto_if_eq VAR_RESULT, TRUE, Route102_EventScript_AmyRematch
	msgbox Route103_Text_AmyPostBattle, MSGBOX_AUTOCLOSE
	end

Route102_EventScript_AmyRegisterMatchCallAfterBattle::
	msgbox Route103_Text_AmyLivRegister, MSGBOX_DEFAULT
	register_matchcall TRAINER_AMY_AND_LIV_1
	release
	end

Route102_EventScript_AmyRematch::
	trainerbattle_rematch_double TRAINER_AMY_AND_LIV_1, Route103_Text_AmyRematchIntro, Route103_Text_AmyRematchDefeated, Route103_Text_AmyRematchNotEnoughPokemon
	msgbox Route103_Text_AmyRematchPostBattle, MSGBOX_AUTOCLOSE
	end

Route103_EventScript_Liv::
	trainerbattle_double TRAINER_AMY_AND_LIV_1, Route103_Text_LivIntro, Route103_Text_LivDefeated, Route103_Text_LivNotEnoughPokemon, Route102_EventScript_LivRegisterMatchCallAfterBattle
	specialvar VAR_RESULT, ShouldTryRematchBattle
	goto_if_eq VAR_RESULT, TRUE, Route102_EventScript_LivRematch
	msgbox Route103_Text_LivPostBattle, MSGBOX_AUTOCLOSE
	end

Route102_EventScript_LivRegisterMatchCallAfterBattle::
	msgbox Route103_Text_AmyLivRegister, MSGBOX_DEFAULT
	register_matchcall TRAINER_AMY_AND_LIV_1
	release
	end

Route102_EventScript_LivRematch::
	trainerbattle_rematch_double TRAINER_AMY_AND_LIV_1, Route103_Text_LivRematchIntro, Route103_Text_LivRematchDefeated, Route103_Text_LivRematchNotEnoughPokemon
	msgbox Route103_Text_LivRematchPostBattle, MSGBOX_AUTOCLOSE
	end

Route103_EventScript_Andrew::
	trainerbattle_single TRAINER_ANDREW, Route103_Text_AndrewIntro, Route103_Text_AndrewDefeated
	msgbox Route103_Text_AndrewPostBattle, MSGBOX_AUTOCLOSE
	end

Route103_EventScript_Miguel::
	trainerbattle_single TRAINER_MIGUEL_1, Route103_Text_MiguelIntro, Route103_Text_MiguelDefeated, Route102_EventScript_MiguelRegisterMatchCallAfterBattle
	specialvar VAR_RESULT, ShouldTryRematchBattle
	goto_if_eq VAR_RESULT, TRUE, Route103_EventScript_MiguelRematch
	msgbox Route103_Text_MiguelPostBattle, MSGBOX_DEFAULT
	release
	end

Route102_EventScript_MiguelRegisterMatchCallAfterBattle::
	special PlayerFaceTrainerAfterBattle
	waitmovement 0
	msgbox Route103_Text_MiguelRegister, MSGBOX_DEFAULT
	register_matchcall TRAINER_MIGUEL_1
	release
	end

Route103_EventScript_MiguelRematch::
	trainerbattle_rematch TRAINER_MIGUEL_1, Route103_Text_MiguelRematchIntro, Route103_Text_MiguelRematchDefeated
	msgbox Route103_Text_MiguelRematchPostBattle, MSGBOX_AUTOCLOSE
	end

Route103_EventScript_Marcos::
	trainerbattle_single TRAINER_MARCOS, Route103_Text_MarcosIntro, Route103_Text_MarcosDefeated
	msgbox Route103_Text_MarcosPostBattle, MSGBOX_AUTOCLOSE
	end

Route103_EventScript_Rhett::
	trainerbattle_single TRAINER_RHETT, Route103_Text_RhettIntro, Route103_Text_RhettDefeated
	msgbox Route103_Text_RhettPostBattle, MSGBOX_AUTOCLOSE
	end

Route103_EventScript_Pete::
	trainerbattle_single TRAINER_PETE, Route103_Text_PeteIntro, Route103_Text_PeteDefeated
	msgbox Route103_Text_PetePostBattle, MSGBOX_AUTOCLOSE
	end

Route103_EventScript_Isabelle::
	trainerbattle_single TRAINER_ISABELLE, Route103_Text_IsabelleIntro, Route103_Text_IsabelleDefeated
	msgbox Route103_Text_IsabellePostBattle, MSGBOX_AUTOCLOSE
	end

Route103_Text_MayRoute103Pokemon:
	.string "She squints at a wild POKéMON.\p"
	.string "Pulls out a notebook. Doodles something.\n"
	.string "It’s not accurate. But she nods anyway.$"

Route103_Text_MayLetsBattle:
	.string "She looks at you and smiles.\p"
	.string "She points at the POKéMON\n"
	.string "following you.\p"
	.string "Smirks. Shrugs. Cracks her neck\n"
	.string "like she's ready to scrap.\p"
	.string "She reaches into her pocket,\n"
	.string "pulls out a half-eaten granola bar,\l"
	.string "stares at it...\l"
	.string "then throws it over her shoulder.\p"
	.string "Battle time!$"

Route103_Text_MayDefeated:
	.string "She looks at you and nods,\n"
	.string "Then jots something in her notebook.\p"
	.string "You swear she writes 'Charlie is trash'.$"

Route103_Text_MayHealsParty:
	.string "She pulls out a small spray bottle\n"
	.string "and walks over to your POKéMON.\p"
	.string "Gives them a few quick spritzes.\n"
	.string "Your POKéMON perk up immediately.\p"
	.string "She nods approvingly and caps\n"
	.string "the bottle with a satisfied grunt.$"

Route103_Text_MayTimeToHeadBack:
	.string "She points at you. Then at her head.\n"
	.string "Then gives a thumbs-up.\p"
	.string "Your POKéMON like you.\n"
	.string "That annoys her, visibly\p"
	.string "She shrugs, then slowly walks away.$"


Route103_Text_ShouldHaveBroughtPotion:
	.string "Yo, my POKéMON’s runnin’ on fumes...\p"
	.string "Shoulda copped a POTION at the\n"
	.string "corner store.\p"
	.string "Now I’m out here lookin’ dumb.$"

Route103_Text_ShortcutToOldale:
	.string "Cross that water right there?\n"
	.string "Boom! Shortcut straight to OLD SCUMPORT.\p"
	.string "Yeah, f'real. That’s the move. Pro tip, kid.$"

Route103_Text_RouteSign:
	.string "ROUTE 103\n"
	.string "{DOWN_ARROW} OLD SCUMPORT$"

