#include "scene/renderer.h"
#include "core/debug.h"

#include <iostream>

void Renderer::draw(const Scene &scene)
{
    draw(scene.getSceneTree(), scene.getCameraLibrary().getCurrentItem(), scene.getLightLibrary().getItems());
}

void Renderer::draw(const std::shared_ptr<ObjectNode> &node, const std::shared_ptr<Camera> &camera, const std::vector<std::shared_ptr<Light>>& lights)
{
    node->drawScene(camera->getView(), camera->getProjection(), lights);
}

