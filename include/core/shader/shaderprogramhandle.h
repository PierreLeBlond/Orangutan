#ifndef SHADER_PROGRAM_HANDLE_H
#define SHADER_PROGRAM_HANDLE_H

#define MAX_ATTACHED_SHADER 3

#include "core/handle.h"

class ShaderProgramHandle : public Handle
{
public:
                                                ShaderProgramHandle();
                                                ShaderProgramHandle(const ShaderProgramHandle& handle);
                                                ShaderProgramHandle(ShaderProgramHandle&& handle) noexcept;

                                                ~ShaderProgramHandle() noexcept;

    ShaderProgramHandle&                        operator=(const ShaderProgramHandle& handle);
    ShaderProgramHandle&                        operator=(ShaderProgramHandle&& handle);
};

#endif //SHADER_PROGRAM_HANDLE_H

