--------------------------------------------------------------------------
--script for auto_funcs.h and auto_funcs.cpp generation
--expects Lua 5.1 or luajit
--------------------------------------------------------------------------
assert(_VERSION=='Lua 5.1',"Must use LuaJIT or Lua5.1")
local script_args = {...}

--test gcc present
local HAVE_GCC
local pipe,err = io.popen("gcc --version","r")
if pipe then
    local str = pipe:read"*a"
    print(str)
    pipe:close()
    if str=="" then
        HAVE_GCC = false
    else
        HAVE_GCC = true
    end
else
    HAVE_GCC = false
    print(err)
end
print("HAVE_GCC",HAVE_GCC)
--get implementations
local implementations = {}
for i=1,#script_args do table.insert(implementations,script_args[i]) end

--------------------------------------------------------------------------
--this table has the functions to be skipped in generation
--------------------------------------------------------------------------
local cimgui_manuals = {
    igLogText = true,
    ImGuiTextBuffer_appendf = true,
	igColorConvertRGBtoHSV = true,
	igColorConvertHSVtoRGB = true
}
--------------------------------------------------------------------------
--this table is a dictionary to force a naming of function overloading (instead of algorythmic generated)
--first level is cimguiname without postfix, second level is the signature of the function, value is the
--desired name
---------------------------------------------------------------------------
local cimgui_overloads = {
    igPushID = {
        --["(const char*)"] =           "igPushIDStr",
        ["(const char*,const char*)"] = "igPushIDRange",
        --["(const void*)"] =           "igPushIDPtr",
        --["(int)"] =                   "igPushIDInt"
    },
    ImDrawList_AddText = {
        ["(const ImVec2,ImU32,const char*,const char*)"] = "ImDrawList_AddText",
    },
    igGetColorU32 = {
        ["(ImGuiCol,float)"] = "igGetColorU32",
    },
    igCollapsingHeader = {
        ["(const char*,ImGuiTreeNodeFlags)"] =  "igCollapsingHeader",
    },
    igCombo = {
        ["(const char*,int*,const char* const[],int,int)"] = "igCombo",
    },
    igPlotLines = {
        ["(const char*,const float*,int,int,const char*,float,float,ImVec2,int)"] = "igPlotLines",
    },
    igBeginChild = {
        ["(const char*,const ImVec2,bool,ImGuiWindowFlags)"] = "igBeginChild",
    },
    igSelectable = {
        ["(const char*,bool,ImGuiSelectableFlags,const ImVec2)"] = "igSelectable"
    },
    igPushStyleColor = {
        ["(ImGuiCol,const ImVec4)"] = "igPushStyleColor"
    }
}
--------------------------------------------------------------------------
--helper functions
--------------------------------------------------------------------------
--iterates lines from a .h file and discards between #if.. and #endif
local function filelines(file)
    local iflevels = {}
    local function location_it()
        repeat
            local line = file:read"*l"
            if not line then return nil end
            if line:sub(1,1) == "#" then
                if line:match("#if") then 
                    iflevels[#iflevels +1 ] = true
                elseif line:match("#endif") then
                    iflevels[#iflevels] = nil
                end
                -- skip
            elseif #iflevels == 0 then
                -- drop IMGUI_APIX
                line = line:gsub("IMGUI_IMPL_API","")
                -- drop IMGUI_API
                line = line:gsub("IMGUI_API","")
                return line
            end
        until false
    end
    return location_it
end
--iterates lines from a gcc -E in a specific location
local function location(file,locpathT)
    local location_re = '^# %d+ "([^"]*)"'
    local path_reT = {}
    for i,locpath in ipairs(locpathT) do
        table.insert(path_reT,'^(.*[\\/])('..locpath..')%.h$')
    end
    local in_location = false
    local which_location = ""
    local function location_it()
        repeat
            local line = file:read"*l"
            if not line then return nil end
            if line:sub(1,1) == "#" then
                -- Is this a location pragma?
                local location_match = line:match(location_re)
                if location_match then
                    in_location = false
                    for i,path_re in ipairs(path_reT) do
                        if location_match:match(path_re) then 
                            in_location = true;
                            which_location = locpathT[i]
                            break 
                        end
                    end
                end
            elseif in_location then
                return line, which_location
            end
        until false
    end
    return location_it
end
------serializeTable("anyname",table) gives a string that recreates the table with dofile(generated_string)
local function serializeTable(name, value, saved)
    
    local function basicSerialize (o)
        if type(o) == "number" or type(o)=="boolean" then
            return tostring(o)
        elseif type(o) == "string" then
            return string.format("%q", o)
        else
            return "nil"
        end
    end
    
    local string_table = {}
    if not saved then 
        table.insert(string_table, "local "..name.." = ") 
    else
        table.insert(string_table, name.." = ") 
    end
    
    saved = saved or {}       -- initial value
    
    if type(value) == "number" or type(value) == "string" or type(value)=="boolean" then
        table.insert(string_table,basicSerialize(value).."\n")
    elseif type(value) == "table" then
        if saved[value] then    -- value already saved?
            table.insert(string_table,saved[value].."\n")          
        else
            saved[value] = name   -- save name for next time
            table.insert(string_table, "{}\n")          
            for k,v in pairs(value) do      -- save its fields
                local fieldname = string.format("%s[%s]", name,basicSerialize(k))
                table.insert(string_table, serializeTable(fieldname, v, saved))
            end
        end
    --else
        --error("cannot save a " .. type(value))
    end
    
    return table.concat(string_table)
end
--merge tables
function mergeT(t1,t2)
    for k,v in pairs(t2) do
        t1[k] = v
    end
    return t1
end
function strsplit(str, pat)
    local t = {} 
    local fpat = "(.-)" .. pat
    local last_end = 1
    local s, e, cap = str:find(fpat, 1)
    while s do
        table.insert(t,cap)
        last_end = e+1
        s, e, cap = str:find(fpat, last_end)
    end
    if last_end <= #str then
        cap = str:sub(last_end)
        table.insert(t, cap)
    elseif str:sub(-1)==pat then
        table.insert(t, "")
    end
    return t
end
local function save_data(filename,...)
    local file = io.open(filename,"w")
    for i=1, select('#', ...) do
        local data = select(i, ...)
        file:write(data)
    end
    file:close()
end

local function strip(cad)
    return cad:gsub("^%s*(.-)%s*$","%1") --remove initial and final spaces
end
local function clean_spaces(cad)
    cad = strip(cad)
    cad = cad:gsub("%s+"," ") --not more than one space
    cad = cad:gsub("%s*([%(%),=])%s*","%1") --not spaces with ( , )
    return cad
end
local function split_comment(line)
    local comment = line:match("(%s*//.*)") or ""
    return line:gsub("%s*//.*",""),comment
end
local function get_manuals(def)
    return cimgui_manuals[def.ov_cimguiname] or cimgui_manuals[def.cimguiname]
end

local function getcimguiname(stname,funcname)
    if #stname == 0 then return funcname end --top level
    local pre = (stname == "ImGui") and "ig" or stname.."_"
    return pre..funcname
end

local function getcimguiname_overload(stname,funcname,signature)
    local cname = getcimguiname(stname,funcname)
    local ov_cname = cimgui_overloads[cname] and cimgui_overloads[cname][signature] --or cname
    return ov_cname
end


local function struct_parser()
    local function_re = "(%a*%w+%s*%b())" --"(%a*%w+%b())" --"(%a*%w+%s+%w+%b())"
    local function_closing_re = "}"
    local function_closed_re = "[;}]$"
    local operator_re = "operator.-%b()"
    local functype_re = "(%(%*)[%w_]+(%)%([^%(%)]*%))"
    local initial_comment_re = [[^%s*//.*]]
    
    local in_functionst = false
    local structcdefs = {}
    local STP = {}
    STP.lines = structcdefs
    function STP.insert(line,comment)
    
        --dont process initial comments but keep it
        if line:match(initial_comment_re) then
            table.insert(structcdefs,line)
            return 
        end
        
        --if in_function discard
        if in_functionst then 
            if line:match(function_closing_re) then
                in_functionst = false
                --print("in function:",line)
            end
            return
        end

        
        
        if (line:match(function_re) or line:match(operator_re)) and not line:match("typedef.*%b().*%b().*") 
        and not line:match(functype_re) then
            if not line:match(function_closed_re) then
                --print("match:",line)
                in_functionst = true
            end
        --else
            --table.insert(structcdefs,linecommented)
        elseif line:match("template") then
            --nothing
        elseif line:match("public:") then
            --nothing
        else
            local linea = line:gsub("%S+",{class="struct",mutable=""})
            linea = linea:gsub("(%b<>)","/*%1*/") --comment template parameters
            table.insert(structcdefs,linea..comment)
            
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
    
    function FP.insert(line,comment,locat)
        
        if line:match"template" then return end
        line = line:gsub("%S+",{class="struct",mutable="",inline=""}) --class -> struct
		line = clean_spaces(line)
        
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
                -- if argscsinpars:match("&") then 
                    -- for arg in argscsinpars:gmatch("[%(,]*([^,%(%)]+)[%),]") do
                        -- if arg:match("&") and not arg:match("const") then
                            -- print(funcname,argscsinpars)
                        -- end
                    -- end
                -- end
                --argscsinpars = argscsinpars:gsub("&","")
                
                local template = argscsinpars:match("ImVector<([%w_]+)>")
                if template then
                    ImVector_templates[template] = true
                end
                
                argscsinpars = argscsinpars:gsub("<([%w_]+)>","_%1") --ImVector
                
                local argsArr = {}
                local functype_re =       "^%s*[%w%s%*]+%(%*[%w_]+%)%([^%(%)]*%)"
                local functype_reex =     "^(%s*[%w%s%*]+)%(%*([%w_]+)%)(%([^%(%)]*%))"
                local functype_arg_rest = "^(%s*[%w%s%*]+%(%*[%w_]+%)%([^%(%)]*%)),*(.*)"
                local rest = argscsinpars:sub(2,-2) --strip ()
                
                while true do
                --local tt = strsplit(rest,",")
                --for ii,arg in ipairs(tt) do
                --for arg in argscsinpars:gmatch("[%(,]*([^,%(%)]+)[%),]") do
                    local type,name,retf,sigf
                    local arg,restt = rest:match(functype_arg_rest)
                    if arg then
                        local t1,namef,t2 = arg:match(functype_reex)
                        type=t1.."(*)"..t2;name=namef
                        retf = t1
                        sigf = t2
                        rest = restt
                    else
                        arg,restt = rest:match(",*([^,%(%)]+),*(.*)")
                        if not arg then break end
                        rest = restt
                        if arg:match("&") and arg:match("const") then
                            arg = arg:gsub("&","")
                        end
                        if arg:match("%.%.%.") then 
                            type="...";name="..."
                        else
                            type,name = arg:match("(.+)%s([^%s]+)")
                        end
                        if not type or not name then 
							print("failure arg detection",funcname,type,name,argscsinpars,arg)
						else
							--float name[2] to float[2] name
							local siz = name:match("(%[%d*%])")
							if siz then
								type = type..siz
								name = name:gsub("(%[%d*%])","")
							end
						end
                    end
                    table.insert(argsArr,{type=type,name=name,ret=retf,signature=sigf})
                    if arg:match("&") and not arg:match("const") then
                        print(funcname,argscsinpars)
                    end
                end
                argscsinpars = argscsinpars:gsub("&","")
                
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
                table.insert(cdefs,{stname=stname,funcname=funcname,args=args,argsc=argscsinpars,signature=signature,cimguiname=cimguiname,call_args=call_args,ret =ret,comment=comment})

                defsT[cimguiname] = defsT[cimguiname] or {}
                table.insert(defsT[cimguiname],{})
                local defT = defsT[cimguiname][#defsT[cimguiname]] 
                defT.defaults = {}
                --for k,def in args:gmatch("([%w%s%*_]+)=([%w_%(%)%s,%*]+)[,%)]") do
                --for k,def in args:gmatch("([%w_]+)=([%w_%(%)%s,%*%.%-]+)[,%)]") do
                for k,def in args:gmatch('([%w_]+)=([%w_%(%)%s,%*%.%-%+%%"]+)[,%)]') do
                    defT.defaults[k]=def
                end
                defT.cimguiname = cimguiname
                defT.stname = stname
                defT.funcname = funcname
                defT.argsoriginal = args
                defT.args=argscsinpars
                defT.signature = signature
                defT.call_args = call_args
                defT.isvararg = signature:match("%.%.%.%)$")
                defT.location = locat
                defT.comment = comment
                defT.argsT = argsArr
				if get_manuals(defT) then
					defT.manual = true
				end
                if ret then
                    defT.ret = clean_spaces(ret:gsub("&","*"))
                    defT.retref = ret:match("&")
					-- if defT.ret=="ImVec2" or defT.ret=="ImVec4" or defT.ret=="ImColor" then
						-- defT.ret = defT.ret.."_Simple"
					-- end
                end
                defsT[cimguiname][signature] = defT
            end
        elseif line=="" and stname~="" then -- not funcdef must be comment
            table.insert(cdefs,{stname=stname,comment=comment})
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
        local strt = {}
        local numoverloaded = 0
        FP.alltypes = {}
        table.insert(strt,"----------------overloadings---------------------------")
        --require"anima.utils"
        for k,v in pairs(FP.defsT) do
            get_types(v)
            if #v > 1 then
                numoverloaded = numoverloaded + #v
                --print(k,#v)
                table.insert(strt,string.format("%s\t%d",k,#v))
                local typesc,post = name_overloadsAlgo(v)
                for i,t in ipairs(v) do
                    --take overloaded name from manual table or algorythm
                    t.ov_cimguiname = getcimguiname_overload(t.stname,t.funcname,t.signature) or k..typetoStr(post[i])
                    --print(i,t.signature,t.ret,t.ov_cimguiname)--,post[i])--,typetoStr(post[i]))
                    table.insert(strt,string.format("%d\t%s\t%s %s",i,t.ret,t.ov_cimguiname,t.signature))
                    --prtable(typesc[i])
                end
            end
        end
        --print(numoverloaded, "overloaded")
        table.insert(strt,string.format("%d overloaded",numoverloaded))
        return table.concat(strt,"\n")
    end
    return FP
end

local function ADDnonUDT(FP)
	--for cimguiname,defs in pairs(defsT) do
	--for i,defT in ipairs(defs) do
	local defsT = FP.defsT
	local newcdefs = {}
	for numcdef,t in ipairs(FP.cdefs) do
        if t.cimguiname then
        local cimf = defsT[t.cimguiname]
        local defT = cimf[t.signature]
		--if UDT return generate nonUDT version
		if defT.ret=="ImVec2" or defT.ret=="ImVec4" or defT.ret=="ImColor" then
			--passing as a pointer arg
			local defT2 = {}
			--first strings
			for k,v in pairs(defT) do
				defT2[k] = v
			end
			--then argsT table
			defT2.argsT = {{type=defT.ret.."*",name="pOut"}}
			for k,v in ipairs(defT.argsT) do
				table.insert(defT2.argsT,{type=v.type,name=v.name})
			end
			local comma = (#defT.argsT > 0) and "," or ""
			defT2.args = "("..defT.ret.." *pOut"..comma..defT.args:sub(2)
			defT2.ret = "void"
			defT2.ov_cimguiname = (defT2.ov_cimguiname or defT2.cimguiname).."_nonUDT"
			defT2.nonUDT = 1
			defT2.retref = nil
			defsT[t.cimguiname][#defsT[t.cimguiname] + 1] = defT2
			defsT[t.cimguiname][t.signature.."nonUDT"] = defT2
			table.insert(newcdefs,{stname=t.stname,funcname=t.funcname,args=args,argsc=argscsinpars,signature=t.signature.."nonUDT",cimguiname=t.cimguiname,call_args=call_args,ret =ret,comment=comment})
			--converting to Simple type----------------------------------------------------
			local defT3 = {}
			--first strings
			for k,v in pairs(defT) do
				defT3[k] = v
			end
			--then argsT table
			defT3.argsT = {}
			for k,v in ipairs(defT.argsT) do
				table.insert(defT3.argsT,{type=v.type,name=v.name})
			end
			local comma = (#defT.argsT > 0) and "," or ""
			--defT3.args = "("..defT.ret.." *pOut"..comma..defT.args:sub(2)
			defT3.ret = defT.ret.."_Simple"
			defT3.retorig = defT.ret
			defT3.ov_cimguiname = (defT3.ov_cimguiname or defT3.cimguiname).."_nonUDT2"
			defT3.nonUDT = 2
			defT3.retref = nil
			defsT[t.cimguiname][#defsT[t.cimguiname] + 1] = defT3
			defsT[t.cimguiname][t.signature.."nonUDT2"] = defT3
			table.insert(newcdefs,{stname=t.stname,funcname=t.funcname,args=args,argsc=argscsinpars,signature=t.signature.."nonUDT2",cimguiname=t.cimguiname,call_args=call_args,ret =ret,comment=comment})
		end
		end
	end
	for i,v in ipairs(newcdefs) do
		table.insert(FP.cdefs,v)
	end
end

local function gen_structs_and_enums_table(cdefs)
    local function_closing_re = "}"
    local namespace_re = "namespace"
    local in_namespace = false
    local struct_re = "^%s*struct%s+([^%s;]+)$"
    local in_struct = false
    local struct_closed_re = "^%s*struct%s+([^%s]+);$"
    local struct_closing_re = "};"
    local struct_op_close_re = "%b{}"
    local structnames = {}
    local enumnames = {}
    local enums_re = "^%s*enum%s+([^%s;]+)"
    local outtab = {structs={},enums={}}
    local typedefs_dict = {}
   
    for i,line in ipairs(cdefs) do
    repeat -- simulating continue with break
        -- separate comments from code
        local linecom = line
        local line, comment = split_comment(line)
        line = clean_spaces(line)
        --typedefs dictionary
        if line:match("typedef") then
            local value,key = line:match("typedef%s+(.+)%s+([%w_]+);")
            if key and value then
                typedefs_dict[key] = value
            else --try function typedef
                local key = line:match("%(%*([%w_]+)%)%([^%(%)]*%)")
                if key then
                    local linet = line
                    linet = linet:gsub("typedef ","")
                    linet = linet:gsub("%(%*("..key..")%)","(*)")
                    typedefs_dict[key] = linet
                else
                    print(key,value,line)
                end
            end
        end
        if line:match(namespace_re) then
            in_namespace = true
        end
        
        local structbegin = line:match(struct_re)
        if structbegin then
            structnames[#structnames + 1] = structbegin
            outtab.structs[structbegin] = outtab.structs[structbegin] or {}
            break
        end
        
        local enumname = line:match(enums_re)
        if enumname then
            enumnames[#enumnames + 1] = enumname
            outtab.enums[enumname] = outtab.enums[enumname] or {}
            break
        end
        
        if in_namespace then
            if line:match(function_closing_re) then
                in_namespace = false
            end
            break -- dont write anything inside
        end
        
        if (#enumnames > 0) then
            assert(#structnames==0,"enum in struct")
            if line:match(struct_closing_re) and not line:match(struct_op_close_re) then
                enumnames[#enumnames] = nil
                break
            end
            if line=="" or line:match("^{") then
                break
            else
                local name,value = line:match("%s*([%w_]+)%s*=%s*([^,]+)")
                if value then
                    table.insert(outtab.enums[enumnames[#enumnames]],{name=name,value=value})
                else --increment by one
                    local name = line:match("%s*([^,]+)")
					local enum_table = outtab.enums[enumnames[#enumnames]]
                    local value = enum_table[#enum_table] and (enum_table[#enum_table].value + 1) or 0
                    table.insert(outtab.enums[enumnames[#enumnames]],{name=name,value=value})
                end
            end
        end
        
        if (#structnames > 0) then
            if line:match(struct_closing_re) and not line:match(struct_op_close_re) then
                structnames[#structnames] = nil
                break
            end
            if line=="" or line:match("^{") then
                break
            elseif structnames[#structnames] ~="ImVector" then --avoid ImVector
                --local functype_re = "^%s*[%w%s%*]+(%(%*)[%w_]+(%)%([^%(%)]*%))"
                local functype_re = "^%s*[%w%s%*]+%(%*[%w_]+%)%([^%(%)]*%)"
                local functype_reex = "^(%s*[%w%s%*]+%(%*)([%w_]+)(%)%([^%(%)]*%))"
                if line:match(functype_re) then
                    local t1,name,t2 = line:match(functype_reex)
                    table.insert(outtab.structs[structnames[#structnames]],{type=t1..t2,name=name})
                    break
                end
                --split type name1,name2; in several lines
                local typen,rest = line:match("([^,]+)%s(%S+[,;])")
                for name in rest:gmatch("([^%s,;]+)%s?[,;]") do
                    table.insert(outtab.structs[structnames[#structnames]],{type=typen,name=name})
                end
            end
        end
    until true
    end
    --calcule size of name[16+1] [xxx_COUNT]
    local allenums = {}
    --first calc_value in enums
    for enumname,enum in pairs(outtab.enums) do
        for i,t in ipairs(enum) do
            local val = tonumber(t.value)
            if val then
                t.calc_value = val
            elseif t.value:match"<<" then
                local v1,v2 = t.value:match("(%d+)%s*<<%s*(%d+)")
                t.calc_value = bit.lshift(v1,v2)
            elseif t.value:match"|" then --or several enums
                local ens = t.value
                ens = strsplit(ens,"|")
                for i,v in ipairs(ens) do ens[i] = allenums[clean_spaces(v)] end
                t.calc_value = bit.bor(unpack(ens))
            elseif allenums[t.value] then
                t.calc_value = allenums[t.value]
            else
                print("Error unknown value in enums",t.value)
            end
            assert(t.calc_value)
            allenums[t.name] = t.calc_value
        end
    end
    --then calcsize in struct members
    for stname,struct in pairs(outtab.structs) do
        for i,t in ipairs(struct) do
            local val = t.name:match"%[([^%[%]]+)%]"
            if val then
                if tonumber(val) then
                    t.size = tonumber(val)
                elseif allenums[val] then
                    t.size = allenums[val]
                elseif val:match"%+" then
                    local s1,s2 = val:match("(%d+)%s*%+%s*(%d+)")
                    t.size = s1+s2
                else
                    print("Error size is",val)
                end
                assert(t.size)
            end
        end
    end
    return outtab, typedefs_dict
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
    local typedefs_table = {}
    local typedefs_dict = {}

    local outtab = {}
    -- Output the file
    --table.insert(outtab,"/////////////// BEGIN AUTOGENERATED SEGMENT\n")

    for i,line in ipairs(cdefs) do
    repeat -- simulating continue with break
        -- separate comments from code and try to add them with same tab
        local line, comment = split_comment(line)
        local linelen = #line
        local desired_linelen = (linelen==0) and 0 or math.max(math.ceil(linelen/10)*10,40)
        local spaces_to_add = 0 --desired_linelen - linelen
        local linecom = line..string.rep(" ",spaces_to_add)..comment

        if line:match(namespace_re) then
            in_namespace = true
        end
        local structbegin = line:match(struct_re)
        if structbegin then
            structnames[#structnames + 1] = structbegin
            if #structnames < 2 and structbegin~= "ImVector" then --not inner and not ImVector
                table.insert(outtab,linecom.."\n")
                break
            end
        end
        
        -- ImVector special treatment
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
            table.insert(outtab,linecom.."\n")
            local struct_closed_name = line:match(struct_closed_re)
            if struct_closed_name then
                table.insert(typedefs_table,"typedef struct "..struct_closed_name.." "..struct_closed_name..";\n")
                typedefs_dict[struct_closed_name] = "struct "..struct_closed_name
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
                    --st[#st + 1] = string.format("typedef struct %s %s;\n",structname,structname)
                    table.insert(typedefs_table,string.format("typedef struct %s %s;\n",structname,structname))
                    typedefs_dict[structname] = "struct "..structname
                    structnames[#structnames] = nil
                end
            elseif line:match(struct_closing_re) and not line:match(struct_op_close_re) then
                local structname = structnames[#structnames]
                --table.insert(outtab,"typedef struct "..structname.." "..structname..";\n")
                table.insert(typedefs_table,"typedef struct "..structname.." "..structname..";\n")
                typedefs_dict[structname] = "struct "..structname
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

    --table.insert(outtab,"//////////////// END AUTOGENERATED SEGMENT \n")
    local uniques = {}
    for i,l in ipairs(typedefs_table) do
        if not uniques[l] then
            uniques[l] = true
            table.insert(outtab,2,l)
        end
    end
    local cstructsstr = table.concat(outtab)
    cstructsstr = cstructsstr:gsub("\n+","\n") --several empty lines to one empty line
    return cstructsstr, typedefs_dict
end

local function func_header_impl_generate(FP)

    local outtab = {}
    
    for _,t in ipairs(FP.cdefs) do
        if t.cimguiname then
            local cimf = FP.defsT[t.cimguiname]
            local def = cimf[t.signature]
            if def.ret then --not constructor
                local addcoment = def.comment or ""
                if def.stname == "" then --ImGui namespace or top level
                    table.insert(outtab,"CIMGUI_API".." "..def.ret.." "..(def.ov_cimguiname or def.cimguiname)..def.args..";"..addcoment.."\n")
                else
                    error("class function in implementations")
                end
            end
        else --not cimguiname
            table.insert(outtab,t.comment:gsub("%%","%%%%").."\n")-- %% substitution for gsub
        end
    end
    local cfuncsstr = table.concat(outtab)
    cfuncsstr = cfuncsstr:gsub("\n+","\n") --several empty lines to one empty line
    return cfuncsstr
end
local function func_header_generate(FP)

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
        if t.cimguiname then
        local cimf = FP.defsT[t.cimguiname]
        local def = cimf[t.signature]
        local manual = get_manuals(def)
        if not manual and def.ret then --not constructor
            local addcoment = def.comment or ""
			local empty = def.args:match("^%(%)") --no args
            if def.stname == "ImGui" or def.stname == "" then --ImGui namespace or top level
                table.insert(outtab,"CIMGUI_API".." "..def.ret.." "..(def.ov_cimguiname or def.cimguiname)..(empty and "(void)" or def.args)..";"..addcoment.."\n")
            else
                
                --local imgui_stname = embeded_structs[def.stname] or def.stname
                local imgui_stname = def.stname
                local args = def.args:gsub("^%(","("..imgui_stname.."* self"..(empty and "" or ","))
                table.insert(outtab,"CIMGUI_API".." "..def.ret.." "..(def.ov_cimguiname or def.cimguiname)..args..";"..addcoment.."\n")
            end
        end
        else --not cimguiname
            table.insert(outtab,t.comment:gsub("%%","%%%%").."\n")-- %% substitution for gsub
        end
    end

    local cfuncsstr = table.concat(outtab)
    cfuncsstr = cfuncsstr:gsub("\n+","\n") --several empty lines to one empty line
    return cfuncsstr
end
local function func_implementation(FP)

    local outtab = {}
    for _,t in ipairs(FP.cdefs) do
        repeat -- continue simulation
        if not t.cimguiname then break end
        local cimf = FP.defsT[t.cimguiname]
        local def = cimf[t.signature]
        local manual = get_manuals(def)
        if not manual and def.ret and def.stname~="" then --not constructor or manual or top level
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
                    if def.ret~="void" then
                        table.insert(outtab,"    "..def.ret.." ret = ImGui::"..def.funcname.."V"..call_args..";\n")
                    else
                        table.insert(outtab,"    ImGui::"..def.funcname.."V"..call_args..";\n")
                    end
                    table.insert(outtab,"    va_end(args);\n")
                    if def.ret~="void" then
                        table.insert(outtab,"    return ret;\n")
                    end
                    --cppfile:write("    return ImGui::",def.funcname,def.call_args,";\n")
                    table.insert(outtab,"}\n")
                elseif def.nonUDT then
					if def.nonUDT == 1 then
                    table.insert(outtab,"CIMGUI_API".." "..def.ret.." "..(def.ov_cimguiname or def.cimguiname)..def.args.."\n")
                    table.insert(outtab,"{\n")
                    table.insert(outtab,"    *pOut = ImGui::"..def.funcname..def.call_args..";\n")
                    table.insert(outtab,"}\n")
					else --nonUDT==2
					table.insert(outtab,"CIMGUI_API".." "..def.ret.." "..(def.ov_cimguiname or def.cimguiname)..def.args.."\n")
                    table.insert(outtab,"{\n")
                    table.insert(outtab,"    "..def.retorig.." ret = ImGui::"..def.funcname..def.call_args..";\n")
					table.insert(outtab,"    "..def.ret.." ret2 = "..def.retorig.."ToSimple(ret);\n")
					table.insert(outtab,"    return ret2;\n")
                    table.insert(outtab,"}\n")
					end
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
                    if def.ret~="void" then
                        table.insert(outtab,"    "..def.ret.." ret = self->"..def.funcname.."V"..call_args..";\n")
                    else
                        table.insert(outtab,"    self->"..def.funcname.."V"..call_args..";\n")
                    end
                    table.insert(outtab,"    va_end(args);\n")
                    if def.ret~="void" then
                        table.insert(outtab,"    return ret;\n")
                    end
                    --cppfile:write("    return self->",def.funcname,def.call_args,";\n")
                    table.insert(outtab,"}\n")
                elseif def.nonUDT then
					if def.nonUDT == 1 then
                    table.insert(outtab,"CIMGUI_API".." "..def.ret.." "..(def.ov_cimguiname or def.cimguiname)..args.."\n")
                    table.insert(outtab,"{\n")
                    table.insert(outtab,"    *pOut = self->"..def.funcname..def.call_args..";\n")
                    table.insert(outtab,"}\n")
					else --nonUDT==2
					table.insert(outtab,"CIMGUI_API".." "..def.ret.." "..(def.ov_cimguiname or def.cimguiname)..args.."\n")
                    table.insert(outtab,"{\n")
					table.insert(outtab,"    "..def.retorig.." ret = self->"..def.funcname..def.call_args..";\n")
					table.insert(outtab,"    "..def.ret.." ret2 = "..def.retorig.."ToSimple(ret);\n")
					table.insert(outtab,"    return ret2;\n")
                    table.insert(outtab,"}\n")
					end
                else
                    table.insert(outtab,"CIMGUI_API".." "..def.ret.." "..(def.ov_cimguiname or def.cimguiname)..args.."\n")
                    table.insert(outtab,"{\n")
                    table.insert(outtab,"    return "..castret..ptret.."self->"..def.funcname..def.call_args..";\n")
                    table.insert(outtab,"}\n")
                end
            end
        end
        until true
    end
    --cppfile:close()
    return table.concat(outtab)
end

--generate cimgui.cpp cimgui.h and auto versions depending on postfix
local function cimgui_generation(postfix,STP,FP)
    --merge it in cimgui_template.h to cimgui.h
    local hfile = io.open("./cimgui_template.h","r")
    local hstrfile = hfile:read"*a"
    hfile:close()
    local cstructsstr,typedefs_dict = gen_structs_and_enums(STP.lines)
    --for not gcc parsing
    if postfix == "" then
        cstructsstr = "typedef unsigned short ImDrawIdx;\ntypedef void* ImTextureID;\n"..cstructsstr
    end
    hstrfile = hstrfile:gsub([[#include "imgui_structs%.h"]],cstructsstr)
    local cfuncsstr = func_header_generate(FP)
    hstrfile = hstrfile:gsub([[#include "auto_funcs%.h"]],cfuncsstr)
    save_data("./generated/cimgui"..postfix..".h",hstrfile)
    
    
    --merge it in cimgui_template.cpp to cimgui.cpp
    local cimplem = func_implementation(FP)
    local hfile = io.open("./cimgui_template.cpp","r")
    local hstrfile = hfile:read"*a"
    hfile:close()
    hstrfile = hstrfile:gsub([[#include "auto_funcs%.cpp"]],cimplem)
    hstrfile = hstrfile:gsub([[#include "cimgui%.h"]],[[#include "cimgui]]..postfix..[[.h"]])
    save_data("./generated/cimgui"..postfix..".cpp",hstrfile)
    return typedefs_dict
end
--------------------------------------------------------
-----------------------------do it----------------------
--------------------------------------------------------
--first without gcc
local pipe,err = io.open("../imgui/imgui.h","r")
if not pipe then
    error("could not open file:"..err)
end

local STP = struct_parser()
local FP = func_parser()

for line in filelines(pipe) do
    local line, comment = split_comment(line)
    STP.insert(line,comment)
    FP.insert(line,comment)
end
pipe:close()
FP:compute_overloads()
cimgui_generation("",STP,FP)

--then gcc
local pFP,pSTP,typedefs_dict2

if HAVE_GCC then
local pipe,err = io.popen([[gcc -E -DIMGUI_DISABLE_OBSOLETE_FUNCTIONS -DIMGUI_API="" -DIMGUI_IMPL_API="" ../imgui/imgui.h]],"r")

if not pipe then
    error("could not execute gcc "..err)
end

pSTP = struct_parser() --overwrite
pFP = func_parser() --overwrite

for line in location(pipe,{"imgui"}) do
    local line, comment = split_comment(line)
    pSTP.insert(line,comment)
    pFP.insert(line,comment)
end
pipe:close()
local ovstr = pFP:compute_overloads()
ADDnonUDT(pFP)
save_data("./generated/overloads.txt",ovstr)
typedefs_dict2 = cimgui_generation("_auto",pSTP,pFP)

end

----------save fundefs in definitions.lua for using in bindings
save_data("./generated/definitions.lua",serializeTable("defs",pFP.defsT),"\nreturn defs")

----------save struct and enums lua table in structs_and_enums.lua for using in bindings
local structs_and_enums_table,typedefs_dict = gen_structs_and_enums_table(pSTP.lines)
save_data("./generated/structs_and_enums.lua",serializeTable("defs",structs_and_enums_table),"\nreturn defs")
typedefs_dict = mergeT(typedefs_dict,typedefs_dict2)
save_data("./generated/typedefs_dict.lua",serializeTable("defs",typedefs_dict),"\nreturn defs")
--=================================Now implementations

local iFP,iSTP

if #implementations > 0 then

    iFP = func_parser()
    iSTP = struct_parser()
    
    for i,impl in ipairs(implementations) do
        local source = [[../imgui/examples/imgui_impl_]].. impl .. ".h "
        local locati = [[imgui_impl_]].. impl
        local pipe,err
        if HAVE_GCC then
            pipe,err = io.popen([[gcc -E -DIMGUI_DISABLE_OBSOLETE_FUNCTIONS -DIMGUI_API="" -DIMGUI_IMPL_API="" ]] ..source,"r")
        else
            pipe,err = io.open(source,"r")
        end
        if not pipe then
            error("could not get file: "..err)
        end
        
        local iterator = (HAVE_GCC and location) or filelines
        
        for line,locat in iterator(pipe,{locati}) do
            local line, comment = split_comment(line)
            iSTP.insert(line,comment)
            iFP.insert(line,comment,locat)
        end
        pipe:close()
    end

    -- save ./cimgui_impl.h
    local cfuncsstr = func_header_impl_generate(iFP)
    local cstructstr = gen_structs_and_enums(iSTP.lines)
    save_data("./generated/cimgui_impl.h",cstructstr,cfuncsstr)

    ----------save fundefs in impl_definitions.lua for using in bindings
    save_data("./generated/impl_definitions.lua",serializeTable("defs",iFP.defsT),"\nreturn defs")

end -- #implementations > 0 then

-------------------------------json saving
--avoid mixed tables (with string and integer keys)
local function json_prepare(defs)
    --delete signatures in function
    for k,def in pairs(defs) do
        for k2,v in pairs(def) do
            if type(k2)=="string" then
                def[k2] = nil
            end
        end
    end
    return defs
end

local json = require"json"
save_data("./generated/definitions.json",json.encode(json_prepare(pFP.defsT)))
save_data("./generated/structs_and_enums.json",json.encode(structs_and_enums_table))
save_data("./generated/typedefs_dict.json",json.encode(typedefs_dict))
if iFP then
    save_data("./generated/impl_definitions.json",json.encode(json_prepare(iFP.defsT)))
end

print"all done!!"
--[[
---dump some infos-----------------------------------------------------------------------
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
    if t.cimguiname and not t.ret then
    print(t.cimguiname,"\t",t.signature,"\t",t.args,"\t",t.argsc,"\t",t.call_args,"\t",t.ret)
    end
end
print"//-------------------------------------------------------------------------------------"
for i,t in ipairs(FP.cdefs) do
    --print(t.cimguiname,"   ",t.funcname,"\t",t.signature,"\t",t.args,"\t",t.argsc,"\t",t.call_args,"\t",t.ret) 
end
---------------------------------------------------------------------------------------------
--]]