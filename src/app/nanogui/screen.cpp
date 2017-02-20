#include "app/nanogui/screen.h"
#include "app/nanogui/maintool.h"
#include "app/nanogui/objecttool.h"
#include "app/nanogui/cameratool.h"
#include "core/debug.h"

#include <nanogui/window.h>
#include <nanogui/layout.h>

#include <chrono>

Screen::Screen(int width, int height, std::string name, bool b) :
    nanogui::Screen(Eigen::Vector2i(width, height), name, b),
    _mainTool(this, "Main"),
    _drawCall(0),
    _time(std::chrono::system_clock::now().time_since_epoch().count())
{
    nanogui::Window *window = new nanogui::Window(this, "Canvas");
    window->setPosition(Eigen::Vector2i(300, 0));
    window->setFixedSize(Eigen::Vector2i(600, 600));
    window->setLayout(new nanogui::GroupLayout());

    _canvas = new Canvas(glfwWindow(), window);
    _canvas->resize(600, 600);
}

Screen::~Screen()
{
    delete _canvas;
}

void Screen::init()
{
    Screenable::init();

    _canvas->setScene(_scene);

    std::function<void()> drawCall = [&](){
        if(_scene->isReady())
        {
            _scene->animate();
            _scene->update();
            _renderer->draw(*_scene);
        }
    };

    _canvas->setDrawCall(drawCall);

    _canvas->setAssetsStorage(_assetsStorage);

    _mainTool.setNVGContext(nvgContext());
    _mainTool.setScreen(this);
    _mainTool.setAssetsStorage(_assetsStorage);

    _mainTool.init();

    new nanogui::Label(this, "Camera");

    std::shared_ptr<CameraTool> cameraTool = std::make_shared<CameraTool>(this, "Camera");
    cameraTool->setNVGContext(nvgContext());
    cameraTool->setScreen(this);
    cameraTool->setVisible(false);
    cameraTool->setCamera(_scene->getCurrentCamera());
    cameraTool->init();

    _mainTool.addTool("Camera Tool", cameraTool);

    std::vector<std::string> cameraNames;

    for(const auto& camera : _scene->getCameras())
        cameraNames.push_back(camera->getName());

    _mainTool.addComboBox(&_mainTool, nanogui::Popup::Right,
                          "Cameras", cameraNames, 0,
                          [&, cameraTool](int id){
                          _scene->setCurrentCamera(_scene->getCameras().at(id));
                          cameraTool->setCamera(_scene->getCurrentCamera());
                          _scene->getCurrentCamera()->setFocus(_scene->getCurrentRenderableObject());
                          cameraTool->update();
                          });

    new nanogui::Label(this, "Object");

    std::shared_ptr<ObjectTool> objectTool = std::make_shared<ObjectTool>(this, "Object");
    objectTool->setNVGContext(nvgContext());
    objectTool->setScreen(this);
    objectTool->setVisible(false);
    objectTool->setCurrentObject(_scene->getCurrentRenderableObject());
    objectTool->setAssetsStorage(_assetsStorage);

    objectTool->init();

    _mainTool.addTool("Object Tool", objectTool);

    std::vector<std::string> renderableObjectNames;

    for(const auto& renderableObject : _scene->getRenderableObjects())
        renderableObjectNames.push_back(renderableObject->getName());

    _mainTool.addComboBox(&_mainTool, nanogui::Popup::Right,
                          "Objects", renderableObjectNames, 0,
                          [&, objectTool, cameraTool](int id){
                          _scene->setCurrentRenderableObject(_scene->getRenderableObjects().at(id));
                          objectTool->setCurrentObject(_scene->getCurrentRenderableObject());
                          _scene->getCurrentCamera()->setFocus(_scene->getCurrentRenderableObject());
                          _scene->getCurrentCamera()->focus();
                          objectTool->update();
                          });

        performLayout();
}

bool Screen::keyboardEvent(int key, int scancode, int action, int modifiers)
{
    if (nanogui::Screen::keyboardEvent(key, scancode, action, modifiers))
        return true;
    if(action == GLFW_PRESS)
    {
        switch(key)
        {
          case GLFW_KEY_ESCAPE:
            setVisible(false);
            return true;
            break;
          default:
            break;
        }
    }
    _canvas->keyboardEvent(key, scancode, action, modifiers);
    return false;
}

void Screen::draw(NVGcontext *ctx)
{
    _drawCall++;
    nanogui::Screen::draw(ctx);
    int time = std::chrono::system_clock::now().time_since_epoch().count();
    if(time - _time > 1000000000)
    {
        _time = time;
        std::cout << _drawCall << std::endl;
        _drawCall = 0;
    }

}
