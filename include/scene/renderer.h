#ifndef RENDERER_H
#define RENDERER_H

#include "scene/scene.h"

class Renderer
{
  public:

    void                                    draw(const Scene &scene);

    void                                    draw(const std::shared_ptr<ObjectNode> &node,
                                                 const std::shared_ptr<Camera> &camera,
                                                 const std::vector<std::shared_ptr<Light>> &lights);
};

#endif //RENDERER_H
