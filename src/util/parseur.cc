#include "util/parseur.h"

using namespace std;

vector<std::shared_ptr<Material>> Parseur::parseMtl(
    const std::string& filename) {
  vector<std::shared_ptr<Material>> materials;

  /*

  std::cout << "-------------------------------------------------------" <<
  std::endl; std::cout << "--- Loading " << filename << std::endl; std::cout <<
  "-------------------------------------------------------" << std::endl;

  std::ifstream mtlStream(filename);

  //On linux, . is ,, so, well, sscanf doesn't work without this.
  setlocale(LC_NUMERIC,"C");

  if(!mtlStream.bad())
  {
      char line[256];
      memset(line, '\0', 256 * sizeof(char));

      int nbMaterials = 0;

      char name[256];
      memset(name, '\0', 256 * sizeof(char));

      glm::vec3 Kd = glm::vec3(1.0f);
      glm::vec3 Ks = glm::vec3(1.0f);
      glm::vec3 Ka = glm::vec3(1.0f);
      int illum = 1;
      float Ns = 1.0f;
      float Tr = 1.0f;


      char textureName[256];
      memset(textureName, '\0', 256 * sizeof(char));


      while (!mtlStream.eof())
      {
          mtlStream.getline(line, 256);

          if(line[0] == 'n' && line[1] == 'e' && line[2] == 'w' && line[3] ==
  'm' && line[4] == 't' && line[5] == 'l' && nbMaterials != 0)
          {

              std::shared_ptr<Material> material =
  std::make_shared<Material>(name); material->setMtl(Kd, Ks, Ka, Ns, Tr);
              if(textureName != "")
              {
                  std::string filename;
                  filename.append("images/");
                  filename.append(textureName);
                  //!\material->CreateDiffuseMap(filename.c_str());
              }

              materials.push_back(material);
              nbMaterials++;

              Kd = glm::vec3(1.0f);
              Ks = glm::vec3(1.0f);
              Ka = glm::vec3(1.0f);
              illum = 1;
              Ns = 1.0f;
              Tr = 1.0f;

              textureName[0] = '\0';
              sscanf(line, "newmtl %s", name);
          }
          else if(line[0] == 'n' && line[1] == 'e' && line[2] == 'w' && line[3]
  == 'm' && line[4] == 't' && line[5] == 'l' && nbMaterials == 0)
          {
              sscanf(line, "newmtl %s", name);
              nbMaterials++;
          }
          else
          {

              if(line[0] == 'K' && line[1] == 'd')
                  sscanf(line, "Kd %f %f %f", &(Kd.x), &(Kd.y), &(Kd.z));
              if(line[0] == 'K' && line[1] == 'a')
                  sscanf(line, "Ka %f %f %f", &(Ka.x), &(Ka.y), &(Ka.z));
              if(line[0] == 'K' && line[1] == 's')
                  sscanf(line, "Ks %f %f %f", &(Ks.x), &(Ks.y), &(Ks.z));
              if(line[0] == 'N' && line[1] == 's')
                  sscanf(line, "Ns %f", &(Ns));
              if(line[0] == 'T' && line[1] == 'r')
                  sscanf(line, "Tr %f", &(Tr));
              if(line[0] == 'm' && line[1] == 'a' && line[2] == 'p' && line[3]
  == '_' && line[4] == 'K' && line[5] == 'd') sscanf(line, "map_Kd %s",
  textureName);
          }


      }

      std::shared_ptr<Material> material = std::make_shared<Material>(name);
      material->setMtl(Kd, Ks, Ka, Ns, Tr);
      if(textureName != "")
      {
          std::string filename;
          filename.append("images/");
          filename.append(textureName);
          //!\material->CreateDiffuseMap(filename.c_str());
      }

      materials.push_back(material);

      mtlStream.close();
  }
*/
  return materials;
}

