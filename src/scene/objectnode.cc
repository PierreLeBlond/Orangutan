
#include "scene/objectnode.h"

#include <iostream>

namespace orangutan {

ObjectNode::ObjectNode(const std::string& name)
    : Asset(name), object_(nullptr) {}

void ObjectNode::set_object(Object* object) { object_ = object; }

void ObjectNode::AddChild(ObjectNode* node) { childs_.push_back(node); }

void ObjectNode::Draw(const glm::mat4& viewMatrix,
                      const glm::vec3& camera_position,
                      const glm::mat4& projectionMatrix,
                      const std::vector<Light*>& lights, const Ibl& ibl,
                      const Texture& brdf) const {
  if (object_) {
    object_->draw(viewMatrix, camera_position, projectionMatrix, lights, ibl,
                  brdf);
  }
}

void ObjectNode::DrawRecursively(const glm::mat4& viewMatrix,
                                 const glm::vec3& camera_position,
                                 const glm::mat4& projectionMatrix,
                                 const std::vector<Light*>& lights,
                                 const Ibl& ibl, const Texture& brdf) const {
  Draw(viewMatrix, camera_position, projectionMatrix, lights, ibl, brdf);
  for (auto& _child : childs_) {
    _child->DrawRecursively(viewMatrix, camera_position, projectionMatrix,
                            lights, ibl, brdf);
  }
}

void ObjectNode::AnimateRecursively() {
  transform_.Animate();
  if (object_) object_->Animate();
  for (auto& child : childs_) {
    child->AnimateRecursively();
  }
}

void ObjectNode::UpdateRecursively(const glm::mat4& mat) {
  /*if(_object)
      _object->update();
  _transform.update();*/
  SetParentMatrix(mat);
  if (object_) object_->SetParentMatrix(mat * transform_.get_model_matrix());
  for (auto& child : childs_) {
    child->UpdateRecursively(mat * transform_.get_model_matrix());
  }
}

// inherit from Transformable
void ObjectNode::SetParentMatrix(const glm::mat4& parent_matrix) {
  transform_.SetParentMatrix(parent_matrix);
}

void ObjectNode::set_model_matrix(const glm::mat4& model_matrix) {
  transform_.set_model_matrix(model_matrix);
}

void ObjectNode::SetXRotation(float angle) { transform_.SetXRotation(angle); }

void ObjectNode::SetYRotation(float angle) { transform_.SetYRotation(angle); }

void ObjectNode::SetZRotation(float angle) { transform_.SetZRotation(angle); }

void ObjectNode::SetXScale(float scale) { transform_.SetXScale(scale); }

void ObjectNode::SetYScale(float scale) { transform_.SetYScale(scale); }

void ObjectNode::SetZScale(float scale) { transform_.SetZScale(scale); }

void ObjectNode::SetXPos(float x) { transform_.SetXPos(x); }

void ObjectNode::SetYPos(float y) { transform_.SetYPos(y); }

void ObjectNode::SetZPos(float z) { transform_.SetZPos(z); }

void ObjectNode::set_position(const glm::vec3& position) {
  transform_.set_position(position);
}

void ObjectNode::Move(glm::vec3& direction) { transform_.Move(direction); }

void ObjectNode::Animate() { transform_.Animate(); }

void ObjectNode::Update() { transform_.Update(); }

}  // namespace orangutan
