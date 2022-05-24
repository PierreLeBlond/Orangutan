#ifndef ORANGUTAN_CORE_SHADER_SHADER_PROGRAM_HANDLE_H
#define ORANGUTAN_CORE_SHADER_SHADER_PROGRAM_HANDLE_H

#define MAX_ATTACHED_SHADER 3

#include "core/handle.h"

namespace orangutan {

class ShaderProgramHandle : public Handle {
 public:
  ShaderProgramHandle();
  ShaderProgramHandle(const ShaderProgramHandle& handle);
  ShaderProgramHandle(ShaderProgramHandle&& handle) noexcept;

  ~ShaderProgramHandle() noexcept;

  ShaderProgramHandle& operator=(const ShaderProgramHandle& handle);
  ShaderProgramHandle& operator=(ShaderProgramHandle&& handle);
};

}  // namespace orangutan

#endif  // ORANGUTAN_CORE_SHADER_SHADER_PROGRAM_HANDLE_H

