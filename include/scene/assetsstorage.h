#ifndef ASSETSSTORAGE_H
#define ASSETSSTORAGE_H

#include <vector>
#include <memory>

#include "core/texture.h"

#include "object/mesh.h"

#include "shader/shaderstrategy.h"


class AssetsStorage
{
public:
                                                            AssetsStorage();
                                                            ~AssetsStorage();

    const std::vector<std::shared_ptr<Mesh>>&               getMeshs() const;
    const std::vector<std::shared_ptr<Texture>>&            getTextures() const;
    const std::vector<std::shared_ptr<Texture>>&            getCubeMapTextures() const;
    const std::vector<std::shared_ptr<ShaderProgram>>&      getShaderPrograms() const;
    const std::vector<std::shared_ptr<const ShaderStrategy>>&  getShaderStrategies() const;
    const std::vector<std::shared_ptr<const ShaderStrategy>>&  getScreenSpaceShaderStrategies() const;

    int                                                     getNumberOfMeshs() const;
    int                                                     getNumberOfTextures() const;
    int                                                     getNumberOfCubeMapTextures() const;
    int                                                     getNumberOfShaderPrograms() const;
    int                                                     getNumberOfShaderStrategies() const;
    int                                                     getNumberOfScreenSpaceShaderStrategies() const;

    std::shared_ptr<Mesh>                                   getMesh(int index) const;
    std::shared_ptr<Texture>                                getTexture(int index) const;
    std::shared_ptr<Texture>                                getCubeMapTexture(int index) const;
    std::shared_ptr<ShaderProgram>                          getShaderProgram(int index) const;
    std::shared_ptr<const ShaderStrategy>                   getShaderStrategy(int index) const;
    std::shared_ptr<const ShaderStrategy>                   getScreenSpaceShaderStrategy(int index) const;

    void                                                    addMesh(std::shared_ptr<Mesh> mesh);
    void                                                    addTexture(std::shared_ptr<Texture> texture);
    void                                                    addCubeMapTexture(std::shared_ptr<Texture> cubeMapTexture);
    void                                                    addShaderProgram(std::shared_ptr<ShaderProgram> shaderProgram);
    void                                                    addShaderStrategy(std::shared_ptr<const ShaderStrategy> shaderStrategy);
    void                                                    addScreenSpaceShaderStrategy(std::shared_ptr<const ShaderStrategy> shaderStrategy);

private:
    std::vector<std::shared_ptr<Mesh>>                      _meshs;
    std::vector<std::shared_ptr<Texture>>                   _textures;
    std::vector<std::shared_ptr<Texture>>                   _cubeMapTextures;
    std::vector<std::shared_ptr<ShaderProgram>>             _shaderPrograms;
    std::vector<std::shared_ptr<const ShaderStrategy>>      _shaderStrategies;
    std::vector<std::shared_ptr<const ShaderStrategy>>      _screenSpaceShaderStrategies;
};

#endif // ASSETSSTORAGE_H
