#ifndef TRANSFORMABLE_H
#define TRANSFORMABLE_H

#include "util/util.h"

#include "glm/glm.hpp"

#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtx/transform.hpp"
#include "glm/gtx/transform2.hpp"
#include "glm/gtc/type_ptr.hpp"

class Transformable{
public:
    virtual                     ~Transformable(){}

    virtual void                setGlobalMatrix(const glm::mat4& sceneMatrix) = 0;
    virtual void                setModelMatrix(const glm::mat4& modelMatrix) = 0;

    virtual void                setXRotation(float angle) = 0;
    virtual void                setYRotation(float angle) = 0;
    virtual void                setZRotation(float angle) = 0;

    virtual void                setXScale(float scale) = 0;
    virtual void                setYScale(float scale) = 0;
    virtual void                setZScale(float scale) = 0;

    virtual void                setTranslationMatrix(const glm::vec3& vector) = 0;

    virtual void                setXPos(int x) = 0;
    virtual void                setXPos(float x) = 0;

    virtual void                setYPos(int y) = 0;
    virtual void                setYPos(float y) = 0;

    virtual void                setZPos(int z) = 0;
    virtual void                setZPos(float z) = 0;

    virtual void                move(int direction) = 0;
    virtual void                animate() = 0;
    virtual void                update() = 0;


    virtual void                setXRotationSpeed(float speed) = 0;
    virtual void                setYRotationSpeed(float speed) = 0;
    virtual void                setZRotationSpeed(float speed) = 0;

    virtual void                setXTranslationSpeed(float speed) = 0;
    virtual void                setYTranslationSpeed(float speed) = 0;
    virtual void                setZTranslationSpeed(float speed) = 0;

    virtual void                setXTranslationSmallAxe(int l) = 0;
    virtual void                setYTranslationSmallAxe(int l) = 0;
    virtual void                setZTranslationSmallAxe(int l) = 0;

    virtual void                setXTranslationBigAxe(int l) = 0;
    virtual void                setYTranslationBigAxe(int l) = 0;
    virtual void                setZTranslationBigAxe(int l) = 0;
};

class Transform : public Transformable
{
public:
                                Transform();

    const glm::mat4&            getGlobalMatrix() const;
    const glm::mat4&            getModelMatrix() const;

    inline float getXPos() const { return _xPos;}
    inline float getYPos() const { return _yPos;}
    inline float getZPos() const { return _zPos;}

    inline glm::vec3 getPos() const { return glm::vec3(_xPos, _yPos, _zPos);}

    inline float getXScale() const {return _xScale;}
    inline float getYScale() const {return _yScale;}
    inline float getZScale() const {return _zScale;}

    inline float getXAngle() const {return _xAngle;}
    inline float getYAngle() const {return _yAngle;}
    inline float getZAngle() const {return _zAngle;}

    const glm::vec4 getDirection() const;

    inline float getXRotationSpeed() const {return _xRotationSpeed;}
    inline float getYRotationSpeed() const {return _yRotationSpeed;}
    inline float getZRotationSpeed() const {return _zRotationSpeed;}

    inline float getXTranslationSpeed() const {return _xTranslationSpeed;}
    inline float getYTranslationSpeed() const {return _yTranslationSpeed;}
    inline float getZTranslationSpeed() const {return _zTranslationSpeed;}

    inline float getXTranslationSmallAxe() const {return _xTranslationSmallAxe;}
    inline float getYTranslationSmallAxe() const {return _yTranslationSmallAxe;}
    inline float getZTranslationSmallAxe() const {return _zTranslationSmallAxe;}

    inline float getXTranslationBigAxe() const {return _xTranslationBigAxe;}
    inline float getYTranslationBigAxe() const {return _yTranslationBigAxe;}
    inline float getZTranslationBigAxe() const {return _zTranslationBigAxe;}


    //inherit from transformable
    virtual void setGlobalMatrix(const glm::mat4& sceneMatrix);
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
    glm::mat4 _globalMatrix;
    glm::mat4 _modelMatrix;/**< La matrice de modele */
    glm::mat4 _translationMatrix;/**< Matrice de translation */
    glm::mat4 _xScaleMatrix;/**< Matrice de scalling selon x */
    glm::mat4 _yScaleMatrix;/**< Matrice de scalling selon y */
    glm::mat4 _zScaleMatrix;/**< Matrice de scalling selon z */
    glm::mat4 _xRotationMatrix;/**< Matrice de rotation selon x */
    glm::mat4 _yRotationMatrix;/**< Matrice de rotation selon y */
    glm::mat4 _zRotationMatrix;/**< Matrice de rotation selon z */

    float _xAngle;/**< L'angle de rotation selon x*/
    float _yAngle;/**< L'angle de rotation selon y*/
    float _zAngle;/**< L'angle de rotation selon z*/

    float _xScale;/**< Le scale selon x*/
    float _yScale;/**< Le scale selon y*/
    float _zScale;/**< Le scale selon z*/

    float _xPos;/**< La position en x*/
    float _yPos;/**< La position en y*/
    float _zPos;/**< La position en z*/

    float _xRotationSpeed;
    float _yRotationSpeed;
    float _zRotationSpeed;

    float _xTranslationSpeed;
    float _yTranslationSpeed;
    float _zTranslationSpeed;

    float _xTranslationSmallAxe;
    float _yTranslationSmallAxe;
    float _zTranslationSmallAxe;

    float _xTranslationBigAxe;
    float _yTranslationBigAxe;
    float _zTranslationBigAxe;
};

#endif // TRANSFORMABLE_H
