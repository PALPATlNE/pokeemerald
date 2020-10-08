.set LOCALID_RIVAL, 2

Route103_MapScripts:: @ 81EC38E
	.byte 0

Route3_House_Sign::
	msgbox Route3_House_Sign_Text, MSGBOX_SIGN
	end

Route3_Teen_Girl::
	faceplayer
	msgbox Route3_Teen_Girl_Text, MSGBOX_NPC
	end

Route3_Little_Girl::
	faceplayer
	msgbox Route3_Little_Girl_Text, MSGBOX_NPC
	end

Route3_Fisherman_Trainer:: @ 81F2B3E
	trainerbattle_single TRAINER_SAXTON, Route3_Text_SaxtonIntro, Route3_Text_SaxtonDefeated
	msgbox Route3_Text_SaxtonPostBattle, MSGBOX_AUTOCLOSE
	end
	
Route3_Little_Girl_Text:
	.string "Ooh your Pokémon is cute!$"

	
Route3_Teen_Girl_Text:
	.string "We're having a great walk away from\n"
	.string "the city.$"

Route3_House_Sign_Text:
	.string "Romani Household$"
