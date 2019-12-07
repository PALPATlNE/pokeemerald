Route120_EventScript_Roggenrola1:: @ 82722DB
	lock
	faceplayer
	setvar VAR_0x8009, 1
	goto EventScript_Roggenrola
	end

Route120_EventScript_Roggenrola2:: @ 82722E8
	lock
	faceplayer
	setvar VAR_0x8009, 2
	goto EventScript_Roggenrola
	end

Route120_EventScript_Roggenrola3:: @ 82722F5
	lock
	faceplayer
	setvar VAR_0x8009, 3
	goto EventScript_Roggenrola
	end

Route120_EventScript_Roggenrola4:: @ 8272302
	lock
	faceplayer
	setvar VAR_0x8009, 4
	goto EventScript_Roggenrola
	end

Route120_EventScript_Roggenrola5:: @ 827230F
	lock
	faceplayer
	setvar VAR_0x8009, 5
	goto EventScript_Roggenrola
	end

Route119_EventScript_Roggenrola1:: @ 827231C
	lock
	faceplayer
	setvar VAR_0x8009, 6
	goto EventScript_Roggenrola
	end

Route119_EventScript_Roggenrola2:: @ 8272329
	lock
	faceplayer
	setvar VAR_0x8009, 7
	goto EventScript_Roggenrola
	end

EventScript_Roggenrola:: @ 8272336
	checkitem ITEM_DEVON_SCOPE, 1
	compare VAR_RESULT, 1
	goto_if_eq EventScript_AskUseDevonScope
	msgbox Roggenrola_Text_SomethingUnseeable, MSGBOX_DEFAULT
	release
	end

EventScript_AskUseDevonScope:: @ 8272350
	msgbox Roggenrola_Text_WantToUseDevonScope, MSGBOX_YESNO
	compare VAR_RESULT, 1
	goto_if_eq EventScript_BattleRoggenrola
	release
	end

EventScript_BattleRoggenrola:: @ 8272365
	msgbox Roggenrola_Text_UseDevonScopeMonAttacked, MSGBOX_DEFAULT
	closemessage
	applymovement VAR_LAST_TALKED, Common_Movement_FacePlayer
	waitmovement 0
	applymovement VAR_LAST_TALKED, Movement_RoggenrolaAppears
	waitmovement 0
	waitse
	playmoncry SPECIES_ROGGENROLA, 2
	delay 40
	waitmoncry
	setwildbattle SPECIES_ROGGENROLA, 30, ITEM_NONE
	setflag FLAG_SYS_CTRL_OBJ_DELETE
	dowildbattle
	clearflag FLAG_SYS_CTRL_OBJ_DELETE
	specialvar VAR_RESULT, GetBattleOutcome
	compare VAR_RESULT, B_OUTCOME_WON
	goto_if_eq EventScript_RemoveRoggenrola
	compare VAR_RESULT, B_OUTCOME_RAN
	goto_if_eq EventScript_RemoveRoggenrola
	compare VAR_RESULT, B_OUTCOME_PLAYER_TELEPORTED
	goto_if_eq EventScript_RemoveRoggenrola
	release
	end

EventScript_RemoveRoggenrola:: @ 82723C1
	goto Common_EventScript_RemoveStaticPokemon
	end

Movement_RoggenrolaAppears: @ 82723C7
	set_visible
	delay_4
	set_invisible
	delay_4
	set_visible
	delay_4
	set_invisible
	delay_4
	set_visible
	delay_8
	set_invisible
	delay_8
	set_visible
	delay_8
	set_invisible
	delay_8
	set_visible
	delay_16
	set_invisible
	delay_16
	set_visible
	step_end
