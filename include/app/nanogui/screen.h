#include "app/screenable.h"
#include "app/nanogui/canvas.h"
#include "app/nanogui/maintool.h"

#include <nanogui/screen.h>

class Screen : public Screenable, public nanogui::Screen
{
public:
                                                Screen(int width = 1200, int height = 600, std::string name = "Orangutan", bool b = false);
    virtual                                     ~Screen();

    virtual void                                init();

    virtual bool                                keyboardEvent(int key, int scancode, int action, int modifiers);

    virtual void                                draw(NVGcontext *ctx);

private:

    Canvas*                                     _canvas;
    MainTool                                    _mainTool;
    int                                         _drawCall;
    int                                         _time;
};


