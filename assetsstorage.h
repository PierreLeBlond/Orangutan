#ifndef ASSETSSTORAGE_H
#define ASSETSSTORAGE_H

#include <vector>

#include "mesh.h"
#include "texture.h"
#include "shader/shaderstrategy.h"
#include "shader/edgefilterstrategy.h"


class AssetsStorage
{
public:
                                                            AssetsStorage();
                                                            ~AssetsStorage();

    const std::vector<std::shared_ptr<Mesh>>&               getMeshs() const;
    const std::vector<std::shared_ptr<Texture>>&            getTextures() const;
    const std::vector<std::shared_ptr<Texture>>&            getCubeMapTextures() const;
    const std::vector<const ShaderProgram*>&                getShaderPrograms() const;
    const std::vector<const ShaderStrategy*>&               getShaderStrategies() const;
    const std::vector<const ShaderStrategy*>&               getScreenSpaceShaderStrategies() const;

    int                                                     getNumberOfMeshs() const;
    int                                                     getNumberOfTextures() const;
    int                                                     getNumberOfCubeMapTextures() const;
    int                                                     getNumberOfShaderPrograms() const;
    int                                                     getNumberOfShaderStrategies() const;
    int                                                     getNumberOfScreenSpaceShaderStrategies() const;

    std::shared_ptr<Mesh>                                   getMesh(int index) const;
    std::shared_ptr< Texture>                               getTexture(int index) const;
    std::shared_ptr< Texture>                               getCubeMapTexture(int index) const;
    const ShaderProgram&                                    getShaderProgram(int index) const;
    const ShaderStrategy*                                   getShaderStrategy(int index) const;
    const ShaderStrategy*                                   getScreenSpaceShaderStrategy(int index) const;

    void                                                    addMesh(std::shared_ptr<Mesh> mesh);
    void                                                    addTexture(std::shared_ptr<Texture> texture);
    void                                                    addCubeMapTexture(std::shared_ptr<Texture> cubeMapTexture);
    void                                                    addShaderProgram(const ShaderProgram *shaderProgram);
    void                                                    addShaderStrategy(const ShaderStrategy *shaderStrategy);
    void                                                    addScreenSpaceShaderStrategy(const ShaderStrategy *shaderStrategy);

private:
    std::vector<std::shared_ptr<Mesh>>                      _meshs;
    std::vector<std::shared_ptr<Texture>>                   _textures;
    std::vector<std::shared_ptr<Texture>>                   _cubeMapTextures;
    std::vector<const ShaderProgram*>                       _shaderPrograms;
    std::vector<const ShaderStrategy*>                      _shaderStrategies;
    std::vector<const ShaderStrategy*>                      _screenSpaceShaderStrategies;
};

#endif // ASSETSSTORAGE_H
