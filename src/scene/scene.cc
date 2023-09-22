#include "scene/scene.h"

#include <memory>

#include "camera/freecamera.h"
#include "camera/trackballcamera.h"
#include "core/debug.h"
#include "model/universe.h"
#include "util/keyboard.h"

namespace orangutan {

Scene::Scene(const std::string& name)
    : Asset(name), scene_tree_(name), ibl_(nullptr), is_ready_(false) {}

void Scene::Update() {
  // TODO: Search for all lights within tree

  glm::mat4 mat(1.0);
  scene_tree_.UpdateRecursively(mat);
}

void Scene::Animate() { scene_tree_.AnimateRecursively(); }

void Scene::Draw(const glm::mat4& view, const glm::vec3 camera_position,
                 const glm::mat4& projection) {
  scene_tree_.DrawRecursively(view, camera_position, projection, lights_, *ibl_,
                              *brdf_);
}

void Scene::set_is_ready(bool isReady) { is_ready_ = isReady; }

bool Scene::get_is_ready() const { return is_ready_; }

ObjectNode& Scene::get_scene_tree() { return scene_tree_; }

void Scene::SetIbl(Ibl* ibl) { ibl_ = ibl; }

void Scene::SetBrdf(Texture* brdf) { brdf_ = brdf; }

}  // namespace orangutan
