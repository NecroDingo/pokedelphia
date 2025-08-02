PetalburgCity_Mart_MapScripts::
	.byte 0

PetalburgCity_Mart_EventScript_Clerk::
	lock
	faceplayer
	goto_if_set FLAG_DAILY_GIANT_REACH_MART, PetalburgCity_Mart_EventScript_Clerk_Regular
	message gText_MyBrotherInOldale
	waitmessage
	setflag FLAG_DAILY_GIANT_REACH_MART
	goto PetalburgCity_Mart_EventScript_Clerk_Continue

PetalburgCity_Mart_EventScript_Clerk_Regular:
	message gText_HowMayIServeYou
	waitmessage
	goto PetalburgCity_Mart_EventScript_Clerk_Continue

PetalburgCity_Mart_EventScript_Clerk_Continue:
	goto_if_set FLAG_PETALBURG_MART_EXPANDED_ITEMS, PetalburgCity_Mart_EventScript_ExpandedItems
	pokemart PetalburgCity_Mart_Pokemart_Basic
	msgbox gText_PleaseComeAgain, MSGBOX_DEFAULT
	release
	end

	.align 2
PetalburgCity_Mart_Pokemart_Basic:
	.2byte ITEM_POKE_BALL
	.2byte ITEM_POTION
	.2byte ITEM_ANTIDOTE
	.2byte ITEM_PARALYZE_HEAL
	.2byte ITEM_AWAKENING
	.2byte ITEM_ESCAPE_ROPE
	.2byte ITEM_REPEL
	.2byte ITEM_X_SPEED
	.2byte ITEM_X_ATTACK
	.2byte ITEM_X_DEFENSE
	.2byte ITEM_ORANGE_MAIL
	pokemartlistend

PetalburgCity_Mart_EventScript_ExpandedItems::
	pokemart PetalburgCity_Mart_Pokemart_Expanded
	msgbox gText_PleaseComeAgain, MSGBOX_DEFAULT
	release
	end

	.align 2
PetalburgCity_Mart_Pokemart_Expanded:
	.2byte ITEM_POKE_BALL
	.2byte ITEM_GREAT_BALL
	.2byte ITEM_POTION
	.2byte ITEM_SUPER_POTION
	.2byte ITEM_ANTIDOTE
	.2byte ITEM_PARALYZE_HEAL
	.2byte ITEM_AWAKENING
	.2byte ITEM_ESCAPE_ROPE
	.2byte ITEM_REPEL
	.2byte ITEM_X_SPEED
	.2byte ITEM_X_ATTACK
	.2byte ITEM_X_DEFENSE
	.2byte ITEM_ORANGE_MAIL
	pokemartlistend

PetalburgCity_Mart_EventScript_Woman::
	msgbox PetalburgCity_Mart_Text_WeakWillGrowStronger, MSGBOX_NPC
	end

PetalburgCity_Mart_EventScript_Boy::
	msgbox PetalburgCity_Mart_Text_RepelIsUseful, MSGBOX_NPC
	end

PetalburgCity_Mart_EventScript_Man::
	msgbox PetalburgCity_Mart_Text_TakeSomeAntidotesWithYou, MSGBOX_NPC
	end

PetalburgCity_Mart_Text_WeakWillGrowStronger:
	.string "Look, even if your Pokémon’s kinda\n"
	.string "weak right now, don’t sweat it!\l"
	.string "They’ll get stronger, no doubt.\p"
	.string "The key? It’s all about love, ya know?\p"
	.string "Some might say brotherly love, but I say\n"
	.string "Pokémon love.\p"
	.string "That’s what makes the difference!$"

PetalburgCity_Mart_Text_RepelIsUseful:
	.string "You ever use REPEL?\p"
	.string "It keeps wild Pokémon off your back.\p"
	.string "Real handy when you’re tryin’ to get\n"
	.string "somewhere fast.$"

PetalburgCity_Mart_Text_TakeSomeAntidotesWithYou:
	.string "You got any ANTIDOTES on you?\p"
	.string "‘Cause if your Pokémon gets poisoned,\n"
	.string "it’s gonna lose HP till it drops.\p"
	.string "Best to carry some ANTIDOTES, trust me\n"
	.string "on this one bro.$"

