#pragma once

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

class LightNode;

class ObjectNode : public Transformable, public Asset {
 public:
  ObjectNode(const std::string& name);

  void set_object(std::shared_ptr<Object> object);
  void AddChild(std::shared_ptr<ObjectNode> node);
  void RemoveChild(std::shared_ptr<ObjectNode> node);
  void RemoveNode(std::shared_ptr<ObjectNode> node);

  void Draw(const glm::mat4& viewMatrix, const glm::mat4& projectionMatrix,
            const std::vector<std::shared_ptr<Light>>& lights) const;
  void DrawScene(const glm::mat4& viewMatrix, const glm::mat4& projectionMatrix,
                 const std::vector<std::shared_ptr<Light>>& lights) const;
  void UpdateScene(const glm::mat4& mat);
  void AnimateScene();

  [[nodiscard]] std::vector<std::shared_ptr<ObjectNode>> get_childs() const {
    return childs_;
  }

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
  std::shared_ptr<Object> object_;
  std::vector<std::shared_ptr<ObjectNode>> childs_;
  Transform transform_;
};
