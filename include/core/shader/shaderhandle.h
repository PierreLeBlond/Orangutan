#ifndef ORANGUTAN_CORE_SHADER_SHADER_HANDLE_H
#define ORANGUTAN_CORE_SHADER_SHADER_HANDLE_H

#include <nanogui/opengl.h>

#include "core/handle.h"

namespace orangutan {

// TODO Put Opengl related stuff in implementation
enum class ShaderType {
  VERTEX = GL_VERTEX_SHADER,
  FRAGMENT = GL_FRAGMENT_SHADER,
  GEOMETRY = GL_GEOMETRY_SHADER
};

class ShaderHandle : public Handle {
 public:
  ShaderHandle(ShaderType type = ShaderType::VERTEX);

  ShaderHandle(const ShaderHandle& handle);
  ShaderHandle(ShaderHandle&& handle) noexcept;

  ~ShaderHandle() noexcept;

  ShaderHandle& operator=(const ShaderHandle& handle);
  ShaderHandle& operator=(ShaderHandle&& handle);

  [[nodiscard]] ShaderType getType() const;

 private:
  ShaderType _type;
};

}  // namespace orangutan

#endif  // ORANGUTAN_CORE_SHADER_SHADER_HANDLE_H
