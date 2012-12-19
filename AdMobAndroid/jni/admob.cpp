#include "gideros.h"
#include "lua.h"
#include "lauxlib.h"
#define LUA_LIB
#include <jni.h>
//this is for debugginh purpose
//and should be commented out before deployment
//you can log using
//__android_log_print(ANDROID_LOG_DEBUG, "tag", "Output String");
#include <android/log.h>

//some configurations of our plugin
static const char* pluginName = "admob";
static const char* pluginVersion = "1.5";
static const char* javaClassName = "com/giderosmobile/android/plugins/AdMob";

//Store Java Environment reference
static JNIEnv *ENV;
//Store our main class, what we will use as plugin
static jclass cls;
//store modifyString method ID
static jmethodID jloadAd;
static jmethodID jRemoveAd;
static jmethodID jSetAlignment;
static jmethodID jSetHorAl;
static jmethodID jSetVerAl;
static jmethodID jGetHorAl;
static jmethodID jGetVerAl;
static jmethodID jSetVisible;

//load ad
static int loadAd(lua_State *L)
{
	//if no Java Env, exit
	if(ENV == NULL) return 0;
	
	//if no class, try to retrieve it
	if(cls == NULL)
	{
		cls = ENV->FindClass(javaClassName);
		if(!cls) return 0;
	}
	
	//if we don't have method yet, try to retrieve it
	if(jloadAd == NULL)
	{
		/****************
		* 1. argument cls - reference to Java class, where we have this method
		* 2. argument name of the method to get
		* 3. argument what arguments does method accept and what it returns
		****************/
		jloadAd = ENV->GetStaticMethodID(cls, "loadAd", "(Ljava/lang/String;Ljava/lang/String;)V");
		if(!jloadAd) return 0;
	}
	
	//get arguments from lua
	const char *admobID = lua_tostring(L, 1);
	
	const char *adType;
	//check if there is a second argument
	if(lua_isstring(L, 2))
	{
		//get it if there is
		adType = lua_tostring(L, 2);
	}
	else
	{
		//or use default value
		adType = "banner";
	}
	
	//call java method with parameters
	ENV->CallStaticVoidMethod(cls, jloadAd, ENV->NewStringUTF(admobID), ENV->NewStringUTF(adType));
	
	return 1;
}

//remove ad
static int removeAd(lua_State *L)
{
	//if no Java Env, exit
	if(ENV == NULL) return 0;
	
	//if no class, try to retrieve it
	if(cls == NULL)
	{
		cls = ENV->FindClass(javaClassName);
		if(!cls) return 0;
	}
	
	//if we don't have method yet, try to retrieve it
	if(jRemoveAd == NULL)
	{
		/****************
		* 1. argument cls - reference to Java class, where we have this method
		* 2. argument name of the method to get
		* 3. argument what arguments does method accept and what it returns
		****************/
		jRemoveAd = ENV->GetStaticMethodID(cls, "removeAd", "()V");
		if(!jRemoveAd) return 0;
	}
	
	//call java method with parameters
	ENV->CallStaticVoidMethod(cls, jRemoveAd);
	
	return 1;
}

//set position of ad
static int setAlignment(lua_State *L)
{
	//if no Java Env, exit
	if(ENV == NULL) return 0;
	
	//if no class, try to retrieve it
	if(cls == NULL)
	{
		cls = ENV->FindClass(javaClassName);
		if(!cls) return 0;
	}
	
	//if we don't have method yet, try to retrieve it
	if(jSetAlignment == NULL)
	{
		/****************
		* 1. argument cls - reference to Java class, where we have this method
		* 2. argument name of the method to get
		* 3. argument what arguments does method accept and what it returns
		****************/
		jSetAlignment = ENV->GetStaticMethodID(cls, "setAlignment", "(Ljava/lang/String;Ljava/lang/String;)V");
		if(!jSetAlignment) return 0;
	}
	
	//get arguments from lua
	const char *horAlign;
	//check if there is a second argument
	if(lua_isstring(L, 1))
	{
		//get it if there is
		horAlign = lua_tostring(L, 1);
	}
	else
	{
		//or use default value
		horAlign = "center";
	}
	const char *verAlign;
	if(lua_isstring(L, 2))
	{
		//get it if there is
		verAlign = lua_tostring(L, 2);
	}
	else
	{
		//or use default value
		verAlign = "top";
	}
	
	//call java method with parameters
	ENV->CallStaticVoidMethod(cls, jSetAlignment, ENV->NewStringUTF(horAlign), ENV->NewStringUTF(verAlign));
	
	return 1;
}

