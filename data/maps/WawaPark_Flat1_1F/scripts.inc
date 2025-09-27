WawaPark_Flat1_1F_MapScripts::
	.byte 0

WawaPark_Flat1_1F_EventScript_Man::
	msgbox WawaPark_Flat1_1F_Text_EveryPokemonHasAbility, MSGBOX_NPC
	end

WawaPark_Flat1_1F_EventScript_Woman::
	msgbox WawaPark_Flat1_1F_Text_PokemonStrange, MSGBOX_NPC
	end

WawaPark_Flat1_1F_Text_EveryPokemonHasAbility:
	.string "Every POKéMON has a special ability\n"
	.string "that it can use.$"

WawaPark_Flat1_1F_Text_PokemonStrange:
	.string "POKéMON are such strange creatures.$"

