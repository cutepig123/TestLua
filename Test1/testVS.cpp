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
    //��������luaState����
	getchar();
    using namespace luabind;
    lua_State* L = lua_open();    //Ҳ������luaL_newState()����
    luaL_openlibs(L);    //ע�⽫luaĬ�Ͽ�򿪣�Ҫ�������N�����ģ�����print������û��
    //��c++�еĺ�����¶��lua
    module(L, "cppapi")
    [
        def("testFunc", (void(*)(void))testFunc)
    ];
    //����lua�ű���������ʱ����test.lua
    int ret =luaL_dofile(L, "test.lua");
	if(ret) goto Exit;
    //try
    {
        //����lua�е�����ȫ�ֱ���
        int nLuaGlobal =     luabind::object_cast<int>(luabind::globals(L)["nGlobal"]) ;
		printf("CPP>>Lua variable nLuaGlobal=%d\n",nLuaGlobal);
        //����lua�е��ַ�������
        string strLuaGlobal = luabind::object_cast<string>(luabind::globals(L)["strGlobal"]);
		printf("CPP>>Lua variable strLuaGlobal=%s\n",strLuaGlobal.c_str());
        //��ȡtable,����һ��ͨ��luabind::object ���з���
		luabind::object luaTable = luabind::globals(L)["t"] ;
		string name=luabind::object_cast<string>(luaTable["name"]) ;
        int age = luabind::object_cast<int>(luaTable["age"]) ;
		printf("CPP>>Lua variable name=%s, age=%d\n",name.c_str(),age);
        //��ȡtable����������ͨ��gettable
        string desc = luabind::object_cast<string>(luabind::gettable(luaTable,"desc"));
		printf("CPP>>Lua variable desc=%s\n",desc.c_str());
        //�����ǵ���lua�к���
        int nAddRes = luabind::call_function<int>(L, "add", 3, 4) ;
		printf("CPP>>Lua function add result =%d\n",nAddRes);
		printf("CPP>>Lua function strEcho\n",nAddRes);
        string strEchoRes = luabind::call_function<string>(L, "strEcho", "c++����") ;
		
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


