#include "object/mesh.h"

#include <iostream>

Mesh::Mesh(const std::string& name) : Asset(name)
{
}

void Mesh::setPositions(const std::vector<glm::vec3>& positions)
{
    _positions.clear();
    for(const auto& triple : positions)
    {
        _positions.push_back(triple.x);
        _positions.push_back(triple.y);
        _positions.push_back(triple.z);
    }
}

void Mesh::setPositions(const std::vector<float>& positions)
{
    _positions = positions;
}

void Mesh::setNormals(const std::vector<glm::vec3>& normals)
{
    _normals.clear();
    for(const auto& triple : normals)
    {
        _normals.push_back(triple.x);
        _normals.push_back(triple.y);
        _normals.push_back(triple.z);
    }
}

void Mesh::setNormals(const std::vector<float>& normals)
{
    _normals = normals;
}

void Mesh::setUvs(const std::vector<glm::vec2>& uvs)
{
    _uvs.clear();
    for(const auto& tupple : uvs)
    {
        _uvs.push_back(tupple.x);
        _uvs.push_back(tupple.y);
    }
}

void Mesh::setUvs(const std::vector<float>& uvs)
{
    _uvs = uvs;
}

void Mesh::setFaces(const std::vector<unsigned int>& faces)
{
    _faces = faces;
}

unsigned int Mesh::getNumberOfPositions() const
{
    return _positions.size();
}

unsigned int Mesh::getNumberOfNormals() const
{
    return _normals.size();
}

unsigned int Mesh::getNumberOfUvs() const
{
    return _uvs.size();
}

unsigned int Mesh::getNumberOfFaces() const
{
    return _faces.size();
}

const std::vector<float>& Mesh::getPositions() const
{
    return _positions;
}

const std::vector<float>& Mesh::getNormals() const
{
    return _normals;
}

const std::vector<float>& Mesh::getUvs() const
{
    return _uvs;
}

const std::vector<unsigned int>& Mesh::getFaces() const
{
    return _faces;
}

std::shared_ptr<Mesh> Mesh::createSquare(const std::string& name){

    std::shared_ptr<Mesh> mesh = std::make_shared<Mesh>(name);

    std::vector<glm::vec3> positions;
    std::vector<glm::vec3> normals;
    std::vector<glm::vec2> uvs;

    positions.push_back(glm::vec3(-1.0f, -1.0f, 0.0f));
    positions.push_back(glm::vec3(1.0f, -1.0f, 0.0f));
    positions.push_back(glm::vec3(-1.0f, 1.0f, 0.0f));
    positions.push_back(glm::vec3(1.0f, 1.0f, 0.0f));

    normals.push_back(glm::vec3(0.0f, 0.0f, -1.0f));
    normals.push_back(glm::vec3(0.0f, 0.0f, -1.0f));
    normals.push_back(glm::vec3(0.0f, 0.0f, -1.0f));
    normals.push_back(glm::vec3(0.0f, 0.0f, -1.0f));

    uvs.push_back(glm::vec2(0.0f, 0.0f));
    uvs.push_back(glm::vec2(1.0f, 0.0f));
    uvs.push_back(glm::vec2(0.0f, 1.0f));
    uvs.push_back(glm::vec2(1.0f, 1.0f));

    std::vector<unsigned int > faces;

    faces.push_back(0);
    faces.push_back(1);
    faces.push_back(2);
    faces.push_back(1);
    faces.push_back(2);
    faces.push_back(3);

    mesh->setPositions(positions);
    mesh->setNormals(normals);
    mesh->setUvs(uvs);
    mesh->setFaces(faces);

    return mesh;
}