//modify string method
static int setHorizontalAlignment(lua_State *L)
{
	//if no Java Env, exit
	if(ENV == NULL) return 0;
	
	//if no class, try to retrieve it
	if(cls == NULL)
	{
		cls = ENV->FindClass(javaClassName);
		if(!cls) return 0;
	}
	
	//if we don't have method yet, try to retrieve it
	if(jSetHorAl == NULL)
	{
		/****************
		* 1. argument cls - reference to Java class, where we have this method
		* 2. argument name of the method to get
		* 3. argument what arguments does method accept and what it returns
		****************/
		jSetHorAl = ENV->GetStaticMethodID(cls, "setHorizontalAlignment", "(Ljava/lang/String;)V");
		if(!jSetHorAl) return 0;
	}
	
	//get arguments from lua
	const char *horAlign = lua_tostring(L, 1);
	
	//call java method with parameters
	ENV->CallStaticVoidMethod(cls, jSetHorAl, ENV->NewStringUTF(horAlign));
	
	return 1;
}

//modify string method
static int setVerticalAlignment(lua_State *L)
{
	//if no Java Env, exit
	if(ENV == NULL) return 0;
	
	//if no class, try to retrieve it
	if(cls == NULL)
	{
		cls = ENV->FindClass(javaClassName);
		if(!cls) return 0;
	}
	
	//if we don't have method yet, try to retrieve it
	if(jSetVerAl == NULL)
	{
		/****************
		* 1. argument cls - reference to Java class, where we have this method
		* 2. argument name of the method to get
		* 3. argument what arguments does method accept and what it returns
		****************/
		jSetVerAl = ENV->GetStaticMethodID(cls, "setVerticalAlignment", "(Ljava/lang/String;)V");
		if(!jSetVerAl) return 0;
	}
	
	//get arguments from lua
	const char *verAlign = lua_tostring(L, 1);
	
	//call java method with parameters
	ENV->CallStaticVoidMethod(cls, jSetVerAl, ENV->NewStringUTF(verAlign));
	
	return 1;
}

//modify string method
static int setVisible(lua_State *L)
{
	//if no Java Env, exit
	if(ENV == NULL) return 0;
	
	//if no class, try to retrieve it
	if(cls == NULL)
	{
		cls = ENV->FindClass(javaClassName);
		if(!cls) return 0;
	}
	
	//if we don't have method yet, try to retrieve it
	if(jSetVisible == NULL)
	{
		/****************
		* 1. argument cls - reference to Java class, where we have this method
		* 2. argument name of the method to get
		* 3. argument what arguments does method accept and what it returns
		****************/
		jSetVisible = ENV->GetStaticMethodID(cls, "setVisible", "(Z)V");
		if(!jSetVisible) return 0;
	}
	
	//get arguments from lua
	bool visible = lua_toboolean(L, 1);
	
	//call java method with parameters
	ENV->CallStaticVoidMethod(cls, jSetVisible, visible);
	
	return 1;
}

//modify string method
static int getHorizontalAlignment(lua_State *L)
{
	//if no Java Env, exit
	if(ENV == NULL) return 0;
	
	//if no class, try to retrieve it
	if(cls == NULL)
	{
		cls = ENV->FindClass(javaClassName);
		if(!cls) return 0;
	}
	
	//if we don't have method yet, try to retrieve it
	if(jGetHorAl == NULL)
	{
		/****************
		* 1. argument cls - reference to Java class, where we have this method
		* 2. argument name of the method to get
		* 3. argument what arguments does method accept and what it returns
		****************/
		jGetHorAl = ENV->GetStaticMethodID(cls, "getHorizontalAlignment", "()Ljava/lang/String;");
		if(!jGetHorAl) return 0;
	}
	
	//call java method with parameters
	jstring align =	(jstring)ENV->CallStaticObjectMethod(cls, jGetHorAl);
	const char *horAlign = ENV->GetStringUTFChars(align , NULL ) ;
	
	//get arguments from lua
    lua_pushstring(L, horAlign);
	
	return 1;
}

