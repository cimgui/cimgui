--script for imgui_structs.h generation
--require"vicutils.utils"
local function strip(cad)
	return cad:gsub("^%s*(.-)%s*$","%1") --remove initial and final spaces
end
local function clean_spaces(cad)
	cad = strip(cad)
	--cad = cad:gsub("%s+","%s") --not more than one space
	cad = cad:gsub("%s*([%(%),=])%s*","%1") --not spaces with ( , )
	return cad
end


local cimgui_overloads = {
	igPushID = {
		["(const char*)"] = 			"igPushIDStr",
		["(const char*,const char*)"] = "igPushIDRange",
		["(const void*)"] = 			"igPushIDPtr",
		["(int)"] = 					"igPushIDInt"
	}
}

local function getcimguiname(stname,funcname)
	local pre = (stname == "ImGui") and "ig" or stname.."_"
	return pre..funcname
end
local function getcimguiname_overload(stname,funcname,signature)
	local cname = getcimguiname(stname,funcname)
	local ov_cname = cimgui_overloads[cname] and cimgui_overloads[cname][signature] --or cname
	return ov_cname
end

cdefs = {}

location_re = '^# %d+ "([^"]*)"'
cimpath_re = '^(.*[\\/])(imgui)%.h$' 
define_re = "^#define%s+([^%s]+)%s+([^%s]+)$"
--function_re = "([^()]+%w%b();)"
function_re = "(%a*%w+%b())" --"(%a*%w+%s+%w+%b())"
struct_re = "^struct%s+([^%s;]+)$"
local struct_closed_re = "^struct%s+([^%s]+);$"
local struct_closing_re = "};"
local struct_op_close_re = "%b{}"
local namespace_re = "namespace ([^%s]+)"
local namespace_closing_re = "^}"
function_closed_re = "[;}]$"
function_closing_re = "}"

number_re = "^-?[0-9]+$"   
hex_re = "0x[0-9a-fA-F]+$"

