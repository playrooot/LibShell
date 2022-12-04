#include"windows.h"
#include"string"
using namespace std;

bool ShellMoveFile(char* DestDir, char* SourceFile)
{
    bool ret = false;
    if (DestDir && SourceFile) {
        size_t Lenth = strlen(SourceFile), PathLenth = strlen(DestDir);
        char* Filename = new char[Lenth + 2], * Dest = new char[PathLenth + 2];;
        strcpy(Filename, SourceFile);
        Filename[Lenth + 1] = '\0';
        Filename[Lenth] = '\0';
        strcpy(Dest, DestDir);
        SourceFile[PathLenth + 1] = '\0';
        SourceFile[PathLenth] = '\0';
        SHFILEOPSTRUCTA FileOp = { 0 };
        FileOp.wFunc = FO_MOVE;
        FileOp.pFrom = Filename;
        FileOp.pTo = Dest;
        if (!::SHFileOperationA(&FileOp) && !FileOp.fAnyOperationsAborted)
            ret = true;
        delete[]Filename;
        delete[] Dest;
    }
    return  ret;
}