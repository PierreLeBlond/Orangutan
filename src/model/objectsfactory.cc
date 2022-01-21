#include "model/objectsfactory.h"

#include <iostream>

ObjectsFactory ObjectsFactory::_instance;

ObjectsFactory& ObjectsFactory::instance() { return _instance; }

std::shared_ptr<RenderableObject> ObjectsFactory::createRenderableObject(
    const Universe& universe, const std::string& name, const Material& material,
    int meshId, int shaderStrategyId, int textureId, int cubeMapId) {
  std::shared_ptr<RenderableObject> object =
      std::make_shared<RenderableObject>(name);

  if (meshId > -1) {
    std::shared_ptr<Mesh> mesh;
    universe.get_mesh_library().GetItemById(meshId, mesh);
    object->setMesh(mesh);
  }

  object->addMaterial(material);

  if (shaderStrategyId > -1) {
    std::shared_ptr<ShaderStrategy> shaderStrategy;
    universe.get_shader_strategy_library().GetItemById(shaderStrategyId,
                                                       shaderStrategy);
    if (shaderStrategy.get() == nullptr) {
      std::cerr << "Shader strategy is invalid" << std::endl;
    }
    object->setShaderStrategy(shaderStrategy);
  }

  if (textureId > -1) {
    std::shared_ptr<DDTexture> texture;
    universe.get_texture_library().GetItemById(textureId, texture);
    object->setTexture("colorMap", texture);
  }

  if (cubeMapId > -1) {
    std::shared_ptr<CubeTexture> cubeTexture;
    universe.get_cube_texture_library().GetItemById(cubeMapId, cubeTexture);
    object->setCubeTexture("cubeMap", cubeTexture);
  }

  return object;
}

