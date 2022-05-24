#include "ui/window.h"

#include <nanovg.h>

#include "nanogui/vector.h"

namespace orangutan {

Window::Window(nanogui::Widget *parent, const std::string &label)
    : nanogui::Window(parent, label),
      left_(0),
      top_(0),
      right_(-1),
      bottom_(-1) {}

void Window::clear() {
  const std::vector<Widget *> childs = children();
  for (auto &child : childs) {
    remove_child(child);
  }
}

void Window::Resize(unsigned int parent_width, unsigned int parent_height) {
  int x = right_ > 0 ? parent_width - (right_ + size().x()) : left_;
  int y = bottom_ > 0 ? parent_height - (bottom_ + size().y()) : top_;
  set_position(nanogui::Vector2i(x, y));
}

void Window::addSliders(
    nanogui::Widget *widget, const std::string &name, const glm::vec3 &value,
    const glm::vec3 &minValue, const glm::vec3 &maxValue,
    const std::vector<std::function<void(float)>> &callbacks) {
  new nanogui::Label(widget, name);

  addSlider(widget, "x", value.x, minValue.x, maxValue.x, callbacks.at(0));

  addSlider(widget, "y", value.y, minValue.y, maxValue.y, callbacks.at(1));

  addSlider(widget, "z", value.z, minValue.z, maxValue.z, callbacks.at(2));
}

void Window::addTextures(nanogui::Widget *widget, NVGcontext *context,
                         const std::string &name,
                         const std::vector<std::string> &textures,
                         const std::function<void(int)> &callback) {
  std::vector<std::pair<int, std::string>> images;

  for (const auto &path : textures) {
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

nanogui::ComboBox *Window::addComboBox(
    nanogui::Widget *widget, nanogui::Popup::Side side, const std::string &name,
    const std::vector<std::string> &items, int id,
    const std::function<void(int)> &callback) {
  new nanogui::Label(widget, name, "sans-bold");

  nanogui::ComboBox *comboBox = new nanogui::ComboBox(widget, items);
  comboBox->set_side(side);
  comboBox->set_callback(callback);
  if (id > 0) {
    comboBox->set_selected_index(id);
  }
}

}  // namespace orangutan

