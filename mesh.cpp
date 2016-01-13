#include "mesh.h"


Mesh::Mesh(std::string name) : _name(name)
{
    _indexes = new GLuint;
    _positions = new GLfloat;
    _normals = new GLfloat;
    _texCoords = new GLfloat;
}

Mesh::Mesh(const Mesh & mesh){

    _name = mesh.getName();

    const GLfloat* texCoords = mesh.getTexCoords();
    const GLfloat* normals = mesh.getNormals();
    const GLfloat* positions = mesh.getPositions();
    const GLuint* indexes = mesh.getIndexes();

    _numberOfVertices = mesh.getNumberOfVertices();
    _numberOfNormals = mesh.getNumberOfNormals();
    _numberOfTexCoords = mesh.getNumberOfTexCoords();
    _numberOfTriangles = mesh.getNumberOfTriangles();

    _indexes = new GLuint[3 * _numberOfTriangles];
    _positions = new GLfloat[3 * _numberOfVertices];
    _normals = new GLfloat[3 * _numberOfNormals];
    _texCoords = new GLfloat[2 * _numberOfTexCoords];

    copyIndexes(indexes);
    copyNormals(normals);
    copyPositions(positions);
    copyTexCoords(texCoords);
}

Mesh::~Mesh()
{
    delete[] _texCoords;
    delete[] _normals;
    delete[] _positions;
    delete[] _indexes;
}

Mesh& Mesh::operator=(const Mesh& mesh){

    delete[] _texCoords;
    delete[] _normals;
    delete[] _positions;
    delete[] _indexes;

    _name = mesh.getName();

    const GLfloat* texCoords = mesh.getTexCoords();
    const GLfloat* normals = mesh.getNormals();
    const GLfloat* positions = mesh.getPositions();
    const GLuint* indexes = mesh.getIndexes();

    _numberOfVertices = mesh.getNumberOfVertices();
    _numberOfNormals = mesh.getNumberOfNormals();
    _numberOfTexCoords = mesh.getNumberOfTexCoords();
    _numberOfTriangles = mesh.getNumberOfTriangles();

    _indexes = new GLuint[3 * _numberOfTriangles];
    _positions = new GLfloat[3 * _numberOfVertices];
    _normals = new GLfloat[3 * _numberOfNormals];
    _texCoords = new GLfloat[2 * _numberOfTexCoords];

    copyIndexes(indexes);
    copyNormals(normals);
    copyPositions(positions);
    copyTexCoords(texCoords);

    return *this;
}

void Mesh::setObj(std::vector<glm::core::type::vec3> vertexList, std::vector<glm::core::type::vec3> normalList, std::vector<glm::core::type::vec2> texCoordList, std::vector<GLuint> faceIndexes)
{
    //ensure that memory is freed before any allocation
    delete[] _texCoords;
    delete[] _normals;
    delete[] _positions;
    delete[] _indexes;

    _numberOfTriangles = faceIndexes.size() / 3.0;
    _indexes = new GLuint[3 * _numberOfTriangles];

    for (unsigned int i = 0; i < _numberOfTriangles; i++)
    {
        for (unsigned int j = 0; j < 3; j++)
        {
            _indexes[3 * i + j] = faceIndexes[3 * i + j];
        }
    }

    _numberOfVertices = (GLuint) vertexList.size();
    _positions = new GLfloat[3 * _numberOfVertices];

    for (unsigned int i = 0; i < _numberOfVertices; ++i)
    {
        _positions[3 * i + 0] = vertexList[i].x;
        _positions[3 * i + 1] = vertexList[i].y;
        _positions[3 * i + 2] = vertexList[i].z;
    }

    _numberOfNormals = (GLuint) normalList.size();
    _normals = new GLfloat[3 * _numberOfNormals];

    for (unsigned int i = 0; i < _numberOfNormals; ++i)
    {
        _normals[3 * i + 0] = normalList[i].x;
        _normals[3 * i + 1] = normalList[i].y;
        _normals[3 * i + 2] = normalList[i].z;
    }

    _numberOfTexCoords = (GLuint) texCoordList.size();
    _texCoords = new GLfloat[2 * _numberOfTexCoords];

    for (unsigned int i = 0; i < _numberOfTexCoords; ++i)
    {
        _texCoords[2 * i + 0] = texCoordList[i].s;
        _texCoords[2 * i + 1] = texCoordList[i].t;
    }
}

