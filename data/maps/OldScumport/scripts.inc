OldScumport_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, OldScumport_OnTransition
	.byte 0

OldScumport_OnTransition:
	call Common_EventScript_SetupRivalGfxId
	setflag FLAG_VISITED_OLD_SCUMPORT
	call_if_eq VAR_OLD_SCUMPORT_TOWN_STATE, 0, OldScumport_EventScript_BlockWestEntrance
	call_if_unset FLAG_RECEIVED_POTION_OLDALE, OldScumport_EventScript_MoveMartEmployee
	end

OldScumport_EventScript_BlockWestEntrance::
	setobjectxyperm LOCALID_FOOTPRINTS_MAN, 1, 11
	setobjectmovementtype LOCALID_FOOTPRINTS_MAN, MOVEMENT_TYPE_FACE_LEFT
	return

OldScumport_EventScript_MoveMartEmployee::
	setobjectxyperm LOCALID_OLD_SCUMPORTMART_EMPLOYEE, 10, 18
	setobjectmovementtype LOCALID_OLD_SCUMPORTMART_EMPLOYEE, MOVEMENT_TYPE_FACE_LEFT
	return

OldScumport_EventScript_TownSign::
	msgbox OldScumport_Text_TownSign, MSGBOX_SIGN
	end

OldScumport_EventScript_MartEmployee::
	lock
	faceplayer
	goto_if_set FLAG_RECEIVED_POTION_OLDALE, OldScumport_EventScript_ExplainPotion
	goto_if_set FLAG_TEMP_1, OldScumport_EventScript_ExplainPotion
	setflag FLAG_TEMP_1
	playbgm MUS_FOLLOW_ME, FALSE
	msgbox OldScumport_Text_IWorkAtPokemonMart, MSGBOX_DEFAULT
	closemessage
	end

OldScumport_EventScript_GoToMart::
	applymovement LOCALID_OLD_SCUMPORTMART_EMPLOYEE, OldScumport_Movement_EmployeeMart
	applymovement LOCALID_PLAYER, OldScumport_Movement_PlayerMart
	waitmovement 0
	goto OldScumport_EventScript_ExplainPokemonMart
	end

OldScumport_EventScript_ExplainPokemonMart::
	msgbox OldScumport_Text_ThisIsAPokemonMart, MSGBOX_DEFAULT
	giveitem ITEM_POTION, 10
	goto_if_eq VAR_RESULT, FALSE, OldScumport_EventScript_BagIsFull
	msgbox OldScumport_Text_PotionExplanation, MSGBOX_DEFAULT
	setflag FLAG_RECEIVED_POTION_OLDALE
	setvar VAR_MART_CALL, 1
	fadedefaultbgm
	release
	end

OldScumport_EventScript_ExplainPotion::
	msgbox OldScumport_Text_PotionExplanation, MSGBOX_DEFAULT
	release
	end

OldScumport_EventScript_BagIsFull::
	msgbox gText_TooBadBagIsFull, MSGBOX_DEFAULT
	fadedefaultbgm
	release
	end

OldScumport_Movement_EmployeeMart:
	walk_up
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
	walk_left
	walk_left
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_right
	walk_right
	walk_right
	walk_in_place_faster_left
	step_end

OldScumport_Movement_Unknown1:
	walk_up
	walk_up
	walk_right
	walk_right
	walk_right
	walk_right
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	delay_8
	walk_in_place_faster_down
	step_end

OldScumport_Movement_PlayerMart:
	delay_16
	delay_16
	delay_16
	walk_up
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
	walk_left
	walk_left
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_right
	walk_right
	step_end

OldScumport_Movement_Unknown2:
	walk_left
	walk_up
	walk_up
	walk_right
	walk_right
	walk_right
	walk_right
	walk_up
	walk_up
	walk_up
	walk_up
	step_end

OldScumport_EventScript_FootprintsMan::
	lock
	faceplayer
	goto_if_eq VAR_OLD_SCUMPORT_TOWN_STATE, 1, OldScumport_EventScript_NotBlockingPath
	msgbox OldScumport_Text_DiscoveredFootprints, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_FOOTPRINTS_MAN, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

OldScumport_EventScript_BlockedPath::
	lockall
	applymovement LOCALID_PLAYER, OldScumport_Movement_PlayerStepBack
	applymovement LOCALID_FOOTPRINTS_MAN, OldScumport_Movement_BackUp
	waitmovement 0
	msgbox OldScumport_Text_WaitDontComeInHere, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_FOOTPRINTS_MAN, OldScumport_Movement_ReturnToOriginalPosition
	waitmovement 0
	releaseall
	end

