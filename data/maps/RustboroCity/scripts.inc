.set LOCALID_LITTLE_BOY, 7
.set LOCALID_LITTLE_GIRL, 8
.set LOCALID_DEVON_EMPLOYEE, 9
.set LOCALID_GRUNT, 10
.set LOCALID_RIVAL, 14
.set LOCALID_SCIENTIST, 15

RustboroCity_MapScripts:: @ 81E06BD
	map_script MAP_SCRIPT_ON_TRANSITION, RustboroCity_OnTransition
	.byte 0

RustboroCity_OnTransition: @ 81E06C8
	setflag FLAG_VISITED_RUSTBORO_CITY
	call Common_EventScript_SetupRivalGfxId
	compare VAR_RUSTBORO_CITY_STATE, 6
	end

SarinCity_HerbShop_Mailbox::
	msgbox SarinCity_HerbShop_Mailbox_Text, MSGBOX_DEFAULT
	closemessage
	end
	
SarinCity_HerbShop_Mailbox_Text:
	.string "Sarin City: Herb & Berry Shop$"
