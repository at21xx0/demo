#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lua.h"
#include "lauxlib.h"
#include "lualib.h"

static int l_test(lua_State *L)
{
	printf("test\n");
	return 0;
}



static int l_testType(lua_State *L)
{
	lua_Number m;
	//lua_Integer n;
	size_t len;
	int i;
	int n;
	n = lua_gettop(L);
	// BOOL NUM STR FUN TAB
	luaL_checktype(L, 1, LUA_TBOOLEAN);
	luaL_checktype(L, 2, LUA_TNUMBER);
	luaL_checktype(L, 3, LUA_TSTRING);
	luaL_checktype(L, 4, LUA_TFUNCTION);
	luaL_checktype(L, 5, LUA_TTABLE);
	luaL_checkany(L, 5);
	//luaL_checktype(L, 6, LUA_TUSERDATA);
	putc('\n', stdout);
	for(i = 1;i <= n;++i)
		printf("arg[%d]: %s\n", i, lua_typename(L, lua_type(L, i)));
	printf("boolean: %d\n", lua_toboolean(L, 1));
	if(lua_isinteger(L, 2))
		printf("number: %lld\n", lua_tointeger(L, 2));
	else
	{
		m = lua_tonumber(L, 2);
		printf("number: %g\n", m);
	}
	printf("str: %s\n", lua_tolstring(L, 3, &len));

	if(!lua_checkstack(L, 2))
	{
		lua_pushliteral(L, "error1");
		lua_error(L);
	}

	lua_pushvalue(L, 4); // ... FUN
	lua_pushvalue(L, 2); // ... FUN NUM
	lua_call(L, 1, 1); // ... FUN(NUM)

	//lua_pushnil(L);
	//lua_pushboolean(L, 1);
	//lua_pushinteger(L, 4);
	//lua_pushlstring(L, "[str]", 5);
	lua_pushstring(L, "[str]");
	return 2; // ... FUN(NUM) "[str]"
}
static int printType(lua_State *L)
{
	int i;
	int n;
	n = lua_gettop(L);
	for(i = 1;i <= n;++i)
		printf("%s ", lua_typename(L, lua_type(L, i)));
	putc('\n',stdout);
	return 0;
}
static int l_testStack(lua_State *L)
{
	luaL_checktype(L, 1, LUA_TNUMBER);
	luaL_checktype(L, 2, LUA_TBOOLEAN);
	luaL_checktype(L, 3, LUA_TNIL);
	/* NUM BOOL NIL
	 * 1 2 3
	 * -3 -2 -1 */
	printType(L);
	lua_pushvalue(L, 1); // NUM BOOL NIL NUM
	printType(L);
	lua_settop(L, 5); // NUM BOOL NIL NUM NIL
	// lua_gettop(L); // 5
	printType(L);
	lua_replace(L, 4); // NUM BOOL NIL NIL
	printType(L);
	lua_rotate(L, 2, 1); // NUM NIL BOOL NIL // BOOL >>>> 1
	printType(L);
	lua_rotate(L, -2, 1); // NUM NIL NIL BOOL // BOOL >>>> 1
	printType(L);
	lua_remove(L, -1); // NUM NIL NIL 
	printType(L);
	lua_pop(L, 1); // NUM NIL
	printType(L);
	lua_copy(L, 1, 2);
	printType(L);
	return 0;

}
static int l_testVar(lua_State *L)
{
	char *name;
	luaL_checktype(L, 1, LUA_TSTRING);
	luaL_checktype(L, 2, LUA_TSTRING);
	name = (char *)lua_tostring(L, 1); // STR1 STR2
	lua_getglobal(L, name); // STR1 STR2 NUM 
	name = (char *)lua_tostring(L, 2);
	lua_setglobal(L, name);
	return 0;
}
//static int l_testPrint
static int l_testTable(lua_State *L)
{
	// TAB
	luaL_checktype(L, 1, LUA_TTABLE);

	lua_getglobal(L, "print");
	lua_pushvalue(L, 1);
	lua_call(L, 1, 0);

	// TAB
	// lua_cretetable(L, 2, 0);
	lua_newtable(L); // TAB TAB2
	lua_getfield(L, 1, "i"); // TAB TAB2 TAB["i"]
	lua_geti(L, 1, 1); // TAB TAB2 TAB["i"] TAB[1]
	//printf("%lld\n", lua_tointeger(L, 4));
	lua_seti(L, 2, 1); // TAB TAB2 TAB["i"]
	lua_setfield(L, 2, "i"); // TAB TAB2
	lua_pushinteger(L, 2); // TAB TAB2 NUM
	lua_pushinteger(L, 2); // TAB TAB2 NUM NUM2
	lua_gettable(L, 1); // TAB TAB2 NUM TAB[NUM2]
	lua_settable(L, 2); // TAB TAB // TAB2[2] = TAB[2]
	// lua_rawset = lua_settable , no __newindex
	// ... lua_rawseti lua_rawget lua_rawgeti
	return 1;
}
static int l_testFunction(lua_State *L)
{
	luaL_checktype(L, 1, LUA_TFUNCTION);
	lua_pushinteger(L, 5);
	lua_pushinteger(L, 8);
	if(lua_pcall(L, 2, 1, 0) != LUA_OK) // lua_call(L, 2, 1);
	{
		printf("%s\n", lua_tostring(L, -1));
	}
	if(lua_isinteger(L, -1))
		printf("%lld\n", lua_tointeger(L, -1));
	lua_pushcfunction(L, &l_test);
	return 1;
}

