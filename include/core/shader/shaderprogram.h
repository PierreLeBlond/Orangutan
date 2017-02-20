#ifndef SHADER_PROGRAM_H
#define SHADER_PROGRAM_H

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtx/transform.hpp"
#include "glm/gtx/transform2.hpp"
#include "glm/gtc/type_ptr.hpp"

#include "core/shader/shader.h"
#include "core/shader/shaderprogramhandle.h"

#define MAX_LIGHT 8

class ShaderProgram
{
public:
                                                ShaderProgram();

    bool                                        build();
    bool                                        build(const std::string &vertexShaderPath,
                                                        const std::string &fragmentShaderPath,
                                                        const std::string &geometryShaderPath = "");

    bool                                        attach(unsigned int id);
    bool                                        link();
    bool                                        detach(unsigned int id);

    void                                        start() const;
    void                                        stop() const;

    unsigned int                                getId() const;

private:
    ShaderProgramHandle                         _handle;

    Shader                                      _vertexShader;
    Shader                                      _fragmentShader;
    Shader                                      _geometryShader;
};

#endif //SHADER_PROGRAM_H
