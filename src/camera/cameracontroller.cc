#include "camera/cameracontroller.h"

#include <glm/gtc/constants.hpp>
#include <iostream>
#include <map>
#include <memory>
#include <utility>

#include "GLFW/glfw3.h"
#include "util/keyboard.h"

const std::map<int, glm::vec3> kTranslations = {
    {GLFW_KEY_W, glm::vec3(0.0f, 0.0f, -1.0f)},
    {GLFW_KEY_S, glm::vec3(0.0f, 0.0f, 1.0f)},
    {GLFW_KEY_A, glm::vec3(-1.0f, 0.0f, 0.0f)},
    {GLFW_KEY_D, glm::vec3(1.0f, 0.0f, 0.0f)},
    {GLFW_KEY_Q, glm::vec3(0.0f, 1.0f, 0.0f)},
    {GLFW_KEY_Z, glm::vec3(0.0f, -1.0f, 0.0f)}};

const std::map<int, float> kYawRotations = {{GLFW_KEY_LEFT, 1.0f},
                                            {GLFW_KEY_RIGHT, -1.0f}};
const std::map<int, float> kPitchRotations = {{GLFW_KEY_DOWN, -1.0f},
                                              {GLFW_KEY_UP, 1.0f}};

CameraController::CameraController(std::shared_ptr<Camera> camera)
    : camera_(std::move(camera)), width_(0), height_(0) {}

void CameraController::set_camera(std::shared_ptr<Camera> camera) {
  camera_ = camera;
}

void CameraController::Update(double delta_time) {
  auto translation_vector = glm::vec3(0.0f);

  // Accumulate directions from pressed touches
  for (auto pair : kTranslations) {
    if (Keyboard::instance().getState(pair.first) == kPressed) {
      translation_vector += pair.second;
    }
  }

  glm::vec3 scaled_translation = (float)delta_time * translation_vector;

  camera_->Move(scaled_translation);

  float yaw_angle = 0.0f;
  for (auto pair : kYawRotations) {
    if (Keyboard::instance().getState(pair.first) == kPressed) {
      yaw_angle += pair.second;
    }
  }
  camera_->Yaw((float)delta_time * glm::half_pi<float>() * yaw_angle);

  float pitch_angle = 0.0f;
  for (auto pair : kPitchRotations) {
    if (Keyboard::instance().getState(pair.first) == kPressed) {
      pitch_angle += pair.second;
    }
  }
  camera_->Pitch((float)delta_time * glm::half_pi<float>() * pitch_angle);
}

void CameraController::SetSize(unsigned int width, unsigned int height) {
  width_ = width;
  height_ = height;
  camera_->set_aspect_ratio((float)width / (float)height);
}
