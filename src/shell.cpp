#include"shell.h"
#include "elib/fnshare.cpp"
#include"Fun.h"
#include"myhelp.h"
#if (_MSC_VER > 1600)
#pragma region  ��ݷ�ʽ����
#endif
/*************************������ݷ�ʽ*******************************/
static ARG_INFO CreateLinkArg[] =
{
	{ _WT("��ݷ�ʽ�ļ���"), _WT("����ļ�����������׺,���Զ�����\".lnk\"��׺��."),0 , 0,  SDT_TEXT, NULL, NULL },
	{ _WT("ָ���ļ�·��"), _WT("�ṩ��ݷ�ʽ��ָ���ļ���ȫ·����"),0 , 0,  SDT_TEXT, NULL, AS_DEFAULT_VALUE_IS_EMPTY },
	{ _WT("��ע��Ϣ"), _WT("�ṩ��Ӧ�˿�ݷ�ʽ�������ı���Ϣ"),0 , 0,  SDT_TEXT, NULL, AS_DEFAULT_VALUE_IS_EMPTY },
	{ _WT("�������ı�"), _WT("�ṩ������ݷ�ʽָ���ļ�ʱ���ӵ��������ı�"),0 , 0,  SDT_TEXT, NULL, AS_DEFAULT_VALUE_IS_EMPTY },
	{ _WT("����Ŀ¼"), _WT("�ṩ������ݷ�ʽָ���ļ�ʱ����Ԥ�õĹ���Ŀ¼"),0 , 0,  SDT_TEXT, NULL, AS_DEFAULT_VALUE_IS_EMPTY },
	{ _WT("�ȼ�"), _WT("�ȼ���ֵ���������΢��ӿ�"),0 , 0,  SDT_INT, NULL, AS_DEFAULT_VALUE_IS_EMPTY },
};
EXTERN_C void shell_fnCreateLink(PMDATA_INF pRetData, INT iArgCount, PMDATA_INF pArgInf)
{

	string Name, path, remark, commline, dir;
	DWORD hotKey=0;
	if (pArgInf[0].m_dtDataType && pArgInf[0].m_pText)
	{
		Name = pArgInf[0].m_pText;
	}
	if (pArgInf[1].m_dtDataType && pArgInf[1].m_pText)
	{
		path = pArgInf[1].m_pText;
	}
	if (pArgInf[2].m_dtDataType && pArgInf[2].m_pText)
	{
		remark = pArgInf[2].m_pText;
	}
	if (pArgInf[3].m_dtDataType && pArgInf[3].m_pText)
	{
		commline = pArgInf[3].m_pText;
	}
	if (pArgInf[4].m_dtDataType && pArgInf[4].m_pText)
	{
		dir = pArgInf[4].m_pText;
	}
	if (pArgInf[5].m_dtDataType)
	{
		hotKey = pArgInf[5].m_int;
	}
	pRetData->m_bool = CreateLink(Name, path, remark, hotKey,commline, dir);
}

