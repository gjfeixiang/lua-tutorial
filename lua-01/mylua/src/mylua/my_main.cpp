extern "C" {
#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>
#include <string.h>

}
// 返回值表是  lua中返回参数个数
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

//lua传入数组 的操作
int CTestArr(lua_State * L) {
	printf("CTestArr begin top= %d \n", lua_gettop(L));
	int len = luaL_len(L, -1); //旧版本是 luaL_getn 获取数据长度
	for (size_t i = 1; i <= len; i++)
	{
		printf("CTestArr top= %d \n", lua_gettop(L));
		lua_pushnumber(L, i); // 将需要获取的 数组的索引存储 栈顶  目前栈顶 是 2
		lua_gettable(L, -2); // popIndex push table[i];  获取栈中 位置 1(栈底)表中索引是 i的操作 ： i 出出栈 然后再压入表中是 索引是i的值到栈顶
		size_t size;
		const char* value = lua_tolstring(L, -1, &size);
		printf("CTestArr i= %d value = %s\n",i, value);
		lua_pop(L, 1); //目前栈顶 2 是 表索引为 i的值 value ，栈底是 表，所以需要将   value 出栈
	}
	return 0;
}

//lua  key value的获取
int CTestTable(lua_State * L) {
	printf("CTestTable begin top= %d \n", lua_gettop(L));
	//获取其中一个 filed			*******************************
	//lua_getfield(L, 1, "name"); 
	//printf("name = %s \n",lua_tostring(L,2)); // or 	printf("name = %s \n",lua_tostring(L,-1));   栈顶的值 就是 namevalue

		// 检查lua 占用元素的类型	******************************* 
	//1 下面这种调用出错程序就中断 
	luaL_checktype(L, 1, LUA_TTABLE);
	printf("lua_checktype finish \n");

	//2
	if (lua_type(L, 2) != LUA_TNUMBER) {
		printf("PARAM 2 IS NOT NUM RETURN "); // or 	printf("name = %s \n",lua_tostring(L,-1
	}
 
	//获取所有的key value			*******************************
	lua_pushnil(L);
	while (lua_next(L,1) != 0) {
		//pop nil push key , value
		printf("key = %s", lua_tostring(L, -2));
		printf(",value = %s \n", lua_tostring(L, -1));
		//调用之后  key出栈 value没出栈
		lua_pop(L,1);
	}


	return 0;
}

int CTestNoParam(lua_State* L) {
	printf("lua called fun-> CTestNoParam begin top= %d \n", lua_gettop(L));

	return 0;
}

