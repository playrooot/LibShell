#include"windows.h"

BOOL DeleteIntoRecycleBin(int DeleteSelect, char* Path)
{
    BOOL ret = FALSE;
    if (Path)
    {
        SHFILEOPSTRUCT FileOp = { 0 };
        FileOp.lpszProgressTitle = 0;
        FileOp.pTo = NULL;
        FileOp.wFunc = FO_DELETE;
        FileOp.fFlags = FOF_ALLOWUNDO;
        size_t lenth = strlen(Path);
        char* FileName = new char[lenth + 2]; ;//Ë«½áÊø·û½áÎ²
        strcpy(FileName, Path);
        FileName[lenth + 1] = '\0';
        FileName[lenth] = '\0';
        FileOp.pFrom = FileName;
        if (DeleteSelect)
        {
            if (DeleteSelect & 1)
                FileOp.fFlags = FOF_NOCONFIRMATION;
            if (DeleteSelect & 2)
                FileOp.fFlags |= FOF_NOERRORUI;
            if (DeleteSelect & 4)
                FileOp.fFlags |= FOF_SILENT;
        }
        if (!::SHFileOperationA(&FileOp) && !FileOp.fAnyOperationsAborted)
            ret = TRUE;
        delete[]FileName;
    }
    return ret;
}