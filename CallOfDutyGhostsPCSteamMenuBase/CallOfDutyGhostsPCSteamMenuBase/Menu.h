bool isDrawn, isInGame, isOpen;
int MaxScroll, Scroll = 1;
const char* Menu = "";
__int64 TickTime, WaitTime;

game_hudelem_s* Options[9];
game_hudelem_s* Background;
game_hudelem_s* Title;
game_hudelem_s* SubMenu;
game_hudelem_s* leftline;
game_hudelem_s* rightline;
game_hudelem_s* topline;
game_hudelem_s* bottomline;

__int64 Sys_Milliseconds()
{
	return RPC<__int64>(0x140501CA0);
}

void wait(int milliseconds)
{
	TickTime = Sys_Milliseconds();
	WaitTime = milliseconds;
}

void StoreHuds(int client)
{
	if (!isDrawn)
	{
		Background = AddShader(client, "white", 450, -1000, 180, 250, 0, 0, 0, 180);
		leftline = AddShader(client, "white", 450, -1000, 2, 250, 0, 0, 255, 255);
		rightline = AddShader(client, "white", 450, -1000, 2, 250, 0, 0, 255, 255);
		topline = AddShader(client, "white", 450, -1000, 180, 2, 0, 0, 255, 255);
		bottomline = AddShader(client, "white", 450, -1000, 183, 2, 0, 0, 255, 255);
		Title = setText(client, "Ghosts PC", 3, 2.5, 540, -1000, 255, 255, 255, 255); ChangeGlow(Title, 0, 0, 255, 255);
		SubMenu = setText(client, "", 3, 1.8, 540, -1000, 255, 255, 255, 255); ChangeGlow(SubMenu, 0, 0, 255, 255);
		Options[1] = setText(client, "Main Mods", 3, 1, 540, -1000, 255, 255, 255, 255);
		Options[2] = setText(client, "Sub Menu 2", 3, 1, 540, -1000, 255, 255, 255, 255);
		Options[3] = setText(client, "Sub Menu 3", 3, 1, 540, -1000, 255, 255, 255, 255);
		Options[4] = setText(client, "Sub Menu 4", 3, 1, 540, -1000, 255, 255, 255, 255);
		Options[5] = setText(client, "Sub Menu 5", 3, 1, 540, -1000, 255, 255, 255, 255);
		Options[6] = setText(client, "Sub Menu 6", 3, 1, 540, -1000, 255, 255, 255, 255);
		Options[7] = setText(client, "Sub Menu 7", 3, 1, 540, -1000, 255, 255, 255, 255);
		Options[8] = setText(client, "Sub Menu 8", 3, 1, 540, -1000, 255, 255, 255, 255);
		isDrawn = true;
		printf("Huds Allocated\nControls Are : \nOpen Menu : ADS + Melee\nExit : Melee\nSelect : Jump\nScroll : Attack & ADS\n");
	}
}

