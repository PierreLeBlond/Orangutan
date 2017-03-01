#ifndef SCENES_H
#define SCENES_H

#include <vector>
#include <memory>

#include "scene/scene.h"

class Scenes
{
public:
    const Library<Scene>&             getSceneLibrary() const;

    void                              addScene(std::shared_ptr<Scene> scene);

private:
    Library<Scene>                    _scenes;
};

#endif // SCENES_H
