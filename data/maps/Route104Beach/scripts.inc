Route104Beach_MapScripts::
	.byte 0


	Route104Beach_EventScript_Elise::
	trainerbattle_single TRAINER_ELISE, Route104Beach_Text_EliseIntro, Route104Beach_Text_EliseDefeat
	msgbox Route104Beach_Text_ElisePostBattle, MSGBOX_AUTOCLOSE
	end

	Route104Beach_EventScript_Isla::
	trainerbattle_single TRAINER_ISLA, Route104Beach_Text_IslaIntro, Route104Beach_Text_IslaDefeat
	msgbox Route104Beach_Text_IslaPostBattle, MSGBOX_AUTOCLOSE
	end

	Route104Beach_EventScript_Hugo::
	trainerbattle_single TRAINER_HUGO, Route104Beach_Text_HugoIntro, Route104Beach_Text_HugoDefeat
	msgbox Route104Beach_Text_HugoPostBattle, MSGBOX_AUTOCLOSE
	end

	Route104Beach_EventScript_Oscar::
	trainerbattle_single TRAINER_OSCAR, Route104Beach_Text_OscarIntro, Route104Beach_Text_OscarDefeat
	msgbox Route104Beach_Text_OscarPostBattle, MSGBOX_AUTOCLOSE
	end

