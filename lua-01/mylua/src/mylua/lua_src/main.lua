-- print("Hello Lua")
CTest("lua call c++",100,true);

local arr = {"1","2","3"}
CTestArr(arr)

-- conf = {
--     titlename="lua ѧϰ",
--     height = 100,
-- }

local tab= {
   name = "gjfeixiang",
   age="22",
   id = "007",
}
local size= 108;
CTestTable(tab,size);

-- local retValue = CTestRet();
-- print("retValue ",retValue.name,retValue.age)

-- MyGName = "LuaNameSpace"


-- print("c++ set golal value = ",test)

-- print("c++ cpp_global",cpp_global)
-- for key, value in pairs(cpp_global) do
--     print("c++ cpp_global,key,value,",key,value)
-- end

function ferror(e)
    print("my error" .. e);
    return "lua change error "
end

function event(eventName)
    print("calll from c++",eventName);
    return "event_ret_value"
end

function eventNoparams()
    return 1;
end

function eventHasTableParams(name,tb)
    print("eventHasTableParams",name)
    for key, value in pairs(tb) do
        print("key",key,"value",value);
    end
    return {name = "gaojie",age = "19"}
end

CTestNoParam()



 
package.path =  package.path  .. ";E:/Personal/PersonalC++/12_lua/mylua/src/mylua/lua_src/?.lua"
print(package.path)
local metatable_test = require "metatable_test"
-- metatable_test.test_rawset_rawget()
-- metatable_test.test_call()
-- metatable_test.test_tostring()
-- metatable_test.test_index()
metatable_test.test_newindex()




require "coroutine_test"


function selecttest(...)
    local a,b,c = select(2,...)
    print(a,b,c)
end

selecttest("a","b","c","d")

print(string.dump(function() print("hello") end,false))



require "Example"

