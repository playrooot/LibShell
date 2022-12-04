#include<string>
#include <shlobj.h>
using namespace std;

char* shell_CloneTextData(char* ps);

char* GetSpecialFolderPath(DWORD Type) {
	CHAR path[MAX_PATH + 1] = {0};
	BOOL IsSucceeded = FALSE;
	if (Type >= 1 && Type <= 8) {
		IsSucceeded = SHGetSpecialFolderPath(NULL, path, (Type == 1 ? CSIDL_PERSONAL : Type == 2 ? CSIDL_FAVORITES : Type == 3 ? CSIDL_DESKTOPDIRECTORY :
			Type == 4 ? CSIDL_FONTS : Type == 5 ? CSIDL_STARTMENU : Type == 6 ? CSIDL_PROGRAMS : Type == 7 ? CSIDL_STARTUP : CSIDL_APPDATA), FALSE);
	}
	else if (Type == 9) {
		IsSucceeded = (GetWindowsDirectory(path, MAX_PATH) > 0);
	}
	else if (Type == 10) {
		IsSucceeded = (GetSystemDirectory(path, MAX_PATH) > 0);
	}
	else
	{
		if (Type != 11) {
			return 0;
		}
		IsSucceeded = (GetTempPath(MAX_PATH, path) > 0);
	}
	CHAR* Ret = 0;
	if (IsSucceeded)
	{
		size_t lenth = strlen(path);
		if (lenth > 0 && path[lenth-1] != '\\')
		{
			path[lenth] = '\\';
			path[lenth + 1] = '\0';
		}
		Ret = shell_CloneTextData(path);
	}
	return Ret;
};