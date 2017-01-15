#include "app/nanogui/objecttool.h"

#include <nanogui/layout.h>
#include <nanogui/label.h>
#include <nanogui/combobox.h>

ObjectTool::ObjectTool(nanogui::Widget* parent, const std::string& label) :
    nanogui::Window(parent, label)
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

    /* No need to store a pointer, the data structure will be automatically
       freed when the parent window is deleted */
    new nanogui::Label(this, "Materials", "sans-bold");

    const std::vector<std::shared_ptr<const ShaderStrategy>>& materials = _assetsStorage->getShaderStrategies();

    std::vector<std::string> names;

    for(int i = 0; i < materials.size(); ++i)
    {
        names.push_back(materials[i]->getName());
    }

    nanogui::ComboBox* comboBox = new nanogui::ComboBox(this, names);
    comboBox->setSide(nanogui::Popup::Left);
    comboBox->setCallback([&](int id){
                         setMaterial(id);
                         });
}
