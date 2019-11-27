#include <windows.h>
#include <cstdio>

#define OPEN_FILE_BUTTON 1
#define SAVE_FILE_BUTTON 2

LRESULT CALLBACK WindowProcedure(HWND,UINT,WPARAM,LPARAM);

void AddControls(HWND hWnd);
void OpenFile(HWND hWnd);
void SaveFile(HWND hWnd);
void displayFile(char* path);
void storeFile(char* path);

HWND hMainWindow, hEdit;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd){
    WNDCLASSW wc = {0};
    wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hInstance = hInstance;
    wc.lpszClassName = L"myWindowClass";
    wc.lpfnWndProc = WindowProcedure;
    if(!RegisterClassW(&wc))
        return -1;

    hMainWindow = CreateWindowW(L"myWindowClass",L"My Window", WS_OVERLAPPEDWINDOW|WS_VISIBLE, 100,100,500,500,NULL,NULL,NULL,NULL);

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
            switch (wp)
            {
                case OPEN_FILE_BUTTON:
                    OpenFile(hWnd);
                    break;
                case SAVE_FILE_BUTTON:
                    SaveFile(hWnd);
                    break;
            }
            break;
        case WM_CREATE:
            AddControls(hWnd);
            break;
        case WM_DESTROY:
            PostQuitMessage(0);
            break;
    }
    return DefWindowProcW(hWnd,msg,wp,lp);
}

void AddControls(HWND hWnd){
    CreateWindowExW(0, L"Button", L"Open File ", WS_VISIBLE|WS_CHILD,10,10,150,36,hWnd,(HMENU)OPEN_FILE_BUTTON,NULL,NULL);
    CreateWindowExW(0, L"Button", L"Save File ", WS_VISIBLE|WS_CHILD,170,10,150,36,hWnd,(HMENU)SAVE_FILE_BUTTON,NULL,NULL);
    hEdit = CreateWindowExW(0, L"Edit", L"", WS_VISIBLE|WS_CHILD|ES_MULTILINE|WS_BORDER|WS_VSCROLL|WS_HSCROLL, 10,50,400,300,hWnd,NULL,NULL,NULL);
}

void displayFile(char* path){
    FILE *file;
    file = fopen(path, "rb");
    fseek(file,0,SEEK_END);
    int _size = ftell(file);
    rewind(file);
    char * data = new char[_size+1];
    fread(data,_size,1,file);
    data[_size] = '\0';

    SetWindowTextA(hEdit, data);
    fclose(file);
}

void OpenFile(HWND hWnd){
    OPENFILENAMEA ofn;
    char file_name[100];
    ZeroMemory(&ofn, sizeof(OPENFILENAMEA));
    ofn.lStructSize = sizeof(OPENFILENAMEA);
    ofn.hwndOwner = hWnd;
    ofn.lpstrFile = file_name;
    ofn.lpstrFile[0] = '\0';
    ofn.nMaxFile = 100;
    ofn.lpstrFilter = "All files\0*.*\0Source Files\0*.CPP\0Text Files\0*.TXT\0";
    ofn.nFilterIndex = 1;
    GetOpenFileNameA(&ofn);
    displayFile(ofn.lpstrFile);
    MessageBoxA(NULL, ofn.lpstrFile, "", MB_OK);
}

void storeFile(char* path){
    FILE *file;
    file = fopen(path, "w");

    int _size = GetWindowTextLengthA(hEdit);
    char * data = new char[_size+1];
    GetWindowTextA(hEdit, data, _size+1);
    fwrite(data,_size+1,1,file);
    fclose(file);
}

void SaveFile(HWND hWnd){
    OPENFILENAMEA ofn;
    char file_name[100];
    ZeroMemory(&ofn, sizeof(OPENFILENAMEA));
    ofn.lStructSize = sizeof(OPENFILENAMEA);
    ofn.hwndOwner = hWnd;
    ofn.lpstrFile = file_name;
    ofn.lpstrFile[0] = '\0';
    ofn.nMaxFile = 100;
    ofn.lpstrFilter = "All files\0*.*\0Source Files\0*.CPP\0Text Files\0*.TXT\0";
    ofn.nFilterIndex = 1;
    GetSaveFileNameA(&ofn);
    storeFile(ofn.lpstrFile);
    MessageBoxA(NULL, ofn.lpstrFile, "", MB_OK);
}