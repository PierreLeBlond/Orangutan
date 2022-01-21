#include "object/material.h"

Material::Material(const std::string &name) : Asset(name)
{}

void Material::addMaterial(Material m)
{
    _materials.push_back(m);
}

const std::vector<Material>& Material::getMaterials() const
{
    return _materials;
}

bool Material::addUniform(const Uniform<float> &u)
{
    return addUniform(u, _1funiforms);
}

bool Material::addUniform(const Uniform<int> &u)
{
    return addUniform(u, _1iuniforms);
}

bool Material::addUniform(const Uniform<unsigned int> &u)
{
    return addUniform(u, _1uiuniforms);
}

bool Material::addUniform(const Uniform<bool> &u)
{
    return addUniform(u, _1buniforms);
}

bool Material::addUniform(const Uniform<glm::vec3> &u)
{
    return addUniform(u, _3funiforms);
}

bool Material::addUniform(const Uniform<glm::vec4> &u)
{
    return addUniform(u, _4funiforms);
}

bool Material::addUniform(const Uniform<glm::mat3> &u)
{
    return addUniform(u, _3x3funiforms);
}

bool Material::addUniform(const Uniform<glm::mat4> &u)
{
    return addUniform(u, _4x4funiforms);
}

bool Material::addTexture(const std::string& name,
                          std::shared_ptr<DDTexture> texture)
{
    bool b = false;
    if(_textures.find(name) == _textures.end())
    {
        _textures.insert(std::make_pair(name, texture));
        b = true;
    }
    return b;
}

bool Material::addCubeTexture(const std::string& name,
                          std::shared_ptr<CubeTexture> texture)
{
    bool b = false;
    if(_cubeTextures.find(name) == _cubeTextures.end())
    {
        _cubeTextures.insert(std::make_pair(name, texture));
        b = true;
    }
    return b;
}

bool Material::setUniform(const std::string& name, float value)
{
    return setUniform(name, value, _1funiforms);
}

bool Material::setUniform(const std::string& name, int value)
{
    return setUniform(name, value, _1iuniforms);
}

bool Material::setUniform(const std::string& name, unsigned int value)
{
    return setUniform(name, value, _1uiuniforms);
}

bool Material::setUniform(const std::string& name, bool value)
{
    return setUniform(name, value, _1buniforms);
}

bool Material::setUniform(const std::string& name, const glm::vec3 &value)
{
    return setUniform(name, value, _3funiforms);
}

bool Material::setUniform(const std::string& name, const glm::vec4 &value)
{
    return setUniform(name, value, _4funiforms);
}

bool Material::setUniform(const std::string& name, const glm::mat3 &value)
{
    return setUniform(name, value, _3x3funiforms);
}

bool Material::setUniform(const std::string& name, const glm::mat4 &value)
{
    return setUniform(name, value, _4x4funiforms);
}

bool Material::setTexture(const std::string& name,
                          std::shared_ptr<DDTexture> texture)
{
    bool b = false;
    auto it = _textures.find(name);
    if(it != _textures.end())
    {
        b = true;
        it->second = texture;
    }

    if(!b)
    {
        for(auto& material : _materials)
        {
            b = material.setTexture(name, texture);
        }
    }
    return b;
}

bool Material::setCubeTexture(const std::string& name,
                          std::shared_ptr<CubeTexture> texture)
{
    bool b = false;
    auto it = _cubeTextures.find(name);
    if(it != _cubeTextures.end())
    {
        b = true;
        it->second = texture;
    }

    if(!b)
    {
        for(auto& material : _materials)
        {
            b = material.setCubeTexture(name, texture);
        }
    }
    return b;
}

bool Material::getUniform(const std::string& name, float &value) const
{
    return getUniform(name, value, _1funiforms);
}

bool Material::getUniform(const std::string& name, int &value) const
{
    return getUniform(name, value, _1iuniforms);
}

bool Material::getUniform(const std::string& name, unsigned int &value) const
{
    return getUniform(name, value, _1uiuniforms);
}

bool Material::getUniform(const std::string& name, bool &value) const
{
    return getUniform(name, value, _1buniforms);
}

bool Material::getUniform(const std::string& name, glm::vec3 &value) const
{
    return getUniform(name, value, _3funiforms);
}

bool Material::getUniform(const std::string& name, glm::vec4 &value) const
{
    return getUniform(name, value, _4funiforms);
}

bool Material::getUniform(const std::string& name, glm::mat3 &value) const
{
    return getUniform(name, value, _3x3funiforms);
}

bool Material::getUniform(const std::string& name, glm::mat4 &value) const
{
    return getUniform(name, value, _4x4funiforms);
}

bool Material::getTexture(const std::string& name, std::shared_ptr<DDTexture>& texture) const
{
    bool b = false;
    auto it = _textures.find(name);
    if(it != _textures.end())
    {
        b = true;
        texture = it->second;
    }

    if(!b)
    {
        for(auto& material : _materials)
        {
            b = material.getTexture(name, texture);
        }
    }

    return b;
}

bool Material::getCubeTexture(const std::string& name, std::shared_ptr<CubeTexture>& texture) const
{
    bool b = false;
    auto it = _cubeTextures.find(name);
    if(it != _cubeTextures.end())
    {
        b = true;
        texture = it->second;
    }

    if(!b)
    {
        for(auto& material : _materials)
        {
            b = material.getCubeTexture(name, texture);
        }
    }

    return b;
}

const std::vector<Uniform<float>>& Material::get1fUniforms() const
{
    return _1funiforms;
}

const std::vector<Uniform<int>>& Material::get1iUniforms() const
{
    return _1iuniforms;
}

const std::vector<Uniform<unsigned int>>& Material::get1uiUniforms() const
{
    return _1uiuniforms;
}

const std::vector<Uniform<bool>>& Material::get1bUniforms() const
{
    return _1buniforms;
}

const std::vector<Uniform<glm::vec3>>& Material::get3fUniforms() const
{
    return _3funiforms;
}

const std::vector<Uniform<glm::vec4>>& Material::get4fUniforms() const
{
    return _4funiforms;
}

const std::vector<Uniform<glm::mat3>>& Material::get3x3fUniforms() const
{
    return _3x3funiforms;
}

const std::vector<Uniform<glm::mat4>>& Material::get4x4fUniforms() const
{
    return _4x4funiforms;
}

const std::map<std::string,
      std::shared_ptr<DDTexture>>& Material::getTextures() const
{
    return _textures;
}

const std::map<std::string,
      std::shared_ptr<CubeTexture>>& Material::getCubeTextures() const
{
    return _cubeTextures;
}
