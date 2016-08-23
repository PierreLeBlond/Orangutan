#ifndef SHADERSTRATEGY_H
#define SHADERSTRATEGY_H

#include "core/opengl.h"
#include "core/shaderprogram.h"
#include "core/vao.h"

#include "object/material.h"
#include "object/light.h"

#include "glm/glm.hpp"

#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtx/transform.hpp"
#include "glm/gtx/transform2.hpp"
#include "glm/gtc/type_ptr.hpp"

class Material;
class ShaderProgram;

class ShaderStrategy : public Asset
{
public:
                                        ShaderStrategy(const std::string& name = "unknown");
    virtual                             ~ShaderStrategy() = 0;

    virtual void                        setUniform(const Material &material, const glm::mat4& modelMatrix, const glm::mat4& viewMatrix, const glm::mat4& projectionMatrix, const std::vector<std::shared_ptr<Light>> &lights) const = 0;
    virtual void                        initAttribute() = 0;

    void                                draw(const Vao &vao) const;

    void                                setShaderProgram(std::shared_ptr<ShaderProgram> shaderProgram);
    std::shared_ptr<ShaderProgram>      getShaderProgram() const;

    inline GLuint                       getVertexAttribute()            const { return _vertexAttribute; }
    inline GLuint                       getNormalAttribute()            const { return _normalAttribute; }
    inline GLuint                       getTextureCoordinateAttribute() const { return _textureCoordinateAttribute; }

protected:
    std::shared_ptr<ShaderProgram>      _shaderProgram;
    GLuint                              _programId;

    GLuint                              _vertexAttribute;
    GLuint                              _normalAttribute;
    GLuint                              _textureCoordinateAttribute;
};


#endif // SHADERSTRATEGY_H
