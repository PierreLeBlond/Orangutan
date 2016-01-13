#include "lightnode.h"

LightNode::LightNode() {
}

LightNode::LightNode(std::shared_ptr<Light> light) : _light(light) {
}

void LightNode::setLight(std::shared_ptr<Light> light) {
    _light = light;
}

void LightNode::display(const glm::core::type::mat4& viewMatrix, const glm::core::type::mat4& projectionMatrix, const std::vector<std::shared_ptr<LightNode>>& lights) {
    for (int i = 0; i < _childs.size(); i++)
    {
        _childs[i]->display(viewMatrix, projectionMatrix, lights);
    }
}

void LightNode::drawNode(const glm::mat4& viewMatrix, const glm::mat4& projectionMatrix, const std::vector<std::shared_ptr<LightNode>> &lights)
{
    //Nothing to do here
}

void LightNode::animateScene() {
    animate();
    _light->animate();
    for(int i = 0; i < _childs.size();i++)
    {
        _childs[i]->animateScene();
    }
}

const Light &LightNode::getLight() const {
    return *_light;
}


