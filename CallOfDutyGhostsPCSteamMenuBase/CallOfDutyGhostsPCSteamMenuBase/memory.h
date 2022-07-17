typedef unsigned __int64 QWORD;
template<typename function_type, typename... Parameters>
function_type RPC(QWORD function_address, Parameters... args)
{
	function_type(*placeholder)(Parameters...) = (function_type(*)(Parameters...))function_address;
	return placeholder(args...);
}

template<typename function_type>
void write_process(QWORD Address, function_type Buffer)
{
	DWORD protect;
	VirtualProtect((LPVOID)Address, BitSize, PAGE_EXECUTE_READWRITE, &protect);
	memcpy((void*)Address, (void*)&Buffer, sizeof(Buffer));
	VirtualProtect((LPVOID)Address, BitSize, protect, &protect);
}

template<typename function_type>
function_type read_process(QWORD Address)
{
	DWORD protect;
	VirtualProtect((LPVOID)Address, BitSize, PAGE_EXECUTE_READ, &protect);
	function_type value = *(function_type*)Address;
	VirtualProtect((LPVOID)Address, BitSize, protect, &protect);
	return value;
}

QWORD get_pointer_address(QWORD startAddress, QWORD offsets[], int level)
{
	if (startAddress == -1)
		return -1;
	QWORD ptr = read_process<QWORD>(startAddress);
	for (int i = 0; i < level - 1; i++) {
		ptr += offsets[i];
		ptr = read_process<QWORD>(ptr);
	}
	ptr += offsets[level - 1];
	return ptr;
}

#pragma once


typedef struct _UNICODE_STRING {
	USHORT Length;
	USHORT MaximumLength;
	PWCH   Buffer;
} UNICODE_STRING;
typedef UNICODE_STRING *PUNICODE_STRING;

typedef struct _PEB_LDR_DATA {
	ULONG      Length;
	BOOLEAN    Initialized;
	PVOID      SsHandle;
	LIST_ENTRY InLoadOrderModuleList;
	LIST_ENTRY InMemoryOrderModuleList;
	LIST_ENTRY InInitializationOrderModuleList;
} PEB_LDR_DATA, *PPEB_LDR_DATA;


typedef struct _PEB {
#ifdef _WIN64
	UINT8 _PADDING_[24];
#else
	UINT8 _PADDING_[12];
#endif
	PEB_LDR_DATA* Ldr;
} PEB, *PPEB;
typedef struct _LDR_MODULE
{
	LIST_ENTRY      InLoadOrderModuleList;
	LIST_ENTRY      InMemoryOrderModuleList;
	LIST_ENTRY      InInitializationOrderModuleList;
	PVOID           BaseAddress;
	PVOID           EntryPoint;
	ULONG           SizeOfImage;
	UNICODE_STRING  FullDllName;
	UNICODE_STRING  BaseDllName;
	ULONG           Flags;
	SHORT           LoadCount;
	SHORT           TlsIndex;
	LIST_ENTRY      HashTableEntry;
	ULONG           TimeDateStamp;
} LDR_MODULE, *PLDR_MODULE;

typedef struct _UNLINKED_MODULE
{
	HMODULE hModule;
	PLIST_ENTRY RealInLoadOrderLinks;
	PLIST_ENTRY RealInMemoryOrderLinks;
	PLIST_ENTRY RealInInitializationOrderLinks;
	PLDR_MODULE Entry; 
} UNLINKED_MODULE;

#define UNLINK(x)					\
	(x).Flink->Blink = (x).Blink;	\
	(x).Blink->Flink = (x).Flink;

#define RELINK(x, real)			\
	(x).Flink->Blink = (real);	\
	(x).Blink->Flink = (real);	\
	(real)->Blink = (x).Blink;	\
	(real)->Flink = (x).Flink;

struct FindModuleHandle
{
	HMODULE m_hModule;
	FindModuleHandle(HMODULE hModule) : m_hModule(hModule)
	{
	}
	bool operator() (UNLINKED_MODULE const &Module) const
	{
		return (Module.hModule == m_hModule);
	}
};
std::vector<UNLINKED_MODULE> UnlinkedModules;
void UnlinkModuleFromPEB(HMODULE hModule)
{
	std::vector<UNLINKED_MODULE>::iterator it = std::find_if(UnlinkedModules.begin(), UnlinkedModules.end(), FindModuleHandle(hModule));
	if (it != UnlinkedModules.end())
	{
		return;
	}

#ifdef _WIN64
	PPEB pPEB = (PPEB)__readgsqword(0x60);
#else
	PPEB pPEB = (PPEB)__readfsdword(0x30);
#endif
	PLIST_ENTRY CurrentEntry = pPEB->Ldr->InLoadOrderModuleList.Flink;
	PLDR_MODULE Current = NULL;
	while (CurrentEntry != &pPEB->Ldr->InLoadOrderModuleList && CurrentEntry != NULL)
	{
		Current = CONTAINING_RECORD(CurrentEntry, LDR_MODULE, InLoadOrderModuleList);
		if (Current->BaseAddress == hModule)
		{
			UNLINKED_MODULE CurrentModule = { 0 };
			CurrentModule.hModule = hModule;
			CurrentModule.RealInLoadOrderLinks = Current->InLoadOrderModuleList.Blink->Flink;
			CurrentModule.RealInInitializationOrderLinks = Current->InInitializationOrderModuleList.Blink->Flink;
			CurrentModule.RealInMemoryOrderLinks = Current->InMemoryOrderModuleList.Blink->Flink;
			CurrentModule.Entry = Current;
			UnlinkedModules.push_back(CurrentModule);

			UNLINK(Current->InLoadOrderModuleList);
			UNLINK(Current->InInitializationOrderModuleList);
			UNLINK(Current->InMemoryOrderModuleList);

			break;
		}

		CurrentEntry = CurrentEntry->Flink;
	}
}

void EraseHeaders(HINSTANCE hModule)
{
	PIMAGE_DOS_HEADER pDoH;
	PIMAGE_NT_HEADERS pNtH;
	DWORD i, ersize, protect;
	if (!hModule) return;
	pDoH = (PIMAGE_DOS_HEADER)(hModule);
	pNtH = (PIMAGE_NT_HEADERS)((LONG)hModule + ((PIMAGE_DOS_HEADER)hModule)->e_lfanew);
	ersize = sizeof(IMAGE_DOS_HEADER);
	if (VirtualProtect(pDoH, ersize, PAGE_READWRITE, &protect))
	{
		for (i = 0; i < ersize; i++)
			*(BYTE*)((BYTE*)pDoH + i) = 0;
	}
	ersize = sizeof(IMAGE_NT_HEADERS);
	if (pNtH && VirtualProtect(pNtH, ersize, PAGE_READWRITE, &protect))
	{
		for (i = 0; i < ersize; i++)
			*(BYTE*)((BYTE*)pNtH + i) = 0;
	}
	return;
}

void ErasePEHeader(HINSTANCE hModule)
{
	MEMORY_BASIC_INFORMATION mbi;
	VirtualQuery((LPCVOID)hModule, &mbi, sizeof(mbi));
	VirtualProtect(mbi.BaseAddress, mbi.RegionSize, PAGE_EXECUTE_READWRITE, &mbi.Protect);
	ZeroMemory((PVOID)hModule, 4096);
	VirtualProtect(mbi.BaseAddress, mbi.RegionSize, mbi.Protect, NULL);
	FlushInstructionCache(GetCurrentProcess(), (LPCVOID)mbi.BaseAddress, mbi.RegionSize);
}