void LoadSub(int client, const char* Sub)
{
	if (Sub == "Main Menu")
	{
		Scroll = 1;
		MaxScroll = 8;
		Menu = Sub;
		ChangeText(Options[1], "Main Mods");
		ChangeText(Options[2], "Sub Menu 2");
		ChangeText(Options[3], "Sub Menu 3");
		ChangeText(Options[4], "Sub Menu 4");
		ChangeText(Options[5], "Sub Menu 5");
		ChangeText(Options[6], "Sub Menu 6");
		ChangeText(Options[7], "Sub Menu 7");
		ChangeText(Options[8], "Sub Menu 8");
	}
	else if (Sub == "Main Mods")
	{
		Scroll = 1;
		MaxScroll = 8;
		Menu = Sub;
		ChangeText(Options[1], "God Mode");
		ChangeText(Options[2], "Give Ak12");
		ChangeText(Options[3], "Clone Yourself");
		ChangeText(Options[4], "Noclip");
		ChangeText(Options[5], "Toggle Infinite Ammo");
		ChangeText(Options[6], "Option 6");
		ChangeText(Options[7], "Option 7");
		ChangeText(Options[8], "Option 8");
	}
	else if (Sub == "Sub Menu 2")
	{
		Scroll = 1;
		MaxScroll = 8;
		Menu = Sub;
		ChangeText(Options[1], "Option 1");
		ChangeText(Options[2], "Option 2");
		ChangeText(Options[3], "Option 3");
		ChangeText(Options[4], "Option 4");
		ChangeText(Options[5], "Option 5");
		ChangeText(Options[6], "Option 6");
		ChangeText(Options[7], "Option 7");
		ChangeText(Options[8], "Option 8");
	}
	else if (Sub == "Sub Menu 3")
	{
		Scroll = 1;
		MaxScroll = 8;
		Menu = Sub;
		ChangeText(Options[1], "Option 1");
		ChangeText(Options[2], "Option 2");
		ChangeText(Options[3], "Option 3");
		ChangeText(Options[4], "Option 4");
		ChangeText(Options[5], "Option 5");
		ChangeText(Options[6], "Option 6");
		ChangeText(Options[7], "Option 7");
		ChangeText(Options[8], "Option 8");
	}
	else if (Sub == "Sub Menu 4")
	{
		Scroll = 1;
		MaxScroll = 8;
		Menu = Sub;
		ChangeText(Options[1], "Option 1");
		ChangeText(Options[2], "Option 2");
		ChangeText(Options[3], "Option 3");
		ChangeText(Options[4], "Option 4");
		ChangeText(Options[5], "Option 5");
		ChangeText(Options[6], "Option 6");
		ChangeText(Options[7], "Option 7");
		ChangeText(Options[8], "Option 8");
	}
	else if (Sub == "Sub Menu 5")
	{
		Scroll = 1;
		MaxScroll = 8;
		Menu = Sub;
		ChangeText(Options[1], "Option 1");
		ChangeText(Options[2], "Option 2");
		ChangeText(Options[3], "Option 3");
		ChangeText(Options[4], "Option 4");
		ChangeText(Options[5], "Option 5");
		ChangeText(Options[6], "Option 6");
		ChangeText(Options[7], "Option 7");
		ChangeText(Options[8], "Option 8");
	}
	else if (Sub == "Sub Menu 6")
	{
		Scroll = 1;
		MaxScroll = 8;
		Menu = Sub;
		ChangeText(Options[1], "Option 1");
		ChangeText(Options[2], "Option 2");
		ChangeText(Options[3], "Option 3");
		ChangeText(Options[4], "Option 4");
		ChangeText(Options[5], "Option 5");
		ChangeText(Options[6], "Option 6");
		ChangeText(Options[7], "Option 7");
		ChangeText(Options[8], "Option 8");
	}
	else if (Sub == "Sub Menu 7")
	{
		Scroll = 1;
		MaxScroll = 8;
		Menu = Sub;
		ChangeText(Options[1], "Option 1");
		ChangeText(Options[2], "Option 2");
		ChangeText(Options[3], "Option 3");
		ChangeText(Options[4], "Option 4");
		ChangeText(Options[5], "Option 5");
		ChangeText(Options[6], "Option 6");
		ChangeText(Options[7], "Option 7");
		ChangeText(Options[8], "Option 8");
	}
	else if (Sub == "Sub Menu 8")
	{
		Scroll = 1;
		MaxScroll = 8;
		Menu = Sub;
		ChangeText(Options[1], "Option 1");
		ChangeText(Options[2], "Option 2");
		ChangeText(Options[3], "Option 3");
		ChangeText(Options[4], "Option 4");
		ChangeText(Options[5], "Option 5");
		ChangeText(Options[6], "Option 6");
		ChangeText(Options[7], "Option 7");
		ChangeText(Options[8], "Option 8");
	}
}

