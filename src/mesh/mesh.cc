#include "mesh/mesh.h"

#include <iostream>

namespace orangutan {

Mesh::Mesh(const std::string& name) : Asset(name) {}

void Mesh::setPositions(const std::vector<glm::vec3>& positions) {
  _positions.clear();
  for (const auto& triple : positions) {
    _positions.push_back(triple.x);
    _positions.push_back(triple.y);
    _positions.push_back(triple.z);
  }
}

void Mesh::setPositions(const std::vector<float>& positions) {
  _positions = positions;
}

void Mesh::setNormals(const std::vector<glm::vec3>& normals) {
  _normals.clear();
  for (const auto& triple : normals) {
    _normals.push_back(triple.x);
    _normals.push_back(triple.y);
    _normals.push_back(triple.z);
  }
}

void Mesh::setNormals(const std::vector<float>& normals) { _normals = normals; }

void Mesh::setUvs(const std::vector<glm::vec2>& uvs) {
  _uvs.clear();
  for (const auto& tupple : uvs) {
    _uvs.push_back(tupple.x);
    _uvs.push_back(tupple.y);
  }
}

void Mesh::setUvs(const std::vector<float>& uvs) { _uvs = uvs; }

void Mesh::setFaces(const std::vector<unsigned int>& faces) { _faces = faces; }

unsigned int Mesh::getNumberOfPositions() const { return _positions.size(); }

unsigned int Mesh::getNumberOfNormals() const { return _normals.size(); }

unsigned int Mesh::getNumberOfUvs() const { return _uvs.size(); }

unsigned int Mesh::getNumberOfFaces() const { return _faces.size(); }

const std::vector<float>& Mesh::getPositions() const { return _positions; }

const std::vector<float>& Mesh::getNormals() const { return _normals; }

const std::vector<float>& Mesh::getUvs() const { return _uvs; }

const std::vector<unsigned int>& Mesh::getFaces() const { return _faces; }

}  // namespace orangutan
