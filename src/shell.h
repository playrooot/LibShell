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
#define LIB_MajorVersion 3 /*�����汾��*/ 
#define LIB_MinorVersion 2 /*��ΰ汾��*/
#define LIB_BuildNumber 0 /*�����汾��*/
#define LIB_SysMajorVer 3 /*ϵͳ���汾��*/
#define LIB_SysMinorVer 0 /*ϵͳ�ΰ汾��*/
#define LIB_KrnlLibMajorVer 3 /*���Ŀ����汾��*/
#define LIB_KrnlLibMinorVer 0 /*���Ŀ�ΰ汾��*/
#define LIB_NAME_STR "����ϵͳ���湦��֧�ֿ�" /*֧�ֿ���*/
#define LIB_DESCRIPTION_STR "\r\n��֧�ֿ��װ�˳��õ�Windows API���ܡ�\r\n"
#define LIB_Author "����" /*��������*/
#define LIB_ZipCode "    " /*��������*/
#define LIB_Address "    " /*ͨ�ŵ�ַ*/
#define LIB_Phone    "   " /*�绰����*/
#define LIB_Fax        " 80805777 " /*QQ����*/
#define LIB_Email     "   " /*��������*/
#define LIB_HomePage "   " /*��ҳ��ַ*/
#define LIB_Other    "   " /*������Ϣ*/
#define LIB_TYPE_COUNT 3 /*�����������*/
#define LIB_TYPE_STR "0000��ݷ�ʽ����\0" "0000�ļ�����\0""0000����\0""\0" /*�������*/
#endif
#endif