int CTestRet(lua_State * L) {
	// 1 返回基本类型				*****************************************
	//lua_pushstring(L, "return value from c++"); //lua 调用完成之后  push的value 就被弹出

	// 返回table					*****************************************
	lua_newtable(L);
	//插入 key value 
	lua_pushstring(L, "name");
	lua_pushstring(L, "xiaoming");
	lua_settable(L, -3); //将-3 上面得值出栈

	lua_pushstring(L, "age");
	lua_pushnumber(L, 18);

	lua_settable(L, -3);//将-3 上面得值出栈  
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

	//// c++ 设置lua全局变量
	lua_pushstring(L, "hello from c++ global value"); //*****************************************
	printf("pushstring lua  top = %d\n", lua_gettop(L));

	lua_setglobal(L, "test");
	printf("after setglobal  top = %d\n", lua_gettop(L));

	//// c++ 设置lua全局变量table
	//lua_newtable(L);					//*****************************************
	////插入 key value 
	//lua_pushstring(L, "c++tbf-name"); //插入key
	//lua_pushstring(L, "xiaoming");  //插入value
	//lua_settable(L, -3); //将-3 上面得值出栈

	//lua_pushstring(L, "c++tbf-age");
	//lua_pushnumber(L, 18);
	//lua_settable(L, -3);//将-3 上面得值出栈  
	//lua_setglobal(L, "cpp_global"); //恢复栈顶 为 3




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
	////c++ 获取lua的全局变量   *****************************************
	//lua_getglobal(L, "MyGName");  
	//printf("MyGName :%s\n", lua_tostring(L, -1));
	//lua_pop(L,1);

	////1  *****************************************
	////lua_getglobal(L, "conf"); // global 变量 conf 被压入栈顶 
	////lua_getfield(L, -1,"titlename"); // 从栈顶获取 conf 变量的 属性 titlename 被压入栈顶 这时候  conf 变量的位置 -2
	////printf("conf titlename :%s\n", lua_tostring(L, -1)); // 从栈顶获取  titlename属性值
	////lua_getfield(L, -2, "height"); // 获取height属性  height属性变量被压入栈顶  
	////printf("conf height :%d\n", (int)lua_tonumber(L, -1));
	////lua_pop(L, 3); //清楚栈顶数据

	//	//优化读取  1 *****************************************
	//lua_getglobal(L, "conf"); // global 变量 conf 被压入栈顶 
	//lua_getfield(L, -1, "titlename"); // 从栈顶获取 conf 变量的 属性 titlename 被压入栈顶 这时候  conf 变量的位置 -2
	//printf("conf titlename :%s\n", lua_tostring(L, -1)); // 从栈顶获取  titlename属性值
	//lua_pop(L, 1);//栈顶还是表 conf titlename被出栈
	//lua_getfield(L, -1, "height"); // 获取height属性  height属性变量被压入栈顶  
	//printf("conf height :%d\n", (int)lua_tonumber(L, -1));
	//lua_pop(L, 1);//栈顶还是表 conf  height被出栈

	//lua_pop(L, 1); //清楚栈顶数据 conf出栈


	//c++ call lua *********************************************
	//top = lua_gettop(L); //获取栈顶数值 开始一个计算完成 开始和结束的栈顶数值应该是一样的 如果不一样 就需要释放多余的栈顶元素
	//printf("top  = %d\n", top);
	//int errorFun = top;//记录栈顶
	//lua_getglobal(L, "ferror"); //压入栈 没执行 不会出栈
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
	//	//lua_pcall调用失败  函数 evetn出栈  ,传入的参数 event_cpp_name 出栈，返回错误值压入了栈顶
	//	printf("call event failed %s  \n", lua_tostring(L,-1));  //如果event函数不存在 那么栈顶就会出现错误信息
	//	top = lua_gettop(L);
	//	printf("lua top :%d after call  ret  value \n", top);
	//}
	//else {
	//	//lua_pcall调用成功  函数 evetn出栈  ,传入的参数 event_cpp_name 出栈，返回值压入了栈顶
	//	printf("call event success return value :%s  \n", lua_tostring(L, -1)); //接受返回值
	//	lua_pop(L, 1);//返回值在栈顶  需要恢复栈顶信息  所以需要pop
	//	top = lua_gettop(L);
	//	printf("lua top :%d after call  ret  value \n", top);
	//}
	//// ferror 没被执行没有出栈  所以需要手动出栈
	//lua_pop(L, 1);
	// top = lua_gettop(L);
	//printf("top  = %d\n", top);

	// lua_pcall 过程是 先读取 lua函数参数 出栈 然后调用 指定func  ,出栈，最后讲返回值压入栈 ************************************************
	//top = lua_gettop(L);
	//printf("before get global func,top  = %d\n", top);
	//lua_getglobal(L, "eventNoparams");
	//printf("after get global func,top  = %d\n", lua_gettop(L));
	//if (lua_pcall(L, 0, 1, 0) != 0) {
	//		top = lua_gettop(L);
	//		//如果有返回值 ，读取之后 pop返回值个数
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
	
		// c++ 传递表,返回表   //*****************************************
	//printf("top = %d\n",lua_gettop(L));
	//lua_getglobal(L, "eventHasTableParams");
	//lua_pushstring(L, "name");
	//lua_newtable(L);					
	////插入 key value 
	//lua_pushstring(L, "c++tbf-name"); //key
	//lua_pushstring(L, "xiaoming"); //value 
	//lua_settable(L, -3); //将-3 上面得值出栈

	//lua_pushstring(L, "c++tbf-age");
	//lua_pushnumber(L, 18);
	//lua_settable(L, -3);//将-3 上面得值出栈  
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