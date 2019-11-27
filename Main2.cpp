#include <windows.h>
#include <iostream>

#define FILE_MENU_NEW 1
#define FILE_MENU_OPEN 2
#define FILE_MENU_EXIT 3

LRESULT CALLBACK WindowProcedure(HWND,UINT,WPARAM,LPARAM);

void AddMenus(HWND);
HMENU hMenu;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd){
    //MessageBox(NULL, "Hello", "My first GUI", MB_OK);//A simple message.
    WNDCLASSW wc = {0};
    wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hInstance = hInstance;
    wc.lpszClassName = L"myWindowClass";
    wc.lpfnWndProc = WindowProcedure;
    
    if(!RegisterClassW(&wc)){
        std::cerr << "pepe";
        return -1;
    }
    CreateWindowW(L"myWindowClass",L"My Window", WS_OVERLAPPEDWINDOW|WS_VISIBLE, 100,100,500,500,NULL,NULL,NULL,NULL);
    
    MSG msg;
    while(GetMessage(&msg,NULL,0,0)){
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    
    return msg.wParam;
}

LRESULT CALLBACK WindowProcedure(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp){
    switch(msg){
        case WM_COMMAND:
            switch(wp){
                case FILE_MENU_EXIT:
                    DestroyWindow(hWnd);
                    break;
                case FILE_MENU_NEW:
                    MessageBeep(MB_ICONINFORMATION);
                    break;
            }
            break;
        case WM_CREATE:
            AddMenus(hWnd);
            break;
        case WM_DESTROY:
            PostQuitMessage(0);
            break;
    }
    return DefWindowProcW(hWnd,msg,wp,lp);
}

void AddMenus(HWND hWnd){
    hMenu = CreateMenu();
    HMENU hFileMEnu = CreateMenu();
    HMENU hSubMenu = CreateMenu();
    
    AppendMenu(hSubMenu, MF_STRING, 0, "SubMenu Item");
    
    AppendMenu(hFileMEnu, MF_STRING, FILE_MENU_NEW, "New");
    AppendMenu(hFileMEnu, MF_POPUP, (UINT_PTR)hSubMenu, "Open");
    AppendMenu(hFileMEnu, MF_SEPARATOR, 0, NULL);
    AppendMenu(hFileMEnu, MF_STRING, FILE_MENU_EXIT, "Exit");
    
    AppendMenu(hMenu, MF_POPUP,(UINT_PTR)hFileMEnu,"File");
    AppendMenu(hMenu, MF_STRING,1,"Help");
    SetMenu(hWnd, hMenu);
}