#ifndef ASSETSFACTORY_H
#define ASSETSFACTORY_H

#include "util/parseur.h"
#include "util/util.h"

#include "shader/shaderstrategy.h"
#include "core/texture/texture.h"

#include <vector>
#include <memory>

class AssetsFactory
{
public:

                                            AssetsFactory(const AssetsFactory&) = delete;
                                            AssetsFactory(AssetsFactory&&) = delete;


    AssetsFactory&                          operator=(const AssetsFactory&) = delete;
    AssetsFactory&                          operator=(AssetsFactory&&) = delete;

    static AssetsFactory&                   instance();

    std::vector<std::shared_ptr<Mesh>>      importMeshs(const std::string& filename,
                                                        const std::string& name = "Mesh X");
    std::shared_ptr<DDTexture>              importTexture(const std::string& filename,
                                                          const std::string& name = "2DTexture X");
    std::shared_ptr<CubeTexture>            importCubeMapTexture(const std::string& filename,
                                                                 const std::string& name = "CubeTexture X");
    std::shared_ptr<ShaderWrapper>          importShader(const std::string& vertexFilename,
                                                         const std::string& fragmentFilename,
                                                         const std::string& geometryFilename = "");

    std::shared_ptr<ShaderStrategy>         createShaderStrategy(std::shared_ptr<ShaderWrapper> shaderWrapper,
                                                                 const std::string& name);

private:
                                            AssetsFactory(){};
                                            ~AssetsFactory(){};

    static AssetsFactory                    _instance;

};

#endif // ASSETSFACTORY_H