//modify string method
static int getVerticalAlignment(lua_State *L)
{
	//if no Java Env, exit
	if(ENV == NULL) return 0;
	
	//if no class, try to retrieve it
	if(cls == NULL)
	{
		cls = ENV->FindClass(javaClassName);
		if(!cls) return 0;
	}
	
	//if we don't have method yet, try to retrieve it
	if(jGetVerAl == NULL)
	{
		/****************
		* 1. argument cls - reference to Java class, where we have this method
		* 2. argument name of the method to get
		* 3. argument what arguments does method accept and what it returns
		****************/
		jGetVerAl = ENV->GetStaticMethodID(cls, "getVerticalAlignment", "()Ljava/lang/String;");
		if(!jGetVerAl) return 0;
	}
	
	//call java method with parameters
	jstring align =	(jstring)ENV->CallStaticObjectMethod(cls, jGetVerAl);
	const char *verAlign = ENV->GetStringUTFChars(align , NULL );
	
	//get arguments from lua
    lua_pushstring(L, verAlign);
	
	return 1;
}

//modify string method
static int getAlignment(lua_State *L)
{
	//if no Java Env, exit
	if(ENV == NULL) return 0;
	
	//if no class, try to retrieve it
	if(cls == NULL)
	{
		cls = ENV->FindClass(javaClassName);
		if(!cls) return 0;
	}
	
	//if we don't have method yet, try to retrieve it
	if(jGetHorAl == NULL)
	{
		/****************
		* 1. argument cls - reference to Java class, where we have this method
		* 2. argument name of the method to get
		* 3. argument what arguments does method accept and what it returns
		****************/
		jGetHorAl = ENV->GetStaticMethodID(cls, "getHorizontalAlignment", "()Ljava/lang/String;");
		if(!jGetHorAl) return 0;
	}
	if(jGetVerAl == NULL)
	{
		/****************
		* 1. argument cls - reference to Java class, where we have this method
		* 2. argument name of the method to get
		* 3. argument what arguments does method accept and what it returns
		****************/
		jGetVerAl = ENV->GetStaticMethodID(cls, "getVerticalAlignment", "()Ljava/lang/String;");
		if(!jGetVerAl) return 0;
	}
	
	//call java method with parameters
	jstring align =	(jstring)ENV->CallStaticObjectMethod(cls, jGetHorAl);
	const char *horAlign = ENV->GetStringUTFChars(align , NULL );
	align =	(jstring)ENV->CallStaticObjectMethod(cls, jGetVerAl);
	const char *verAlign = ENV->GetStringUTFChars(align , NULL );
	
	//get arguments from lua
    lua_pushstring(L, horAlign);
    lua_pushstring(L, verAlign);
	
	return 2;
}


//here we register all functions we could call from lua
//lua function name as key and C function as value
static const struct luaL_Reg funcs[] = {
  { "loadAd",	loadAd },
  { "removeAd",	removeAd },
  { "setAlignment",	setAlignment },
  { "setHorizontalAlignment",	setHorizontalAlignment },
  { "setVerticalAlignment",	setVerticalAlignment },
  { "getHorizontalAlignment",	getHorizontalAlignment },
  { "getVerticalAlignment",	getVerticalAlignment },
  { "getAlignment",	getAlignment },
  { "setVisible",	setVisible },
  { NULL, NULL }//don't forget nulls at the end
};

//here we register all the C functions for lua
//so lua engine would know they exists
LUALIB_API int luaopen_plugin(lua_State *L)
{
  luaL_register(L, pluginName, funcs);
  return 1;
}

//here we do all our stuff needs to be done on initialization
static void g_initializePlugin(lua_State *L)
{
	//get java environment reference
	ENV = g_getJNIEnv();
	
	//get global package object
	lua_getglobal(L, "package");
	lua_getfield(L, -1, "preload");
	
	//put our plugin name inside with a callback to
	//registering C functions
	lua_pushcfunction(L, luaopen_plugin);
	lua_setfield(L, -2, pluginName);

	lua_pop(L, 2);
}

//and here we free everything we need to free
static void g_deinitializePlugin(lua_State *L)
{

}

//register our plugin with Gideros lib
REGISTER_PLUGIN(pluginName, pluginVersion)