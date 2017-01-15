#ifndef OBJECT_TOOL_H
#define OBJECT_TOOL_H

#include "app/objecttoolable.h"
#include "scene/assetsstorage.h"

#include <nanogui/window.h>

class ObjectTool : public ObjectToolable, public nanogui::Window
{
  public:
    ObjectTool(nanogui::Widget *parent = 0, const std::string& label = "Unknow window");
    virtual                                     ~ObjectTool();

    void                                        init();
};

#endif // OBJECT_TOOL_H
