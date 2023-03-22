//extern "C" {
//#include <lua.h>
//#include <lauxlib.h>
//#include <lualib.h>
//#include <string.h>
//
//}
//
//// 返回值表是  lua中返回参数个数
//int CTestNoParam(lua_State* L) {
//	printf("lua called fun-> CTestNoParam begin top= %d \n", lua_gettop(L));
//
//	return 0;
//}
//
//// 返回值表是  lua中返回参数个数
//int CTest(lua_State* L) {
//	printf("lua called fun-> CTest begin top= %d \n", lua_gettop(L));
//	printf("lua called fun-> int CTest\n");
//	size_t len;
//	const char* name = lua_tolstring(L, -3, &len);
//	printf("lua called fun-> lua name:%s\n", name);
//	int age = lua_tonumber(L, -2);
//	printf("lua called fun-> lua name:%d\n", age);
//	bool flag = lua_toboolean(L, -1);
//	printf("lua called fun-> lua name:%d\n", flag);
//
//	return 0;
//}
//
////lua传入数组 的操作
//int CTestArr(lua_State* L) {
//	printf("lua called fun-> CTestArr print:begin top= %d \n", lua_gettop(L));
//	int len = luaL_len(L, 1); //旧版本是 luaL_getn 获取数据长度
//	for (size_t i = 1; i <= len; i++)
//	{
//		printf("lua called fun-> CTestArr top= %d \n", lua_gettop(L));
//		lua_pushnumber(L, i); // 将需要获取的 数组的索引存储 栈顶  目前栈顶 是 2
//		lua_gettable(L, 1); // popIndex push table[i];  获取栈中 位置 1(栈底)表中索引是 i的操作 ： i 出出栈 然后再压入表中是 索引是i的值到栈顶
//		size_t size;
//		const char* value = lua_tolstring(L, 2, &size);
//		printf("lua called fun-> CTestArr i= %d value = %s\n", i, value);
//		lua_pop(L, 1); //目前栈顶 2 是 表索引为 i的值 value ，栈底是 表，所以需要将   value 出栈
//	}
//	return 0;
//}
//
////lua  key value的获取
//int CTestTable(lua_State* L) {
//	printf("lua called fun->CTestTable print : CTestTable begin top= %d \n", lua_gettop(L));
//	//获取其中一个 filed			*******************************
//	//lua_getfield(L, 1, "name"); 
//	//printf("name = %s \n",lua_tostring(L,2)); // or 	printf("name = %s \n",lua_tostring(L,-1));   栈顶的值 就是 namevalue
//
//		// 检查lua 占用元素的类型	******************************* 
//	//1 下面这种调用出错程序就中断 
//	luaL_checktype(L, 1, LUA_TTABLE);
//	printf("lua called fun-> lua_checktype finish \n");
//
//	//2
//	if (lua_type(L, 2) != LUA_TNUMBER) {
//		printf("lua called fun-> PARAM 2 IS NOT NUM RETURN "); // or 	printf("name = %s \n",lua_tostring(L,-1
//	}
//
//	//获取所有的key value			*******************************
//	lua_pushnil(L);
//	while (lua_next(L, 1) != 0) {
//		//pop nil push key , value
//		printf("lua called fun-> key = %s", lua_tostring(L, -2));
//		printf("lua called fun-> ,value = %s \n", lua_tostring(L, -1));
//		//调用之后  key出栈 value没出栈
//		lua_pop(L, 1);
//	}
//	return 0;
//}
//
//int CTestRet(lua_State* L) {
//	// 1 返回基本类型				*****************************************
//	//lua_pushstring(L, "return value from c++"); //lua 调用完成之后  push的value 就被弹出
//
//	// 返回table					*****************************************
//	lua_newtable(L);
//	//插入 key value 
//	lua_pushstring(L, "name");
//	lua_pushstring(L, "xiaoming");
//	lua_settable(L, -3); //将-3 上面得值出栈
//
//	lua_pushstring(L, "age");
//	lua_pushnumber(L, 18);
//
//	lua_settable(L, -3);//将-3 上面得值出栈  
//	return 1;
//}
//
//
//
//
//
//void my_lua_registe(lua_State* L) {
//	lua_register(L, "CTest", &CTest);
//	lua_register(L, "CTestArr", &CTestArr);
//	lua_register(L, "CTestTable", &CTestTable);
//	lua_register(L, "CTestRet", &CTestRet);
//	lua_register(L, "CTestNoParam", &CTestNoParam);
//}
//
//int mainc()
//{
//	lua_State* L = luaL_newstate();
//	luaopen_base(L);
//	luaopen_string(L);
//	luaopen_table(L);
//	my_lua_registe(L);
//
//	printf("main print :init lua  top = %d\n", lua_gettop(L));
//
//	//// c++ 设置lua全局变量
//	lua_pushstring(L, "hello from c++ global value"); //*****************************************
//	printf("main print :pushstring lua  top = %d\n", lua_gettop(L));
//
//	lua_setglobal(L, "test");
//	printf("main print :after setglobal  top = %d\n", lua_gettop(L));
//
//
//	if (luaL_loadfile(L, "lua_src/main.lua")) {
//		const char* error = lua_tostring(L, -1);
//		printf("main print : lua load error:%s\n", error);
//	};
//	printf("main print : luaL_loadfile lua  top = %d\n", lua_gettop(L));
//	if (lua_pcall(L, 0, 0, 0)) {
//		const char* error = lua_tostring(L, -1);
//		printf("lua call error:%s\n", error);
//		return -1;
//	}
//	printf("main print : after lua_pcall lua  top = %d\n", lua_gettop(L));
//	
//	lua_close(L);
//	return 0;
//}