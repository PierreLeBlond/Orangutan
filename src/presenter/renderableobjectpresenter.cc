#include "presenter/renderableobjectpresenter.h"

RenderableObjectPresenter::RenderableObjectPresenter(
    std::shared_ptr<Universe> universe, NVGcontext* context, View* view)
    : Presenter(std::move(universe), context), view_(view) {}

void RenderableObjectPresenter::Init() {
  view_->set_layout(new nanogui::GroupLayout());

  Update();
}

void RenderableObjectPresenter::Update() {
  view_->clear();

  std::shared_ptr<RenderableObject> object =
      get_universe()->get_renderable_object_library().get_current_item();

  const std::vector<std::shared_ptr<ShaderStrategy>>& shaderStrategies =
      get_universe()->get_shader_strategy_library().get_items();

  std::vector<std::string> names;

  int shaderStrategyId = 0;

  for (unsigned int i = 0; i < shaderStrategies.size(); ++i) {
    names.push_back(shaderStrategies[i]->getName());
    if (shaderStrategies[i] == object->getShaderStrategy())
      shaderStrategyId = i;
  }

  view_->addComboBox(
      view_, nanogui::Popup::Left, "Shader", names, shaderStrategyId,
      [&, object](int id) {
        std::shared_ptr<ShaderStrategy> strategy;
        get_universe()->get_shader_strategy_library().GetItemById(id, strategy);
        object->setShaderStrategy(strategy);
      });

  const Material& material = object->getShaderMaterial();
  names = object->getShaderStrategy()->get_shader_wrapper()->getUniformsName();

  UpdateMaterial(material, names);
}

void RenderableObjectPresenter::UpdateMaterial(
    const Material& material, const std::vector<std::string>& names) {
  std::shared_ptr<RenderableObject> object =
      get_universe()->get_renderable_object_library().get_current_item();

  unsigned int uniformsCount = 0;

  for (const auto& uniform : material.get1fUniforms()) {
    if (std::find(names.begin(), names.end(), uniform.getName()) != names.end())
      uniformsCount++;
  }

  for (const auto& uniform : material.get1iUniforms()) {
    if (std::find(names.begin(), names.end(), uniform.getName()) != names.end())
      uniformsCount++;
  }

  for (const auto& uniform : material.get3fUniforms()) {
    if (std::find(names.begin(), names.end(), uniform.getName()) != names.end())
      uniformsCount++;
  }

  for (const auto& texture : material.getTextures()) {
    if (std::find(names.begin(), names.end(), texture.first) != names.end())
      uniformsCount++;
  }

  for (const auto& texture : material.getCubeTextures()) {
    if (std::find(names.begin(), names.end(), texture.first) != names.end())
      uniformsCount++;
  }

  if (uniformsCount > 0) {
    new nanogui::Label(view_, material.getName(), "sans-bold");

    for (const auto& uniform : material.get1fUniforms()) {
      if (std::find(names.begin(), names.end(), uniform.getName()) !=
          names.end()) {
        view_->addSlider(view_, uniform.getName(), uniform.getValue(),
                         uniform.getMinValue(), uniform.getMaxValue(),
                         [&, object](float res) {
                           object->setUniform(uniform.getName(), res);
                         });
      }
    }

    for (const auto& uniform : material.get1iUniforms()) {
      if (std::find(names.begin(), names.end(), uniform.getName()) !=
          names.end()) {
        view_->addSlider(view_, uniform.getName(), uniform.getValue(),
                         uniform.getMinValue(), uniform.getMaxValue(),
                         [&, object](float res) {
                           object->setUniform(uniform.getName(), (int)res);
                         });
      }
    }

    for (const auto& uniform : material.get3fUniforms()) {
      /*std::vector<std::function<void(float)>> callbacks;
        callbacks.push_back([&](float res){
        _object->setUniform(uniform.getName(),
        glm::vec3(res,
        uniform.getValue().y,
        uniform.getValue().z));
        });

        callbacks.push_back([&](float res){
        _object->setUniform(uniform.getName(),
        glm::vec3(uniform.getValue().x,
        res,
        uniform.getValue().z));
        });

        callbacks.push_back([&](float res){
        _object->setUniform(uniform.getName(),
        glm::vec3(uniform.getValue().x,
        uniform.getValue().y,
        res));
        });*/

      if (std::find(names.begin(), names.end(), uniform.getName()) !=
          names.end()) {
        view_->addSlider(view_, uniform.getName(), uniform.getValue().x,
                         uniform.getMinValue().x, uniform.getMaxValue().x,
                         [&, object](float res) {
                           object->setUniform(uniform.getName(),
                                              glm::vec3(res, res, res));
                         });
      }
    }

    std::vector<std::string> textureNames;
    for (const auto& texture :
         get_universe()->get_texture_library().get_items()) {
      textureNames.push_back(texture->getPath());
    }

    for (const auto& texture : material.getTextures()) {
      if (std::find(names.begin(), names.end(), texture.first) != names.end()) {
        view_->addTextures(view_, get_context(), texture.first, textureNames,
                           [&, object, texture](int i) {
                             std::shared_ptr<DDTexture> ddtexture;
                             get_universe()->get_texture_library().GetItemById(
                                 i, ddtexture);
                             object->setTexture(texture.first, ddtexture);
                           });
      }
    }

    std::vector<std::string> cubeTextureNames;
    for (const auto& texture :
         get_universe()->get_cube_texture_library().get_items()) {
      cubeTextureNames.push_back(texture->getPath());
    }

    for (const auto& texture : material.getCubeTextures()) {
      if (std::find(names.begin(), names.end(), texture.first) != names.end()) {
        view_->addTextures(
            view_, get_context(), texture.first, cubeTextureNames,
            [&, object](int i) {
              std::shared_ptr<CubeTexture> texture;
              get_universe()->get_cube_texture_library().GetItemById(i,
                                                                     texture);
              object->setCubeTexture(texture->getName(), texture);
            });
      }
    }
  }

  for (const auto& subMaterial : material.getMaterials()) {
    UpdateMaterial(subMaterial, names);
  }
}
