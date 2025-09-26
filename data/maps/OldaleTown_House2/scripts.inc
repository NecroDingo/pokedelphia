OldaleTown_House2_MapScripts::
	.byte 0

OldaleTown_House2_EventScript_Woman::
	msgbox OldaleTown_House2_Text_PokemonLevelUp, MSGBOX_NPC
	end

OldaleTown_House2_EventScript_Man::
	msgbox OldaleTown_House2_Text_YoullGoFurtherWithStrongPokemon, MSGBOX_NPC
	end

OldaleTown_House2_Text_PokemonLevelUp:
	.string "The stronger your guys get, the less\n"
	.string "likely they are to get absolutely\l" 
	.string "smoked.$"
	.string "Plus, you might even survive outside\n"
	.string "this dump of a town.$"

OldaleTown_House2_Text_YoullGoFurtherWithStrongPokemon:
	.string "Yeah, so apparently when POKéMON fight,\n"
	.string "they get stronger and evolve or mutate\l"
	.string "or something.\p"
	.string "It’s like puberty, but with more lasers.$"

