#include <stdio.h>
#include <string.h>
#include "lua.h"
#include "lauxlib.h"
#include "lualib.h"



int main(void)
{
  int status;
  lua_State *L = luaL_newstate();
	if(L == NULL)
		return 1;
  luaL_openlibs(L);
	status = luaL_loadstring(L, "print(\"test\")") || lua_pcall(L, 0, 0, 0);
	if (status)
	{
		fprintf(stderr, "%s\n", lua_tostring(L, -1));
		lua_pop(L, 1);
	}
	status = luaL_loadfile(L, "c.lua") | lua_pcall(L, 0, 0, 0);
	if (status)
	{
		fprintf(stderr, "%s\n", lua_tostring(L, -1));
		lua_pop(L, 1);
	}
	//luaL_dofile(L, "c.lua");

  lua_close(L);

	return 0;
}
