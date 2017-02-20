#ifndef OBJECT_TOOL_H
#define OBJECT_TOOL_H

#include "app/nanogui/tool.h"
#include "scene/assetsstorage.h"
#include "object/renderableobject.h"

#include <nanogui/window.h>

class ObjectTool : public Tool
{
  public:
                                                ObjectTool(nanogui::Widget *parent = 0, const std::string& label = "Unknow window");
    virtual                                     ~ObjectTool();

    virtual void                                init();
    virtual void                                update();

    void                                        setCurrentObject(std::shared_ptr<RenderableObject> object);

    void                                        initShader(nanogui::Widget *widget);
    void                                        initMaterials(nanogui::Widget *widget,
                                                              const Material &material,
                                                              const std::vector<std::string> &names);

  private:
    std::shared_ptr<RenderableObject>           _object;
};

#endif // OBJECT_TOOL_H
