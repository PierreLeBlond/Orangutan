#ifndef OBJECT_H
#define OBJECT_H

#include <memory>
#include <string>
#include <vector>

#include "object/asset.h"
#include "physics/transformable.h"

class Light;

class Object : public Asset, public Transformable {
 public:
  Object(const std::string& name = "Object X");

  [[nodiscard]] const Transform& getTransform() const;
  void setTransform(const Transform& transform);

  virtual void draw(const glm::mat4& viewMatrix,
                    const glm::mat4& projectionMatrix,
                    const std::vector<std::shared_ptr<Light>>& lights);

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

  void Move(glm::vec3& position) override;
  void Animate() override;
  void Update() override;

 private:
  Transform _transform;
};

#endif  // OBJECT_H
