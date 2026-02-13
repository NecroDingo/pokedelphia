Route104_MrBrineysHouse_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, Route104_MrBrineysHouse_OnTransition
	.byte 0

Route104_MrBrineysHouse_OnTransition:
	setflag FLAG_LANDMARK_MR_BRINEY_HOUSE
	call_if_eq VAR_BRINEY_HOUSE_STATE, 1, Route104_MrBrineysHouse_EventScript_SetBrineyPeekoPos
	call_if_set FLAG_RECEIVED_POKENAV, Route104_MrBrineysHouse_EventScript_HideRustboroRival
	end

Route104_MrBrineysHouse_EventScript_HideRustboroRival::
	setflag FLAG_HIDE_RUSTBORO_CITY_RIVAL
	return

Route104_MrBrineysHouse_EventScript_SetBrineyPeekoPos::
	setobjectxyperm LOCALID_BRINEYS_HOUSE_BRINEY, 9, 3
	setobjectmovementtype LOCALID_BRINEYS_HOUSE_BRINEY, MOVEMENT_TYPE_WALK_SEQUENCE_DOWN_LEFT_UP_RIGHT
	setobjectxyperm LOCALID_BRINEYS_HOUSE_PEEKO, 9, 6
	setobjectmovementtype LOCALID_BRINEYS_HOUSE_PEEKO, MOVEMENT_TYPE_WALK_SEQUENCE_LEFT_UP_RIGHT_DOWN
	return

Route104_MrBrineysHouse_EventScript_Briney::
	lock
	faceplayer
	call_if_unset FLAG_MR_BRINEY_SAILING_INTRO, Route104_MrBrineysHouse_EventScript_SailingIntro
	goto_if_unset FLAG_DELIVERED_STEVEN_LETTER, Route104_MrBrineysHouse_EventScript_SailBothDeliveries
	goto_if_unset FLAG_DELIVERED_DEVON_GOODS, Route104_MrBrineysHouse_EventScript_SailDeliverPackage
	goto Route104_MrBrineysHouse_EventScript_WhereAreWeBound
	end

Route104_MrBrineysHouse_EventScript_SailingIntro::
	setflag FLAG_MR_BRINEY_SAILING_INTRO
	msgbox Route104_MrBrineysHouse_Text_WaitUpPeeko, MSGBOX_DEFAULT
	msgbox Route104_MrBrineysHouse_Text_ItsYouLetsSailToDewford, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, Route104_MrBrineysHouse_EventScript_DeclineDeliverySailing
	goto Route104_MrBrineysHouse_EventScript_SailToDewford
	end

Route104_MrBrineysHouse_EventScript_WhereAreWeBound::
	message Route104_MrBrineysHouse_Text_WhereAreWeBound
	waitmessage
	multichoicedefault 20, 8, MULTI_BRINEY_OFF_DEWFORD, 1, FALSE
	switch VAR_RESULT
	case 0, Route104_MrBrineysHouse_EventScript_SailToDewford
	case 1, Route104_MrBrineysHouse_EventScript_DeclineSailing
	case MULTI_B_PRESSED, Route104_MrBrineysHouse_EventScript_DeclineSailing
	end

Route104_MrBrineysHouse_EventScript_SailBothDeliveries::
	msgbox Route104_MrBrineysHouse_Text_NeedToMakeDeliveriesSailToDewford, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, Route104_MrBrineysHouse_EventScript_DeclineDeliverySailing
	goto Route104_MrBrineysHouse_EventScript_SailToDewford
	end

Route104_MrBrineysHouse_EventScript_SailDeliverPackage::
	msgbox Route104_MrBrineysHouse_Text_NeedToDeliverPackageSailToDewford, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, Route104_MrBrineysHouse_EventScript_DeclineDeliverySailing
	goto Route104_MrBrineysHouse_EventScript_SailToDewford
	end

Route104_MrBrineysHouse_EventScript_DeclineDeliverySailing::
	msgbox Route104_MrBrineysHouse_Text_DeclineDeliverySail, MSGBOX_DEFAULT
	release
	end

Route104_MrBrineysHouse_EventScript_DeclineSailing::
	msgbox Route104_MrBrineysHouse_Text_TellMeWheneverYouWantToSail, MSGBOX_DEFAULT
	release
	end

