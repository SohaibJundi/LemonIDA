#include <windows.h>

typedef void(__fastcall* pullAllMetadata_ptr)(INT64*, INT64*, INT64*, INT64);
static pullAllMetadata_ptr pullAllMetadata;
static INT64* connection;

//init the plugin
static int __stdcall init(void)
{
    typedef INT64* (__fastcall* get_server_connection_ptr)();
    HMODULE handle = GetModuleHandle(TEXT("ida64.dll"));
    get_server_connection_ptr get_server_connection = (get_server_connection_ptr)GetProcAddress(handle, "get_server_connection");
    connection = get_server_connection();
    pullAllMetadata = *(pullAllMetadata_ptr*)(*connection + 32);

    return 2;
}

//cleanup on plugin unload
static void __stdcall term(void)
{

}

//called when user clicks in plugin menu or presses hotkey
static void __stdcall run(int arg)
{
    INT64 unk1[] = { 0, 0, 0 };
    INT64 unk2 = 0;
    pullAllMetadata(connection, unk1, &unk2, 1);
}

BOOL WINAPI DllMain(HINSTANCE hInstDll, DWORD dwReason, LPVOID lpReserved)
{
    return TRUE;
}


static char comment[] = "Calls lumina pull all metadata";
static char help[] = "LemonIDA";
static char name[] = "LemonIDA";
static char hotkey[] = "Shift-L";

typedef struct _plugin
{
    int version;
    int flags;
    int(__stdcall* init)(void);
    void(__stdcall* term)(void);
    void(__stdcall* run)(int arg);
    char* comment;
    char* help;
    char* name;
    char* hotkey;
} plugin;

extern __declspec(dllexport) plugin PLUGIN =
{
    700,
    0,
    init,
    term,
    run,
    comment,
    help,
    name,
    hotkey
};
