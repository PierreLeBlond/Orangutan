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
    const std::vector<std::shared_ptr<Mesh>>&               getMeshs() const;
    const std::vector<std::shared_ptr<DDTexture>>&          getTextures() const;
    const std::vector<std::shared_ptr<CubeTexture>>&        getCubeMapTextures() const;
    const std::vector<std::shared_ptr<ShaderWrapper>>&      getShaderWrappers() const;
    const std::vector<
        std::shared_ptr<const ShaderStrategy>>&             getShaderStrategies() const;
    const std::vector<
        std::shared_ptr<const ShaderStrategy>>&             getScreenSpaceShaderStrategies() const;

    int                                                     getNumberOfMeshs() const;
    int                                                     getNumberOfTextures() const;
    int                                                     getNumberOfCubeMapTextures() const;
    int                                                     getNumberOfShaderWrappers() const;
    int                                                     getNumberOfShaderStrategies() const;
    int                                                     getNumberOfScreenSpaceShaderStrategies() const;

    std::shared_ptr<Mesh>                                   getMesh(int index) const;
    std::shared_ptr<DDTexture>                              getTexture(int index) const;
    std::shared_ptr<CubeTexture>                            getCubeMapTexture(int index) const;
    std::shared_ptr<ShaderWrapper>                          getShaderWrapper(int index) const;
    std::shared_ptr<const ShaderStrategy>                   getShaderStrategy(int index) const;
    std::shared_ptr<const ShaderStrategy>                   getScreenSpaceShaderStrategy(int index) const;

    void                        addMesh(std::shared_ptr<Mesh> mesh);
    void                        addTexture(std::shared_ptr<DDTexture> texture);
    void                        addCubeMapTexture(std::shared_ptr<CubeTexture> cubeMapTexture);
    void                        addShaderWrapper(std::shared_ptr<ShaderWrapper> shaderWrapper);
    void                        addShaderStrategy(std::shared_ptr<const ShaderStrategy> shaderStrategy);
    void                        addScreenSpaceShaderStrategy(std::shared_ptr<const ShaderStrategy> shaderStrategy);

private:
    std::vector<std::shared_ptr<Mesh>>                      _meshs;
    std::vector<std::shared_ptr<DDTexture>>                 _textures;
    std::vector<std::shared_ptr<CubeTexture>>               _cubeMapTextures;
    std::vector<std::shared_ptr<ShaderWrapper>>             _shaderWrappers;
    std::vector<std::shared_ptr<const ShaderStrategy>>      _shaderStrategies;
    std::vector<std::shared_ptr<const ShaderStrategy>>      _screenSpaceShaderStrategies;
};

#endif // ASSETS_H
