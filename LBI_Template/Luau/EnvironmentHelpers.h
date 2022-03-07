#pragma once

#define LUA_OK 0
#define LUA_ER 1

int lua_Print(lua_State* lua) {

	std::string a1 = lua_tostring(lua, 1);

	Log("Lua just printed something!");
	Log(a1.c_str());

	return 0;
}