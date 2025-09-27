ProfFrank_EventScript_UpdateLocation::
	goto_if_eq VAR_GIANTS_REACH_GYM_STATE, 0, Common_EventScript_NopReturn
	goto_if_set FLAG_SYS_GAME_CLEAR, ProfFrank_EventScript_MoveToLab
	call_if_eq VAR_FRANK_STATE, 0, ProfFrank_EventScript_MoveToLab
	call_if_eq VAR_FRANK_STATE, 1, ProfFrank_EventScript_MoveToLab
	call_if_eq VAR_FRANK_STATE, 2, ProfFrank_EventScript_MoveToRoute101
	call_if_eq VAR_FRANK_STATE, 3, ProfFrank_EventScript_MoveToRoute101
	call_if_eq VAR_FRANK_STATE, 4, ProfFrank_EventScript_MoveToRoute103
	call_if_eq VAR_FRANK_STATE, 5, ProfFrank_EventScript_MoveToRoute103
	call_if_eq VAR_FRANK_STATE, 6, ProfFrank_EventScript_MoveToLab
	call_if_eq VAR_FRANK_STATE, 7, ProfFrank_EventScript_MoveToLab
	return

ProfFrank_EventScript_MoveToLab::
	clearflag FLAG_HIDE_TRASHBURG_FRANKS_LAB_FRANK
	clearflag FLAG_HIDE_TRASHBURG_FRANKS_LAB_UNKNOWN_0x380
	setflag FLAG_HIDE_ROUTE_101_FRANK
	setflag FLAG_HIDE_ROUTE_103_FRANK
	return

ProfFrank_EventScript_MoveToRoute101::
	clearflag FLAG_HIDE_ROUTE_101_FRANK
	setflag FLAG_HIDE_TRASHBURG_FRANKS_LAB_FRANK
	setflag FLAG_HIDE_TRASHBURG_FRANKS_LAB_UNKNOWN_0x380
	setflag FLAG_HIDE_ROUTE_103_FRANK
	return

ProfFrank_EventScript_MoveToRoute103::
	clearflag FLAG_HIDE_ROUTE_103_FRANK
	setflag FLAG_HIDE_ROUTE_101_FRANK
	setflag FLAG_HIDE_TRASHBURG_FRANKS_LAB_FRANK
	setflag FLAG_HIDE_TRASHBURG_FRANKS_LAB_UNKNOWN_0x380
	return

ProfFrank_EventScript_RatePokedexOrRegister::
	lock
	faceplayer
	goto_if_unset FLAG_HAS_MATCH_CALL, ProfFrank_EventScript_AskRatePokedex
	goto_if_unset FLAG_ENABLE_PROF_FRANK_MATCH_CALL, EventScript_RegisterProfFrank

ProfFrank_EventScript_AskRatePokedex::
	msgbox gFrankDexRatingText_AreYouCurious, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, ProfFrank_EventScript_DeclineRating
	call ProfFrank_EventScript_RatePokedex
	release
	end

ProfFrank_EventScript_DeclineRating::
	msgbox gFrankDexRatingText_Cancel, MSGBOX_DEFAULT
	release
	end

ProfFrank_EventScript_ShowRatingMessage::
	copyvar VAR_0x8004, VAR_0x8009
	special ShowPokedexRatingMessage
	waitmessage
	waitbuttonpress
	return

ProfFrank_EventScript_RatePokedex::
	setvar VAR_0x8004, 0
	specialvar VAR_RESULT, ScriptGetPokedexInfo
	copyvar VAR_0x8008, VAR_0x8005
	copyvar VAR_0x8009, VAR_0x8006
	copyvar VAR_0x800A, VAR_RESULT
	buffernumberstring STR_VAR_1, VAR_0x8008  @ Num Hoenn seen
	buffernumberstring STR_VAR_2, VAR_0x8009  @ Num Hoenn caught
	msgbox gFrankDexRatingText_SoYouveSeenAndCaught, MSGBOX_DEFAULT
	call ProfFrank_EventScript_ShowRatingMessage
	goto_if_eq VAR_0x800A, 0, Common_EventScript_NopReturn  @ National dex not enabled
	setvar VAR_0x8004, 1
	specialvar VAR_RESULT, ScriptGetPokedexInfo
	copyvar VAR_0x8008, VAR_0x8005
	copyvar VAR_0x8009, VAR_0x8006
	buffernumberstring STR_VAR_1, VAR_0x8008  @ Num National seen
	buffernumberstring STR_VAR_2, VAR_0x8009  @ Num National caught
	msgbox gFrankDexRatingText_OnANationwideBasis, MSGBOX_DEFAULT
	return
