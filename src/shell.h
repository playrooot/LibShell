#pragma once
#ifndef __ELIBFNE__
#define __ELIBFNE__
#include <windows.h>
#include <tchar.h>
#include <cassert>   
#include"elib/lib2.h" 
#include "elib/lang.h"
#include "elib/fnshare.h"

#define LIBARAYNAME "shell_ProcessNotifyLib"

extern "C" __declspec(dllexport) PLIB_INFO  GetNewInf();

EXTERN_C INT WINAPI shell_ProcessNotifyLib(INT nMsg, DWORD dwParam1, DWORD dwParam2);

#ifndef __E_STATIC_LIB
#define LIB_GUID_STR "52F260023059454187AF826A3C07AF2A" 
#define LIB_MajorVersion 3 /*库主版本号*/ 
#define LIB_MinorVersion 2 /*库次版本号*/
#define LIB_BuildNumber 0 /*构建版本号*/
#define LIB_SysMajorVer 3 /*系统主版本号*/
#define LIB_SysMinorVer 0 /*系统次版本号*/
#define LIB_KrnlLibMajorVer 3 /*核心库主版本号*/
#define LIB_KrnlLibMinorVer 0 /*核心库次版本号*/
#define LIB_NAME_STR "操作系统界面功能支持库" /*支持库名*/
#define LIB_DESCRIPTION_STR "\r\n本支持库封装了常用的Windows API功能。\r\n"
#define LIB_Author "阿龙" /*作者名称*/
#define LIB_ZipCode "    " /*邮政编码*/
#define LIB_Address "    " /*通信地址*/
#define LIB_Phone    "   " /*电话号码*/
#define LIB_Fax        " 80805777 " /*QQ号码*/
#define LIB_Email     "   " /*电子邮箱*/
#define LIB_HomePage "   " /*主页地址*/
#define LIB_Other    "   " /*其它信息*/
#define LIB_TYPE_COUNT 3 /*命令分类数量*/
#define LIB_TYPE_STR "0000快捷方式操作\0" "0000文件操作\0""0000杂类\0""\0" /*命令分类*/
#endif
#endif


