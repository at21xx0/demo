
--  单行注释
--[[ 
  多行注释
	]]--


-- nil 无效值
-- boolean
-- number
-- string
-- function
-- userdata
-- thread
-- table

print(type("str"))
print(type(print))
k=0;
print(k)
str=[[
wode
zixin
]]
print(str)
print("len");
print(#str)
table1={}
table2={"apple","pear","orange","grape"}
a={}
a["key"]="value"
a[4]=12
for key, val in pairs(a) do
	print(key .. " : " .. val)
end

function f1(t,f)
	i=4
	local d=f(t)
	print(d)
	return d;
end

i=5
f1(i,function(a)
	return a+1
end
);
print("hello" .. "world")
a,b=10,6;
a,b=b,a;
print(a,b)
--swap 'a' for 'b'
a=10
while( a < 20 )
	do
		print("a: ",a)
		a=a+1;
	end
for i=10,1,-1 do
	print(i)
end
for i=0,10 do
	print(i)
end
a = 10
repeat
	print(a)
	a=a+1;
until(a<15)
a=10
while(a<20)
	do
		print("break")
		break;
	end
a=1
::lz::
print(a)
a=a+1
if a<3 then
	goto lz;
end
if(0) then
	print(0)
elseif(2) then
	print(2)
else
	print(3)
end

function max(n1,n2)
	if(n1>n2) then
		return n1
	else
		return n2
	end
end
local function local_ab()
	return 2,3
end
a,b=local_ab()
function add(...)
	local s=0
	print("sl",select("#",...))
	print("ss",select(3,...))
	for i,v in ipairs{...} do
		s=v+s
	end
	return s
end
print(add(12,34,56,78))

str="Main"

print(string.upper(str))
print(string.lower(str))
print(string.gsub(str,"ai","**",1))
print(string.find(str,"ai",nil,1))
print(string.reverse(str))
print(string.format("%d",5))
print(string.char(97,98,99,100))
print(string.byte("ABCD",4))
print(string.byte("ABCD"))
-- string.char(53)
print(string.len(str))
print(string.rep(str,4))
print(str .. "1")
print(tostring(1))

arr1 = {"xl", "en", "dk"}
for i = 1,3 do
	print(arr1[i])
end
arr2 = {}
arr2[1] = {4, 6}
arr2[2] = {3, 5}
print(arr2[1][1])
for k, v in pairs(arr1) do
	print(k, v)
end
function Iter(arr)
	local i = 0
	local n = #arr
	return function()
		i = i + 1
		if i <= n
			then
				return arr[i]
			end
		end
	end
for e in Iter(arr1) do
	print(e)
end
arr2 = nil


-- table
t1 = {}
t1["zn"] = "xl"
t1["gt"] = "dk"
print(type(t1))
print(t1["gt"])
t2 = t1
t2["gt"] = "zi"
print(t1["gt"] .. " " .. t2["gt"])
t1 = nil
function pArr(a)
	print(table.concat(a, "|"))
end
print(table.concat(arr1))
print(table.concat(arr1, "|"))
print(table.concat(arr1, "|", 2, 3))
table.insert(arr1, "zi")
table.insert(arr1, 2, "p0")
pArr(arr1)
table.sort(arr1)
table.remove(arr1)
pArr(arr1)

function tableToString(t)
	s = ""
	for k, v in pairs(t) do
		s = s .. k .. " = " .. v .. "; "
	end
	return s
end
function pTab(t)
	print(tableToString(t))
end


-- require("module1")
local m = require("module1")
m.f1()
m.f2()
print(m.gb)

-- export LUA_PATH="~/lua/?.lua;;"
-- ;; 表示默认LUA_PATH
print(os.getenv("PWD"))
m.loc1.test()

t2 = {}
-- t3 = {}
t2.zi = "ul"
t2.ml = "en"
pTab(t2)
t1 = setmetatable(t2, {__index = {lg = "sg"}})
pTab(t1)
print(t1.lg)
t1 = setmetatable(t2, {
	__index = function(t, k)
		if k == "lg" then
			return "sg"
		else
			return nil
		end
	end
	, __newindex = function(t, k, v) -- t3
		rawset(t, k, "[".. v .. "]")
	end
	,  __add = function(t, n)
		print("__add(" .. tableToString(t) .. ", " .. tableToString(n) .. ")")
		return nil
	end
	-- __add + __sub - __mul * __div / __mod % __unm - __concat .. __lt < __le > __eq ==
	, __call = function(t, n)
		print("__call(" .. tableToString(t) .. ", " .. tableToString(n) .. "]")
		return nil
	end
	, __tostring = function(t)
		return tableToString(t)
	end
})
print(t1.lg) -- __index
t1.lt = "le" -- __newindex
pArr(t1)
print(t1 + t2) -- __add
print(t1(t2)) -- __call
print(t1) -- __tostring

-- coroutinue
c1 = coroutine.create(
	function(t)
		print(t)
	end
)
coroutine.resume(c1, 1)
print(coroutine.status(c1))
print("\n\n")
c1 = coroutine.wrap(function(i) print(i) end)
c1(1)
c2 = coroutine.create(
	function()
		for i = 1, 10 do
			print(i)
			if i == 3 then
				print(coroutine.status())
				print(coroutine.running())
			end
			print(i)
			coroutine.yield()
		end
	end
)
coroutine.resume(c2)
print(coroutine.status(c2))
coroutine.resume(c2)
coroutine.resume(c2)
print(coroutine.status(c2))
print(coroutine.running())
function fadd1(i)
	return coroutine.yield(i + 1)
end
c1 = coroutine.create(
function(t)
	print(t)
	t = fadd1(t)
	print(t)
	t = fadd1(t)
	print(t)
	t = coroutine.yield(t + 1)
	print(t)
end)
status, v = coroutine.resume(c1, 1)
status, v = coroutine.resume(c1, v)
status, v = coroutine.resume(c1, v)
print(coroutine.resume(c1, v))

f1 = io.open("a.txt", "w+") -- r w a r+ w+ a+ + b
io.output(f1)
io.write("xxxx \n5 abcdef\nzi_mul")
io.close(f1)
f1 = io.open("a.txt", "r")
io.input(f1)
print(io.read()) -- "*i"
print(io.read("*n")) -- "*n"
print(io.read(5)) -- 5
print(io.type(f1))
-- io.flush()
io.close(f1)
-- f2 = io.tmpfile()
f2 = io.open("a.txt", "r")
print(f2:read())
f2:seek("set", 0)
print(f2:read())
f2:seek("cur", 2) 
print(f2:read())
-- f2:seek("end", -6)
-- print(f2:read())
f2:flush()
f2:close()
for l in io.lines("a.txt") do
	print(l)
end

assert(type(arr1) == "table", "arr1")
-- level = 1 -- default 0, 1, 2
-- error("mesage", level)
if pcall(function(i) print(i) error("err") return 1 end, 1) then
else
	print("error")
end
function errF()
	e = e + 1
end
function errorHander(e)
	print("err: " .. e)
end
status = xpcall(errF, errorHander)
print(status)

C = {v = 0}
function C:new(o, v)
	o = o or {}
	setmetatable(o, self)
	self.__index = self
	v = v or 0
	self.v = v
	return o
end
function C:getV()
	return self.v
end
c1 = C:new(nil, 5)
print(c1.v)
print(c1:getV())

loadfile("hello.lua")()
-- loadstring("print(5)")()



