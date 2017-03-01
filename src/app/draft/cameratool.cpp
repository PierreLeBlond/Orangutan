#include "app/nanogui/cameratool.h"

#include <iostream>

CameraTool::CameraTool(nanogui::Widget *parent, const std::string& label) :
    Tool(parent, label)
{
}

CameraTool::~CameraTool()
{
}

void CameraTool::setCamera(std::shared_ptr<Camera> camera)
{
    _camera = camera;
    initCamera();
}

void CameraTool::init()
{
    setFixedSize(Eigen::Vector2i(300, 600));
    setPosition(Eigen::Vector2i(900, 0));
    setLayout(new nanogui::GroupLayout());
}

void CameraTool::update()
{
    removeChildrenWidget(this);
    initCamera();
    _screen->performLayout();
}

void CameraTool::initCamera()
{
    addSlider(this,
               "FOV",
               75.0,
               0.0,
               100.0,
               [&](float res){
               _camera->setFovy(res);
               });

    addSlider(this,
               "Speed",
               2.0,
               1.0,
               3.0,
               [&](float res){
               _camera->setSpeed(res);
               });
}
