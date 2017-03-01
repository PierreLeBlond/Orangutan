#ifndef SCENE_H
#define SCENE_H

#include "model/objectlibrary.h"

#include <memory>

class Universe;

class Scene : public Asset, public ObjectLibrary
{
  public:
                                            Scene(const std::string& name = "Scene X");
    void                                    setSkybox(int index);

    void                                    build(Universe& universe);
    void                                    update();
    void                                    animate();

    void                                    setIsReady(bool isReady);
    bool                                    isReady() const;

    const std::shared_ptr<ObjectNode>&      getSceneTree() const;

  private:

    std::shared_ptr<ObjectNode>                 _sceneTree;
    bool                                        _isReady;
};

#endif // SCENE_H
