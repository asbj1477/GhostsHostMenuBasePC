typedef unsigned char byte;
typedef unsigned int uint;

union color_s
{
	struct
	{
		byte r, g, b, a;
	};

	uint rgba;
};

struct hudelem_s
{
	int type;
	float x;
	float y;
	float z;
	int targetEntNum;
	float fontScale;
	float fromFontScale;
	float fontScaleStartTime;
	float fontScaleTime;
	int font;
	int alignOrg;
	int alignScreen;
	color_s color;
	color_s fromColor;
	int fadeStartTime;
	int fadeTime;
	int label;
	int width;
	int height;
	int materialIndex;
	int fromWidth;
	int fromHeight;
	int scaleStartTime;
	int scaleTime;
	float fromX;
	float fromY;
	int fromAlignOrg;
	int fromAlignScreen;
	int moveStartTime;
	int moveTime;
	int time;
	int duration;
	float value;
	int text;
	float sort;
	color_s glowColor;
	int fxBirthTime;
	int fxLetterTime;
	int fxDecayStartTime;
	int fxDecayDuration;
	int soundID;
	int flags;
};

struct game_hudelem_s
{
	hudelem_s elem;
	int clientNum;
	int team;
	int archived;
	int currentShowInKillcam;
};

int(*G_MaterialIndex)(const char* shader) = (int(*)(const char*))0x140162320;

int(*G_FindConfigstringIndex)(const char* name, int start, int max, int create, const char* error) = (int(*)(const char*, int, int, int, const char*))0x140161F90;

game_hudelem_s*(*HudElem_Alloc)(int client, int team) = (game_hudelem_s*(*)(int, int))0x1403997E0;

game_hudelem_s* setText(int client, char* Text, int font, float fontScale, float x, float y, byte r, byte g, byte b, byte a)
{
	game_hudelem_s* Element = HudElem_Alloc(client, 0);
	Element->elem.type = 0x1;
	Element->elem.alignOrg = 0;
	Element->elem.alignScreen = 0;
	Element->elem.font = font;
	Element->elem.fontScale = fontScale;
	Element->elem.x = x;
	Element->elem.y = y;
	Element->elem.color.r = r;
	Element->elem.color.g = g;
	Element->elem.color.b = b;
	Element->elem.color.a = a;
	Element->elem.sort = 1;
	Element->elem.text = G_FindConfigstringIndex(Text, 0x21D, 0x1FF, 1, "localized string");
	return Element;
}

game_hudelem_s* AddShader(int client, char* Shader, float x, float y, int width, int height, byte r, byte g, byte b, byte a)
{
	game_hudelem_s* element = HudElem_Alloc(client, 0);
	element->elem.type = 0x04;
	element->elem.materialIndex = G_MaterialIndex(Shader);
	element->elem.x = x;
	element->elem.y = y;
	element->elem.width = width;
	element->elem.height = height;
	element->elem.alignOrg = 0;
	element->elem.alignScreen = 0;
	element->elem.sort = 0;
	element->elem.color.r = r;
	element->elem.color.g = g;
	element->elem.color.b = b;
	element->elem.color.a = a;
	return element;
}

void ChangeGlow(game_hudelem_s* element, byte r, byte g, byte b, byte a)
{
	element->elem.glowColor.r = r;
	element->elem.glowColor.g = g;
	element->elem.glowColor.b = b;
	element->elem.glowColor.a = a;
}

void ChangeColor(game_hudelem_s* element, byte r, byte g, byte b, byte a)
{
	element->elem.color.r = r;
	element->elem.color.g = g;
	element->elem.color.b = b;
	element->elem.color.a = a;
}

void ChangeFontScale(game_hudelem_s* element, float Scale)
{
	element->elem.fontScale = Scale;
}

void ChangeText(game_hudelem_s* element, const char* Text)
{
	element->elem.text = G_FindConfigstringIndex(Text, 0x21D, 0x1FF, 1, "localized string");
}

void ChangeMaterial(game_hudelem_s* element, const char* material)
{
	element->elem.materialIndex = G_MaterialIndex(material);
}

void MoveXY(game_hudelem_s* element, float x, float y)
{
	element->elem.x = x;
	element->elem.y = y;
}