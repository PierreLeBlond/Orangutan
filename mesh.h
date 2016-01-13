#pragma once

#include <vector>
#include <fstream>

#include "opengl.h"

#include "glm/glm.hpp"

#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtx/transform.hpp"
#include "glm/gtx/transform2.hpp"
#include "glm/gtc/type_ptr.hpp"

class Mesh
{
public:
                                            Mesh(std::string name = "untitled");
                                            Mesh(const Mesh& mesh);
                                            ~Mesh();
    Mesh&                                   operator=(const Mesh& mesh);

    void                                    setObj(std::vector<glm::vec3> vertexList,
                                                std::vector<glm::vec3> normalList,
                                                std::vector<glm::vec2> texCoordList,
                                                std::vector<GLuint> faceIndexes);

    inline const std::string&               getName() const { return _name; }
    inline GLuint                           getNumberOfVertices() const { return _numberOfVertices; }
    inline GLuint                           getNumberOfNormals() const { return _numberOfNormals; }
    inline GLuint                           getNumberOfTexCoords() const { return _numberOfTexCoords; }
    inline GLuint                           getNumberOfTriangles() const { return _numberOfTriangles; }
    inline const GLfloat*                   getPositions() const { return _positions; }
    inline const GLfloat*                   getNormals() const { return _normals; }
    inline const GLfloat*                   getTexCoords() const { return _texCoords; }
    inline const GLuint*                    getIndexes() const { return _indexes; }

    void                                    copyPositions(const GLfloat* positions);
    void                                    copyNormals(const GLfloat* normals);
    void                                    copyTexCoords(const GLfloat* texCoord);
    void                                    copyIndexes(const GLuint* indexes);

    static Mesh                             createCube(GLint resolution = 1, const std::string& name = "cube");
    static Mesh                             createSphere(GLint resolution = 8, const std::string& name = "sphere");
    static Mesh                             createCylinder( GLint resolution = 8, const std::string& name = "cylindre");

private:

    std::string                             _name;

    GLuint                                  _numberOfVertices;
    GLuint                                  _numberOfNormals;
    GLuint                                  _numberOfTexCoords;
    GLuint                                  _numberOfTriangles;

    GLfloat *                               _positions;
    GLfloat *                               _normals;
    GLfloat *                               _texCoords;
    GLuint *                                _indexes;


};
