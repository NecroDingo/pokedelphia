GiantsReach_MatthewsHouse_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, GiantsReach_MatthewsHouse_OnTransition
	map_script MAP_SCRIPT_ON_FRAME_TABLE, GiantsReach_MatthewsHouse_OnFrame
	map_script MAP_SCRIPT_ON_WARP_INTO_MAP_TABLE, GiantsReach_MatthewsHouse_OnWarp
	.byte 0

GiantsReach_MatthewsHouse_OnTransition:
	questmenu QUEST_MENU_CHECK_COMPLETE, QUEST_3_ROOT_FOSSIL
	compare VAR_RESULT, TRUE
	goto_if_eq GiantsReach_MatthewsHouse_OnTransition_End
	questmenu QUEST_MENU_CHECK_ACTIVE, QUEST_3_ROOT_FOSSIL
	compare VAR_RESULT, TRUE
	call_if_eq GiantsReach_MatthewsHouse_EventScript_SetupQuest3Scene
	questmenu QUEST_MENU_CHECK_REWARD, QUEST_3_ROOT_FOSSIL
	compare VAR_RESULT, TRUE
	call_if_eq GiantsReach_MatthewsHouse_EventScript_SetupQuest3Scene
	end

GiantsReach_MatthewsHouse_OnTransition_End:
	end

GiantsReach_MatthewsHouse_EventScript_SetupQuest3Scene::
	setobjectxyperm LOCALID_MATTHEWS_HOUSE_MATTHEWS_DAD, 4, 4
	setobjectxyperm LOCALID_MATTHEWS_HOUSE_MATTHEWS_MOM, 7, 5
	goto_if_set FLAG_HIDE_FRANK_QUEST3_COMPLETE, GiantsReach_MatthewsHouse_EventScript_SetupQuest3Scene_End
	clearflag FLAG_HIDE_FRANK_GIANTS_REACH
	addobject LOCALID_MATTHEWS_HOUSE_FRANK
	setobjectxyperm LOCALID_MATTHEWS_HOUSE_FRANK, 4, 5

GiantsReach_MatthewsHouse_EventScript_SetupQuest3Scene_End::
	return

GiantsReach_MatthewsHouse_OnWarp:
	map_script_2 VAR_GIANTS_REACH_CITY_STATE, 4, GiantsReach_MatthewsHouse_EventScript_PlayerMatthewsDadFaceEachOther
	.2byte 0

GiantsReach_MatthewsHouse_EventScript_PlayerMatthewsDadFaceEachOther::
	turnobject LOCALID_PLAYER, DIR_EAST
	turnobject LOCALID_MATTHEWS_HOUSE_MATTHEWS_DAD, DIR_WEST
	end

GiantsReach_MatthewsHouse_OnFrame:
	map_script_2 VAR_GIANTS_REACH_CITY_STATE, 4, GiantsReach_MatthewsHouse_EventScript_GiveHMSurf
	.2byte 0

GiantsReach_MatthewsHouse_EventScript_GiveHMSurf::
	lockall
	msgbox GiantsReach_MatthewsHouse_Text_PleaseExcuseUs, MSGBOX_DEFAULT
	giveitem ITEM_HM_SURF
	setflag FLAG_RECEIVED_HM_SURF
	msgbox GiantsReach_MatthewsHouse_Text_SurfGoAllSortsOfPlaces, MSGBOX_DEFAULT
	setvar VAR_GIANTS_REACH_CITY_STATE, 5
	releaseall
	end

GiantsReach_MatthewsHouse_EventScript_MatthewsDad::
	lock
	faceplayer
	goto_if_set FLAG_HIDE_FRANK_QUEST3_COMPLETE, GiantsReach_MatthewsHouse_EventScript_MatthewsDadAfterFrank
	questmenu QUEST_MENU_CHECK_ACTIVE, QUEST_3_ROOT_FOSSIL
	compare VAR_RESULT, TRUE
	goto_if_eq GiantsReach_MatthewsHouse_EventScript_MatthewsDadQuest3
	questmenu QUEST_MENU_CHECK_REWARD, QUEST_3_ROOT_FOSSIL
	compare VAR_RESULT, TRUE
	goto_if_eq GiantsReach_MatthewsHouse_EventScript_MatthewsDadQuest3
	goto_if_set FLAG_DEFEATED_MATTHEW_VICTORY_ROAD, GiantsReach_MatthewsHouse_EventScript_DefeatedMatthewInVictoryRoad
	goto_if_set FLAG_RECEIVED_HM_SURF, GiantsReach_MatthewsHouse_EventScript_ReceievedHMSurf
	goto_if_set FLAG_THANKED_FOR_PLAYING_WITH_MATTHEW, GiantsReach_MatthewsHouse_EventScript_PlayedWithMatthew
	msgbox GiantsReach_MatthewsHouse_Text_ThanksForPlayingWithMatthew, MSGBOX_DEFAULT
	setflag FLAG_THANKED_FOR_PLAYING_WITH_MATTHEW
	release
	end