/*************************��ѯ��ݷ�ʽ****************************/
static ARG_INFO GetShortCutArg[] =
{
	{ _WT("��ݷ�ʽ�ļ���"), _WT(""),0 , 0, SDT_TEXT, NULL,NULL },
};
EXTERN_C void shell_fnGetShortCut(PMDATA_INF pRetData, INT iArgCount, PMDATA_INF pArgInf)
{
	wstring Name, Path;
	GetShortCutTarget(Name, Path);
	pRetData->m_pText = W2Estr(Path);
}
/*************************����ļ���****************************/
static ARG_INFO BrowseForFolderArg[] =
{
	{ _WT("����"), _WT("�������ṩ��ʾ�ڶԻ����ϲ��ı����ı�"),0 , 0, SDT_TEXT, NULL,NULL },
	{ _WT("�Ƿ�����ļ�"), _WT("������ָ���Ƿ����������ͬʱ�г��ļ����������ʡ�ԣ�Ĭ��ֵΪ��"),0 , 0, SDT_BOOL, NULL,AS_DEFAULT_VALUE_IS_EMPTY },
	{ _WT("���ھ��"), _WT("Ĭ��Ϊ��ǰ���̻�����Ҳ���ǽ������ھ��"),0 , 0, SDT_TEXT, NULL,AS_DEFAULT_VALUE_IS_EMPTY },
};
EXTERN_C void shell_fnBrowseForFolder(PMDATA_INF pRetData, INT iArgCount, PMDATA_INF pArgInf)
{
	bool IsDisplayFile = false; HWND hWndP = NULL;
	if (pArgInf[1].m_dtDataType && pArgInf[1].m_bool)
	{
		IsDisplayFile = TRUE;
	}
	if (pArgInf[2].m_dtDataType && pArgInf[2].m_int)
	{
		hWndP = (HWND)pArgInf[2].m_int;
	}
	pRetData->m_pText = BrowseForFolder(pArgInf[0].m_pText, IsDisplayFile, hWndP);
}
/*************************ɾ��������վ****************************/
static ARG_INFO DeleteIntoRecycleBinArg[] =
{
	{ _WT("ɾ��ѡ��"), _WT("�������ṩɾ������ѡ�����Ϊ���³���ֵ֮һ��֮�ͣ� 1: #��ѯ��ɾ��; 2: #����ʾ����; 4: #����ʾ���ȡ������ʡ�ԣ�Ĭ��ֵΪ 0 "),0 , 0, SDT_INT, NULL,AS_DEFAULT_VALUE_IS_EMPTY },
	{ _WT("��ɾ���ļ�"), _WT("�������ṩ��ʾ�ڶԻ����ϲ��ı����ı�"),0 , 0, SDT_TEXT, NULL,NULL },
};
EXTERN_C void shell_fnDeleteIntoRecycleBin(PMDATA_INF pRetData, INT iArgCount, PMDATA_INF pArgInf)
{
	INT Selected = 0;
	if (pArgInf[0].m_dtDataType && pArgInf[0].m_int>0 && pArgInf[0].m_int <= 0)
	{
		Selected =pArgInf[0].m_int;
	}
	pRetData->m_bool = DeleteIntoRecycleBin(Selected,pArgInf[1].m_pText);
}
/*************************���ȸ����ļ�****************************/
static ARG_INFO ShellCopyFileArg[] =
{
	{ _WT("Ŀ��Ŀ¼"), _WT("�������ṩĿ��Ŀ¼·���������Ŀ¼�����ڣ�ϵͳ���Զ�ѯ���Ƿ񴴽�"),0 , 0, SDT_TEXT, NULL,NULL },
	{ _WT("Դ�ļ�"), _WT("���������鷽ʽͬʱ�ṩ����ļ����ļ�������ע�������ȫ·����֧��ͨ�����*���͡�?��"),0 , 0, SDT_TEXT, NULL,NULL },
};
EXTERN_C void shell_fnShellCopyFile(PMDATA_INF pRetData, INT iArgCount, PMDATA_INF pArgInf)
{
	pRetData->m_bool = ShellCopyFile(pArgInf[0].m_pText, pArgInf[1].m_pText);
}
/*************************�����ƶ��ļ�****************************/
EXTERN_C void shell_fnShellMoveFile(PMDATA_INF pRetData, INT iArgCount, PMDATA_INF pArgInf)
{
	pRetData->m_bool = ShellMoveFile(pArgInf[0].m_pText, pArgInf[1].m_pText);
}
/*************************ִ��****************************/
static ARG_INFO ShellExecuteArg[] =
{	{ _WT("��������"), _WT("�������ṩ��ִ����������ͣ�����Ϊ���³���ֵ֮һ�� �� 1: #�༭�ĵ�; �����༭����򿪡��������ļ�����������ָ�����ĵ��ļ����б༭�� �� 2: #����ļ���; �򿪡��������ļ�����������ָ�����ļ��н�������� �� 3: #Ѱ���ļ�; �򿪡��������ļ�����������ָ�����ļ��н����ļ�Ѱ�Ҳ����� �� 4: #���ļ�; �򿪡��������ļ�����������ָ�����ļ������ļ������ǿ�ִ���ļ����ĵ��ļ����ļ��С� �� 5: #��ӡ�ĵ�; ��ӡ���������ļ�����������ָ�����ĵ��ļ���ע����ĵ��ı༭������ܲ�֧�ֱ������ʹ��ǰ��Ҫ�Ȳ����Ƿ���á� �� �����������ʡ�Ի���Ϊ0��ϵͳ��������Ѱע����Ի�ȡ��Ӧ���������ļ���һ�������������ͣ����δ�ҵ�����ʹ�á�#���ļ�������"),0 , 0, SDT_INT, NULL,AS_DEFAULT_VALUE_IS_EMPTY },
	{ _WT("�������ļ���"), _WT("�������ṩ�������ļ����ļ��е�����"),0 , 0, SDT_TEXT, NULL,NULL },
	{ _WT("������"), _WT("��������в���������Ϊ�����ļ����ұ����ļ�Ϊ��ִ���ļ����������ṩ�����ÿ�ִ���ļ�ʱ�����ӵ��������ı�����������±������������ԡ������������ʡ�ԣ�Ĭ��Ϊ���ı�"),0 , 0, SDT_TEXT, NULL,AS_DEFAULT_VALUE_IS_EMPTY },
	{ _WT("Ĭ�ϵ�ǰĿ¼"), _WT("�������ṩ����ִ��ʱ��Ĭ�ϵ�ǰĿ¼�������ʡ�ԣ�Ĭ��Ϊ���ı�"),0 , 0, SDT_TEXT, NULL,AS_DEFAULT_VALUE_IS_EMPTY },
	{ _WT("������ʾ��ʽ"), _WT("����ֵ����Ϊ���³���֮һ��1��#���ش��ڣ� 2��#��ͨ��� 3��#��С����� 4��#��󻯼�� 5��#��ͨ����� 6��#��С����������ʡ�Ա�������Ĭ��Ϊ����ͨ�����ʽ������������������ļ��������ǿ�ִ���ļ���������ʾ��ʽ��ת��������������Ŀ�ִ�г����������Ƿ�����ȷ�������ʾ��ʽ��ȡ���ڸó�������"),0 , 0, SDT_INT, NULL,AS_DEFAULT_VALUE_IS_EMPTY },

};
EXTERN_C void shell_fnShellExecute(PMDATA_INF pRetData, INT iArgCount, PMDATA_INF pArgInf)
{
	pRetData->m_bool = (INT_PTR)MyShellExecute(pArgInf[0].m_int, pArgInf[1].m_pText, pArgInf[2].m_pText, pArgInf[3].m_pText, pArgInf[4].m_int) > 32;
}

