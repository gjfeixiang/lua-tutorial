local Tag =  "test_rawset_rawget"
return {
    test_rawset_rawget = function ()
        Tag =  "test_rawset_rawget"
        local t1 = {id = 100,name = "xiaoming"}
        local newIndexTable = {
            dog = "newIndexTable_dog"
        }
        local indexTable = {
            cat = "index_cat"
        }
        setmetatable(t1,{
            __newindex = newIndexTable;
            __index = indexTable;
        })

        --rawset/rawget 都是针对本表 做赋值和读取 如果本表没有，不受元表影响
        print(rawset(t1,"dog","mydog"))
        print(Tag,t1.dog,newIndexTable.dog)
        print(Tag,rawget(t1,"cat"),indexTable.cat)
    end,

    test_call = function()
        Tag =  "test_call"
        local t1 = {id = 101}

        -- t1()  会查找有没有元表 有没有实现 __call 方法 如果实现了 调用call方法
        -- t1.__call = function()
        --     print(Tag," __call")
        -- end
        setmetatable(t1,{
           __call = function(t) print(Tag,t1.id) end
        })

        t1(t1);  --这样必须要设置 元表对象并且要 添加 __call属性  可以做一些初始化 或者其他操作 也有点类似c++ () 运算符重载
    end,

    test_tostring = function()
        Tag =  "test_tostring"
        local t1 = {id = 102} 
        setmetatable(t1,{
            __tostring = function(t) return Tag .. t.id end
         })
        print(t1)
    end,

    test_index = function() 
        Tag =  "test_index"
        -- 先去当前表中的key 如果有直接返回
        -- 如果没有 
        --        查找有没有元表
        --        如果没有 返回 nil
        --        如果有
        --            查找有没有 __index
        --            如果没有 返回nil
        --            如果有 
        --                查看  __index  是不是个表
        --                如果不是
        --                    查看是不是个方法、
        --                    如果是，直接调用该方法 且表和key 都是该方法的参数，如果有返回值 第一次获取的是返回值  第二次获取的是方法复制key的值
        --                如果是
        --                    查看有没有 指定 key
        --                    如果有返回 
        --                    如果没有  返回 nil

        local t1 = {id = 104,name = "xiaoming"} 
        -- local t2 = {}
        -- local meta = {}
        -- -- __index = table
        -- setmetatable(t1,t2)
        -- print(Tag,t1.phone)  -- nil
        -- t2.phone = "t2_phone"
        -- print(Tag,t1.phone) -- nil
        -- t2.__index = meta  
        -- meta.phone = "meta_phone"
        -- print(Tag,t1.phone)  -- meta_phone

        -- __index = function
        local t3 = {}
        setmetatable(t1,t3)
        print(Tag,t1.phone)  -- nil
        t3.phone = "t3_phone"
        print(Tag,t1.phone) -- nil
        t3.__index = function(t,k)
            print(Tag,t,k)
            rawset(t,k,"t3_index_function_phone")
            return "123"
        end  
        print(Tag,t1.phone)  -- test_index 123
        print(Tag,t1.phone)  -- test_index t3_index_function_phone
    end,

    test_newindex = function() 
        Tag =  "test_newindex"
        local t1 = {id = 105,name = "xiaoming"} 
        local t2 = {}
        -- local newindext = {phone = "newindex_phone"}
        -- -- __newindex = table
        -- setmetatable(t1,t2)
        -- print(Tag,t1.phone)  -- nil
        -- t2.__newindex = newindext  
        -- t1.phone = "t1_phone1"
        -- print(Tag,t1.phone,t2.phonel,newindext.phone) 

        -- rawset(t1,"phone","t1_phone2")
        -- print(Tag,t1.phone,t2.phonel,newindext.phone) 
        -- newindext.phone = "newindext phone:t1_phone after rawset"
        -- t1.phone = " == to reset phone value"
        -- print(Tag,t1.phone,t2.phonel,newindext.phone) 


        -- __newindex = func
        setmetatable(t1,t2)
        print(Tag,t1.phone)  -- nil
        t2.__newindex = function(t,k,v) 
            -- t[k] = v -- warnning stack overflow
            print(Tag,t,k,v)
            rawset(t,k,v)
        end  
        t1.phone = "t1_phone1"
    end
}

