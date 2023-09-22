#ifndef ORANGUTAN_SCENE_SCENE_FACTORY_H
#define ORANGUTAN_SCENE_SCENE_FACTORY_H

#include <memory>
#include <vector>

#include "assimp/Importer.hpp"
#include "assimp/scene.h"
#include "model/universe.h"

namespace orangutan {

class SceneFactory {
 public:
  static std::unique_ptr<ObjectNode> ImportSceneTree(Assimp::Importer& importer,
                                                     Universe& universe,
                                                     const std::string& name,
                                                     const std::string& url);

 private:
  static std::unique_ptr<ObjectNode> ExtractSceneTree(Universe& universe,
                                                      const aiScene& scene,
                                                      const aiNode& node);
  static void CleanAssimpScene(const aiScene* assimp_scene);
};

}  // namespace orangutan

#endif  // ORANGUTAN_OBJECT_SCENE_SCENE_FACTORY_H
