//#include"windows.h"
//#include"string"
//#include"shtypes.h"
#include<string>
#include <shlobj.h>
using namespace std;

char* shell_CloneTextData(char* ps);

char* BrowseForFolder(char* Title, bool IsDisplayFile, HWND hWndParent) {
    BROWSEINFOA bi = { 0 };
    CHAR pszPath[MAX_PATH];
    bi.pszDisplayName = pszPath;
    bi.lpszTitle = Title;
    bi.ulFlags = BIF_EDITBOX;
    char* ret = NULL;
    if (IsDisplayFile)//�Ƿ���ʾ�ļ�
    {
        bi.ulFlags |= BIF_BROWSEINCLUDEFILES;
    }
    HWND hWnd = IsWindow(hWndParent) != 0 ? hWndParent : GetActiveWindow();//�������Ƿ���Ч
    bi.hwndOwner = IsWindow(hWnd) != 0 ? hWnd : NULL;//ȡ��ǰ���̻����
    if (LPITEMIDLIST pil = SHBrowseForFolderA(&bi))
    {
        if (SHGetPathFromIDListA(pil, pszPath)) {
            ret = shell_CloneTextData(pszPath);
        }
        IMalloc* ppMalloc;
        if (SHGetMalloc(&ppMalloc) >= 0)
        {

            ppMalloc->Free(pil);
            ppMalloc->Release();
        }
    }
    return ret;
}
