#include "object/object.h"

#include <iostream>

namespace orangutan {

Object::Object(const std::string& name) : Asset(name) {}

const Transform& Object::getTransform() const { return _transform; }

void Object::setTransform(const Transform& transform) {
  _transform = transform;
}

void Object::draw(const glm::mat4& viewMatrix, const glm::vec3& camera_position,
                  const glm::mat4& projectionMatrix,
                  const std::vector<Light*>& lights, const Ibl& ibl,
                  const Texture& brdf) {
  // By default, nothing to draw
}

void Object::SetParentMatrix(const glm::mat4& parent_matrix) {
  _transform.SetParentMatrix(parent_matrix);
}

void Object::set_model_matrix(const glm::mat4& model_matrix) {
  _transform.set_model_matrix(model_matrix);
}

void Object::SetXRotation(float angle) { _transform.SetXRotation(angle); }

void Object::SetYRotation(float angle) { _transform.SetYRotation(angle); }

void Object::SetZRotation(float angle) { _transform.SetZRotation(angle); }

void Object::SetXScale(float scale) { _transform.SetXScale(scale); }

void Object::SetYScale(float scale) { _transform.SetYScale(scale); }

void Object::SetZScale(float scale) { _transform.SetZScale(scale); }

void Object::SetXPos(float x) { _transform.SetXPos(x); }

void Object::SetYPos(float y) { _transform.SetYPos(y); }

void Object::SetZPos(float z) { _transform.SetZPos(z); }

void Object::set_position(const glm::vec3& position) {
  _transform.set_position(position);
}

void Object::Move(glm::vec3& direction) { _transform.Move(direction); }

void Object::Animate() { _transform.Animate(); }

void Object::Update() { _transform.Update(); }

}  // namespace orangutan
