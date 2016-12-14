#pragma once

#include <vector>
#include <fstream>
#include <memory>

#include "object/asset.h"

#include "glm/glm.hpp"

#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtx/transform.hpp"
#include "glm/gtx/transform2.hpp"
#include "glm/gtc/type_ptr.hpp"

class Mesh : public Asset
{
public:
                                            Mesh(std::string name = "untitled");
                                            Mesh(const Mesh& mesh);
                                            ~Mesh();
    Mesh&                                   operator=(const Mesh& mesh);

    void                                    setObj(std::vector<glm::vec3> vertexList,
                                                std::vector<glm::vec3> normalList,
                                                std::vector<glm::vec2> texCoordList,
                                                std::vector<unsigned int> faceIndexes);

    inline unsigned int                     getNumberOfVertices() const { return _numberOfVertices; }
    inline unsigned int                     getNumberOfNormals() const { return _numberOfNormals; }
    inline unsigned int                     getNumberOfTexCoords() const { return _numberOfTexCoords; }
    inline unsigned int                     getNumberOfTriangles() const { return _numberOfTriangles; }
    inline const float*                     getPositions() const { return _positions; }
    inline const float*                     getNormals() const { return _normals; }
    inline const float*                     getTexCoords() const { return _texCoords; }
    inline const unsigned int *             getIndexes() const { return _indexes; }

    void                                    copyPositions(const float* positions);
    void                                    copyNormals(const float* normals);
    void                                    copyTexCoords(const float* texCoord);
    void                                    copyIndexes(const unsigned int * indexes);

    static std::shared_ptr<Mesh>            createSquare(const std::string& name = "square");
    static std::shared_ptr<Mesh>            createCube(int resolution = 1, const std::string& name = "cube");
    static std::shared_ptr<Mesh>            createSphere(int resolution = 8, const std::string& name = "sphere");
    static std::shared_ptr<Mesh>            createCylinder( int resolution = 8, const std::string& name = "cylindre");

private:

    unsigned int                             _numberOfVertices;
    unsigned int                             _numberOfNormals;
    unsigned int                             _numberOfTexCoords;
    unsigned int                             _numberOfTriangles;

    float*                                  _positions;
    float*                                  _normals;
    float*                                  _texCoords;
    unsigned int*                           _indexes;
};
