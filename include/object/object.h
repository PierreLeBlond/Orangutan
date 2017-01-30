#ifndef OBJECT_H
#define OBJECT_H

#include "object/asset.h"
#include "physics/transformable.h"

#include <string>
#include <memory>
#include <vector>

class Light;

class Object : public Asset, public Transformable
{
public:
                                Object();
                                Object(const std::string &name);

    const Transform&            getTransform() const;
    void                        setTransform(const Transform& transform);

    virtual void                draw(const glm::mat4& viewMatrix,
                                        const glm::mat4& projectionMatrix,
                                        const std::vector<std::shared_ptr<Light>> &lights);

    //Inherit from transformable
    virtual void                setGlobalMatrix(const glm::mat4& sceneMatrix);
    virtual void                setModelMatrix(const glm::mat4& modelMatrix);

    virtual void                setXRotation(float angle);
    virtual void                setYRotation(float angle);
    virtual void                setZRotation(float angle);

    virtual void                setXScale(float scale);
    virtual void                setYScale(float scale);
    virtual void                setZScale(float scale);

    virtual void                setXPos(int x);
    virtual void                setXPos(float x);

    virtual void                setYPos(int y);
    virtual void                setYPos(float y);

    virtual void                setZPos(int z);
    virtual void                setZPos(float z);

    virtual void                setTranslationMatrix(const glm::vec3& vector);

    virtual void                move(int direction);
    virtual void                animate();
    virtual void                update();

    virtual void                setXRotationSpeed(float speed);
    virtual void                setYRotationSpeed(float speed);
    virtual void                setZRotationSpeed(float speed);

    virtual void                setXTranslationSpeed(float speed);
    virtual void                setYTranslationSpeed(float speed);
    virtual void                setZTranslationSpeed(float speed);

    virtual void                setXTranslationSmallAxe(int l);
    virtual void                setYTranslationSmallAxe(int l);
    virtual void                setZTranslationSmallAxe(int l);

    virtual void                setXTranslationBigAxe(int l);
    virtual void                setYTranslationBigAxe(int l);
    virtual void                setZTranslationBigAxe(int l);

private:
    Transform                   _transform;
};

#endif // OBJECT_H
