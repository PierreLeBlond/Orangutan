#ifndef ORANGUTAN_UI_TEXTURE_WINDOW_H
#define ORANGUTAN_UI_TEXTURE_WINDOW_H

#include "manager/texturemanager.h"
#include "presenter/presenter.h"
#include "ui/window.h"

namespace orangutan {

class TextureWindow : public Window {
 public:
  TextureWindow(nanogui::Widget *parent, const std::string &label,
                TextureManager *texture_manager);
  void Update();

 private:
  TextureManager *texture_manager_;

  std::string state_change_signal_uuid_;

  std::vector<std::string> texture_names_;
  nanogui::ComboBox *texture_combo_box_;
  nanogui::Button *display_texture_button_;

  std::vector<std::string> cube_texture_names_;
  nanogui::ComboBox *cube_texture_combo_box_;
  nanogui::Button *display_cube_texture_button_;

  std::vector<std::string> ibl_names_;
  nanogui::ComboBox *ibl_combo_box_;
  nanogui::Button *display_irradiance_button_;
  nanogui::Button *display_radiance_button_;
  nanogui::Button *load_hdr_button_;
  nanogui::Button *load_dds_button_;
  nanogui::Button *export_button_;
  nanogui::Button *export_rgbd_button_;
};

}  // namespace orangutan

#endif  // ORANGUTAN_UI_TEXTURE_WINDOW_H
