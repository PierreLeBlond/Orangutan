#ifndef ORANGUTAN_SCENE_OBJECT_NODE_FACTORY_H
#define ORANGUTAN_SCENE_OBJECT_NODE_FACTORY_H

#include <memory>

#include "assimp/scene.h"
#include "scene/objectnode.h"

namespace orangutan {

class ObjectNodeFactory {
 public:
  static std::unique_ptr<ObjectNode> ExtractObjectNode(
      const aiNode& assimp_node);
};

}  // namespace orangutan

#endif  // ORANGUTAN_OBJECT_SCENE_OBJECT_NODE_FACTORY_H
