#ifndef PARSEUR_H
#define PARSEUR_H

#include <locale.h>

#include <memory>
#include <sstream>
#include <vector>

#include "object/material.h"
#include "object/mesh.h"

class Parseur {
 public:
  static std::vector<std::shared_ptr<Material> > parseMtl(
      const std::string& filename);
  static std::vector<std::shared_ptr<Mesh> > parseObj(
      const std::string& filename);
};

#endif  // PARSEUR_H
