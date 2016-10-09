#ifndef NULLPTR_HPP
#define NULLPTR_HPP

namespace app {
    class nullptr_t {
    public:
        nullptr_t() : padding_(0) { }

        template <typename Ty>
        operator Ty *() const {
            return 0;
        }

        template <typename Class, typename Ty>
        operator Ty Class:: *() const {
            return 0;
        }

        operator void *() const {
            return 0;
        }

        friend bool operator==(nullptr_t const &, nullptr_t const &) {
            return true;
        }

        friend bool operator!=(nullptr_t const &, nullptr_t const &) {
            return false;
        }
    private:
        void *padding_;
    };
} // END of namespace app

#define APP_NULLPTR    ((app::nullptr_t()))

#endif // NULLPTR_HPP
