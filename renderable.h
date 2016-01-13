#pragma once

#include "opengl.h"
#include "mesh.h"
#include "material.h"
#include "Shader/shaderstrategy.h"
#include "transformable.h"
#include "lightnode.h"
#include "util.h"

#include <vector>

class Renderable : public Materialable, public Transformable
{
public:

                                    Renderable();

    virtual                         ~Renderable();

    void                            createVertexArrayObject();

    void                            fillInVBO();

    void                            draw(const glm::core::type::mat4& modelMatrix, const glm::mat4&	viewMatrix, const glm::mat4& projectionMatrix, const std::vector<std::shared_ptr<LightNode>> &lights);

    void                            setMesh(const Mesh* mesh);

    inline void                     setMaterial(const Material& material) { _material = material;}

    inline const Transform&         getTransform() const {return _transform;}

    inline const Material&          getMaterial() const {return _material;}

    inline GLuint                   getIdOfPositionArray()  const { return _idOfPositionArray; }
    inline GLuint                   getIdOfIndexArray()     const { return _idOfIndexArray; }
    inline GLuint                   getIdOfNormalArray()    const { return _idOfNormalArray; }
    inline GLuint                   getIdOfTexCoordArray()  const { return _idOfTexCoordArray; }

    inline GLuint                   getVao()                const { return _vao; }

    //inherit from Materialable
    virtual void                    setShaderStrategy(const ShaderStrategy* shaderStrategy);

    virtual void                    setMtl(glm::vec3 Kd, glm::vec3 Ks, glm::vec3 Ka, float Ns, float Tr);

    virtual void                    setDiffuseMapId(Texture* texture);

    virtual void                    CreateCubeMap();

    virtual void                    setCubeMapId(GLuint id);

    virtual void                    setColor(QColor color);
    virtual void                    setKd(float Kd);
    virtual void                    setKa(float Ka);
    virtual void                    setKs(float Ks);
    virtual void                    setNs(float Ns);
    virtual void                    setRefractionRatio(float ratio);
    virtual void                    setReflexionPercentage(float percentage);

    //inherit from Transformable
    virtual void setModelMatrix(const glm::mat4& modelMatrix);

    virtual void setXRotation(float angle);
    virtual void setYRotation(float angle);
    virtual void setZRotation(float angle);

    virtual void setXScale(float scale);
    virtual void setYScale(float scale);
    virtual void setZScale(float scale);

    virtual void setXPos(int x);
    virtual void setXPos(float x);

    virtual void setYPos(int y);
    virtual void setYPos(float y);

    virtual void setZPos(int z);
    virtual void setZPos(float z);

    virtual void setTranslationMatrix(const glm::vec3& vector);

    virtual void move(int direction);
    virtual void animate();
    virtual void update();


    virtual void setXRotationSpeed(float speed);
    virtual void setYRotationSpeed(float speed);
    virtual void setZRotationSpeed(float speed);

    virtual void setXTranslationSpeed(float speed);
    virtual void setYTranslationSpeed(float speed);
    virtual void setZTranslationSpeed(float speed);

    virtual void setXTranslationSmallAxe(int l);
    virtual void setYTranslationSmallAxe(int l);
    virtual void setZTranslationSmallAxe(int l);

    virtual void setXTranslationBigAxe(int l);
    virtual void setYTranslationBigAxe(int l);
    virtual void setZTranslationBigAxe(int l);

private:
    Transform                       _transform;

    const Mesh*                     _mesh;

    Material                        _material;

    int                             _shaderProgramMode;

    GLuint                          _idOfPositionArray;
    GLuint                          _idOfIndexArray;
    GLuint                          _idOfNormalArray;
    GLuint                          _idOfTexCoordArray;

    GLuint                          _vao;


};

