--------------------------------------------------------------------------
--script for auto_funcs.h and auto_funcs.cpp generation
--------------------------------------------------------------------------

--------------------------------------------------------------------------
--this table has the functions to be skipped in generation
--------------------------------------------------------------------------
local cimgui_manuals = {
	igLogText = true,
	ImGuiTextBuffer_appendf = true,
}
--------------------------------------------------------------------------
--this table is a dictionary to force a naming of function overloading (instead of algorythmic generated)
--first level is cimguiname without postfix, second level is the signature of the function, value is the
--desired name
---------------------------------------------------------------------------
local cimgui_overloads = {
	igPushID = {
		--["(const char*)"] = 			"igPushIDStr",
		["(const char*,const char*)"] = "igPushIDRange",
		--["(const void*)"] = 			"igPushIDPtr",
		--["(int)"] = 					"igPushIDInt"
	},
	igCollapsingHeader = {
		["(const char*,ImGuiTreeNodeFlags)"] =		"igCollapsingHeader"
	}
}
--------------------------------------------------------------------------
--helper functions
--------------------------------------------------------------------------
--iterates lines from a gcc -E in a specific location
local function location(file,locpath)
	local location_re = '^# %d+ "([^"]*)"'
	local path_re = '^(.*[\\/])('..locpath..')%.h$' 
	local in_location = false
	local function location_it()
		repeat
			local line = file:read"*l"
			if not line then return nil end
			if #line == 0 then --nothing
			elseif line:sub(1,1) == "#" then
				-- Is this a location pragma?
				local location_match = line:match(location_re)
				if location_match then
					-- If we are transitioning to a header we need to parse, set the flag
					local path_match,aaa = location_match:match(path_re)
					in_location = (path_match ~= nil)
				end
			elseif in_location then
				return line
			end
		until false
	end
	return location_it
end


local function strip(cad)
	return cad:gsub("^%s*(.-)%s*$","%1") --remove initial and final spaces
end
local function clean_spaces(cad)
	cad = strip(cad)
	--cad = cad:gsub("%s+","%s") --not more than one space
	cad = cad:gsub("%s*([%(%),=])%s*","%1") --not spaces with ( , )
	return cad
end

local function get_manuals(def)
	return cimgui_manuals[def.ov_cimguiname] or cimgui_manuals[def.cimguiname]
end

local function getcimguiname(stname,funcname)
	local pre = (stname == "ImGui") and "ig" or stname.."_"
	return pre..funcname
end

local function getcimguiname_overload(stname,funcname,signature)
	local cname = getcimguiname(stname,funcname)
	local ov_cname = cimgui_overloads[cname] and cimgui_overloads[cname][signature] --or cname
	return ov_cname
end


local function struct_parser()
	local function_re = "(%a*%w+%b())" --"(%a*%w+%s+%w+%b())"
	local function_closing_re = "}"
	local function_closed_re = "[;}]$"
	local operator_re = "operator.-%b()"
	local functype_re = "(%(%*)[%w_]+(%)%([^%(%)]*%))"
	
	local in_functionst = false
	local structcdefs = {}
	local STP = {}
	STP.lines = structcdefs
	function STP.insert(line)
		
		--if in_function discard
        if in_functionst then 
            if line:match(function_closing_re) then
                in_functionst = false
            end
            return
        end
        
        if (line:match(function_re) or line:match(operator_re)) and not line:match("typedef.*%b().*%b().*") 
		and not line:match(functype_re) then
            if not line:match(function_closed_re) then
                in_functionst = true
            end
        elseif line:match("template") then
            --nothing
        elseif line:match("public") then
            --nothing
        else
            local linea = line:gsub("%S+",{class="struct",mutable=""})
            linea = linea:gsub("(%b<>)","/%*%1%*/") --comment template parameters
            table.insert(structcdefs,linea)
        end
		return 
	end
	return STP
end

local function typetoStr(typ)
	--typ = typ:gsub("[^%(%)]+%(%*?(.+)%).+","%1") -- funcs
	typ = typ:gsub("[^%(%)]+%(%*?(.+)%).+","FnPtr")
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
		if not equal then -- not all the same
			for i=1,#v do
				if not done[i] then
					bb[i] = bb[i]..(aa[i][l]=="nil" and "" or aa[i][l])
					if keys[aa[i][l]] == 1 then
						done[i] = true
					end
				end
			end
		end
	end
	return aa,bb
