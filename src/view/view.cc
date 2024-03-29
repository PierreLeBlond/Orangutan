#include "view/view.h"
#include <nanovg.h>

View::View(nanogui::Widget *parent, const std::string& label) :
    nanogui::Window(parent, label) {
}

void View::clear() {
    const std::vector<Widget *> childs = children();
    for(auto &child : childs)
    {
        remove_child(child);
    }
}

void View::addSliders(nanogui::Widget *widget,
                      const std::string &name,
                      const glm::vec3 &value,
                      const glm::vec3 &minValue,
                      const glm::vec3 &maxValue,
                      const std::vector<
                      std::function<void(float)>> &callbacks) {
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

void View::addTextures(nanogui::Widget *widget,
                       NVGcontext* context,
                       const std::string &name,
                       const std::vector<std::string> &textures,
                       const std::function<void(int)> &callback) {
    std::vector<std::pair<int, std::string>> images;

    for(const auto& path : textures) {
        int id = nvgCreateImage(context, path.c_str(), 0);
        images.push_back(std::make_pair(id, path));
    }

    nanogui::PopupButton *popupButton = new nanogui::PopupButton(widget, name);
    popupButton->set_side(nanogui::Popup::Left);
    nanogui::Popup *popup = popupButton->popup();
    nanogui::VScrollPanel *vScrollPanel = new nanogui::VScrollPanel(popup);
    nanogui::ImagePanel *imagePanel = new nanogui::ImagePanel(vScrollPanel);
    imagePanel->set_images(images);
    popup->set_fixed_size(nanogui::Vector2i(245, 150));

    imagePanel->set_callback(callback);
}

void View::addComboBox(nanogui::Widget *widget,
                       nanogui::Popup::Side side,
                       const std::string &name,
                       const std::vector<std::string> &items,
                       int id,
                       const std::function<void(int)> &callback) {
    //new nanogui::Label(widget, name, "sans-bold");

    nanogui::ComboBox* comboBox = new nanogui::ComboBox(widget, items);
    comboBox->set_side(side);
    comboBox->set_callback(callback);
    comboBox->set_selected_index(id);
}

