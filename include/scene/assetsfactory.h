#ifndef ASSETSFACTORY_H
#define ASSETSFACTORY_H

#include "scene/assetsstorage.h"

#include "util/parseur.h"
#include "util/util.h"

#include "shader/shaderstrategy.h"

#include "core/texture.h"

#include <vector>


class AssetsFactory
{
public:
                                            AssetsFactory(std::shared_ptr<AssetsStorage> assetsStorage);
                                            ~AssetsFactory();

    int                                     importMeshs(const char* filename, const char *name = "unknown");
    int                                     importTexture(const char* filename, const char* name = "unknown");
    int                                     importCubeMapTexture(const char*filename, const char *name = "unknown");
    int                                     importShader(const char* vertexFilename, const char* fragmentFilename, const char* geometryFilename = "");
    int                                     createNewShaderStrategy(int shaderId, const char* name);
    int                                     createNewScreenSpaceShaderStrategy(int type, int shaderId, const char* name);

private:
    std::shared_ptr<AssetsStorage>          _assetsStorage;

};

#endif // ASSETSFACTORY_H
