#ifndef SHADERSTRATEGY_H
#define SHADERSTRATEGY_H

#include "core/shaderprogram.h"
#include "core/vao.h"
#include "core/debug.h"

#include "object/material.h"
#include "object/light.h"

#include "glm/glm.hpp"

#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtx/transform.hpp"
#include "glm/gtx/transform2.hpp"
#include "glm/gtc/type_ptr.hpp"

#include <algorithm>

class Material;
class ShaderProgram;

class ShaderStrategy : public Asset
{
public:
                                        ShaderStrategy(const std::string& name = "unknown");
    virtual                             ~ShaderStrategy();

    template<class T>
    void                                setUniform(const Uniform<T>& uniform) const
    {
        std::vector<std::string> names = _shaderProgram->getUniformsName();
        auto it = std::find(names.begin(), names.end(), uniform.getName());
        if(it != names.end())
        {
            _shaderProgram->setUniform(uniform.getName(), uniform.getValue());
        }
    }

    void                                setUniforms(const Material &material,
                                                   const glm::mat4& modelMatrix,
                                                   const glm::mat4& viewMatrix,
                                                   const glm::mat4& projectionMatrix,
                                                   const std::vector<std::shared_ptr<Light>> &lights) const;

    void                                setLightUniforms(const std::vector<std::shared_ptr<Light>> &lights,
                                                        const glm::mat4& viewMatrix) const;
    void                                setMatrixUniforms(const glm::mat4& modelMatrix,
                                                         const glm::mat4& viewMatrix,
                                                         const glm::mat4& projectionMatrix) const;
    void                                setMaterialUniforms(const Material &material) const;

    void                                initAttribute();

    void                                draw(const Vao &vao) const;

    void                                setShaderProgram(std::shared_ptr<ShaderProgram> shaderProgram);
    const std::shared_ptr<
        ShaderProgram>&                 getShaderProgram() const;

    int                                 getVertexAttribute()            const { return _vertexAttribute; }
    int                                 getNormalAttribute()            const { return _normalAttribute; }
    int                                 getTextureCoordinateAttribute() const { return _textureCoordinateAttribute; }

protected:

    std::shared_ptr<ShaderProgram>      _shaderProgram;
    unsigned int                        _programId;

    int                                 _vertexAttribute;
    int                                 _normalAttribute;
    int                                 _textureCoordinateAttribute;
};


#endif // SHADERSTRATEGY_H
