#include "app/nanogui/screen.h"
#include <iostream>

int main(int argc, char *argv[])
{
    try {
        nanogui::init();

        /* scoped variables */ {
            nanogui::ref<Screen> app = new Screen();
            app->init();
            app->drawAll();
            app->setVisible(true);
            nanogui::mainloop();
        }

        nanogui::shutdown();
    } catch (const std::runtime_error &e) {
        std::string error_msg = std::string("Caught a fatal error: ") + std::string(e.what());
#if defined(_WIN32)
        MessageBoxA(nullptr, error_msg.c_str(), NULL, MB_ICONERROR | MB_OK);
#else
        std::cerr << error_msg << std::endl;
#endif
        return -1;
    }

    return 0;
}
