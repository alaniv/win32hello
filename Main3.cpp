#include <windows.h>
#include <iostream>

#define FILE_MENU_NEW 1
#define FILE_MENU_OPEN 2
#define FILE_MENU_EXIT 3
#define CHANGE_TITLE 4

LRESULT CALLBACK WindowProcedure(HWND,UINT,WPARAM,LPARAM);

void AddMenus(HWND);
void AddControls(HWND hWnd);
HMENU hMenu;
HWND hEdit;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd){
    //MessageBox(NULL, "Hello", "My first GUI", MB_OK);//A simple message.
    WNDCLASSW wc = {0};
    wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hInstance = hInstance;
    wc.lpszClassName = L"myWindowClass";
    wc.lpfnWndProc = WindowProcedure;
    
    std::cerr << "yee";

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
                case CHANGE_TITLE:
                    wchar_t text[100];
                    GetWindowTextW(hEdit, text, 100);
                    std::cout << text[0];
                    SetWindowTextW(hWnd,text);
                    break;
            }
            break;
        case WM_CREATE:
            AddMenus(hWnd);
            AddControls(hWnd);
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
    
    AppendMenuW(hSubMenu, MF_STRING, CHANGE_TITLE, L"Change Title");
    
    AppendMenuW(hFileMEnu, MF_STRING, FILE_MENU_NEW, L"New");
    AppendMenuW(hFileMEnu, MF_POPUP, (UINT_PTR)hSubMenu, L"Open");
    AppendMenuW(hFileMEnu, MF_SEPARATOR, 0, NULL);
    AppendMenuW(hFileMEnu, MF_STRING, FILE_MENU_EXIT, L"Exit");
    
    AppendMenuW(hMenu, MF_POPUP,(UINT_PTR)hFileMEnu, L"File");
    AppendMenuW(hMenu, MF_STRING,1, L"Help");
    SetMenu(hWnd, hMenu);
}

void AddControls(HWND hWnd){
    CreateWindowW(L"Static", L"Enter Text here :", WS_VISIBLE|WS_CHILD|WS_BORDER|SS_CENTER,200,100,100,50,hWnd,NULL,NULL,NULL);
    hEdit = CreateWindowW(L"Edit", L"...", WS_VISIBLE|WS_CHILD|WS_BORDER|SS_CENTER|ES_MULTILINE|ES_AUTOVSCROLL|ES_AUTOHSCROLL,200,152,100,50,hWnd,NULL,NULL,NULL);
}