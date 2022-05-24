#include "manager/texturemanager.h"

#include <memory>
#include <utility>

#include "nanogui/common.h"
#include "texture/texturefactory.h"

namespace orangutan {

TextureManager::TextureManager(Universe* universe, Canvas* canvas, Scene* scene)
    : universe_(universe), canvas_(canvas), scene_(scene) {
  // There should always be a current item, unless the library is empty
  auto texture_names = universe_->get_texture_library().GetNames();
  SetCurrentTexture(!texture_names.empty() ? texture_names.front() : "");

  auto cube_texture_names = universe_->get_cube_texture_library().GetNames();
  SetCurrentCubeTexture(!cube_texture_names.empty() ? cube_texture_names.front()
                                                    : "");

  auto ibl_names = universe_->get_ibl_library().GetNames();
  SetCurrentIbl(!ibl_names.empty() ? ibl_names.front() : "");
}

void TextureManager::GetTextureNames(
    std::vector<std::string>& texture_names) const {
  texture_names = universe_->get_texture_library().GetNames();
}

void TextureManager::GetCubeTextureNames(
    std::vector<std::string>& cube_texture_names) const {
  cube_texture_names = universe_->get_cube_texture_library().GetNames();
}

void TextureManager::GetIblNames(std::vector<std::string>& ibl_names) const {
  ibl_names = universe_->get_ibl_library().GetNames();
}

const std::string& TextureManager::GetCurrentTextureName() const {
  return current_texture_name_;
}

const std::string& TextureManager::GetCurrentCubeTextureName() const {
  return current_cube_texture_name_;
}

const std::string& TextureManager::GetCurrentIblName() const {
  return current_ibl_name_;
}

void TextureManager::SetCurrentTexture(const std::string& name,
                                       const std::string& source_handler_uuid) {
  current_texture_name_ = name;
  state_change_signal_.Emit(source_handler_uuid);
}

void TextureManager::SetCurrentCubeTexture(
    const std::string& name, const std::string& source_handler_uuid) {
  current_cube_texture_name_ = name;
  state_change_signal_.Emit(source_handler_uuid);
}

void TextureManager::SetCurrentIbl(const std::string& name,
                                   const std::string& source_handler_uuid) {
  current_ibl_name_ = name;
  scene_->SetIbl(universe_->get_ibl_library().GetItemByName(current_ibl_name_));
  state_change_signal_.Emit(source_handler_uuid);
}

void TextureManager::ShowCurrentTexture() {
  if (!display_texture_handler_id_.empty()) {
    HideCurrentTexture();
  }
  display_texture_handler_id_ = canvas_->get_after_draw_signal().Connect([&]() {
    debug_.DisplayTexture(
        *universe_->get_texture_library().GetItemByName(current_texture_name_));
  });
}

void TextureManager::ShowCurrentCubeTexture() {
  if (!display_cube_texture_handler_id_.empty()) {
    HideCurrentCubeTexture();
  }
  display_cube_texture_handler_id_ =
      canvas_->get_after_draw_signal().Connect([&]() {
        debug_.DisplayCubeTexture(
            *universe_->get_cube_texture_library().GetItemByName(
                current_cube_texture_name_),
            canvas_->width(), canvas_->height());
      });
}

void TextureManager::ShowCurrentIblRadiance() {
  if (!display_ibl_radiance_handler_id_.empty()) {
    HideCurrentIblRadiance();
  }
  display_ibl_radiance_handler_id_ =
      canvas_->get_after_draw_signal().Connect([&]() {
        debug_.DisplayCubeTexture(*universe_->get_ibl_library()
                                       .GetItemByName(current_ibl_name_)
                                       ->radiance.get(),
                                  canvas_->width(), canvas_->height());
      });
}

void TextureManager::ShowCurrentIblIrradiance() {
  if (!display_ibl_irradiance_handler_id_.empty()) {
    HideCurrentIblIrradiance();
  }
  display_ibl_irradiance_handler_id_ =
      canvas_->get_after_draw_signal().Connect([&]() {
        debug_.DisplayCubeTexture(*universe_->get_ibl_library()
                                       .GetItemByName(current_ibl_name_)
                                       ->irradiance.get(),
                                  canvas_->width(), canvas_->height());
      });
}

void TextureManager::HideCurrentTexture() {
  canvas_->get_after_draw_signal().Disconnect(display_texture_handler_id_);
  display_texture_handler_id_.clear();
}

void TextureManager::HideCurrentCubeTexture() {
  canvas_->get_after_draw_signal().Disconnect(display_cube_texture_handler_id_);
  display_cube_texture_handler_id_.clear();
}

void TextureManager::HideCurrentIblRadiance() {
  canvas_->get_after_draw_signal().Disconnect(display_ibl_radiance_handler_id_);
  display_ibl_radiance_handler_id_.clear();
}

void TextureManager::HideCurrentIblIrradiance() {
  canvas_->get_after_draw_signal().Disconnect(
      display_ibl_irradiance_handler_id_);
  display_ibl_irradiance_handler_id_.clear();
}

void TextureManager::LoadDdsIbl(const std::string& name,
                                const std::string& path,
                                const std::string& source_handler_uuid) {
  std::string irradiance_filename = path + "/" + name + "_irradiance.dds";
  std::string radiance_filename = path + "/" + name + "_radiance.dds";

  auto ibl = TextureFactory::ImportIBLFromDds(name, irradiance_filename,
                                              radiance_filename);
  universe_->AddIbl(std::move(ibl));

  scene_->SetIbl(universe_->get_ibl_library().GetItemByName(name));
  SetCurrentIbl(name);
  state_change_signal_.Emit(source_handler_uuid);
}

void TextureManager::LoadHdrIbl(const std::string& name,
                                const std::string& filename,
                                const std::string& source_handler_uuid) {
  auto ibl = TextureFactory::ImportIBLFromHdr(name, filename);
  universe_->AddIbl(std::move(ibl));

  scene_->SetIbl(universe_->get_ibl_library().GetItemByName(name));
  SetCurrentIbl(name);
  state_change_signal_.Emit(source_handler_uuid);
}

void TextureManager::ExportDdsIbl(const std::string& name,
                                  const std::string& path,
                                  const std::string& source_handler_uuid) {
  std::string irradiance_filename = path + "/" + name + "_irradiance.dds";
  std::string radiance_filename = path + "/" + name + "_radiance.dds";

  TextureFactory::ExportIbl(
      name, irradiance_filename, radiance_filename,
      *universe_->get_ibl_library().GetItemByName(current_ibl_name_));
}

void TextureManager::ExportDdsRgbdIbl(const std::string& name,
                                      const std::string& path,
                                      const std::string& source_handler_uuid) {
  std::string irradiance_filename = path + "/" + name + "_rgbd_irradiance.dds";
  std::string radiance_filename = path + "/" + name + "_rgbd_radiance.dds";

  bool convert_to_rgbd = true;

  TextureFactory::ExportIbl(
      name, irradiance_filename, radiance_filename,
      *universe_->get_ibl_library().GetItemByName(current_ibl_name_),
      convert_to_rgbd);
}

Signal<>& TextureManager::GetStateChangeSignal() {
  return state_change_signal_;
}

}  // namespace orangutan
