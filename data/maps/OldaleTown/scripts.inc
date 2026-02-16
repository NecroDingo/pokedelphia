OldaleTown_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, OldaleTown_OnTransition
	.byte 0

OldaleTown_OnTransition:
	call Common_EventScript_SetupRivalGfxId
	setflag FLAG_VISITED_OLDALE_TOWN
	call_if_eq VAR_OLDALE_TOWN_STATE, 0, OldaleTown_EventScript_BlockWestEntrance
	call_if_unset FLAG_RECEIVED_POTION_OLDALE, OldaleTown_EventScript_MoveMartEmployee
	end

OldaleTown_EventScript_BlockWestEntrance::
	setobjectxyperm LOCALID_FOOTPRINTS_MAN, 1, 11
	setobjectmovementtype LOCALID_FOOTPRINTS_MAN, MOVEMENT_TYPE_FACE_LEFT
	return

OldaleTown_EventScript_MoveMartEmployee::
	setobjectxyperm LOCALID_OLDALE_MART_EMPLOYEE, 10, 18
	setobjectmovementtype LOCALID_OLDALE_MART_EMPLOYEE, MOVEMENT_TYPE_FACE_LEFT
	return

OldaleTown_EventScript_TownSign::
	msgbox OldaleTown_Text_TownSign, MSGBOX_SIGN
	end

OldaleTown_EventScript_MartEmployee::
	lock
	faceplayer
	goto_if_set FLAG_RECEIVED_POTION_OLDALE, OldaleTown_EventScript_ExplainPotion
	goto_if_set FLAG_TEMP_1, OldaleTown_EventScript_ExplainPotion
	setflag FLAG_TEMP_1
	playbgm MUS_FOLLOW_ME, FALSE
	msgbox OldaleTown_Text_IWorkAtPokemonMart, MSGBOX_DEFAULT
	closemessage
	end

OldaleTown_EventScript_GoToMart::
	applymovement LOCALID_OLDALE_MART_EMPLOYEE, OldaleTown_Movement_EmployeeMart
	applymovement LOCALID_PLAYER, OldaleTown_Movement_PlayerMart
	waitmovement 0
	goto OldaleTown_EventScript_ExplainPokemonMart
	end

OldaleTown_EventScript_ExplainPokemonMart::
	msgbox OldaleTown_Text_ThisIsAPokemonMart, MSGBOX_DEFAULT
	giveitem ITEM_POTION, 10
	goto_if_eq VAR_RESULT, FALSE, OldaleTown_EventScript_BagIsFull
	msgbox OldaleTown_Text_PotionExplanation, MSGBOX_DEFAULT
	setflag FLAG_RECEIVED_POTION_OLDALE
	setvar VAR_MART_CALL, 1
	fadedefaultbgm
	release
	end

OldaleTown_EventScript_ExplainPotion::
	msgbox OldaleTown_Text_PotionExplanation, MSGBOX_DEFAULT
	release
	end

OldaleTown_EventScript_BagIsFull::
	msgbox gText_TooBadBagIsFull, MSGBOX_DEFAULT
	fadedefaultbgm
	release
	end

OldaleTown_Movement_EmployeeMart:
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

OldaleTown_Movement_Unknown1:
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

OldaleTown_Movement_PlayerMart:
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

OldaleTown_Movement_Unknown2:
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

OldaleTown_EventScript_FootprintsMan::
	lock
	faceplayer
	goto_if_eq VAR_OLDALE_TOWN_STATE, 1, OldaleTown_EventScript_NotBlockingPath
	msgbox OldaleTown_Text_DiscoveredFootprints, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_FOOTPRINTS_MAN, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

OldaleTown_EventScript_BlockedPath::
	lockall
	applymovement LOCALID_PLAYER, OldaleTown_Movement_PlayerStepBack
	applymovement LOCALID_FOOTPRINTS_MAN, OldaleTown_Movement_BackUp
	waitmovement 0
	msgbox OldaleTown_Text_WaitDontComeInHere, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_FOOTPRINTS_MAN, OldaleTown_Movement_ReturnToOriginalPosition
	waitmovement 0
	releaseall
	end

OldaleTown_EventScript_NotBlockingPath::
	msgbox OldaleTown_Text_FinishedSketchingFootprints, MSGBOX_DEFAULT
	release
	end

