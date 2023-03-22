print("-----------------------------------------------------------------")
function test1()
    c = nil
	a = 1
	b = a + 3
	print(b)
	--print(c.x)
end

function test2()
	c = {}
	table.insert(c,1)
	print("table size is : ".. #c)
end

function hook()
	print(debug.traceback())
end


test1()

function test2(...)
    local name,name2= select(2,...)
    print("test2",name2)
    print("select(2,...)",select(2,...))
end

test2("nihao","feixiang","gaojie")
--debug.sethook(hook,"l")


co = coroutine.create(function()
    for i=0,10 do
        print(i)
        coroutine.yield()  --挂起
        print("after yield")
    end
end)
coroutine.resume(co)    --0
coroutine.resume(co)    --after yield 和 1
print(coroutine.status(co)) --suspended
coroutine.resume(co)    --after yield 和 2
coroutine.resume(co)    --after yield 和 3
coroutine.resume(co)    --after yield 和 4
coroutine.resume(co)    --after yield 和 5
coroutine.resume(co)    --after yield 和 6
coroutine.resume(co)    --after yield 和 7
coroutine.resume(co)    --after yield 和 8
coroutine.resume(co)    --after yield 和 9
coroutine.resume(co)    --after yield 和 10
print(coroutine.resume(co) )   
print(coroutine.resume(co) )   
print(coroutine.resume(co) )   
print(coroutine.resume(co) )   
print(coroutine.resume(co) )   



wrap =  coroutine.wrap(function()
    for i=0,2 do
        print("coroutine warp ",i)
        coroutine.yield()
    end
end)
wrap()  --1
wrap()  --2
wrap()  --3
-- wrap()  --什么都没打印，协程执行完毕（这是因为碰到yield后，协程的状态为挂起，而不是死亡）
-- wrap()  --error：cann


co = coroutine.create(function(a,b)
    print("coroutine",a,b)
end
)
coroutine.resume(co,1,2)  -- 


co = coroutine.create(function(x)
    print("coroutine",coroutine.yield())
end
)
coroutine.resume(co,1)      --不打印任何值
coroutine.resume(co,1,2)    --打印 1 2

co = coroutine.create(function(x)
    return 1,2
end
)
print("coroutine",coroutine.resume(co))  -- true  1  2

print("********************************************")
function foo (a)
    print("foo", a)
    return coroutine.yield(2*a)
end

co = coroutine.create(function (a,b)
        print("co-body", a, b)
        local r = foo(a+1)
        print("co-body", r)
        local r, s = coroutine.yield(a+b, a-b)
        print("co-body", r, s)
        return b, "end"
    end)

print("main  1", coroutine.resume(co, 1, 10))
print("********************************************")
print("main  2", coroutine.resume(co, "r"))
print("********************************************")
print("main  3", coroutine.resume(co, "x", "y"))
-- print("********************************************")
-- print("main", coroutine.resume(co, "x", "y"))
-- print("********************************************")


print("consume and productor>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>");
local newProductor

function productor()
     local i = 0
     while i < 100  do
          i = i + 1
          send(i)     -- 将生产的物品发送给消费者
     end
end

function consumer()
     while true do
          local i = receive()     -- 从生产者那里得到物品
          print(i)
          if  not i or i >= 102 then 
            break
          end 
     end
end

function receive()
     local status, value = coroutine.resume(newProductor)
     return value
end

function send(x)
     coroutine.yield(x)     -- x表示需要发送的值，值返回以后，就挂起该协同程序
end

-- 启动程序
newProductor = coroutine.create(productor)
consumer()
print("consume and productor>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>");