#ifndef PARSEUR_H
#define PARSEUR_H

#include "material.h"
#include "mesh.h"

#include <vector>

class Parseur
{
public:
                                        Parseur();

    static std::vector<Material*>       parseMtl(const char* filename);
    static std::vector<Mesh*>          parseObj(const char* filename);
};

#endif // PARSEUR_H
