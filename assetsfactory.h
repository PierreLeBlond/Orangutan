#ifndef ASSETSFACTORY_H
#define ASSETSFACTORY_H

#include "assetsstorage.h"
#include "parseur.h"
#include "util.h"
#include "Shader/gouraudstrategy.h"
#include "Shader/environmentstrategy.h"
#include "Shader/skyboxstrategy.h"
#include "Shader/toonstrategy.h"

#include <vector>
#include <QImage>


class AssetsFactory
{
public:
                                            AssetsFactory(std::shared_ptr<AssetsStorage> assetsStorage);
                                            ~AssetsFactory();

    int                                     importMeshs(const char* filename);
    int                                     importTexture(const char* filename);
    int                                     importShader(const char* vertexFilename, const char* fragmentFilename, const char* geometryFilename = "");
    int                                     createNewShaderStrategy(int type, int shaderId, const char* name);

private:
    std::shared_ptr<AssetsStorage>          _assetsStorage;

};

#endif // ASSETSFACTORY_H
