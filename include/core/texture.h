#ifndef TEXTURE_H
#define TEXTURE_H

#include <vector>

#include "object/asset.h"

enum Image_type {
    O_TEXTURE_2D = 0,
    O_TEXTURE_CUBE_MAP = 2
};

class Texture : public Asset
{
public:
                                Texture(std::string path, std::string name = "unknow");
                                Texture();

    unsigned int                getId() const;

    bool                        load(std::string path);

    void                        loadCubeMap(std::string path_prefix);

private:
    unsigned int                _id;
    std::string                 _path;
    int                         _type;
};

#endif // TEXTURE_H
