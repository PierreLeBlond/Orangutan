#ifndef SCENE_H
#define SCENE_H

#include <memory>

#include "object/asset.h"
#include "scene/objectnode.h"

class Universe;

class Scene : public Asset {
 public:
  Scene(const std::string& name);
  void SetSkybox(int index);

  void Build(const Universe& universe);
  void Update();
  void Animate();

  void set_is_ready(bool isReady);
  [[nodiscard]] bool get_is_ready() const;

  [[nodiscard]] const std::shared_ptr<ObjectNode>& get_scene_tree() const;

 private:
  std::shared_ptr<ObjectNode> scene_tree_;
  bool is_ready_;
};

#endif  // SCENE_H
