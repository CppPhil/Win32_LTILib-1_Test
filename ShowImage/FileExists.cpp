#include "FileExists.hpp"

namespace app {
    BOOL WINAPI fileExists(LPCTSTR szPath) {
        DWORD dwAttrib = GetFileAttributes(szPath);
        return (dwAttrib != INVALID_FILE_ATTRIBUTES &&
               !(dwAttrib & FILE_ATTRIBUTE_DIRECTORY));
    }
} // END of namespace app
