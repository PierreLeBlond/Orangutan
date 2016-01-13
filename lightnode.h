#ifndef LIGHTNODE_H
#define LIGHTNODE_H

#include "scenenode.h"
#include "light.h"

#include <memory>

class LightNode : public SceneNode
{
public:
                                        LightNode();
                                        LightNode(std::shared_ptr<Light> light);
    void                                setLight(std::shared_ptr<Light> light);

    virtual void                        display(const glm::core::type::mat4& viewMatrix, const glm::core::type::mat4& projectionMatrix, const std::vector<std::shared_ptr<LightNode>>& lights);
    virtual void                        drawNode(const glm::mat4& viewMatrix, const glm::mat4& projectionMatrix, const std::vector<std::shared_ptr<LightNode>>& lights);
    virtual void                        animateScene();

    const Light&                        getLight() const;
private:
    std::shared_ptr<Light>              _light;
};

#endif // LIGHTNODE_H
