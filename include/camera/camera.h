#ifndef CAMERA_H
#define CAMERA_H

#include "scene/objectnode.h"
#include "util/util.h"

class Camera : public ObjectNode {
 public:
  Camera(const std::string& name);

  [[nodiscard]] const glm::mat4& get_view_matrix() const;
  void set_view_matrix(const glm::mat4& view_matrix);

  [[nodiscard]] const glm::mat4& get_projection_matrix() const;
  void set_projection_matrix(const glm::mat4& projection_matrix);

  [[nodiscard]] const glm::vec3& get_focus_point() const;
  void set_focus_point(const glm::vec3& focus_point);
  void set_focus_object(std::shared_ptr<Object> focus_object);
  void UpdateFocus();

  [[nodiscard]] const float get_fovy() const;
  void set_fovy(float fovy);

  [[nodiscard]] const float get_aspect_ratio() const;
  void set_aspect_ratio(float aspect_ratio);

  [[nodiscard]] const float get_speed() const;
  void set_speed(float speed);

  void UpdateYawPitchRoll();

  [[nodiscard]] const glm::vec3& get_pitch() const;
  void Pitch(float pitchAngle);
  [[nodiscard]] const glm::vec3& get_yaw() const;
  void Yaw(float yawAngle);
  [[nodiscard]] const glm::vec3& get_roll() const;
  void Roll(float rollAngle);

  void Update() override = 0;
  void Move(glm::vec3& direction) override = 0;

  void Focus();

 private:
  float fovy_;
  float aspect_ratio_;

  glm::mat4 view_matrix_;
  glm::mat4 projection_matrix_;

  glm::vec3 focus_point_;
  std::shared_ptr<Object> focus_object_;

  float yaw_angle_;
  float pitch_angle_;
  float roll_angle_;

  glm::vec3 yaw_;
  glm::vec3 pitch_;
  glm::vec3 roll_;

  float speed_;
};

#endif  // CAMERA_H
