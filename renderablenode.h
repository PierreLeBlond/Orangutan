#pragma once

#include "scenenode.h"
#include "renderable.h"

#include <vector>
#include <memory>

class LightNode;

class RenderableNode : public SceneNode
{
public:
                                        RenderableNode();
                                        RenderableNode(std::shared_ptr<Renderer> renderable);

    void                                addRenderable(std::shared_ptr<Renderer> renderable);

    virtual void                        display(const glm::mat4& viewMatrix, const glm::mat4& projectionMatrix, const std::vector<std::shared_ptr<LightNode>>& lights);
    virtual void                        drawNode(const glm::mat4& viewMatrix, const glm::mat4& projectionMatrix, const std::vector<std::shared_ptr<LightNode>>& lights);
    virtual void                        animateScene();

    inline std::vector<std::shared_ptr<Renderer>>     getRenderables() const { return _renderables; }


private:
    std::vector<std::shared_ptr<Renderer>>           _renderables;
	
};

