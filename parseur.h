#ifndef PARSEUR_H
#define PARSEUR_H

#include "material.h"
#include "mesh.h"

#include <vector>
#include <memory>
#include <sstream>
#include <locale.h>

class Parseur
{
public:
                                        Parseur();

    static std::vector<std::shared_ptr<Material> > parseMtl(const char* filename);
    static std::vector<std::shared_ptr<Mesh>>          parseObj(const char* filename);
};

#endif // PARSEUR_H
