#ifndef ORANGUTAN_SCENE_SCENE_H
#define ORANGUTAN_SCENE_SCENE_H

#include <memory>

#include "object/asset.h"
#include "scene/objectnode.h"
#include "texture/ibl.h"

namespace orangutan {

class Universe;

class Scene : public Asset {
 public:
  Scene(const std::string& name);
  void SetSkybox(int index);

  void Build(const Universe& universe);
  void Update();
  void Animate();
  void Draw(const glm::mat4& view, const glm::vec3 camera_position,
            const glm::mat4& projection);

  void set_is_ready(bool isReady);
  [[nodiscard]] bool get_is_ready() const;

  [[nodiscard]] const ObjectNode& get_scene_tree() const;

  void SetIbl(Ibl* ibl);
  void SetBrdf(Texture* brdf);

 private:
  ObjectNode scene_tree_;
  std::vector<Light*> lights_;
  Ibl* ibl_;
  Texture* brdf_;
  bool is_ready_;
};

}  // namespace orangutan

#endif  // ORANGUTAN_SCENE_SCENE_H
