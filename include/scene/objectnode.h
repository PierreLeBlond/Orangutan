#pragma once

#include "physics/transformable.h"

#include "object/object.h"
#include "object/light.h"

#include "glm/glm.hpp"

#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtx/transform.hpp"
#include "glm/gtx/transform2.hpp"
#include "glm/gtc/type_ptr.hpp"

#include <vector>
#include <list>
#include <memory>

class LightNode;

class ObjectNode : public Transformable
{
public:
                                             ObjectNode();

    void                                     setObject(std::shared_ptr<Object> object);
    void                                     addChild(std::shared_ptr<ObjectNode> node);
    void                                     removeChild(std::shared_ptr<ObjectNode> node);
    void                                     removeNode(std::shared_ptr<ObjectNode> node);

    void                                     draw(const glm::mat4& viewMatrix,
                                                const glm::mat4& projectionMatrix,
                                                const std::vector<std::shared_ptr<Light>>& lights);
    void                                     drawScene(const glm::mat4& viewMatrix,
                                                const glm::mat4& projectionMatrix,
                                                const std::vector<std::shared_ptr<Light>>& lights);
    void                                     updateScene(const glm::mat4& mat);
    void                                     animateScene();

    std::vector<std::shared_ptr<ObjectNode>> getChilds() const { return _childs;}

    const Transform&                         getTransform() const {return _transform;}

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
    /* Associated Object */
    std::shared_ptr<Object>                     _object;
    /* Array of child nodes */
    std::vector<std::shared_ptr<ObjectNode>>    _childs;
    /* Transform component */
    Transform                                   _transform;

};
