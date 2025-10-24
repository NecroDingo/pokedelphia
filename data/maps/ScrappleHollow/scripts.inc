ScrappleHollow_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, ScrappleHollow_StartNurse_OnTransition
	.byte 0

ScrappleHollow_StartNurse_OnTransition::
	setrespawn HEAL_LOCATION_SCRAPPLE_HOLLOW
	end

ScrappleHollow_EventScript_NurseWaitressHeal::
	lock
	faceplayer
	setvar VAR_0x8004, 0
    msgbox ScrappleHollow_Text_NurseHeal, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, ScrappleHollow_EventScript_HealPkmn
	goto_if_eq VAR_RESULT, NO, ScrappleHollow_EventScript_Goodbye
	end

ScrappleHollow_EventScript_HealPkmn::
	closemessage
	incrementgamestat GAME_STAT_USED_POKECENTER
	call Common_EventScript_OutOfCenterPartyHeal
	delay 20
    msgbox ScrappleHollow_Text_PayingMe, MSGBOX_NPC
    waitmessage
    release
    end

ScrappleHollow_EventScript_Goodbye::
	msgbox ScrappleHollow_Text_WhyAreYouTalking, MSGBOX_NPC
	waitmessage
    release
    end

ScrappleHollow_Text_NurseHeal:
	.string "WAITRESS: Oh great... Hi Charlie.\n"
	.string "Do you need your POKéMON healed?$"

ScrappleHollow_Text_PayingMe:
	.string "WAITRESS: I’m only here ‘cause they pay\n"
	.string "me to be.\p"
	.string "Don’t get any ideas Charlie.$"

ScrappleHollow_Text_WhyAreYouTalking:
	.string "WAITRESS: Wow, seriously? Why are you\n"
	.string "even talking to me...$"



ScrappleHollow_EventScript_DevonResearcherLeft::
	lockall
	call ScrappleHollow_EventScript_DevonResearcherIntro
	applymovement LOCALID_SCRAPPLE_HOLLOW_DEVON_EMPLOYEE, ScrappleHollow_Movement_DevonResearcherApproachPlayerLeft
	waitmovement 0
	msgbox ScrappleHollow_Text_HaveYouSeenShroomish, MSGBOX_DEFAULT
	closemessage
	playbgm MUS_ENCOUNTER_AQUA, FALSE
	applymovement LOCALID_SCRAPPLE_HOLLOW_GRUNT, ScrappleHollow_Movement_AquaEntrance
	waitmovement 0
	msgbox ScrappleHollow_Text_IWasGoingToAmbushYou, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_SCRAPPLE_HOLLOW_GRUNT, ScrappleHollow_Movement_AquaApproachResearcherLeft
	waitmovement 0
	applymovement LOCALID_SCRAPPLE_HOLLOW_DEVON_EMPLOYEE, Common_Movement_WalkInPlaceFasterRight
	waitmovement 0
	msgbox ScrappleHollow_Text_HandOverThosePapers, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_SCRAPPLE_HOLLOW_DEVON_EMPLOYEE, ScrappleHollow_Movement_DevonResearcherFleeToPlayerLeft
	waitmovement 0
	msgbox ScrappleHollow_Text_YouHaveToHelpMe, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_SCRAPPLE_HOLLOW_GRUNT, ScrappleHollow_Movement_AquaApproachPlayer
	waitmovement 0
	msgbox ScrappleHollow_Text_NoOneCrossesTeamAqua, MSGBOX_DEFAULT
	trainerbattle_no_intro TRAINER_GRUNT_SCRAPPLE_HOLLOW, ScrappleHollow_Text_YoureKiddingMe
	applymovement LOCALID_SCRAPPLE_HOLLOW_GRUNT, ScrappleHollow_Movement_AquaBackOff
	waitmovement 0
	call ScrappleHollow_EventScript_DevonResearcherPostBattle
	applymovement LOCALID_PLAYER, ScrappleHollow_Movement_WatchResearcherLeave
	applymovement LOCALID_SCRAPPLE_HOLLOW_DEVON_EMPLOYEE, ScrappleHollow_Movement_DevonResearcherExitLeft
	waitmovement 0
	goto ScrappleHollow_EventScript_RemoveDevonResearcher
	end