GiantsReach_MatthewsHouse_EventScript_MatthewsDadQuest3::
	msgbox GiantsReach_MatthewsHouse_Text_MatthewsDadQuest3, MSGBOX_DEFAULT
	release
	end

GiantsReach_MatthewsHouse_EventScript_ReceievedHMSurf::
	msgbox GiantsReach_MatthewsHouse_Text_MatthewIsComingHomeSoon, MSGBOX_DEFAULT
	release
	end

GiantsReach_MatthewsHouse_EventScript_DefeatedMatthewInVictoryRoad::
	msgbox GiantsReach_MatthewsHouse_Text_YouMetMatthewInEverGrandeCity, MSGBOX_DEFAULT
	release
	end

GiantsReach_MatthewsHouse_EventScript_PlayedWithMatthew::
	msgbox GiantsReach_MatthewsHouse_Text_WonderHowMatthewIsDoing, MSGBOX_DEFAULT
	release
	end

GiantsReach_MatthewsHouse_EventScript_MatthewsDadAfterFrank::
	msgbox GiantsReach_MatthewsHouse_Text_MatthewsDadAfterFrank, MSGBOX_DEFAULT
	release
	end

GiantsReach_MatthewsHouse_EventScript_MatthewsMomAfterFrank::
	msgbox GiantsReach_MatthewsHouse_Text_MatthewsMomAfterFrank, MSGBOX_DEFAULT
	release
	end

GiantsReach_MatthewsHouse_EventScript_MatthewsMom::
	lock
	faceplayer
	goto_if_set FLAG_HIDE_FRANK_QUEST3_COMPLETE, GiantsReach_MatthewsHouse_EventScript_MatthewsMomAfterFrank
	questmenu QUEST_MENU_CHECK_ACTIVE, QUEST_3_ROOT_FOSSIL
	compare VAR_RESULT, TRUE
	goto_if_eq GiantsReach_MatthewsHouse_EventScript_MatthewsMomQuest3
	questmenu QUEST_MENU_CHECK_REWARD, QUEST_3_ROOT_FOSSIL
	compare VAR_RESULT, TRUE
	goto_if_eq GiantsReach_MatthewsHouse_EventScript_MatthewsMomQuest3
	goto_if_set FLAG_RECEIVED_HM_SURF, GiantsReach_MatthewsHouse_EventScript_ReceivedHMSurf
	msgbox GiantsReach_MatthewsHouse_Text_MatthewWasReallyHappy, MSGBOX_DEFAULT
	release
	end

GiantsReach_MatthewsHouse_EventScript_MatthewsMomQuest3::
	msgbox GiantsReach_MatthewsHouse_Text_MatthewsMomQuest3, MSGBOX_DEFAULT
	release
	end

GiantsReach_MatthewsHouse_EventScript_ReceivedHMSurf::
	msgbox GiantsReach_MatthewsHouse_Text_MatthewLeftWithoutTelling, MSGBOX_DEFAULT
	release
	end

GiantsReach_MatthewsHouse_EventScript_Frank::
	lock
	faceplayer
	questmenu QUEST_MENU_CHECK_REWARD, QUEST_3_ROOT_FOSSIL
	compare VAR_RESULT, TRUE
	goto_if_eq GiantsReach_MatthewsHouse_EventScript_FrankTurnInQuest
	msgbox GiantsReach_MatthewsHouse_Text_FrankWaiting, MSGBOX_DEFAULT
	release
	end

GiantsReach_MatthewsHouse_EventScript_FrankTurnInQuest::
	msgbox GiantsReach_MatthewsHouse_Text_FrankTurnIn, MSGBOX_DEFAULT
	questmenu QUEST_MENU_COMPLETE_QUEST, QUEST_3_ROOT_FOSSIL
	msgbox GiantsReach_MatthewsHouse_Text_FrankLeaving, MSGBOX_DEFAULT
	closemessage
	call_if_eq VAR_FACING, DIR_NORTH, GiantsReach_MatthewsHouse_EventScript_MovePlayerForFrankExit
	applymovement LOCALID_MATTHEWS_HOUSE_FRANK, GiantsReach_MatthewsHouse_Movement_FrankLeave
	waitmovement 0
	setflag FLAG_HIDE_FRANK_QUEST3_COMPLETE
	setflag FLAG_HIDE_FRANK_GIANTS_REACH
	removeobject LOCALID_MATTHEWS_HOUSE_FRANK
	release
	end

