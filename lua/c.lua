local loc1 = require "loc1"
loc1.test()

n, s = loc1.testType(true, 5, "[str]", function(a) return a * a end, {i = 5})
print(n, s)

loc1.testStack(5, true, nil)
var1 = 5

loc1.testVar("var1", "var2")
print(var2)

v = loc1.testTable({[1] = 4, [2] = 8, [0] = 7, i = 5})
print(v.i, v[1], v[2]);
-- print(v)

f = loc1.testFunction(function(a, b) return a + b end)
f()

s = loc1.testString("[str]")
print(s)

v = loc1.newBitMap(500)
print(#v)
v[5] = true
print(v[5])
print(v)

c1 = loc1.newCounter()
print(c1())
print(c1())
print(c1())

loc1.testU2(function(u) print(type(u)) return u end)