OldScumport_EventScript_NotBlockingPath::
	msgbox OldScumport_Text_FinishedSketchingFootprints, MSGBOX_DEFAULT
	release
	end

OldScumport_EventScript_MartEmployeeCall1::
	lockall
	applymovement LOCALID_OLD_SCUMPORTMART_EMPLOYEE, Common_Movement_ExclamationMark
	msgbox OldScumport_Text_HeyOverHere, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_PLAYER, Common_Movement_ExclamationMark
	waitmovement 0
	applymovement LOCALID_PLAYER, OldScumport_Movement_PlayerStepRight
	waitmovement 0
	msgbox OldScumport_Text_IWorkAtPokemonMart, MSGBOX_DEFAULT
	closemessage
	goto OldScumport_EventScript_GoToMart
	releaseall
	end

	OldScumport_EventScript_MartEmployeeCall2::
	lockall
	applymovement LOCALID_OLD_SCUMPORTMART_EMPLOYEE, Common_Movement_ExclamationMark
	msgbox OldScumport_Text_HeyOverHere, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_PLAYER, Common_Movement_ExclamationMark
	waitmovement 0
	applymovement LOCALID_PLAYER, OldScumport_Movement_PlayerStepRight
	waitmovement 0
	applymovement LOCALID_PLAYER, OldScumport_Movement_PlayerStepRight
	waitmovement 0
	msgbox OldScumport_Text_IWorkAtPokemonMart, MSGBOX_DEFAULT
	closemessage
	goto OldScumport_EventScript_GoToMart
	releaseall
	end

	OldScumport_EventScript_MartEmployeeCall3::
	lockall
	applymovement LOCALID_OLD_SCUMPORTMART_EMPLOYEE, Common_Movement_ExclamationMark
	msgbox OldScumport_Text_HeyOverHere, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_PLAYER, Common_Movement_ExclamationMark
	waitmovement 0
	applymovement LOCALID_PLAYER, OldScumport_Movement_PlayerStepRight
	waitmovement 0
	applymovement LOCALID_PLAYER, OldScumport_Movement_PlayerStepRight
	waitmovement 0
	applymovement LOCALID_PLAYER, OldScumport_Movement_PlayerStepRight
	waitmovement 0
	msgbox OldScumport_Text_IWorkAtPokemonMart, MSGBOX_DEFAULT
	closemessage
	goto OldScumport_EventScript_GoToMart
	releaseall
	end

OldScumport_EventScript_Rival::
	lockall
	applymovement LOCALID_OLD_SCUMPORTRIVAL, Common_Movement_FacePlayer
	waitmovement 0
	setvar VAR_0x8009, 0
	goto OldScumport_EventScript_ShowRivalMessage
	end

OldScumport_EventScript_RivalTrigger1::
	lockall
	applymovement LOCALID_OLD_SCUMPORTRIVAL, OldScumport_Movement_RivalApproachPlayer1
	waitmovement 0
	applymovement LOCALID_PLAYER, Common_Movement_WalkInPlaceFasterRight
	waitmovement 0
	setvar VAR_0x8009, 1
	goto OldScumport_EventScript_ShowRivalMessage
	end

OldScumport_EventScript_RivalTrigger2::
	lockall
	applymovement LOCALID_OLD_SCUMPORTRIVAL, OldScumport_Movement_RivalApproachPlayer2
	waitmovement 0
	applymovement LOCALID_PLAYER, Common_Movement_WalkInPlaceFasterRight
	waitmovement 0
	setvar VAR_0x8009, 1
	goto OldScumport_EventScript_ShowRivalMessage
	end

OldScumport_EventScript_RivalTrigger3::
	lockall
	applymovement LOCALID_OLD_SCUMPORTRIVAL, OldScumport_Movement_RivalApproachPlayer3
	waitmovement 0
	applymovement LOCALID_PLAYER, Common_Movement_WalkInPlaceFasterRight
	waitmovement 0
	setvar VAR_0x8009, 1
	goto OldScumport_EventScript_ShowRivalMessage
	end

OldScumport_EventScript_ShowRivalMessage::
	checkplayergender
	goto_if_eq VAR_RESULT, MALE, OldScumport_EventScript_ShowMayMessage
	goto_if_eq VAR_RESULT, FEMALE, OldScumport_EventScript_ShowBrendanMessage
	end

OldScumport_EventScript_ShowMayMessage::
	msgbox OldScumport_Text_MayLetsGoBack, MSGBOX_DEFAULT
	goto OldScumport_EventScript_RivalFinish
	end

OldScumport_EventScript_ShowBrendanMessage::
	msgbox OldScumport_Text_BrendanLetsGoBack, MSGBOX_DEFAULT
	goto OldScumport_EventScript_RivalFinish
	end

