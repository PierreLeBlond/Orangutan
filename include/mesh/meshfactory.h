#ifndef ORANGUTAN_MESH_MESH_FACTORY_H
#define ORANGUTAN_MESH_MESH_FACTORY_H

#include <memory>

#include "mesh/mesh.h"

namespace orangutan {

class MeshFactory {
 public:
  static std::unique_ptr<Mesh> CreateSquare(const std::string& name);
  static std::unique_ptr<Mesh> CreateCube(const std::string& name,
                                          int resolution = 1);
};

}  // namespace orangutan

#endif  // ORANGUTAN_MESH_MESH_FACTORY_H
