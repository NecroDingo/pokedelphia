PetalburgCity_WallysHouse_MapScripts::
	map_script MAP_SCRIPT_ON_FRAME_TABLE, PetalburgCity_WallysHouse_OnFrame
	map_script MAP_SCRIPT_ON_WARP_INTO_MAP_TABLE, PetalburgCity_WallysHouse_OnWarp
	.byte 0

PetalburgCity_WallysHouse_OnWarp:
	map_script_2 VAR_PETALBURG_CITY_STATE, 4, PetalburgCity_WallysHouse_EventScript_PlayerWallysDadFaceEachOther
	.2byte 0

PetalburgCity_WallysHouse_EventScript_PlayerWallysDadFaceEachOther::
	turnobject LOCALID_PLAYER, DIR_EAST
	turnobject LOCALID_WALLYS_HOUSE_WALLYS_DAD, DIR_WEST
	end

PetalburgCity_WallysHouse_OnFrame:
	map_script_2 VAR_PETALBURG_CITY_STATE, 4, PetalburgCity_WallysHouse_EventScript_GiveHMSurf
	.2byte 0

PetalburgCity_WallysHouse_EventScript_GiveHMSurf::
	lockall
	msgbox PetalburgCity_WallysHouse_Text_PleaseExcuseUs, MSGBOX_DEFAULT
	giveitem ITEM_HM_SURF
	setflag FLAG_RECEIVED_HM_SURF
	msgbox PetalburgCity_WallysHouse_Text_SurfGoAllSortsOfPlaces, MSGBOX_DEFAULT
	setvar VAR_PETALBURG_CITY_STATE, 5
	releaseall
	end

PetalburgCity_WallysHouse_EventScript_WallysDad::
	lock
	faceplayer
	goto_if_set FLAG_DEFEATED_WALLY_VICTORY_ROAD, PetalburgCity_WallysHouse_EventScript_DefeatedWallyInVictoryRoad
	goto_if_set FLAG_RECEIVED_HM_SURF, PetalburgCity_WallysHouse_EventScript_ReceievedHMSurf
	goto_if_set FLAG_THANKED_FOR_PLAYING_WITH_WALLY, PetalburgCity_WallysHouse_EventScript_PlayedWithWally
	msgbox PetalburgCity_WallysHouse_Text_ThanksForPlayingWithWally, MSGBOX_DEFAULT
	setflag FLAG_THANKED_FOR_PLAYING_WITH_WALLY
	release
	end

PetalburgCity_WallysHouse_EventScript_ReceievedHMSurf::
	msgbox PetalburgCity_WallysHouse_Text_WallyIsComingHomeSoon, MSGBOX_DEFAULT
	release
	end

PetalburgCity_WallysHouse_EventScript_DefeatedWallyInVictoryRoad::
	msgbox PetalburgCity_WallysHouse_Text_YouMetWallyInEverGrandeCity, MSGBOX_DEFAULT
	release
	end

PetalburgCity_WallysHouse_EventScript_PlayedWithWally::
	msgbox PetalburgCity_WallysHouse_Text_WonderHowWallyIsDoing, MSGBOX_DEFAULT
	release
	end

PetalburgCity_WallysHouse_EventScript_WallysMom::
	lock
	faceplayer
	goto_if_set FLAG_RECEIVED_HM_SURF, PetalburgCity_WallysHouse_EventScript_ReceivedHMSurf
	msgbox PetalburgCity_WallysHouse_Text_WallyWasReallyHappy, MSGBOX_DEFAULT
	release
	end

PetalburgCity_WallysHouse_EventScript_ReceivedHMSurf::
	msgbox PetalburgCity_WallysHouse_Text_WallyLeftWithoutTelling, MSGBOX_DEFAULT
	release
	end

PetalburgCity_WallysHouse_Text_ThanksForPlayingWithWally:
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

PetalburgCity_WallysHouse_Text_WonderHowWallyIsDoing:
	.string "I wonder how our Matthew’s holdin’ up\n"
	.string "these days.$"

PetalburgCity_WallysHouse_Text_PleaseExcuseUs:
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

PetalburgCity_WallysHouse_Text_SurfGoAllSortsOfPlaces:
	.string "If your Pokémon can Surf, you’ll be\n"
	.string "able to travel to all kinds of places,\l"
	.string "God willing.$"

PetalburgCity_WallysHouse_Text_WallyIsComingHomeSoon:
	.string "Matthew’s comin’ home soon.\p"
	.string "I’m lookin’ forward to that day with all\n"
	.string "my heart.$"

PetalburgCity_WallysHouse_Text_YouMetWallyInEverGrandeCity:
	.string "Oh? You met Matthew in Ever Grande City?\n"
	.string "Oh, {PLAYER}, don’t be foolish.\p"
	.string "He may be stronger now, but he ain’t\n"
	.string "ready to roam that far all alone.$"

PetalburgCity_WallysHouse_Text_WallyWasReallyHappy:
	.string "Matthew was truly joyful when he told\n"
	.string "us he caught a Pokémon.\p"
	.string "It’s been a long time since I’ve seen\n"
	.string "him smile like that. Praise be!$"

PetalburgCity_WallysHouse_Text_WallyLeftWithoutTelling:
	.string "I ask you to keep this between us,\n"
	.string "please...\p"
	.string "Matthew left Verdanturf Town without\n"
	.string "lettin' anyone know.\p"
	.string "He’s frail, sure, but he’s got a will\n"
	.string "of iron.\p"
	.string "I trust the Lord will keep him safe,\n"
	.string "and he’ll come back sound and well\l"
	.string "one day.$"