/*************************ȡ�ض�Ŀ¼****************************/
static ARG_INFO GetSpecialFolderPathArg[] =
{
	{ _WT("����ȡĿ¼����"), _WT("������ָ������ȡĿ¼�����ͣ�����Ϊ���³���ֵ֮һ�� 1: #�ҵ��ĵ�; 2: #�ҵ��ղؼ�; 3: #ϵͳ����; 4: #ϵͳ����; 5: #��ʼ�˵���; 6: #����˵���; 7: #�����˵���; 8: #��������Ŀ¼; 9: #Windows��װĿ¼; 10: #WindowsϵͳĿ¼; 11: #��ʱ�ļ�Ŀ¼"),0 , 0, SDT_INT, NULL,NULL },
};
EXTERN_C void shell_fnGetSpecialFolderPath(PMDATA_INF pRetData, INT iArgCount, PMDATA_INF pArgInf)
{
	pRetData->m_pText = GetSpecialFolderPath(pArgInf[0].m_int);
}
/*************************�ر�ϵͳ****************************/
static ARG_INFO ExitWindowsArg[] =
{
	{ _WT("�رշ�ʽ"), _WT("����������Ϊ���³���ֵ֮һ�� 1: #�ػ�; 2: #����; 3: #ע��; 4: #���� 5: #���ߡ� ע����Windows95/98/ME�¶��ߵ�ͬ������"),0 , 0, SDT_INT, NULL,NULL },
	{ _WT("�Ƿ�ǿ��ִ��"), _WT("������ָ���Ƿ񲻵ȴ���ǰ�������е����������������������ִ��ָ���Ĳ����������������ʡ�ԣ�Ĭ��ֵΪ��"),0 , 0, SDT_BOOL, NULL,AS_DEFAULT_VALUE_IS_EMPTY },
};
EXTERN_C void shell_fnExitWindows(PMDATA_INF pRetData, INT iArgCount, PMDATA_INF pArgInf)
{
	bool Enforce = FALSE;
	if (pArgInf[1].m_dtDataType && pArgInf[1].m_bool == TRUE)
	{
		Enforce = TRUE;
	}
	pRetData->m_bool = MyExitWindows(pArgInf[0].m_int, Enforce);
}
#if (_MSC_VER > 1600)
#pragma endregion
#endif

