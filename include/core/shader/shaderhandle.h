#ifndef SHADER_HANDLE_H
#define SHADER_HANDLE_H

#include "core/handle.h"

#include <nanogui/opengl.h>

//TODO Put Opengl related stuff in implementation
enum class ShaderType {VERTEX = GL_VERTEX_SHADER,
    FRAGMENT = GL_FRAGMENT_SHADER,
    GEOMETRY = GL_GEOMETRY_SHADER};

class ShaderHandle : public Handle
{
  public:
                                    ShaderHandle(ShaderType type = ShaderType::VERTEX);

                                    ShaderHandle(const ShaderHandle& handle);
                                    ShaderHandle(ShaderHandle&& handle) noexcept;

                                    ~ShaderHandle() noexcept;

    ShaderHandle&                   operator=(const ShaderHandle& handle);
    ShaderHandle&                   operator=(ShaderHandle&& handle);

    ShaderType                      getType() const;

  private:
    ShaderType                      _type;
};

#endif //SHADER_HANDLE_H
