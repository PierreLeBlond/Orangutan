#include "model/assetsfactory.h"

std::vector<std::shared_ptr<Mesh>> AssetsFactory::importMeshs(const std::string& filename,
                                                              const std::string& name)
{
    std::vector<std::shared_ptr<Mesh>> meshs = Parseur::parseObj(filename);

    for(unsigned int i = 0;i < meshs.size();++i) {
        meshs[i]->setName(name);
    }

    return meshs;
}

int AssetsFactory::importTexture(const std::string& filename,
                                 const std::string& name)
{
    std::shared_ptr<DDTexture> texture = std::make_shared<DDTexture>(filename, name);
    texture->setName(name);
    return texture;
}

int AssetsFactory::importCubeMapTexture(const std::string& filename,
                                        const std::string& name)
{
    std::shared_ptr<CubeTexture> texture = std::make_shared<CubeTexture>();
    texture->load(filename);
    texture->setName(name);
    return texture;
}

int AssetsFactory::importShader(const std::string& vertexFilename,
                                const std::string& fragmentFilename,
                                const std::string& geometryFilename)
{
    std::shared_ptr<ShaderWrapper> shaderWrapper = std::make_shared<ShaderWrapper>();
    shaderWrapper->build(vertexFilename, fragmentFilename, geometryFilename);
    return shaderWrapper;
}

int AssetsFactory::createShaderStrategy(std::shared_ptr<ShaderWrapper> shaderWrapper,
                                           const std::string& name)
{
    std::shared_ptr<ShaderStrategy> strategy;
    strategy = std::make_shared<ShaderStrategy>(name);
    strategy->setShaderWrapper(shaderWrapper);
    strategy->initAttribute();
    return strategy;
}

