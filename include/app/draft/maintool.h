#ifndef MAIN_TOOL_H
#define MAIN_TOOL_H

#include "app/nanogui/tool.h"

#include <nanogui/window.h>

#include <memory>

class MainTool : public Tool
{
public:
                                                MainTool(nanogui::Widget *parent = 0, const std::string& label = "Unknow window");
    virtual                                     ~MainTool();

    virtual void                                init();

    const std::map<std::string,
          std::shared_ptr<Tool>>&               getTools() const;

    void                                        addTool(const std::string &name, std::shared_ptr<Tool> tool);

private:

    std::map<std::string,
        std::shared_ptr<Tool>>                  _tools;
};

#endif // MAIN_TOOL_H
