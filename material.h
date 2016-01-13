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

class ShaderStrategy;

class Materialable
{
public:
    virtual                         ~Materialable(){}

    virtual void                    setShaderStrategy(const ShaderStrategy* shaderStrategy) = 0;

    virtual void                    setMtl(glm::vec3 Kd, glm::vec3 Ks, glm::vec3 Ka, float Ns, float Tr) = 0;

    virtual void                    setDiffuseMapId(Texture* texture) = 0;

    virtual void                    CreateCubeMap() = 0;

    virtual void                    setCubeMapId(GLuint id) = 0;

    virtual void                    setColor(QColor color) = 0;
    virtual void                    setKd(float Kd) = 0;
    virtual void                    setKa(float Ka) = 0;
    virtual void                    setKs(float Ks) = 0;
    virtual void                    setNs(float Ns) = 0;
    virtual void                    setRefractionRatio(float ratio) = 0;
    virtual void                    setReflexionPercentage(float percentage) = 0;
};

class Material : public Materialable
{
public:
                                    Material(std::string name = "untitled");
                                    ~Material();


    const ShaderStrategy*           getShaderStrategy() const;


    void                            CreateAmbientMap(const char* filename);
    void                            CreateDiffuseMap(const char* filename);
    void                            CreateBumpMap(const char* filename);
    void                            CreateNormalMap(const char* filename);
    void                            CreateSpecularMap(const char* filename);
    void                            CreateShininessMap(const char* filename);



    inline std::string				getName()			const { return _name; }

    inline Texture*                 getAmbientMapId()	const { return _ambientMapId; }
    inline Texture*                 getDiffuseMapId()	const { return _diffuseMapId; }
    inline Texture*                 getBumpMapId()		const { return _bumpMapId; }
    inline Texture*                 getNormalMapId()	const { return _normalMapId; }
    inline Texture*                 getSpecularMapId()	const { return _specularMapId; }
    inline Texture*                 getShininessMapId()	const { return _shininessMapId; }

    inline GLuint                   getCubeMapId()      const { return _cubeMapId; }

    inline QColor                   getColor() const {return _color;}
    inline glm::vec3                getKd() const {return _Kd;}
    inline glm::vec3                getKa() const {return _Ka;}
    inline glm::vec3                getKs() const {return _Ks;}
    inline GLfloat                  getTr() const {return _Tr;}
    inline GLfloat                  getNs() const {return _Ns;}
    inline GLfloat                  getRefractionRatio() const {return _refractionRatio;}
    inline GLfloat                  getReflexionPercentage() const {return _reflexionPercentage;}

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


private:
    std::string                     _name;

    Texture*                        _diffuseMapId;
    Texture*                        _ambientMapId;
    Texture*                        _bumpMapId;
    Texture*                        _normalMapId;
    Texture*                        _specularMapId;
    Texture*                        _shininessMapId;

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