ScrappleHollow_EventScript_DevonResearcherRight::
	lockall
	call ScrappleHollow_EventScript_DevonResearcherIntro
	applymovement LOCALID_SCRAPPLE_HOLLOW_DEVON_EMPLOYEE, ScrappleHollow_Movement_DevonResearcherApproachPlayerRight
	waitmovement 0
	applymovement LOCALID_PLAYER, Common_Movement_WalkInPlaceFasterRight
	waitmovement 0
	msgbox ScrappleHollow_Text_HaveYouSeenShroomish, MSGBOX_DEFAULT
	closemessage
	playbgm MUS_ENCOUNTER_AQUA, FALSE
	applymovement LOCALID_SCRAPPLE_HOLLOW_GRUNT, ScrappleHollow_Movement_AquaEntrance
	waitmovement 0
	msgbox ScrappleHollow_Text_IWasGoingToAmbushYou, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_SCRAPPLE_HOLLOW_GRUNT, ScrappleHollow_Movement_AquaApproachResearcherRight
	waitmovement 0
	applymovement LOCALID_SCRAPPLE_HOLLOW_DEVON_EMPLOYEE, Common_Movement_WalkInPlaceFasterRight
	waitmovement 0
	msgbox ScrappleHollow_Text_HandOverThosePapers, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_SCRAPPLE_HOLLOW_DEVON_EMPLOYEE, ScrappleHollow_Movement_DevonResearcherFleeToPlayerRight
	waitmovement 0
	msgbox ScrappleHollow_Text_YouHaveToHelpMe, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_SCRAPPLE_HOLLOW_GRUNT, ScrappleHollow_Movement_AquaApproachPlayer
	waitmovement 0
	msgbox ScrappleHollow_Text_NoOneCrossesTeamAqua, MSGBOX_DEFAULT
	trainerbattle_no_intro TRAINER_GRUNT_SCRAPPLE_HOLLOW, ScrappleHollow_Text_YoureKiddingMe
	applymovement LOCALID_SCRAPPLE_HOLLOW_GRUNT, ScrappleHollow_Movement_AquaBackOff
	waitmovement 0
	call ScrappleHollow_EventScript_DevonResearcherPostBattle
	applymovement LOCALID_PLAYER, ScrappleHollow_Movement_WatchResearcherLeave
	applymovement LOCALID_SCRAPPLE_HOLLOW_DEVON_EMPLOYEE, ScrappleHollow_Movement_DevonResearcherExitRight
	waitmovement 0
	goto ScrappleHollow_EventScript_RemoveDevonResearcher
	end

ScrappleHollow_EventScript_DevonResearcherIntro::
	applymovement LOCALID_SCRAPPLE_HOLLOW_DEVON_EMPLOYEE, ScrappleHollow_Movement_DevonResearcherLookAround
	waitmovement 0
	msgbox ScrappleHollow_Text_NotAOneToBeFound, MSGBOX_DEFAULT
	closemessage
	return

ScrappleHollow_EventScript_DevonResearcherPostBattle::
	msgbox ScrappleHollow_Text_YouveGotSomeNerve, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_SCRAPPLE_HOLLOW_GRUNT, ScrappleHollow_Movement_AquaRunAway
	waitmovement 0
	removeobject LOCALID_SCRAPPLE_HOLLOW_GRUNT
	applymovement LOCALID_PLAYER, Common_Movement_WalkInPlaceFasterLeft
	waitmovement 0
	msgbox ScrappleHollow_Text_ThatWasAwfullyClose, MSGBOX_DEFAULT
	giveitem ITEM_GREAT_BALL
	goto_if_eq VAR_RESULT, FALSE, ScrappleHollow_EventScript_BagFull
	goto ScrappleHollow_EventScript_DevonResearcherFinish
	end

ScrappleHollow_EventScript_BagFull::
	msgbox ScrappleHollow_Text_YoureLoadedWithItems, MSGBOX_DEFAULT
	goto ScrappleHollow_EventScript_DevonResearcherFinish
	end

