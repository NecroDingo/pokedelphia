WawaPark_House3_MapScripts::
	.byte 0

WawaPark_House3_EventScript_OldMan::
	msgbox WawaPark_House3_Text_IGivePerfectlySuitedNicknames, MSGBOX_NPC
	end

WawaPark_House3_EventScript_OldWoman::
	msgbox WawaPark_House3_Text_NamingPikachuPekachu, MSGBOX_NPC
	end

@ Misspelling on purpose, see nickname
WawaPark_House3_EventScript_Pekachu::
	lock
	faceplayer
	waitse
	playmoncry SPECIES_PIKACHU, CRY_MODE_NORMAL
	msgbox WawaPark_House3_Text_Pekachu, MSGBOX_DEFAULT
	waitmoncry
	release
	end

WawaPark_House3_Text_IGivePerfectlySuitedNicknames:
	.string "For my own POKéMON, I give them\n"
	.string "perfectly suited nicknames!\p"
	.string "It's my expression of, uh…\n"
	.string "originality, yes, that's it!$"

WawaPark_House3_Text_NamingPikachuPekachu:
	.string "But giving the name PEKACHU to\n"
	.string "a PIKACHU? It seems pointless.\p"
	.string "I suppose it is good to use a name\n"
	.string "that's easy to understand, but…$"

WawaPark_House3_Text_Pekachu:
	.string "PEKACHU: Peka!$"