GiantsReach_MatthewsHouse_EventScript_MovePlayerForFrankExit::
	applymovement LOCALID_PLAYER, GiantsReach_MatthewsHouse_Movement_PlayerMoveLeftForFrank
	waitmovement 0
	return

GiantsReach_MatthewsHouse_Text_ThanksForPlayingWithMatthew:
	.string "You’re…\n"
	.string "Ah, you must be {PLAYER}, right?\p"
	.string "Thank you for spendin’ some time with\n"
	.string "Matthew a little while ago.\p"
	.string "I am a Priest friend of his. We travel\n"
	.string "together. He is still learning.\p"
	.string "Were sending him to stay with kinfolk in\n"
	.string "Verdanturf Town for a while.\p"
	.string "The air there’s cleaner, better for his\n"
	.string "health and studies, you know?\p"
	.string "What’s that? Where’s Matthew now?\n"
	.string "He’s already moved on, our Matthew.\p"
	.string "I wonder where the good Lord’s led him\n"
	.string "to now.$"

GiantsReach_MatthewsHouse_Text_WonderHowMatthewIsDoing:
	.string "I wonder how our Matthew’s holdin’ up\n"
	.string "these days.$"

GiantsReach_MatthewsHouse_Text_PleaseExcuseUs:
	.string "{PLAYER}! Forgive us for draggin’ you\n"
	.string "out here like this.\p"
	.string "Matthew’s gotten a lot stronger in\n"
	.string "faith since he went to Verdanturf Town.\p"
	.string "We owe a lot of that to you!\p"
	.string "When Matthew left, you helped him catch a Pokémon, right?\n"
	.string "That truly lifted his spirits.\p"
	.string "Not just his, but mine as well,\n"
	.string "as his friend and a humble servant\l"
	.string "of the Lord.\p"
	.string "It warms my heart to see him find\n"
	.string "such a good friend in you.\p"
	.string "This ain’t no bribe or nothin’, but I'd\n"
	.string "be honored if you accepted this gift.$"

GiantsReach_MatthewsHouse_Text_SurfGoAllSortsOfPlaces:
	.string "If your Pokémon can Surf, you’ll be\n"
	.string "able to travel to all kinds of places,\l"
	.string "God willing.$"

GiantsReach_MatthewsHouse_Text_MatthewIsComingHomeSoon:
	.string "Matthew’s comin’ home soon.\p"
	.string "I’m lookin’ forward to that day with all\n"
	.string "my heart.$"

GiantsReach_MatthewsHouse_Text_YouMetMatthewInEverGrandeCity:
	.string "Oh? You met Matthew in Ever Grande City?\n"
	.string "Oh, {PLAYER}, don’t be foolish.\p"
	.string "He may be stronger now, but he ain’t\n"
	.string "ready to roam that far all alone.$"

GiantsReach_MatthewsHouse_Text_MatthewWasReallyHappy:
	.string "Matthew was truly joyful when he told\n"
	.string "us he caught a Pokémon.\p"
	.string "It’s been a long time since I’ve seen\n"
	.string "him smile like that. Praise be!$"

GiantsReach_MatthewsHouse_Text_MatthewLeftWithoutTelling:
	.string "I ask you to keep this between us,\n"
	.string "please...\p"
	.string "Matthew left Verdanturf Town without\n"
	.string "lettin' anyone know.\p"
	.string "He’s frail, sure, but he’s got a will\n"
	.string "of iron.\p"
	.string "I trust the Lord will keep him safe,\n"
	.string "and he’ll come back sound and well\l"
	.string "one day.$"

GiantsReach_MatthewsHouse_Movement_FrankLeave:
	walk_down
	walk_down
	step_end

GiantsReach_MatthewsHouse_Movement_PlayerMoveLeftForFrank:
	face_right
	lock_facing_direction
	walk_fast_left
	step_end

