#include "DisplayImage.hpp"
#include "nullptr.hpp"
#include <stdexcept>
#include <ltiRGBPixel.h>
#include <ltiObject.h>
#include <ltiBMPFunctor.h>
#include <ltiViewer.h>

namespace app {
    class DisplayImageCleaner {
    public:
        explicit DisplayImageCleaner(lti::viewer &v)
            : v_(v) { }

        ~DisplayImageCleaner() {
            v_.hide();
        }

    private:
        DisplayImageCleaner(DisplayImageCleaner const &);
        DisplayImageCleaner &operator=(DisplayImageCleaner const &);

        lti::viewer &v_;
    };

    void displayImage(std::string const &imgStr) {
        if (imgStr.empty()) {
            throw std::invalid_argument("invalid image selected");
        }

        lti::loadBMP loader;
        lti::image img;

        lti::viewer view("Image Display");

        DisplayImageCleaner cleaner(view);

        loader.load(imgStr, img);

        view.show(img);
        MessageBox(APP_NULLPTR, TEXT("Click OK to close the application"),
                   TEXT("Exit prompt"), MB_OK);
    }
} // END of namespace app
