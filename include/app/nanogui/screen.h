#include "app/screenable.h"
#include "app/nanogui/canvas.h"

#include <nanogui/screen.h>

class Screen : public Screenable, public nanogui::Screen
{
public:
                                                Screen(int width = 1000, int height = 750, std::string name = "Orangutan", bool b = false);
    virtual                                     ~Screen();

    virtual void                                init();

    virtual void                                drawContents();

    virtual bool                                keyboardEvent(int key, int scancode, int action, int modifiers);

    virtual void                                draw(NVGcontext *ctx);

private:

    Canvas*                                     _canvas;
};


