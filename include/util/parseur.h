#ifndef PARSEUR_H
#define PARSEUR_H

#include "object/material.h"
#include "object/mesh.h"

#include <vector>
#include <memory>
#include <sstream>
#include <locale.h>

class Parseur
{
public:
    static std::vector<std::shared_ptr<Material> >      parseMtl(const std::string& filename);
    static std::vector<std::shared_ptr<Mesh> >          parseObj(const std::string& filename);
};

#endif // PARSEUR_H
