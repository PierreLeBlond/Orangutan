#include "object/light.h"

namespace orangutan {

Light::Light(const std::string& name)
    : Object(name),
      color_(glm::vec3(1.0f, 1.0f, 1.0f)),
      intensity_(1),
      falloff_radius_(100) {}

const glm::vec3& Light::get_color() const { return color_; }

const float Light::get_intensity() const { return intensity_; }

const float Light::get_falloff_radius() const { return falloff_radius_; }

void Light::set_color(const glm::vec3& color) { color_ = color; }

void Light::set_intensity(float intensity) { intensity_ = intensity; }

void Light::set_falloff_radius(float falloff_radius) {
  falloff_radius_ = falloff_radius;
}

}  // namespace orangutan
