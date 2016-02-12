#pragma once

#include "texture.h"
#include "Shader/shaderstrategy.h"

#include "glm/glm.hpp"

#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtx/transform.hpp"
#include "glm/gtx/transform2.hpp"
#include "glm/gtc/type_ptr.hpp"

#include <vector>
#include <QImage>
#include <QColor>
#include <fstream>
#include <memory>

class ShaderStrategy;

class Materialable
{
public:

    virtual const ShaderStrategy*    getShaderStrategy() const                                              = 0;
    virtual std::shared_ptr<const Texture> getColorMap() const                                                    = 0;

    virtual GLuint                   getCubeMapId() const                                                   = 0;

    virtual QColor                   getColor() const                                                       = 0;
    virtual glm::vec3                getKd() const                                                          = 0;
    virtual glm::vec3                getKa() const                                                          = 0;
    virtual glm::vec3                getKs() const                                                          = 0;
    virtual GLfloat                  getTr() const                                                          = 0;
    virtual GLfloat                  getNs() const                                                          = 0;
    virtual GLfloat                  getRefractionRatio() const                                             = 0;
    virtual GLfloat                  getReflexionPercentage() const                                         = 0;

    virtual void                    setShaderStrategy(const ShaderStrategy* shaderStrategy)                 = 0;

    virtual void                    setMtl(glm::vec3 Kd, glm::vec3 Ks, glm::vec3 Ka, float Ns, float Tr)    = 0;

    virtual void                    setColorMap(std::shared_ptr<const Texture> texture)                           = 0;

    virtual void                    CreateCubeMap()                                                         = 0;

    virtual void                    setCubeMapId(GLuint id)                                                 = 0;

    virtual void                    setColor(QColor color)                                                  = 0;
    virtual void                    setKd(float Kd)                                                         = 0;
    virtual void                    setKa(float Ka)                                                         = 0;
    virtual void                    setKs(float Ks)                                                         = 0;
    virtual void                    setNs(float Ns)                                                         = 0;
    virtual void                    setRefractionRatio(float ratio)                                         = 0;
    virtual void                    setReflexionPercentage(float percentage)                                = 0;
};

class Material : public Materialable
{
public:
                                    Material(std::string name = "untitled");


    virtual const ShaderStrategy*   getShaderStrategy() const;

    inline std::string				getName()			const { return _name; }

    virtual std::shared_ptr<const Texture>getColorMap()	const;

    virtual GLuint                   getCubeMapId()      const;

    virtual QColor                   getColor() const;
    virtual glm::vec3                getKd() const;
    virtual glm::vec3                getKa() const;
    virtual glm::vec3                getKs() const;
    virtual GLfloat                  getTr() const;
    virtual GLfloat                  getNs() const;
    virtual GLfloat                  getRefractionRatio() const;
    virtual GLfloat                  getReflexionPercentage() const;

    virtual void                    setShaderStrategy(const ShaderStrategy* shaderStrategy);

    virtual void                    setMtl(glm::vec3 Kd, glm::vec3 Ks, glm::vec3 Ka, float Ns, float Tr);

    virtual void                    setColorMap(std::shared_ptr<const Texture> texture);

    virtual void                    CreateCubeMap();

    virtual void                    setCubeMapId(GLuint id);

    virtual void                    setColor(QColor color);
    virtual void                    setKd(float Kd);
    virtual void                    setKa(float Ka);
    virtual void                    setKs(float Ks);
    virtual void                    setNs(float Ns);
    virtual void                    setRefractionRatio(float ratio);
    virtual void                    setReflexionPercentage(float percentage);


private:
    std::string                     _name;

    std::shared_ptr<const Texture>  _colorMap;

    GLuint                          _cubeMapId;

    QColor                          _color;
    glm::vec3                       _Kd;
    glm::vec3                       _Ks;
    glm::vec3                       _Ka;
    GLuint                          _illum;
    GLfloat                         _Ns;
    GLfloat                         _Tr;

    GLfloat                         _refractionRatio;
    GLfloat                         _reflexionPercentage;

    const ShaderStrategy*           _shaderStrategy;
};