ScrappleHollow_EventScript_DevonResearcherFinish::
	msgbox ScrappleHollow_Text_TeamAquaAfterSomethingInRustboro, MSGBOX_DEFAULT
	applymovement LOCALID_SCRAPPLE_HOLLOW_DEVON_EMPLOYEE, ScrappleHollow_Movement_DevonResearcherStartExit
	waitmovement 0
	msgbox ScrappleHollow_Text_ICantBeWastingTime, MSGBOX_DEFAULT
	closemessage
	return

ScrappleHollow_EventScript_RemoveDevonResearcher::
	removeobject LOCALID_SCRAPPLE_HOLLOW_DEVON_EMPLOYEE
	setvar VAR_SCRAPPLE_HOLLOW_STATE, 1
	releaseall
	end

ScrappleHollow_Movement_DevonResearcherLookAround:
	walk_left
	walk_left
	walk_left
	delay_16
	face_up
	delay_16
	delay_4
	face_right
	delay_16
	delay_8
	walk_left
	walk_left
	walk_down
	delay_16
	delay_8
	face_up
	delay_16
	face_right
	delay_16
	delay_8
	walk_left
	walk_left
	face_up
	delay_16
	delay_8
	face_down
	delay_16
	delay_8
	walk_right
	walk_right
	delay_16
	delay_8
	face_down
	delay_16
	step_end

ScrappleHollow_Movement_DevonResearcherExitLeft:
	walk_fast_down
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	step_end

ScrappleHollow_Movement_DevonResearcherApproachPlayerLeft:
	delay_16
	face_player
	walk_down
	walk_down
	walk_left
	walk_left
	step_end

ScrappleHollow_Movement_DevonResearcherApproachPlayerRight:
	delay_16
	face_player
	walk_down
	walk_down
	walk_down
	walk_left
	walk_left
	step_end

ScrappleHollow_Movement_DevonResearcherExitRight:
	walk_fast_up
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	step_end

ScrappleHollow_Movement_WatchResearcherLeave:
	delay_16
	delay_16
	walk_in_place_fast_right
	step_end

ScrappleHollow_Movement_DevonResearcherFleeToPlayerLeft:
	walk_fast_down
	walk_fast_left
	walk_fast_left
	walk_fast_up
	walk_in_place_faster_right
	step_end

ScrappleHollow_Movement_DevonResearcherFleeToPlayerRight:
	walk_fast_up
	walk_fast_left
	walk_fast_left
	walk_fast_down
	walk_in_place_faster_right
	step_end

ScrappleHollow_Movement_DevonResearcherStartExit:
	walk_in_place_faster_down
	delay_16
	delay_16
	delay_16
	delay_16
	delay_16
	face_down
	step_end

ScrappleHollow_Movement_AquaApproachResearcherLeft:
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_left
	step_end

ScrappleHollow_Movement_AquaBackOff:
	lock_facing_direction
	walk_right
	unlock_facing_direction
	step_end

ScrappleHollow_Movement_AquaRunAway:
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	delay_16
	delay_16
	step_end

ScrappleHollow_Movement_AquaApproachResearcherRight:
	walk_fast_down
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_left
	step_end

ScrappleHollow_Movement_AquaEntrance:
	walk_left
	walk_left
	delay_16
	delay_16
	step_end

ScrappleHollow_Movement_AquaApproachPlayer:
	walk_left
	step_end

ScrappleHollow_EventScript_Boy1::
	msgbox ScrappleHollow_Text_StayOutOfTallGrass, MSGBOX_NPC
	end

ScrappleHollow_EventScript_Boy2::
	msgbox ScrappleHollow_Text_HiddenItemsExplanation, MSGBOX_NPC
	end

ScrappleHollow_EventScript_Girl::
	lock
	faceplayer
	goto_if_set FLAG_RECEIVED_MIRACLE_SEED, ScrappleHollow_EventScript_ExplainMiracleSeed
	msgbox ScrappleHollow_Text_TryUsingThisItem, MSGBOX_DEFAULT
	giveitem ITEM_MIRACLE_SEED
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_ShowBagIsFull
	setflag FLAG_RECEIVED_MIRACLE_SEED
	release
	end

