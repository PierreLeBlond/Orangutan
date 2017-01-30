#include "app/nanogui/tool.h"
#include <nanovg.h>

Tool::Tool(nanogui::Widget *parent, const std::string& label) :
    nanogui::Window(parent, label)
{
}

Tool::~Tool()
{
}

void Tool::setNVGContext(NVGcontext *context)
{
    _context = context;
}

void Tool::addSliders(nanogui::Widget *widget,
                      const std::string &name,
                      const glm::vec3 &value,
                      const glm::vec3 &minValue,
                      const glm::vec3 &maxValue,
                      const std::vector<
                      std::function<void(float)>> &callbacks)
{
    new nanogui::Label(widget, name);

    addSlider(widget, "x", value.x,
               minValue.x, maxValue.x,
               callbacks.at(0));

    addSlider(widget, "y", value.y,
               minValue.y, maxValue.y,
               callbacks.at(1));

    addSlider(widget, "z", value.z,
               minValue.z, maxValue.z,
               callbacks.at(2));
}

void Tool::addTextures(nanogui::Widget *widget,
                       const std::string &name,
                       const std::vector<std::string> &textures,
                       const std::function<void(int)> &callback)
{
    std::vector<std::pair<int, std::string>> images;

    for(const auto& name : textures)
    {
        int id = nvgCreateImage(_context, name.c_str(), 0);
        images.push_back(std::make_pair(id, name));
    }

    nanogui::PopupButton *popupButton = new nanogui::PopupButton(widget, name);
    popupButton->setSide(nanogui::Popup::Left);
    nanogui::Popup *popup = popupButton->popup();
    nanogui::VScrollPanel *vScrollPanel = new nanogui::VScrollPanel(popup);
    nanogui::ImagePanel *imagePanel = new nanogui::ImagePanel(vScrollPanel);
    imagePanel->setImages(images);

    imagePanel->setCallback(callback);
}