void Mesh::copyPositions(const GLfloat *positions){
    for(GLuint i = 0; i < 3 * _numberOfVertices; i++){
        if(&positions[i] != 0){
            _positions[i] = positions[i];
        }
    }
}

void Mesh::copyNormals(const GLfloat *normals){
    for(GLuint i = 0; i < 3 * _numberOfNormals; i++){
        if(&normals[i] != 0){
            _normals[i] = normals[i];
        }
    }
}

void Mesh::copyTexCoords(const GLfloat *texCoord){
    for(GLuint i = 0; i < 2 * _numberOfTexCoords; i++){
        if(&texCoord[i] != 0){
            _texCoords[i] = texCoord[i];
        }
    }
}

void Mesh::copyIndexes(const GLuint *indexes){
    for(GLuint i = 0; i < 3 * _numberOfTriangles; i++){
        if(&indexes[i] != 0){
            _indexes[i] = indexes[i];
        }
    }
}

Mesh Mesh::createCube(GLint resolution, const std::string& name){
    Mesh mesh(name);

    std::vector<glm::vec3> vertexList;
    std::vector<glm::vec3> normalList;
    std::vector<glm::vec2> texCoordList;

    std::vector<GLuint> faceIndexes;

    //front
    //0
    vertexList.push_back(glm::vec3(1.0, 1.0, 1.0));
    normalList.push_back(glm::vec3(0.0, 0.0, 1.0));
    texCoordList.push_back(glm::vec2(0.5, 0.3334));
    //1
    vertexList.push_back(glm::vec3(-1.0, 1.0, 1.0));
    normalList.push_back(glm::vec3(0.0, 0.0, 1.0));
    texCoordList.push_back(glm::vec2(0.25, 0.3334));
    //2
    vertexList.push_back(glm::vec3(-1.0, -1.0, 1.0));
    normalList.push_back(glm::vec3(0.0, 0.0, 1.0));
    texCoordList.push_back(glm::vec2(0.25, 0.0));
    //3
    vertexList.push_back(glm::vec3(1.0, -1.0, 1.0));
    normalList.push_back(glm::vec3(0.0, 0.0, 1.0));
    texCoordList.push_back(glm::vec2(0.5, 0.0));

    faceIndexes.push_back(0);
    faceIndexes.push_back(1);
    faceIndexes.push_back(2);
    faceIndexes.push_back(0);
    faceIndexes.push_back(2);
    faceIndexes.push_back(3);

    //back
    //4
    vertexList.push_back(glm::vec3(1.0, 1.0, -1.0));
    normalList.push_back(glm::vec3(0.0, 0.0, -1.0));
    texCoordList.push_back(glm::vec2(0.5, 0.6665));
    //5
    vertexList.push_back(glm::vec3(-1.0, 1.0, -1.0));
    normalList.push_back(glm::vec3(0.0, 0.0, -1.0));
    texCoordList.push_back(glm::vec2(0.25, 0.6665));
    //6
    vertexList.push_back(glm::vec3(-1.0, -1.0, -1.0));
    normalList.push_back(glm::vec3(0.0, 0.0, -1.0));
    texCoordList.push_back(glm::vec2(0.25, 1.0));
    //7
    vertexList.push_back(glm::vec3(1.0, -1.0, -1.0));
    normalList.push_back(glm::vec3(0.0, 0.0, -1.0));
    texCoordList.push_back(glm::vec2(0.5, 1.0));

    faceIndexes.push_back(4);
    faceIndexes.push_back(5);
    faceIndexes.push_back(6);
    faceIndexes.push_back(4);
    faceIndexes.push_back(6);
    faceIndexes.push_back(7);

    //top
    //8
    vertexList.push_back(glm::vec3(1.0, 1.0, -1.0));
    normalList.push_back(glm::vec3(0.0, 1.0, 0.0));
    texCoordList.push_back(glm::vec2(0.5, 0.6665));
    //9
    vertexList.push_back(glm::vec3(-1.0, 1.0, -1.0));
    normalList.push_back(glm::vec3(0.0, 1.0, 0.0));
    texCoordList.push_back(glm::vec2(0.25, 0.6665));
    //10
    vertexList.push_back(glm::vec3(-1.0, 1.0, 1.0));
    normalList.push_back(glm::vec3(0.0, 1.0, 0.0));
    texCoordList.push_back(glm::vec2(0.25, 0.3334));
    //11
    vertexList.push_back(glm::vec3(1.0, 1.0, 1.0));
    normalList.push_back(glm::vec3(0.0, 1.0, 0.0));
    texCoordList.push_back(glm::vec2(0.5, 0.3334));

    faceIndexes.push_back(8);
    faceIndexes.push_back(9);
    faceIndexes.push_back(10);
    faceIndexes.push_back(8);
    faceIndexes.push_back(10);
    faceIndexes.push_back(11);

    //bottom
    //12
    vertexList.push_back(glm::vec3(1.0, -1.0, -1.0));
    normalList.push_back(glm::vec3(0.0, -1.0, 0.0));
    texCoordList.push_back(glm::vec2(0.75, 0.6665));
    //13
    vertexList.push_back(glm::vec3(-1.0, -1.0, -1.0));
    normalList.push_back(glm::vec3(0.0, -1.0, 0.0));
    texCoordList.push_back(glm::vec2(1.0, 0.6665));
    //14
    vertexList.push_back(glm::vec3(-1.0, -1.0, 1.0));
    normalList.push_back(glm::vec3(0.0, -1.0, 0.0));
    texCoordList.push_back(glm::vec2(1.0, 0.3334));
    //15
    vertexList.push_back(glm::vec3(1.0, -1.0, 1.0));
    normalList.push_back(glm::vec3(0.0, -1.0, 0.0));
    texCoordList.push_back(glm::vec2(0.75, 0.3334));

    faceIndexes.push_back(12);
    faceIndexes.push_back(13);
    faceIndexes.push_back(14);
    faceIndexes.push_back(12);
    faceIndexes.push_back(14);
    faceIndexes.push_back(15);

    //right
    //16
    vertexList.push_back(glm::vec3(1.0, 1.0, -1.0));
    normalList.push_back(glm::vec3(1.0, 0.0, 0.0));
    texCoordList.push_back(glm::vec2(0.5, 0.6665));
    //17
    vertexList.push_back(glm::vec3(1.0, 1.0, 1.0));
    normalList.push_back(glm::vec3(1.0, 0.0, 0.0));
    texCoordList.push_back(glm::vec2(0.5, 0.3334));
    //18
    vertexList.push_back(glm::vec3(1.0, -1.0, 1.0));
    normalList.push_back(glm::vec3(1.0, 0.0, 0.0));
    texCoordList.push_back(glm::vec2(0.75, 0.3334));
    //19
    vertexList.push_back(glm::vec3(1.0, -1.0, -1.0));
    normalList.push_back(glm::vec3(1.0, 0.0, 0.0));
    texCoordList.push_back(glm::vec2(0.75, 0.6665));

    faceIndexes.push_back(16);
    faceIndexes.push_back(17);
    faceIndexes.push_back(18);
    faceIndexes.push_back(16);
    faceIndexes.push_back(18);
    faceIndexes.push_back(19);

    //left
    //20
    vertexList.push_back(glm::vec3(-1.0, 1.0, -1.0));
    normalList.push_back(glm::vec3(-1.0, 0.0, 0.0));
    texCoordList.push_back(glm::vec2(0.25, 0.6665));
    //21
    vertexList.push_back(glm::vec3(-1.0, 1.0, 1.0));
    normalList.push_back(glm::vec3(-1.0, 0.0, 0.0));
    texCoordList.push_back(glm::vec2(0.25, 0.3334));
    //22
    vertexList.push_back(glm::vec3(-1.0, -1.0, 1.0));
    normalList.push_back(glm::vec3(-1.0, 0.0, 0.0));
    texCoordList.push_back(glm::vec2(0.0, 0.3334));
    //23
    vertexList.push_back(glm::vec3(-1.0, -1.0, -1.0));
    normalList.push_back(glm::vec3(-1.0, 0.0, 0.0));
    texCoordList.push_back(glm::vec2(0.0, 0.6665));

    faceIndexes.push_back(20);
    faceIndexes.push_back(21);
    faceIndexes.push_back(22);
    faceIndexes.push_back(20);
    faceIndexes.push_back(22);
    faceIndexes.push_back(23);

    for(int subdivide = 0;subdivide < resolution; subdivide++){

        size_t nbVertex = vertexList.size();
        GLuint **mat = new GLuint*[nbVertex];

        for(size_t i=0;i<nbVertex;i++){
            mat[i] = new GLuint[nbVertex];
        }
        for(size_t i = 0; i < nbVertex;i++)
            for(size_t j = 0;j < nbVertex;j++)
                mat[i][j] = -1;


        GLuint stIndex;
        GLuint sndIndex;
        GLuint thIndex;
        GLuint stNewIndex;
        GLuint sndNewIndex;
        GLuint thNewIndex;

        size_t numberOfIndexes = nbVertex - 1;

        size_t nbFace = faceIndexes.size()/3;
        for(size_t i = 0; i < nbFace;i++){

            stIndex = faceIndexes[3*i];
            sndIndex = faceIndexes[3*i + 1];
            thIndex = faceIndexes[3*i + 2];
            if(mat[stIndex][sndIndex] != -1){
                stNewIndex = mat[stIndex][sndIndex];
            } else if(mat[sndIndex][stIndex] != -1){
                stNewIndex = mat[sndIndex][stIndex];
            } else {
                stNewIndex = (GLuint) ++numberOfIndexes;
                mat[stIndex][sndIndex] = stNewIndex;
                glm::vec3 stPosition = vertexList[stIndex];
                glm::vec3 sndPosition = vertexList[sndIndex];
                vertexList.push_back(0.5f*(stPosition + sndPosition));
                glm::vec2 stTex = texCoordList[stIndex];
                glm::vec2 sndTex = texCoordList[sndIndex];
                texCoordList.push_back(0.5f*(stTex + sndTex));
                normalList.push_back(normalList[stIndex]);
            }

            if(mat[thIndex][sndIndex] != -1){
                sndNewIndex = mat[thIndex][sndIndex];
            } else if(mat[sndIndex][thIndex] != -1){
                sndNewIndex = mat[sndIndex][thIndex];
            } else {
                sndNewIndex = (GLuint) ++numberOfIndexes;
                mat[thIndex][sndIndex] = sndNewIndex;
                glm::vec3 thPosition = vertexList[thIndex];
                glm::vec3 sndPosition = vertexList[sndIndex];
                vertexList.push_back(0.5f*(thPosition + sndPosition));
                glm::vec2 thTex = texCoordList[thIndex];
                glm::vec2 sndTex = texCoordList[sndIndex];
                texCoordList.push_back(0.5f*(thTex + sndTex));
                normalList.push_back(normalList[sndIndex]);
            }

            if(mat[stIndex][thIndex] != -1){
                thNewIndex = mat[stIndex][thIndex];
            } else if(mat[thIndex][stIndex] != -1){
                thNewIndex = mat[thIndex][stIndex];
            } else {
                thNewIndex = (GLuint) ++numberOfIndexes;
                mat[stIndex][thIndex] = thNewIndex;
                glm::vec3 stPosition = vertexList[stIndex];
                glm::vec3 thPosition = vertexList[thIndex];
                vertexList.push_back(0.5f*(stPosition + thPosition));
                glm::vec2 stTex = texCoordList[stIndex];
                glm::vec2 thTex = texCoordList[thIndex];
                texCoordList.push_back(0.5f*(stTex + thTex));
                normalList.push_back(normalList[thIndex]);
            }

            faceIndexes[3*i] = stNewIndex;
            faceIndexes[3*i + 1] = sndNewIndex;
            faceIndexes[3*i + 2] = thNewIndex;
            faceIndexes.push_back(stIndex);
            faceIndexes.push_back(stNewIndex);
            faceIndexes.push_back(thNewIndex);
            faceIndexes.push_back(sndIndex);
            faceIndexes.push_back(stNewIndex);
            faceIndexes.push_back(sndNewIndex);
            faceIndexes.push_back(thIndex);
            faceIndexes.push_back(sndNewIndex);
            faceIndexes.push_back(thNewIndex);

        }


        for (int i=0; i < nbVertex; i++)
            delete[] mat[i];
        delete[] mat;

    }
    mesh.setObj(vertexList, normalList, texCoordList, faceIndexes);



    return mesh;
}