GiantsReach_MatthewsHouse_Text_MatthewsDadQuest3:
	.string "I… I don’t know what to make\n"
	.string "of this man, Charlie.\p"
	.string "Frank’s been very… honest.\n"
	.string "Too honest.\p"
	.string "He’s laid out stuff that, normally,\n"
	.string "I’d call immediate confession material.\p"
	.string "He swears up and down you two are\n"
	.string "the best of friends.\p"
	.string "He says it like it’s supposed to\n"
	.string "explain everything, but it just makes\l"
	.string "me more uneasy.\p"
	.string "Just now, he was pitching us on\n"
	.string "some kind of ‘business opportunity’.\l"
	.string "Counterfeit holy water.\p"
	.string "The Lord teaches us to welcome\n"
	.string "strangers, but… with Frank,\l"
	.string "it feels less like hospitality and\l"
	.string "more like enabling.$"

GiantsReach_MatthewsHouse_Text_MatthewsMomQuest3:
	.string "Your friend here…\n"
	.string "he’s been listing off some real\l"
	.string "colorful activities.\p"
	.string "Uh, scams, crimes, I think\n"
	.string "something about eating raccoon meat?\p"
	.string "He keeps asking,\n"
	.string "'So what if I skim just a little off\l"
	.string "the top? Is that hell?'\p"
	.string "Charlie, I can’t…\n"
	.string "I’m not qualified to give a yes\l"
	.string "or no on that.\p"
	.string "We just… pray for him.\n$"

GiantsReach_MatthewsHouse_Text_FrankWaiting:
	.string "Charlie, you find that little treasure\n"
	.string "I stashed yet?\p"
	.string "Don't keep me waitin' too long.\p"
	.string "These folks are nice enough, but\n"
	.string "their constant prayin' is gettin'\l"
	.string "on my nerves.\p"
	.string "Here's that riddle again..\p"
	.string "A little vase with leafy hair,\n"
	.string "got somethin’ juicy hid in there.\l"
	.string "Don’t go screw around in the grass,\l"
	.string "the prize sits where trainers pass.$"
	.string "C'mon Charlie, I thought you\n"
	.string "would have it by now.$"

GiantsReach_MatthewsHouse_Text_FrankTurnIn:
	.string "Well, well, well.\p"
	.string "Look what Charlie dragged in.\p"
	.string "A Root Fossil, huh? Not bad.\n"
	.string "Not bad at all.\p"
	.string "You solved my riddle, kid.\n"
	.string "Fair and square.\p"
	.string "That fossil's all yours now.\n"
	.string "Do whatever the hell you want with it.$"

GiantsReach_MatthewsHouse_Text_FrankLeaving:
	.string "Alright, I’m blowin’ outta here.\p"
	.string "Thanks for the, uh… whatever that was,\n"
	.string "hospitality or judgment or whatever.\p"
	.string "Charlie, listen.\p"
	.string "Above Route 104, there’s this gnarly\n"
	.string "dump of a forest.\p"
	.string "They call it Scrapple Hollow.\p"
	.string "Lotta dopes go in there, don’t come back.\n"
	.string "Whole thing’s like a maze on bath salts.\p"
	.string "If you’re gonna stumble through it,\n"
	.string "you better stock up on Poké Balls,\l"
	.string "potions, whatever's available.\p"
	.string "They say it leads up to Wawa Park.\n"
	.string "Nice place, good sandwiches.\p"
	.string "Anyway, talk to ya later!\n$"

GiantsReach_MatthewsHouse_Text_MatthewsDadAfterFrank:
	.string "I… I can finally breathe again.\n"
	.string "That man’s like a storm in human form.\p"
	.string "He left us with questions I never\n"
	.string "thought I’d have to answer.\p"
	.string "And… he tried to sell me a brick\n"
	.string "with ‘HOLY WATER’ written on it.\p"
	.string "I don’t know if he’s wicked, or just…\n"
	.string "deeply confused.\p"
	.string "Still, the Lord works in mysterious\n"
	.string "ways. Perhaps there was a purpose\l"
	.string "to his visit.\p"
	.string "At least now we can have some\n"
	.string "peace and quiet to pray properly.$"

GiantsReach_MatthewsHouse_Text_MatthewsMomAfterFrank:
	.string "Oh, thank the Lord he's finally gone!\p"
	.string "My word… I have never heard such talk\n"
	.string "in my life.\p"
	.string "Confession, penance, absolution.\n"
	.string "He skipped all of it and went\l"
	.string "straight to the scams.\p"
	.string "He said he’s going to Heaven ‘cause\n"
	.string "he found a loophole.\p"
	.string "The Lord teaches us to welcome\n"
	.string "strangers, but… that one?\l"
	.string "That one tests the limits.\p"
	.string "That man surely was a trial sent\n"
	.string "to test our faith.$"
