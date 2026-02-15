OldaleTown_Mart_MapScripts::
	.byte 0

OldaleTown_Mart_EventScript_Clerk::
	lock
	faceplayer
	specialvar VAR_TEMP_0, CalculatePlayerPartyCount
	specialvar VAR_TEMP_1, CountPartyNonEggMons
	goto_if_lt VAR_TEMP_1, VAR_TEMP_0, OldaleTown_Mart_EventScript_QuestCheck
	message gText_HowMayIServeYou
	waitmessage
	goto_if_set FLAG_ADVENTURE_STARTED, OldaleTown_Mart_ExpandedItems
	pokemart OldaleTown_Mart_Pokemart_Basic
	goto OldaleTown_Mart_PostMart


OldaleTown_Mart_EventScript_QuestCheck::
questmenu QUEST_MENU_CHECK_COMPLETE, QUEST_2_EGG_SCAM
goto_if_quest_complete QUEST_2_EGG_SCAM, OldaleTown_Mart_EventScript_HasEggNoQuest
goto OldaleTown_Mart_EventScript_HasEggQuestActive

OldaleTown_Mart_EventScript_HasEggQuestActive::
	msgbox OldaleTown_Mart_Text_EggScamGreeting, MSGBOX_DEFAULT
	waitmessage
	goto_if_set FLAG_ADVENTURE_STARTED, OldaleTown_Mart_ExpandedItems
	pokemart OldaleTown_Mart_Pokemart_Basic
	goto OldaleTown_Mart_PostMart


OldaleTown_Mart_EventScript_HasEggNoQuest::
	msgbox OldaleTown_Mart_Text_EggScamGreeting, MSGBOX_DEFAULT
	waitmessage
	goto_if_set FLAG_ADVENTURE_STARTED, OldaleTown_Mart_ExpandedItems
	pokemart OldaleTown_Mart_Pokemart_Basic
	goto OldaleTown_Mart_PostMart


	.align 2
OldaleTown_Mart_Pokemart_Basic:
	.2byte ITEM_POTION
	.2byte ITEM_ANTIDOTE
	.2byte ITEM_PARALYZE_HEAL
	.2byte ITEM_AWAKENING
	pokemartlistend

OldaleTown_Mart_ExpandedItems::
	pokemart OldaleTown_Mart_Pokemart_Expanded
	goto OldaleTown_Mart_PostMart


	.align 2
OldaleTown_Mart_Pokemart_Expanded:
	.2byte ITEM_POKE_BALL
	.2byte ITEM_POTION
	.2byte ITEM_ANTIDOTE
	.2byte ITEM_PARALYZE_HEAL
	.2byte ITEM_AWAKENING
	pokemartlistend

OldaleTown_Mart_PostMart:
	msgbox gText_PleaseComeAgain, MSGBOX_DEFAULT
	waitmessage

	specialvar VAR_TEMP_0, CalculatePlayerPartyCount
	specialvar VAR_TEMP_1, CountPartyNonEggMons
	goto_if_lt VAR_TEMP_1, VAR_TEMP_0, OldaleTown_Mart_PostMart_QuestCheck
	release
	end

OldaleTown_Mart_PostMart_QuestCheck::
	questmenu QUEST_MENU_CHECK_COMPLETE, QUEST_2_EGG_SCAM
	goto_if_quest_complete QUEST_2_EGG_SCAM, OldaleTown_Mart_PostMart_HasEggNoQuest
	questmenu QUEST_MENU_SET_REWARD QUEST_2_EGG_SCAM
	applymovement LOCALID_PLAYER, Common_Movement_WalkInPlaceFasterDown
	waitmovement 0
	msgbox OldaleTown_Mart_Text_TellPlayerToSeeFrank, MSGBOX_DEFAULT
	waitmessage
	release
	end

OldaleTown_Mart_PostMart_HasEggNoQuest::
	release
	end

OldaleTown_Mart_EventScript_Woman::
	lock
	faceplayer
	goto_if_set FLAG_ADVENTURE_STARTED, OldaleTown_Mart_EventScript_PokeBallsInStock
	msgbox OldaleTown_Mart_Text_PokeBallsAreSoldOut, MSGBOX_DEFAULT
	release
	end

OldaleTown_Mart_EventScript_PokeBallsInStock::
	msgbox OldaleTown_Mart_Text_ImGoingToBuyPokeBalls, MSGBOX_DEFAULT
	release
	end

OldaleTown_Mart_EventScript_Boy::
	msgbox OldaleTown_Mart_Text_RestoreHPWithPotion, MSGBOX_NPC
	end

OldaleTown_Mart_Text_PokeBallsAreSoldOut:
	.string "Can you believe this? They're out\n"
	.string "of Poké Balls... Outrageous!\p"
	.string "What kind of operation are they\n"
	.string "runnin' here?$"

OldaleTown_Mart_Text_ImGoingToBuyPokeBalls:
	.string "Finally they're back. I've been\n"
	.string "waiting forever!\p"
	.string "I’m gonna scoop up like a dozen\n"
	.string "Poké Balls.\p"
	.string "Catch everything that moves.\n"
	.string "That’s the plan.$"

OldaleTown_Mart_Text_RestoreHPWithPotion:
	.string "If your guy gets knocked out, he’s done.\n"
	.string "Keep some potions on you or you’re toast.\p"
	.string "No one wants to see their main guy eat\n"
	.string "dirt out there.$"

OldaleTown_Mart_Text_EggScamGreeting:
	.string "Yo.\p"
	.string "..... ..... ..... .....\p"
	.string "Aww shit...\n"
	.string "You here for the Professor, huh?\p"
	.string "..... ..... ..... .....\p"
	.string "Tell that low-life piece of garbage\n"
	.string "to take those janky eggs and shove ’em\l"
	.string "where the sun don’t shine...\l"
	.string "capisce?\p"
	.string "Now you gonna buy somethin’ or you\n"
	.string "just here to make a scene?$"

OldaleTown_Mart_Text_TellPlayerToSeeFrank:
	.string "Go back to Frank and tell him about\n"
	.string "the clerk not wanting his egg.$"
