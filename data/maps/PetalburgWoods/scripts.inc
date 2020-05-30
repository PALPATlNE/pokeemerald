PetalburgWoods_MapScripts:: @ 822DFD6
	.byte 0

TestScript::
	clearflag FLAG_HIDE_ROUTE104_POKEMON
	releaseall
	end

SarinForest_BugCatcher_Trainer:: @ 81F2B3E
	trainerbattle_single TRAINER_JOSH, SarinForest_Text_JoshIntro, SarinForest_Text_JoshDefeat	
	msgbox SarinForest_Text_JoshPostBattle, MSGBOX_AUTOCLOSE
	end
