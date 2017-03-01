#include "app/nanogui/maintool.h"

#include <iostream>

MainTool::MainTool(nanogui::Widget* parent, const std::string& label) :
    Tool(parent, label)
{
}

MainTool::~MainTool()
{
}

void MainTool::init()
{
    setFixedSize(Eigen::Vector2i(300, 600));
    setPosition(Eigen::Vector2i(0, 0));

    setLayout(new nanogui::GroupLayout());
}

const std::map<std::string, std::shared_ptr<Tool>>& MainTool::getTools() const
{
    return _tools;
}

void MainTool::addTool(const std::string& name, std::shared_ptr<Tool> tool)
{
    nanogui::Button *button = new nanogui::Button(this, name);
    _tools.insert(std::make_pair(name, tool));
    button->setCallback([&, name]{
                        for(auto &t : _tools)
                        {
                            t.second->setVisible(false);
                        }
                        _tools.at(name)->setVisible(true);
                        _screen->performLayout();
                        });
}


