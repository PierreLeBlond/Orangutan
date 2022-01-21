#ifndef VIEW_H
#define VIEW_H

#include <nanogui/combobox.h>
#include <nanogui/imagepanel.h>
#include <nanogui/label.h>
#include <nanogui/layout.h>
#include <nanogui/popupbutton.h>
#include <nanogui/screen.h>
#include <nanogui/slider.h>
#include <nanogui/textbox.h>
#include <nanogui/vscrollpanel.h>
#include <nanogui/window.h>

#include <iostream>
#include <memory>

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "glm/gtx/transform.hpp"
#include "glm/gtx/transform2.hpp"

class View : public nanogui::Window {
 public:
  View(nanogui::Widget *parent = nullptr,
       const std::string &label = "Unknow window");

  void clear();

  template <class T>
  void addSlider(nanogui::Widget *widget, const std::string &name,
                 const T &value, const T &minValue, const T &maxValue,
                 const std::function<void(float)> &callback) {
    nanogui::Widget *panel = new nanogui::Widget(widget);
    panel->set_layout(new nanogui::BoxLayout(nanogui::Orientation::Horizontal,
                                             nanogui::Alignment::Middle, 0, 5));

    new nanogui::Label(panel, name);

    nanogui::Slider *slider = new nanogui::Slider(panel);
    // slider->setHighlightedRange(std::make_pair(uniform.getMinValue(),
    // uniform.getMaxValue()));
    T range = maxValue - minValue;
    slider->set_value((float)(value - minValue) / range);
    slider->set_fixed_width(100);

    nanogui::TextBox *textBox = new nanogui::TextBox(panel);
    textBox->set_fixed_size(nanogui::Vector2i(50, 25));
    textBox->set_value(std::to_string(value).substr(0, 4));
    textBox->set_font_size(20);
    textBox->set_alignment(nanogui::TextBox::Alignment::Right);

    slider->set_callback([&, textBox, range, callback](float res) {
      res = res * range + minValue;
      callback(res);
      textBox->set_value(std::to_string(res).substr(0, 4));
    });
  }

  void addSliders(nanogui::Widget *widget, const std::string &name,
                  const glm::vec3 &value, const glm::vec3 &minValue,
                  const glm::vec3 &maxValue,
                  const std::vector<std::function<void(float)>> &callbacks);

  void addComboBox(nanogui::Widget *widget, nanogui::Popup::Side side,
                   const std::string &name,
                   const std::vector<std::string> &items, int id,
                   const std::function<void(int)> &callback);

  void addTextures(nanogui::Widget *widget, NVGcontext *context,
                   const std::string &name,
                   const std::vector<std::string> &textures,
                   const std::function<void(int)> &callback);
};

#endif  // VIEW_H
