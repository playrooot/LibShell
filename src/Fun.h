#include<string>
#include<Windows.h>

using namespace std;
BOOL CreateLink(const string& LinkName, const string& FilePath, const string& remark, WORD wHotkey, const string& comline, const string& workdir);
BOOL GetShortCutTarget(const wstring& lpszLinkFilePath, wstring& FilePath);
char* BrowseForFolder(char* Title, bool IsDisplayFile, HWND hWndParent);
BOOL DeleteIntoRecycleBin(int DeleteSelect, char* Path);
bool ShellCopyFile(char* DestDir, char* SourceFile);
bool ShellMoveFile(char* DestDir, char* SourceFile);
HINSTANCE  MyShellExecute(int CommandType, char* FileName, char* CommandLine, char* CurrentDir, int DisplayMode);
char* GetSpecialFolderPath(DWORD Type);
BOOL MyExitWindows(int Type, bool Enforce);