Route104_MrBrineysHouse_EventScript_SailToDewford::
	msgbox Route104_MrBrineysHouse_Text_SetSailForDewford, MSGBOX_DEFAULT
	call EventScript_BackupMrBrineyLocation
	setvar VAR_BOARD_BRINEY_BOAT_STATE, 1
	clearflag FLAG_HIDE_ROUTE_104_MR_BRINEY
	setflag FLAG_HIDE_BRINEYS_HOUSE_MR_BRINEY
	setflag FLAG_HIDE_BRINEYS_HOUSE_PEEKO
	setvar VAR_RUSTBORO_CITY_STATE, 8
	setvar VAR_ROUTE104_STATE, 2
	setflag FLAG_HIDE_RUSTBORO_CITY_RIVAL
	setflag FLAG_HIDE_ROUTE_104_RIVAL
	warp MAP_ROUTE104, 13, 51
	waitstate
	releaseall
	end

Route104_MrBrineysHouse_EventScript_Peeko::
	lock
	faceplayer
	waitse
	playmoncry SPECIES_WINGULL, CRY_MODE_NORMAL
	msgbox Route104_MrBrineysHouse_Text_Peeko, MSGBOX_DEFAULT
	waitmoncry
	release
	end

Route104_MrBrineysHouse_Text_WaitUpPeeko:
	.string "ARTEMIS: Hold up, baby!\p"
	.string "Wait up, SKYLAR!\n"
	.string "Your mother’s still adjusting her\l"
	.string "stance.$"


Route104_MrBrineysHouse_Text_ItsYouLetsSailToDewford:
	.string "Hm? Ohhh, it’s {PLAYER}!\n"
	.string "The hero who saved my precious SKYLAR!\p"
	.string "Oh, he used to be “PEEKO,”\n"
	.string "but I renamed him after my first crush\l"
	.string "from mime school.\p"
	.string "Skylar had big dreams, and an even\n"
	.string "bigger relationship with the wind.\p"
	.string "Anyway, you need a ride?\p"
	.string "....... ....... ....... .......\p"
	.string "A LETTER to DEWFORD and a package for SLATEPORT?\p"
	.string "I love a multi-stop voyage. It’s like a\n"
	.string "progressive dinner, but saltier.\p"
	.string "You’ve come to the right woman.\n"
	.string "Let’s set sail, baby!$"

Route104_MrBrineysHouse_Text_SetSailForDewford:
	.string "ARTEMIS: DEWFORD, here we come!\n"
	.string "Anchors aweigh, and bras off!\p"
	.string "SKYLAR, let’s show ‘em what a wind\n"
	.string "child can do!$"

Route104_MrBrineysHouse_Text_DeclineDeliverySail:
	.string "ARTEMIS: Ohhh, playing hard to get, huh?\p"
	.string "Your deliveries can wait?\p"
	.string "Fine, but don’t tease a woman who\n"
	.string "has a boat, a SKYLAR, and zero\l"
	.string "boundaries.$"

Route104_MrBrineysHouse_Text_NeedToMakeDeliveriesSailToDewford:
	.string "ARTEMIS: Ahoy baby!\p"
	.string "I can smell a mission from a mile away.\p"
	.string "Letter for DEWFORD, package for\n"
	.string "SLATEPORT? This is how legends are\l"
	.string "made, baby.\p"
	.string "No problem. First stop DEWFORD.\n"
	.string "SKYLAR will catch the wind for us.$"

Route104_MrBrineysHouse_Text_NeedToDeliverPackageSailToDewford:
	.string "ARTEMIS: Ahoy baby!\p"
	.string "Package to CAPT. STERN in SLATEPORT?\n"
	.string "I’ve done stranger deliveries… much stranger.\p"
	.string "Once with SKYLAR in a hat..\n"
	.string "Don’t ask.\p"
	.string "First stop, DEWFORD.$"

Route104_MrBrineysHouse_Text_WhereAreWeBound:
	.string "ARTEMIS: Ahoy, baby!\p"
	.string "For you, I’ll hit the open sea anytime.\p"
	.string "Where we going? SKYLAR’s ready to fly.$"

Route104_MrBrineysHouse_Text_TellMeWheneverYouWantToSail:
	.string "ARTEMIS: Is that so?\p"
	.string "Well, SKYLAR owes you everything…\n"
	.string "and I mean everything.\p"
	.string "You just say the word, sailor, and\n"
	.string "we’ll make the tide blush.$"

Route104_MrBrineysHouse_Text_Peeko:
	.string "SKYLAR: Pii piihyoro!$"