std::shared_ptr<Mesh> Mesh::createCube(int resolution, const std::string& name){

    std::shared_ptr<Mesh> mesh = std::make_shared<Mesh>(name);

    std::vector<glm::vec3> positions;
    std::vector<glm::vec3> normals;
    std::vector<glm::vec2> uvs;

    std::vector<unsigned int > faces;

    //front
    //0
    positions.push_back(glm::vec3(1.0, 1.0, 1.0));
    normals.push_back(glm::vec3(0.0, 0.0, 1.0));
    uvs.push_back(glm::vec2(0.5, 0.3334));
    //1
    positions.push_back(glm::vec3(-1.0, 1.0, 1.0));
    normals.push_back(glm::vec3(0.0, 0.0, 1.0));
    uvs.push_back(glm::vec2(0.25, 0.3334));
    //2
    positions.push_back(glm::vec3(-1.0, -1.0, 1.0));
    normals.push_back(glm::vec3(0.0, 0.0, 1.0));
    uvs.push_back(glm::vec2(0.25, 0.0));
    //3
    positions.push_back(glm::vec3(1.0, -1.0, 1.0));
    normals.push_back(glm::vec3(0.0, 0.0, 1.0));
    uvs.push_back(glm::vec2(0.5, 0.0));

    faces.push_back(0);
    faces.push_back(1);
    faces.push_back(2);
    faces.push_back(0);
    faces.push_back(2);
    faces.push_back(3);

    //back
    //4
    positions.push_back(glm::vec3(1.0, 1.0, -1.0));
    normals.push_back(glm::vec3(0.0, 0.0, -1.0));
    uvs.push_back(glm::vec2(0.5, 0.6665));
    //5
    positions.push_back(glm::vec3(-1.0, 1.0, -1.0));
    normals.push_back(glm::vec3(0.0, 0.0, -1.0));
    uvs.push_back(glm::vec2(0.25, 0.6665));
    //6
    positions.push_back(glm::vec3(-1.0, -1.0, -1.0));
    normals.push_back(glm::vec3(0.0, 0.0, -1.0));
    uvs.push_back(glm::vec2(0.25, 1.0));
    //7
    positions.push_back(glm::vec3(1.0, -1.0, -1.0));
    normals.push_back(glm::vec3(0.0, 0.0, -1.0));
    uvs.push_back(glm::vec2(0.5, 1.0));

    faces.push_back(4);
    faces.push_back(5);
    faces.push_back(6);
    faces.push_back(4);
    faces.push_back(6);
    faces.push_back(7);

    //top
    //8
    positions.push_back(glm::vec3(1.0, 1.0, -1.0));
    normals.push_back(glm::vec3(0.0, 1.0, 0.0));
    uvs.push_back(glm::vec2(0.5, 0.6665));
    //9
    positions.push_back(glm::vec3(-1.0, 1.0, -1.0));
    normals.push_back(glm::vec3(0.0, 1.0, 0.0));
    uvs.push_back(glm::vec2(0.25, 0.6665));
    //10
    positions.push_back(glm::vec3(-1.0, 1.0, 1.0));
    normals.push_back(glm::vec3(0.0, 1.0, 0.0));
    uvs.push_back(glm::vec2(0.25, 0.3334));
    //11
    positions.push_back(glm::vec3(1.0, 1.0, 1.0));
    normals.push_back(glm::vec3(0.0, 1.0, 0.0));
    uvs.push_back(glm::vec2(0.5, 0.3334));

    faces.push_back(8);
    faces.push_back(9);
    faces.push_back(10);
    faces.push_back(8);
    faces.push_back(10);
    faces.push_back(11);

    //bottom
    //12
    positions.push_back(glm::vec3(1.0, -1.0, -1.0));
    normals.push_back(glm::vec3(0.0, -1.0, 0.0));
    uvs.push_back(glm::vec2(0.75, 0.6665));
    //13
    positions.push_back(glm::vec3(-1.0, -1.0, -1.0));
    normals.push_back(glm::vec3(0.0, -1.0, 0.0));
    uvs.push_back(glm::vec2(1.0, 0.6665));
    //14
    positions.push_back(glm::vec3(-1.0, -1.0, 1.0));
    normals.push_back(glm::vec3(0.0, -1.0, 0.0));
    uvs.push_back(glm::vec2(1.0, 0.3334));
    //15
    positions.push_back(glm::vec3(1.0, -1.0, 1.0));
    normals.push_back(glm::vec3(0.0, -1.0, 0.0));
    uvs.push_back(glm::vec2(0.75, 0.3334));

    faces.push_back(12);
    faces.push_back(13);
    faces.push_back(14);
    faces.push_back(12);
    faces.push_back(14);
    faces.push_back(15);

    //right
    //16
    positions.push_back(glm::vec3(1.0, 1.0, -1.0));
    normals.push_back(glm::vec3(1.0, 0.0, 0.0));
    uvs.push_back(glm::vec2(0.5, 0.6665));
    //17
    positions.push_back(glm::vec3(1.0, 1.0, 1.0));
    normals.push_back(glm::vec3(1.0, 0.0, 0.0));
    uvs.push_back(glm::vec2(0.5, 0.3334));
    //18
    positions.push_back(glm::vec3(1.0, -1.0, 1.0));
    normals.push_back(glm::vec3(1.0, 0.0, 0.0));
    uvs.push_back(glm::vec2(0.75, 0.3334));
    //19
    positions.push_back(glm::vec3(1.0, -1.0, -1.0));
    normals.push_back(glm::vec3(1.0, 0.0, 0.0));
    uvs.push_back(glm::vec2(0.75, 0.6665));

    faces.push_back(16);
    faces.push_back(17);
    faces.push_back(18);
    faces.push_back(16);
    faces.push_back(18);
    faces.push_back(19);

    //left
    //20
    positions.push_back(glm::vec3(-1.0, 1.0, -1.0));
    normals.push_back(glm::vec3(-1.0, 0.0, 0.0));
    uvs.push_back(glm::vec2(0.25, 0.6665));
    //21
    positions.push_back(glm::vec3(-1.0, 1.0, 1.0));
    normals.push_back(glm::vec3(-1.0, 0.0, 0.0));
    uvs.push_back(glm::vec2(0.25, 0.3334));
    //22
    positions.push_back(glm::vec3(-1.0, -1.0, 1.0));
    normals.push_back(glm::vec3(-1.0, 0.0, 0.0));
    uvs.push_back(glm::vec2(0.0, 0.3334));
    //23
    positions.push_back(glm::vec3(-1.0, -1.0, -1.0));
    normals.push_back(glm::vec3(-1.0, 0.0, 0.0));
    uvs.push_back(glm::vec2(0.0, 0.6665));

    faces.push_back(20);
    faces.push_back(21);
    faces.push_back(22);
    faces.push_back(20);
    faces.push_back(22);
    faces.push_back(23);

    for(int subdivide = 0;subdivide < resolution; subdivide++){

        size_t nbVertex = positions.size();
        int  **mat = new int *[nbVertex];

        for(size_t i=0;i<nbVertex;i++){
            mat[i] = new int [nbVertex];
        }
        for(size_t i = 0; i < nbVertex;i++)
            for(size_t j = 0;j < nbVertex;j++)
                mat[i][j] = -1;


        unsigned int  stIndex;
        unsigned int  sndIndex;
        unsigned int  thIndex;
        unsigned int  stNewIndex;
        unsigned int  sndNewIndex;
        unsigned int  thNewIndex;

        size_t numberOfIndexes = nbVertex - 1;

        size_t nbFace = faces.size()/3;
        for(size_t i = 0; i < nbFace;i++){

            stIndex = faces[3*i];
            sndIndex = faces[3*i + 1];
            thIndex = faces[3*i + 2];
            if(mat[stIndex][sndIndex] != -1){
                stNewIndex = mat[stIndex][sndIndex];
            } else if(mat[sndIndex][stIndex] != -1){
                stNewIndex = mat[sndIndex][stIndex];
            } else {
                stNewIndex = (unsigned int ) ++numberOfIndexes;
                mat[stIndex][sndIndex] = stNewIndex;
                glm::vec3 stPosition = positions[stIndex];
                glm::vec3 sndPosition = positions[sndIndex];
                positions.push_back(0.5f*(stPosition + sndPosition));
                glm::vec2 stTex = uvs[stIndex];
                glm::vec2 sndTex = uvs[sndIndex];
                uvs.push_back(0.5f*(stTex + sndTex));
                normals.push_back(normals[stIndex]);
            }

            if(mat[thIndex][sndIndex] != -1){
                sndNewIndex = mat[thIndex][sndIndex];
            } else if(mat[sndIndex][thIndex] != -1){
                sndNewIndex = mat[sndIndex][thIndex];
            } else {
                sndNewIndex = (unsigned int ) ++numberOfIndexes;
                mat[thIndex][sndIndex] = sndNewIndex;
                glm::vec3 thPosition = positions[thIndex];
                glm::vec3 sndPosition = positions[sndIndex];
                positions.push_back(0.5f*(thPosition + sndPosition));
                glm::vec2 thTex = uvs[thIndex];
                glm::vec2 sndTex = uvs[sndIndex];
                uvs.push_back(0.5f*(thTex + sndTex));
                normals.push_back(normals[sndIndex]);
            }

            if(mat[stIndex][thIndex] != -1){
                thNewIndex = mat[stIndex][thIndex];
            } else if(mat[thIndex][stIndex] != -1){
                thNewIndex = mat[thIndex][stIndex];
            } else {
                thNewIndex = (unsigned int ) ++numberOfIndexes;
                mat[stIndex][thIndex] = thNewIndex;
                glm::vec3 stPosition = positions[stIndex];
                glm::vec3 thPosition = positions[thIndex];
                positions.push_back(0.5f*(stPosition + thPosition));
                glm::vec2 stTex = uvs[stIndex];
                glm::vec2 thTex = uvs[thIndex];
                uvs.push_back(0.5f*(stTex + thTex));
                normals.push_back(normals[thIndex]);
            }

            faces[3*i] = stNewIndex;
            faces[3*i + 1] = sndNewIndex;
            faces[3*i + 2] = thNewIndex;
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


        for (unsigned int i=0; i < nbVertex; i++)
            delete[] mat[i];
        delete[] mat;

    }

    mesh->setPositions(positions);
    mesh->setNormals(normals);
    mesh->setUvs(uvs);
    mesh->setFaces(faces);

    return mesh;
}

std::shared_ptr<Mesh> Mesh::createSphere(int resolution, const std::string& name){

    std::shared_ptr<Mesh> mesh = createCube(resolution, name);

    std::vector<float> newNormals(mesh->getNormals());

    std::vector<float> newPositions(mesh->getPositions());
    std::vector<float> oldPositions(newPositions);

    for(unsigned int i = 0; i < mesh->getNumberOfPositions() / 3;i++){
        float l = sqrt(oldPositions[3*i]*oldPositions[3*i] +
                       oldPositions[3*i+1]*oldPositions[3*i+1] +
                       oldPositions[3*i+2]*oldPositions[3*i+2]);
        newPositions[3*i] = oldPositions[3*i]/l;
        newNormals[3*i] = oldPositions[3*i];
        newPositions[3*i + 1] = oldPositions[3*i + 1]/l;
        newNormals[3*i + 1] = oldPositions[3*i + 1];
        newPositions[3*i + 2] = oldPositions[3*i + 2]/l;
        newNormals[3*i + 2] = oldPositions[3*i + 2];
    }

    mesh->setNormals(newNormals);
    mesh->setPositions(newPositions);

    return mesh;
}

std::shared_ptr<Mesh> Mesh::createCylinder(int resolution, const std::string& name){

    std::shared_ptr<Mesh> mesh = createCube(resolution, name);

    std::vector<float> newNormals(mesh->getNormals());

    std::vector<float> newPositions(mesh->getPositions());
    std::vector<float> oldPositions(mesh->getPositions());

    for(unsigned int  i = 0; i < mesh->getNumberOfPositions() / 3;i++){
        if(oldPositions[3*i + 1] == 1.0 || oldPositions[3*i + 1] == -1.0){
            float l = sqrt(oldPositions[3*i]*oldPositions[3*i] + oldPositions[3*i+2]*oldPositions[3*i+2]);
            if(l > 1.0){
                newPositions[3*i] = oldPositions[3*i]/l;
                newPositions[3*i + 2] = oldPositions[3*i + 2]/l;
            }
            /*if(abs(positions[3*i]) >= abs(positions[3*i + 2])){
               positions[3*i] = abs(positions[3*i + 2])*positions[3*i];
               positions[3*i + 2] = abs(positions[3*i + 2])*positions[3*i + 2];
            }else if(abs(positions[3*i]) < abs(positions[3*i + 2])){
                positions[3*i] *= abs(positions[3*i]);
                positions[3*i + 2] *= abs(positions[3*i]);
            }*/
        }else{
            float l = sqrt(oldPositions[3*i]*oldPositions[3*i] + oldPositions[3*i+2]*oldPositions[3*i+2]);
            newPositions[3*i] = oldPositions[3*i]/l;
            newNormals[3*i] = oldPositions[3*i];
            newPositions[3*i + 2] = oldPositions[3*i + 2]/l;
            newNormals[3*i + 2] = oldPositions[3*i + 2];
        }
    }

    mesh->setNormals(newNormals);
    mesh->setPositions(newPositions);

    return mesh;
}
