#ifndef CAMERA_TOOL_H
#define CAMERA_TOOL_H

#include <app/nanogui/tool.h>
#include <camera/camera.h>

class CameraTool : public Tool
{
  public:
                                                CameraTool(nanogui::Widget *parent = 0,
                                                     const std::string& label = "Unknow window");
    virtual                                     ~CameraTool();

    void                                        setCamera(std::shared_ptr<Camera> camera);

    virtual void                                init();
    virtual void                                update();

    void                                        initCamera();

  private:
    std::shared_ptr<Camera>                     _camera;
};

#endif // CAMERA_TOOL_H
