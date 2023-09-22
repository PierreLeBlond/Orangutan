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

  void SetPositions(const std::vector<glm::vec3>& positions);
  void SetPositions(const std::vector<float>& positions);
  void SetNormals(const std::vector<glm::vec3>& normals);
  void SetNormals(const std::vector<float>& normals);
  void SetTangents(const std::vector<glm::vec3>& tangents);
  void SetTangents(const std::vector<float>& tangents);
  void SetUvs(const std::vector<glm::vec2>& uvs);
  void SetUvs(const std::vector<float>& uvs);
  void SetUvs2(const std::vector<glm::vec2>& uvs_2);
  void SetUvs2(const std::vector<float>& uvs_2);
  void SetFaces(const std::vector<unsigned int>& faces);

  [[nodiscard]] unsigned int GetNumberOfPositions() const;
  [[nodiscard]] unsigned int GetNumberOfNormals() const;
  [[nodiscard]] unsigned int GetNumberOfTangents() const;
  [[nodiscard]] unsigned int GetNumberOfUvs() const;
  [[nodiscard]] unsigned int GetNumberOfUvs2() const;
  [[nodiscard]] unsigned int GetNumberOfFaces() const;

  [[nodiscard]] const std::vector<float>& GetPositions() const;
  [[nodiscard]] const std::vector<float>& GetNormals() const;
  [[nodiscard]] const std::vector<float>& GetTangents() const;
  [[nodiscard]] const std::vector<float>& GetUvs() const;
  [[nodiscard]] const std::vector<float>& GetUvs2() const;
  [[nodiscard]] const std::vector<unsigned int>& GetFaces() const;

 private:
  std::vector<float> positions_;
  std::vector<float> normals_;
  std::vector<float> tangents_;
  std::vector<float> uvs_;
  std::vector<float> uvs_2_;
  std::vector<unsigned int> faces_;
};

}  // namespace orangutan

#endif  // ORANGUTAN_MESH_MESH_H
