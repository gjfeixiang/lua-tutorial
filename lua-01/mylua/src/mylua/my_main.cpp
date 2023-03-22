extern "C" {
#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>
#include <string.h>

}
// ����ֵ����  lua�з��ز�������
int CTest(lua_State * L) {
	printf("CTest begin top= %d \n", lua_gettop(L));
	printf("int CTest");
	size_t len;
	const char * name = lua_tolstring(L, -3, &len);
	printf("lua name:%s", name);
	int age = lua_tonumber(L, -2);
	printf("lua name:%d", age);
	bool flag = lua_toboolean(L, -1);
	printf("lua name:%d", flag);

	return 0;
}

//lua�������� �Ĳ���
int CTestArr(lua_State * L) {
	printf("CTestArr begin top= %d \n", lua_gettop(L));
	int len = luaL_len(L, -1); //�ɰ汾�� luaL_getn ��ȡ���ݳ���
	for (size_t i = 1; i <= len; i++)
	{
		printf("CTestArr top= %d \n", lua_gettop(L));
		lua_pushnumber(L, i); // ����Ҫ��ȡ�� ����������洢 ջ��  Ŀǰջ�� �� 2
		lua_gettable(L, -2); // popIndex push table[i];  ��ȡջ�� λ�� 1(ջ��)���������� i�Ĳ��� �� i ����ջ Ȼ����ѹ������� ������i��ֵ��ջ��
		size_t size;
		const char* value = lua_tolstring(L, -1, &size);
		printf("CTestArr i= %d value = %s\n",i, value);
		lua_pop(L, 1); //Ŀǰջ�� 2 �� ������Ϊ i��ֵ value ��ջ���� ��������Ҫ��   value ��ջ
	}
	return 0;
}

//lua  key value�Ļ�ȡ
int CTestTable(lua_State * L) {
	printf("CTestTable begin top= %d \n", lua_gettop(L));
	//��ȡ����һ�� filed			*******************************
	//lua_getfield(L, 1, "name"); 
	//printf("name = %s \n",lua_tostring(L,2)); // or 	printf("name = %s \n",lua_tostring(L,-1));   ջ����ֵ ���� namevalue

		// ���lua ռ��Ԫ�ص�����	******************************* 
	//1 �������ֵ��ó��������ж� 
	luaL_checktype(L, 1, LUA_TTABLE);
	printf("lua_checktype finish \n");

	//2
	if (lua_type(L, 2) != LUA_TNUMBER) {
		printf("PARAM 2 IS NOT NUM RETURN "); // or 	printf("name = %s \n",lua_tostring(L,-1
	}
 
	//��ȡ���е�key value			*******************************
	lua_pushnil(L);
	while (lua_next(L,1) != 0) {
		//pop nil push key , value
		printf("key = %s", lua_tostring(L, -2));
		printf(",value = %s \n", lua_tostring(L, -1));
		//����֮��  key��ջ valueû��ջ
		lua_pop(L,1);
	}


	return 0;
}

int CTestNoParam(lua_State* L) {
	printf("lua called fun-> CTestNoParam begin top= %d \n", lua_gettop(L));

	return 0;
}

int CTestRet(lua_State * L) {
	// 1 ���ػ�������				*****************************************
	//lua_pushstring(L, "return value from c++"); //lua �������֮��  push��value �ͱ�����

	// ����table					*****************************************
	lua_newtable(L);
	//���� key value 
	lua_pushstring(L, "name");
	lua_pushstring(L, "xiaoming");
	lua_settable(L, -3); //��-3 �����ֵ��ջ

	lua_pushstring(L, "age");
	lua_pushnumber(L, 18);

	lua_settable(L, -3);//��-3 �����ֵ��ջ  
	return 1;
}



 

void my_lua_registe(lua_State* L) {
	printf("func CTest pre no & %p", CTest);
	printf("func CTest pre nwith & %p", &CTest);
	lua_register(L, "CTest",&CTest);
	lua_register(L, "CTestArr", &CTestArr);
	lua_register(L, "CTestTable", &CTestTable);
	lua_register(L, "CTestRet", &CTestRet);
	lua_register(L, "CTestNoParam", &CTestNoParam);
}

