---- importing ----
print (1)

-- a helper to print a Lua table
function print_table(t)
    print(table.concat(t,","))
end

-- a helper to print a C array
function print_array(arr,len)
    for i=0,len-1 do
        io.write(example.int_getitem(arr,i),",")
    end
    io.write("\n")
end

print (2)
math.randomseed(0)  -- init random

print (3)
--[[ version 1: passing a C array to the code
let's test call sort_int()
this requires a C array, so is the hardest to use]]
ARRAY_SIZE=10
arr=example.new_int(ARRAY_SIZE)
print (4)

for i=0,ARRAY_SIZE-1 do
    example.int_setitem(arr,i,math.random(1000))
end
print ("unsorted")
print_array(arr,ARRAY_SIZE)
example.sort_int(arr,ARRAY_SIZE)
print "sorted"
print_array(arr,ARRAY_SIZE)
example.delete_int(arr) -- must delete it
print ""

--[[ version 2: using %luacode to write a helper
a simpler way is to use a %luacode
which is a lua function added into the module
this can do the conversion for us
so we can just add a lua table directly
(what we do is move the lua code into the module instead)
]]
t={}
for i=1,ARRAY_SIZE do
    t[i]=math.random(1000)
end
print "unsorted"
print_table(t)
example.sort_int2(t) -- calls lua helper which then calls C
print "sorted"
print_table(t)
print ""

--[[ version 3: use a typemap
this is the best way
it uses the SWIG-Lua typemaps to do the work
one item of note: the typemap creates a copy, rather than edit-in-place]]
t={}
for i=1,ARRAY_SIZE do
    t[i]=math.random(1000)/10
end
print "unsorted"
print_table(t)
t=example.sort_double(t) -- replace t with the result
print "sorted"
print_table(t)

