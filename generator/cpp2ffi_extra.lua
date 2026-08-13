local insert = table.insert

local function ToStr(t,dometatables)
    local function basicToStr (o)
        if type(o) == "number" or type(o)=="boolean" then
            return tostring(o)
        elseif type(o) == "string" then
            return string.format("%q", o)
        else
            return tostring(o) --"nil"
        end
    end
    local strTG = {}
    --local basicToStr= basicSerialize --tostring
    if type(t) ~="table" then  return basicToStr(t) end
    local recG = 0
    local nameG="SELF"..recG
    local ancest ={}
    local function _ToStr(t,strT,rec,name)
        if ancest[t] then
            strT[#strT + 1]=ancest[t]
            return
        end
        rec = rec + 1
        ancest[t]=name
        strT[#strT + 1]='{'
        local count=0
        -------------
        --if t.name then strT[#strT + 1]=string.rep("\t",rec).."name:"..tostring(t.name) end
        ----------------
        for k,v in pairs(t) do
            count=count+1
            strT[#strT + 1]="\n"
            local kstr
            if type(k) == "table" then
                local name2=string.format("%s.KEY%d",name,count)
                strT[#strT + 1]=string.rep("\t",rec).."["
                local strTK = {}
                _ToStr(k,strTK,rec,name2)
                kstr=table.concat(strTK)
                strT[#strT + 1]=kstr.."]="
            else
                kstr = basicToStr(k)
                strT[#strT + 1]=string.rep("\t",rec).."["..kstr.."]="
            end
            
            if type(v) == "table" then
                    local name2=string.format("%s[%s]",name,kstr)
                    _ToStr(v,strT,rec,name2)
            else
                strT[#strT + 1]=basicToStr(v)
            end
        end
        if dometatables then
            local mt = getmetatable(t)
            if mt then
                local namemt = string.format("%s.METATABLE",name)
                local strMT = {}
                _ToStr(mt,strMT,rec,namemt)
                local metastr=table.concat(strMT)
                strT[#strT + 1] = "\n"..string.rep("\t",rec).."[METATABLE]="..metastr
            end
        end
        strT[#strT + 1]='}'
        rec = rec - 1
        return
    end
    _ToStr(t,strTG,recG,nameG)
    return table.concat(strTG)
end

local function prtable(...)
    for i=1, select('#', ...) do
        local t = select(i, ...)
        print(ToStr(t))
        print("\n")
    end
end

-- more compact serialization
local function basicSerialize (o)
    if type(o) == "number" then
        return string.format("%.17g", o)
    elseif type(o)=="boolean" then
        return tostring(o)
    elseif type(o) == "string" then
        return string.format("%q", o)
    elseif pcall(function() return o.__serialize end) then
        return o.__serialize(o)
    elseif type(o)=="cdata" then
        return cdataSerialize(o)
    else
        return tostring(o) --"nil"
    end
end
-- very readable and now suited for cyclic tables
local kw = {['and'] = true, ['break'] = true, ['do'] = true, ['else'] = true,
    ['elseif'] = true, ['end'] = true, ['false'] = true, ['for'] = true,
    ['function'] = true, ['goto'] = true, ['if'] = true, ['in'] = true,
    ['local'] = true, ['nil'] = true, ['not'] = true, ['or'] = true,
    ['repeat'] = true, ['return'] = true, ['then'] = true, ['true'] = true,
    ['until'] = true, ['while'] = true}
function tb2st_serialize(t,options)
    options = options or {}
    local function sorter(a,b)
        if type(a)==type(b) then 
            return a<b 
        elseif type(a)=="number" then
            return true
        else
            assert(type(b)=="number")
            return false
        end
    end
    local function serialize_key(val, dodot, pretty)
        local dot = dodot and "." or ""
        if type(val)=="string" then
            if  val:match '^[_%a][_%w]*$' and not kw[val] then
                return dot..tostring(val)
            else
                return "[\""..tostring(val).."\"]"
            end
        elseif (not pretty) and (not dodot) and (type(val) == "number") and (math.floor(val)==val) then
            return  --array index
        else
            return "["..tostring(val).."]"
        end
    end
    local function serialize_key_name(val)
        return serialize_key(val, true)
    end
    local insert = table.insert
    local function _tb2st(t,saved,sref,level,name)
        saved = saved or {}     -- initial value
        level = level or 0
        sref = sref or {}
        name = name or "t"
        if type(t)=="table" then
            if saved[t] then
                sref[#sref+1] = {saved[t],name}
                return"nil"
            else
                saved[t] = name

                local ordered_keys = {}
                for k,v in pairs(t) do
                    insert(ordered_keys,k)
                end
                table.sort(ordered_keys,sorter)
                
                local str2 = {}
                insert(str2,"{")
                if options.pretty then insert(str2,"\n") end
                for _,k in ipairs(ordered_keys) do
                    if options.pretty then insert(str2,("  "):rep(level+1)) end
                    local v = t[k]
                    local kser = serialize_key(k, nil, options.pretty)
                    insert(str2, (kser and (kser .."=") or ""))
                    if type(v)~="table" then
                        insert(str2, basicSerialize(v))
                    else
                        local name2 = name .. serialize_key_name(k)
                        insert(str2,_tb2st(v,saved,sref,level+1,name2))
                    end
                    if options.pretty then insert(str2,",\n") else insert(str2, ",") end
                end
                str2[#str2] = "}"
                if level == 0 then
                    --insert(str2, 1,"local ffi = require'ffi'\nlocal t=")
                    insert(str2, 1,"local t=")
                    for i,v in ipairs(sref) do 
                        insert(str2, "\n"..v[2].."="..v[1])
                    end
                    insert(str2,"\n return t")
                end
                return table.concat(str2)
            end
        else
            return basicSerialize(t)
        end
    end
    return(_tb2st(t))
end
local serializeTableF = function(t) return tb2st_serialize(t,{pretty=true}) end --new serialization more compact

local function deepcopy(object)
    local lookup_table = {}
    local function _copy(object)
        --assert(object~=REST)
        if type(object) ~= "table" then
            return object
        elseif lookup_table[object] then
            return lookup_table[object]
        end
        local new_table = {}
        lookup_table[object] = new_table
        for index, value in pairs(object) do
            new_table[_copy(index)] = _copy(value)
        end
        return setmetatable(new_table, getmetatable(object))
    end
    return _copy(object)
end

local function table_do_sorted(t,f)
    local sorted = {}
    for k,v in pairs(t) do
        table.insert(sorted,k)
    end
    table.sort(sorted)
    for ii,k in ipairs(sorted) do
        f(k,t[k])
    end
end

----------------------------
local function save_data(filename,...)
    local file,err = io.open(filename,"w")
    if not file then error(err) end
    for i=1, select('#', ...) do
        local data = select(i, ...)
        file:write(data)
    end
    file:close()
end

local function  read_data(filename)
    local hfile,err = io.open(filename,"r")
    if not hfile then error(err) end
    local hstrfile = hfile:read"*a"
    hfile:close()
    return hstrfile
end

local function copyfile(src,dst,blocksize)
    blocksize = blocksize or 1024*4
    print( "copyfile", src, dst)
    local srcf, err = io.open(src,"rb")
    if not srcf then error(err) end
    local dstf, err = io.open(dst,"wb")
    if not dstf then error(err) end
    while true do
        local data = srcf:read(blocksize)
        if not data then break end
        dstf:write(data)
    end
    srcf:close()
    dstf:close()
end

local function paramListWithoutDots(params)
    local i, j = string.find(params, "%.%.%.")
    while i > 1 do
        i = i - 1
        local c = string.sub(params,i,i)
        if c == "," then
            return string.sub(params, 1, i-1) .. params:sub(j+1)
        elseif c == "(" then
            return string.sub(params, 1, i) .. params:sub(j+1)
        end
    end

    error("paramListWithoutDots failed")
    return "()"
end

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

local function save_output(self)
    --add VARGS0
    local defsVARG = {}
    for k,defs in pairs(self.defsT) do
        for i, def in ipairs(defs) do
            if def.isvararg then
                --print("vararg",k,#def)
                local def1 = deepcopy(def)
                def1.isvararg = nil
                def1.isVARG0 = true
                def1.argsT[#def1.argsT] = nil
                def1.args = paramListWithoutDots(def1.args)
                def1.call_args_old = paramListWithoutDots(def1.call_args_old)
                def1.call_args = paramListWithoutDots(def1.call_args)
                def1.signature = paramListWithoutDots(def1.signature)
                def1.cimguiname = def1.cimguiname.."0"
                def1.ov_cimguiname = def1.ov_cimguiname.."0"
                defsVARG[k.."0"] = defsVARG[k.."0"] or {}
                table.insert(defsVARG[k.."0"], def1)
            end
        end
    end
    for k,def in pairs(defsVARG) do
        self.defsT[k] = def
    end
    --add manual not present in module
    for k,v in pairs(self.manuals) do
        if not self.defsT[k] then
            --print("add manual",k)
            self.defsT[k] = {v}
        else
            --print("skipped manual",k)
        end
    end

    ----------------------
    save_data("./output/overloads.txt",self.overloadstxt)
    save_data("./output/definitions.lua",serializeTableF(self.defsT))
    save_data("./output/structs_and_enums.lua",serializeTableF(self.structs_and_enums_table))
    save_data("./output/typedefs_dict.lua",serializeTableF(self.typedefs_dict))
    save_data("./output/constants.lua",serializeTableF(self.constants))
    
    local json = require"json"
    local json_opts = {dict_on_empty={defaults=true}}
    save_data("./output/definitions.json",json.encode(json_prepare(self.defsT),json_opts))
    save_data("./output/structs_and_enums.json",json.encode(self.structs_and_enums_table))
    save_data("./output/typedefs_dict.json",json.encode(self.typedefs_dict))
    save_data("./output/constants.json",json.encode(self.constants))
    
    local modulename = self.modulename
    copyfile("./output/"..modulename..".h", "../"..modulename..".h")
    copyfile("./output/"..modulename..".cpp", "../"..modulename..".cpp")
    os.remove("./output/"..modulename..".h")
    os.remove("./output/"..modulename..".cpp")
end
---------------------- C writing functions
local function func_header_generate_structs(FP)

    local outtab = {}--"\n/////func_header_generate_structs\n"}
    prtable("embeded_structs",FP.embeded_structs)
    table_do_sorted(FP.embeded_structs,function(k,v) 
        if not FP.typenames[k] then
            print("embeded",k,v)
            table.insert(outtab,"typedef "..v.." "..k..";\n")
        end
    end)
    
    table_do_sorted(FP.embeded_enums,function(k,v) table.insert(outtab,"typedef "..v.." "..k..";\n") end)
    --table.insert(outtab, "\n//////////templates\n")
    table_do_sorted(FP.templates,function(ttype,v)
        --print("func_header_generate_structs",ttype)
        if not (ttype == "std::function") then
            table_do_sorted(v,function(ttypein,te)
                local ttype2 = ttype:gsub("::","_") --std::string
                table.insert(outtab,"typedef "..ttype.."<"..ttypein.."> "..ttype2.."_"..te..";\n")
            end)
        end
    end)
    --M.prtable("typenames",FP.typenames)
    table_do_sorted(FP.opaque_structs,function(k,v)
        if not FP.typenames[k] then
            table.insert(outtab,"typedef "..v.." "..k..";\n") 
            --table.insert(outtab,"typedef const "..v.."* "..k.."_opq;\n") 
            --table.insert(outtab,"typedef "..v.."* "..k.."_opq;\n") 
        end
    end)
    --table.insert(outtab, "\n//////////end func header\n")
    return outtab
end

local function func_header_generate_funcs(FP)

    local outtab = {}
   
    for _,t in ipairs(FP.funcdefs) do
        if t.cimguiname then
        local cimf = FP.defsT[t.cimguiname]
        local def = cimf[t.signature]
        assert(def,t.signature..t.cimguiname)
        local custom
        if FP.custom_header then
            custom = FP.custom_header(outtab, def)
        end
        local manual = FP.get_manuals(def)
        if not custom and not manual and not def.templated and not FP.get_skipped(def) --and not (FP.opaque_structs[def.stname] and not def.is_static_function)
        then
            local addcoment = "" --def.comment or ""
            local empty = def.args:match("^%(%)") --no args
            if def.constructor then
                assert(def.stname ~= "","constructor without struct")
                table.insert(outtab,"CIMGUI_API "..def.stname.."* "..def.ov_cimguiname ..(empty and "(void)" or def.args)..";"..addcoment.."\n")
                if FP.CONSTRUCTORS_GENERATION then
                    outtab[#outtab] = outtab[#outtab].."\nCIMGUI_API void "..def.ov_cimguiname.."_Construct("..def.stname.."* self"..(empty and "" or ","..def.args:sub(2,-2))..");\n"
                end
            elseif def.destructor then
                table.insert(outtab,"CIMGUI_API void "..def.ov_cimguiname..def.args..";"..addcoment.."\n")
            else --not constructor
                --local ret = FP.nP_ret[def.ret] or def.ret
                local ret = def.ret
                if def.stname == "" or def.is_static_function then --ImGui namespace or top level
                    table.insert(outtab,"CIMGUI_API "..ret.." ".. def.ov_cimguiname ..(empty and "(void)" or def.args)..";"..addcoment.."\n")
                    if def.isvararg then
                        -- For variadic functions we add a function implementation with zero argumets, for compatibility with languages such as C#.
                        table.insert(outtab, "#ifdef CIMGUI_VARGS0\n")
                        table.insert(outtab, "CIMGUI_API".." "..ret.." "..def.ov_cimguiname.."0"..paramListWithoutDots(def.args)..";\n")
                        table.insert(outtab, "#endif\n")
                    end
                else
                    table.insert(outtab,"CIMGUI_API "..ret.." "..def.ov_cimguiname..def.args..";"..addcoment.."\n")
                    if def.isvararg then
                        -- For variadic functions we add a function implementation with zero argumets, for compatibility with languages such as C#.
                        table.insert(outtab, "#ifdef CIMGUI_VARGS0\n")
                        table.insert(outtab, "CIMGUI_API".." "..ret.." "..def.ov_cimguiname.."0"..paramListWithoutDots(def.args)..";\n")
                        table.insert(outtab, "#endif\n")
                    end
                end
            end 
        end
        if FP.custom_function_post then
            FP:custom_function_post(outtab, def)
        end
        else --not cimguiname
            table.insert(outtab,t.comment:gsub("%%","%%%%").."\n")-- %% substitution for gsub
        end
        
    end

    return outtab
end

local function func_header_generate(FP)

    local outtab = func_header_generate_structs(FP)
    table.insert(outtab, 1, "\n#ifndef CIMGUI_DEFINE_ENUMS_AND_STRUCTS\n")
    table.insert(outtab,"#endif //CIMGUI_DEFINE_ENUMS_AND_STRUCTS\n")
    
    local outtabf = func_header_generate_funcs(FP)
    outtabf = table.concat(outtabf)
    assert(type(outtabf)=="string")
    --outtabf = M.header_subs_nonPOD(FP,outtabf)
    local cfuncsstr = table.concat(outtab)..outtabf
    cfuncsstr = cfuncsstr:gsub("\n+","\n") --several empty lines to one empty line

    return cfuncsstr
end

local function ImGui_f_implementation(def)
    local outtab = {}
    local ptret = def.retref and "&" or ""
    table.insert(outtab,"CIMGUI_API".." "..def.ret.." "..def.ov_cimguiname..def.args.."\n")
    table.insert(outtab,"{\n")
    local namespace = def.namespace and def.namespace.."::" or ""
    --namespace = def.is_static_function and namespace..def.stname.."::" or namespace
    if def.isvararg then
        local call_args = def.call_args:gsub("%.%.%.","args")
        table.insert(outtab,"    va_list args;\n")
        table.insert(outtab,"    va_start(args, fmt);\n")
        if def.ret~="void" then
            table.insert(outtab,"    "..def.ret.." ret = "..namespace..def.funcname.."V"..call_args..";\n")
        else
            table.insert(outtab,"    "..namespace..def.funcname.."V"..call_args..";\n")
        end
        table.insert(outtab,"    va_end(args);\n")
        if def.ret~="void" then
            table.insert(outtab,"    return ret;\n")
        end
        table.insert(outtab,"}\n")
        -- For variadic functions we add a function implementation with zero argumets, for compatibility with languages such as C#.
        table.insert(outtab, "#ifdef CIMGUI_VARGS0\n")
        table.insert(outtab, "CIMGUI_API".." "..def.ret.." "..def.ov_cimguiname.."0"..paramListWithoutDots(def.args).."\n")
        table.insert(outtab, "{\n")
        local returnword = "return "
        if def.ret=="void" then returnword = "" end
        table.insert(outtab, "    "..returnword..def.ov_cimguiname..paramListWithoutDots(def.call_args_old)..";\n")
        table.insert(outtab, "}\n")
        table.insert(outtab, "#endif\n")
    elseif def.nonUDT then
        if def.nonUDT == 1 then
            --table.insert(outtab,"    *pOut = "..namespace..def.funcname..def.call_args..";\n")
            insert(outtab,"    return ConvertFromCPP_"..def.conv.."("..namespace..def.funcname..def.call_args..");\n")
        elseif def.nonUDT == 2 then
            insert(outtab,"    return reinterpret_cast<"..def.ret..">("..ptret..namespace..def.funcname..def.call_args..");\n")
        elseif def.nonUDT == "string" then
            insert(outtab,"    static std::string str;\n")
            insert(outtab,"    str.assign("..ptret.."self->"..def.funcname..def.call_args..");\n")
            insert(outtab,"    return str.c_str();\n")
        elseif def.nonUDT == "opaque" then
            insert(outtab,"    static auto opq = "..ptret..namespace..def.funcname..def.call_args..";\n")
            insert(outtab,"    opq = "..ptret..namespace..def.funcname..def.call_args..";\n")
            insert(outtab,"    return &opq;\n")
        end
        table.insert(outtab,"}\n")
    else --standard ImGui
        table.insert(outtab,"    return "..ptret..namespace..def.funcname..def.call_args..";\n")
        table.insert(outtab,"}\n")
    end
    --table.insert(outtab,"}\n")
    return table.concat(outtab, "")
end
local function struct_f_implementation(def)
    local outtab = {}
    local empty = def.args:match("^%(%)") --no args
    local ptret = def.retref and "&" or ""

    local imgui_stname = def.stname

    table.insert(outtab,"CIMGUI_API".." "..def.ret.." "..def.ov_cimguiname..def.args.."\n")
    table.insert(outtab,"{\n")
    if def.isvararg then
        local call_args = def.call_args:gsub("%.%.%.","args")
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
        table.insert(outtab,"}\n")
        -- For variadic functions we add a function implementation with zero argumets, for compatibility with languages such as C#.
        table.insert(outtab, "#ifdef CIMGUI_VARGS0\n")
        table.insert(outtab, "CIMGUI_API".." "..def.ret.." "..def.ov_cimguiname.."0"..paramListWithoutDots(def.args).."\n")
        table.insert(outtab, "{\n")
        local returnword = "return "
        if def.ret=="void" then returnword = "" end
        table.insert(outtab, "    "..returnword..def.ov_cimguiname.."(self,"..paramListWithoutDots(def.call_args_old):sub(2,-1)..";\n")
        table.insert(outtab, "}\n")
        table.insert(outtab, "#endif\n")
    elseif def.nonUDT then
        if def.nonUDT == 1 then
            --table.insert(outtab,"    *pOut = self->"..def.funcname..def.call_args..";\n")
            --local typret = (def.ret):gsub("const ","")
            insert(outtab,"    return ConvertFromCPP_"..def.conv.."(self->"..def.funcname..def.call_args..");\n")
        elseif def.nonUDT == 2 then
            insert(outtab,"    return reinterpret_cast<"..def.ret..">("..ptret.."self->"..def.funcname..def.call_args..");\n")
        elseif def.nonUDT == "string" then
            insert(outtab,"    static std::string str;\n")
            insert(outtab,"    str.assign("..ptret.."self->"..def.funcname..def.call_args..");\n")
            insert(outtab,"    return str.c_str();\n")
        elseif def.nonUDT == "opaque" then
            insert(outtab,"    static auto opq = "..ptret.."self->"..def.funcname..def.call_args..";\n")
            insert(outtab,"    opq = "..ptret.."self->"..def.funcname..def.call_args..";\n")
            insert(outtab,"    return &opq;\n")
        end
        table.insert(outtab,"}\n")
    else --standard struct
        table.insert(outtab,"    return "..ptret.."self->"..def.funcname..def.call_args..";\n")
        table.insert(outtab,"}\n")
    end

    return table.concat(outtab, "")
end

local function func_implementation(FP)

    local outtab = {}
    for _,t in ipairs(FP.funcdefs) do
        repeat -- continue simulation
        if not t.cimguiname then break end
        local cimf = FP.defsT[t.cimguiname]
        local def = cimf[t.signature]
        assert(def)
        local custom
        if FP.custom_implementation then
            custom = FP.custom_implementation(outtab, def, FP)
        end
        local manual = FP.get_manuals(def)
        if not custom and not manual and not def.templated and not FP.get_skipped(def) --and not (FP.opaque_structs[def.stname] and not def.is_static_function)
        then
            if def.constructor then
                local tab = {}
                assert(def.stname ~= "","constructor without struct")
                local empty = def.args:match("^%(%)") --no args
                table.insert(tab,"CIMGUI_API "..def.stname.."* "..def.ov_cimguiname..(empty and "(void)" or def.args).."\n")
                table.insert(tab,"{\n")
                table.insert(tab,"    return IM_NEW("..def.stname..")"..def.call_args..";\n")
                table.insert(tab,"}\n")
                if FP.CONSTRUCTORS_GENERATION then
                    table.insert(tab,"CIMGUI_API void "..def.ov_cimguiname.."_Construct("..def.stname.."* self"..(empty and "" or ","..def.args:sub(2,-2))..")\n")
                    table.insert(tab,"{\n")
                    table.insert(tab,"    IM_PLACEMENT_NEW(self)"..def.stname..def.call_args..";\n")
                    table.insert(tab,"}\n")
                end
                table.insert(outtab, table.concat(tab, ""))
            elseif def.destructor then
                local tab = {}
                local args = "("..def.stname.."* self)"
                local fname = def.stname.."_destroy" 
                table.insert(tab,"CIMGUI_API void "..fname..args.."\n")
                table.insert(tab,"{\n")
                table.insert(tab,"    IM_DELETE(self);\n")
                table.insert(tab,"}\n")
                table.insert(outtab, table.concat(tab, ""))
            elseif def.stname == "" or def.is_static_function then
                table.insert(outtab, ImGui_f_implementation(def))
            else -- stname
                table.insert(outtab, struct_f_implementation(def))
            end
        end
        if FP.custom_function_post then
            FP:custom_function_post(outtab, def)
        end
        until true
    end
    local conversors = FP:genConversors()
    local cimplem = conversors .. table.concat(outtab)
    return cimplem
end

return {func_implementation = func_implementation, save_output = save_output, save_data = save_data, read_data = read_data, copyfile = copyfile, func_header_generate = func_header_generate, prtable = prtable, table_do_sorted = table_do_sorted, save_output = save_output, deepcopy = deepcopy, serializeTableF = serializeTableF, func_header_generate_structs = func_header_generate_structs}