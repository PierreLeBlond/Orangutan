#include "mesh/meshfactory.h"

#include <iostream>
#include <memory>
#include <type_traits>

namespace orangutan {

std::unique_ptr<Mesh> MeshFactory::CreateSquare(const std::string& name) {
  auto mesh = std::make_unique<Mesh>(name);

  std::vector<glm::vec3> positions;
  std::vector<glm::vec3> normals;
  std::vector<glm::vec3> tangents;
  std::vector<glm::vec2> uvs;

  positions.push_back(glm::vec3(-1.0f, -1.0f, 0.0f));
  positions.push_back(glm::vec3(1.0f, -1.0f, 0.0f));
  positions.push_back(glm::vec3(-1.0f, 1.0f, 0.0f));
  positions.push_back(glm::vec3(1.0f, 1.0f, 0.0f));

  normals.push_back(glm::vec3(0.0f, 0.0f, -1.0f));
  normals.push_back(glm::vec3(0.0f, 0.0f, -1.0f));
  normals.push_back(glm::vec3(0.0f, 0.0f, -1.0f));
  normals.push_back(glm::vec3(0.0f, 0.0f, -1.0f));

  tangents.push_back(glm::vec3(1.0f, 0.0f, 0.0f));
  tangents.push_back(glm::vec3(1.0f, 0.0f, 0.0f));
  tangents.push_back(glm::vec3(1.0f, 0.0f, 0.0f));
  tangents.push_back(glm::vec3(1.0f, 0.0f, 0.0f));

  uvs.push_back(glm::vec2(0.0f, 0.0f));
  uvs.push_back(glm::vec2(1.0f, 0.0f));
  uvs.push_back(glm::vec2(0.0f, 1.0f));
  uvs.push_back(glm::vec2(1.0f, 1.0f));

  std::vector<unsigned int> faces;

  faces.push_back(0);
  faces.push_back(1);
  faces.push_back(2);
  faces.push_back(1);
  faces.push_back(2);
  faces.push_back(3);

  mesh->SetPositions(positions);
  mesh->SetNormals(normals);
  mesh->SetTangents(tangents);
  mesh->SetUvs(uvs);
  mesh->SetFaces(faces);

  return mesh;
}

std::unique_ptr<Mesh> MeshFactory::CreateCube(const std::string& name,
                                              int resolution) {
  auto mesh = std::make_unique<Mesh>(name);

  std::vector<glm::vec3> positions;
  std::vector<glm::vec3> normals;
  std::vector<glm::vec2> uvs;

  std::vector<unsigned int> faces;

  // front
  // 0
  positions.push_back(glm::vec3(1.0, 1.0, 1.0));
  normals.push_back(glm::vec3(0.0, 0.0, 1.0));
  uvs.push_back(glm::vec2(0.5, 0.3334));
  // 1
  positions.push_back(glm::vec3(-1.0, 1.0, 1.0));
  normals.push_back(glm::vec3(0.0, 0.0, 1.0));
  uvs.push_back(glm::vec2(0.25, 0.3334));
  // 2
  positions.push_back(glm::vec3(-1.0, -1.0, 1.0));
  normals.push_back(glm::vec3(0.0, 0.0, 1.0));
  uvs.push_back(glm::vec2(0.25, 0.0));
  // 3
  positions.push_back(glm::vec3(1.0, -1.0, 1.0));
  normals.push_back(glm::vec3(0.0, 0.0, 1.0));
  uvs.push_back(glm::vec2(0.5, 0.0));

  faces.push_back(0);
  faces.push_back(1);
  faces.push_back(2);
  faces.push_back(0);
  faces.push_back(2);
  faces.push_back(3);

  // back
  // 4
  positions.push_back(glm::vec3(1.0, 1.0, -1.0));
  normals.push_back(glm::vec3(0.0, 0.0, -1.0));
  uvs.push_back(glm::vec2(0.5, 0.6665));
  // 5
  positions.push_back(glm::vec3(-1.0, 1.0, -1.0));
  normals.push_back(glm::vec3(0.0, 0.0, -1.0));
  uvs.push_back(glm::vec2(0.25, 0.6665));
  // 6
  positions.push_back(glm::vec3(-1.0, -1.0, -1.0));
  normals.push_back(glm::vec3(0.0, 0.0, -1.0));
  uvs.push_back(glm::vec2(0.25, 1.0));
  // 7
  positions.push_back(glm::vec3(1.0, -1.0, -1.0));
  normals.push_back(glm::vec3(0.0, 0.0, -1.0));
  uvs.push_back(glm::vec2(0.5, 1.0));

  faces.push_back(4);
  faces.push_back(5);
  faces.push_back(6);
  faces.push_back(4);
  faces.push_back(6);
  faces.push_back(7);

  // top
  // 8
  positions.push_back(glm::vec3(1.0, 1.0, -1.0));
  normals.push_back(glm::vec3(0.0, 1.0, 0.0));
  uvs.push_back(glm::vec2(0.5, 0.6665));
  // 9
  positions.push_back(glm::vec3(-1.0, 1.0, -1.0));
  normals.push_back(glm::vec3(0.0, 1.0, 0.0));
  uvs.push_back(glm::vec2(0.25, 0.6665));
  // 10
  positions.push_back(glm::vec3(-1.0, 1.0, 1.0));
  normals.push_back(glm::vec3(0.0, 1.0, 0.0));
  uvs.push_back(glm::vec2(0.25, 0.3334));
  // 11
  positions.push_back(glm::vec3(1.0, 1.0, 1.0));
  normals.push_back(glm::vec3(0.0, 1.0, 0.0));
  uvs.push_back(glm::vec2(0.5, 0.3334));

  faces.push_back(8);
  faces.push_back(9);
  faces.push_back(10);
  faces.push_back(8);
  faces.push_back(10);
  faces.push_back(11);

  // bottom
  // 12
  positions.push_back(glm::vec3(1.0, -1.0, -1.0));
  normals.push_back(glm::vec3(0.0, -1.0, 0.0));
  uvs.push_back(glm::vec2(0.75, 0.6665));
  // 13
  positions.push_back(glm::vec3(-1.0, -1.0, -1.0));
  normals.push_back(glm::vec3(0.0, -1.0, 0.0));
  uvs.push_back(glm::vec2(1.0, 0.6665));
  // 14
  positions.push_back(glm::vec3(-1.0, -1.0, 1.0));
  normals.push_back(glm::vec3(0.0, -1.0, 0.0));
  uvs.push_back(glm::vec2(1.0, 0.3334));
  // 15
  positions.push_back(glm::vec3(1.0, -1.0, 1.0));
  normals.push_back(glm::vec3(0.0, -1.0, 0.0));
  uvs.push_back(glm::vec2(0.75, 0.3334));

  faces.push_back(12);
  faces.push_back(13);
  faces.push_back(14);
  faces.push_back(12);
  faces.push_back(14);
  faces.push_back(15);

  // right
  // 16
  positions.push_back(glm::vec3(1.0, 1.0, -1.0));
  normals.push_back(glm::vec3(1.0, 0.0, 0.0));
  uvs.push_back(glm::vec2(0.5, 0.6665));
  // 17
  positions.push_back(glm::vec3(1.0, 1.0, 1.0));
  normals.push_back(glm::vec3(1.0, 0.0, 0.0));
  uvs.push_back(glm::vec2(0.5, 0.3334));
  // 18
  positions.push_back(glm::vec3(1.0, -1.0, 1.0));
  normals.push_back(glm::vec3(1.0, 0.0, 0.0));
  uvs.push_back(glm::vec2(0.75, 0.3334));
  // 19
  positions.push_back(glm::vec3(1.0, -1.0, -1.0));
  normals.push_back(glm::vec3(1.0, 0.0, 0.0));
  uvs.push_back(glm::vec2(0.75, 0.6665));

  faces.push_back(16);
  faces.push_back(17);
  faces.push_back(18);
  faces.push_back(16);
  faces.push_back(18);
  faces.push_back(19);

  // left
  // 20
  positions.push_back(glm::vec3(-1.0, 1.0, -1.0));
  normals.push_back(glm::vec3(-1.0, 0.0, 0.0));
  uvs.push_back(glm::vec2(0.25, 0.6665));
  // 21
  positions.push_back(glm::vec3(-1.0, 1.0, 1.0));
  normals.push_back(glm::vec3(-1.0, 0.0, 0.0));
  uvs.push_back(glm::vec2(0.25, 0.3334));
  // 22
  positions.push_back(glm::vec3(-1.0, -1.0, 1.0));
  normals.push_back(glm::vec3(-1.0, 0.0, 0.0));
  uvs.push_back(glm::vec2(0.0, 0.3334));
  // 23
  positions.push_back(glm::vec3(-1.0, -1.0, -1.0));
  normals.push_back(glm::vec3(-1.0, 0.0, 0.0));
  uvs.push_back(glm::vec2(0.0, 0.6665));

  faces.push_back(20);
  faces.push_back(21);
  faces.push_back(22);
  faces.push_back(20);
  faces.push_back(22);
  faces.push_back(23);

  for (int subdivide = 0; subdivide < resolution; subdivide++) {
    size_t nbVertex = positions.size();
    int** mat = new int*[nbVertex];

    for (size_t i = 0; i < nbVertex; i++) {
      mat[i] = new int[nbVertex];
    }
    for (size_t i = 0; i < nbVertex; i++)
      for (size_t j = 0; j < nbVertex; j++) mat[i][j] = -1;

    unsigned int stIndex;
    unsigned int sndIndex;
    unsigned int thIndex;
    unsigned int stNewIndex;
    unsigned int sndNewIndex;
    unsigned int thNewIndex;

    size_t numberOfIndexes = nbVertex - 1;

    size_t nbFace = faces.size() / 3;
    for (size_t i = 0; i < nbFace; i++) {
      stIndex = faces[3 * i];
      sndIndex = faces[3 * i + 1];
      thIndex = faces[3 * i + 2];
      if (mat[stIndex][sndIndex] != -1) {
        stNewIndex = mat[stIndex][sndIndex];
      } else if (mat[sndIndex][stIndex] != -1) {
        stNewIndex = mat[sndIndex][stIndex];
      } else {
        stNewIndex = (unsigned int)++numberOfIndexes;
        mat[stIndex][sndIndex] = stNewIndex;
        glm::vec3 stPosition = positions[stIndex];
        glm::vec3 sndPosition = positions[sndIndex];
        positions.push_back(0.5f * (stPosition + sndPosition));
        glm::vec2 stTex = uvs[stIndex];
        glm::vec2 sndTex = uvs[sndIndex];
        uvs.push_back(0.5f * (stTex + sndTex));
        normals.push_back(normals[stIndex]);
      }

      if (mat[thIndex][sndIndex] != -1) {
        sndNewIndex = mat[thIndex][sndIndex];
      } else if (mat[sndIndex][thIndex] != -1) {
        sndNewIndex = mat[sndIndex][thIndex];
      } else {
        sndNewIndex = (unsigned int)++numberOfIndexes;
        mat[thIndex][sndIndex] = sndNewIndex;
        glm::vec3 thPosition = positions[thIndex];
        glm::vec3 sndPosition = positions[sndIndex];
        positions.push_back(0.5f * (thPosition + sndPosition));
        glm::vec2 thTex = uvs[thIndex];
        glm::vec2 sndTex = uvs[sndIndex];
        uvs.push_back(0.5f * (thTex + sndTex));
        normals.push_back(normals[sndIndex]);
      }

      if (mat[stIndex][thIndex] != -1) {
        thNewIndex = mat[stIndex][thIndex];
      } else if (mat[thIndex][stIndex] != -1) {
        thNewIndex = mat[thIndex][stIndex];
      } else {
        thNewIndex = (unsigned int)++numberOfIndexes;
        mat[stIndex][thIndex] = thNewIndex;
        glm::vec3 stPosition = positions[stIndex];
        glm::vec3 thPosition = positions[thIndex];
        positions.push_back(0.5f * (stPosition + thPosition));
        glm::vec2 stTex = uvs[stIndex];
        glm::vec2 thTex = uvs[thIndex];
        uvs.push_back(0.5f * (stTex + thTex));
        normals.push_back(normals[thIndex]);
      }

      faces[3 * i] = stNewIndex;
      faces[3 * i + 1] = sndNewIndex;
      faces[3 * i + 2] = thNewIndex;
      faces.push_back(stIndex);
      faces.push_back(stNewIndex);
      faces.push_back(thNewIndex);
      faces.push_back(sndIndex);
      faces.push_back(stNewIndex);
      faces.push_back(sndNewIndex);
      faces.push_back(thIndex);
      faces.push_back(sndNewIndex);
      faces.push_back(thNewIndex);
    }

    for (unsigned int i = 0; i < nbVertex; i++) delete[] mat[i];
    delete[] mat;
  }

  mesh->SetPositions(positions);
  mesh->SetNormals(normals);
  mesh->SetUvs(uvs);
  mesh->SetFaces(faces);

  return mesh;
}

std::unique_ptr<Mesh> MeshFactory::ExtractMesh(const aiMesh& mesh) {
  auto extracted_mesh = std::make_unique<Mesh>(mesh.mName.C_Str());

  std::vector<glm::vec3> vertices;
  std::vector<glm::vec3> normals;
  std::vector<glm::vec3> tangents;
  std::vector<glm::vec2> uvs;
  std::vector<glm::vec2> uvs_2;

  std::vector<unsigned int> indices;

  for (unsigned int i = 0; i < mesh.mNumVertices; i++) {
    glm::vec3 vertex = glm::vec3(mesh.mVertices[i].x, mesh.mVertices[i].y,
                                 mesh.mVertices[i].z);
    vertices.push_back(vertex);

    glm::vec3 normal =
        glm::vec3(mesh.mNormals[i].x, mesh.mNormals[i].y, mesh.mNormals[i].z);
    normals.push_back(normal);

    glm::vec3 tangent = glm::vec3(mesh.mTangents[i].x, mesh.mTangents[i].y,
                                  mesh.mTangents[i].z);
    tangents.push_back(tangent);

    glm::vec2 uv;
    if (mesh.mTextureCoords[0]) {
      uv = glm::vec2(mesh.mTextureCoords[0][i].x, mesh.mTextureCoords[0][i].y);
    }
    uvs.push_back(uv);

    glm::vec2 uv_2;
    if (mesh.mTextureCoords[1]) {
      uv_2 =
          glm::vec2(mesh.mTextureCoords[1][i].x, mesh.mTextureCoords[1][i].y);
    }
    uvs_2.push_back(uv_2);
  }

  for (unsigned int i = 0; i < mesh.mNumFaces; i++) {
    aiFace face = mesh.mFaces[i];
    for (unsigned int j = 0; j < face.mNumIndices; j++) {
      indices.push_back(face.mIndices[j]);
    }
  }

  extracted_mesh->SetPositions(vertices);
  extracted_mesh->SetNormals(normals);
  extracted_mesh->SetTangents(tangents);
  extracted_mesh->SetUvs(uvs);
  extracted_mesh->SetUvs2(uvs_2);
  extracted_mesh->SetFaces(indices);

  return extracted_mesh;
}

}  // namespace orangutan
