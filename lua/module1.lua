module = {}
module.gb = "dk"
function module.f1()
	print("public")
end
local function fc()
	print("fc")
end
function module.f2()
	fc()
end
local loc1_path = "./loc1.so"
-- module.loc1 = assert(loadlib(loc1_path, "loc1"))
module.loc1 = require("loc1")

return module
