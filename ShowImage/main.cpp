#include <cstdlib>
#include <Windows.h>
#include <tchar.h>
#include "Common.hpp"
#include "WndProc.hpp"
#include "nullptr.hpp"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
                   LPSTR lpCmdLine, int nCmdShow) {
    APP_UNUSED(hPrevInstance);
    APP_UNUSED(lpCmdLine);

    int const width = 800;
    int const height = 600;

    TCHAR const szClassName[] = TEXT("windowClass");

    WNDCLASSEX wc;    
    wc.cbSize = sizeof(WNDCLASSEX);
    wc.style = CS_HREDRAW | CS_VREDRAW;
    wc.lpfnWndProc = &app::WndProc;
    wc.cbClsExtra = 0;
    wc.cbWndExtra = 0;
    wc.hInstance = hInstance;
    wc.hIcon = LoadIcon(APP_NULLPTR, IDI_APPLICATION);
    wc.hCursor = LoadCursor(APP_NULLPTR, IDC_ARROW);
    wc.hbrBackground = reinterpret_cast<HBRUSH>(COLOR_WINDOW + 1);
    wc.lpszMenuName = APP_NULLPTR;
    wc.lpszClassName = szClassName;
    wc.hIconSm = LoadIcon(APP_NULLPTR, IDI_APPLICATION);

    if (!RegisterClassEx(&wc)) {
        MessageBox(APP_NULLPTR, TEXT("Window Registration Failed!"),
                   TEXT("Error!"), MB_ICONEXCLAMATION | MB_OK);
        return EXIT_FAILURE;
    }

    HWND hwnd = CreateWindowEx(WS_EX_CLIENTEDGE, szClassName,
                               TEXT("Image Displayer"), WS_OVERLAPPEDWINDOW,
                               CW_USEDEFAULT, CW_USEDEFAULT,
                               width, height,
                               APP_NULLPTR, APP_NULLPTR, hInstance, APP_NULLPTR);

    if (hwnd == APP_NULLPTR) {
        MessageBox(APP_NULLPTR, TEXT("Window Creation Failed!"), TEXT("Error!"),
                   MB_ICONEXCLAMATION | MB_OK);
        return EXIT_FAILURE;
    }

    ShowWindow(hwnd, nCmdShow);
    UpdateWindow(hwnd);

    MSG Msg;
    while (GetMessage(&Msg, APP_NULLPTR, 0, 0) > 0) {
        TranslateMessage(&Msg);
        DispatchMessage(&Msg);
    }
    
    return static_cast<int>(Msg.wParam);
} // END of WinMain