OldScumport_EventScript_RivalFinish::
	closemessage
	call_if_eq VAR_0x8009, 0, OldScumport_EventScript_DoExitMovement1
	call_if_eq VAR_0x8009, 1, OldScumport_EventScript_DoExitMovement2
	applymovement LOCALID_OLD_SCUMPORTRIVAL, OldScumport_Movement_RivalExit
	waitmovement 0
	removeobject LOCALID_OLD_SCUMPORTRIVAL
	setvar VAR_OLD_SCUMPORT_RIVAL_STATE, 2
	setflag FLAG_HIDE_OLD_SCUMPORT_RIVAL
	releaseall
	end

OldScumport_EventScript_DoExitMovement1::
	goto_if_ne VAR_FACING, DIR_SOUTH, OldScumport_EventScript_DoExitMovement2
	applymovement LOCALID_OLD_SCUMPORTRIVAL, OldScumport_Movement_RivalExit
	waitmovement 0
	return

OldScumport_EventScript_DoExitMovement2::
	applymovement LOCALID_PLAYER, OldScumport_Movement_WatchRivalExit
	applymovement LOCALID_OLD_SCUMPORTRIVAL, OldScumport_Movement_RivalExit
	waitmovement 0
	return

OldScumport_Movement_RivalApproachPlayer1:
	walk_left
	walk_left
	step_end

OldScumport_Movement_RivalApproachPlayer2:
	walk_left
	step_end

OldScumport_Movement_RivalApproachPlayer3:
	face_left
	step_end

OldScumport_Movement_RivalExit:
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	step_end

OldScumport_Movement_WatchRivalExit:
	delay_8
	delay_4
	walk_in_place_faster_down
	step_end

OldScumport_Movement_PlayerStepBack:
	lock_facing_direction
	walk_fast_right
	walk_right
	step_end

OldScumport_Movement_BackUp:
	walk_fast_up
	walk_in_place_fast_right
	delay_8
	walk_right
	step_end

OldScumport_Movement_ReturnToOriginalPosition:
	walk_down
	walk_left
	step_end

OldScumport_Movement_PlayerStepRight:
	walk_right
	step_end

OldScumport_Text_IWorkAtPokemonMart:
	.string "Yo!\n"
	.string "I hustle for the POKéMART.\p"
	.string "Wanna come with? I’ll hook you up.$"

OldScumport_Text_ThisIsAPokemonMart:
	.string "This? It’s a POKéMART.\n"
	.string "The blue roof means 'Buy shit.'\p"
	.string "We’ve got balls, meds, junk…\n"
	.string "you know, all you need out here.\p"
	.string "Here, I've got free samples.\p"
	.string "Don’t you even ask any questions.\n"
	.string "They fell off the truck...$"

OldScumport_Text_PotionExplanation:
	.string "POTIONS got that magic juice.\p"
	.string "Drink that shit and you feelin' good\n"
	.string "for a while.$"

OldScumport_Text_WaitDontComeInHere:
	.string "Yo! Yo! Back it up, bro.\n"
	.string "You can’t roll through here.\p"
	.string "I think I just found some rare-ass\n"
	.string "Pokémon prints or somethin’.\p"
	.string "Lemme get this down real quick.\p"
	.string "Don’t step in it, man.\p"
	.string "I ain’t jokin’.$"

OldScumport_Text_DiscoveredFootprints:
	.string "Aight, chill.\n"
	.string "I’m workin’ here.\p"
	.string "Could be ancient, y’know?\n"
	.string "Like legendary-level footprints.\p"
	.string "This is serious business. Back it up.$"

OldScumport_Text_FinishedSketchingFootprints:
	.string "Aight... done with the sketch.\p"
	.string "Wait...\p"
	.string "Yo, hold up.....\p"
	.string "These are my kicks?\p"
	.string "Haha! Damn, I’m the rare Pokémon.\p"
	.string "Tell the streets:\p"
	.string "I’m a freakin’ legend.$"

OldScumport_Text_MayLetsGoBack:
	.string "Margaret stares at you, wide-eyed.\p"
	.string "She jerks her thumb behind her,\n"
	.string "then takes off running.$"

OldScumport_Text_BrendanLetsGoBack:
	.string "BRENDAN: I'm heading back to my dad's\n"
	.string "LAB now.\l"
	.string "{PLAYER}, you should hustle back, too.$"

OldScumport_Text_TownSign:
	.string "OLD SCUMPORT\n"
	.string "“Scraped together, barely functional.”$"

OldScumport_Text_HeyOverHere:
	.string "Hey, you!\n"
	.string "Over here!$"