OldaleTown_EventScript_MartEmployeeCall1::
	lockall
	applymovement LOCALID_PLAYER, Common_Movement_ExclamationMark
	applymovement LOCALID_OLDALE_MART_EMPLOYEE, Common_Movement_ExclamationMark
	msgbox OldaleTown_Text_HeyOverHere, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_PLAYER, OldaleTown_Movement_PlayerStepRight
	waitmovement 0
	msgbox OldaleTown_Text_IWorkAtPokemonMart, MSGBOX_DEFAULT
	closemessage
	goto OldaleTown_EventScript_GoToMart
	releaseall
	end

	OldaleTown_EventScript_MartEmployeeCall2::
	lockall
	applymovement LOCALID_PLAYER, Common_Movement_ExclamationMark
	applymovement LOCALID_OLDALE_MART_EMPLOYEE, Common_Movement_ExclamationMark
	msgbox OldaleTown_Text_HeyOverHere, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_PLAYER, OldaleTown_Movement_PlayerStepRight
	waitmovement 0
	applymovement LOCALID_PLAYER, OldaleTown_Movement_PlayerStepRight
	waitmovement 0
	msgbox OldaleTown_Text_IWorkAtPokemonMart, MSGBOX_DEFAULT
	closemessage
	goto OldaleTown_EventScript_GoToMart
	releaseall
	end

	OldaleTown_EventScript_MartEmployeeCall3::
	lockall
	applymovement LOCALID_PLAYER, Common_Movement_ExclamationMark
	applymovement LOCALID_OLDALE_MART_EMPLOYEE, Common_Movement_ExclamationMark
	msgbox OldaleTown_Text_HeyOverHere, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_PLAYER, OldaleTown_Movement_PlayerStepRight
	waitmovement 0
	applymovement LOCALID_PLAYER, OldaleTown_Movement_PlayerStepRight
	waitmovement 0
	applymovement LOCALID_PLAYER, OldaleTown_Movement_PlayerStepRight
	waitmovement 0
	msgbox OldaleTown_Text_IWorkAtPokemonMart, MSGBOX_DEFAULT
	closemessage
	goto OldaleTown_EventScript_GoToMart
	releaseall
	end

OldaleTown_EventScript_Rival::
	lockall
	applymovement LOCALID_OLDALE_RIVAL, Common_Movement_FacePlayer
	waitmovement 0
	setvar VAR_0x8009, 0
	goto OldaleTown_EventScript_ShowRivalMessage
	end

OldaleTown_EventScript_RivalTrigger1::
	lockall
	applymovement LOCALID_OLDALE_RIVAL, OldaleTown_Movement_RivalApproachPlayer1
	waitmovement 0
	applymovement LOCALID_PLAYER, Common_Movement_WalkInPlaceFasterRight
	waitmovement 0
	setvar VAR_0x8009, 1
	goto OldaleTown_EventScript_ShowRivalMessage
	end

OldaleTown_EventScript_RivalTrigger2::
	lockall
	applymovement LOCALID_OLDALE_RIVAL, OldaleTown_Movement_RivalApproachPlayer2
	waitmovement 0
	applymovement LOCALID_PLAYER, Common_Movement_WalkInPlaceFasterRight
	waitmovement 0
	setvar VAR_0x8009, 1
	goto OldaleTown_EventScript_ShowRivalMessage
	end

OldaleTown_EventScript_RivalTrigger3::
	lockall
	applymovement LOCALID_OLDALE_RIVAL, OldaleTown_Movement_RivalApproachPlayer3
	waitmovement 0
	applymovement LOCALID_PLAYER, Common_Movement_WalkInPlaceFasterRight
	waitmovement 0
	setvar VAR_0x8009, 1
	goto OldaleTown_EventScript_ShowRivalMessage
	end

OldaleTown_EventScript_ShowRivalMessage::
	checkplayergender
	goto_if_eq VAR_RESULT, MALE, OldaleTown_EventScript_ShowMayMessage
	goto_if_eq VAR_RESULT, FEMALE, OldaleTown_EventScript_ShowBrendanMessage
	end

OldaleTown_EventScript_ShowMayMessage::
	msgbox OldaleTown_Text_MayLetsGoBack, MSGBOX_DEFAULT
	goto OldaleTown_EventScript_RivalFinish
	end

OldaleTown_EventScript_ShowBrendanMessage::
	msgbox OldaleTown_Text_BrendanLetsGoBack, MSGBOX_DEFAULT
	goto OldaleTown_EventScript_RivalFinish
	end

OldaleTown_EventScript_RivalFinish::
	closemessage
	call_if_eq VAR_0x8009, 0, OldaleTown_EventScript_DoExitMovement1
	call_if_eq VAR_0x8009, 1, OldaleTown_EventScript_DoExitMovement2
	applymovement LOCALID_OLDALE_RIVAL, OldaleTown_Movement_RivalExit
	waitmovement 0
	removeobject LOCALID_OLDALE_RIVAL
	setvar VAR_OLDALE_RIVAL_STATE, 2
	setflag FLAG_HIDE_OLDALE_TOWN_RIVAL
	releaseall
	end

