#ifndef LIGHT_H
#define LIGHT_H

#include "object/object.h"

enum light_type {
    AMBIANT = 0, DIRECTION, PONCTUAL, SPOT
};

class Light : public Object
{
public:
                                    Light();
    virtual                         ~Light();

    const glm::vec4&                getColor() const;
    const glm::vec3&                getLd() const;
    const glm::vec3&                getLa() const;
    const glm::vec3&                getLs() const;
    int                             getType() const;
    float                           getCutoffAngle() const;
    float                           getExponent() const;

    bool                            getState() const;

    void                            setColor(const glm::vec4 &color);
    void                            setLd(float Ld);
    void                            setLa(float La);
    void                            setLs(float Ls);
    void                            setType(int type);
    void                            setCutoffAngle(float angle);
    void                            setExponent(float exponent);
    void                            setState(bool state);

private:
    glm::vec4                       _color;
    glm::vec3                       _Ld;
    glm::vec3                       _La;
    glm::vec3                       _Ls;

    int                             _type;

    float                           _cutoffAngle;
    float                           _exponent;

    bool                            _state;
};

#endif // LIGHT_H
