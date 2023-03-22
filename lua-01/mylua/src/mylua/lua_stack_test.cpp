//extern "C" {
//#include <lua.h>
//#include <lauxlib.h>
//#include <lualib.h>
//#include <string.h>
//
//}
//
//// ����ֵ����  lua�з��ز�������
//int CTestNoParam(lua_State* L) {
//	printf("lua called fun-> CTestNoParam begin top= %d \n", lua_gettop(L));
//
//	return 0;
//}
//
//// ����ֵ����  lua�з��ز�������
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
////lua�������� �Ĳ���
//int CTestArr(lua_State* L) {
//	printf("lua called fun-> CTestArr print:begin top= %d \n", lua_gettop(L));
//	int len = luaL_len(L, 1); //�ɰ汾�� luaL_getn ��ȡ���ݳ���
//	for (size_t i = 1; i <= len; i++)
//	{
//		printf("lua called fun-> CTestArr top= %d \n", lua_gettop(L));
//		lua_pushnumber(L, i); // ����Ҫ��ȡ�� ����������洢 ջ��  Ŀǰջ�� �� 2
//		lua_gettable(L, 1); // popIndex push table[i];  ��ȡջ�� λ�� 1(ջ��)���������� i�Ĳ��� �� i ����ջ Ȼ����ѹ������� ������i��ֵ��ջ��
//		size_t size;
//		const char* value = lua_tolstring(L, 2, &size);
//		printf("lua called fun-> CTestArr i= %d value = %s\n", i, value);
//		lua_pop(L, 1); //Ŀǰջ�� 2 �� ������Ϊ i��ֵ value ��ջ���� ��������Ҫ��   value ��ջ
//	}
//	return 0;
//}
//
////lua  key value�Ļ�ȡ
//int CTestTable(lua_State* L) {
//	printf("lua called fun->CTestTable print : CTestTable begin top= %d \n", lua_gettop(L));
//	//��ȡ����һ�� filed			*******************************
//	//lua_getfield(L, 1, "name"); 
//	//printf("name = %s \n",lua_tostring(L,2)); // or 	printf("name = %s \n",lua_tostring(L,-1));   ջ����ֵ ���� namevalue
//
//		// ���lua ռ��Ԫ�ص�����	******************************* 
//	//1 �������ֵ��ó��������ж� 
//	luaL_checktype(L, 1, LUA_TTABLE);
//	printf("lua called fun-> lua_checktype finish \n");
//
//	//2
//	if (lua_type(L, 2) != LUA_TNUMBER) {
//		printf("lua called fun-> PARAM 2 IS NOT NUM RETURN "); // or 	printf("name = %s \n",lua_tostring(L,-1
//	}
//
//	//��ȡ���е�key value			*******************************
//	lua_pushnil(L);
//	while (lua_next(L, 1) != 0) {
//		//pop nil push key , value
//		printf("lua called fun-> key = %s", lua_tostring(L, -2));
//		printf("lua called fun-> ,value = %s \n", lua_tostring(L, -1));
//		//����֮��  key��ջ valueû��ջ
//		lua_pop(L, 1);
//	}
//	return 0;
//}
//
//int CTestRet(lua_State* L) {
//	// 1 ���ػ�������				*****************************************
//	//lua_pushstring(L, "return value from c++"); //lua �������֮��  push��value �ͱ�����
//
//	// ����table					*****************************************
//	lua_newtable(L);
//	//���� key value 
//	lua_pushstring(L, "name");
//	lua_pushstring(L, "xiaoming");
//	lua_settable(L, -3); //��-3 �����ֵ��ջ
//
//	lua_pushstring(L, "age");
//	lua_pushnumber(L, 18);
//
//	lua_settable(L, -3);//��-3 �����ֵ��ջ  
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
//	//// c++ ����luaȫ�ֱ���
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