OldaleTown_EventScript_DoExitMovement1::
	goto_if_ne VAR_FACING, DIR_SOUTH, OldaleTown_EventScript_DoExitMovement2
	applymovement LOCALID_OLDALE_RIVAL, OldaleTown_Movement_RivalExit
	waitmovement 0
	return

OldaleTown_EventScript_DoExitMovement2::
	applymovement LOCALID_PLAYER, OldaleTown_Movement_WatchRivalExit
	applymovement LOCALID_OLDALE_RIVAL, OldaleTown_Movement_RivalExit
	waitmovement 0
	return

OldaleTown_Movement_RivalApproachPlayer1:
	walk_left
	walk_left
	step_end

OldaleTown_Movement_RivalApproachPlayer2:
	walk_left
	step_end

OldaleTown_Movement_RivalApproachPlayer3:
	face_left
	step_end

OldaleTown_Movement_RivalExit:
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	step_end

OldaleTown_Movement_WatchRivalExit:
	delay_8
	delay_4
	walk_in_place_faster_down
	step_end

OldaleTown_Movement_PlayerStepBack:
	lock_facing_direction
	walk_fast_right
	walk_right
	step_end

OldaleTown_Movement_BackUp:
	walk_fast_up
	walk_in_place_fast_right
	delay_8
	walk_right
	step_end

OldaleTown_Movement_ReturnToOriginalPosition:
	walk_down
	walk_left
	step_end

OldaleTown_Movement_PlayerStepRight:
	walk_right
	step_end

OldaleTown_Text_IWorkAtPokemonMart:
	.string "Yo!\n"
	.string "I hustle for the POKéMART.\p"
	.string "Wanna come with? I’ll hook you up.$"

OldaleTown_Text_ThisIsAPokemonMart:
	.string "This? It’s a POKéMART.\n"
	.string "The blue roof means 'Buy shit.'\p"
	.string "We’ve got balls, meds, junk…\n"
	.string "you know, all you need out here.\p"
	.string "Here, I've got free samples.\p"
	.string "Don’t you even ask any questions.\n"
	.string "They fell off the truck...$"

OldaleTown_Text_PotionExplanation:
	.string "POTIONS got that magic juice.\p"
	.string "Drink that shit and you feelin' good\n"
	.string "for a while.$"

OldaleTown_Text_WaitDontComeInHere:
	.string "REX: Yo! Yo! Back it up, bro.\n"
	.string "You can’t roll through here.\p"
	.string "I think I just found some rare-ass\n"
	.string "Pokémon prints or somethin’.\p"
	.string "Lemme get this down real quick.\p"
	.string "Don’t step in it, man. I ain’t jokin’.$"

OldaleTown_Text_DiscoveredFootprints:
	.string "REX: Aight, chill.\n"
	.string "I’m workin’ here.\p"
	.string "Could be ancient, y’know?\n"
	.string "Like legendary-level footprints.\p"
	.string "This is serious business. Back it up.$"

OldaleTown_Text_FinishedSketchingFootprints:
	.string "REX: Aight... done with the sketch.\p"
	.string "Wait...\p"
	.string "Yo, hold up...these are my kicks?\p"
	.string "Haha! Damn, I’m the rare Pokémon.\p"
	.string "Tell the streets: I’m a freakin’ legend.$"

OldaleTown_Text_MayLetsGoBack:
	.string "Margaret stares at you, wide-eyed.\p"
	.string "She jerks her thumb behind her,\n"
	.string "then takes off running.$"

OldaleTown_Text_BrendanLetsGoBack:
	.string "BRENDAN: I'm heading back to my dad's\n"
	.string "LAB now.\l"
	.string "{PLAYER}, you should hustle back, too.$"

OldaleTown_Text_TownSign:
	.string "OLD SCUMPORT\n"
	.string "“Scraped together, barely functional.”$"

OldaleTown_Text_HeyOverHere:
	.string "Hey, you!\n"
	.string "Over here!$"

OldaleTown_EventScript_GailTheSnail::
    lock
    faceplayer
    goto_if_quest_complete QUEST_1_FIND_CHESTO, OldaleTown_EventScript_GailTheSnail_Completed
	goto_if_quest_active QUEST_1_FIND_CHESTO, OldaleTown_EventScript_GailTheSnail_CheckBerry
	goto OldaleTown_EventScript_GailTheSnail_Offer

OldaleTown_EventScript_GailTheSnail_Offer:
	msgbox OldaleTown_Text_GailTheSnailIntroQuest, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, OldaleTown_EventScript_GailTheSnail_Accept
	msgbox OldaleTown_Text_GailTheSnailDecline, MSGBOX_NPC
	release
	end

OldaleTown_EventScript_GailTheSnail_Accept:
	msgbox OldaleTown_Text_GailTheSnailAccept, MSGBOX_NPC
	waitmessage
	startquest QUEST_1_FIND_CHESTO
	msgbox OldaleTown_Text_GailTheSnailAccept2, MSGBOX_NPC
	waitmessage
	release
	end