OldScumport_EventScript_LadyElizabeth::
    lock
    faceplayer
    goto_if_quest_complete QUEST_1_FIND_CHESTO, OldScumport_EventScript_LadyElizabeth_Completed
	goto_if_quest_active QUEST_1_FIND_CHESTO, OldScumport_EventScript_LadyElizabeth_CheckBerry
	goto OldScumport_EventScript_LadyElizabeth_Offer

OldScumport_EventScript_LadyElizabeth_Offer:
	msgbox OldScumport_Text_LadyElizabethIntroQuest, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, OldScumport_EventScript_LadyElizabeth_Accept
	msgbox OldScumport_Text_LadyElizabethDecline, MSGBOX_NPC
	release
	end

OldScumport_EventScript_LadyElizabeth_Accept:
	msgbox OldScumport_Text_LadyElizabethAccept, MSGBOX_NPC
	startquest QUEST_1_FIND_CHESTO 
	release
	end

OldScumport_EventScript_LadyElizabeth_CheckBerry:
    checkitem ITEM_CHESTO_BERRY, 1
    goto_if_eq VAR_RESULT, TRUE, OldScumport_EventScript_LadyElizabeth_TurnIn
    msgbox OldScumport_Text_LadyElizabethActiveNoBerry, MSGBOX_NPC
    release
    end	

OldScumport_EventScript_LadyElizabeth_TurnIn:
	faceplayer
	msgbox OldScumport_Text_LadyElizabethTurnIn, MSGBOX_NPC
	removeitem ITEM_CHESTO_BERRY, 1
	completequest QUEST_1_FIND_CHESTO
	msgbox OldScumport_Text_LadyElizabethTurnIn2, MSGBOX_NPC
	waitmessage
	playfanfare MUS_OBTAIN_ITEM
	msgbox OldScumport_Text_ReceivedMoney, MSGBOX_DEFAULT
	addmoney 500
	waitmessage
	release
	end

OldScumport_EventScript_LadyElizabeth_Completed:
	msgbox OldScumport_Text_LadyElizabethCompleted, MSGBOX_NPC
	release
	end

	OldScumport_Text_LadyElizabethIntroQuest:
	.string "LADY ELIZABETH: Yo!\n"
	.string "You look like you can handle a\l"
	.string "little errand for me.\p"
	.string "My Psyduck is knocked out cold thanks\n"
	.string "to a dumb Drowzee I was fightin'.\p"
	.string "I need a Chesto Berry to wake him up.\n"
	.string "Can you grab one for me?\p"
	.string "I’m not about to let that\n"
	.string "sleepyhead ruin my day!$"

OldScumport_Text_LadyElizabethAccept:
	.string "Sweet!\p"
	.string "Sometimes you'll see berry bushes\n"
	.string "growing out of soil. Maybe we can get\l"
	.string "lucky over on Route 102.\p"
	.string "If not, I think theres an older\n"
	.string "woman up by WAWA PARK that might have\l"
	.string "one.\p"
	.string "I can’t deal with this nonsense much\n"
	.string "longer.\p"
	.string "I swear,\n"
	.string "if I have to listen to him snore one\l"
	.string "more time...$"

OldScumport_Text_LadyElizabethDecline:
	.string "Look, I’m not going back after that\n"
	.string "Drowzee.\p"
	.string "I’ve got better things to do\n"
	.string "than play tag with a sleepy Pokémon.\p"
	.string "I’ll owe you one.$"

OldScumport_Text_LadyElizabethActiveNoBerry:
	.string "Hey, did you forget something?\n"
	.string "I’m still waiting on that Chesto Berry!\p"
	.string "My Psyduck is still snoozing over\n"
	.string "there, and I can’t have him\l"
	.string "missing out on the fun.\p"
	.string "Hurry it up, will ya?\n"
	.string "I can’t stand the sound of his snoring!$"

OldScumport_Text_LadyElizabethTurnIn:
	.string "No way, you actually found it?\n"
	.string "You’re a lifesaver!\p"
	.string "Now let’s wake up my Psyduck\n"
	.string "and get back to business.$"

OldScumport_Text_LadyElizabethTurnIn2:
	.string "Here's a little something for you.\n"
	.string "Thanks for your help!$"

OldScumport_Text_LadyElizabethCompleted:
	.string "Oh, look who it is!\n"
	.string "You really came through for me.\p"
	.string "My Psyduck is back in action,\n"
	.string "thanks to you! You’ve got some serious\l"
	.string "skills.$"

OldScumport_Text_ReceivedMoney:
	.string "Lady Elizabeth hands Charlie\n"
	.string "500 dollars!$"
