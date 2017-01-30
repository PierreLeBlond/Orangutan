#pragma once

#include "core/vao.h"

#include "object/object.h"
#include "object/mesh.h"
#include "object/shadermaterial.h"

#include "util/util.h"
#include <vector>

class RenderableObject : public Object, public ShaderMaterialable
{
public:
                                        RenderableObject();

    virtual                             ~RenderableObject();

    void                                initVertexArrayObject();

    void                                fillInVBO();

    virtual void                        draw(const glm::mat4& viewMatrix,
                                             const glm::mat4& projectionMatrix,
                                             const std::vector<std::shared_ptr<Light>> &lights);

    void                                setMesh(
                                            std::shared_ptr<const Mesh> mesh);

    const ShaderMaterial&               getShaderMaterial() const;
    void                                setShaderMaterial(const ShaderMaterial& shadermaterial);

    unsigned int                        getIdOfPositionArray()  const;
    unsigned int                        getIdOfIndexArray()     const;
    unsigned int                        getIdOfNormalArray()    const;
    unsigned int                        getIdOfTexCoordArray()  const;

    const Vao&                          getVao()                const;

    virtual std::shared_ptr<
                const ShaderStrategy>   getShaderStrategy() const;
    virtual void                        setShaderStrategy(
        std::shared_ptr<
        const ShaderStrategy> shaderStrategy);

    bool                                setTexture(const std::string& name,
                                                   std::shared_ptr<Texture> texture);

    template <class T>
    bool                    addUniform(Uniform<T> u)
    {
        return _shaderMaterial.addUniform(u);
    }

    template <class T>
    bool                    setUniform(const std::string& name,
                                               const T &value)
    {
        return _shaderMaterial.setUniform(name, value);
    }

    template <class T>
    bool                    getUniform(const std::string& name,
                                               T &value) const
    {
        return _shaderMaterial.getUniform(name, value);
    }

    void                    addMaterial(Material m);

private:
    std::shared_ptr<const Mesh>         _mesh;

    ShaderMaterial                      _shaderMaterial;

    unsigned int                        _idOfPositionArray;
    unsigned int                        _idOfIndexArray;
    unsigned int                        _idOfNormalArray;
    unsigned int                        _idOfTexCoordArray;

    Vao                                 _vao;
};
