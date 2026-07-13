#include "ui/texturewindow.h"

#include "imgui.h"
#include "nfd.h"
#include "nfd_glfw3.h"

namespace orangutan {

TextureWindow::TextureWindow(TextureManager *texture_manager)
    : texture_manager_(texture_manager) {
  /*
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

    display_irradiance_button_ = new nanogui::Button(this, "Display
    irradiance");
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

    export_button_ = new nanogui::Button(this, "Export to .dds (RGBA32)");
    export_button_->set_callback([&]() {
      // const std::vector<std::pair<std::string, std::string>> file_types{
      //     std::make_pair("dds", "Radiance or Irradiance cube map"),
      //     std::make_pair("png", "Brdf lookup texture")};
      // const std::string filename = nanogui::file_dialog(file_types, true);
      const std::string filename = "./studio.dds";
      const auto last_slash = filename.find_last_of("/\\");
      const auto last_dot = filename.find_last_of('.');
      const std::string path = filename.substr(0, last_slash);
      const std::string name =
          filename.substr(last_slash + 1, last_dot - (last_slash + 1));
      texture_manager_->ExportDdsIbl(name, path);
    });

    export_rgbd_button_ = new nanogui::Button(this, "Export to .dds (RGBD8)");
    export_rgbd_button_->set_callback([&]() {
      // const std::vector<std::pair<std::string, std::string>> file_types{
      // std::make_pair("dds", "Radiance or Irradiance cube map"),
      //    std::make_pair("png", "Brdf lookup texture")};
      // const std::string filename = nanogui::file_dialog(file_types, true);
      const std::string filename = "./studio_rgbd.dds";
      const auto last_slash = filename.find_last_of("/\\");
      const auto last_dot = filename.find_last_of('.');
      const std::string path = filename.substr(0, last_slash);
      const std::string name =
          filename.substr(last_slash + 1, last_dot - (last_slash + 1));
      texture_manager_->ExportDdsRgbdIbl(name, path);
    });

    export_ktx_button_ = new nanogui::Button(this, "Export to .ktx2 (RGBA16)");
    export_ktx_button_->set_callback([&]() {
      // const std::vector<std::pair<std::string, std::string>> file_types{
      // std::make_pair("dds", "Radiance or Irradiance cube map"),
      //    std::make_pair("png", "Brdf lookup texture")};
      // const std::string filename = nanogui::file_dialog(file_types, true);
      const std::string filename = "./studio.ktx2";
      const auto last_slash = filename.find_last_of("/\\");
      const auto last_dot = filename.find_last_of('.');
      const std::string path = filename.substr(0, last_slash);
      const std::string name =
          filename.substr(last_slash + 1, last_dot - (last_slash + 1));
      texture_manager_->ExportKtxIbl(name, path);
    });

    export_ktx_uastc_button_ =
        new nanogui::Button(this, "Export to .ktx2 (UASTC16)");
    export_ktx_uastc_button_->set_callback([&]() {
      // const std::vector<std::pair<std::string, std::string>> file_types{
      // std::make_pair("dds", "Radiance or Irradiance cube map"),
      //    std::make_pair("png", "Brdf lookup texture")};
      // const std::string filename = nanogui::file_dialog(file_types, true);
      // const auto last_slash = filename.find_last_of("/\\");
      // const auto last_dot = filename.find_last_of('.');
      // const std::string path = filename.substr(0, last_slash);
      // const std::string name =
      //    filename.substr(last_slash + 1, last_dot - (last_slash + 1));
      const std::string path = "./output";
      const std::string name = "studio";
      texture_manager_->ExportKtxUastcIbl(name, path);
    });

    Update();
    state_change_signal_uuid_ =
        texture_manager_->GetStateChangeSignal().Connect([&]() { Update(); });
    */
}

void TextureWindow::DrawTextureCombo(
    const std::string &label, const std::vector<std::string> &texture_names,
    const std::string &current_texture_name, unsigned int current_texture_id,
    const std::function<void(const std::string &)> &on_texture_picked) {

  if (current_texture_id != -1) {
    ImGui::Image((ImTextureID)(intptr_t)current_texture_id, ImVec2(128, 128));
  }

  static ImGuiComboFlags flags = 0;
  if (ImGui::BeginCombo(label.c_str(), current_texture_name.c_str(), flags)) {
    for (int n = 0; n < texture_names.size(); n++) {
      const bool is_selected = current_texture_name == texture_names[n];
      if (ImGui::Selectable(texture_names[n].c_str(), is_selected)) {
        on_texture_picked(texture_names[n]);
      }

      // Set the initial focus when opening the combo (scrolling + keyboard
      // navigation focus)
      if (is_selected) {
        ImGui::SetItemDefaultFocus();
      }
    }
    ImGui::EndCombo();
  }
}

void TextureWindow::OpenLoadDialog(
    const std::string &label, const nfdu8filteritem_t *filters,
    unsigned int filterCount, GLFWwindow *window,
    const std::function<void(const std::string &, const std::string &)>
        &on_path_picked) {
  if (ImGui::Button(label.c_str())) {
    nfdu8char_t *out_path;
    nfdopendialogu8args_t args = {0};
    args.filterList = filters;
    args.filterCount = filterCount;
    if (!NFD_GetNativeWindowFromGLFWWindow(window, &args.parentWindow)) {
      printf("NFD_GetNativeWindowFromGLFWWindow failed\n");
    }
    nfdresult_t result = NFD_OpenDialogU8_With(&out_path, &args);
    if (result == NFD_OKAY) {
      const std::string file_path = out_path;
      const auto last_slash = file_path.find_last_of('/');
      const auto last_dot = file_path.find_last_of('.');
      const std::string base_name =
          file_path.substr(last_slash + 1, last_dot - (last_slash + 1));
      on_path_picked(file_path, base_name);

      NFD_FreePathU8(out_path);
    } else if (result == NFD_CANCEL) {
      puts("User pressed cancel.");
    } else {
      printf("Error: %s\n", NFD_GetError());
    }
  }
}

void TextureWindow::OpenSaveDialog(
    const std::string &label, const nfdu8filteritem_t *filters,
    unsigned int filterCount, GLFWwindow *window,
    const std::function<void(const std::string &, const std::string &)>
        &on_path_picked) {
  if (ImGui::Button(label.c_str())) {
    nfdu8char_t *out_path;
    nfdsavedialogu8args_t args = {0};
    args.filterList = filters;
    args.filterCount = filterCount;
    if (!NFD_GetNativeWindowFromGLFWWindow(window, &args.parentWindow)) {
      printf("NFD_GetNativeWindowFromGLFWWindow failed\n");
    }
    nfdresult_t result = NFD_SaveDialogU8_With(&out_path, &args);
    if (result == NFD_OKAY) {
      const std::string file_path = out_path;
      const auto last_slash = file_path.find_last_of("/\\");
      const auto last_dot = file_path.find_last_of('.');
      const std::string path = file_path.substr(0, last_slash);
      const std::string base_name =
          file_path.substr(last_slash + 1, last_dot - (last_slash + 1));
      on_path_picked(path, base_name);

      NFD_FreePathU8(out_path);
    } else if (result == NFD_CANCEL) {
      puts("User pressed cancel.");
    } else {
      printf("Error: %s\n", NFD_GetError());
    }
  }
}

void TextureWindow::Draw(GLFWwindow *window) {
  ImGui::Begin("Textures");

  std::vector<std::string> texture_names;
  texture_manager_->GetTextureNames(texture_names);

  std::string current_texture_name = texture_manager_->GetCurrentTextureName();
  unsigned int current_texture_id =
      texture_manager_->GetTextureId(current_texture_name);

  DrawTextureCombo("textures", texture_names, current_texture_name,
                   current_texture_id, [&](const std::string &name) {
                     texture_manager_->SetCurrentTexture(name);
                   });

  std::vector<std::string> cube_texture_names;
  texture_manager_->GetCubeTextureNames(cube_texture_names);

  std::string current_cube_texture_name =
      texture_manager_->GetCurrentCubeTextureName();

  DrawTextureCombo("cube textures", cube_texture_names,
                   current_cube_texture_name, -1, [&](const std::string &name) {
                     texture_manager_->SetCurrentCubeTexture(name);
                   });

  std::vector<std::string> ibl_names;
  texture_manager_->GetIblNames(ibl_names);

  std::string current_ibl_name = texture_manager_->GetCurrentIblName();

  DrawTextureCombo(
      "ibls", ibl_names, current_ibl_name, -1,
      [&](const std::string &name) { texture_manager_->SetCurrentIbl(name); });

  nfdu8filteritem_t hdrFilters[1] = {{"hdr file", "hdr"}};
  OpenLoadDialog(
      "Load .hdr", hdrFilters, 1, window,
      [&](const std::string &file_path, const std::string &base_name) {
        texture_manager_->LoadHdrIbl(base_name, file_path);
      });

  nfdu8filteritem_t ddsFilters[2] = {{"Radiance or Irradiance cube map", "dds"},
                                     {"Brdff lookup texture", "png"}};
  OpenLoadDialog(
      "Load .dds", ddsFilters, 2, window,
      [&](const std::string &file_path, const std::string &base_name) {
        const auto last_slash = file_path.find_last_of("/\\");
        const std::string base_path = file_path.substr(0, last_slash);
        texture_manager_->LoadDdsIbl(base_name, base_path);
      });

  OpenSaveDialog("Export to .dds (RGBA32)", ddsFilters, 2, window,
                 [&](const std::string &path, const std::string &base_name) {
                   texture_manager_->ExportDdsIbl(path, base_name);
                 });

  OpenSaveDialog("Export to .dds (RGBD8)", ddsFilters, 2, window,
                 [&](const std::string &path, const std::string &base_name) {
                   texture_manager_->ExportDdsRgbdIbl(path, base_name);
                 });

  nfdu8filteritem_t ktxFilters[1] = {{"ktx2 cube map", "ktx2"}};
  OpenSaveDialog("Export to .ktx2 (RGBDA16)", ktxFilters, 1, window,
                 [&](const std::string &path, const std::string &base_name) {
                   texture_manager_->ExportKtxIbl(path, base_name);
                 });

  OpenSaveDialog("Export to .ktx2 (UASTC16)", ktxFilters, 1, window,
                 [&](const std::string &path, const std::string &base_name) {
                   texture_manager_->ExportKtxUastcIbl(path, base_name);
                 });
  ImGui::End();
}

/*void TextureWindow::Update() {
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
    cube_texture_combo_box_->set_selected_index(current_cube_texture_iterator
  - cube_texture_names_.begin());
                                                }

  texture_manager_->GetIblNames(ibl_names_);
  ibl_combo_box_->set_items(ibl_names_);

  if (!ibl_names_.empty()) {
    auto current_ibl_iterator =
        std::find(ibl_names_.begin(), ibl_names_.end(),
                  texture_manager_->GetCurrentIblName());
    ibl_combo_box_->set_selected_index(current_ibl_iterator -
                                       ibl_names_.begin());
  }*/

} // namespace orangutan
