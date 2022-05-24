#ifndef ORANGUTAN_SCENE_OBJECT_NODE_H
#define ORANGUTAN_SCENE_OBJECT_NODE_H

#include <list>
#include <memory>
#include <vector>

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "glm/gtx/transform.hpp"
#include "glm/gtx/transform2.hpp"
#include "object/light.h"
#include "object/object.h"
#include "physics/transformable.h"
#include "texture/ibl.h"

namespace orangutan {

class LightNode;

class ObjectNode : public Transformable, public Asset {
 public:
  ObjectNode(const std::string& name);

  void set_object(Object* object);
  void AddChild(ObjectNode* node);

  void Draw(const glm::mat4& viewMatrix, const glm::vec3& camera_position,
            const glm::mat4& projectionMatrix,
            const std::vector<Light*>& lights, const Ibl& ibl,
            const Texture& brdf) const;
  void DrawRecursively(const glm::mat4& viewMatrix,
                       const glm::vec3& camera_position,
                       const glm::mat4& projectionMatrix,
                       const std::vector<Light*>& lights, const Ibl& ibl,
                       const Texture& brdf) const;
  void UpdateRecursively(const glm::mat4& mat);
  void AnimateRecursively();

  [[nodiscard]] std::vector<ObjectNode*> get_childs() const { return childs_; }

  [[nodiscard]] const Transform& get_transform() const { return transform_; }

  // Inherit from transformable
  void SetParentMatrix(const glm::mat4& parent_matrix) override;
  void set_model_matrix(const glm::mat4& model_matrix) override;

  void SetXRotation(float angle) override;
  void SetYRotation(float angle) override;
  void SetZRotation(float angle) override;

  void SetXScale(float scale) override;
  void SetYScale(float scale) override;
  void SetZScale(float scale) override;

  void SetXPos(float x) override;
  void SetYPos(float y) override;
  void SetZPos(float z) override;

  void set_position(const glm::vec3& position) override;

  void Move(glm::vec3& direction) override;
  void Animate() override;
  void Update() override;

 private:
  Object* object_;
  std::vector<ObjectNode*> childs_;
  Transform transform_;
};

}  // namespace orangutan

#endif  // ORANGUTAN_SCENE_OBJECT_NODE_H