static int l_testString(lua_State *L)
{
	char *s;
	char *m;
	luaL_Buffer b;
	size_t l;
	
	s = (char *)luaL_checklstring(L, 1, &l);
	m = luaL_buffinitsize(L, &b, l);
	strncpy(m, s, l);
	luaL_pushresultsize(&b, l); // STR STR2
	luaL_buffinit(L, &b); // init
	lua_pushstring(L, "[STR]");
	luaL_addvalue(&b);
	luaL_addlstring(&b, "[Str]", 5);
	luaL_addstring(&b, "[str]");
	luaL_addchar(&b, '\t');
	luaL_pushresult(&b);
	return 1;
}

#define TEST_BITMAP


#ifdef TEST_BITMAP
typedef struct BitMap_t
{
	size_t size;
	uint32_t bits[1];
}BitMap_t;

static int l_newBitMap(lua_State *L)
{
	size_t size;
	BitMap_t *n;
	luaL_checktype(L, 1, LUA_TNUMBER);
	if(!lua_isinteger(L, 1))
	{
		lua_pushnil(L);
		return 1;
	}
	size = (size_t)lua_tointeger(L, 1) + 1;
	n = (BitMap_t *)lua_newuserdata(L, (size >> 5) * sizeof(uint32_t) + sizeof(uint32_t) + sizeof(BitMap_t));
	n->size = size;
	for(size >>= 5;size != 0;--size, n->bits[size] = 0);
	luaL_getmetatable(L, "BitMap");
  lua_setmetatable(L, -2);
	return 1;
}

static int l_bitMap_len(lua_State *L)
{
	BitMap_t *n = (BitMap_t *)luaL_checkudata(L, 1, "BitMap");
	lua_pushinteger(L, n->size - 1);
	return 1;
}

static int l_bitMap_newindex(lua_State *L)
{
	size_t i;
	BitMap_t *n = (BitMap_t *)luaL_checkudata(L, 1, "BitMap");
	i = luaL_checkinteger(L, 2);
	luaL_checktype(L, 3, LUA_TBOOLEAN);
	if(n->size < i)
	{
		lua_pushliteral(L, "out_of_range");
		lua_error(L);
		return 0;
	}
	if(lua_toboolean(L, 3))
		n->bits[i >> 5] |= 1 << (31 & i);
	else
		n->bits[i >> 5] &= ~(1 << (31 & i));
	return 0;
}
static int l_bitMap_index(lua_State *L)
{
	size_t i;
	BitMap_t *n = (BitMap_t *)luaL_checkudata(L, 1, "BitMap");
	i = luaL_checkinteger(L, 2);
	if(n->size < i)
	{
		lua_pushnil(L);
		return 1;
	}
	lua_pushboolean(L, n->bits[i >> 5] & (1 << (i & 31)));
	return 1;
}
static int l_bitMap_tostring(lua_State *L)
{
	lua_pushstring(L, "[BitMap]");
	return 1;
}

static const struct luaL_Reg bitMap_[] = 
{
	{"__len", &l_bitMap_len},
	{"__newindex", &l_bitMap_newindex},
	{"__index", &l_bitMap_index},
	{"__tostring", &l_bitMap_tostring},
	{NULL, NULL}
};
#endif

static int counter(lua_State *L)
{
	int i = lua_tointeger(L, lua_upvalueindex(1)); // int1
	lua_pushinteger(L, ++i);
	lua_copy(L, -1, lua_upvalueindex(1));
	return 1;
}
int newCounter(lua_State *L)
{
	lua_pushinteger(L, 0); // int1
	lua_pushcclosure(L, &counter, 1);
	return 1;
}

static int l_testU2(lua_State *L)
{
	int i = 0;
	int *p;
	luaL_checktype(L, 1, LUA_TFUNCTION);
	lua_pushvalue(L, 1);
	lua_pushlightuserdata(L, &i);
	lua_call(L, 1, 1);
	p = lua_touserdata(L, -1);
	*p = 5;
	if(*p == i && p == &i)
		printf("passed\n");
	else
		printf("failed\n");
	return 0;
}


static const struct luaL_Reg loc1[] = {
	{"test", &l_test}, 
	{"newCounter", &newCounter},
	{"testType", &l_testType},
	{"testStack", &l_testStack},
	{"testVar", &l_testVar},
	{"testTable", &l_testTable},
	{"testFunction", &l_testFunction},
	{"testString", &l_testString},
#ifdef TEST_BITMAP
	{"newBitMap", &l_newBitMap},
#endif
	{"testU2", &l_testU2},
	{NULL, NULL}
};

int luaopen_loc1(lua_State *L)
{
#ifdef TEST_BITMAP
  luaL_newmetatable(L, "BitMap");
  luaL_setfuncs(L, bitMap_, 0);
#endif

	luaL_newlib(L, loc1);
	return 1;
}


