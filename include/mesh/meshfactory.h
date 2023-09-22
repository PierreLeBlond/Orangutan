#ifndef ORANGUTAN_MESH_MESH_FACTORY_H
#define ORANGUTAN_MESH_MESH_FACTORY_H

#include <memory>

#include "assimp/Importer.hpp"
#include "assimp/scene.h"
#include "mesh/mesh.h"

namespace orangutan {

class MeshFactory {
 public:
  static std::unique_ptr<Mesh> CreateSquare(const std::string& name);
  static std::unique_ptr<Mesh> CreateCube(const std::string& name,
                                          int resolution = 1);
  static std::unique_ptr<Mesh> ExtractMesh(const aiMesh& assimp_mesh);
};

}  // namespace orangutan

#endif  // ORANGUTAN_MESH_MESH_FACTORY_H
