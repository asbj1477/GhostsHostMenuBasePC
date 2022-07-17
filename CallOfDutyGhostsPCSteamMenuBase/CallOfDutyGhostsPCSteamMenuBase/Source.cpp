#include "stdafx.h"

unsigned int client = 0;
unsigned __int64(__cdecl*ClientThink_real_stub)(DWORD *a1, __int64 a2, __int64 a3, __int64 a4, __int64 a5, __int64 a6, float a7, __int64 a8, __int64 a9, __int64 a10) = (unsigned __int64(__cdecl*)(DWORD *, __int64, __int64, __int64, __int64, __int64, float, __int64, __int64, __int64))(0x1403832E0);
unsigned __int64(ClientThink_real_hook)(DWORD *a1, __int64 a2, __int64 a3, __int64 a4, __int64 a5, __int64 a6, float a7, __int64 a8, __int64 a9, __int64 a10)
{
	if (isInGame)
	{
		StoreHuds(client);
		bool WaitOver = ((Sys_Milliseconds() - TickTime) < WaitTime) ? false : true;
		if (WaitOver)
		{
			if (Player_adsButtonPressed(client)&&Player_meleeButtonPressed(client))
			{
				ToggleMenu(client);
				Update(client);
			}
			else if (Player_attackButtonPressed(client))
			{
				if (isOpen)
				{
					if (Scroll == MaxScroll)
						Scroll = 1;
					else
						Scroll++;
					Update(client);
				}
			}
			else if (Player_adsButtonPressed(client))
			{
				if (isOpen)
				{
					if (Scroll == 1)
						Scroll = MaxScroll;
					else
						Scroll--;
					Update(client);
				}
			}
			else if (Player_meleeButtonPressed(client))
			{
				if (isOpen)
				{
					if (Menu == "Main Mods") { LoadSub(client, "Main Menu"); Scroll = 1; Update(client); }
					else if (Menu == "Sub Menu 2") { LoadSub(client, "Main Menu"); Scroll = 2; Update(client); }
					else if (Menu == "Sub Menu 3") { LoadSub(client, "Main Menu"); Scroll = 3; Update(client); }
					else if (Menu == "Sub Menu 4") { LoadSub(client, "Main Menu"); Scroll = 4; Update(client); }
					else if (Menu == "Sub Menu 5") { LoadSub(client, "Main Menu"); Scroll = 5; Update(client); }
					else if (Menu == "Sub Menu 6") { LoadSub(client, "Main Menu"); Scroll = 6; Update(client); }
					else if (Menu == "Sub Menu 7") { LoadSub(client, "Main Menu"); Scroll = 7; Update(client); }
					else if (Menu == "Sub Menu 8") { LoadSub(client, "Main Menu"); Scroll = 8; Update(client); }
					else { ToggleMenu(client); }
				}
			}
			else if (Player_jumpButtonPressed(client))
			{
				if (isOpen)
				{
					Toggle(client, Menu, Scroll);
					Update(client);
				}
			}
			wait(100);
		}
		// add loops below
		if (infammo)
			InfiniteAmmo(client);
	}
	return ClientThink_real_stub(a1, a2, a3,a4,a5,a6,a7,a8,a9,a10);
}

void IsInGameThread()
{
	for (;;)
	{
		if (read_process<int>(0x14427D73C) == 1)
			isInGame = true;
		else
		{
			isOpen = false;
			isDrawn = false;
			WaitTime = 0;
			TickTime = 0;
		}
		Sleep(100);
	}
}

BOOL WINAPI DllMain(HMODULE h, DWORD s, LPVOID b)
{
	if (s == DLL_PROCESS_ATTACH)
	{
		DisableThreadLibraryCalls(h);
		EraseHeaders(h);
		ErasePEHeader(h);
		UnlinkModuleFromPEB(h);
		CloseHandle(CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE)IsInGameThread, h, 0, nullptr));
		DetourTransactionBegin();
		DetourUpdateThread(GetCurrentThread());
		DetourAttach((PVOID*)(&ClientThink_real_stub), (PVOID)ClientThink_real_hook);
		DetourTransactionCommit();
		AllocConsole();
		freopen_s((FILE**)stdin, "CONIN$", "r", stdin);
		freopen_s((FILE**)stdout, "CONOUT$", "w", stdout);
		printf("Attached To Game\n");
	}
	return TRUE;
}