ScrappleHollow_EventScript_ExplainMiracleSeed::
	msgbox ScrappleHollow_Text_MiracleSeedExplanation, MSGBOX_DEFAULT
	release
	end

ScrappleHollow_EventScript_Sign1::
	msgbox ScrappleHollow_Text_Conditions, MSGBOX_SIGN
	end

ScrappleHollow_EventScript_Sign2::
	msgbox ScrappleHollow_Text_Advantages, MSGBOX_SIGN
	end

ScrappleHollow_EventScript_Sign3::
	msgbox ScrappleHollow_Text_GotPunked, MSGBOX_SIGN
	end	

ScrappleHollow_EventScript_Lyle::
	trainerbattle_single TRAINER_LYLE, ScrappleHollow_Text_GoBugPokemonTeam, ScrappleHollow_Text_ICouldntWin
	msgbox ScrappleHollow_Text_ImOutOfPokeBalls, MSGBOX_AUTOCLOSE
	end

ScrappleHollow_EventScript_Liam::
	trainerbattle_single TRAINER_LIAM, ScrappleHollow_Text_ScrapplePro, ScrappleHollow_Text_KeepGrindin
	msgbox ScrappleHollow_Text_ImOutOfPokeBalls, MSGBOX_AUTOCLOSE
	end

ScrappleHollow_EventScript_Maya::
	trainerbattle_single TRAINER_MAYA, ScrappleHollow_Text_YourLost, ScrappleHollow_Text_WayOut
	msgbox ScrappleHollow_Text_ImOutOfPokeBalls, MSGBOX_AUTOCLOSE
	end	

ScrappleHollow_EventScript_James::
	trainerbattle_single TRAINER_JAMES_1, ScrappleHollow_Text_InstantlyPopularWithBugPokemon, ScrappleHollow_Text_CantBePopularIfILose, ScrappleHollow_EventScript_TryRegisterJames
	specialvar VAR_RESULT, ShouldTryRematchBattle
	goto_if_eq VAR_RESULT, TRUE, ScrappleHollow_EventScript_JamesRematch
	setvar VAR_0x8004, TRAINER_JAMES_1
	specialvar VAR_RESULT, IsTrainerRegistered
	goto_if_eq VAR_RESULT, FALSE, ScrappleHollow_EventScript_TryRegisterJames2
	msgbox ScrappleHollow_Text_PeopleRespectYou, MSGBOX_DEFAULT
	release
	end

ScrappleHollow_EventScript_TryRegisterJames::
	special PlayerFaceTrainerAfterBattle
	waitmovement 0
	goto_if_set FLAG_HAS_MATCH_CALL, ScrappleHollow_EventScript_RegisterJames
	release
	end

ScrappleHollow_EventScript_RegisterJames::
	msgbox ScrappleHollow_Text_IWantRematch1, MSGBOX_DEFAULT
	register_matchcall TRAINER_JAMES_1
	release
	end

ScrappleHollow_EventScript_TryRegisterJames2::
	goto_if_set FLAG_HAS_MATCH_CALL, ScrappleHollow_EventScript_RegisterJames2
	msgbox ScrappleHollow_Text_PeopleRespectYou, MSGBOX_DEFAULT
	release
	end

ScrappleHollow_EventScript_RegisterJames2::
	msgbox ScrappleHollow_Text_IWantRematch2, MSGBOX_DEFAULT
	register_matchcall TRAINER_JAMES_1
	release
	end

ScrappleHollow_EventScript_JamesRematch::
	trainerbattle_rematch TRAINER_JAMES_1, ScrappleHollow_Text_MyPokemonHaveGrown, ScrappleHollow_Text_CantBePopularIfLose
	msgbox ScrappleHollow_Text_IveBeenTrainingHard, MSGBOX_AUTOCLOSE
	end

ScrappleHollow_Text_NotAOneToBeFound:
	.string "Hmmm…\n"
	.string "Not a one to be found…$"

ScrappleHollow_Text_HaveYouSeenShroomish:
	.string "Yo, you seen a SHROOMISH lurkin'\n"
	.string "around here?\p"
	.string "I got a soft spot for the lil' dude.$"

