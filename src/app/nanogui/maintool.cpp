#include "app/nanogui/maintool.h"

MainTool::MainTool(nanogui::Widget* parent, const std::string& label) :
    nanogui::Window(parent, label),
    _objectTool(parent, "Object")
{
}

MainTool::~MainTool()
{
}

void MainTool::init()
{
    setFixedSize(Eigen::Vector2i(300, 600));
    setPosition(Eigen::Vector2i(0, 0));
    _objectTool.init();
}

void MainTool::setAssetsStorage(std::shared_ptr<AssetsStorage> assetsStorage){
    _assetsStorage = assetsStorage;
    _objectTool.setAssetsStorage(assetsStorage);
}

void MainTool::setCurrentObject(std::shared_ptr<RenderableObject> object)
{
    _object = object;
    _objectTool.setCurrentObject(object);
}
