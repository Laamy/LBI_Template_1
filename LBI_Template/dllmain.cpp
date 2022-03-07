#pragma region Imports

#include <windows.h>
#include <iostream>

extern "C" {
#include "Lua\lua.h"
#include "Lua\lua.hpp"
#include "Lua\lualib.h"
#include "Lua\lauxlib.h"
#include "Lua\luaconf.h"
#include "Lua\llimits.h"
}

const void Log(const char* str) {
    std::cout << str << std::endl;
}

// helper
#include "Luau/EnvironmentHelpers.h"

#pragma endregion

lua_State* lua;
FILE* fp;

void Init() { // learning how 2 make LBI's
    AllocConsole();
    freopen_s(&fp, "CONOUT$", "w", stdout);

    Log("Initalizing environment...");

    std::string script = "a = 7 + 11";

    lua = luaL_newstate();
    luaL_openlibs(lua);

    lua_register(lua, "Print", lua_Print);
    lua_register(lua, "print", lua_Print);

    int r = luaL_dofile(lua, "test.lua");
    if (r == LUA_ER) {
        std::string err = lua_tostring(lua, -1);
        Log(err.c_str());
    }

    lua_close(lua);
    // ignore error
}

BOOL APIENTRY DllMain(HMODULE a1, DWORD a2, LPVOID a3)
{
    if (a2 == DLL_PROCESS_ATTACH)
    {
        DisableThreadLibraryCalls(a1);
        CreateThread(0, 0, (LPTHREAD_START_ROUTINE)Init, 0, 0, 0);
    }
    return TRUE;
}