ScrappleHollow_Text_IWasGoingToAmbushYou:
	.string "I was gonna jump ya, but you been\n"
	.string "strollin' through SCRAPPLE HOLLOW\l"
	.string "like it's a damn park.\p"
	.string "I got bored waitin', so let's go!$"

ScrappleHollow_Text_HandOverThosePapers:
	.string "Hey! WAWA SUIT!\p"
	.string "Fork over them papers before I make\n"
	.string "a scene, pal!$"

ScrappleHollow_Text_YouHaveToHelpMe:
	.string "Ayo! Help me out!\p"
	.string "You look like you got a squad of\n"
	.string "POKéMON. Lend a hand, please!$"

ScrappleHollow_Text_NoOneCrossesTeamAqua:
	.string "Yo, what's your problem, kid?\n"
	.string "You runnin' security for this guy?\p"
	.string "Nobody crosses THE JERSEY MIKE BOYS\n"
	.string "and walks away smilin'.\p"
	.string "Square up, punk!$"

ScrappleHollow_Text_YoureKiddingMe:
	.string "What?! You ain't playin' around!$"

ScrappleHollow_Text_YouveGotSomeNerve:
	.string "Tch... You got guts, messin' with\n"
	.string "THE JERSEY MIKE BOYS.\p"
	.string "I'd run it back, but I’m fresh outta\n"
	.string "POKéMON...\p"
	.string "Whatever. We’re hittin’ RUSTBORO next.\p"
	.string "Count ya blessings, kid.$"

ScrappleHollow_Text_ThatWasAwfullyClose:
	.string "Sheesh...\n"
	.string "That was way too close!\p"
	.string "Thanks, or that meathead would've\n"
	.string "jacked my important papers.\p"
	.string "Here, take this GREAT BALL. Least\n"
	.string "I can do.$"

ScrappleHollow_Text_TeamAquaAfterSomethingInRustboro:
	.string "Didn't that JERSEY MIKE goon say\n"
	.string "they’re plannin’ somethin' in\l"
	.string "Wawa Park?$"

ScrappleHollow_Text_ICantBeWastingTime:
	.string "Crap! This is bad!\n"
	.string "No time to waste!$"

ScrappleHollow_Text_YoureLoadedWithItems:
	.string "You're loaded with items.\n"
	.string "I can't give you this GREAT BALL.$"

ScrappleHollow_Text_GoBugPokemonTeam:
	.string "I caught a whole bunch of POKéMON!\p"
	.string "Go, go, go!\n"
	.string "My BUG POKéMON team!$"

ScrappleHollow_Text_ICouldntWin:
	.string "I have all these POKéMON,\n"
	.string "but I couldn't win…$"

ScrappleHollow_Text_ImOutOfPokeBalls:
	.string "I caught a bunch of POKéMON.\n"
	.string "Now I'm out of POKé BALLS.$"

ScrappleHollow_Text_InstantlyPopularWithBugPokemon:
	.string "If you take BUG POKéMON to school,\n"
	.string "you get to be instantly popular!$"

ScrappleHollow_Text_CantBePopularIfILose:
	.string "I can't be popular if I lose.$"

ScrappleHollow_Text_PeopleRespectYou:
	.string "If you have a big BUG POKéMON,\n"
	.string "people respect you for it.$"

ScrappleHollow_Text_IWantRematch1:
	.string "I want a rematch when my BUG\n"
	.string "POKéMON grow up!\p"
	.string "I'm registering you in my POKéNAV!$"

ScrappleHollow_Text_IWantRematch2:
	.string "I want a rematch when my BUG \n"
	.string "POKéMON grow up!\p"
	.string "I'm registering you in my POKéNAV!$"

ScrappleHollow_Text_MyPokemonHaveGrown:
	.string "My BUG POKéMON have grown.\n"
	.string "I'll be popular again.$"

ScrappleHollow_Text_CantBePopularIfLose:
	.string "I can't be popular if I lose.$"

ScrappleHollow_Text_IveBeenTrainingHard:
	.string "You get to be popular if you have\n"
	.string "strong POKéMON, right?\l"
	.string "So, I've been training hard.$"