int main()
{
	lua_State* L = luaL_newstate();
	luaopen_base(L);
	luaopen_string(L);
	luaopen_table(L);
	luaopen_debug(L);
	//luaopen_libraries(L);
	luaL_openlibs(L);
	luaopen_coroutine(L);

	my_lua_registe(L);

	printf("init lua  top = %d\n", lua_gettop(L));

	//// c++ ����luaȫ�ֱ���
	lua_pushstring(L, "hello from c++ global value"); //*****************************************
	printf("pushstring lua  top = %d\n", lua_gettop(L));

	lua_setglobal(L, "test");
	printf("after setglobal  top = %d\n", lua_gettop(L));

	//// c++ ����luaȫ�ֱ���table
	//lua_newtable(L);					//*****************************************
	////���� key value 
	//lua_pushstring(L, "c++tbf-name"); //����key
	//lua_pushstring(L, "xiaoming");  //����value
	//lua_settable(L, -3); //��-3 �����ֵ��ջ

	//lua_pushstring(L, "c++tbf-age");
	//lua_pushnumber(L, 18);
	//lua_settable(L, -3);//��-3 �����ֵ��ջ  
	//lua_setglobal(L, "cpp_global"); //�ָ�ջ�� Ϊ 3




	if (luaL_loadfile(L, "lua_src/main.lua")) {
		const char* error = lua_tostring(L,-1);
		printf("lua load error:%s\n", error);
	};
	printf("luaL_loadfile lua  top = %d\n", lua_gettop(L));
	if (lua_pcall(L, 0, 0, 0)) {
		const char* error = lua_tostring(L,-1);
		printf("lua call error:%s\n", error);
		return -1;
	}
	printf("after lua_pcall lua  top = %d\n", lua_gettop(L));
	int top = lua_gettop(L);
	////c++ ��ȡlua��ȫ�ֱ���   *****************************************
	//lua_getglobal(L, "MyGName");  
	//printf("MyGName :%s\n", lua_tostring(L, -1));
	//lua_pop(L,1);

	////1  *****************************************
	////lua_getglobal(L, "conf"); // global ���� conf ��ѹ��ջ�� 
	////lua_getfield(L, -1,"titlename"); // ��ջ����ȡ conf ������ ���� titlename ��ѹ��ջ�� ��ʱ��  conf ������λ�� -2
	////printf("conf titlename :%s\n", lua_tostring(L, -1)); // ��ջ����ȡ  titlename����ֵ
	////lua_getfield(L, -2, "height"); // ��ȡheight����  height���Ա�����ѹ��ջ��  
	////printf("conf height :%d\n", (int)lua_tonumber(L, -1));
	////lua_pop(L, 3); //���ջ������

	//	//�Ż���ȡ  1 *****************************************
	//lua_getglobal(L, "conf"); // global ���� conf ��ѹ��ջ�� 
	//lua_getfield(L, -1, "titlename"); // ��ջ����ȡ conf ������ ���� titlename ��ѹ��ջ�� ��ʱ��  conf ������λ�� -2
	//printf("conf titlename :%s\n", lua_tostring(L, -1)); // ��ջ����ȡ  titlename����ֵ
	//lua_pop(L, 1);//ջ�����Ǳ� conf titlename����ջ
	//lua_getfield(L, -1, "height"); // ��ȡheight����  height���Ա�����ѹ��ջ��  
	//printf("conf height :%d\n", (int)lua_tonumber(L, -1));
	//lua_pop(L, 1);//ջ�����Ǳ� conf  height����ջ

	//lua_pop(L, 1); //���ջ������ conf��ջ


	//c++ call lua *********************************************
	//top = lua_gettop(L); //��ȡջ����ֵ ��ʼһ��������� ��ʼ�ͽ�����ջ����ֵӦ����һ���� �����һ�� ����Ҫ�ͷŶ����ջ��Ԫ��
	//printf("top  = %d\n", top);
	//int errorFun = top;//��¼ջ��
	//lua_getglobal(L, "ferror"); //ѹ��ջ ûִ�� �����ջ
	//errorFun++;
	//lua_getglobal(L, "event");
	//top = lua_gettop(L);
	//printf("lua top : %d after get event func \n",top);
	//lua_pushstring(L, "event_cpp_name"); 
	//top = lua_gettop(L);
	//printf("lua top : %d after push  param \n",top);
	//top = lua_gettop(L);
	//printf("errorFun :%d  \n", errorFun);
	//if (lua_pcall(L,1,1, errorFun) != 0 ) {
	//	//lua_pcall����ʧ��  ���� evetn��ջ  ,����Ĳ��� event_cpp_name ��ջ�����ش���ֵѹ����ջ��
	//	printf("call event failed %s  \n", lua_tostring(L,-1));  //���event���������� ��ôջ���ͻ���ִ�����Ϣ
	//	top = lua_gettop(L);
	//	printf("lua top :%d after call  ret  value \n", top);
	//}
	//else {
	//	//lua_pcall���óɹ�  ���� evetn��ջ  ,����Ĳ��� event_cpp_name ��ջ������ֵѹ����ջ��
	//	printf("call event success return value :%s  \n", lua_tostring(L, -1)); //���ܷ���ֵ
	//	lua_pop(L, 1);//����ֵ��ջ��  ��Ҫ�ָ�ջ����Ϣ  ������Ҫpop
	//	top = lua_gettop(L);
	//	printf("lua top :%d after call  ret  value \n", top);
	//}
	//// ferror û��ִ��û�г�ջ  ������Ҫ�ֶ���ջ
	//lua_pop(L, 1);
	// top = lua_gettop(L);
	//printf("top  = %d\n", top);

	// lua_pcall ������ �ȶ�ȡ lua�������� ��ջ Ȼ����� ָ��func  ,��ջ����󽲷���ֵѹ��ջ ************************************************
	//top = lua_gettop(L);
	//printf("before get global func,top  = %d\n", top);
	//lua_getglobal(L, "eventNoparams");
	//printf("after get global func,top  = %d\n", lua_gettop(L));
	//if (lua_pcall(L, 0, 1, 0) != 0) {
	//		top = lua_gettop(L);
	//		//����з���ֵ ����ȡ֮�� pop����ֵ����
	//		int number = (int)lua_tonumber(L, -1);
	//		lua_pop(L,1);
	//		printf("call func error: lua top :%d  \n", top);
	//}
	//else {
	//	top = lua_gettop(L);
	//	printf("call lua func success ,lua top :%d  \n", top);
	//	int number = (int)lua_tonumber(L, -1);
	//	lua_pop(L, 1);
	//	printf("pop 1 , to correct lua stack");
	//}
	
		// c++ ���ݱ�,���ر�   //*****************************************
	//printf("top = %d\n",lua_gettop(L));
	//lua_getglobal(L, "eventHasTableParams");
	//lua_pushstring(L, "name");
	//lua_newtable(L);					
	////���� key value 
	//lua_pushstring(L, "c++tbf-name"); //key
	//lua_pushstring(L, "xiaoming"); //value 
	//lua_settable(L, -3); //��-3 �����ֵ��ջ

	//lua_pushstring(L, "c++tbf-age");
	//lua_pushnumber(L, 18);
	//lua_settable(L, -3);//��-3 �����ֵ��ջ  
	//

	//if (lua_pcall(L, 2, 1, 0) != 0) {

	//}
	//else {
	//	lua_getfield(L, -1, "name");
	//	const char* name =  lua_tostring(L, -1);
	//	lua_pop(L, 1);
	//	lua_getfield(L, -1, "age");
	//	const char *   age = lua_tostring(L, -1);
	//	lua_pop(L, 1);
	//	printf("name = %s, age = %s\n", name ,age);
	//}
	//lua_pop(L, 1);
	//printf("top = %d\n", lua_gettop(L));


	//printf("stack 1 datat type %d", lua_type(L, 1));
	//printf("stack 2 datat type %d", lua_type(L, 2));
	//printf("stack 3 datat type %d", lua_type(L, 3));
	lua_close(L);
	return 0;
} 