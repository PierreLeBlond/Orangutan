#include "mesh/mesh.h"

#include <iostream>

namespace orangutan {

Mesh::Mesh(const std::string& name) : Asset(name) {}

void Mesh::SetPositions(const std::vector<glm::vec3>& positions) {
  positions_.clear();
  for (const auto& triple : positions) {
    positions_.push_back(triple.x);
    positions_.push_back(triple.y);
    positions_.push_back(triple.z);
  }
}

void Mesh::SetPositions(const std::vector<float>& positions) {
  positions_ = positions;
}

void Mesh::SetNormals(const std::vector<glm::vec3>& normals) {
  normals_.clear();
  for (const auto& triple : normals) {
    normals_.push_back(triple.x);
    normals_.push_back(triple.y);
    normals_.push_back(triple.z);
  }
}

void Mesh::SetNormals(const std::vector<float>& normals) { normals_ = normals; }

void Mesh::SetTangents(const std::vector<glm::vec3>& tangents) {
  tangents_.clear();
  for (const auto& triple : tangents) {
    tangents_.push_back(triple.x);
    tangents_.push_back(triple.y);
    tangents_.push_back(triple.z);
  }
}

void Mesh::SetTangents(const std::vector<float>& tangents) {
  tangents_ = tangents;
}

void Mesh::SetUvs(const std::vector<glm::vec2>& uvs) {
  uvs_.clear();
  for (const auto& tupple : uvs) {
    uvs_.push_back(tupple.x);
    uvs_.push_back(tupple.y);
  }
}

void Mesh::SetUvs(const std::vector<float>& uvs) { uvs_ = uvs; }

void Mesh::SetUvs2(const std::vector<glm::vec2>& uvs_2) {
  uvs_2_.clear();
  for (const auto& tupple : uvs_2) {
    uvs_2_.push_back(tupple.x);
    uvs_2_.push_back(tupple.y);
  }
}

void Mesh::SetUvs2(const std::vector<float>& uvs_2) { uvs_2_ = uvs_2; }

void Mesh::SetFaces(const std::vector<unsigned int>& faces) { faces_ = faces; }

unsigned int Mesh::GetNumberOfPositions() const { return positions_.size(); }

unsigned int Mesh::GetNumberOfNormals() const { return normals_.size(); }

unsigned int Mesh::GetNumberOfTangents() const { return tangents_.size(); }

unsigned int Mesh::GetNumberOfUvs() const { return uvs_.size(); }

unsigned int Mesh::GetNumberOfUvs2() const { return uvs_2_.size(); }

unsigned int Mesh::GetNumberOfFaces() const { return faces_.size(); }

const std::vector<float>& Mesh::GetPositions() const { return positions_; }

const std::vector<float>& Mesh::GetNormals() const { return normals_; }

const std::vector<float>& Mesh::GetTangents() const { return tangents_; }

const std::vector<float>& Mesh::GetUvs() const { return uvs_; }

const std::vector<float>& Mesh::GetUvs2() const { return uvs_2_; }

const std::vector<unsigned int>& Mesh::GetFaces() const { return faces_; }

}  // namespace orangutan
