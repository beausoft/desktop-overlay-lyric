#pragma once
#include "targetver.h"

//#define WIN32_LEAN_AND_MEAN             //  从 Windows 头文件中排除极少使用的信息
// Windows 头文件:
#include <windows.h>

// C 运行时头文件
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>

//GDI库
#include <GdiPlus.h>
#pragma comment(lib,"GdiPlus.lib")
using namespace Gdiplus;
using namespace DllExports;

//string字符串
#include <string>
using  std::string;
using  std::wstring;

//能够使用Visual C＋＋中的一些特殊COM支持类。有了这个头文件，gdiplus.h里面有东西就可以用了。
//#include <comdef.h>