local in_imgui = false
local in_function = false
in_namespace = false
local structnames = {}
local stname = ""
local defsT = {}
for line in io.lines() do
repeat -- simulate continue with break

	--print(line)
	line = clean_spaces(line)
	if #line == 0 then break end
	-- Is this a preprocessor statement?
	if line:sub(1,1) == "#" then
		-- Is this a location pragma?
		local location_match = line:match(location_re)
		if location_match then
			--print("location_match",line)
			-- If we are transitioning to a header we need to parse, set the flag
			local cimpath_match,aaa = location_match:match(cimpath_re)
			in_imgui = (cimpath_match ~= nil)
			--if in_gl then print(aaa) end
			break
		end
		
	
	elseif in_imgui then
		--print(line)
		line = line:gsub("%S+",{class="struct",mutable=""}) --class -> struct
		if in_function then 
            if line:match(function_closing_re) then
                in_function = false
            end
            break --discard
        end
		if line:match(function_re) and not line:match("typedef.*%b().*%b().*") then
            -- function and functypedef
            if not line:match(function_closed_re) then
                in_function = true
            end
		end
		if line:match(namespace_re) then
			in_namespace = true
			stname = line:match(namespace_re)
		end
		if in_namespace then
			if line:match(namespace_closing_re) then
				in_namespace = false
				stname = ""
			end
		end
		structnames[#structnames + 1] = line:match(struct_re) 
		if #structnames > 0 then
			if line:match(struct_closing_re) and not line:match(struct_op_close_re) then
				structnames[#structnames] = nil
			end
			stname = structnames[#structnames] or ""
		end
		--print("pre func re:",line)
		local func = line:match(function_re)
		if func and not in_function and not line:match("typedef.*%b().*%b().*") then--not line:match("typedef.*%b().*%b().*") then
			--print(2,line)
			
			if stname~="ImVector" and not line:match("operator") then
			
				--clean implemetation
				line = line:gsub("%s*%b{}","")
				--clean attribute
				line = line:gsub("%s*__attribute__%b()","")
				
				local ret = line:match("([^%(%)]+)[%s%*]~?[_%w]+(%b())") --"(^.+)(%w+)(%b())"
				local funcname, args = line:match("(~?[_%w]+)(%b())")
				
				local argscsinpars = args:gsub("(=[^,%(%)]*)(%b())","%1")
				argscsinpars = argscsinpars:gsub("(=[^,%(%)]*)([,%)])","%2")
				argscsinpars = argscsinpars:gsub("&","")
				--print(funcname,ret,args,argscsinpars)
				local signature = argscsinpars:gsub("([%w%s%*_]+)%s[%w_]+%s*([,%)])","%1%2")
				signature = signature:gsub("%s*([,%)])","%1")
				signature = signature:gsub(",%s*",",")
			    local call_args = argscsinpars:gsub("[^%(].-([%w_]+)%s*([,%)])","%1%2")
				
				--if line:match(".*%b()%b().*") then print("bb:",line);print("b2:",ret,funcname,args) end
				if not ret then --must be constructors
					if not (stname == funcname or "~"..stname==funcname) then --break end
					print("bb:",line);
					print("b2:",ret,stname,funcname,args)
					break --are function defs
					end
				end
				
				--local cimguiname = getcimguiname_overload(stname,funcname,signature)
				local cimguiname = getcimguiname(stname,funcname)
				table.insert(cdefs,{stname=stname,funcname=funcname,args=args,argsc=argscsinpars,signature=signature,cimguiname=cimguiname,call_args=call_args,ret =ret})

				defsT[cimguiname] = defsT[cimguiname] or {}
				table.insert(defsT[cimguiname],{})
				local defT = defsT[cimguiname][#defsT[cimguiname]] 
				--for k,def in args:gmatch("([%w%s]+)=([%w%(%)%s,]+)[,%)]") do
				defT.defaults = {}
				for k,def in args:gmatch("([%w%s%*]+)=([%w%(%)%s,%*]+)[,%)]") do
					defT.defaults[k]=def
					--print(k, def)
				end
				defT.cimguiname = cimguiname
				defT.stname = stname
				defT.funcname = funcname
				defT.args=argscsinpars
				defT.signature = signature
				defT.call_args = call_args
				if ret then
					defT.ret = ret:gsub("&","*")
					defT.retref = ret:match("&")
				end
				defsT[cimguiname][signature] = defT

			end
		end

	end

until true
end


--[[
for s in str:gsub("(%[.-%])",
                  function(x)
                    return x:gsub("%s+", "\0") 
                  end)
            :gmatch "%S+"
do
  print( (s:gsub("%z+", " ")) )
end
--]]

local alltypes = {}
local function get_types(v)
	for i,t in ipairs(v) do
		local signature = t.signature:sub(2,-2) -- without parenthesis
		for typec in signature:gsub("(%(.-%))", function(x) return x:gsub(",","\0") end):gmatch(".-([^,]+),?") do
			local key = typec:gsub("%z+", ",")
			alltypes[key] = true
		end
	end
end

local function name_overloadsAlgo(v)
	local aa = {}
	local bb = {}
	local done = {}
	local maxnum = 0
	for i,t in ipairs(v) do
		bb[i] = ""
		local signature = t.signature:sub(2,-2) -- without parenthesis
		aa[i] = {}
		local num = 1
		--for typec in t.signature:gmatch(".-([^,%(%s]+)[,%)]") do
		--for typec in t.signature:gmatch(".-([^,%(]+)[,%)]") do
		--for typec in signature:gmatch(".-([^,]+),?") do
		for typec in signature:gsub("(%(.-%))", function(x) return x:gsub(",","\0") end):gmatch(".-([^,]+),?") do
			--typec = typec:gsub
			aa[i][num] = typec:gsub("%z+", ",")
			num = num + 1
		end
		num = num - 1
		maxnum = (num > maxnum) and num or maxnum
	end
	
	for l=1,maxnum do
		local keys = {}
		local diferent = true
		local equal = true
		for i=1,#v do
			aa[i][l] = aa[i][l] or "nil"
			keys[aa[i][l]] = 1 + (aa[i][l] and keys[aa[i][l]] or 0)
			if not done[i] then
			for j=i+1,#v do
				if not done[j] then
				if aa[i][l] == aa[j][l] then
					diferent = false
				else
					equal = false
				end
				end
			end
			end
		end
		--if not diferent then assert(#keys == 1) end
		if not equal then -- not all the same
			--prtable(keys)
			for i=1,#v do
				if not done[i] then
					bb[i] = bb[i]..(aa[i][l]=="nil" and "" or aa[i][l])
					if keys[aa[i][l]] == 1 then
						done[i] = true
					end
				end
			end
			--for i=1,#v do
			--	bb[i] = bb[i]..tostring(aa[i][l])
			--end
		end
	end
	return aa,bb
end
local function typetoStr(typ)
	typ = typ:gsub("[^%(%)]+%(%*?(.+)%).+","%1") -- funcs
	typ = typ:gsub("[%w_]+%[(%d*)%]","arr%1")
	typ = typ:gsub("%*","Ptr")
	typ = typ:gsub("void","")
	typ = typ:gsub("unsigned%s","u")
	typ = typ:gsub("const%s","")--"c")
	typ = typ:gsub("%s+","_")
	typ = typ:gsub("charPtr","Str")
	typ = typ:gsub("int","Int")
	typ = typ:gsub("bool","Bool")
	typ = typ:gsub("float","Float")
	typ = typ:gsub("uInt","Uint")
	typ = typ:gsub("ImGui","")
	typ = typ:gsub("Im","")
	typ = typ:gsub("[<>]","")
	return typ
end
local numoverloaded = 0
print"overloading"
for k,v in pairs(defsT) do
	get_types(v)
	if #v > 1 then
		numoverloaded = numoverloaded + #v
		print(k,#v)
		local typesc,post = name_overloadsAlgo(v)
		for i,t in ipairs(v) do
			t.ov_cimguiname = getcimguiname_overload(t.stname,t.funcname,t.signature) or k..typetoStr(post[i])
			print(i,t.signature,t.ret,t.ov_cimguiname)--post[i],typetoStr(post[i]))
			--prtable(typesc[i])
		end
	end
end
print(numoverloaded, "overloaded")
print"//-------------------------------------------------------------------------------------"

for k,v in pairs(alltypes) do print(k, typetoStr(k) ) end
print"//-------------------------------------------------------------------------------------"

for i,t in ipairs(cdefs) do
	print(t.cimguiname,"   ",t.funcname,"\t",t.signature,"\t",t.args,"\t",t.argsc,"\t",t.call_args,"\t",t.ret) --,"\n")
end
print"//-------------------------------------------------------------------------------------"
--[[
print"//constructors------------------------------------------------------------------"
for i,t in ipairs(cdefs) do
	if not t.ret then
	print(t.cimguiname,"\t",t.signature,"\t",t.args,"\t",t.argsc,"\t",t.call_args,"\t",t.ret) --,"\n")
	end
end
--]]
local hfile = io.open("./auto_funcs.h","w")
for _,t in ipairs(cdefs) do
	local cimf = defsT[t.cimguiname]
	local def = cimf[t.signature]
	if def.ret then --not constructor
		if def.stname == "ImGui" then
			hfile:write("CIMGUI_API"," ",def.ret," ",def.ov_cimguiname or def.cimguiname,def.args,";\n")
		else
			local args = def.args:gsub("^%(","("..def.stname.."* self,")
			hfile:write("CIMGUI_API"," ",def.ret," ",def.ov_cimguiname or def.cimguiname,args,";\n")
		end
	end
end
hfile:close()
print"//-------------------------------------------------------------------------------------"
local cppfile = io.open("./auto_funcs.cpp","w")
for _,t in ipairs(cdefs) do
	local cimf = defsT[t.cimguiname]
	--for i,def in ipairs(cimf) do
	--prtable(cimf)
	local def = cimf[t.signature]
	if def.ret then --not constructor
		if def.stname == "ImGui" then
			cppfile:write("CIMGUI_API"," ",def.ret," ",def.ov_cimguiname or def.cimguiname,def.args,"\n")
			cppfile:write("{\n")
			cppfile:write("    return ImGui::",def.funcname,def.call_args,";\n")
			cppfile:write("}\n")
		else
			local args = def.args:gsub("^%(","("..def.stname.."* self,")
			cppfile:write("CIMGUI_API"," ",def.ret," ",def.ov_cimguiname or def.cimguiname,args,"\n")
			cppfile:write("{\n")
			cppfile:write("    return self->",def.funcname,def.call_args,";\n")
			cppfile:write("}\n")
		end
	end
	--end
end
cppfile:close()
