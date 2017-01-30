#ifndef MAIN_TOOL_H
#define MAIN_TOOL_H

#include "app/maintoolable.h"
#include "app/nanogui/objecttool.h"
#include "app/nanogui/tool.h"

#include <nanogui/window.h>

#include <memory>

class MainTool : public MainToolable, public Tool
{
public:
                                                MainTool(nanogui::Widget *parent = 0, const std::string& label = "Unknow window");
    virtual                                     ~MainTool();

    void                                        init();

    void                                        setCurrentObject(std::shared_ptr<RenderableObject> object);
    void                                        setAssetsStorage(std::shared_ptr<AssetsStorage> assetsStorage);
    void                                        setNVGContext(NVGcontext *context);

private:

    std::unique_ptr<ObjectTool>                 _objectTool;
};

#endif // MAIN_TOOL_H
