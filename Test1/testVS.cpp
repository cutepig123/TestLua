//reference
// error handling:
//	http://lua-users.org/lists/lua-l/2007-01/msg00566.html

// c call lua
//  http://hi.baidu.com/combojiang/item/df605a3e77549680c2cf2996

#include<iostream>
#include<string>
using namespace std;
#include<lua.hpp>
#include<luabind/function.hpp>

void testFunc()
{
    cout<<"CPP>>helo there, i am a cpp fun"<<endl;
}
int main(int argc, char* argv[])
{
    //首先声明luaState环境
	getchar();
    using namespace luabind;
    lua_State* L = lua_open();    //也可以用luaL_newState()函数
    luaL_openlibs(L);    //注意将lua默认库打开，要不会出现N多错误的，比如print函数都没有
    //将c++中的函数暴露给lua
    module(L, "cppapi")
    [
        def("testFunc", (void(*)(void))testFunc)
    ];
    //加载lua脚本，我们临时起名test.lua
    int ret =luaL_dofile(L, "test.lua");
	if(ret) goto Exit;
    //try
    {
        //调用lua中的整形全局变量
        int nLuaGlobal =     luabind::object_cast<int>(luabind::globals(L)["nGlobal"]) ;
		printf("CPP>>Lua variable nLuaGlobal=%d\n",nLuaGlobal);
        //调用lua中的字符串变量
        string strLuaGlobal = luabind::object_cast<string>(luabind::globals(L)["strGlobal"]);
		printf("CPP>>Lua variable strLuaGlobal=%s\n",strLuaGlobal.c_str());
        //获取table,方法一，通过luabind::object 固有方法
		luabind::object luaTable = luabind::globals(L)["t"] ;
		string name=luabind::object_cast<string>(luaTable["name"]) ;
        int age = luabind::object_cast<int>(luaTable["age"]) ;
		printf("CPP>>Lua variable name=%s, age=%d\n",name.c_str(),age);
        //获取table，方法二，通过gettable
        string desc = luabind::object_cast<string>(luabind::gettable(luaTable,"desc"));
		printf("CPP>>Lua variable desc=%s\n",desc.c_str());
        //下面是调用lua中函数
        int nAddRes = luabind::call_function<int>(L, "add", 3, 4) ;
		printf("CPP>>Lua function add result =%d\n",nAddRes);
		printf("CPP>>Lua function strEcho\n",nAddRes);
        string strEchoRes = luabind::call_function<string>(L, "strEcho", "c++参数") ;
		
    }
    //catch(...)
    //{
    //    cout<<"error"<<endl;
    //}
Exit:
	if(ret)
		printf("%s\n", lua_tostring(L, -1));
    return ret;
}


