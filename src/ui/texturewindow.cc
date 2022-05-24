#include "ui/texturewindow.h"

#include <memory>

#include "nanogui/popup.h"

namespace orangutan {

TextureWindow::TextureWindow(nanogui::Widget *parent, const std::string &label,
                             TextureManager *texture_manager)
    : Window(parent, label), texture_manager_(texture_manager) {
  set_layout(new nanogui::GroupLayout());

  // Doing all initialization work within constructor, but we might considere
  // implementing the answer : https://abseil.io/tips/42

  texture_combo_box_ = new nanogui::ComboBox(this);
  texture_combo_box_->set_side(nanogui::Popup::Left);
  texture_combo_box_->set_callback([&](unsigned int index) {
    texture_manager_->SetCurrentTexture(texture_names_[index],
                                        state_change_signal_uuid_);
  });

  display_texture_button_ = new nanogui::Button(this, "Display");
  display_texture_button_->set_flags(nanogui::Button::ToggleButton);
  display_texture_button_->set_change_callback([&](bool state) {
    if (state) {
      texture_manager_->ShowCurrentTexture();
    } else {
      texture_manager_->HideCurrentTexture();
    }
  });

  cube_texture_combo_box_ = new nanogui::ComboBox(this);
  cube_texture_combo_box_->set_side(nanogui::Popup::Left);
  cube_texture_combo_box_->set_callback([&](unsigned int index) {
    texture_manager_->SetCurrentCubeTexture(cube_texture_names_[index],
                                            state_change_signal_uuid_);
  });

  display_cube_texture_button_ = new nanogui::Button(this, "Display");
  display_cube_texture_button_->set_flags(nanogui::Button::ToggleButton);
  display_cube_texture_button_->set_change_callback([&](bool state) {
    if (state) {
      texture_manager_->ShowCurrentCubeTexture();
    } else {
      texture_manager_->HideCurrentCubeTexture();
    }
  });

  ibl_combo_box_ = new nanogui::ComboBox(this);
  ibl_combo_box_->set_side(nanogui::Popup::Left);
  ibl_combo_box_->set_callback([&](unsigned int index) {
    texture_manager_->SetCurrentIbl(ibl_names_[index],
                                    state_change_signal_uuid_);
  });

  display_irradiance_button_ = new nanogui::Button(this, "Display irradiance");
  display_irradiance_button_->set_flags(nanogui::Button::ToggleButton);
  display_irradiance_button_->set_change_callback([&](bool state) {
    if (state) {
      texture_manager_->ShowCurrentIblIrradiance();
    } else {
      texture_manager_->HideCurrentIblIrradiance();
    }
  });

  display_radiance_button_ = new nanogui::Button(this, "Display radiance");
  display_radiance_button_->set_flags(nanogui::Button::ToggleButton);
  display_radiance_button_->set_change_callback([&](bool state) {
    if (state) {
      texture_manager_->ShowCurrentIblRadiance();
    } else {
      texture_manager_->HideCurrentIblRadiance();
    }
  });

  load_hdr_button_ = new nanogui::Button(this, "Load .hdr");
  load_hdr_button_->set_callback([&]() {
    const std::vector<std::pair<std::string, std::string>> file_types{
        std::make_pair(
            "hdr", "High dynamic range equirectangular environment texture")};
    const std::string filename = nanogui::file_dialog(file_types, true);
    const auto last_slash = filename.find_last_of('/');
    const auto last_dot = filename.find_last_of('.');
    const std::string name =
        filename.substr(last_slash + 1, last_dot - (last_slash + 1));
    texture_manager_->LoadHdrIbl(name, filename);
  });

  load_dds_button_ = new nanogui::Button(this, "Load .dds");
  load_dds_button_->set_callback([&]() {
    const std::vector<std::pair<std::string, std::string>> file_types{
        std::make_pair("dds", "Radiance or Irradiance cube map"),
        std::make_pair("png", "Brdf lookup texture")};

    const std::string filename = nanogui::file_dialog(file_types, true);
    const auto last_underscore = filename.find_last_of('_');
    const auto last_slash = filename.find_last_of("/\\");
    const std::string path = filename.substr(0, last_slash);
    const std::string name =
        filename.substr(last_slash + 1, last_underscore - (last_slash + 1));
    texture_manager_->LoadDdsIbl(name, path);
  });

  export_button_ = new nanogui::Button(this, "Export");
  export_button_->set_callback([&]() {
    const std::vector<std::pair<std::string, std::string>> file_types{
        std::make_pair("dds", "Radiance or Irradiance cube map"),
        std::make_pair("png", "Brdf lookup texture")};
    const std::string filename = nanogui::file_dialog(file_types, true);
    const auto last_slash = filename.find_last_of("/\\");
    const auto last_dot = filename.find_last_of('.');
    const std::string path = filename.substr(0, last_slash);
    const std::string name =
        filename.substr(last_slash + 1, last_dot - (last_slash + 1));
    texture_manager_->ExportDdsIbl(name, path);
  });

  export_rgbd_button_ = new nanogui::Button(this, "Export RGBD");
  export_rgbd_button_->set_callback([&]() {
    const std::vector<std::pair<std::string, std::string>> file_types{
        std::make_pair("dds", "Radiance or Irradiance cube map"),
        std::make_pair("png", "Brdf lookup texture")};
    const std::string filename = nanogui::file_dialog(file_types, true);
    const auto last_slash = filename.find_last_of("/\\");
    const auto last_dot = filename.find_last_of('.');
    const std::string path = filename.substr(0, last_slash);
    const std::string name =
        filename.substr(last_slash + 1, last_dot - (last_slash + 1));
    texture_manager_->ExportDdsRgbdIbl(name, path);
  });

  Update();
  state_change_signal_uuid_ =
      texture_manager_->GetStateChangeSignal().Connect([&]() { Update(); });
}

void TextureWindow::Update() {
  texture_manager_->GetTextureNames(texture_names_);
  texture_combo_box_->set_items(texture_names_);
  if (!texture_names_.empty()) {
    auto current_texture_iterator =
        std::find(texture_names_.begin(), texture_names_.end(),
                  texture_manager_->GetCurrentTextureName());
    texture_combo_box_->set_selected_index(current_texture_iterator -
                                           texture_names_.begin());
  }

  texture_manager_->GetCubeTextureNames(cube_texture_names_);
  cube_texture_combo_box_->set_items(cube_texture_names_);
  if (!cube_texture_names_.empty()) {
    auto current_cube_texture_iterator =
        std::find(cube_texture_names_.begin(), cube_texture_names_.end(),
                  texture_manager_->GetCurrentCubeTextureName());
    cube_texture_combo_box_->set_selected_index(current_cube_texture_iterator -
                                                cube_texture_names_.begin());
  }

  texture_manager_->GetIblNames(ibl_names_);
  ibl_combo_box_->set_items(ibl_names_);

  if (!ibl_names_.empty()) {
    auto current_ibl_iterator =
        std::find(ibl_names_.begin(), ibl_names_.end(),
                  texture_manager_->GetCurrentIblName());
    ibl_combo_box_->set_selected_index(current_ibl_iterator -
                                       ibl_names_.begin());
  }

  screen()->perform_layout();
}

}  // namespace orangutan