ScrappleHollow_Text_ScrapplePro:
	.string "Yo, what’s good?\p"
	.string "I’m Liam, straight outta Scrapple\n"
	.string "Hollow, huntin’ bugs like a pro.\p"
	.string "You think you got what it takes to\n"
	.string "roll with my crew? Let’s see it!$"

ScrappleHollow_Text_YourLost:
	.string "Yo, hold up! You think you’re headin’\n"
	.string "the right way? Nah, you’re lost.\p"
	.string "This forest’s a maze, and you’re way\n"
	.string "off track.\p"
	.string "If you want some help, step up and show\n"
	.string "me what you got.$"

ScrappleHollow_Text_KeepGrindin:
	.string "Aight, you got me good!\n"
	.string "Didn’t think you had that kinda skill.\p"
	.string "I’ma keep grindin’. Next time, I'm\n"
	.string "comin’ back stronger, no doubt.$"

ScrappleHollow_Text_WayOut:
	.string "Yo, respect! You got me good.\p"
	.string "Listen, up ahead there’s a little cliff\n"
	.string "you gotta jump down.\p"
	.string "That’s the move if you wanna find your\n"
	.string "way outta this maze.\p"
	.string "Don’t get lost now!$"

ScrappleHollow_Text_StayOutOfTallGrass:
	.string "Yo, hold up, I ain’t goin’ in there.\n"
	.string "You know what I just found out?\p"
	.string "These Repels. It don’t matter if it’s\n"
	.string "the fancy Max ones or whatever,\l"
	.string "they only keep out the lil’ jabroni\l"
	.string "Pokémon that are weaker than your\l"
	.string "first guy.\p"
	.string "So if some big beefy dude in the grass is\n"
	.string "the same level or higher than your lead?\p"
	.string "Boom! He’s still jumpin’ out at ya.\p"
	.string "Like, why am I payin’ top dollar for\n"
	.string "that?\p"
	.string "Nah, I’m stayin’ right here where it's\n"
	.string "safe. Got enough problems already...$"

ScrappleHollow_Text_HiddenItemsExplanation:
	.string "Yo, listen.\n"
	.string "Sometimes there’s stuff just layin’\l"
	.string "around, even if you don’t see it.\p"
	.string "Could be cash, could be snacks, could\n"
	.string "be… a weird rock.\p"
	.string "That’s why I’m always checkin’ every\n"
	.string "bush. You never know what’s hidin'\l"
	.string "in there.\p"
	.string "Might look crazy to other people,\n"
	.string "but who’s laughin’ when I find\l"
	.string "somethin’ sweet?$"

ScrappleHollow_Text_TryUsingThisItem:
	.string "Hey, you look like you could use a\n"
	.string "little boost.\p"
	.string "Here, take this Miracle Seed.$"

ScrappleHollow_Text_MiracleSeedExplanation:
	.string "It's a MIRACLE SEED.\n"
	.string "If a POKéMON holds that item, its\l"
	.string "GRASS-type moves become stronger.\p"
	.string "Besides MIRACLE SEED, I think there are\n"
	.string "other convenient items for POKéMON\l"
	.string "to hold.$"

ScrappleHollow_Text_Conditions:
	.string "TRAINER TIPS\p"
	.string "Moves that cause status conditions,\n"
	.string "such as paralysis or sleep, can give\l"
	.string "you a major advantage in battle.\p"
	.string "Even if they deal no direct damage,\n"
	.string "status moves can weaken or disrupt an\l"
	.string "opponent, making victory easier.$"

ScrappleHollow_Text_Advantages:
	.string "TRAINER TIPS\p"
	.string "Knowing type advantages is key to\n"
	.string "success.\p"
	.string "A move that is “super effective” will\n"
	.string "deal double damage, while one that is\l"
	.string "“not very effective” will deal only\l"
	.string "half.\p"
	.string "Choose your attacks wisely to turn\n"
	.string "the tide of battle.$"

ScrappleHollow_Text_GotPunked:
	.string "The message is carved into the sign\n"
	.string "from a sharp object.\p"
	.string "“Ha, You got Punk'd” is carved out\n"
	.string "over the old message.$"
