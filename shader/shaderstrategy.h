#ifndef SHADERSTRATEGY_H
#define SHADERSTRATEGY_H

#include "shaderprogram.h"
#include "../material.h"
#include "../mesh.h"
#include "../lightnode.h"

#include "../opengl.h"

#include "glm/glm.hpp"

#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtx/transform.hpp"
#include "glm/gtx/transform2.hpp"
#include "glm/gtc/type_ptr.hpp"

class Material;
class ShaderProgram;

class ShaderStrategy
{
public:
                                        ShaderStrategy();
    virtual                             ~ShaderStrategy() = 0;

    virtual void                        draw(GLuint vao, GLuint idOfIndexArray, const Mesh &mesh, const Material &material, const glm::mat4& modelMatrix, const glm::mat4& viewMatrix, const glm::mat4& projectionMatrix, const std::vector<std::shared_ptr<LightNode>> &lights) const = 0;
    virtual void                        initAttribute() = 0;
    virtual void                        initUniformLocation() = 0;

    void                                setShaderProgram(const ShaderProgram* shaderProgram);

    void                                setName(std::string name);
    std::string                         getName() const;

    inline GLuint                       getVertexAttribute()            const { return _vertexAttribute; }
    inline GLuint                       getNormalAttribute()            const { return _normalAttribute; }
    inline GLuint                       getTextureCoordinateAttribute() const { return _textureCoordinateAttribute; }

protected:
    const ShaderProgram*                _shaderProgram;
    GLuint                              _programId;

    GLuint                              _vertexAttribute;
    GLuint                              _normalAttribute;
    GLuint                              _textureCoordinateAttribute;

    std::string                         _name;
};


#endif // SHADERSTRATEGY_H
