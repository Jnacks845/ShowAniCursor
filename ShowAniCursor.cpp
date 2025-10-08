#include <windows.h>
#include <windowsx.h>

HICON LoadAniIcon(HINSTANCE hInst, LPCTSTR name)
{
    HRSRC hRsrc = FindResource(hInst, name, RT_RCDATA);
    DWORD cbData = SizeofResource(hInst, hRsrc);
    HGLOBAL hGlobal = LoadResource(hInst, hRsrc);
    LPVOID pvData = LockResource(hGlobal);
    return (HCURSOR)CreateIconFromResource((PBYTE)pvData, cbData, TRUE, 0x00030000);
}

HCURSOR LoadAniCursor(HINSTANCE hInst, LPCTSTR name)
{
    HRSRC hRsrc = FindResource(hInst, name, RT_RCDATA);
    DWORD cbData = SizeofResource(hInst, hRsrc);
    HGLOBAL hGlobal = LoadResource(hInst, hRsrc);
    LPVOID pvData = LockResource(hGlobal);
    return (HCURSOR)CreateIconFromResource((PBYTE)pvData, cbData, FALSE, 0x00030000);
}

BOOL OnInitDialog(HWND hwnd, HWND hwndFocus, LPARAM lParam)
{
    HCURSOR hcur = LoadAniCursor(GetModuleHandle(NULL), MAKEINTRESOURCE(1));
    //HCURSOR hcur = LoadCursorFromFile(TEXT("Minecraft's Compass.ani"));
    SendDlgItemMessage(hwnd, ico1, STM_SETIMAGE, IMAGE_CURSOR, (LPARAM)hcur);
    return TRUE;
}

void OnCommand(HWND hwnd, int id, HWND hwndCtl, UINT codeNotify)
{
    switch (id)
    {
    case IDOK:
    case IDCANCEL:
        EndDialog(hwnd, id);
        break;
    }
}

INT_PTR CALLBACK
DialogProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg)
    {
        HANDLE_MSG(hwnd, WM_INITDIALOG, OnInitDialog);
        HANDLE_MSG(hwnd, WM_COMMAND, OnCommand);
    }
    return 0;
}

INT WINAPI
WinMain(HINSTANCE   hInstance,
        HINSTANCE   hPrevInstance,
        LPSTR       lpCmdLine,
        INT         nCmdShow)
{
    DialogBox(hInstance, MAKEINTRESOURCE(1), NULL, DialogProc);
    return 0;
}
