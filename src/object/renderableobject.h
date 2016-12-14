#pragma once

#include "core/opengl.h"
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

    GLuint                              getIdOfPositionArray()  const;
    GLuint                              getIdOfIndexArray()     const;
    GLuint                              getIdOfNormalArray()    const;
    GLuint                              getIdOfTexCoordArray()  const;

    const Vao&                          getVao()                const;

    //inherit from Materialable
    virtual std::shared_ptr<
                const ShaderStrategy>   getShaderStrategy() const;
    virtual GLuint                      getColorMapId() const;
    virtual GLuint                      getCubeMapId() const;
    virtual GLuint                      getRenderMapId() const;

    virtual QColor                      getColor() const;
    virtual glm::vec3                   getKd() const;
    virtual glm::vec3                   getKa() const;
    virtual glm::vec3                   getKs() const;
    virtual GLfloat                     getTr() const;
    virtual GLfloat                     getNs() const;
    virtual GLfloat                     getRefractionRatio() const;
    virtual GLfloat                     getReflexionPercentage() const;
    virtual GLfloat                     getEdgeFilterThreshold() const;

    virtual void                        setShaderStrategy(
                                            std::shared_ptr<const ShaderStrategy> shaderStrategy);

    virtual void                        setMtl(glm::vec3 Kd, glm::vec3 Ks,
                                            glm::vec3 Ka, float Ns, float Tr);

    virtual void                        setColorMapId(GLuint id);
    virtual void                        setCubeMapId(GLuint id);
    virtual void                        setRenderMapId(GLuint id);

    virtual void                        setColor(QColor color);
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

    GLuint                              _idOfPositionArray;
    GLuint                              _idOfIndexArray;
    GLuint                              _idOfNormalArray;
    GLuint                              _idOfTexCoordArray;

    Vao                                 _vao;
};
