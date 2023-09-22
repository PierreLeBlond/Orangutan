#include "scene/objectnodefactory.h"

#include <memory>

namespace orangutan {

std::unique_ptr<ObjectNode> ObjectNodeFactory::ExtractObjectNode(
    const aiNode& assimp_node) {
  auto node = std::make_unique<ObjectNode>(assimp_node.mName.C_Str());
  auto assimp_matrix = assimp_node.mTransformation;
  // TODO: Extract all transformations
  node->set_position(
      glm::vec3(assimp_matrix.a4, assimp_matrix.b4, assimp_matrix.c4));
  return node;
}

}  // namespace orangutan
