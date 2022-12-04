#include"shell.h"
#include "elib/fnshare.cpp"
#include"Fun.h"
#include"myhelp.h"
#if (_MSC_VER > 1600)
#pragma region  快捷方式操作
#endif
/*************************创建快捷方式*******************************/
static ARG_INFO CreateLinkArg[] =
{
	{ _WT("快捷方式文件名"), _WT("如果文件名不包含后缀,将自动加上\".lnk\"后缀名."),0 , 0,  SDT_TEXT, NULL, NULL },
	{ _WT("指向文件路径"), _WT("提供快捷方式所指向文件的全路径名"),0 , 0,  SDT_TEXT, NULL, AS_DEFAULT_VALUE_IS_EMPTY },
	{ _WT("备注信息"), _WT("提供对应此快捷方式的描述文本信息"),0 , 0,  SDT_TEXT, NULL, AS_DEFAULT_VALUE_IS_EMPTY },
	{ _WT("命令行文本"), _WT("提供启动快捷方式指向文件时附加的命令行文本"),0 , 0,  SDT_TEXT, NULL, AS_DEFAULT_VALUE_IS_EMPTY },
	{ _WT("工作目录"), _WT("提供启动快捷方式指向文件时所需预置的工作目录"),0 , 0,  SDT_TEXT, NULL, AS_DEFAULT_VALUE_IS_EMPTY },
	{ _WT("热键"), _WT("热键键值，具体参照微软接口"),0 , 0,  SDT_INT, NULL, AS_DEFAULT_VALUE_IS_EMPTY },
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

/*************************查询快捷方式****************************/
static ARG_INFO GetShortCutArg[] =
{
	{ _WT("快捷方式文件名"), _WT(""),0 , 0, SDT_TEXT, NULL,NULL },
};
EXTERN_C void shell_fnGetShortCut(PMDATA_INF pRetData, INT iArgCount, PMDATA_INF pArgInf)
{
	wstring Name, Path;
	GetShortCutTarget(Name, Path);
	pRetData->m_pText = W2Estr(Path);
}
/*************************浏览文件夹****************************/
static ARG_INFO BrowseForFolderArg[] =
{
	{ _WT("标题"), _WT("本参数提供显示在对话框上部的标题文本"),0 , 0, SDT_TEXT, NULL,NULL },
	{ _WT("是否包含文件"), _WT("本参数指定是否在浏览框中同时列出文件名。如果被省略，默认值为假"),0 , 0, SDT_BOOL, NULL,AS_DEFAULT_VALUE_IS_EMPTY },
	{ _WT("窗口句柄"), _WT("默认为当前进程活动句柄，也就是焦点所在句柄"),0 , 0, SDT_TEXT, NULL,AS_DEFAULT_VALUE_IS_EMPTY },
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
/*************************删除到回收站****************************/
static ARG_INFO DeleteIntoRecycleBinArg[] =
{
	{ _WT("删除选项"), _WT("本参数提供删除操作选项，可以为以下常量值之一或之和： 1: #不询问删除; 2: #不提示错误; 4: #不显示进度。如果被省略，默认值为 0 "),0 , 0, SDT_INT, NULL,AS_DEFAULT_VALUE_IS_EMPTY },
	{ _WT("欲删除文件"), _WT("本参数提供显示在对话框上部的标题文本"),0 , 0, SDT_TEXT, NULL,NULL },
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
/*************************进度复制文件****************************/
static ARG_INFO ShellCopyFileArg[] =
{
	{ _WT("目的目录"), _WT("本参数提供目的目录路径，如果该目录不存在，系统将自动询问是否创建"),0 , 0, SDT_TEXT, NULL,NULL },
	{ _WT("源文件"), _WT("可以以数组方式同时提供多个文件或文件夹名，注意必须是全路径，支持通配符“*”和“?”"),0 , 0, SDT_TEXT, NULL,NULL },
};
EXTERN_C void shell_fnShellCopyFile(PMDATA_INF pRetData, INT iArgCount, PMDATA_INF pArgInf)
{
	pRetData->m_bool = ShellCopyFile(pArgInf[0].m_pText, pArgInf[1].m_pText);
}
/*************************进度移动文件****************************/
EXTERN_C void shell_fnShellMoveFile(PMDATA_INF pRetData, INT iArgCount, PMDATA_INF pArgInf)
{
	pRetData->m_bool = ShellMoveFile(pArgInf[0].m_pText, pArgInf[1].m_pText);
}
/*************************执行****************************/
static ARG_INFO ShellExecuteArg[] =
{	{ _WT("命令类型"), _WT("本参数提供欲执行命令的类型，可以为以下常量值之一： ， 1: #编辑文档; 启动编辑软件打开“欲操作文件名”参数所指定的文档文件进行编辑。 ， 2: #浏览文件夹; 打开“欲操作文件名”参数所指定的文件夹进行浏览。 ， 3: #寻找文件; 打开“欲操作文件名”参数所指定的文件夹进行文件寻找操作。 ， 4: #打开文件; 打开“欲操作文件名”参数所指定的文件，该文件可以是可执行文件、文档文件或文件夹。 ， 5: #打印文档; 打印“欲操作文件名”参数所指定的文档文件，注意该文档的编辑软件可能不支持本命令，故使用前需要先测试是否可用。 ， 如果本参数被省略或者为0，系统将首先搜寻注册表以获取对应于欲操作文件的一个合适命令类型，如果未找到，将使用“#打开文件”命令"),0 , 0, SDT_INT, NULL,AS_DEFAULT_VALUE_IS_EMPTY },
	{ _WT("欲操作文件名"), _WT("本参数提供欲操作文件或文件夹的名称"),0 , 0, SDT_TEXT, NULL,NULL },
	{ _WT("命令行"), _WT("如果欲进行操作的类型为“打开文件”且被打开文件为可执行文件，本参数提供启动该可执行文件时欲附加的命令行文本，其它情况下本参数将被忽略。如果本参数被省略，默认为空文本"),0 , 0, SDT_TEXT, NULL,AS_DEFAULT_VALUE_IS_EMPTY },
	{ _WT("默认当前目录"), _WT("本参数提供命令执行时的默认当前目录，如果被省略，默认为空文本"),0 , 0, SDT_TEXT, NULL,AS_DEFAULT_VALUE_IS_EMPTY },
	{ _WT("窗口显示方式"), _WT("参数值可以为以下常量之一：1、#隐藏窗口； 2、#普通激活； 3、#最小化激活； 4、#最大化激活； 5、#普通不激活； 6、#最小化不激活。如果省略本参数，默认为“普通激活”方式。如果参数“欲操作文件名”不是可执行文件，窗口显示方式将转交给与其相关联的可执行程序处理，至于是否能正确处理此显示方式，取决于该程序自身。"),0 , 0, SDT_INT, NULL,AS_DEFAULT_VALUE_IS_EMPTY },

};
EXTERN_C void shell_fnShellExecute(PMDATA_INF pRetData, INT iArgCount, PMDATA_INF pArgInf)
{
	pRetData->m_bool = (INT_PTR)MyShellExecute(pArgInf[0].m_int, pArgInf[1].m_pText, pArgInf[2].m_pText, pArgInf[3].m_pText, pArgInf[4].m_int) > 32;
}

/*************************取特定目录****************************/
static ARG_INFO GetSpecialFolderPathArg[] =
{
	{ _WT("欲获取目录类型"), _WT("本参数指定欲获取目录的类型，可以为以下常量值之一： 1: #我的文档; 2: #我的收藏夹; 3: #系统桌面; 4: #系统字体; 5: #开始菜单组; 6: #程序菜单组; 7: #启动菜单组; 8: #程序数据目录; 9: #Windows安装目录; 10: #Windows系统目录; 11: #临时文件目录"),0 , 0, SDT_INT, NULL,NULL },
};
EXTERN_C void shell_fnGetSpecialFolderPath(PMDATA_INF pRetData, INT iArgCount, PMDATA_INF pArgInf)
{
	pRetData->m_pText = GetSpecialFolderPath(pArgInf[0].m_int);
}
/*************************关闭系统****************************/
static ARG_INFO ExitWindowsArg[] =
{
	{ _WT("关闭方式"), _WT("本参数可以为以下常量值之一： 1: #关机; 2: #重启; 3: #注销; 4: #休眠 5: #冬眠。 注意在Windows95/98/ME下冬眠等同于休眠"),0 , 0, SDT_INT, NULL,NULL },
	{ _WT("是否强制执行"), _WT("本参数指定是否不等待当前正在运行的所有软件正常结束而立即执行指定的操作。如果本参数被省略，默认值为假"),0 , 0, SDT_BOOL, NULL,AS_DEFAULT_VALUE_IS_EMPTY },
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

//命令指针入口
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
//命令定义入口
static CMD_INFO s_Commands[] = { 
	{ _WT("创建快捷方式"), _WT("CreateLink"), _WT("建立指定的快捷方式文件,返回是否成功."),1 , 0,SDT_BOOL , 0, LVL_SIMPLE,0 ,0 ,6, CreateLinkArg },
	{ _WT("查询快捷方式"), _WT("GetShortCut"), _WT("如果文件名不包含后缀，将自动加上“.lnk”后缀名"),1 , NULL, SDT_TEXT , 0, LVL_SIMPLE,0 ,0 ,sizeof(GetShortCutArg) / sizeof(GetShortCutArg[0]), GetShortCutArg},
	{ _WT("浏览文件夹"), _WT("BrowseForFolder"), _WT("打开一个对话框，浏览系统中存在的所有文件夹，返回被选定文件夹的路径名，如果未选中任何文件夹，则返回空文本。"),2 , NULL, SDT_TEXT , 0, LVL_SIMPLE,0 ,0 ,sizeof(BrowseForFolderArg) / sizeof(BrowseForFolderArg[0]), BrowseForFolderArg},
	{ _WT("删除到回收站"), _WT("DeleteIntoRecycleBin"), _WT("本命令可以将一个或一批文件删除到Windows系统回收站中，成功返回真，失败或被用户中止删除操作返回假。"),2 , NULL, SDT_BOOL , 0, LVL_SIMPLE,0 ,0 ,sizeof(DeleteIntoRecycleBinArg) / sizeof(DeleteIntoRecycleBinArg[0]),DeleteIntoRecycleBinArg},
	{ _WT("进度复制文件"), _WT("ShellCopyFile"), _WT("本命令可以将一个或一批文件复制到另一个目录中，并同时显示一个复制进度对话框，成功返回真，失败或被用户中止复制操作返回假。"),2 , NULL, SDT_BOOL , 0, LVL_SIMPLE,0 ,0 ,sizeof(ShellCopyFileArg) / sizeof(ShellCopyFileArg[0]),ShellCopyFileArg},
	{ _WT("进度移动文件"), _WT("ShellMoveFile"), _WT("本命令可以将一个或一批文件移动到另一个目录中，并同时显示一个移动进度对话框，成功返回真，失败或被用户中止移动操作返回假。"),2 , NULL, SDT_BOOL , 0, LVL_SIMPLE,0 ,0 ,sizeof(ShellCopyFileArg) / sizeof(ShellCopyFileArg[0]),ShellCopyFileArg},
	{ _WT("执行"), _WT("ShellExecute"), _WT("使用Windows的用户界面系统执行指定命令。"),3 , NULL, SDT_BOOL , 0, LVL_SIMPLE,0 ,0 ,sizeof(ShellExecuteArg) / sizeof(ShellExecuteArg[0]),ShellExecuteArg},
	{ _WT("取特定目录"), _WT("GetSpecialFolderPath"), _WT("本命令返回指定的Windows系统特定目录，所返回目录名以“\\”符号结束，如失败返回空文本。"),3 , NULL, SDT_TEXT , 0, LVL_SIMPLE,0 ,0 ,sizeof(GetSpecialFolderPathArg) / sizeof(GetSpecialFolderPathArg[0]),GetSpecialFolderPathArg},
	{ _WT("关闭系统"), _WT("ExitWindows"), _WT("本命令可以执行关机、重启、注销等Windows系统操作。成功返回真，失败返回假。"),3 , NULL, SDT_BOOL , 0, LVL_SIMPLE,0 ,0 ,sizeof(ExitWindowsArg) / sizeof(ExitWindowsArg[0]),ExitWindowsArg},

};

static LIB_CONST_INFO s_ConstInfo[] =
{		 /* { 中文名称, 英文名称, 常量布局, 常量等级(LVL_), 参数类型(CT_), 文本内容, 数值内容 } */
	{_T("编辑文档"), NULL, NULL,  1,  CT_NUM,NULL,1},
	{_T("浏览文件夹"), NULL, NULL,  1,  CT_NUM,NULL,2},
	{_T("寻找文件"), NULL, NULL,  1,  CT_NUM,NULL,3},
	{_T("打开文件"), NULL, NULL,  1,  CT_NUM,NULL,4},
	{_T("打印文档"), NULL, NULL,  1,  CT_NUM,NULL,5},
	{_T("我的文档"), NULL, NULL,  1,  CT_NUM,NULL,1},
	{_T("我的收藏夹"), NULL, NULL,  1,  CT_NUM,NULL,2},
	{_T("系统桌面"), NULL, NULL,  1,  CT_NUM,NULL,3},
	{_T("系统字体"), NULL, NULL,  1,  CT_NUM,NULL,4},
	{_T("开始菜单组"), NULL, NULL,  1,  CT_NUM,NULL,5},
	{_T("程序菜单组"), NULL, NULL,  1,  CT_NUM,NULL,6},
	{_T("启动菜单组"), NULL, NULL,  1,  CT_NUM,NULL,7},
	{_T("程序数据目录"), NULL, NULL,  1,  CT_NUM,NULL,8},
	{_T("Windows安装目录"), NULL, NULL,  1,  CT_NUM,NULL,9},
	{_T("Windows系统目录"), NULL, NULL,  1,  CT_NUM,NULL,10},
	{_T("临时文件目录"), NULL, NULL,  1,  CT_NUM,NULL,11},
	{_T("不询问删除"), NULL, NULL,  1,  CT_NUM,NULL,1},
	{_T("不提示错误"), NULL, NULL,  1,  CT_NUM,NULL,2},
	{_T("不显示进度"), NULL, NULL,  1,  CT_NUM,NULL,4},
	{_T("关机"), NULL, NULL,  1,  CT_NUM,NULL,1},
	{_T("重启"), NULL, NULL,  1,  CT_NUM,NULL,2},
	{_T("注销"), NULL, NULL,  1,  CT_NUM,NULL,3},
	{_T("休眠"), NULL, NULL,  1,  CT_NUM,NULL,4},
	{_T("冬眠"), NULL, NULL,  1,  CT_NUM,NULL,5},
};





#ifndef __E_STATIC_LIB
static LIB_INFO LibInfo =
{

	/* { 库格式号, GUID串号, 主版本号, 次版本号, 构建版本号, 系统主版本号, 系统次版本号, 核心库主版本号, 核心库次版本号,

	支持库名, 支持库语言, 支持库描述, 支持库状态,

	作者姓名, 邮政编码, 通信地址, 电话号码, 传真号码, 电子邮箱, 主页地址, 其它信息,

	类型数量, 类型指针, 类别数量, 命令类别, 命令总数, 命令指针, 命令入口,

	附加功能, 功能描述, 消息指针, 超级模板, 模板描述,

	常量数量, 常量指针, 外部文件} */
	LIB_FORMAT_VER,//库格式号
	_T(LIB_GUID_STR),//GUID串号
	LIB_MajorVersion,//主版本号
	LIB_MinorVersion,//次版本号
	LIB_BuildNumber,//构建版本号
	LIB_SysMajorVer,//系统主版本号
	LIB_SysMinorVer,//系统次版本号
	LIB_KrnlLibMajorVer,//核心库主版本号
	LIB_KrnlLibMinorVer,//核心库次版本号
	_T(LIB_NAME_STR),//支持库名
	__GBK_LANG_VER,//支持库语言
	_WT(LIB_DESCRIPTION_STR),//支持库描述
	_LIB_OS(__OS_WIN),//支持库状态
	_WT(LIB_Author),//作者姓名
	_WT(LIB_ZipCode),// 邮政编码
	_WT(LIB_Address),//通信地址
	_WT(LIB_Phone),//电话号码
	_WT(LIB_Fax),//传真号码
	_WT(LIB_Email),//电子邮箱
	_WT(LIB_HomePage),//主页地址
	_WT(LIB_Other),//其它信息
	0,//类型数量
	0,//类型指针
	LIB_TYPE_COUNT,//类别数量
	_WT(LIB_TYPE_STR),//命令类别
   sizeof(s_Commands) / sizeof(s_Commands[0]),//命令总数
	s_Commands,//命令指针
	s_ExecuteCommand,//命令入口
	NULL,//附加功能
	NULL,//功能描述
	shell_ProcessNotifyLib,//消息指针
	NULL,//超级模板
	NULL,//模板描述
	sizeof(s_ConstInfo)/ sizeof(s_ConstInfo[0]),//常量数量
	s_ConstInfo,//常量指针
	NULL//外部文件
};





extern "C" PLIB_INFO  GetNewInf()

{

	return (&LibInfo);

};
#endif
EXTERN_C INT WINAPI shell_ProcessNotifyLib(INT nMsg, DWORD dwParam1, DWORD dwParam2)
{

#ifndef __E_STATIC_LIB

	if (nMsg == NL_GET_CMD_FUNC_NAMES) // 返回所有命令实现函数的的函数名称数组(char*[]), 支持静态编译的动态库必须处理

		return (INT)CommandNames;

	else if (nMsg == NL_GET_NOTIFY_LIB_FUNC_NAME) // 返回处理系统通知的函数名称(PFN_NOTIFY_LIB函数名称), 支持静态编译的动态库必须处理

		return (INT)LIBARAYNAME;

	else if (nMsg == NL_GET_DEPENDENT_LIBS) return (INT)NULL;

	// 返回静态库所依赖的其它静态库文件名列表(格式为\0分隔的文本,结尾两个\0), 支持静态编译的动态库必须处理

	// kernel32.lib user32.lib gdi32.lib 等常用的系统库不需要放在此列表中

	// 返回NULL或NR_ERR表示不指定依赖文件

#endif

	return ProcessNotifyLib(nMsg, dwParam1, dwParam2);

}