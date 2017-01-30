#include "scene/renderer.h"
#include "core/debug.h"

#include <iostream>

void Renderer::draw(const Scene &scene)
{
    draw(scene.getSceneTree(), scene.getCurrentCamera(), scene.getLights());
}

void Renderer::draw(const std::shared_ptr<ObjectNode> &node, const std::shared_ptr<Camera> &camera, const std::vector<std::shared_ptr<Light>>& lights)
{
    //std::cout << "new draw" << std::endl;
    node->drawScene(camera->getView(), camera->getProjection(), lights);
}