//����ָ�����
static PFN_EXECUTE_CMD s_ExecuteCommand[] = {
shell_fnCreateLink ,
shell_fnGetShortCut ,
shell_fnBrowseForFolder,
shell_fnDeleteIntoRecycleBin ,
shell_fnShellCopyFile,
shell_fnShellMoveFile,
shell_fnShellExecute,
shell_fnGetSpecialFolderPath,
shell_fnExitWindows
};
static const char* const CommandNames[] = {
	"shell_fnCreateLink",
	"shell_fnGetShortCut",
	"shell_fnBrowseForFolder",
	"shell_fnDeleteIntoRecycleBin" ,
	"shell_fnShellCopyFile",
	"shell_fnShellMoveFile",
	"shell_fnShellExecute",
	"shell_fnGetSpecialFolderPath",
	"shell_fnExitWindows"
};
//��������
static CMD_INFO s_Commands[] = { 
	{ _WT("������ݷ�ʽ"), _WT("CreateLink"), _WT("����ָ���Ŀ�ݷ�ʽ�ļ�,�����Ƿ�ɹ�."),1 , 0,SDT_BOOL , 0, LVL_SIMPLE,0 ,0 ,6, CreateLinkArg },
	{ _WT("��ѯ��ݷ�ʽ"), _WT("GetShortCut"), _WT("����ļ�����������׺�����Զ����ϡ�.lnk����׺��"),1 , NULL, SDT_TEXT , 0, LVL_SIMPLE,0 ,0 ,sizeof(GetShortCutArg) / sizeof(GetShortCutArg[0]), GetShortCutArg},
	{ _WT("����ļ���"), _WT("BrowseForFolder"), _WT("��һ���Ի������ϵͳ�д��ڵ������ļ��У����ر�ѡ���ļ��е�·���������δѡ���κ��ļ��У��򷵻ؿ��ı���"),2 , NULL, SDT_TEXT , 0, LVL_SIMPLE,0 ,0 ,sizeof(BrowseForFolderArg) / sizeof(BrowseForFolderArg[0]), BrowseForFolderArg},
	{ _WT("ɾ��������վ"), _WT("DeleteIntoRecycleBin"), _WT("��������Խ�һ����һ���ļ�ɾ����Windowsϵͳ����վ�У��ɹ������棬ʧ�ܻ��û���ֹɾ���������ؼ١�"),2 , NULL, SDT_BOOL , 0, LVL_SIMPLE,0 ,0 ,sizeof(DeleteIntoRecycleBinArg) / sizeof(DeleteIntoRecycleBinArg[0]),DeleteIntoRecycleBinArg},
	{ _WT("���ȸ����ļ�"), _WT("ShellCopyFile"), _WT("��������Խ�һ����һ���ļ����Ƶ���һ��Ŀ¼�У���ͬʱ��ʾһ�����ƽ��ȶԻ��򣬳ɹ������棬ʧ�ܻ��û���ֹ���Ʋ������ؼ١�"),2 , NULL, SDT_BOOL , 0, LVL_SIMPLE,0 ,0 ,sizeof(ShellCopyFileArg) / sizeof(ShellCopyFileArg[0]),ShellCopyFileArg},
	{ _WT("�����ƶ��ļ�"), _WT("ShellMoveFile"), _WT("��������Խ�һ����һ���ļ��ƶ�����һ��Ŀ¼�У���ͬʱ��ʾһ���ƶ����ȶԻ��򣬳ɹ������棬ʧ�ܻ��û���ֹ�ƶ��������ؼ١�"),2 , NULL, SDT_BOOL , 0, LVL_SIMPLE,0 ,0 ,sizeof(ShellCopyFileArg) / sizeof(ShellCopyFileArg[0]),ShellCopyFileArg},
	{ _WT("ִ��"), _WT("ShellExecute"), _WT("ʹ��Windows���û�����ϵͳִ��ָ�����"),3 , NULL, SDT_BOOL , 0, LVL_SIMPLE,0 ,0 ,sizeof(ShellExecuteArg) / sizeof(ShellExecuteArg[0]),ShellExecuteArg},
	{ _WT("ȡ�ض�Ŀ¼"), _WT("GetSpecialFolderPath"), _WT("�������ָ����Windowsϵͳ�ض�Ŀ¼��������Ŀ¼���ԡ�\\�����Ž�������ʧ�ܷ��ؿ��ı���"),3 , NULL, SDT_TEXT , 0, LVL_SIMPLE,0 ,0 ,sizeof(GetSpecialFolderPathArg) / sizeof(GetSpecialFolderPathArg[0]),GetSpecialFolderPathArg},
	{ _WT("�ر�ϵͳ"), _WT("ExitWindows"), _WT("���������ִ�йػ���������ע����Windowsϵͳ�������ɹ������棬ʧ�ܷ��ؼ١�"),3 , NULL, SDT_BOOL , 0, LVL_SIMPLE,0 ,0 ,sizeof(ExitWindowsArg) / sizeof(ExitWindowsArg[0]),ExitWindowsArg},

};

