#pragma once

#include "core/vao.h"

#include "object/object.h"
#include "object/mesh.h"
#include "object/material.h"

#include "util/util.h"

#include <vector>

class RenderableObject : public Object, public Materialable
{
public:
                                        RenderableObject();

    virtual                             ~RenderableObject();

    void                                createVertexArrayObject();

    void                                fillInVBO();

    virtual void                        draw(const glm::mat4&	viewMatrix,
                                              const glm::mat4& projectionMatrix,
                                               const std::vector<std::shared_ptr<Light>> &lights);

    void                                setMesh(
                                            std::shared_ptr<const Mesh> mesh);

    const Material&                     getMaterial() const;
    void                                setMaterial(const Material& material);

    unsigned int                        getIdOfPositionArray()  const;
    unsigned int                        getIdOfIndexArray()     const;
    unsigned int                        getIdOfNormalArray()    const;
    unsigned int                        getIdOfTexCoordArray()  const;

    const Vao&                          getVao()                const;

    //inherit from Materialable
    virtual std::shared_ptr<
                const ShaderStrategy>   getShaderStrategy() const;
    virtual unsigned int                getColorMapId() const;
    virtual unsigned int                getCubeMapId() const;
    virtual unsigned int                getRenderMapId() const;

    virtual glm::vec4                   getColor() const;
    virtual glm::vec3                   getKd() const;
    virtual glm::vec3                   getKa() const;
    virtual glm::vec3                   getKs() const;
    virtual float                       getTr() const;
    virtual float                       getNs() const;
    virtual float                       getRefractionRatio() const;
    virtual float                       getReflexionPercentage() const;
    virtual float                       getEdgeFilterThreshold() const;

    virtual void                        setShaderStrategy(
                                            std::shared_ptr<const ShaderStrategy> shaderStrategy);

    virtual void                        setMtl(glm::vec3 Kd, glm::vec3 Ks,
                                            glm::vec3 Ka, float Ns, float Tr);

    virtual void                        setColorMapId(unsigned int id);
    virtual void                        setCubeMapId(unsigned int id);
    virtual void                        setRenderMapId(unsigned int id);

    virtual void                        setColor(glm::vec4 color);
    virtual void                        setKd(float Kd);
    virtual void                        setKa(float Ka);
    virtual void                        setKs(float Ks);
    virtual void                        setNs(float Ns);
    virtual void                        setRefractionRatio(float ratio);
    virtual void                        setReflexionPercentage(float percentage);
    virtual void                        setEdgeFilterThreshold(float threshold);

private:
    std::shared_ptr<const Mesh>         _mesh;

    Material                            _material;

    unsigned int                        _idOfPositionArray;
    unsigned int                        _idOfIndexArray;
    unsigned int                        _idOfNormalArray;
    unsigned int                        _idOfTexCoordArray;

    Vao                                 _vao;
};
