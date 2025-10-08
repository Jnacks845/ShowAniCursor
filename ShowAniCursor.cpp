// ShowAniCursor by katahiromz
// License: MIT
#include <windows.h>
#include <windowsx.h>
#include <commctrl.h>

HINSTANCE g_hInst = NULL;

HICON LoadAnimatedIcon(HINSTANCE hInst, LPCTSTR name)
{
    HRSRC hRsrc = FindResource(hInst, name, RT_ANIICON);
    DWORD cbData = SizeofResource(hInst, hRsrc);
    HGLOBAL hGlobal = LoadResource(hInst, hRsrc);
    LPVOID pvData = LockResource(hGlobal);
    return (HCURSOR)CreateIconFromResource((PBYTE)pvData, cbData, TRUE, 0x00030000);
}

HCURSOR LoadAnimatedCursor(HINSTANCE hInst, LPCTSTR name)
{
    HRSRC hRsrc = FindResource(hInst, name, RT_ANICURSOR);
    DWORD cbData = SizeofResource(hInst, hRsrc);
    HGLOBAL hGlobal = LoadResource(hInst, hRsrc);
    LPVOID pvData = LockResource(hGlobal);
    return (HCURSOR)CreateIconFromResource((PBYTE)pvData, cbData, FALSE, 0x00030000);
}

BOOL OnInitDialog(HWND hwnd, HWND hwndFocus, LPARAM lParam)
{
    HCURSOR hCursor = LoadAnimatedCursor(g_hInst, MAKEINTRESOURCE(1));
    //HCURSOR hCursor = LoadCursorFromFile(TEXT("searching.ani"));
    SendDlgItemMessage(hwnd, ico1, STM_SETIMAGE, IMAGE_CURSOR, (LPARAM)hCursor);
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
    g_hInst = hInstance;
    InitCommonControls();
    DialogBox(hInstance, MAKEINTRESOURCE(1), NULL, DialogProc);
    return 0;
}
