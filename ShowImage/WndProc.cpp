#include "WndProc.hpp"
#include "ScopedArray.hpp"
#include "DisplayImage.hpp"
#include "FileExists.hpp"
#include <cstdlib>
#include <cstddef>
#include <string>
#include <stdexcept>
#include <algorithm>

namespace app {
    static std::string const fileExtension(".bmp");

    template <typename Range>
    inline bool endsWith(Range const &range, Range const &subRange) {
        if (range.size() < subRange.size()) {
            return false;
        }

        return std::equal(subRange.rbegin(), subRange.rend(), range.rbegin());
    }

    struct WindowProperties {
        HWND handle;
        DWORD style;
        int x;
        int y;
        int width;
        int height;
    };

    LRESULT CALLBACK WndProc(HWND hwnd, UINT msg,
                             WPARAM wParam, LPARAM lParam) {
        static int const idcMainButton = 101;
        static int const idcMainEdit = 102;
        static WindowProperties edit = { APP_NULLPTR,
            WS_CHILD | WS_VISIBLE | ES_MULTILINE | ES_AUTOVSCROLL | ES_AUTOHSCROLL,
            50, 100, 300, 100 };
        static WindowProperties button = { APP_NULLPTR,
            WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
            50, 220, 100, 24 };

        switch (msg) {
            case WM_CREATE : {
                edit.handle = CreateWindowEx(WS_EX_CLIENTEDGE, TEXT("EDIT"), TEXT(""),
                                                             edit.style, edit.x, edit.y, edit.width, edit.height,
                                                             hwnd, reinterpret_cast<HMENU>(idcMainEdit),
                                                             GetModuleHandle(APP_NULLPTR), APP_NULLPTR);

                HGDIOBJ hfDefault = GetStockObject(DEFAULT_GUI_FONT);
                HFONT hFont = CreateFont(24, 0, 0, 0, FW_DONTCARE, FALSE, FALSE, FALSE,
                                         DEFAULT_CHARSET, OUT_OUTLINE_PRECIS,
                                         CLIP_DEFAULT_PRECIS, CLEARTYPE_QUALITY, VARIABLE_PITCH, TEXT("Arial"));
                SendMessage(edit.handle, WM_SETFONT,
                            reinterpret_cast<WPARAM>(hFont), MAKELPARAM(FALSE, 0));
                SendMessage(edit.handle, WM_SETTEXT, 0,
                            reinterpret_cast<LPARAM>(TEXT("Enter image to load here...")));

                button.handle = CreateWindowEx(0, TEXT("BUTTON"), TEXT("Load image"),
                                                   button.style, button.x, button.y, button.width, button.height,
                                                   hwnd, reinterpret_cast<HMENU>(idcMainButton),
                                                   GetModuleHandle(APP_NULLPTR), APP_NULLPTR);
                SendMessage(button.handle, WM_SETFONT,
                            reinterpret_cast<WPARAM>(hfDefault),
                            MAKELPARAM(FALSE, 0));

            }
                break;
            case WM_COMMAND :
                switch (LOWORD(wParam)) {
                    case idcMainButton : {
                        std::string imgStr;
                        LRESULT bytes = SendMessage(edit.handle, // bytes does not include null terminator
                                                    WM_GETTEXTLENGTH, 0, 0);  
                        ++bytes;
                        scoped_array<TCHAR> buf(new TCHAR[bytes]());
                        SendMessage(edit.handle, WM_GETTEXT, bytes, // how many bytes including null terminator
                                    reinterpret_cast<LPARAM>(buf.get()));

                        if (!fileExists(buf.get())) {
                            imgStr = "";
                        } else {
#ifdef UNICODE
                            scoped_array<char> buf2(new char[bytes]());
                            std::size_t bytesWritten = // bytesWritten will not include the null terminator
                                std::wcstombs(buf2.get(),
                                              buf.get(),
                                              static_cast<std::size_t>(bytes));
                            if (bytesWritten != (static_cast<std::size_t>(bytes) - 1U)) {
                                MessageBox(APP_NULLPTR, TEXT("Failed to convert in std::wcstombs"),
                                           TEXT("Error"), MB_ICONERROR);
                                imgStr = "";
                            } else {
                                imgStr = buf2.get();
                            }

#else
                            imgStr = buf.get();
#endif
                        }
                    
                        if (!endsWith(imgStr, fileExtension)) {
                            imgStr = "";
                        }

                        try {
                            displayImage(imgStr); 
                        } catch (std::invalid_argument const &e) {
                            MessageBoxA(APP_NULLPTR, e.what(),
                                        "caught std::invalid_argument", MB_ICONERROR);
                        }
                        PostMessage(hwnd, WM_CLOSE, 0, 0); // exit
                    }
                        break;
                }
                break;
            case WM_CLOSE :
                DestroyWindow(hwnd);
                break;
            case WM_DESTROY :
                PostQuitMessage(EXIT_SUCCESS);
                break;
            default :
                return DefWindowProc(hwnd, msg,
                                     wParam, lParam);
        }
        return 0;
    } // END of WndProc
} // END of namespace app
