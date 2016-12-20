#ifndef SHADERSTRATEGY_H
#define SHADERSTRATEGY_H

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

    virtual void                        setUniform(const Material &material,
                                                   const glm::mat4& modelMatrix,
                                                   const glm::mat4& viewMatrix,
                                                   const glm::mat4& projectionMatrix,
                                                   const std::vector<std::shared_ptr<Light>> &lights) const = 0;

    void                                setLightUniform(const std::vector<std::shared_ptr<Light>> &lights,
                                                        const glm::mat4& viewMatrix) const;
    void                                setMatrixUniform(const glm::mat4& modelMatrix,
                                                         const glm::mat4& viewMatrix,
                                                         const glm::mat4& projectionMatrix) const;
    void                                setMaterialUniform(const Material &material) const;

    virtual void                        initAttribute() = 0;

    void                                draw(const Vao &vao) const;

    void                                setShaderProgram(std::shared_ptr<ShaderProgram> shaderProgram);
    std::shared_ptr<ShaderProgram>      getShaderProgram() const;

    inline int                          getVertexAttribute()            const { return _vertexAttribute; }
    inline int                          getNormalAttribute()            const { return _normalAttribute; }
    inline int                          getTextureCoordinateAttribute() const { return _textureCoordinateAttribute; }

protected:
    std::shared_ptr<ShaderProgram>      _shaderProgram;
    unsigned int                        _programId;

    int                                 _vertexAttribute;
    int                                 _normalAttribute;
    int                                 _textureCoordinateAttribute;
};


#endif // SHADERSTRATEGY_H
