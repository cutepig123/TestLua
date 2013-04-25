path E:\soft\boost_1_47_0\boost_1_47_0;F:\Program Files\Lua\5.1\lib;F:\lua\luabind-0.9.1\bin\msvc-10.0\debug;%path%
set BOOST_ROOT=E:\soft\boost_1_47_0\boost_1_47_0
set LUA_PATH=F:\Program Files\Lua\5.1
copy boost-build.jam F:\lua\luabind-0.9.1
pushd F:\lua\luabind-0.9.1
bjam
