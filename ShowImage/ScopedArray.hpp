#ifndef SCOPEDARRAY_HPP
#define SCOPEDARRAY_HPP

#include "nullptr.hpp"

#if defined(_MSC_VER)
#   if _MSC_FULL_VER >= 190023026
#       define APP_NOEXCEPT noexcept
#   else
#       define APP_NOEXCEPT throw()
#   endif
#elif defined(__clang__)
#   if __has_feature(cxx_noexcept)
#       define APP_NOEXCEPT noexcept
#   else
#       define APP_NOEXCEPT throw()
#   endif
#elif defined(__GNUC__)
#   if __GNUC__ * 10 + __GNUC_MINOR__ >= 46
#       define APP_NOEXCEPT noexcept
#   else
#       define APP_NOEXCEPT throw()
#   endif
#else
#   error "Unsupported compiler"
#endif

namespace app {
    template <typename Ty>
    class scoped_array {
    public:
        explicit scoped_array(Ty *p = APP_NULLPTR)
            : p_(p) {  }

        ~scoped_array() {
            delete[] p_;
        }

        Ty *get() const APP_NOEXCEPT {
            return p_;
        }
            
    private:
        Ty *p_;
    };
} // END of namespace app

#endif // SCOPEDARRAY_HPP
