#ifndef APP_H
#define APP_H

#include "view/nanogui/screenview.h"

class App
{
public:

    void                                init();
    void                                initAssets();

private:

    nanogui::ref<ScreenView>            _screenView;
    std::shared_ptr<Assets>             _assets;

};

#endif //APP_H
