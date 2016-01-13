#ifndef LIGHT_H
#define LIGHT_H

#include "transformable.h"
#include <QColor>

enum light_type {
    AMBIANT = 0, DIRECTION, PONCTUAL, SPOT
};


class Light : public Transformable
{
public:
                                    Light();
    virtual                         ~Light();

    const Transform&                getTransform() const;

    const QColor&                   getColor() const;
    const glm::vec3&                getLd() const;
    const glm::vec3&                getLa() const;
    const glm::vec3&                getLs() const;
    int                             getType() const;
    float                           getCutoffAngle() const;
    float                           getExponent() const;

    bool                            getState() const;

    void                            setColor(const QColor &color);
    void                            setLd(float Ld);
    void                            setLa(float La);
    void                            setLs(float Ls);
    void                            setType(int type);
    void                            setCutoffAngle(float angle);
    void                            setExponent(float exponent);
    void                            setState(bool state);

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

    QColor                          _color;
    glm::vec3                       _Ld;
    glm::vec3                       _La;
    glm::vec3                       _Ls;

    int                             _type;

    float                           _cutoffAngle;
    float                           _exponent;

    bool                            _state;
};

#endif // LIGHT_H
