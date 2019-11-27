#include <windows.h>
#include <iostream>
#include <cstdlib>

#define FILE_MENU_NEW 1
#define FILE_MENU_OPEN 2
#define FILE_MENU_EXIT 3
#define GENERATE_BUTTON 4

LRESULT CALLBACK WindowProcedure(HWND,UINT,WPARAM,LPARAM);

void AddMenus(HWND);
void AddControls(HWND hWnd);
void loadImages();

HMENU hMenu;
HWND hName, hAge, hOut, hLogo;
HBITMAP hLogoImage, hGenerateImage;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd){
    //MessageBox(NULL, "Hello", "My first GUI", MB_OK);//A simple message.
    WNDCLASSW wc = {0};
    wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hInstance = hInstance;
    wc.lpszClassName = L"myWindowClass";
    wc.lpfnWndProc = WindowProcedure;
    
    if(!RegisterClassW(&wc)){
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
    int val;
    switch(msg){
        case WM_COMMAND:
            switch(wp){
                case FILE_MENU_EXIT:
                    //DestroyWindow(hWnd);
                    val = MessageBoxW(NULL, L"Are you sure?", L"Wait!!!", MB_YESNO | MB_ICONEXCLAMATION);
                    if(val == IDYES) DestroyWindow(hWnd);
                    break;
                case FILE_MENU_NEW:
                    MessageBeep(MB_ICONINFORMATION);
                    break;
                case GENERATE_BUTTON:
                    wchar_t name[30], age[10], out[50];
                    GetWindowTextW(hName, name, 30);
                    GetWindowTextW(hAge, age, 10);

                    if(wcscmp(name,L"")==0||wcscmp(age,L"")==0){
                        val = MessageBoxW(hWnd, L"You did not enter anything!", NULL, MB_ABORTRETRYIGNORE|MB_ICONERROR);
                        switch (val)
                        {
                        case IDABORT:
                            DestroyWindow(hWnd);
                            break;                        
                        case IDRETRY:
                            return 0;
                        case IDIGNORE:
                            break;
                        }
                    }


                    wcscpy(out, name);
                    wcscat(out, L" is ");
                    wcscat(out, age);
                    wcscat(out, L" old.");
                    SetWindowTextW(hOut,out);
                    break;
            }
            break;
        case WM_CREATE:
            AddMenus(hWnd);
            loadImages();
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
    
    AppendMenuW(hSubMenu, MF_STRING, 0, L"Item");
    
    AppendMenuW(hFileMEnu, MF_STRING, FILE_MENU_NEW, L"New");
    AppendMenuW(hFileMEnu, MF_POPUP, (UINT_PTR)hSubMenu, L"Open");
    AppendMenuW(hFileMEnu, MF_SEPARATOR, 0, NULL);
    AppendMenuW(hFileMEnu, MF_STRING, FILE_MENU_EXIT, L"Exit");
    
    AppendMenuW(hMenu, MF_POPUP,(UINT_PTR)hFileMEnu, L"File");
    AppendMenuW(hMenu, MF_STRING,1, L"Help");
    SetMenu(hWnd, hMenu);
}

void AddControls(HWND hWnd){
    CreateWindowExW(0, L"Static", L"Name: ", WS_VISIBLE|WS_CHILD,100,50,98,38,hWnd,NULL,NULL,NULL);
    hName = CreateWindowExW(0, L"Edit", L"", WS_VISIBLE|WS_CHILD|WS_BORDER,200,50,98,38,hWnd,NULL,NULL,NULL);

    CreateWindowExW(0, L"Static", L"Age: ", WS_VISIBLE|WS_CHILD,100,90,98,38,hWnd,NULL,NULL,NULL);
    hAge = CreateWindowExW(0, L"Edit", L"", WS_VISIBLE|WS_CHILD|WS_BORDER,200,90,98,38,hWnd,NULL,NULL,NULL);

    HWND hBut = CreateWindowExW(0, L"Button", L"Generate", WS_VISIBLE|WS_CHILD|BS_BITMAP,150,140,98,38,hWnd,(HMENU)GENERATE_BUTTON,NULL,NULL);
    SendMessageW(hBut, BM_SETIMAGE, IMAGE_BITMAP, (LPARAM)hGenerateImage );

    hOut = CreateWindowExW(0, L"Edit", L"", WS_VISIBLE|WS_CHILD|WS_BORDER,100,200,300,200,hWnd,NULL,NULL,NULL);
    hLogo = CreateWindowExW(0, L"Static", NULL, WS_VISIBLE|WS_CHILD|SS_BITMAP,350,60,100,100,hWnd,NULL,NULL,NULL);
    SendMessageW(hLogo, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)hLogoImage );
}

void loadImages(){
    hLogoImage = (HBITMAP)LoadImageW(NULL, L"Logo.bmp", IMAGE_BITMAP,100,100,LR_LOADFROMFILE);
    hGenerateImage = (HBITMAP)LoadImageW(NULL, L"Generate.bmp", IMAGE_BITMAP,98,38,LR_LOADFROMFILE);
}