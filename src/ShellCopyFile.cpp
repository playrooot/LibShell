#include"windows.h"
#include"string"

using namespace std;

bool ShellCopyFile(char* DestDir, char* SourceFile)
{
    bool ret = false;
    if (DestDir && SourceFile) {
        size_t Lenth = strlen(SourceFile), PathLenth = strlen(DestDir);;
        char* Filename = new char[Lenth + 2], * Dest = new char[PathLenth + 2];    //Ë«½áÊø·û½áÎ²
        SHFILEOPSTRUCT FileOp = { 0 };
        FileOp.wFunc = FO_COPY;
        FileOp.fFlags = FOF_ALLOWUNDO;
        strcpy(Filename, SourceFile);
        strcpy(Dest, DestDir);
        FileOp.pFrom = Filename;
        FileOp.pTo = Dest;
        if (!::SHFileOperationA(&FileOp) && !FileOp.fAnyOperationsAborted)
            ret = true;
        delete[]Filename;
        delete[] Dest;
    }
    return  ret;
}