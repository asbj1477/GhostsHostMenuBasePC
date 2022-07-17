#include <Windows.h>
#include <iostream>
#include <vector>
#include <algorithm>
#include <detours.h>
#pragma comment(lib, "detours.lib")
#ifdef _WIN64
#define BitSize 0x08
#else
#define BitSize 0x04
#endif
#include "memory.h"
#include "Functions.h"
#include "Huds.h"
#include "Menu.h"