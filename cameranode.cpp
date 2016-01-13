#include "cameranode.h"

CameraNode::CameraNode()
{

}

CameraNode::CameraNode(std::shared_ptr<Camera> camera) : _camera(camera)
{
}

CameraNode::~CameraNode()
{
}

void CameraNode::display(const glm::core::type::mat4& viewMatrix, const glm::core::type::mat4& projectionMatrix, const std::vector<std::shared_ptr<LightNode>>& lights)
{
    for (int i = 0; i < _childs.size(); i++)
    {
        _childs[i]->display(viewMatrix, projectionMatrix, lights);
    }
}

void  CameraNode::drawNode(const glm::mat4& viewMatrix, const glm::mat4& projectionMatrix, const std::vector<std::shared_ptr<LightNode>>& lights)
{
    //Nothing to draw
}

void CameraNode::animateScene()
{
    animate();
    for(int i = 0; i < _childs.size();i++)
    {
        _childs[i]->animateScene();
    }

}

glm::mat4 CameraNode::getView()
{
    return _camera->getView(glm::vec3(_transform.getXPos(), _transform.getYPos(), _transform.getZPos()));
}

