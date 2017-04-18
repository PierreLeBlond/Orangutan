#include "presenter/renderableobjectpresenter.h"

RenderableObjectPresenter::RenderableObjectPresenter(std::shared_ptr<Presenter> parent) :
    Presenter(parent)
{}

void RenderableObjectPresenter::init()
{
    _view->setFixedSize(Eigen::Vector2i(300, 600));
    _view->setPosition(Eigen::Vector2i(900, 0));

    _view->setLayout(new nanogui::GroupLayout());

    update();
}

void RenderableObjectPresenter::update()
{
    _view->clear();

    std::shared_ptr<Scene> scene = _universe->getSceneLibrary().getCurrentItem();
    std::shared_ptr<RenderableObject> object = scene->getRenderableObjectLibrary().getCurrentItem();

    const std::vector<
            std::shared_ptr<
            ShaderStrategy>>& shaderStrategies = _universe->getShaderStrategyLibrary().getItems();

    std::vector<std::string> names;

    int shaderStrategyId = 0;

    for(unsigned int i = 0; i < shaderStrategies.size(); ++i)
    {
        names.push_back(shaderStrategies[i]->getName());
        if(shaderStrategies[i] == object->getShaderStrategy())
            shaderStrategyId = i;
    }

    _view->addComboBox(_view.get(), nanogui::Popup::Left, "Shader", names, shaderStrategyId,
                [&, object](int id){
                std::shared_ptr<ShaderStrategy> strategy;
                if(_universe->getShaderStrategyLibrary().getItemById(id, strategy))
                {
                object->setShaderStrategy(strategy);
                notifyChangeToModel();
                }
                });

    const Material& material = object->getShaderMaterial();
    names = object->getShaderStrategy()->getShaderWrapper()->getUniformsName();

    updateMaterial(material, names);
}

void RenderableObjectPresenter::setView(nanogui::ref<View> view)
{
    _view = view;
}

void RenderableObjectPresenter::updateMaterial(const Material &material,
                                               const std::vector<std::string> &names)
{
    std::shared_ptr<Scene> scene = _universe->getSceneLibrary().getCurrentItem();
    std::shared_ptr<RenderableObject> object = scene->getRenderableObjectLibrary().getCurrentItem();

    unsigned int uniformsCount = 0;

    for(const auto& uniform : material.get1fUniforms())
    {
        if(std::find(names.begin(), names.end(), uniform.getName()) != names.end())
            uniformsCount++;
    }

    for(const auto& uniform : material.get1iUniforms())
    {
        if(std::find(names.begin(), names.end(), uniform.getName()) != names.end())
            uniformsCount++;
    }

    for(const auto& uniform : material.get3fUniforms())
    {
        if(std::find(names.begin(), names.end(), uniform.getName()) != names.end())
            uniformsCount++;
    }

    for(const auto& texture : material.getTextures())
    {
        if(std::find(names.begin(), names.end(), texture.first) != names.end())
            uniformsCount++;
    }

    for(const auto& texture : material.getCubeTextures())
    {
        if(std::find(names.begin(), names.end(), texture.first) != names.end())
            uniformsCount++;
    }

    if(uniformsCount > 0)
    {
        new nanogui::Label(_view.get(), material.getName(), "sans-bold");

        for(const auto& uniform : material.get1fUniforms())
        {
            if(std::find(names.begin(), names.end(), uniform.getName()) != names.end())
            {
                _view->addSlider(_view.get(),
                          uniform.getName(),
                          uniform.getValue(),
                          uniform.getMinValue(),
                          uniform.getMaxValue(),
                          [&, object](float res){
                          object->setUniform(uniform.getName(), res);
                          });
            }
        }

        for(const auto& uniform : material.get1iUniforms())
        {
            if(std::find(names.begin(), names.end(), uniform.getName()) != names.end())
            {
                _view->addSlider(_view.get(),
                          uniform.getName(),
                          uniform.getValue(),
                          uniform.getMinValue(),
                          uniform.getMaxValue(),
                          [&, object](float res){
                          object->setUniform(uniform.getName(), (int) res);
                          });
            }
        }

        for(const auto& uniform : material.get3fUniforms())
        {
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

            if(std::find(names.begin(), names.end(), uniform.getName()) != names.end())
            {
                _view->addSlider(_view.get(),
                          uniform.getName(),
                          uniform.getValue().x,
                          uniform.getMinValue().x,
                          uniform.getMaxValue().x,
                          [&, object](float res){
                          object->setUniform(uniform.getName(),
                                              glm::vec3(res,
                                                        res,
                                                        res));
                          });
            }
        }

        std::vector<std::string> textureNames;
        for(const auto& texture : _universe->getTextureLibrary().getItems())
        {
            textureNames.push_back(texture->getPath());
        }

        for(const auto& texture : material.getTextures())
        {
            if(std::find(names.begin(), names.end(), texture.first) != names.end())
            {
                _view->addTextures(_view.get(),
                            getContext(),
                            texture.first,
                            textureNames,
                            [&, object, texture](int i){
                            std::shared_ptr<DDTexture> ddtexture;
                            if(_universe->getTextureLibrary().getItemById(i, ddtexture))
                                object->setTexture(texture.first, ddtexture);
                            });
            }
        }

        std::vector<std::string> cubeTextureNames;
        for(const auto& texture : _universe->getCubeTextureLibrary().getItems())
        {
            cubeTextureNames.push_back(texture->getPath());
        }

        for(const auto& texture : material.getCubeTextures())
        {
            if(std::find(names.begin(), names.end(), texture.first) != names.end())
            {
                _view->addTextures(_view.get(),
                            getContext(),
                            texture.first,
                            cubeTextureNames,
                            [&, object](int i){
                            std::shared_ptr<CubeTexture> texture;
                            if(_universe->getCubeTextureLibrary().getItemById(i, texture))
                                object->setCubeTexture(texture->getName(), texture);
                            });
            }
        }
    }

    for(const auto& subMaterial : material.getMaterials())
    {
        updateMaterial(subMaterial, names);
    }
}
