#ifndef ASSETS_H
#define ASSETS_H

#include <vector>
#include <memory>

#include "core/texture/texture.h"
#include "object/mesh.h"
#include "shader/shaderstrategy.h"


class Assets
{
public:
    const Library<Mesh>&               getMeshLibrary() const;
    const Library<DDTexture>&          getTextureLibrary() const;
    const Library<CubeTexture>&        getCubeMapTextureLibrary() const;
    const Library<ShaderWrapper>&      getShaderWrapperLibrary() const;
    const Library<ShaderStrategy>&     getShaderStrategieLibrary() const;

    void                               addMesh(std::shared_ptr<Mesh> mesh);
    void                               addTexture(std::shared_ptr<DDTexture> texture);
    void                               addCubeMapTexture(std::shared_ptr<CubeTexture> cubeMapTexture);
    void                               addShaderWrapper(std::shared_ptr<ShaderWrapper> shaderWrapper);
    void                               addShaderStrategy(std::shared_ptr<ShaderStrategy> shaderStrategy);

private:
    Library<Mesh>                      _meshs;
    Library<DDTexture>                 _textures;
    Library<CubeTexture>               _cubeMapTextures;
    Library<ShaderWrapper>             _shaderWrappers;
    Library<ShaderStrategy>            _shaderStrategies;
};

#endif // ASSETS_H
