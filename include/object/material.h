#pragma once

#include "core/texture.h"
#include "object/asset.h"
#include "object/uniform.h"

#include "glm/glm.hpp"

#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtx/transform.hpp"
#include "glm/gtx/transform2.hpp"
#include "glm/gtc/type_ptr.hpp"

#include <iostream>
#include <vector>
#include <map>
#include <fstream>
#include <memory>

class Material : public Asset
{
public:

                                    Material(const std::string &name = "untitled");

    template<class T>
        bool                        createUniform(const std::string& name,
                                                  const T& value = T(),
                                                  const T& minValue = T(),
                                                  const T& maxValue = T())
        {
            Uniform<T> u(name, value, minValue, maxValue);
            return addUniform(u);//implement move semantic
        }


    void                            addMaterial(Material m);
    const std::vector<Material>&    getMaterials() const;

    template <class T>
    bool                            addUniform(const Uniform<T> &u,
                                               std::vector<Uniform<T>> &uniforms)
    {
        unsigned int i = 0;
        bool result = true;
        while(i < uniforms.size() && !result)
        {
            const Uniform<T> &uniform = uniforms[i];
            if(uniform.getName() == u.getName())
            {
                result = false;
                std::cout << "Error, uniform with name " << u.getName() << " already exist" << std::endl;
            }
            ++i;
        }
        if(result)
        {
            std::cout << "pushing uniform " << u.getName() << std::endl;
            uniforms.push_back(u);
        }
        return result;
    }

    bool                            addUniform(const Uniform<float> &u);
    bool                            addUniform(const Uniform<int> &u);
    bool                            addUniform(const Uniform<unsigned int> &u);
    bool                            addUniform(const Uniform<bool> &u);
    bool                            addUniform(const Uniform<glm::vec3> &u);
    bool                            addUniform(const Uniform<glm::vec4> &u);
    bool                            addUniform(const Uniform<glm::mat3> &u);
    bool                            addUniform(const Uniform<glm::mat4> &u);

    bool                            addTexture(const std::string& name,
                                               std::shared_ptr<Texture> texture);

    template <class T>
    bool                            setUniform(const std::string& name,
                                               const T& value,
                                               std::vector<Uniform<T>> &uniforms)
    {
        bool result = false;
        unsigned int i = 0;
        while(i < uniforms.size() && !result)
        {
            Uniform<T> &uniform = uniforms.at(i);
            if(uniform.getName() == name)
            {
                result = true;
                uniform.setValue(value);
            }
            ++i;
        }
        i = 0;
        while(i < _materials.size() && !result)
        {
            result = _materials[i].setUniform(name, value);
            ++i;
        }
        return result;
    }

    bool                            setUniform(const std::string& name,
                                                   float value);
    bool                            setUniform(const std::string& name,
                                               int value);
    bool                            setUniform(const std::string& name,
                                               unsigned int value);
    bool                            setUniform(const std::string& name,
                                               bool value);
    bool                            setUniform(const std::string& name,
                                               const glm::vec3& value);
    bool                            setUniform(const std::string& name,
                                               const glm::vec4& value);
    bool                            setUniform(const std::string& name,
                                               const glm::mat3& value);
    bool                            setUniform(const std::string& name,
                                               const glm::mat4& value);

    bool                            setTexture(const std::string& name,
                                               std::shared_ptr<Texture> texture);

    template <class T>
    bool                            getUniform(const std::string& name,
                                               T& value,
                                               const std::vector<Uniform<T>> &uniforms) const
    {
        bool result = false;
        unsigned int i = 0;
        while(i < uniforms.size() && !result)
        {
            const Uniform<T> &uniform = uniforms.at(i);
            if(uniform.getName() == name)
            {
                result = true;
                value = uniform.getValue();
            }
            ++i;
        }
        i = 0;
        while(i < _materials.size() && !result)
        {
            result = _materials[i].getUniform(name, value);
            ++i;
        }
        return result;
    }

    bool                            getUniform(const std::string& name,
                                               float &value) const;
    bool                            getUniform(const std::string& name,
                                               int &value) const;
    bool                            getUniform(const std::string& name,
                                               unsigned int &value) const;
    bool                            getUniform(const std::string& name,
                                               bool &value) const;
    bool                            getUniform(const std::string& name,
                                               glm::vec3 &value) const;
    bool                            getUniform(const std::string& name,
                                               glm::vec4 &value) const;
    bool                            getUniform(const std::string& name,
                                               glm::mat3 &value) const;
    bool                            getUniform(const std::string& name,
                                               glm::mat4 &value) const;

    bool                            getTexture(const std::string& name,
                                               std::shared_ptr<
                                               Texture> & texture) const;

    const std::vector<
        Uniform<float>>&            get1fUniforms() const;
    const std::vector<
        Uniform<int>>&              get1iUniforms() const;
    const std::vector<
        Uniform<unsigned int>>&     get1uiUniforms() const;
    const std::vector<
        Uniform<bool>>&             get1bUniforms() const;
    const std::vector<
        Uniform<glm::vec3>>&        get3fUniforms() const;
    const std::vector<
        Uniform<glm::vec4>>&        get4fUniforms() const;
    const std::vector<
        Uniform<glm::mat3>>&        get3x3fUniforms() const;
    const std::vector<
        Uniform<glm::mat4>>&        get4x4fUniforms() const;

    const std::map<std::string,
        std::shared_ptr<Texture>>&  getTextures() const;
private:

    std::vector<Material>                           _materials;

    std::vector<Uniform<float>>                     _1funiforms;
    std::vector<Uniform<int>>                       _1iuniforms;
    std::vector<Uniform<unsigned int>>              _1uiuniforms;
    std::vector<Uniform<bool>>                      _1buniforms;
    std::vector<Uniform<glm::vec3>>                 _3funiforms;
    std::vector<Uniform<glm::vec4>>                 _4funiforms;
    std::vector<Uniform<glm::mat3>>                 _3x3funiforms;
    std::vector<Uniform<glm::mat4>>                 _4x4funiforms;

    std::map<std::string, std::shared_ptr<Texture>> _textures;
};

