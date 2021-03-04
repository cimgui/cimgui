local M = {}

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
function M.prtable(...)
	for i=1, select('#', ...) do
		local t = select(i, ...)
		print(ToStr(t))
		print("\n")
	end
end
local function str_split(str, pat)
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
local function strsplit(str, pat)
    local t = {} 
	local t2 = {}
    local fpat = "(.-)" .. pat
    local last_end = 1
    local s, e, cap, cap2 = str:find(fpat, 1)
    while s do
        table.insert(t,cap)
		table.insert(t2,cap2)
        last_end = e+1
        s, e, cap, cap2 = str:find(fpat, last_end)
    end
    if last_end <= #str then
        cap = str:sub(last_end)
        table.insert(t, cap)
    elseif str:sub(-1)==pat then
        table.insert(t, "")
    end
    return t,t2
end
M.strsplit = strsplit
local function split_comment(line)
    local comment = line:match("(%s*//.*)") --or ""
    line = line:gsub("%s*//.*","")
    line = line:gsub("%s*$","")
    return line,comment
end
M.split_comment = split_comment
local function clean_comments(txt)
	local comms = ""
	for comm in txt:gmatch("(%s*//[^\n]*)") do
		comms = comms..comm
	end
	txt = txt:gsub("%s*//[^\n]*","")
	return txt,comms
end
local function strip(cad)
    return cad:gsub("^%s*(.-)%s*$","%1") --remove initial and final spaces
end
local function strip_end(cad)
    return cad:gsub("^(.-)%s*$","%1") --remove  final spaces
end
local function clean_spaces(cad)
    cad = strip(cad)
    cad = cad:gsub("%s+"," ") --not more than one space
    cad = cad:gsub("%s*([%(%),=:%+])%s*","%1") --not spaces with ( , ) or ( = ) or ( : ) or + 
	--name [] to name[]
	cad = cad:gsub("(%S)%s(%[)","%1%2")
	--clean %d * %d (could be done above but type*name should be treated different in other places)
	cad = cad:gsub("(%d)%s*(%*)%s*(%d)","%1%2%3")
    return cad
end

