#ifndef FILEEXISTS_HPP
#define FILEEXISTS_HPP
#include <Windows.h>

namespace app {
    BOOL WINAPI fileExists(LPCTSTR szPath);
} // END of namespace app

#endif // FILEEXISTS_HPP