static LIB_CONST_INFO s_ConstInfo[] =
{		 /* { ��������, Ӣ������, ��������, �����ȼ�(LVL_), ��������(CT_), �ı�����, ��ֵ���� } */
	{_T("�༭�ĵ�"), NULL, NULL,  1,  CT_NUM,NULL,1},
	{_T("����ļ���"), NULL, NULL,  1,  CT_NUM,NULL,2},
	{_T("Ѱ���ļ�"), NULL, NULL,  1,  CT_NUM,NULL,3},
	{_T("���ļ�"), NULL, NULL,  1,  CT_NUM,NULL,4},
	{_T("��ӡ�ĵ�"), NULL, NULL,  1,  CT_NUM,NULL,5},
	{_T("�ҵ��ĵ�"), NULL, NULL,  1,  CT_NUM,NULL,1},
	{_T("�ҵ��ղؼ�"), NULL, NULL,  1,  CT_NUM,NULL,2},
	{_T("ϵͳ����"), NULL, NULL,  1,  CT_NUM,NULL,3},
	{_T("ϵͳ����"), NULL, NULL,  1,  CT_NUM,NULL,4},
	{_T("��ʼ�˵���"), NULL, NULL,  1,  CT_NUM,NULL,5},
	{_T("����˵���"), NULL, NULL,  1,  CT_NUM,NULL,6},
	{_T("�����˵���"), NULL, NULL,  1,  CT_NUM,NULL,7},
	{_T("��������Ŀ¼"), NULL, NULL,  1,  CT_NUM,NULL,8},
	{_T("Windows��װĿ¼"), NULL, NULL,  1,  CT_NUM,NULL,9},
	{_T("WindowsϵͳĿ¼"), NULL, NULL,  1,  CT_NUM,NULL,10},
	{_T("��ʱ�ļ�Ŀ¼"), NULL, NULL,  1,  CT_NUM,NULL,11},
	{_T("��ѯ��ɾ��"), NULL, NULL,  1,  CT_NUM,NULL,1},
	{_T("����ʾ����"), NULL, NULL,  1,  CT_NUM,NULL,2},
	{_T("����ʾ����"), NULL, NULL,  1,  CT_NUM,NULL,4},
	{_T("�ػ�"), NULL, NULL,  1,  CT_NUM,NULL,1},
	{_T("����"), NULL, NULL,  1,  CT_NUM,NULL,2},
	{_T("ע��"), NULL, NULL,  1,  CT_NUM,NULL,3},
	{_T("����"), NULL, NULL,  1,  CT_NUM,NULL,4},
	{_T("����"), NULL, NULL,  1,  CT_NUM,NULL,5},
};