void Toggle(int i, const char* Sub, int scroll)
{
	if (Sub == "Main Menu")
	{
		if (scroll == 1) LoadSub(i, "Main Mods");
		else if (scroll == 2) LoadSub(i, "Sub Menu 2");
		else if (scroll == 3) LoadSub(i, "Sub Menu 3");
		else if (scroll == 4) LoadSub(i, "Sub Menu 4");
		else if (scroll == 5) LoadSub(i, "Sub Menu 5");
		else if (scroll == 6) LoadSub(i, "Sub Menu 6");
		else if (scroll == 7) LoadSub(i, "Sub Menu 7");
		else if (scroll == 8) LoadSub(i, "Sub Menu 8");
	}
	else if (Sub == "Main Mods")
	{
		if (scroll == 1) GodMode(i);
		else if (scroll == 2) { 
			PlayerCMD_giveWeapon(i, "iw6_ak12_mp");	
			PlayerCMD_switchToWeapon(i, "iw6_ak12_mp"); 
			iPrintln(i, "^5Ak12 Given!"); 
		}
		else if (scroll == 3) PlayerCMD_ClonePlayer(i);
		else if (scroll == 4) Noclip(i);
		else if (scroll == 5) {
				infammo = !infammo;
				iPrintlnBold(i, BoolToString(infammo,"Infinite Ammo : ^2ON", "Infinite Ammo : ^1OFF"));
				
		}
		else if (scroll == 6) iPrintlnBold(i, "^5Main Mods: ^5Option 6");
		else if (scroll == 7) iPrintlnBold(i, "^5Main Mods: ^5Option 7");
		else if (scroll == 8) iPrintlnBold(i, "^5Main Mods: ^5Option 8");
	}
	else if (Sub == "Sub Menu 2")
	{
		if (scroll == 1) iPrintlnBold(i, "^5Sub Menu 2: ^5Option 1");
		else if (scroll == 2) iPrintlnBold(i, "^5Sub Menu 2: ^5Option 2");
		else if (scroll == 3) iPrintlnBold(i, "^5Sub Menu 2: ^5Option 3");
		else if (scroll == 4) iPrintlnBold(i, "^5Sub Menu 2: ^5Option 4");
		else if (scroll == 5) iPrintlnBold(i, "^5Sub Menu 2: ^5Option 5");
		else if (scroll == 6) iPrintlnBold(i, "^5Sub Menu 2: ^5Option 6");
		else if (scroll == 7) iPrintlnBold(i, "^5Sub Menu 2: ^5Option 7");
		else if (scroll == 8) iPrintlnBold(i, "^5Sub Menu 2: ^5Option 8");
	}
	else if (Sub == "Sub Menu 3")
	{
		if (scroll == 1) iPrintlnBold(i, "^5Sub Menu 3: ^5Option 1");
		else if (scroll == 2) iPrintlnBold(i, "^5Sub Menu 3: ^5Option 2");
		else if (scroll == 3) iPrintlnBold(i, "^5Sub Menu 3: ^5Option 3");
		else if (scroll == 4) iPrintlnBold(i, "^5Sub Menu 3: ^5Option 4");
		else if (scroll == 5) iPrintlnBold(i, "^5Sub Menu 3: ^5Option 5");
		else if (scroll == 6) iPrintlnBold(i, "^5Sub Menu 3: ^5Option 6");
		else if (scroll == 7) iPrintlnBold(i, "^5Sub Menu 3: ^5Option 7");
		else if (scroll == 8) iPrintlnBold(i, "^5Sub Menu 3: ^5Option 8");
	}
	else if (Sub == "Sub Menu 4")
	{
		if (scroll == 1) iPrintlnBold(i, "^5Sub Menu 4: ^5Option 1");
		if (scroll == 2) iPrintlnBold(i, "^5Sub Menu 4: ^5Option 2");
		if (scroll == 3) iPrintlnBold(i, "^5Sub Menu 4: ^5Option 3");
		if (scroll == 4) iPrintlnBold(i, "^5Sub Menu 4: ^5Option 4");
		if (scroll == 5) iPrintlnBold(i, "^5Sub Menu 4: ^5Option 5");
		if (scroll == 6) iPrintlnBold(i, "^5Sub Menu 4: ^5Option 6");
		if (scroll == 7) iPrintlnBold(i, "^5Sub Menu 4: ^5Option 7");
		if (scroll == 8) iPrintlnBold(i, "^5Sub Menu 4: ^5Option 8");
	}
	else if (Sub == "Sub Menu 5")
	{
		if (scroll == 1) iPrintlnBold(i, "^5Sub Menu 5: ^5Option 1");
		else if (scroll == 2) iPrintlnBold(i, "^5Sub Menu 5: ^5Option 2");
		else if (scroll == 3) iPrintlnBold(i, "^5Sub Menu 5: ^5Option 3");
		else if (scroll == 4) iPrintlnBold(i, "^5Sub Menu 5: ^5Option 4");
		else if (scroll == 5) iPrintlnBold(i, "^5Sub Menu 5: ^5Option 5");
		else if (scroll == 6) iPrintlnBold(i, "^5Sub Menu 5: ^5Option 6");
		else if (scroll == 7) iPrintlnBold(i, "^5Sub Menu 5: ^5Option 7");
		else if (scroll == 8) iPrintlnBold(i, "^5Sub Menu 5: ^5Option 8");
	}
	else if (Sub == "Sub Menu 6")
	{
		if (scroll == 1) iPrintlnBold(i, "^5Sub Menu 6: ^5Option 1");
		else if (scroll == 2) iPrintlnBold(i, "^5Sub Menu 6: ^5Option 2");
		else if (scroll == 3) iPrintlnBold(i, "^5Sub Menu 6: ^5Option 3");
		else if (scroll == 4) iPrintlnBold(i, "^5Sub Menu 6: ^5Option 4");
		else if (scroll == 5) iPrintlnBold(i, "^5Sub Menu 6: ^5Option 5");
		else if (scroll == 6) iPrintlnBold(i, "^5Sub Menu 6: ^5Option 6");
		else if (scroll == 7) iPrintlnBold(i, "^5Sub Menu 6: ^5Option 7");
		else if (scroll == 8) iPrintlnBold(i, "^5Sub Menu 6: ^5Option 8");
	}
	else if (Sub == "Sub Menu 7")
	{
		if (scroll == 1) iPrintlnBold(i, "^5Sub Menu 7: ^5Option 1");
		else if (scroll == 2) iPrintlnBold(i, "^5Sub Menu 7: ^5Option 2");
		else if (scroll == 3) iPrintlnBold(i, "^5Sub Menu 7: ^5Option 3");
		else if (scroll == 4) iPrintlnBold(i, "^5Sub Menu 7: ^5Option 4");
		else if (scroll == 5) iPrintlnBold(i, "^5Sub Menu 7: ^5Option 5");
		else if (scroll == 6) iPrintlnBold(i, "^5Sub Menu 7: ^5Option 6");
		else if (scroll == 7) iPrintlnBold(i, "^5Sub Menu 7: ^5Option 7");
		else if (scroll == 8) iPrintlnBold(i, "^5Sub Menu 7: ^5Option 8");
	}
	else if (Sub == "Sub Menu 8")
	{
		if (scroll == 1) iPrintlnBold(i, "^5Sub Menu 8: ^5Option 1");
		else if (scroll == 2) iPrintlnBold(i, "^5Sub Menu 8: ^5Option 2");
		else if (scroll == 3) iPrintlnBold(i, "^5Sub Menu 8: ^5Option 3");
		else if (scroll == 4) iPrintlnBold(i, "^5Sub Menu 8: ^5Option 4");
		else if (scroll == 5) iPrintlnBold(i, "^5Sub Menu 8: ^5Option 5");
		else if (scroll == 6) iPrintlnBold(i, "^5Sub Menu 8: ^5Option 6");
		else if (scroll == 7) iPrintlnBold(i, "^5Sub Menu 8: ^5Option 7");
		else if (scroll == 8) iPrintlnBold(i, "^5Sub Menu 8: ^5Option 8");
	}
}