------------------------------------
local function parse_enum_value(value, allenums,dontpost)
	local function clean(val)
		if type(val)=="string" then
			return clean_spaces(val)
		else
			return val
		end
	end
	
	if type(value)=="number" then
		return value
	elseif type(value)=="string" then 
		--numbers
		local numval = tonumber(value)
		if numval then return numval end 
		--already in allenums
		if allenums[clean(value)] then return allenums[clean(value)] end
		--must be several and operators
		------------precedence order (hope not ())
		--first drop outer ()
		value = value:gsub("^(%()",""):gsub("(%))$","")
		assert(not value:match("[%(%)]"),value)
		
		local several,seps = strsplit(value,"([<>&|~%+]+)") 
		--M.prtable(value,several,seps)
		assert(#seps+1==#several)
		
		local i = 1
		local ik = 1
		local sepk = {"~","<<",">>","&","^","|","+"}
		while(#seps>0) do
			local sep = sepk[ik]
			local v = seps[i]
			if sep==v then
				local val1 = clean(several[i])
				local val2 = clean(several[i+1])
				if allenums[val1] then val1 = allenums[val1] end
				if allenums[val2] then val2 = allenums[val2] end
				--clean 1u
				if type(val1)=="string" then val1 = val1:gsub("(%d)(u)$","%1") end
				if type(val2)=="string" then val2 = val2:gsub("(%d)(u)$","%1") end
				--for getting numbers from "1ULL"
				if type(val1)=="string" then val1 = loadstring("return "..val1)() end
				if type(val2)=="string" then val2 = loadstring("return "..val2)() end
				if v=="~" then
					assert(several[i]==" " or several[i]=="")
					several[i] = bit.bnot(val2)
				elseif v=="<<" then
					several[i] = bit.lshift(val1,val2)
				elseif v==">>" then
					several[i] = bit.rshift(val1,val2)
				elseif v=="&" then
					several[i] = bit.band(val1,val2)
				elseif v=="^" then
					error"^ operator still not done"
				elseif v=="|" then
					several[i] = bit.bor(val1,val2)
				elseif v=="+" then
					several[i] = val1 + val2
				else
					error("unknown operator "..v)
				end
				table.remove(several,i+1)
				table.remove(seps,i)
			else
				i = i + 1
			end				

			if i>#seps then
				ik = ik + 1 --next operator
				if ik > #sepk then break end
				i = 1
			end
		end
		if #seps>0 or type(several[1])~="number" and not dontpost then
			--M.prtable("enline",enline)
			print("parse_enum_value WARNING",value,several[1])
			--M.prtable(several,seps)
			--M.prtable("allenums",allenums)
		end
		assert(#seps==0)
		assert(type(several[1])=="number" or type(several[1])=="cdata")
		--converst 1ULL to "1ULL"
		if type(several[1])=="cdata" then several[1] = tostring(several[1]) end
		return several[1]
	end
end
M.parse_enum_value = parse_enum_value
--------------------------------------------------------------------------
local function save_data(filename,...)
    local file,err = io.open(filename,"w")
    if not file then error(err) end
    for i=1, select('#', ...) do
        local data = select(i, ...)
        file:write(data)
    end
    file:close()
end
M.save_data = save_data
----------------------------------------
local function  read_data(filename)
    local hfile,err = io.open(filename,"r")
    if not hfile then error(err) end
    local hstrfile = hfile:read"*a"
    hfile:close()
    return hstrfile
end
M.read_data = read_data
------------------------------------------------------------
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
M.copyfile = copyfile

--gives the re table
local function getRE()
	local res = {
	function_re = "^([^;{}]+%b()[\n%s]*;)%s*",
	function_re = "^([^;{}=]+%b()[\n%s%w]*;)", --const at the end
	struct_re = "^([^;{}]-struct[^;{}]-%b{}[%s%w_%(%)]*;)",
	enum_re = "^([^;{}]-enum[^;{}]-%b{}[%s%w_%(%)]*;)",
	union_re = "^([^;{}]-union[^;{}]-%b{}[%s%w_%(%)]*;)",
	structenum_re = "^([^;{}]-%b{}[%s%w_%(%)]*;)",
	namespace_re = "^([^;{}]-namespace[^;{}]-%b{})",
	class_re = "^([^;{}]-class[^;{}]-%b{}%s*;)",
	typedef_re = "^\n*%s*(typedef[^;]+;)",
	typedef_st_re = "^\n*(typedef%s+struct%s*%b{}.-;)",
	functypedef_re = "^\n*%s*(typedef[%w%s%*_]+%(%s*%*%s*[%w_]+%s*%)%s*%b()%s*;)",
	functypedef_re = "^\n*%s*(typedef[%w%s%*_]+%([^*]*%*?%s*[%w_]+%s*%)%s*%b()%s*;)",
	--vardef_re = "^\n*([^;{}%(%)]+;)",
	--change for things as
	--[[ImU8 Used4kPagesMap[((sizeof(ImWchar16) == 2 ? 0xFFFF : 0x10FFFF)+1)/4096/8];]]
	vardef_re = "^\n*([^;{}]+;)",
	functionD_re = "^([^;{}]-%b()[\n%s%w]*%b{}%s-;*)",
	--functionD_re = "^([^;{}]-%b()[^{}%(%)]*%b{})",
	functype_re = "^%s*[%w%s%*]+%(%*[%w_]+%)%([^%(%)]*%)%s*;",
	comment_re = "^%s*//[^\n]*",
	comment2_re = "^%s*/%*.-%*/"
	}
	
	local resN = {"comment2_re","comment_re","functypedef_re","functype_re","function_re","functionD_re","typedef_st_re","struct_re","enum_re","union_re","namespace_re","class_re","typedef_re","vardef_re"}
	
	return res,resN
end
local function isLeaf(re)
	return (re ~= "typedef_st_re" and re ~= "struct_re" and re~="namespace_re" and re~="class_re")
end
M.getRE = getRE
--takes preprocesed file in table cdefsor and returns items
local function parseItems(txt,linenumdict, itparent, dumpit)
	--assert(loca)
	--dumpit = true
	local res,resN = getRE()
	
	local ini = 1
	local item
	local items = {}
	local itemarr = {}
	local outercomms = {}
	while true do
		local found = false
		for ire,re_name in ipairs(resN) do
			local re = res[re_name]
			local i,e = txt:find(re,ini)
			if i then
				item = txt:sub(i,e)
				------------------
				--[[
				--if re~=functionD_re then --skip defined functions
					item = item:gsub("extern __attribute__%(%(dllexport%)%) ","")
					table.insert(itemarr,{re_name=re_name,item=item,locat=loca})
				--end
				items[re_name] = items[re_name] or {}
				table.insert(items[re_name],item)
				--]]
				--------------------
				if re_name=="comment_re" or re_name=="comment2_re" then
					--[[
					table.insert(outercomms,item)
					-- comments to previous item
					if itemarr[#itemarr] then 
						local prev = itemarr[#itemarr].comments or ""
						itemarr[#itemarr].comments = prev .. item 
					end
					--]]
					--comments begining with \n will go to next item
					if item:match("^%s*\n") then
						table.insert(outercomms,item)
					else
						-- comments to previous item
						if itemarr[#itemarr] then 
							local prev = itemarr[#itemarr].comments or ""
							itemarr[#itemarr].comments = prev .. item 
						end
					end
				else
					--item,inercoms = clean_comments(item)
					local itemold = item
					item = item:gsub("extern __attribute__%(%(dllexport%)%) ","")
					local comments = table.concat(outercomms,"\n") --..inercoms
					if comments=="" then comments=nil end
					outercomms = {}
					local loca
					if linenumdict then
						local itemfirstline = itemold:match("[^\n]+")
						loca = linenumdict[itemfirstline]
						if type(loca)=="table" then
							--local prevloca = itemarr[#itemarr] and itemarr[#itemarr].locat
							--print("loca is table for",itemfirstline)
							--print("prevloca is",prevloca)
							--print("parent loca is",itparent and itparent.locat)
							-- for ii,ss in ipairs(loca) do
								-- print(ii,ss)
							-- end
							loca = table.remove(loca,1)
						end
						if not loca then
							print(string.format("%q , %q ",itemold,itemfirstline),#itemfirstline)
							for k,v in pairs(linenumdict) do
								if k:match(itemfirstline) then
									print(string.format("%q",k),#k)
								end
							end
							error"no entry in linenumdict"
						end
					else
						error"no linenumdict"
					end
					table.insert(itemarr,{re_name=re_name,item=item,locat=loca})--,comments=comments})
					items[re_name] = items[re_name] or {}
					table.insert(items[re_name],item)
				end
				-----------------------
				found = true
				ini = e + 1
				if dumpit then
					print(item)
					print(ire,re_name,"------------------------------------------------------")
				end
				break
			end
		end
		if not found then
			if not (ini >= #txt) then 
				local rest = txt:sub(ini)
				local onlyspaces = rest:match("^%s*$")
				if not onlyspaces then
					print(ini,#txt);
					print(txt);
					print"item:"
					print(item)
					error"parseItems error"
				end
			end
			break 
		end
	end
	return itemarr,items
end
M.parseItems = parseItems
local function name_overloadsAlgo(v)

    local aa = {}
    local bb = {}
    local done = {}
    local maxnum = 0
    for i,t in ipairs(v) do
        bb[i] = ""
		local signature = t.signature:match("%b()")
		signature = signature:sub(2,-2)
		--add const function
		if t.signature:match("const$") then
			signature = signature .. ",_const"
		end
        aa[i] = {}
        local num = 1
        for typec in signature:gsub("(%(.-%))", function(x) return x:gsub(",","\0") end):gmatch(".-([^,]+),?") do
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
            keys[aa[i][l]] = 1 + (keys[aa[i][l]] or 0)
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
                    -- if keys[aa[i][l]] == 1 then
                        -- done[i] = true
                    -- end
                end
            end
        end
		--test done
		for i=1,#v do
			done[i] = true
			for j=1,#v do
				if i~=j and bb[i]==bb[j] then
					done[i] = false
				end
			end
		end
    end
	--avoid empty postfix which will be reserved to generic
	for i,v in ipairs(bb) do if v=="" then bb[i]="Nil" end end
    return aa,bb
end
local function typetoStr(typ)
	--print("typetoStr",typ)
    --typ = typ:gsub("[^%(%)]+%(%*?(.+)%).+","%1") -- funcs
    --typ = typ:gsub("[^%(%)]+%(%*?(.+)%).+","FnPtr")
    typ = typ:gsub("([^%(%)]+)%(%*?(.+)%).+","Fn%1Ptr")
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
    --typ = typ:gsub("ImStr","STR")
    typ = typ:gsub("Im","")
    typ = typ:gsub("[<>]","")
    return typ
end
--used to clean signature in function ptr argument
local function clean_names_from_signature(self,signat)
	local rest = signat:sub(2,-2)
	local arg,restt,typ,name
	local result = "("
	while true do
		arg,restt = rest:match(",*([^,%(%)]+),*(.*)")
        if not arg then break end
        rest = restt
		if arg:match("%.%.%.") then 
           typ="...";name="..."
        else
           typ,name = arg:match("(.+)%s([^%s]+)")
        end
		if not typ or not name or name:match"%*" or M.c_types[name]  or self.typedefs_dict[name] then
            print("clean_names_from_signature bad argument name",funcname,typ,name,arg)
			typ = arg
			name = ""
        end
        --float name[2] to float[2] name
		--[[
        local siz = name:match("(%[%d*%])")
        if siz then
            typ = typ..siz
            name = name:gsub("(%[%d*%])","")
        end
		--]]
		result = result .. typ .. ","
	end
	result = result:sub(1,-2) .. ")"
	return result
end
local function parseFunction(self,stname,itt,namespace,locat)
	local lineorig,comment = split_comment(itt.item)
	line = clean_spaces(lineorig)
	--move *
	line = line:gsub("%s*%*","%*")
	line = line:gsub("%*([%w_])","%* %1")
	line = line:gsub("(%(%*)%s","%1")

	--print(line)
    --clean implemetation
    line = line:gsub("%s*%b{}","")
    --clean attribute
    line = line:gsub("%s*__attribute__%b()","")
    --clean static and inline and mutable
	local is_static_function
	if line:match("static") and stname~="" then
		--print("parseFuncion static",line)
		is_static_function = true
	end
    line = line:gsub("static","")
	line = line:gsub("inline","")
	line = line:gsub("mutable","")
	line = line:gsub("explicit","")
	--skip operator
	if line:match("operator") then return end
	--skip template
	if line:match("template") then 
		--print("template",lineorig)
		return 
	end
    
    local ret = line:match("([^%(%):,]+[%*%s])%s?~?[_%w]+%b()")
    --local funcname, args = line:match("(~?[_%w]+)%s*(%b())")
	local funcname, args, extraconst = line:match("(~?[_%w]+)%s*(%b())(.*)")
	extraconst = extraconst:match("const")

	if not args then
		print"not getting args in"
		print(line,lineorig)
		print(funcname,"args",args)
		error"parseFunction not getting args"
    end
	
	
	local argsp = args:sub(2,-2)..","
	local argsTa = {}
	for tynam in argsp:gmatch("([^,]+),") do
		if tynam:match("%)") and not tynam:match("%b()") then
			--patenthesis not closed are merged in previous (happens in some defaults)
			argsTa[#argsTa] = argsTa[#argsTa]..","..tynam
			while argsTa[#argsTa]:match("%)") and not argsTa[#argsTa]:match("%b()") do
				argsTa[#argsTa-1] = argsTa[#argsTa-1] .. "," .. argsTa[#argsTa]
				argsTa[#argsTa] = nil
			end
		else
			argsTa[#argsTa+1] = tynam
		end
	end
	--- templates in args
	for i,ar in ipairs(argsTa) do
		--TODO several diferent templates
		local ttype,template = ar:match("([^%s,%(%)]+)%s*<(.-)>")

		local te=""
		if template then
			if self.typenames[stname] ~= template then --rule out template typename
			te = template:gsub("%s","_")
			te = te:gsub("%*","Ptr")
	
			self.templates[ttype] = self.templates[ttype] or {}
			self.templates[ttype][template] = te
			te = "_"..te
			end
		end
	    argsTa[i] = ar:gsub("<([%w_%*%s]+)>",te) --ImVector
	end
	
	--get typ, name and defaults
	local functype_re =        "^%s*[%w%s%*]+%(%*[%w_]+%)%([^%(%)]*%)"
    local functype_reex =     "^(%s*[%w%s%*]+)%(%*([%w_]+)%)(%([^%(%)]*%))"
    local functype_arg_rest = "^(%s*[%w%s%*]+%(%*[%w_]+%)%([^%(%)]*%)),*(.*)"
	local argsTa2 = {}
	local noname_counter = 0
	for i,ar in ipairs(argsTa) do
		local typ,name,retf,sigf,reftoptr,defa,ar1
		if ar:match(functype_re) then
			local t1,namef,t2 = ar:match(functype_reex)
            typ, name = t1.."(*)"..t2, namef
            retf = t1
            sigf = t2
		else
			reftoptr = nil
			if ar:match("&") then
				if ar:match("const") then
					ar = ar:gsub("&","")
				else
					ar = ar:gsub("&","*")
					reftoptr = true
				end
            end
			if ar:match("%.%.%.") then 
				typ, name = "...", "..."
			else
				ar1,defa = ar:match"([^=]+)=([^=]+)"
				ar1 = ar1 or ar
				typ,name = ar1:match("(.+)%s([^%s]+)")
			end
			if not typ or not name or name:match"%*" or M.c_types[name]  or self.typedefs_dict[name] then
				print("bad argument name",funcname,typ,name,ar)
				ar1,defa = ar:match"([^=]+)=([^=]+)"
				ar1 = ar1 or ar
				typ = ar1
				noname_counter = noname_counter + 1
				name = "noname"..noname_counter
			end
			--float name[2] to float[2] name
            local siz = name:match("(%[%d*%])")
            if siz then
                typ = typ..siz
                name = name:gsub("(%[%d*%])","")
            end
		end
		argsTa2[i] = {type=typ,name=name,default=defa,reftoptr=reftoptr,ret=retf,signature=sigf}
		if ar:match("&") and not ar:match("const") then
            --only post error if not manual
            local cname = self.getCname(stname,funcname, namespace) --cimguiname
            if not self.manuals[cname] then
                print("reference to no const arg in",funcname,argscsinpars,ar)
            end
        end
	end
	
	local argsArr = argsTa2

	--recreate argscsinpars, call_args and signature from argsArr
	local asp, caar,signat
	if #argsArr > 0 then
		asp = "("
		caar = "("
		signat = "("
		for i,v in ipairs(argsArr) do
			if v.ret then --function pointer
				asp = asp .. v.ret .. "(*" .. v.name .. ")" .. v.signature .. ","
				caar = caar .. v.name .. ","
				signat = signat .. v.ret .. "(*)" .. clean_names_from_signature(self,v.signature) .. ","
			else
				local siz = v.type:match("(%[%d*%])") or ""
				local typ = v.type:gsub("(%[%d*%])","")
				asp = asp .. typ .. (v.name~="..." and " "..v.name or "") .. siz .. ","
				local callname = v.reftoptr and "*"..v.name or v.name 
				caar = caar .. callname .. ","
				signat = signat .. typ .. siz .. ","
			end
		end
		asp = asp:sub(1,-2)..")"
		caar = caar:sub(1,-2)..")"
		signat = signat:sub(1,-2)..")" .. (extraconst or "")
	else
		asp = "()"
		caar = "()"
		signat = "()" .. (extraconst or "")
	end

    ------------------------------
    
    if not ret and stname then --must be constructors
        if not (stname == funcname or "~"..stname==funcname) then --break end
            print("false constructor:",line);
            print("b2:",ret,stname,funcname,args)
            return --are function defs
        end
    end
    
    local cimguiname = self.getCname(stname,funcname, namespace)
    table.insert(self.funcdefs,{stname=stname,funcname=funcname,args=args,signature=signat,cimguiname=cimguiname,call_args=caar,ret =ret})
	local defsT = self.defsT
	            defsT[cimguiname] = defsT[cimguiname] or {}
                table.insert(defsT[cimguiname],{})
                local defT = defsT[cimguiname][#defsT[cimguiname]] 
    defT.defaults = {}
	for i,ar in ipairs(argsArr) do
		if ar.default then
			defT.defaults[ar.name] = ar.default
			ar.default = nil
		end
	end
	defT.templated = self.typenames[stname] and true
	defT.namespace = namespace
    defT.cimguiname = cimguiname
    defT.stname = stname
    defT.is_static_function = is_static_function
    defT.funcname = funcname
    defT.argsoriginal = args
    defT.args= asp 
    defT.signature = signat --signature
    defT.call_args = caar --call_args
    defT.isvararg = signat:match("%.%.%.%)$")
    defT.location = locat
    local comentario = (itt.comments or "")..(comment or "")
	if comentario=="" then comentario=nil end
    defT.comment = comentario
    defT.argsT = argsArr
    if self.get_manuals(defT) then
        defT.manual = true
    end
    if self.get_skipped(defT) then
        defT.skipped = true
    end
    if ret then
        defT.ret = clean_spaces(ret:gsub("&","*"))
        defT.retref = ret:match("&")
        -- if defT.ret=="ImVec2" or defT.ret=="ImVec4" or defT.ret=="ImColor" then
            -- defT.ret = defT.ret.."_Simple"
        -- end
    end
	defsT[cimguiname][signat] = defT
end
local function itemsCount(items)
	print"------------items"
	local res,resN = getRE()
	for k,v in pairs(resN) do
		local its = items[v]
		print(v,its and #its or 0)
	end
end

local function AdjustArguments(FP)
    for fun,defs in pairs(FP.defsT) do
        --struct function but no constructors or static functions
        if defs[1].stname~="" and defs[1].ret and not defs[1].is_static_function then
            --print("adjusting",fun)
            for i,def in ipairs(defs) do
                local empty = def.args:match("^%(%)") --no args
                --local ptret = def.retref and "&" or ""
                def.args = def.args:gsub("^%(","("..def.stname.."* self"..(empty and "" or ","))
                table.insert(def.argsT,1,{type=def.stname.."*",name="self"})
            end
        end
    end
end
local function ADDIMSTR_S(FP)
    local defsT = FP.defsT
    local newcdefs = {}
    for numcdef,t in ipairs(FP.funcdefs) do
		newcdefs[#newcdefs+1] = t
        if t.cimguiname then
        local cimf = defsT[t.cimguiname]
        local defT = cimf[t.signature]

        --if isIMSTR return generate _S version
		local isIMSTR = false
		for i,arg in ipairs(defT.argsT) do
			if arg.type == "ImStrv" then isIMSTR=true;break end
		end
        --if defT.ret=="ImVec2" or defT.ret=="ImVec4" or defT.ret=="ImColor" then
		--if isIMSTR then print(t.cimguiname,defT.ov_cimguiname,defT.argsoriginal,"isIMSTR") end
		if isIMSTR then
            --passing as a pointer arg
            local defT2 = {}
            --first strings
            for k,v in pairs(defT) do
                defT2[k] = v
            end
            --then argsT table
            defT2.argsT = {}
            for k,v in ipairs(defT.argsT) do
				local typ = v.type == "ImStrv" and "const char*" or v.type
                table.insert(defT2.argsT,{type=typ,name=v.name})
            end
			--defaults table
			defT2.defaults = {}
			for k,v in pairs(defT.defaults) do
				defT2.defaults[k] = v
            end
            defT2.args = defT2.args:gsub("ImStrv","const char*")
			--recreate call_args for wrapping into ImStrv
			local caar
			if #defT.argsT > 0 then
				caar = "("
				for i,v in ipairs(defT.argsT) do
					local name = v.name 
					if v.ret then --function pointer
						caar = caar .. name .. ","
					else
						local callname = v.reftoptr and "*"..name or name 
						caar = caar .. callname .. ","
					end
				end
				caar = caar:sub(1,-2)..")"
			else
				caar = "()"
			end
			defT2.call_args = caar 
			------------------
            defT2.signature = defT.signature:gsub("ImStrv","const char*") --.."_S"
            defT2.ov_cimguiname = defT2.ov_cimguiname .. "_Strv"
            defT2.isIMSTR_S = 1
			-- check there is not an equal version in imgui_stname
			local doadd = true
			for i,dd in ipairs(cimf) do
				if dd.signature == defT2.signature then 
					doadd = false;
					print("skip _S addition",defT2.cimguiname)
					break 
				end
			end
			--add _S version
			if doadd then
			cimf[#cimf+1] = defT2
			cimf[defT2.signature] = defT2
			newcdefs[#newcdefs+1] = {stname=t.stname,funcname=t.funcname,args=defT2.args,signature=defT2.signature,cimguiname=defT2.cimguiname,ret =defT2.ret}
			end
        end
		else print("not cimguiname in");M.prtable(t)
        end
    end
	FP.funcdefs = newcdefs
end
local function ADDnonUDT(FP)
    local defsT = FP.defsT
    --local newcdefs = {}
    for numcdef,t in ipairs(FP.funcdefs) do
        if t.cimguiname then
        local cimf = defsT[t.cimguiname]
        local defT = cimf[t.signature]
		--find index
		local index
		for ind,ddd in ipairs(cimf) do
			if ddd == defT then index=ind; break end
		end
        --if UDT return generate nonUDT version
		local isUDT = false
		for _,udt_ret in ipairs(FP.UDTs) do
			if udt_ret == defT.ret then isUDT=true;break end
		end
        --if defT.ret=="ImVec2" or defT.ret=="ImVec4" or defT.ret=="ImColor" then
		if isUDT then
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
            defT2.ov_cimguiname = (defT2.ov_cimguiname or defT2.cimguiname) --.."_nonUDT"
            defT2.nonUDT = 1
            defT2.retref = nil
			
			--replace
			cimf[index] = defT2
			cimf[t.signature] = defT2
			FP.funcdefs[numcdef] = {stname=t.stname,funcname=t.funcname,args=args,signature=t.signature,cimguiname=t.cimguiname,ret =t.ret}
			
            -- defsT[t.cimguiname][#defsT[t.cimguiname] + 1] = defT2
            -- defsT[t.cimguiname][t.signature.."nonUDT"] = defT2
            -- table.insert(newcdefs,{stname=t.stname,funcname=t.funcname,args=args,argsc=argscsinpars,signature=t.signature.."nonUDT",cimguiname=t.cimguiname,call_args=call_args,ret =t.ret})
        end
		else print("not cimguiname in");M.prtable(t)
        end
    end
    -- for i,v in ipairs(newcdefs) do
        -- table.insert(FP.funcdefs,v)
    -- end
end

local function ADDdestructors(FP)
    local defsT = FP.defsT
    local newcdefs = {}

	local keep_dest_locat = {}
	--first get destructor locations
	for numcdef,t in ipairs(FP.funcdefs) do
        if t.cimguiname then
            local defT = defsT[t.cimguiname]
			if not defT[1].ret and not defT[1].constructor then --if constructor not processed
				if defT[1].funcname:match("~") then
					keep_dest_locat[defT[1].stname] = defT[1].location
				end
			end
		else
			assert(false,"no cimguiname")
        end
    end
	
    for numcdef,t in ipairs(FP.funcdefs) do
        newcdefs[#newcdefs+1] = t
        if t.cimguiname then
            local defT = defsT[t.cimguiname]
        if not defT[1].ret and not defT[1].constructor then --if constructor not processed
            if defT[1].funcname:match("~") then
                defsT[t.cimguiname] = nil --clear destructor
                newcdefs[#newcdefs] = nil
            else
				for j,cons in ipairs(defT) do
					cons.constructor = true
				end
				if(defT[1].stname~=defT[1].funcname) then
					print(defT[1].stname, defT[1].funcname)
					error"names should be equal"
				end
				local def = {}
				def.stname = defT[1].stname
				def.templated = defT[1].templated
				def.location = keep_dest_locat[defT[1].stname]
				def.ret = "void"
				def.ov_cimguiname = def.stname.."_destroy"
				def.cimguiname = def.ov_cimguiname
				def.destructor = true
				def.realdestructor = def.location and true
				def.args = "("..def.stname.."* self)"
				def.call_args = "(self)"
				def.signature = "("..def.stname.."*)"
				def.defaults = {}
				def.argsT = {{type=def.stname.."*",name="self"}}
				defsT[def.ov_cimguiname] = {def}
				defsT[def.ov_cimguiname][def.signature] = def
				newcdefs[#newcdefs+1]={stname=def.stname,funcname=def.ov_cimguiname,args=def.args,signature=def.signature,cimguiname=def.cimguiname,call_args=def.call_args,ret =def.ret}
            end
        end
        end
    end
    FP.funcdefs = newcdefs
end

--only basic ending
local c_types = {
    ["bool"]=true,
    ["char"]=true,
    ["int"]=true,
    ["float"]=true,
    ["double"]=true,
    ["short"]=true,
    ["long"]=true,
    ["signed"]=true,
    ["unsigned"]=true,
    ["size_t"]=true,
    ["ptrdiff_t"]=true,
}
M.c_types = c_types
local function check_arg_detection(fdefs,typedefs)
    print"-----------------check arg detection---------------------------"
    for k,defT in pairs(fdefs) do
        for i,def in ipairs(defT) do
            for j,arg in ipairs(def.argsT) do
                --check name is not type, which happens in declaration without name
                if arg.name=="*" or not arg.type or not arg.name or c_types[arg.name] or typedefs[arg.name] then
                    print("bad argument name",arg.name, "in",def.funcname,def.args)
                end
            end
        end
    end
    print"-----------------end check arg detection-----------------------"
end
local function printItems(items)
	local function printItemsKind(items,kind)
		local res,resN = getRE()
		print("---------------------------------------",kind)
		local someit = items[kind]
		if someit then
			for i=1,#someit do print(someit[i]) end
		end
	end
	local res,resN = getRE()
	for k,v in pairs(resN) do
		printItemsKind(items,v)
	end
end
-------------
function M.Parser()
	local par = {}
	local cdefs ={}
	local itemsarr={}
	local items = {}
	par.itemsarr = itemsarr
	par.items = items
	par.defsT = {}
	par.funcdefs = {}
	par.embeded_structs = {}
	par.templates = {}
	par.typenames = {}
	par.typedefs_dict = {}
	par.cname_overloads = {}
	par.manuals = {}
	par.skipped = {}
	par.UDTs = {}

	function par:insert(line,loca)
		--table.insert(cdefs,{line,loca})
		--table.insert(cdefs,{line:gsub("^%s*(.-)%s*$", "%1"),loca})
		table.insert(cdefs,{line:gsub("^(%s*.-)%s*$", "%1"),loca})
	end
	function par.getCname(stname,funcname, namespace)
		if #stname == 0 then return funcname end --top level
		local pre = stname.."_"
		return pre..funcname
	end
	function par.getCname_overload(stname,funcname,signature, namespace)
		local cname = par.getCname(stname,funcname, namespace)
		local ov_cname = par.cname_overloads[cname] and par.cname_overloads[cname][signature] --or cname
		return ov_cname
	end
	function par.get_manuals(def)
		return par.manuals[def.ov_cimguiname] or par.manuals[def.cimguiname]
	end
	function par.get_skipped(def)
		return par.skipped[def.ov_cimguiname] or par.skipped[def.cimguiname]
	end
	function par:take_lines(cmd_line,names,compiler)
		local pipe,err = io.popen(cmd_line,"r")
		if not pipe then
			error("could not execute COMPILER "..err)
		end
		local defines = {}
		for line,loca,loca2 in M.location(pipe,names,defines,compiler) do
			self:insert(line, tostring(loca)..":"..tostring(loca2))
		end
		pipe:close()
		return defines
	end
	function par:do_parse()
		self:parseItems()
		self:gen_structs_and_enums_table()
		self:gen_structs_and_enums()
		self:compute_overloads()
		--self:compute_templated()
		ADDdestructors(self)
	end
	function par:initTypedefsDict()
		--typedefs dictionary
		for i,cdef in ipairs(cdefs) do
			--local line = cdef[1]
			local line = split_comment(cdef[1])
			if line:match("typedef") then
				line = clean_spaces(line)
				local value,key = line:match("typedef%s+(.+)%s+([%w_]+);")
				if key and value then
					self.typedefs_dict[key] = value
				else --try function pointer typedef
					local key = line:match("%(%*([%w_]+)%)%([^%(%)]*%)")
					if key then
						local linet = line
						linet = linet:gsub("typedef ","")
						linet = linet:gsub("%(%*("..key..")%)","(*)")
						self.typedefs_dict[key] = linet
					else
						--try function typedef
						key = line:match("%(([%w_]+)%)%([^%(%)]*%)")
						if key then
							local linet = line
							linet = linet:gsub("typedef ","")
							linet = linet:gsub("%(("..key..")%)","()")
							self.typedefs_dict[key] = linet
						elseif not line:match"typedef%s*struct" then --discard typedef struct
							print("typedef not found")
							print(key,value,line)
						end
					end
				end
			end
		end
	end
	
	function par:Listing(arr,ff)
		for i,it in ipairs(arr) do
			ff(it)
			if not isLeaf(it.re_name) then
				par:Listing(it.childs,ff)
			end
		end
	end
	--recursive item parsing
	function par:parseItemsR2(txt, itparent)
		local itsarr,its = parseItems(txt,self.linenumdict,itparent)
		for i,it in ipairs(itsarr) do
			if not isLeaf(it.re_name) then
				local inner = strip_end(it.item:match("%b{}"):sub(2,-2))
				it.childs = par:parseItemsR2(inner, it)
				for j,child in ipairs(it.childs) do
					child.parent = it
				end
				if it.re_name == "struct_re" then
					local typename = it.item:match("^%s*template%s*<%s*typename%s*(%S+)%s*>")
					local stname = it.item:match("struct%s+(%S+)")
					it.name = stname
					
					local templa1,templa2 = it.item:match("^%s*template%s*<%s*(%S+)%s*(%S+)%s*>")
					if templa1 or templa2 then print("template found",stname,templa1,templa2,"typename",typename) end
					
					if typename or templa2 then -- it is a struct template
						self.typenames = self.typenames or {}
						self.typenames[stname] = typename or templa2
					end
				elseif it.re_name == "namespace_re" then
					it.name = it.item:match("namespace%s+(%S+)")
				end
			end
		end
		return itsarr
	end
	function par:parseItems()
		self:initTypedefsDict()
		
		self.linenumdict = {}
		local cdefs2 = {}
		for i,cdef in ipairs(cdefs) do
			if self.linenumdict[cdef[1]] then
				--print("linenumdict alredy defined for", cdef[1],type(self.linenumdict[cdef[1]]))
				if type(self.linenumdict[cdef[1]])=="string" then
					self.linenumdict[cdef[1]] = {self.linenumdict[cdef[1]], cdef[2]}
				else -- must be table already
					table.insert(self.linenumdict[cdef[1]],cdef[2])
				end
			else
				self.linenumdict[cdef[1]]=cdef[2]
			end
			table.insert(cdefs2,cdef[1])
		end
		local txt = table.concat(cdefs2,"\n")
		
		self.itemsarr = par:parseItemsR2(txt)
		itemsarr = self.itemsarr
	end
	
	function par:printItems()
		printItems(items)
	end
	par.parseFunction = parseFunction
	
	function par:clean_structR1(itst)
		local stru = itst.item
		local outtab = {}
		local commtab = {}
		local predeclare = ""
		--local iner = strip_end(stru:match("%b{}"):sub(2,-2))
		local inistruct = clean_spaces(stru:match("(.-)%b{}"))
		--local stname = stru:match("struct%s*(%S+)%s*%b{}")
		local stname, derived
		if inistruct:match":" then
			stname,derived = inistruct:match"struct%s*([^%s:]+):(.+)"
			derived = derived:match"(%S+)$"
		else
			stname = inistruct:match"struct%s(%S+)"
		end

		if derived then print(stname,"derived from",derived) end
		
		--try to get name from typedef structs
		if not stname and stru:match("typedef struct") then
			stname = stru:match("%b{}%s*(%S+)%s*;")
		end
		
		if not stname then
			print(stru)
			error"could not get stname"
		end
		--initial
		--table.insert(outtab,stru:match("(.-)%b{}"))
		table.insert(outtab,"\nstruct "..stname.."\n")
		table.insert(outtab,"{")
		table.insert(commtab,nil)--"")
		table.insert(commtab,nil)--"")
		if derived then
			table.insert(outtab,"\n    "..derived.." _"..derived..";")
			table.insert(commtab,nil)--"")
		end
		--local itlist,itemsin = parseItems(iner, false,locat)
		local itlist = itst.childs
		if #itlist == 0 then 
			print("clean_struct with empty struc",stname);
			-- M.prtable(itst)
			-- if stname=="StbUndoRecord" then error"dddd" end
			return "" 
		end --here we avoid empty structs
		for j,it in ipairs(itlist) do
			if (it.re_name == "vardef_re" or it.re_name == "functype_re" or it.re_name == "union_re") then
			if  not (it.re_name == "vardef_re" and it.item:match"static") then --skip static variables
				local it2 = it.item --:gsub("<([%w_]+)>","_%1") --templates
				--local ttype,template = it.item:match("([^%s,%(%)]+)%s*<(.+)>")
				local ttype,template =    it.item:match"([^%s,%(%)]+)%s*<(.+)>"
				if template then
					if self.typenames[ttype] ~= template then --rule out T (template typename)
					local te = template:gsub("%s","_")
					te = te:gsub("%*","Ptr")
					self.templates[ttype] = self.templates[ttype] or {}
					self.templates[ttype][template] = te
					it2 = it2:gsub("(<[%w_%*%s]+>)([^%s])","%1 %2") --add if not present space after <>
					it2 = it2:gsub("<([%w_%*%s]+)>","_"..te)
					end
				end
				--clean mutable
				it2 = it2:gsub("mutable","")
				--clean namespaces
				it2 = it2:gsub("%w+::","")
				--clean initializations
				if it.re_name == "vardef_re" then
					it2 = it2:gsub("%s*=.+;",";")
				end
				table.insert(outtab,it2)
				table.insert(commtab,it.comments )--or "")
				end
			elseif it.re_name == "struct_re" then
				--check if has declaration
				local decl = it.item:match"%b{}%s*([^%s}{]+)%s*;"
				if decl then
					table.insert(outtab,"\n    "..it.name.." "..decl..";")
					table.insert(commtab,it.comments )--or "")
				end
				local cleanst,structname,strtab,comstab,predec = self:clean_structR1(it)
				predeclare = predeclare .. predec .. cleanst
			elseif it.re_name == "enum_re" then
				--nop
			elseif it.re_name ~= "functionD_re" and it.re_name ~= "function_re" then
				print(it.re_name,"not processed clean_struct in",stname,it.item:sub(1,24))
				--M.prtable(it)
			end
		end
		--final
		table.insert(outtab,"\n};")
		return table.concat(outtab,""),stname,outtab,commtab, predeclare
	end
	local function get_parents_name(it)
		local parnam = ""
		while it.parent do
			parnam = it.parent.name.."::"..parnam
			it = it.parent
		end
		return parnam
	end
	local function get_parents_nameC(it)
		local parnam = ""
		while it.parent do
			parnam = it.parent.name.."::"..parnam
			it = it.parent
		end
		if parnam~="" then parnam = parnam:sub(1,-3) end
		return parnam
	end
	function par:gen_structs_and_enums()
		local outtab = {} 
		local outtabpre = {}
		local typedefs_table = {}
		self.embeded_enums = {}
		
		local processer = function(it)
			if it.re_name == "typedef_re" or it.re_name == "functypedef_re" or it.re_name == "vardef_re" then
				if not it.parent or it.parent.re_name=="namespace_re" then
					table.insert(outtabpre,it.item)
					-- add typedef after struct name
					if it.re_name == "vardef_re" and it.item:match"^%s*struct" then
						local stname = it.item:match("struct%s*(%S+)%s*;")
						table.insert(typedefs_table,"typedef struct "..stname.." "..stname..";\n")
						self.typedefs_dict[stname]="struct "..stname
						if it.parent then --must be struct name; inside namespace
							local parname = get_parents_name(it)
							self.embeded_structs[stname] = parname..stname
						end
					end
				end
			elseif it.re_name == "enum_re" then
				--local enumname, enumbody = it.item:match"^%s*enum%s+([^%s;{}]+)[%s\n\r]*(%b{})"
				local enumname = it.item:match"^%s*enum%s+([^%s;{}]+)"
				if enumname then
					--if it's an enum with int type changed
					if self.structs_and_enums_table.enumtypes[enumname] then
						local enumtype = self.structs_and_enums_table.enumtypes[enumname]
						local enumbody = ""
						local extraenums = ""
						for i,v in ipairs(self.structs_and_enums_table.enums[enumname]) do
							if type(v.calc_value)=="string" then
								extraenums = extraenums .."\nstatic const "..enumtype.." "..v.name.." = "..v.calc_value..";"
							else
								enumbody = enumbody .. "\n" ..v.name .."="..v.value..","
							end
						end
						enumbody = "{"..enumbody.."\n}"
						table.insert(outtab,"\ntypedef enum ".. enumbody..enumname..";"..extraenums)
					else
						local enumbody = it.item:match"(%b{})"
						enumbody = clean_comments(enumbody)
						table.insert(outtab,"\ntypedef enum ".. enumbody..enumname..";")
					end
					if it.parent then
						if it.parent.re_name == "namespace_re" then
							local namespace = it.parent.item:match("namespace%s+(%S+)")
							self.embeded_enums[enumname] = namespace.."::"..enumname
						end
					end
				else --unamed enum just repeat declaration
					local cl_item = clean_comments(it.item)
					table.insert(outtab,cl_item)
					print("unnamed enum",cl_item)
				end
			elseif it.re_name == "struct_re" or it.re_name == "typedef_st_re" then
				local cleanst,structname,strtab,comstab,predec = self:clean_structR1(it)
				if not structname then print("NO NAME",cleanst,it.item) end
				--if not void stname or templated
				if structname and not self.typenames[structname] then
					--dont insert child structs as they are inserted before parent struct
					if not (it.parent and it.parent.re_name == "struct_re") then
						table.insert(outtab,predec .. cleanst)
					end
					table.insert(typedefs_table,"typedef struct "..structname.." "..structname..";\n")
					self.typedefs_dict[structname]="struct "..structname
				end
				if it.parent  then --and (it.parent.re_name == "struct_re" or it.parent.re_name == "typedef_st_re" then
					local embededst = (it.re_name == "struct_re" and it.item:match("struct%s+(%S+)")) 
					or (it.re_name == "typedef_st_re" and it.item:match("%b{}%s*(%S+)%s*;"))
					--TODO nesting namespace and class
					local parname = get_parents_name(it)
					self.embeded_structs[embededst] = parname..embededst
				end
			elseif it.re_name == "namespace_re" or it.re_name == "union_re" or it.re_name == "functype_re" then
				--nop
			elseif it.re_name == "functionD_re" or it.re_name == "function_re" then
				local stname = ""
				local namespace
				if it.parent then
					if it.parent.re_name == "struct_re" or it.parent.re_name == "typedef_st_re" then
						stname = it.parent.name
					elseif it.parent.re_name == "namespace_re" then
						namespace = get_parents_nameC(it) --it.parent.name
					end
				end
				if it.item:match"^%s*template%s+<" then
					local ttype,fun = it.item:match"^%s*template%s+<%s*typename%s+([^>]+)%s*>%s*(.+)$"
					if self.ftemplate_list and self.ftemplate_list[ttype] then
						for iT,vT in ipairs(self.ftemplate_list[ttype]) do
							local funT = fun:gsub(ttype,vT)
							self:parseFunction(stname,{item=funT},namespace,it.locat)
						end
					end
				else
					self:parseFunction(stname,it,namespace,it.locat)
				end
			else
				print("not processed gen",it.re_name,it.item:sub(1,20))
			end
		end
		
		self:Listing(itemsarr,processer)
		
		local uniques = {}
		for i,l in ipairs(typedefs_table) do
			if not uniques[l] then
				uniques[l] = true
				table.insert(outtabpre,1,l)
			end
		end
		--check arg detection failure if no name in function declaration
		check_arg_detection(self.defsT,self.typedefs_dict)
		local outtabprest, outtabst = table.concat(outtabpre,""),table.concat(outtab,"")
		self.structs_and_enums = {outtabprest, outtabst or ""}
		return outtabprest, outtabst
	end
	-----------
	function par:parse_struct_line(line,outtab,comment)
		local functype_re = "^%s*[%w%s%*]+%(%*[%w_]+%)%([^%(%)]*%)"
		local functype_reex = "^(%s*[%w%s%*]+%(%*)([%w_]+)(%)%([^%(%)]*%))"
		line = clean_spaces(line)
		if line:match(functype_re) then
			local t1,name,t2 = line:match(functype_reex)
			table.insert(outtab,{type=t1..t2,name=name,comment=comment})
		else
			--split type name1,name2; in several lines
			local typen,rest = line:match("%s*([^,]+)%s(%S+[,;])")
            if not typen then -- Lets try Type*name
                typen,rest = line:match("([^,]+%*)(%S+[,;])")
            end
			local template_type 
			for k,v in pairs(self.templates) do
				local template_type2 = typen:match(k.."_(.+)")
				if template_type2 then 
					for k1,k2 in pairs(v) do
						if template_type2==k2 then
							template_type=k1
							break
						end
					end
					assert(template_type)
					break 
				end
			end
			for name in rest:gmatch("([^%s,;]+)%s?[,;]") do
				--unnamed unions
				local union_re = "^([^;{}]-union[^;{}]-%b{}[%s%w_%(%)]*;)"
				if line:match(union_re) and name == "}" then
					typen = typen..name
					name = ""
				end
				local namebitfield,bitfield = name:match("([^:]+):(%d+)") --take care of bitfields
				table.insert(outtab,{type=typen,template_type=template_type,name=namebitfield or name,bitfield=bitfield,comment=comment})
			end
		end
	end
	local unnamed_enum_counter = 0
	local function enums_for_table(it, outtab, enumsordered)
		local enumname = it.item:match"^%s*enum%s+([^%s;{}]+)"
		if not enumname then
			unnamed_enum_counter = unnamed_enum_counter + 1
			enumname = "unnamed"..unnamed_enum_counter
			print("unamed enum",enumname,it.parent and ("parent:"..it.parent.name) or "no parent")
		end
		local enumtype = it.item:match"^%s*enum%s+[^%s;{}:]+%s*:%s*([^{%s]+)"
		if enumtype then 
			print("enumtype",enumtype) 
			outtab.enumtypes[enumname] = enumtype
		end
		outtab.enums[enumname] = {}
		table.insert(enumsordered,enumname)
		local inner = strip_end(it.item:match("%b{}"):sub(2,-2))
		
		--clean comments adding them to last item
		local enumarrtmp = str_split(inner,"\n")
		local enumarr = {}
		for k,lin in ipairs(enumarrtmp) do
			local lin1,comm = split_comment(lin)
			if lin1~="" then
				local lin1arr = str_split(lin1,",")
				for k2,lin1s in ipairs(lin1arr) do
					if lin1s~="" then table.insert(enumarr,lin1s) end
				end
				enumarr[#enumarr] = enumarr[#enumarr] .. (comm or "")
			end 
		end
		
		for j,line in ipairs(enumarr) do
			local comment
			line, comment = split_comment(line)
			assert(line~="")
			local name,value = line:match("%s*([%w_]+)%s*=%s*([^,]+)")
			if value then
				table.insert(outtab.enums[enumname],{name=name,value=value,comment=comment})
				outtab.locations[enumname] = it.locat
			else --increment by one
				local name = line:match("%s*([^,]+)")
				local enum_table = outtab.enums[enumname]
				local prevvalue = enum_table[#enum_table] and enum_table[#enum_table].value
				local value --= enum_table[#enum_table] and (enum_table[#enum_table].value + 1) or 0
				if not prevvalue then
					value = "0"
				elseif tonumber(prevvalue) then
					value = tostring(prevvalue +1)
				else --should be string
					value = prevvalue .. "+1"
				end
				if name then --avoid last , if present
				table.insert(outtab.enums[enumname],{name=name,value=value,comment=comment})
				outtab.locations[enumname] = it.locat
				end
			end
		end
	end
	par.enums_for_table = enums_for_table
	function par:gen_structs_and_enums_table()
		local outtab = {enums={},structs={},locations={},enumtypes={}}
		self.typedefs_table = {}
		local enumsordered = {}
		unnamed_enum_counter = 0
		
		local processer = function(it)
			if it.re_name == "typedef_re" or it.re_name == "functypedef_re" or it.re_name == "vardef_re" then
				if it.re_name == "typedef_re" and not it.parent then
					local typedefdef,typedefname = it.item:match"typedef(.+)%s([^%s;]+);$"
					typedefname = strip(typedefname)
					self.typedefs_table[typedefname] = strip(typedefdef)
				end
			elseif it.re_name == "enum_re" then
				enums_for_table(it, outtab, enumsordered)
			elseif it.re_name == "struct_re" or it.re_name == "typedef_st_re" then
				local cleanst,structname,strtab,comstab = self:clean_structR1(it)
				--if not void stname or templated
				if not structname then print("NO NAME",cleanst,it.item) end
				if structname and not self.typenames[structname] then
					outtab.structs[structname] = {}
					outtab.locations[structname] = it.locat
					for j=3,#strtab-1 do
						self:parse_struct_line(strtab[j],outtab.structs[structname],comstab[j])
					end
				else
					print("skipped unnamed or templated struct",structname)
				end
			elseif it.re_name == "namespace_re" or it.re_name == "union_re" or it.re_name == "functype_re" then
				--nop
			elseif it.re_name ~= "functionD_re" and it.re_name ~= "function_re" then
				print("not processed gen table",it.re_name)
			end
		end
		
		self:Listing(itemsarr,processer)
		
		--calcule size of name[16+1] [xxx_COUNT]
		local allenums = {}
		--first calc_value in enums
		for i,enumname in ipairs(enumsordered) do
		--for enumname,enum in pairs(outtab.enums) do
			local enum = outtab.enums[enumname]
			for i,t in ipairs(enum) do
				t.calc_value = parse_enum_value(t.value,allenums)
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
					else
						local f,err = loadstring("estevalor="..val)
						if not f then print("error on loadstring",err,"with val:",val) end
						f()
						t.size = estevalor
					end
					--assert(t.size,val)
					if not t.size then
						print("not t.size for",val,"in",t.name)
						error"not t.size"
					end
				end
			end
		end
		self.structs_and_enums_table = outtab
		return outtab
	end
	par.alltypes = {}
    local function get_types(v)
        for i,t in ipairs(v) do
            local signature = t.signature:sub(2,-2) -- without parenthesis
            for typec in signature:gsub("(%(.-%))", function(x) return x:gsub(",","\0") end):gmatch(".-([^,]+),?") do
                local key = typec:gsub("%z+", ",")
                par.alltypes[key] = true
            end
        end
    end
    function par:dump_alltypes()
        for k,v in pairs(self.alltypes) do print(k, typetoStr(k) ) end
    end
    function par:compute_overloads()
		--ADDIMSTR_S(self)
        local strt = {}
        local numoverloaded = 0
        self.alltypes = {}
        table.insert(strt,"----------------overloadings---------------------------")
        --require"anima.utils" 
		M.table_do_sorted(self.defsT, function(k,v)
            get_types(v)
            if #v > 1 then
                numoverloaded = numoverloaded + #v
                --print(k,#v)
                table.insert(strt,string.format("%s\t%d",k,#v))
                local typesc,post = name_overloadsAlgo(v)
                for i,t in ipairs(v) do
                    --take overloaded name from manual table or algorythm
                    t.ov_cimguiname = self.getCname_overload(t.stname,t.funcname,t.signature,t.namespace) or k..typetoStr(post[i])
					--check ...
					if( t.ov_cimguiname:match"%.%.%.") then
						print("... in ov",t.ov_cimguiname)
						for i,dd in ipairs(v) do
							print(dd.signature,post[i])
						end
						error"Bad check ..."
					end
                    table.insert(strt,string.format("%d\t%s\t%s %s",i,t.ret,t.ov_cimguiname,t.signature))
                end
                --check not two names are equal (produced by bad cimguiname_overload)
                for i=1,#v-1 do 
                    for j=i+1,#v do
                        if v[i].ov_cimguiname == v[j].ov_cimguiname then
                          local t,tj = v[i],v[j]
                          print("Error caused by Bad overloading "..t.ov_cimguiname.." of function ",t.funcname,t.signature,"conflicts with ",tj.funcname,tj.signature)
                          error("Bad overloading:"..t.ov_cimguiname) 
                        end
                    end
                end
			else
				v[1].ov_cimguiname = v[1].cimguiname
            end
		end)
        --print(numoverloaded, "overloaded")
        table.insert(strt,string.format("%d overloaded",numoverloaded))
		ADDIMSTR_S(self)
		AdjustArguments(self)
		ADDnonUDT(self)

		--ADDdestructors(self)
        self.overloadstxt  = table.concat(strt,"\n")
    end
	local function typename_gsub(cad,typename,tname)
		local str,n = "",0
		if tname:match"%*" then
		str,n = cad:gsub("(const%s+)("..typename..")", tname.." %1")
		end
		if n==0 then
		str,n = cad:gsub("(const%s+)("..typename..")(%s*%*)", tname.." %1%3")
		end
		if n==0 then
		str,n = cad:gsub("([^_%w])("..typename..")([^_%w])", "%1"..tname.."%3")
		end
		if n==0 then
		str,n = cad:gsub("([^_%w])("..typename..")$", "%1"..tname)
		end
		if n==0 then
		str,n = cad:gsub("^("..typename..")(%s*%*)", tname.."%2")
		end
		return str
	end
	function par:compute_templated()
		local defsT = self.defsT
		local newcdefs = {}
		for numcdef,t in ipairs(self.funcdefs) do
			if t.cimguiname then
			local cimf = defsT[t.cimguiname]
			local defT = cimf[t.signature]
			if defT.templated then
				local templates = self.templates[defT.stname]
				local typename = self.typenames[defT.stname]
				for tname,tnamestr in pairs(templates) do
					--local tnamestr = typetoStr(tname)
					local stname = defT.stname .. "_" .. tnamestr
					local cimguiname = t.cimguiname:gsub(defT.stname,stname)
					local ov_cimguiname = defT.ov_cimguiname:gsub(defT.stname,stname)
					local signature = defT.signature:gsub(typename, tname)
					local ret 
					if defT.ret then
						--ret = defT.ret:gsub(typename, tname)
						ret = typename_gsub(defT.ret, typename, tname)
					end

					local args = defT.args:gsub(defT.stname,stname)

					args = typename_gsub(args, typename, tname)
					
					local argsT = {}
					for i,ar in ipairs(defT.argsT) do
						argsT[i] = {}
						for k,v in pairs(ar) do
							if k=="type" then
								v = v:gsub(defT.stname,stname)
								v = typename_gsub(v, typename, tname)
							end
							argsT[i][k]=v
						end
					end
					-----------reconstruct args
					--if(#argsT==0 and not defT.constructor) then M.prtable(defT) end
					--if is const function make self const
					if #argsT>0 and signature:match"const$" then
						argsT[1].type = "const "..argsT[1].type
					end
					
					args = "("
					for i=1,#argsT-1 do
						local ar = argsT[i]
						args = args .. ar.type .. " " ..ar.name .. ","
					end
					local ar = argsT[#argsT]
					if ar then args = args .. ar.type .. " " ..ar.name .. ")" 
					else args = args .. ")" end
					args = args:gsub("&","")
					------------------------------
					
					defTnew = {}
					defTnew.cimguiname = cimguiname
					defTnew.ov_cimguiname = ov_cimguiname
					defTnew.signature = signature
					defTnew.ret = ret
					defTnew.retref = defT.retref
					defTnew.templatedgen = true
					defTnew.call_args = defT.call_args
					defTnew.stname = stname
					local funcname = defT.funcname
					if funcname == defT.stname then --is constructor
						funcname = stname
					end
					defTnew.funcname = funcname
					defTnew.args = args
					defTnew.argsT = argsT
					defTnew.defaults = {}
					--print(cimguiname,ov_cimguiname, signature , ret)
					defsT[cimguiname] = defsT[cimguiname] or {}
					defsT[cimguiname][#defsT[cimguiname] + 1] = defTnew
					defsT[cimguiname][signature] = defTnew
					table.insert(newcdefs,{stname=stname,funcname=t.funcname,args=args,argsc=argscsinpars,signature=signature,cimguiname=cimguiname,call_args=call_args,ret =t.ret})
				end
			end -- templated
			end --cimguiname
		end
		for i,v in ipairs(newcdefs) do
			table.insert(self.funcdefs,v)
		end
	end
	return par
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
---[[
            local ordered_keys = {}
            for k,v in pairs(value) do
                table.insert(ordered_keys,k)
            end
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
            table.sort(ordered_keys,sorter)
            for _,k in ipairs(ordered_keys) do
                local v = value[k]
--]]
           -- for k,v in pairs(value) do      -- save its fields

                local fieldname = string.format("%s[%s]", name,basicSerialize(k))
                table.insert(string_table, serializeTable(fieldname, v, saved))
            end
        end
    --else
        --error("cannot save a " .. type(value))
    end
    
    return table.concat(string_table)
end
M.serializeTable = serializeTable
M.serializeTableF = function(t)
	return M.serializeTable("defs",t).."\nreturn defs"
end
--iterates lines from a gcc/clang -E in a specific location
local function location(file,locpathT,defines,COMPILER)
	local define_re = "^#define%s+([^%s]+)%s+(.+)$"
	local number_re = "^-?[0-9]+u*$"
	local hex_re = "0x[0-9a-fA-F]+u*$"
    local location_re 
    if COMPILER == "cl" then
        location_re = '^#line (%d+) "([^"]*)"'
    else --gcc, clang
        location_re = '^# (%d+) "([^"]*)"'
    end

    local path_reT = {}
    for i,locpath in ipairs(locpathT) do
        table.insert(path_reT,'^.*[\\/]('..locpath..')%.h$')
    end
    local in_location = false
    local which_location = ""
    local loc_num
    local loc_num_incr
    local lineold = "" 
    local which_locationold,loc_num_realold
    local lastdumped = false
    local function location_it()
        repeat
            local line = file:read"*l"
            if not line then
                if not lastdumped then
                    lastdumped = true
                    return lineold, which_locationold,loc_num_realold
                else
                    return nil
                end
            end

            if line:sub(1,1) == "#" then
			--elseif line:match"^%s*#" then
                -- Is this a location pragma?
                local loc_num_t,location_match = line:match(location_re)
                if location_match then
                    in_location = false
                    for i,path_re in ipairs(path_reT) do
						local locpath = location_match:match(path_re)
                        if locpath then 
                            in_location = true;
                            loc_num = loc_num_t
                            loc_num_incr = 0
                            which_location = locpath --locpathT[i]
                            break 
                        end
                    end
				elseif in_location then
					loc_num_incr = loc_num_incr + 1
					local name,val = line:match(define_re)
					if name and val then
						--while defines[val] do val = defines[val] end
						--if val:match(number_re) or val:match(hex_re) then
							table.insert(defines,{name , val})
						--end
					end
                end
				
            elseif in_location then
                local loc_num_real = loc_num + loc_num_incr
                loc_num_incr = loc_num_incr + 1
				--if doprint then print(which_locationold,which_location) end
				if line:match("%S") then --nothing on emptyline
                if (which_locationold~=which_location) or (loc_num_realold and loc_num_realold < loc_num_real) then
                    --old line complete
					--doprint = false
                    local lineR,which_locationR,loc_num_realR = lineold, which_locationold,loc_num_realold
                    lineold, which_locationold,loc_num_realold = line,which_location,loc_num_real
                    return lineR,which_locationR,loc_num_realR
                else
                    lineold=lineold..line
                    which_locationold,loc_num_realold = which_location,loc_num_real
                --return line,loc_num_real, which_location
                end
				end
            end
        until false --forever
    end
    return location_it
end
M.location = location
---------------------- C writing functions
local function ImGui_f_implementation(outtab,def)
    local ptret = def.retref and "&" or ""
    table.insert(outtab,"CIMGUI_API".." "..def.ret.." "..def.ov_cimguiname..def.args.."\n")
    table.insert(outtab,"{\n")
	local namespace = def.namespace and def.namespace.."::" or ""
	namespace = def.is_static_function and namespace..def.stname.."::" or namespace
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
    elseif def.nonUDT then
        if def.nonUDT == 1 then
            table.insert(outtab,"    *pOut = "..namespace..def.funcname..def.call_args..";\n")
        end
    else --standard ImGui
        table.insert(outtab,"    return "..ptret..namespace..def.funcname..def.call_args..";\n")
    end
    table.insert(outtab,"}\n")
end
local function struct_f_implementation(outtab,def)
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
    elseif def.nonUDT then
        if def.nonUDT == 1 then
            table.insert(outtab,"    *pOut = self->"..def.funcname..def.call_args..";\n")
        end
    else --standard struct
        table.insert(outtab,"    return "..ptret.."self->"..def.funcname..def.call_args..";\n")
    end
    table.insert(outtab,"}\n")
end
local function func_implementation(FP)

    local outtab = {}
    for _,t in ipairs(FP.funcdefs) do
        repeat -- continue simulation
        if not t.cimguiname then break end
        local cimf = FP.defsT[t.cimguiname]
        local def = cimf[t.signature]
        assert(def)
        local manual = FP.get_manuals(def)
        if not manual and not def.templated and not FP.get_skipped(def) then 
            if def.constructor then
                assert(def.stname ~= "","constructor without struct")
                local empty = def.args:match("^%(%)") --no args
                table.insert(outtab,"CIMGUI_API "..def.stname.."* "..def.ov_cimguiname..(empty and "(void)" or def.args).."\n")
                table.insert(outtab,"{\n")
                table.insert(outtab,"    return IM_NEW("..def.stname..")"..def.call_args..";\n")
                table.insert(outtab,"}\n")
            elseif def.destructor then
                local args = "("..def.stname.."* self)"
                local fname = def.stname.."_destroy" 
                table.insert(outtab,"CIMGUI_API void "..fname..args.."\n")
                table.insert(outtab,"{\n")
                table.insert(outtab,"    IM_DELETE(self);\n")
                table.insert(outtab,"}\n")
            elseif def.stname == "" or def.is_static_function then
                ImGui_f_implementation(outtab,def)
            else -- stname
                struct_f_implementation(outtab,def)
            end
        end
        until true
    end
    return table.concat(outtab)
end

M.func_implementation = func_implementation
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
M.table_do_sorted = table_do_sorted

local function func_header_generate_structs(FP)

    local outtab = {}

	table_do_sorted(FP.embeded_structs,function(k,v) table.insert(outtab,"typedef "..v.." "..k..";\n") end)
	
	table_do_sorted(FP.embeded_enums,function(k,v) table.insert(outtab,"typedef "..v.." "..k..";\n") end)
	
	table_do_sorted(FP.templates,function(ttype,v)
		table_do_sorted(v,function(ttypein,te)
			table.insert(outtab,"typedef "..ttype.."<"..ttypein.."> "..ttype.."_"..te..";\n")
		end)
	end)
	return outtab
end
M.func_header_generate_structs = func_header_generate_structs

local function func_header_generate_funcs(FP)

    local outtab = {}
   
    for _,t in ipairs(FP.funcdefs) do

        if t.cimguiname then
        local cimf = FP.defsT[t.cimguiname]
        local def = cimf[t.signature]
        assert(def,t.signature..t.cimguiname)
        local manual = FP.get_manuals(def)
        if not manual and not def.templated and not FP.get_skipped(def) then

            local addcoment = "" --def.comment or ""
            local empty = def.args:match("^%(%)") --no args
            if def.constructor then
                assert(def.stname ~= "","constructor without struct")
                table.insert(outtab,"CIMGUI_API "..def.stname.."* "..def.ov_cimguiname ..(empty and "(void)" or def.args)..";"..addcoment.."\n")
            elseif def.destructor then
                table.insert(outtab,"CIMGUI_API void "..def.ov_cimguiname..def.args..";"..addcoment.."\n")
            else --not constructor

                if def.stname == "" or def.is_static_function then --ImGui namespace or top level
                    table.insert(outtab,"CIMGUI_API "..def.ret.." ".. def.ov_cimguiname ..(empty and "(void)" or def.args)..";"..addcoment.."\n")
                else
                    table.insert(outtab,"CIMGUI_API "..def.ret.." "..def.ov_cimguiname..def.args..";"..addcoment.."\n")
                end
            end 
        end
        else --not cimguiname
            table.insert(outtab,t.comment:gsub("%%","%%%%").."\n")-- %% substitution for gsub
        end
    end

    return outtab
end
M.func_header_generate_funcs = func_header_generate_funcs

local function func_header_generate(FP)

    local outtab = func_header_generate_structs(FP)
    table.insert(outtab, 1, "#ifndef CIMGUI_DEFINE_ENUMS_AND_STRUCTS\n")
    table.insert(outtab,"#endif //CIMGUI_DEFINE_ENUMS_AND_STRUCTS\n")
    
    local outtabf = func_header_generate_funcs(FP)
    
    local cfuncsstr = table.concat(outtab)..table.concat(outtabf)
    cfuncsstr = cfuncsstr:gsub("\n+","\n") --several empty lines to one empty line
    return cfuncsstr
end

M.func_header_generate = func_header_generate
--[=[
-- tests
local line = [[struct ImDrawListSharedData
{
    ImVec2 TexUvWhitePixel;
    ImFont* Font;
    float FontSize;
    float CurveTessellationTol;
    float CircleSegmentMaxError;
    ImVec4 ClipRectFullscreen;
    ImDrawListFlags InitialFlags;
    ImVec2 ArcFastVtx[12 * 1];
    ImU8 CircleSegmentCounts[64];
    ImDrawListSharedData();
    void SetCircleSegmentMaxError(float max_error);
};]]
local parser = M.Parser()
parser:insert(line)
parser:do_parse()
--M.prtable(parser)
M.prtable(parser:gen_structs_and_enums_table())
--]=]
--print(clean_spaces[[ImVec2 ArcFastVtx[12 * 1];]])

return M