end

local function func_parser()
	local function_closing_re = "}"
	local function_re = "(%a*%w+%b())" --"(%a*%w+%s+%w+%b())"
	local function_closed_re = "[;}]$"
	local namespace_re = "namespace ([^%s]+)"
	local namespace_closing_re = "^}"
	local struct_re = "^struct%s+([^%s;]+)$"
	local struct_closing_re = "};"
	local struct_op_close_re = "%b{}"
	local functype_re = "^%s*[%w%s]+(%(%*)[%w_]+(%)%([^%(%)]*%))"
	
	local in_function = false
	local in_namespace = false
	local cdefs = {}
	local structnames = {}
	local embeded_structs = {}
	local stname = ""
	local defsT = {}
	local ImVector_templates = {}
	
	
	local FP = {}
	FP.cdefs = cdefs
	FP.embeded_structs = embeded_structs
	FP.defsT = defsT
	FP.ImVector_templates = ImVector_templates
	function FP.insert(line)
		line = clean_spaces(line)
		if line:match"template" then return end
		line = line:gsub("%S+",{class="struct",mutable=""}) --class -> struct
		
		if in_function then 
            if line:match(function_closing_re) then
                in_function = false
            end
            return --discard
        end
		if line:match(function_re) and not line:match("typedef.*%b().*%b().*") then
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
			if #structnames > 1 then
				local embeded_name = table.concat(structnames,"::")
				embeded_structs[stname] = embeded_name
			end
		end
		local func = line:match(function_re)
		if func and not in_function and not line:match("typedef.*%b().*%b().*") 
		and not line:match(functype_re) 
		then
			--if line:match(functype_re) then print("ft",line) end
			if stname~="ImVector" 
			--and stname~="GlyphRangesBuilder" and stname~="CustomRect"  and stname~="TextRange" and stname~="Pair"
			and not line:match("operator") then
			
				--clean implemetation
				line = line:gsub("%s*%b{}","")
				--clean attribute
				line = line:gsub("%s*__attribute__%b()","")
				--clean static
				line = line:gsub("static","")
				
				local ret = line:match("([^%(%)]+[%*%s])%s?~?[_%w]+%b()")
				local funcname, args = line:match("(~?[_%w]+)(%b())")
				
				local argscsinpars = args:gsub("(=[^,%(%)]*)(%b())","%1")
				argscsinpars = argscsinpars:gsub("(=[^,%(%)]*)([,%)])","%2")
				argscsinpars = argscsinpars:gsub("&","")
				
				local template = argscsinpars:match("ImVector<([%w_]+)>")
				if template then
					ImVector_templates[template] = true
				end
				
				argscsinpars = argscsinpars:gsub("<([%w_]+)>","_%1") --ImVector
				
				local signature = argscsinpars:gsub("([%w%s%*_]+)%s[%w_]+%s*([,%)])","%1%2")
				signature = signature:gsub("%s*([,%)])","%1") --space before , and )
				signature = signature:gsub(",%s*",",")--space after ,
				signature = signature:gsub("([%w_]+)%s[%w_]+(%[%d*%])","%1%2") -- float[2]
				signature = signature:gsub("(%(%*)[%w_]+(%)%([^%(%)]*%))","%1%2") --func defs
				
				local call_args = argscsinpars:gsub("([%w_]+%s[%w_]+)%[%d*%]","%1") --float[2]
				call_args = call_args:gsub("%(%*([%w_]+)%)%([^%(%)]*%)"," %1") --func type
				call_args = call_args:gsub("[^%(].-([%w_]+)%s*([,%)])","%1%2")
				
				if not ret then --must be constructors
					if not (stname == funcname or "~"..stname==funcname) then --break end
						print("false constructor:",line);
						print("b2:",ret,stname,funcname,args)
						return --are function defs
					end
				end
				
				local cimguiname = getcimguiname(stname,funcname)
				table.insert(cdefs,{stname=stname,funcname=funcname,args=args,argsc=argscsinpars,signature=signature,cimguiname=cimguiname,call_args=call_args,ret =ret})

				defsT[cimguiname] = defsT[cimguiname] or {}
				table.insert(defsT[cimguiname],{})
				local defT = defsT[cimguiname][#defsT[cimguiname]] 
				defT.defaults = {}
				for k,def in args:gmatch("([%w%s%*]+)=([%w%(%)%s,%*]+)[,%)]") do
					defT.defaults[k]=def
				end
				defT.cimguiname = cimguiname
				defT.stname = stname
				defT.funcname = funcname
				defT.args=argscsinpars
				defT.signature = signature
				defT.call_args = call_args
				defT.isvararg = signature:match("%.%.%.%)$")
				if ret then
					defT.ret = ret:gsub("&","*")
					defT.retref = ret:match("&")
				end
				defsT[cimguiname][signature] = defT

			end
		end
	end
	FP.alltypes = {}
	local function get_types(v)
		for i,t in ipairs(v) do
			local signature = t.signature:sub(2,-2) -- without parenthesis
			for typec in signature:gsub("(%(.-%))", function(x) return x:gsub(",","\0") end):gmatch(".-([^,]+),?") do
				local key = typec:gsub("%z+", ",")
				FP.alltypes[key] = true
			end
		end
	end
	function FP:dump_alltypes()
		for k,v in pairs(self.alltypes) do print(k, typetoStr(k) ) end
	end
	function FP:compute_overloads()
		local numoverloaded = 0
		FP.alltypes = {}
		print"----------------overloadings---------------------------"
		for k,v in pairs(FP.defsT) do
			get_types(v)
			if #v > 1 then
				numoverloaded = numoverloaded + #v
				print(k,#v)
				local typesc,post = name_overloadsAlgo(v)
				for i,t in ipairs(v) do
					t.ov_cimguiname = getcimguiname_overload(t.stname,t.funcname,t.signature) or k..typetoStr(post[i])
					print(i,t.signature,t.ret,t.ov_cimguiname,post[i])--,typetoStr(post[i]))
					--prtable(typesc[i])
				end
			end
		end
		print(numoverloaded, "overloaded")
	end
	return FP
end

local function gen_structs_and_enums(cdefs)
	local function_closing_re = "}"
	local namespace_re = "namespace"
	local in_namespace = false
	local struct_re = "^%s*struct%s+([^%s;]+)$"
	local struct_closed_re = "^%s*struct%s+([^%s]+);$"
	local struct_closing_re = "};"
	local struct_op_close_re = "%b{}"
	local structnames = {}
	local innerstructs = {}
	--local hfile = io.open("./imgui_structs2.h","w")
	local outtab = {}
	-- Output the file
    table.insert(outtab,"/////////////// BEGIN AUTOGENERATED SEGMENT\n")
    --table.insert(outtab,"#ifndef IMGUI_STRUCTS_INCLUDED\n")
    --table.insert(outtab,"#define IMGUI_STRUCTS_INCLUDED\n")
    
    for i,line in ipairs(cdefs) do
    repeat -- simulating continue with break
        
        if line:match(namespace_re) then
            in_namespace = true
        end
        local structbegin = line:match(struct_re)
        if structbegin then
            structnames[#structnames + 1] = structbegin
            if #structnames < 2 and structbegin~= "ImVector" then --not inner and not ImVector
                table.insert(outtab,line.."\n")
                break
            end
        end
        
        if structnames[#structnames] == "ImVector" then
            if line:match(struct_closing_re) then
                table.insert(outtab,[[struct ImVector
{
    int Size;
    int Capacity;
    void* Data;
};
typedef struct ImVector ImVector;]])
                structnames[#structnames] = nil
            end
            break -- dont write
        end
        
        if in_namespace then
            if line:match(function_closing_re) then
                in_namespace = false
            end
            break -- dont write anything inside
        end
        
        if #structnames < 2 then -- not inner
            if (#structnames > 0) then
                if line:match("typedef") then --dont allow inner typedefs
                    break
                elseif not line:match("^{$") and not line:match(struct_closing_re) then --avoid tab { and };
                    --line = "    "..line
                end
            end
            table.insert(outtab,line.."\n")
            local struct_closed_name = line:match(struct_closed_re)
            if struct_closed_name then
                table.insert(outtab,"typedef struct "..struct_closed_name.." "..struct_closed_name..";\n")
            end
        end

        if #structnames > 0 then
            if #structnames > 1 then --inner structs
                innerstructs[structnames[#structnames]] = innerstructs[structnames[#structnames]] or {}
                local st = innerstructs[structnames[#structnames]]
                -- if not line:match("struct") and not line:match("^{$") and not line:match(struct_closing_re) then --avoid tab in struct { and };
                    --line = "    "..line
                -- end
                st[#st + 1] = line
                if line:match(struct_closing_re) and not line:match(struct_op_close_re) then
                    local structname = structnames[#structnames]
                    st[#st + 1] = string.format("typedef struct %s %s;\n",structname,structname)
                    structnames[#structnames] = nil
                end
            elseif line:match(struct_closing_re) and not line:match(struct_op_close_re) then
                local structname = structnames[#structnames]
                table.insert(outtab,"typedef struct "..structname.." "..structname..";\n")
                structnames[#structnames] = nil
            end
        end
        

    until true
    end
    for k,v in pairs(innerstructs) do 
        for i,line in ipairs(v) do
            table.insert(outtab,line.."\n") 
        end
    end
    --table.insert(outtab,"#endif //IMGUI_STRUCTS_INCLUDED\n")
    table.insert(outtab,"//////////////// END AUTOGENERATED SEGMENT \n")
	--hfile:close()
	return outtab
end

local function func_header_generate(FP)
	--local hfile = io.open("./auto_funcs2.h","w")
	local outtab = {}
	table.insert(outtab,"#ifndef CIMGUI_DEFINE_ENUMS_AND_STRUCTS\n")
	for k,v in pairs(FP.embeded_structs) do
		--print(k,v)
		table.insert(outtab,"typedef "..v.." "..k..";\n")
	end
	for k,v in pairs(FP.ImVector_templates) do
		table.insert(outtab,"typedef ImVector<"..k.."> ImVector_"..k..";\n")
	end
	table.insert(outtab,"#else //CIMGUI_DEFINE_ENUMS_AND_STRUCTS\n")
	for k,v in pairs(FP.ImVector_templates) do
		table.insert(outtab,"typedef ImVector ImVector_"..k..";\n")
	end
	table.insert(outtab,"#endif //CIMGUI_DEFINE_ENUMS_AND_STRUCTS\n")
	for _,t in ipairs(FP.cdefs) do
		local cimf = FP.defsT[t.cimguiname]
		local def = cimf[t.signature]
		local manual = get_manuals(def)
		if not manual and def.ret then --not constructor
			if def.stname == "ImGui" then
				table.insert(outtab,"CIMGUI_API".." "..def.ret.." "..(def.ov_cimguiname or def.cimguiname)..def.args..";\n")
			else
				local empty = def.args:match("^%(%)") --no args
				--local imgui_stname = embeded_structs[def.stname] or def.stname
				local imgui_stname = def.stname
				local args = def.args:gsub("^%(","("..imgui_stname.."* self"..(empty and "" or ","))
				table.insert(outtab,"CIMGUI_API".." "..def.ret.." "..(def.ov_cimguiname or def.cimguiname)..args..";\n")
			end
		end
	end
	--hfile:close()
	return outtab
end
local function func_implementation(FP)
	--local cppfile = io.open("./auto_funcs2.cpp","w")
	local outtab = {}
	for _,t in ipairs(FP.cdefs) do
		local cimf = FP.defsT[t.cimguiname]
		local def = cimf[t.signature]
		local manual = get_manuals(def)
		if not manual and def.ret then --not constructor
			local ptret = def.retref and "&" or ""
			-- local castret = def.ret:gsub("[^%s]+",function(x)
					-- local y = x:gsub("%*","")
					-- local typ = embeded_structs[y]
					-- if typ then return "("..x..")" else return "" end
				-- end)
				local castret = ""
			if def.stname == "ImGui" then
				if def.isvararg then
					local call_args = def.call_args:gsub("%.%.%.","args")
					table.insert(outtab,"CIMGUI_API".." "..def.ret.." "..(def.ov_cimguiname or def.cimguiname)..def.args.."\n")
					table.insert(outtab,"{\n")
					table.insert(outtab,"    va_list args;\n")
					table.insert(outtab,"    va_start(args, fmt);\n")
					table.insert(outtab,"    ImGui::"..def.funcname.."V"..call_args..";\n")
					table.insert(outtab,"    va_end(args);\n")
					--cppfile:write("    return ImGui::",def.funcname,def.call_args,";\n")
					table.insert(outtab,"}\n")
				else
					table.insert(outtab,"CIMGUI_API".." "..def.ret.." "..(def.ov_cimguiname or def.cimguiname)..def.args.."\n")
					table.insert(outtab,"{\n")
					table.insert(outtab,"    return "..castret..ptret.."ImGui::"..def.funcname..def.call_args..";\n")
					table.insert(outtab,"}\n")
				end
			else
				local empty = def.args:match("^%(%)") --no args
				--local imgui_stname = embeded_structs[def.stname] or def.stname
				local imgui_stname = def.stname
				local args = def.args:gsub("^%(","("..imgui_stname.."* self"..(empty and "" or ","))
				if def.isvararg then
					local call_args = def.call_args:gsub("%.%.%.","args")
					table.insert(outtab,"CIMGUI_API".." "..def.ret.." "..(def.ov_cimguiname or def.cimguiname)..args.."\n")
					table.insert(outtab,"{\n")
					table.insert(outtab,"    va_list args;\n")
					table.insert(outtab,"    va_start(args, fmt);\n")
					table.insert(outtab,"    self->"..def.funcname.."V"..call_args..";\n")
					table.insert(outtab,"    va_end(args);\n")
					--cppfile:write("    return self->",def.funcname,def.call_args,";\n")
					table.insert(outtab,"}\n")
				else
					table.insert(outtab,"CIMGUI_API".." "..def.ret.." "..(def.ov_cimguiname or def.cimguiname)..args.."\n")
					table.insert(outtab,"{\n")
					table.insert(outtab,"    return "..castret..ptret.."self->"..def.funcname..def.call_args..";\n")
					table.insert(outtab,"}\n")
				end
			end
		end
	end
	--cppfile:close()
	return outtab
end
--------------------------------------------------------
-----------------------------do it----------------------
--------------------------------------------------------
local STP = struct_parser()
local FP = func_parser()

for line in location(io.input(),"imgui") do
	STP.insert(line)
	FP.insert(line)
end

FP:compute_overloads()

local cstructs = gen_structs_and_enums(STP.lines)
local cfuncs = func_header_generate(FP)

--merge it in cimgui_template.h to cimgui.h
local hfile = io.open("./cimgui_template.h","r")
local hstrfile = hfile:read"*a"
hfile:close()
hstrfile = hstrfile:gsub([[#include "imgui_structs%.h"]],table.concat(cstructs))
hstrfile = hstrfile:gsub([[#include "auto_funcs%.h"]],table.concat(cfuncs))
local outfile = io.open("./cimgui.h","w")
outfile:write(hstrfile)
outfile:close()

local cimplem = func_implementation(FP)

--merge it in cimgui_template.cpp to cimgui.cpp
local hfile = io.open("./cimgui_template.cpp","r")
local hstrfile = hfile:read"*a"
hfile:close()
hstrfile = hstrfile:gsub([[#include "auto_funcs%.cpp"]],table.concat(cimplem))
local outfile = io.open("./cimgui.cpp","w")
outfile:write(hstrfile)
outfile:close()



---dump infos-----------------------------------------------------------------------
------------------------------------------------------------------------------------
print"//-------alltypes--------------------------------------------------------------------"
FP:dump_alltypes()
print"//embeded_structs---------------------------------------------------------------------------"
for k,v in pairs(FP.embeded_structs) do
	--print(k,v)
	io.write("typedef ",v," ",k,";\n")
end
print"//templates---------------------------------------------------------------------------"
for k,v in pairs(FP.ImVector_templates) do
	--print(k,v)
	io.write("typedef ImVector<",k,"> ImVector_",k,";\n")
end

print"//constructors------------------------------------------------------------------"
for i,t in ipairs(FP.cdefs) do
	if not t.ret then
	print(t.cimguiname,"\t",t.signature,"\t",t.args,"\t",t.argsc,"\t",t.call_args,"\t",t.ret)
	end
end
print"//-------------------------------------------------------------------------------------"
for i,t in ipairs(FP.cdefs) do
	--print(t.cimguiname,"   ",t.funcname,"\t",t.signature,"\t",t.args,"\t",t.argsc,"\t",t.call_args,"\t",t.ret) 
end
---------------------------------------------------------------------------------------------



