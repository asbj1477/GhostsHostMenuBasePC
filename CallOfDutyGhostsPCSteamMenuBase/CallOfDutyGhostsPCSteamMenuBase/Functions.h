#define G_ENTITY(clientIndex) 0x14427A0E0 + (clientIndex * 0x2F0)
#define G_CLIENT(clientIndex) 0x1443F4600 + (clientIndex * 0x3A68)
#define Scr_GetMethod 0x1403CDB10
#define Scr_GetFunction 0x1403CD9F0
#define FPS_TEXT 0x14088C100

/*
base common_method pdb : 1404BF549
base common_method exe : 14086D450
*/

typedef DWORD _DWORD;
typedef __int64 _QWORD;

inline const char * const BoolToString(bool b, const char* tval, const char* fval)
{
	return b ? tval : fval;
}

void SV_GameSendServerCommand(int client, const char* command)
{
	RPC<void>(0x1404758C0, client, 0, command);
}

void iPrintln(int client, const char* msg) {
	char buf[100];
	snprintf(buf, 100, "f \"%s%s", msg, "\"");
	SV_GameSendServerCommand(client, buf);
}

bool Player_meleeButtonPressed(unsigned int Player)
{
	__int64 v1; // rbx
	__int64 v2; // rax
	int v3; // ecx
	__int64 result;
	v1 = G_ENTITY(Player);
	v2 = *((__int64 *)v1 + 47);
	if (v2)
		v3 = *(DWORD *)(v2 + 13236);
	else
		v3 = *(DWORD *)(*((__int64 *)v1 + 45) + 14020) | *(DWORD *)(*((__int64 *)v1 + 45) + 14032);
	if (v3 & 4)
		return true;
	else
		return false;
}

bool Player_attackButtonPressed(unsigned int Player)
{
	_QWORD v1 = G_ENTITY(Player); // rbx
	_QWORD v2 = *((_QWORD *)v1 + 47); // rax
	_DWORD v3; // ecx
	if (v2)
		v3 = *(_DWORD *)(v2 + 13236);
	else
		v3 = *(_DWORD *)(*((_QWORD *)v1 + 45) + 14020) | *(_DWORD *)(*((_QWORD *)v1 + 45) + 14032);
	if (v3 & 1)
		return true;
	else
		return false;
}

bool Player_adsButtonPressed(unsigned int Player)
{
	_QWORD v1 = G_ENTITY(Player); // rbx
	if ((*(_DWORD *)(*((_QWORD *)v1 + 45) + 14020) | *(_DWORD *)(*((_QWORD *)v1 + 45) + 14032)) & 2048)
		return true;
	else
		return false;
}

bool Player_jumpButtonPressed(unsigned int Player)
{
	__int64 v1; // rbx
	__int64 v2; // rax
	v1 = G_ENTITY(Player);
	v2 = *(_DWORD *)(*((_QWORD *)v1 + 45) + 14020) | *(_DWORD *)(*((_QWORD *)v1 + 45) + 14032);
	if (_bittest64(&v2, 0xAu))
		return true;
	else
		return false;
}

void iPrintlnBold(int client, const char* msg) {
	char buf[100];
	snprintf(buf, 100, "c \"%s%s", msg, "\"");
	SV_GameSendServerCommand(client, buf);
}

const char* visionlist[] = {
"default_mp",
"thermal_mp",
"default_night_mp",
"missilecam",
"ac130",
"ac130_enhanced",
"ac130_inverted",
"aftermath",
"black_bw",
"cheat_bw",
"coup_sunblind",
"default",
"default_night",
"default_night_mp",
"end_game",
"misslecam",
"mp_character_room",
"mp_fahrenheit",
"mp_fahrenheit_storm_exterior_dark",
"mp_flooded",
"mp_flooded_vision_set_cg_helo",
"mp_flooded_vision_set_cg_garage",
"mp_flooded_vision_set_cg_garage_water",
"mp_flooded_vision_set_cg_interior_ng",
"mp_flooded_vision_set_cg_ng",
"mp_frag",
"mp_hashima",
"mp_hashima_intiriors",
"mp_lonestar",
"mp_strikezone_bridge",
"mp_strikezone_flash",
"mp_strikezone_interior",
"mp_strikezone_stadium_bar",
"mp_warhawk",
"mp_warhawk_interior",
"pintro",
"pintro_dart",
"mpnuke",
"mpnuke_aftermath",
"mpoutro",
"near_death",
"near_death_mp",
"thermal_mp",
"thermal_snowlevel_mp"
};

