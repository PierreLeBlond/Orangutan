#ifndef CAMERANODE_H
#define CAMERANODE_H

#include "scenenode.h"
#include "camera.h"

#include <memory>


class CameraNode : public SceneNode
{
public:
                                    CameraNode();
                                    CameraNode(std::shared_ptr<Camera> camera);
                                    ~CameraNode();

    virtual void                    display(const glm::mat4& viewMatrix, const glm::mat4& projectionMatrix, const std::vector<std::shared_ptr<LightNode>>& lights);
    virtual void                    drawNode(const glm::mat4& viewMatrix, const glm::mat4& projectionMatrix, const std::vector<std::shared_ptr<LightNode>>& lights);
    virtual void                    animateScene();

    inline std::shared_ptr<Camera>  getCamera() const { return _camera; }
    inline void                     setCamera(std::shared_ptr<Camera> camera){ _camera = camera; }

    glm::mat4                       getView();

private:
    std::shared_ptr<Camera>         _camera;
};

#endif // CAMERANODE_H