void ToggleMenu(int client)
{
	if (!isOpen)
	{
		LoadSub(client, "Main Menu");
		MoveXY(Background, 370, 100);
		MoveXY(leftline, 370-2, 100);
		MoveXY(topline, 370, 100);
		MoveXY(rightline, (370 + 180)-1, 100);
		MoveXY(bottomline, 370-2, 100+250);
		MoveXY(Title, 415, 110);
		MoveXY(SubMenu, 415, 35+110);
		MoveXY(Options[1], 430, 110 + 70);
		MoveXY(Options[2], 430, 130 + 70);
		MoveXY(Options[3], 430, 150 + 70);
		MoveXY(Options[4], 430, 170 + 70);
		MoveXY(Options[5], 430, 190 + 70);
		MoveXY(Options[6], 430, 210 + 70);
		MoveXY(Options[7], 430, 230 + 70);
		MoveXY(Options[8], 430, 250 + 70);
		isOpen = true;
	}
	else
	{
		MoveXY(Title, -1000, 550);
		MoveXY(SubMenu, -1000,550);
		MoveXY(Background, -1000, 550);
		MoveXY(leftline, -1000, 550);
		MoveXY(rightline, -1000, 550);
		MoveXY(topline, -1000, 550);
		MoveXY(bottomline, -1000, 550);
		MoveXY(Options[1], -1000, 550);
		MoveXY(Options[2], -1000, 550);
		MoveXY(Options[3], -1000, 550);
		MoveXY(Options[4], -1000, 550);
		MoveXY(Options[5], -1000, 550);
		MoveXY(Options[6], -1000, 550);
		MoveXY(Options[7], -1000, 550);
		MoveXY(Options[8], -100, 550);
		isOpen = false;
	}
}

void Update(int client)
{
	for (int i = 1; i < 9; i++)
	{
		ChangeColor(Options[i], 255, 255, 255, 170);
		ChangeFontScale(Options[i], 1);
	}
	ChangeColor(Options[Scroll], 0, 0, 255, 255);
	ChangeFontScale(Options[Scroll], 1.2);
	ChangeText(SubMenu, Menu);
}