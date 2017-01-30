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

    if(_object)
    {
        initShader(this);
        _uniformPanel = new nanogui::Widget(this);
        _uniformPanel->setLayout(new nanogui::BoxLayout(nanogui::Orientation::Vertical,
                                                nanogui::Alignment::Middle, 0, 5));
        initMaterials(_uniformPanel, _object->getShaderMaterial(),
                      _object->getShaderStrategy()->getShaderProgram()->getUniformsName());
    }
}

void ObjectTool::initShader(nanogui::Widget *widget)
{
    new nanogui::Label(widget, "Shader", "sans-bold");

    const std::vector<
        std::shared_ptr<
        const ShaderStrategy>>& shaderStrategies = _assetsStorage->getShaderStrategies();

    std::vector<std::string> names;

    for(int i = 0; i < shaderStrategies.size(); ++i)
    {
        names.push_back(shaderStrategies[i]->getName());
    }

    nanogui::ComboBox* comboBox = new nanogui::ComboBox(widget, names);
    comboBox->setSide(nanogui::Popup::Left);
    comboBox->setCallback([&](int id){
                         setShaderStrategy(id);
                         updateMaterials();
                         });
}

void ObjectTool::removeChildrenWidget(nanogui::Widget *widget)
{
    const std::vector<Widget *> children = widget->children();
    for(auto &child : children)
    {
        removeChildrenWidget(child);
        widget->removeChild(child);
    }
}

void ObjectTool::updateMaterials()
{
    removeChildrenWidget(_uniformPanel);
    //removeChild(_uniformPanel);
    //_uniformPanel = new nanogui::Widget(this);
    //_uniformPanel->setLayout(new nanogui::BoxLayout(nanogui::Orientation::Vertical,
                                                    //nanogui::Alignment::Middle, 0, 5));

    initMaterials(_uniformPanel, _object->getShaderMaterial(),
                  _object->getShaderStrategy()->getShaderProgram()->getUniformsName());

    if(_context)
    {
        performLayout(_context);
        performLayout(_context);
    }
}

void ObjectTool::initMaterials(nanogui::Widget *widget,
                               const Material& material,
                               const std::vector<std::string> &names)
{
    int uniformsCount = 0;

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

    std::cout << "Found " << uniformsCount << " uniforms for " << material.getName() << "." << std::endl;

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
                            names,
                            [&](int i){
                            _object->setTexture(texture.first, _assetsStorage->getTexture(i));
                            });
            }
        }
    }

    for(const auto& subMaterial : material.getMaterials())
    {
        initMaterials(widget, subMaterial, names);
    }
}

