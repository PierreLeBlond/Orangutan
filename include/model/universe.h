#ifndef UNIVERSE_H
#define UNIVERSE_H

#include <vector>
#include <memory>

#include "model/objectlibrary.h"

#include "object/mesh.h"
#include "core/texture/ddtexture.h"
#include "core/texture/cubetexture.h"
#include "shader/shaderstrategy.h"
#include "scene/scene.h"

class Universe : public ObjectLibrary
{
  public:
    const Library<Mesh>&                getMeshLibrary() const;
    const Library<DDTexture>&           getTextureLibrary() const;
    const Library<CubeTexture>&         getCubeTextureLibrary() const;
    const Library<ShaderWrapper>&       getShaderWrapperLibrary() const;
    const Library<ShaderStrategy>&      getShaderStrategyLibrary() const;

    const Library<Scene>&               getSceneLibrary() const;

    void                                addMesh(std::shared_ptr<Mesh> item);
    void                                addTexture(std::shared_ptr<DDTexture> item);
    void                                addCubeTexture(std::shared_ptr<CubeTexture> item);
    void                                addShaderWrapper(std::shared_ptr<ShaderWrapper> item);
    void                                addShaderStrategy(std::shared_ptr<ShaderStrategy> item);

    void                                addScene(std::shared_ptr<Scene> item);

  private:

    Library<Mesh>                       _meshs;
    Library<DDTexture>                  _textures;
    Library<CubeTexture>                _cubeTextures;
    Library<ShaderWrapper>              _shaderWrappers;
    Library<ShaderStrategy>             _shaderStrategies;

    Library<Scene>                      _scenes;
};

#endif // UNIVERSE_H
