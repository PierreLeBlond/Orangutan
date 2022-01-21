#pragma once

#include <vector>

#include "core/vertex/vao.h"
#include "object/mesh.h"
#include "object/object.h"
#include "object/shadermaterial.h"
#include "util/util.h"

class RenderableObject : public Object, public ShaderMaterialable {
 public:
  RenderableObject(const std::string& name = "RenderableObject");

  void initVertexArrayObject();

  void fillInVBO();

  void draw(const glm::mat4& viewMatrix, const glm::mat4& projectionMatrix,
            const std::vector<std::shared_ptr<Light>>& lights) override;

  void setMesh(std::shared_ptr<const Mesh> mesh);

  [[nodiscard]] const ShaderMaterial& getShaderMaterial() const;
  void setShaderMaterial(const ShaderMaterial& shadermaterial);

  [[nodiscard]] unsigned int getIdOfPositionArray() const;
  [[nodiscard]] unsigned int getIdOfIndexArray() const;
  [[nodiscard]] unsigned int getIdOfNormalArray() const;
  [[nodiscard]] unsigned int getIdOfTexCoordArray() const;

  [[nodiscard]] const Vao& getVao() const;

  [[nodiscard]] std::shared_ptr<const ShaderStrategy> getShaderStrategy()
      const override;
  void setShaderStrategy(
      std::shared_ptr<const ShaderStrategy> shaderStrategy) override;

  bool setTexture(const std::string& name, std::shared_ptr<DDTexture> texture);
  bool setCubeTexture(const std::string& name,
                      std::shared_ptr<CubeTexture> texture);

  template <class T>
  bool addUniform(Uniform<T> u) {
    return _shaderMaterial.addUniform(u);
  }

  template <class T>
  bool setUniform(const std::string& name, const T& value) {
    return _shaderMaterial.setUniform(name, value);
  }

  template <class T>
  bool getUniform(const std::string& name, T& value) const {
    return _shaderMaterial.getUniform(name, value);
  }

  void addMaterial(Material m);

 private:
  std::shared_ptr<const Mesh> _mesh;

  ShaderMaterial _shaderMaterial;

  unsigned int _idOfPositionArray;
  unsigned int _idOfIndexArray;
  unsigned int _idOfNormalArray;
  unsigned int _idOfTexCoordArray;

  Vao _vao;
};
