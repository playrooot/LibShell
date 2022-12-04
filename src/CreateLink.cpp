#include <shlobj.h>
#include<string>
using namespace std;

BOOL CreateLink(const string &LinkName, const string& FilePath, const string& remark, WORD wHotkey, const string& comline, const string& workdir)
{
	BOOL blSucceeded = FALSE;
	IShellLink* piShellLink;
	if (SUCCEEDED(CoCreateInstance(CLSID_ShellLink, NULL, CLSCTX_INPROC_SERVER, IID_IShellLink, (void**)&piShellLink)))
	{
		IPersistFile* piPersistFile;
		if (SUCCEEDED(piShellLink->QueryInterface(IID_IPersistFile, (void**)&piPersistFile)))
		{
			piShellLink->SetPath(FilePath.c_str());
			piShellLink->SetShowCmd(SW_SHOW);
			if (remark.empty() == FALSE)  piShellLink->SetDescription(remark.c_str());
			if (comline.empty() == FALSE)  piShellLink->SetArguments(comline.c_str());
			if (wHotkey != 0)  piShellLink->SetHotkey(wHotkey);
			if (workdir.empty() == FALSE)  piShellLink->SetWorkingDirectory(workdir.c_str());
			const char* FileNmae = (strchr(LinkName.c_str(), '.') != NULL ? LinkName.c_str() : (LinkName + ".lnk").c_str());
			WCHAR WideCharStr[MAX_PATH] = { 0 };
			MultiByteToWideChar(0, 0, FileNmae, -1, WideCharStr, MAX_PATH);
			blSucceeded = SUCCEEDED(piPersistFile->Save(WideCharStr, TRUE));
			piPersistFile->Release();
		}
		piShellLink->Release();
	}
	return blSucceeded;
}
