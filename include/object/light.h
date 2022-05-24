#ifndef ORANGUTAN_OBJECT_LIGHT_H
#define ORANGUTAN_OBJECT_LIGHT_H

#include "object/object.h"

namespace orangutan {

enum light_type { AMBIANT = 0, DIRECTION, PONCTUAL, SPOT };

class Light : public Object {
 public:
  Light(const std::string& name);

  [[nodiscard]] const glm::vec3& get_color() const;
  [[nodiscard]] const float get_intensity() const;
  [[nodiscard]] const float get_falloff_radius() const;

  void set_color(const glm::vec3& color);
  void set_intensity(float intensity);
  void set_falloff_radius(float falloff_radius);

 private:
  glm::vec3 color_;
  float intensity_;
  float falloff_radius_;
};

}  // namespace orangutan

#endif  // ORANGUTAN_OBJECT_LIGHT_H
