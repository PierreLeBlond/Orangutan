#ifndef SCREEN_VIEW_H
#define SCREEN_VIEW_H

#include <nanogui/screen.h>
#include <nanogui/opengl.h>

#include "util/keyboard.h"

class ScreenView : public nanogui::Screen
{
public:
                                                ScreenView(int width = 1200,
                                                           int height = 600,
                                                           const std::string& name = "Orangutan");

    virtual bool                                keyboardEvent(int key, int scancode, int action, int modifiers);
};

#endif //SCREEN_VIEW_H
