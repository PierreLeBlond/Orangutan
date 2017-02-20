#ifndef CUBETEXTURE_H
#define CUBETEXTURE_H

#include "core/texture/texture.h"

class CubeTexture : public Texture
{
public:
                                CubeTexture(const std::string &name = "CubeTexture X");
                                CubeTexture(const std::string &path,
                                            const std::string &name);

    virtual bool                load(const std::string &path);
};

#endif // CUBETEXTURE_H