Mesh Mesh::createSphere(GLint resolution, const std::string& name){

    Mesh mesh = createCube(resolution, name);

    GLfloat* newNormals = new GLfloat[3 * mesh.getNumberOfNormals()];

    GLfloat* newPositions = new GLfloat[3 * mesh.getNumberOfVertices()];
    const GLfloat* oldPositions = mesh.getPositions();

    for(unsigned int i = 0; i < mesh.getNumberOfVertices();i++){
        GLfloat l = sqrt(oldPositions[3*i]*oldPositions[3*i] + oldPositions[3*i+1]*oldPositions[3*i+1] + oldPositions[3*i+2]*oldPositions[3*i+2]);
        newPositions[3*i] = oldPositions[3*i]/l;
        newNormals[3*i] = oldPositions[3*i];
        newPositions[3*i + 1] = oldPositions[3*i + 1]/l;
        newNormals[3*i + 1] = oldPositions[3*i + 1];
        newPositions[3*i + 2] = oldPositions[3*i + 2]/l;
        newNormals[3*i + 2] = oldPositions[3*i + 2];
    }

    mesh.copyNormals(newNormals);
    mesh.copyPositions(newPositions);

    return mesh;
}

Mesh Mesh::createCylinder(GLint resolution, const std::string& name){

    Mesh mesh = createCube(resolution, name);

    GLfloat* newNormals = new GLfloat[3 * mesh.getNumberOfNormals()];

    GLfloat* newPositions = new GLfloat[3 * mesh.getNumberOfVertices()];
    const GLfloat* oldPositions = mesh.getPositions();

    for(GLuint i = 0; i < mesh.getNumberOfVertices();i++){
        if(oldPositions[3*i + 1] == 1.0 || oldPositions[3*i + 1] == -1.0){
            GLfloat l = sqrt(oldPositions[3*i]*oldPositions[3*i] + oldPositions[3*i+2]*oldPositions[3*i+2]);
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
            GLfloat l = sqrt(oldPositions[3*i]*oldPositions[3*i] + oldPositions[3*i+2]*oldPositions[3*i+2]);
            newPositions[3*i] = oldPositions[3*i]/l;
            newNormals[3*i] = oldPositions[3*i];
            newPositions[3*i + 2] = oldPositions[3*i + 2]/l;
            newNormals[3*i + 2] = oldPositions[3*i + 2];
        }
    }

    mesh.copyNormals(newNormals);
    mesh.copyPositions(newPositions);

    return mesh;
}

