#ifndef OBJECT_TOOL_H
#define OBJECT_TOOL_H

#include "app/objecttoolable.h"
#include "app/nanogui/tool.h"
#include "scene/assetsstorage.h"

#include <nanogui/window.h>

class ObjectTool : public ObjectToolable, public Tool
{
  public:
                                                ObjectTool(nanogui::Widget *parent = 0, const std::string& label = "Unknow window");
    virtual                                     ~ObjectTool();

    void                                        removeChildrenWidget(nanogui::Widget *widget);

    void                                        init();
    void                                        initShader(nanogui::Widget *widget);
    void                                        initMaterials(nanogui::Widget *widget,
                                                              const Material &material,
                                                              const std::vector<std::string> &names);
    void                                        updateMaterials();

  private:
    nanogui::Widget*                            _uniformPanel;
};

#endif // OBJECT_TOOL_H
