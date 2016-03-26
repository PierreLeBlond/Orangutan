#include "renderablenode.h"

RenderableNode::RenderableNode() {
}

RenderableNode::RenderableNode(std::shared_ptr<Renderer> renderable) {
    _renderables.push_back(renderable);
}

void RenderableNode::addRenderable(std::shared_ptr<Renderer> renderable) {
    _renderables.push_back(renderable);
}

void RenderableNode::display(const glm::core::type::mat4& viewMatrix, const glm::core::type::mat4& projectionMatrix, const std::vector<std::shared_ptr<LightNode>>& lights)
{
    for(unsigned int i = 0; i < _renderables.size();i++) {
        if(_renderables[i])
        {
            _renderables[i]->draw(_sceneMatrix, viewMatrix, projectionMatrix, lights);
        }
    }
    for (int i = 0; i < _childs.size(); i++)
    {
        _childs[i]->display(viewMatrix, projectionMatrix, lights);
    }
}

void RenderableNode::drawNode(const glm::core::type::mat4& viewMatrix, const glm::core::type::mat4& projectionMatrix, const std::vector<std::shared_ptr<LightNode> > &lights)
{
    for(unsigned int i = 0; i < _renderables.size();i++) {
        if(_renderables[i])
        {
            _renderables[i]->draw(_sceneMatrix, viewMatrix, projectionMatrix, lights);
        }
    }
}

void RenderableNode::animateScene()
{
    animate();
    for(unsigned int i = 0; i < _renderables.size();i++) {
        if(_renderables[i])
        {
            _renderables[i]->animate();
        }
    }
    for(int i = 0; i < _childs.size();i++)
    {
        _childs[i]->animateScene();
    }
}
