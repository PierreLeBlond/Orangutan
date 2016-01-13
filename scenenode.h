#pragma once

#include "transformable.h"

#include "glm/glm.hpp"

#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtx/transform.hpp"
#include "glm/gtx/transform2.hpp"
#include "glm/gtc/type_ptr.hpp"

#include <vector>
#include <list>
#include <memory>

class LightNode;

class SceneNode : public Transformable
{
public:
                                                    SceneNode();
	
    void                                            addChild(std::shared_ptr<SceneNode> node);
    void                                            removeChild(std::shared_ptr<SceneNode> node);
    void                                            removeNode(std::shared_ptr<SceneNode> node);

    virtual void                                    display(const glm::mat4& viewMatrix, const glm::mat4& projectionMatrix, const std::vector<std::shared_ptr<LightNode>>& lights) = 0;
    virtual void                                    drawNode(const glm::mat4& viewMatrix, const glm::mat4& projectionMatrix, const std::vector<std::shared_ptr<LightNode>>& lights) = 0;
    void                                            updateScene(glm::mat4 mat);
    virtual void                                    animateScene() = 0;

    glm::mat4                                       getSceneMatrix() const;
    void                                            setSceneMatrix(glm::mat4 mat);

    inline std::vector<std::shared_ptr<SceneNode>>  getChilds() const { return _childs; }

    inline const Transform&                         getTransform(){return _transform;}

    //Inherit from transformable
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



protected:
    std::vector<std::shared_ptr<SceneNode>>     _childs;

    Transform                                   _transform;

    glm::mat4                                   _sceneMatrix;
};

