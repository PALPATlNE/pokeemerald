Route2_House_1F_MapScripts::
	.byte 0

Route2_House_Old_Lady::
	faceplayer
	msgbox Route2_House_Old_Lady_Text, MSGBOX_NPC
	closemessage
	fadescreen FADE_TO_BLACK
	special HealPlayerParty
	playfanfare MUS_HEAL
	waitfanfare
	fadescreen FADE_FROM_BLACK
	msgbox Route2_House_Old_Lady_Text2, MSGBOX_NPC
	end

Route2_House_Old_Lady_Text:
	.string "Oh hello sweetie!\p"
	.string "You look so tired!\n"
	.string "Here get some rest$"
	
Route2_House_Old_Lady_Text2:	
	.string "There you go, now back into the wide\n"
	.string "world!$"
