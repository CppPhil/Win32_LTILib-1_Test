#ifndef WNDPROC_HPP
#define WNDPROC_HPP

#include <Windows.h>

namespace app {
    LRESULT CALLBACK WndProc(HWND hwnd, UINT msg,
                             WPARAM wParam, LPARAM lParam);
} // END of namespace app

#endif // WNDPROC_HPP