void SetVision(int client, const char* vision) {
	char buf[100];
	snprintf(buf, 100, "J \"%s%s", vision, "\"");
	SV_GameSendServerCommand(client, buf);
}

bool god = false;
void GodMode(int client)
{
	if (god)
	{
		write_process<int>(0x14427A0E0 + 0x1DC, 100);
		iPrintlnBold(client, "God Mode : ^1OFF");
	}
	else
	{
		write_process<int>(0x14427A0E0 + 0x1DC, INT32_MAX);
		iPrintlnBold(client, "God Mode : ^2ON");
	}
	god = !god;
}
void Scr_SetNumParam(int A) {
	write_process<int>(0x144D4B0B8 + 4, A);
}

void Scr_ClearOutParams() {
	RPC<void>(0x140438600);
}

void Scr_AddString(const char * value) {
	RPC<void>(0x1404381D0, value);
}

void Scr_AddBool(int value) //use a scr_addint scr_addbool is not in the game
{
	RPC<void>(0x1404380F0, value);
}

void PlayerCMD_giveWeapon(unsigned int Player, const char * Weapon)
{
	Scr_AddString(Weapon);
	Scr_SetNumParam(1);
	RPC<void>(0x1403891F0, Player);
	Scr_ClearOutParams();
}

void PlayerCMD_switchToWeapon(unsigned int Player, const char * Weapon)
{
	Scr_AddString(Weapon);
	Scr_SetNumParam(1);
	RPC<void>(0x14038ADA0, Player);
	Scr_ClearOutParams();
}

void PlayerCMD_ClonePlayer(unsigned int Player)
{
	Scr_AddBool(1);
	Scr_SetNumParam(1);
	RPC<void>(0x140390890, Player);
	Scr_ClearOutParams();
}

const char* SL_ConvertToString(int value)
{
	return RPC<const char*>(0x1404317F0, value);
}

const char* PlayerCMD_getCurrentWeapon(unsigned int Player)
{
	return SL_ConvertToString(RPC<int>(0x140389D90, Player));
}

void PlayerCmd_giveMaxAmmo(unsigned int Player, const char* WeaponName)
{
	Scr_AddString(WeaponName);
	Scr_SetNumParam(1);
	RPC<__int64>(0x14038B690, Player);
	Scr_ClearOutParams();
}

void PlayerCmd_SetWeaponAmmoClip(unsigned int Player, const char* weapon, int value)
{
	Scr_AddBool(value);
	Scr_AddString(weapon);
	Scr_SetNumParam(2);
	RPC<_QWORD>(0x140388C40, Player);
	Scr_ClearOutParams();
}

int GScr_WeaponClipSize(unsigned int Player, const char* weapon)
{
	int index = RPC<int>(0x1403DA060, weapon); // G_GetWeaponForName
	return RPC<int>(0x14023E0D0, 0, index, 0); // BG_GetClipSize
}
bool infammo = false;
void InfiniteAmmo(unsigned int Player)
{
	const char* v1 = PlayerCMD_getCurrentWeapon(Player);
	PlayerCmd_SetWeaponAmmoClip(Player, v1, GScr_WeaponClipSize(Player,v1));
	PlayerCmd_giveMaxAmmo(Player, v1);
}

bool noclip = false;
void Noclip(unsigned int Player)
{
	__int64 result = *((__int64 *)G_ENTITY(Player) + 45);
	if (noclip)
	{
		*(DWORD *)(result + 14000) = 0x00;
		iPrintlnBold(Player, "Noclip : ^1OFF");
	}
	else
	{
		*(DWORD *)(result + 14000) = 0x02;
		iPrintlnBold(Player, "Noclip : ^2ON");
	}
	noclip = !noclip;
}

