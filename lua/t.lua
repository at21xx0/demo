
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
print(string.len(str))
print(string.rep(str,4))
print(str .. "1")





