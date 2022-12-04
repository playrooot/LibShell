#include"windows.h"
#include"string"
using namespace std;
static const int ShowCmds[] = { SW_HIDE,SW_SHOWNORMAL,SW_SHOWMINIMIZED,SW_SHOWMAXIMIZED,SW_SHOWNA,SW_MINIMIZE };

HINSTANCE  MyShellExecute(int CommandType, char* FileName, char* CommandLine, char* CurrentDir, int DisplayMode)
{
    INT Mod = SW_SHOWNORMAL;
    HINSTANCE result;

    if (DisplayMode >= 1 && DisplayMode <= 6) {
        Mod = ShowCmds[DisplayMode - 1];
    }
    switch (CommandType)
    {
    case 1:
        result = ShellExecuteA(0, "edit", FileName, CommandLine, CurrentDir, Mod);
        break;
    case 2:
        result = ShellExecuteA(0, "explore", FileName, CommandLine, CurrentDir, Mod);
        break;
    case 3:
        result = ShellExecuteA(0, "find", FileName, CommandLine, CurrentDir, Mod);
        break;
    case 4:
        result = ShellExecuteA(0, "open", FileName, CommandLine, CurrentDir, Mod);
        break;
    default:
        result = ShellExecuteA(0, CommandType != 5 ? NULL : "print", FileName, CommandLine, CurrentDir, Mod);
        break;
    }
    return result;
}