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
                                            Mesh(const std::string& name = "Mesh X");

    void                                    setPositions(const std::vector<glm::vec3>& positions);
    void                                    setPositions(const std::vector<float>& positions);
    void                                    setNormals(const std::vector<glm::vec3>& normals);
    void                                    setNormals(const std::vector<float>& normals);
    void                                    setUvs(const std::vector<glm::vec2>& uvs);
    void                                    setUvs(const std::vector<float>& uvs);
    void                                    setFaces(const std::vector<unsigned int>& faces);

    unsigned int                            getNumberOfPositions() const;
    unsigned int                            getNumberOfNormals() const;
    unsigned int                            getNumberOfUvs() const;
    unsigned int                            getNumberOfFaces() const;

    const std::vector<float>&               getPositions() const;
    const std::vector<float>&               getNormals() const;
    const std::vector<float>&               getUvs() const;
    const std::vector<unsigned int>&        getFaces() const;

    static std::shared_ptr<Mesh>            createSquare(const std::string& name = "Square X");
    static std::shared_ptr<Mesh>            createCube(int resolution = 1,
                                                       const std::string& name = "Cube X");
    static std::shared_ptr<Mesh>            createSphere(int resolution = 8,
                                                         const std::string& name = "Sphere X");
    static std::shared_ptr<Mesh>            createCylinder(int resolution = 8,
                                                           const std::string& name = "Cylindre X");

private:
    std::vector<float>                       _positions;
    std::vector<float>                       _normals;
    std::vector<float>                       _uvs;
    std::vector<unsigned int>                _faces;
};