#ifndef __E_STATIC_LIB
static LIB_INFO LibInfo =
{

	/* { ���ʽ��, GUID����, ���汾��, �ΰ汾��, �����汾��, ϵͳ���汾��, ϵͳ�ΰ汾��, ���Ŀ����汾��, ���Ŀ�ΰ汾��,

	֧�ֿ���, ֧�ֿ�����, ֧�ֿ�����, ֧�ֿ�״̬,

	��������, ��������, ͨ�ŵ�ַ, �绰����, �������, ��������, ��ҳ��ַ, ������Ϣ,

	��������, ����ָ��, �������, �������, ��������, ����ָ��, �������,

	���ӹ���, ��������, ��Ϣָ��, ����ģ��, ģ������,

	��������, ����ָ��, �ⲿ�ļ�} */
	LIB_FORMAT_VER,//���ʽ��
	_T(LIB_GUID_STR),//GUID����
	LIB_MajorVersion,//���汾��
	LIB_MinorVersion,//�ΰ汾��
	LIB_BuildNumber,//�����汾��
	LIB_SysMajorVer,//ϵͳ���汾��
	LIB_SysMinorVer,//ϵͳ�ΰ汾��
	LIB_KrnlLibMajorVer,//���Ŀ����汾��
	LIB_KrnlLibMinorVer,//���Ŀ�ΰ汾��
	_T(LIB_NAME_STR),//֧�ֿ���
	__GBK_LANG_VER,//֧�ֿ�����
	_WT(LIB_DESCRIPTION_STR),//֧�ֿ�����
	_LIB_OS(__OS_WIN),//֧�ֿ�״̬
	_WT(LIB_Author),//��������
	_WT(LIB_ZipCode),// ��������
	_WT(LIB_Address),//ͨ�ŵ�ַ
	_WT(LIB_Phone),//�绰����
	_WT(LIB_Fax),//�������
	_WT(LIB_Email),//��������
	_WT(LIB_HomePage),//��ҳ��ַ
	_WT(LIB_Other),//������Ϣ
	0,//��������
	0,//����ָ��
	LIB_TYPE_COUNT,//�������
	_WT(LIB_TYPE_STR),//�������
   sizeof(s_Commands) / sizeof(s_Commands[0]),//��������
	s_Commands,//����ָ��
	s_ExecuteCommand,//�������
	NULL,//���ӹ���
	NULL,//��������
	shell_ProcessNotifyLib,//��Ϣָ��
	NULL,//����ģ��
	NULL,//ģ������
	sizeof(s_ConstInfo)/ sizeof(s_ConstInfo[0]),//��������
	s_ConstInfo,//����ָ��
	NULL//�ⲿ�ļ�
};





extern "C" PLIB_INFO  GetNewInf()

{

	return (&LibInfo);

};
#endif
EXTERN_C INT WINAPI shell_ProcessNotifyLib(INT nMsg, DWORD dwParam1, DWORD dwParam2)
{

#ifndef __E_STATIC_LIB

	if (nMsg == NL_GET_CMD_FUNC_NAMES) // ������������ʵ�ֺ����ĵĺ�����������(char*[]), ֧�־�̬����Ķ�̬����봦��

		return (INT)CommandNames;

	else if (nMsg == NL_GET_NOTIFY_LIB_FUNC_NAME) // ���ش���ϵͳ֪ͨ�ĺ�������(PFN_NOTIFY_LIB��������), ֧�־�̬����Ķ�̬����봦��

		return (INT)LIBARAYNAME;

	else if (nMsg == NL_GET_DEPENDENT_LIBS) return (INT)NULL;

	// ���ؾ�̬����������������̬���ļ����б�(��ʽΪ\0�ָ����ı�,��β����\0), ֧�־�̬����Ķ�̬����봦��

	// kernel32.lib user32.lib gdi32.lib �ȳ��õ�ϵͳ�ⲻ��Ҫ���ڴ��б���

	// ����NULL��NR_ERR��ʾ��ָ�������ļ�

#endif

	return ProcessNotifyLib(nMsg, dwParam1, dwParam2);

}