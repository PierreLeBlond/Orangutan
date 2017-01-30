#include "app/nanogui/maintool.h"

#include <iostream>

MainTool::MainTool(nanogui::Widget* parent, const std::string& label) :
    Tool(parent, label),
    _objectTool(std::make_unique<ObjectTool>(parent, "material"))
{
}

MainTool::~MainTool()
{
}

void MainTool::init()
{
    setFixedSize(Eigen::Vector2i(300, 600));
    setPosition(Eigen::Vector2i(0, 0));
    _objectTool->setAssetsStorage(_assetsStorage);
    _objectTool->setCurrentObject(_object);
    _objectTool->init();
}

void MainTool::setAssetsStorage(std::shared_ptr<AssetsStorage> assetsStorage){
    _assetsStorage = assetsStorage;
}

void MainTool::setCurrentObject(std::shared_ptr<RenderableObject> object)
{
    _object = object;
}

void MainTool::setNVGContext(NVGcontext *context)
{
    Tool::setNVGContext(context);
    _objectTool->setNVGContext(context);
}
