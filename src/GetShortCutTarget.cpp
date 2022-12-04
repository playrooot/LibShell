#include <shlobj.h>
#include<string>
using namespace std;

BOOL GetShortCutTarget(const wstring& lpszLinkFilePath, wstring& FilePath)
{
    SHFILEINFOW info = { 0 };
    FilePath = wstring();
    BOOL bReturn = FALSE;
    if (SHGetFileInfoW(lpszLinkFilePath.c_str(), 0, &info, sizeof(info), SHGFI_ATTRIBUTES) != 0 && (info.dwAttributes & SFGAO_LINK) != 0) {

        IShellLinkW* pShellLink = 0;
        CoInitialize(NULL);
        if (S_OK == CoCreateInstance(CLSID_ShellLink, NULL, CLSCTX_INPROC_SERVER, IID_IShellLinkW, (void**)&pShellLink))
        {
            IPersistFile* pPersistFile = 0;
            if (S_OK == pShellLink->QueryInterface(IID_IPersistFile, (void**)&pPersistFile))
            {
                if (S_OK == pPersistFile->Load(lpszLinkFilePath.c_str(), STGM_READ))
                {
                    WCHAR Temp[MAX_PATH] = { 0 };
                    if (S_OK == pShellLink->GetPath(Temp, MAX_PATH, 0, SLGP_UNCPRIORITY))//ÎÄ¼þÂ·¾¶
                    {
                        FilePath = Temp;
                    }
                }
                pPersistFile->Release();
            }
            pShellLink->Release();
        }
        CoUninitialize();
    }
    return bReturn;
}



