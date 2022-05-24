#ifndef ORANGUTAN_MESH_MESH_H
#define ORANGUTAN_MESH_MESH_H

#include <fstream>
#include <memory>
#include <vector>

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "glm/gtx/transform.hpp"
#include "glm/gtx/transform2.hpp"
#include "object/asset.h"

namespace orangutan {

class Mesh : public Asset {
 public:
  Mesh(const std::string& name);

  void setPositions(const std::vector<glm::vec3>& positions);
  void setPositions(const std::vector<float>& positions);
  void setNormals(const std::vector<glm::vec3>& normals);
  void setNormals(const std::vector<float>& normals);
  void setUvs(const std::vector<glm::vec2>& uvs);
  void setUvs(const std::vector<float>& uvs);
  void setFaces(const std::vector<unsigned int>& faces);

  [[nodiscard]] unsigned int getNumberOfPositions() const;
  [[nodiscard]] unsigned int getNumberOfNormals() const;
  [[nodiscard]] unsigned int getNumberOfUvs() const;
  [[nodiscard]] unsigned int getNumberOfFaces() const;

  [[nodiscard]] const std::vector<float>& getPositions() const;
  [[nodiscard]] const std::vector<float>& getNormals() const;
  [[nodiscard]] const std::vector<float>& getUvs() const;
  [[nodiscard]] const std::vector<unsigned int>& getFaces() const;

 private:
  std::vector<float> _positions;
  std::vector<float> _normals;
  std::vector<float> _uvs;
  std::vector<unsigned int> _faces;
};

}  // namespace orangutan

#endif  // ORANGUTAN_MESH_MESH_H