OldaleTown_EventScript_GailTheSnail_CheckBerry:
    checkitem ITEM_CHESTO_BERRY, 1
    goto_if_eq VAR_RESULT, TRUE, OldaleTown_EventScript_GailTheSnail_TurnIn
    msgbox OldaleTown_Text_GailTheSnailActiveNoBerry, MSGBOX_NPC
    release
    end	

OldaleTown_EventScript_GailTheSnail_TurnIn:
	faceplayer
	msgbox OldaleTown_Text_GailTheSnailTurnIn, MSGBOX_NPC
	removeitem ITEM_CHESTO_BERRY, 1
	completequest QUEST_1_FIND_CHESTO
	msgbox OldaleTown_Text_GailTheSnailTurnIn2, MSGBOX_NPC
	waitmessage
	playfanfare MUS_OBTAIN_ITEM
	msgbox OldaleTown_Text_ReceivedMoney, MSGBOX_DEFAULT
	addmoney 500
	waitmessage
	release
	end

OldaleTown_EventScript_GailTheSnail_Completed:
	msgbox OldaleTown_Text_GailTheSnailCompleted, MSGBOX_NPC
	release
	end

OldaleTown_Text_GailTheSnailIntroQuest:
	.string "GAIL THE SNAIL: Sllrrrp-\p"
	.string "Oh. Hey, Charlie.\p"
	.string "You look… helpful.\p"
	.string "My Lickitung is like, totally out.\n"
	.string "That dumb Drowzee put him to sleep.\p"
	.string "He was doing sooo good too.\p"
	.string "Now he’s just laying there like-\n"
	.string "snrrrk… slrrrp…\p"
	.string "It’s honestly disgusting.\p"
	.string "Can you get me a Chesto Berry?\n"
	.string "I do not wanna deal with this.$"

OldaleTown_Text_GailTheSnailAccept:
	.string "GAIL THE SNAIL: Ugh, thank you.\p"
	.string "You’re being, like, decent.\n"
	.string "It's kinda hot...\p"
	.string "I mean, not that I’m into you\n" 
	.string "or anything...\l"
	.string "Sllrrrp.\p"
	.string "There’s berry bushes around here.\n"
	.string "You just, like… pick them.\p"
	.string "Or that old lady by WAWA PARK\n"
	.string "might have one.\p"
	.string "Just put it in your Berry pocket.\n"
	.string "Don’t squish it. It's messy.\p"
	.string "Sllrrrp.$"

OldaleTown_Text_GailTheSnailAccept2:
	.string "GAIL THE SNAIL: Oh my god, listen\n"
	.string "to him.\p"
	.string "snrrrk… slrrrp…\p"
	.string "It’s like wet breathing.\p"
	.string "I hate it.\p"
	.string "Just hurry.$"

OldaleTown_Text_GailTheSnailDecline:
	.string "GAIL THE SNAIL: Wow.\p"
	.string "Okay.\p"
	.string "So I’m just supposed to sit here\n"
	.string "with this noise?\p"
	.string "That’s actually so rude.\p"
	.string "Sllrrrp.$"

OldaleTown_Text_GailTheSnailActiveNoBerry:
	.string "GAIL THE SNAIL: Um.\p"
	.string "Still asleep.\p"
	.string "Still gross.\p"
	.string "snrrrk… slrrrp…\p"
	.string "Did you even try?\p"
	.string "Are you just into me or something?\n"
	.string "Or did you forget?\p"
	.string "You forget things a lot, Charlie.$"

OldaleTown_Text_GailTheSnailTurnIn:
	.string "GAIL THE SNAIL: Wait.\p"
	.string "Is that it?\p"
	.string "Oh my god, finally.\p"
	.string "Okay, wake up.\p"
	.string "Don’t make it weird.\p"
	.string "…Sllrrrp.$"

OldaleTown_Text_GailTheSnailTurnIn2:
	.string "GAIL THE SNAIL: Here.\p"
	.string "I have some cash.\p"
	.string "It was in my pocket.\p"
	.string "…Sllrrrp.\p"
	.string "Just take it.\p"
	.string "Don’t make it a thing.$"

OldaleTown_Text_GailTheSnailCompleted:
	.string "GAIL THE SNAIL: Oh hey.\p"
	.string "Lickitung’s fine now.\p"
	.string "He keeps licking stuff.\p"
	.string "Which is, like… whatever.\p"
	.string "Anyway.\p"
	.string "Thanks again.\p"
	.string "Sllrrrp.$"

OldaleTown_Text_ReceivedMoney:
	.string "GAIL THE SNAIL hands Charlie\n"
	.string "500 dollars.\p"
	.string "They feel slightly damp.$"
