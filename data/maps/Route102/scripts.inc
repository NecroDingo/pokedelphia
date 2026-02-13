Route102_MapScripts::

	.byte 0

Route102_EventScript_LittleBoy::
	msgbox Route102_Text_ImNotVeryTall, MSGBOX_NPC
	end

Route102_EventScript_RouteSignOldale::
	msgbox Route102_Text_RouteSignOldale, MSGBOX_SIGN
	end

Route102_EventScript_RouteSignPetalburg::
	msgbox Route102_Text_RouteSignPetalburg, MSGBOX_SIGN
	end

Route102_EventScript_Boy::
	msgbox Route102_Text_CatchWholeBunchOfPokemon, MSGBOX_NPC
	end

Route102_EventScript_Calvin::
	trainerbattle_single TRAINER_CALVIN_1, Route102_Text_CalvinIntro, Route102_Text_CalvinDefeated, Route102_EventScript_CalvinRegisterMatchCallAfterBattle
	specialvar VAR_RESULT, ShouldTryRematchBattle
	goto_if_eq VAR_RESULT, TRUE, Route102_EventScript_CalvinRematch
	setvar VAR_0x8004, TRAINER_CALVIN_1
	specialvar VAR_RESULT, IsTrainerRegistered
	goto_if_eq VAR_RESULT, FALSE, Route102_EventScript_CalvinTryRegister
	msgbox Route102_Text_CalvinPostBattle, MSGBOX_DEFAULT
	release
	end

Route102_EventScript_CalvinRegisterMatchCallAfterBattle::
	special PlayerFaceTrainerAfterBattle
	waitmovement 0
	goto_if_set FLAG_HAS_MATCH_CALL, Route102_EventScript_CalvinRegisterMatchCall
	release
	end

Route102_EventScript_CalvinRegisterMatchCall::
	msgbox Route102_Text_CalvinRegisterShort, MSGBOX_DEFAULT
	register_matchcall TRAINER_CALVIN_1
	release
	end

Route102_EventScript_CalvinTryRegister::
	goto_if_set FLAG_HAS_MATCH_CALL, Route102_EventScript_CalvinRegister
	msgbox Route102_Text_CalvinPostBattle, MSGBOX_DEFAULT
	release
	end

Route102_EventScript_CalvinRegister::
	msgbox Route102_Text_CalvinRegister, MSGBOX_DEFAULT
	register_matchcall TRAINER_CALVIN_1
	release
	end

Route102_EventScript_CalvinRematch::
	trainerbattle_rematch TRAINER_CALVIN_1, Route102_Text_CalvinRematchIntro, Route102_Text_CalvinRematchDefeated
	msgbox Route102_Text_CalvinRematchPostBattle, MSGBOX_AUTOCLOSE
	end

Route102_EventScript_Rick::
	trainerbattle_single TRAINER_RICK, Route102_Text_RickIntro, Route102_Text_RickDefeated
	msgbox Route102_Text_RickPostBattle, MSGBOX_AUTOCLOSE
	end

Route102_EventScript_Tiana::
	trainerbattle_single TRAINER_TIANA, Route102_Text_TianaIntro, Route102_Text_TianaDefeated
	msgbox Route102_Text_TianaPostBattle, MSGBOX_AUTOCLOSE
	end

Route102_EventScript_Allen::
	trainerbattle_single TRAINER_ALLEN, Route102_Text_AllenIntro, Route102_Text_AllenDefeated
	msgbox Route102_Text_AllenPostBattle, MSGBOX_AUTOCLOSE
	end

Route102_EventScript_Meghan::
	trainerbattle_single TRAINER_MEGHAN, Route102_Text_MeghanIntro, Route102_Text_MeghanDefeated
	msgbox Route102_Text_MeghanPostBattle, MSGBOX_AUTOCLOSE
	end

Route102_EventScript_Zach::
	trainerbattle_single TRAINER_ZACH, Route102_Text_ZachIntro, Route102_Text_ZachDefeated
	msgbox Route102_Text_ZachPostBattle, MSGBOX_AUTOCLOSE
	end

Route102_EventScript_Chaz::
	trainerbattle_single TRAINER_CHAZ, Route102_Text_ChazIntro, Route102_Text_ChazDefeated
	msgbox Route102_Text_ChazPostBattle, MSGBOX_AUTOCLOSE
	end

Route102_EventScript_Hikaru::
	trainerbattle_single TRAINER_HIKARU, Route102_Text_HikaruIntro, Route102_Text_HikaruDefeated
	msgbox Route102_Text_HikaruPostBattle, MSGBOX_AUTOCLOSE
	end

Route102_Text_WatchMeCatchPokemon:
	.string "Matthew: Thanks, {PLAYER}…\p"
	.string "Pokémon usually hang out in tall\n"
	.string "grass like this, right? Alright.\p"
	.string "Watch me snag one real quick.\n"
	.string "Just gotta be calm, confident…\p"
	.string "…Wait, whoa, oh my goodness?!\p"
	.string "That thing’s not supposed to be here!\n"
	.string "Is this even legal!?$"

Route102_Text_WallyIDidIt:
	.string "Matthew: I actually did it…\p"
	.string "This is my Pokémon now!\n"
	.string "For real! My own partner!$"

Route102_Text_LetsGoBack:
	.string "Matthew: {PLAYER}, you’re the real MVP.\n"
	.string "For real.\p"
	.string "Let’s head back to the Gym!\n$"

Route102_Text_ImNotVeryTall:
	.string "Yo... what street even is this?\p"
	.string "I been walkin' in circles\n"
	.string "for like, an hour now.\p"
	.string "I'm all turned around bro.$"

Route102_Text_CatchWholeBunchOfPokemon:
	.string "Hey bro, you goin' in there?\p"
	.string "This place is scary as hell.\p"
	.string "I heard some wild Pokémon\n"
	.string "been actin’ real funny.\p"
	.string "Keep ya eyes peeled, a'ight?$"

Route102_Text_RouteSignOldale:
	.string "ROUTE 102\n"
	.string "{RIGHT_ARROW} OLD SCUMPORT$"

Route102_Text_RouteSignPetalburg:
	.string "ROUTE 102\n"
	.string "{LEFT_ARROW} GIANT'S REACH$"