vector<std::shared_ptr<Mesh>> Parseur::parseObj(const std::string& filename) {
  vector<std::shared_ptr<Mesh>> meshs;

  // std::cout << "-------------------------------------------------------" <<
  // std::endl; std::cout << "--- Loading " << filename << std::endl; std::cout
  // << "-------------------------------------------------------" << std::endl;

  std::ifstream objStream(filename);

  // On linux, . is ,, so, well, sscanf doesn't work without this.
  setlocale(LC_NUMERIC, "C");

  if (!objStream.bad()) {
    std::vector<glm::vec3> vertexList;
    std::vector<glm::vec3> normalList;
    std::vector<glm::vec2> texCoordList;

    std::vector<glm::vec3> duplicatedVertices;
    std::vector<glm::vec3> duplicatedNormals;
    std::vector<glm::vec2> duplicatedTexCoords;

    std::vector<unsigned int> faceIndexes;

    char name[256];

    int nbMesh = 0;

    char line[256];
    memset(line, '\0', 256 * sizeof(char));

    while (!objStream.eof()) {
      objStream.getline(line, 256);

      if ((line[0] == 'o' || line[0] == 'g') && nbMesh != 0) {
        // std::cout << "New mesh load successfully" << std::endl;
        // std::cout << "Number of vertices: " << vertexList.size() <<
        // std::endl; std::cout << "Number of vertex normals: " <<
        // normalList.size() << std::endl; std::cout << "Number of Map
        // coordinates: " << texCoordList.size() << std::endl; std::cout <<
        // "Number of triangular faces: " << faceIndexes.size() / 3 <<
        // std::endl;

        if (!duplicatedNormals.empty() &&
            duplicatedVertices.size() != duplicatedNormals.size()) {
          std::cerr << "/!\\ Error while loading normals" << std::endl;
        }

        if (!duplicatedTexCoords.empty() &&
            duplicatedVertices.size() != duplicatedTexCoords.size()) {
          std::cerr << "/!\\ Error while loading tex coords" << std::endl;
        }

        std::shared_ptr<Mesh> mesh = std::make_shared<Mesh>(std::string(name));
        mesh->setPositions(duplicatedVertices);
        mesh->setNormals(duplicatedNormals);
        mesh->setUvs(duplicatedTexCoords);
        mesh->setFaces(faceIndexes);
        meshs.push_back(mesh);
        nbMesh++;

        /*vertexList.clear();
        normalList.clear();
        texCoordList.clear();
        faceIndexes.clear();*/

        duplicatedVertices.clear();
        duplicatedNormals.clear();
        duplicatedTexCoords.clear();

        sscanf(line, "o %s", name);

      } else if ((line[0] == 'o' || line[0] == 'g') && nbMesh == 0) {
        sscanf(line, "o %s", name);
        nbMesh++;
      } else {
        if (line[0] == 'v') {
          if (line[1] == 'n') {
            glm::vec3 normal;

            sscanf(line, "vn %f %f %f", &(normal.x), &(normal.y), &(normal.z));

            normalList.push_back(normal);
          } else if (line[1] == 't') {
            glm::vec2 texCoord;

            sscanf(line, "vt %f %f", &(texCoord.s), &(texCoord.t));

            texCoordList.push_back(texCoord);
          } else if (line[1] == ' ') {
            glm::vec3 vertex;

            sscanf(line, "v %f %f %f", &(vertex.x), &(vertex.y), &(vertex.z));

            vertexList.push_back(vertex);
          }
        } else if (line[0] == 'f') {
          int faceVertices[3] = {-1, -1, -1};
          int faceNormals[3] = {-1, -1, -1};
          int faceMaps[3] = {-1, -1, -1};

          if (normalList.empty() && texCoordList.empty()) {
            sscanf(line, "f %i %i %i", &(faceVertices[0]), &(faceVertices[1]),
                   &(faceVertices[2]));
          } else if (!normalList.empty() && texCoordList.empty()) {
            sscanf(line, "f %i//%i %i//%i %i//%i", &(faceVertices[0]),
                   &(faceNormals[0]), &(faceVertices[1]), &(faceNormals[1]),
                   &(faceVertices[2]), &(faceNormals[2]));
          } else if (normalList.empty() && !texCoordList.empty()) {
            sscanf(line, "f %i/%i/ %i/%i/ %i/%i/", &(faceVertices[0]),
                   &(faceMaps[0]), &(faceVertices[1]), &(faceMaps[1]),
                   &(faceVertices[2]), &(faceMaps[2]));
          } else if (!normalList.empty() && !texCoordList.empty()) {
            sscanf(line, "f %i/%i/%i %i/%i/%i %i/%i/%i", &(faceVertices[0]),
                   &(faceMaps[0]), &(faceNormals[0]), &(faceVertices[1]),
                   &(faceMaps[1]), &(faceNormals[1]), &(faceVertices[2]),
                   &(faceMaps[2]), &(faceNormals[2]));
          }

          for (unsigned int i = 0; i < 3; ++i) {
            faceIndexes.push_back(duplicatedVertices.size());

            if (faceVertices[i] != -1) {
              duplicatedVertices.push_back(vertexList[faceVertices[i] - 1]);
            }

            if (faceNormals[i] != -1) {
              duplicatedNormals.push_back(normalList[faceNormals[i] - 1]);
            }

            if (faceMaps[i] != -1) {
              duplicatedTexCoords.push_back(texCoordList[faceMaps[i] - 1]);
            }
          }
        }
      }
    }

    // std::cout << "New and Last mesh load successfully" << std::endl;
    // std::cout << "Number of vertices: " << vertexList.size() << std::endl;
    // std::cout << "Number of vertex normals: " << normalList.size() <<
    // std::endl; std::cout << "Number of Map coordinates: " <<
    // texCoordList.size() << std::endl; std::cout << "Number of triangular
    // faces: " << faceIndexes.size() / 3 << std::endl;

    if (!duplicatedNormals.empty() &&
        duplicatedVertices.size() != duplicatedNormals.size()) {
      std::cerr << "/!\\ Error while loading normals" << std::endl;
    }

    if (!duplicatedTexCoords.empty() &&
        duplicatedVertices.size() != duplicatedTexCoords.size()) {
      std::cerr << "/!\\ Error while loading tex coords" << std::endl;
    }

    std::shared_ptr<Mesh> mesh = std::make_shared<Mesh>(std::string(name));
    mesh->setPositions(duplicatedVertices);
    mesh->setNormals(duplicatedNormals);
    mesh->setUvs(duplicatedTexCoords);
    mesh->setFaces(faceIndexes);

    meshs.push_back(mesh);
    nbMesh++;

    objStream.close();
  }

  return meshs;
}
