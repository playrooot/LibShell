#include<windows.h>

void  RIGHT_PRIVILEGES()
{
    HANDLE hToken;
    TOKEN_PRIVILEGES NewPermission, OldNewPermission;
    LUID Luid;
    OpenProcessToken(GetCurrentProcess(), TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY, &hToken);
    LookupPrivilegeValue(NULL, SE_SHUTDOWN_NAME, &Luid);
    NewPermission.PrivilegeCount = 1;
    NewPermission.Privileges->Luid = Luid;
    NewPermission.Privileges->Attributes = SE_PRIVILEGE_ENABLED;
    AdjustTokenPrivileges(hToken, FALSE, &NewPermission, sizeof(TOKEN_PRIVILEGES), &OldNewPermission,NULL);
}


BOOL MyExitWindows(int Type, bool Enforce)
{
    BOOL result = FALSE;
    UINT uFlag = 0;
    RIGHT_PRIVILEGES();
    if (Type >= 1 && Type <= 5)
    {
        if (Type < 4)
        {
            if (Type == 1)
            {
                OSVERSIONINFO osv = { 0 };
                osv.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);
                GetVersionEx(&osv);
                if (osv.dwPlatformId == VER_PLATFORM_WIN32_NT)
                    uFlag = EWX_POWEROFF;
                else
                    uFlag = EWX_SHUTDOWN;
            }
            else if (Type == 2)
            {
                uFlag = EWX_REBOOT;
            }
            else
            {
                uFlag = EWX_LOGOFF;
            }
            if (Enforce)
                uFlag = uFlag | 4;
            result = ExitWindowsEx(uFlag, 0);
        }
        else
        {
            result = SetSystemPowerState(Type == 4, Enforce);
        }
    }
    return result;
}