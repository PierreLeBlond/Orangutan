#include "app/nanogui/objecttool.h"

#include <nanogui/layout.h>
#include <nanogui/label.h>
#include <nanogui/combobox.h>
#include <nanogui/slider.h>
#include <nanogui/textbox.h>

ObjectTool::ObjectTool(nanogui::Widget* parent, const std::string& label) :
    Tool(parent, label)
{
}

ObjectTool::~ObjectTool()
{
}

void ObjectTool::init()
{
    setFixedSize(Eigen::Vector2i(300, 600));
    setPosition(Eigen::Vector2i(900, 0));
    setLayout(new nanogui::GroupLayout());

    update();
}

void ObjectTool::initShader(nanogui::Widget *widget)
{
    if(_object)
    {
        const std::vector<
            std::shared_ptr<
            const ShaderStrategy>>& shaderStrategies = _assetsStorage->getShaderStrategies();

        std::vector<std::string> names;

        int shaderStrategyId = 0;

        for(unsigned int i = 0; i < shaderStrategies.size(); ++i)
        {
            names.push_back(shaderStrategies[i]->getName());
            if(shaderStrategies[i] == _object->getShaderStrategy())
                shaderStrategyId = i;
        }

        addComboBox(widget, nanogui::Popup::Left, "Shader", names, shaderStrategyId,
                    [&](int id){
                    _object->setShaderStrategy(_assetsStorage->getShaderStrategy(id));
                    update();
                    });
    }
}

void ObjectTool::update()
{
    removeChildrenWidget(this);

    initShader(this);
    initMaterials(this, _object->getShaderMaterial(),
                  _object->getShaderStrategy()->getShaderWrapper()->getUniformsName());

    if(_screen)
    {
        _screen->performLayout();
    }
}

void ObjectTool::initMaterials(nanogui::Widget *widget,
                               const Material& material,
                               const std::vector<std::string> &names)
{
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
        new nanogui::Label(widget, material.getName(), "sans-bold");

        for(const auto& uniform : material.get1fUniforms())
        {
            if(std::find(names.begin(), names.end(), uniform.getName()) != names.end())
            {
                addSlider(widget,
                          uniform.getName(),
                          uniform.getValue(),
                          uniform.getMinValue(),
                          uniform.getMaxValue(),
                          [&](float res){
                          _object->setUniform(uniform.getName(), res);
                          });
            }
        }

        for(const auto& uniform : material.get1iUniforms())
        {
            if(std::find(names.begin(), names.end(), uniform.getName()) != names.end())
            {
                addSlider(widget,
                          uniform.getName(),
                          uniform.getValue(),
                          uniform.getMinValue(),
                          uniform.getMaxValue(),
                          [&](float res){
                          _object->setUniform(uniform.getName(), (int) res);
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
                addSlider(widget,
                          uniform.getName(),
                          uniform.getValue().x,
                          uniform.getMinValue().x,
                          uniform.getMaxValue().x,
                          [&](float res){
                          _object->setUniform(uniform.getName(),
                                              glm::vec3(res,
                                                        res,
                                                        res));
                          });
            }
        }

        std::vector<std::string> textureNames;
        for(const auto& texture : _assetsStorage->getTextures())
        {
            textureNames.push_back(texture->getPath());
        }

        for(const auto& texture : material.getTextures())
        {
            if(std::find(names.begin(), names.end(), texture.first) != names.end())
            {
                addTextures(widget,
                            texture.first,
                            textureNames,
                            [&](int i){
                            _object->setTexture(texture.first, _assetsStorage->getTexture(i));
                            });
            }
        }

        std::vector<std::string> cubeTextureNames;
        for(const auto& texture : _assetsStorage->getCubeMapTextures())
        {
            cubeTextureNames.push_back(texture->getPath());
        }

        for(const auto& texture : material.getCubeTextures())
        {
            if(std::find(names.begin(), names.end(), texture.first) != names.end())
            {
                addTextures(widget,
                            texture.first,
                            cubeTextureNames,
                            [&](int i){
                            _object->setCubeTexture(texture.first, _assetsStorage->getCubeMapTexture(i));
                            });
            }
        }
    }

    for(const auto& subMaterial : material.getMaterials())
    {
        initMaterials(widget, subMaterial, names);
    }
}

void ObjectTool::setCurrentObject(std::shared_ptr<RenderableObject> object)
{
    _object = object;
}

