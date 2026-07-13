#include "manager/texturemanager.h"

#include <memory>
#include <utility>

#include "texture/basisutexturefactory.h"
#include "texture/ktxtexturefactory.h"
#include "texture/texturefactory.h"

namespace orangutan {

TextureManager::TextureManager(Universe *universe, Scene *scene)
    : universe_(universe), scene_(scene) {
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
    std::vector<std::string> &texture_names) const {
  texture_names = universe_->get_texture_library().GetNames();
}

unsigned int TextureManager::GetTextureId(std::string texture_name) const {
  return universe_->get_texture_library()
      .GetItemByName(texture_name)
      ->getHandle()
      .getId();
}

void TextureManager::GetCubeTextureNames(
    std::vector<std::string> &cube_texture_names) const {
  cube_texture_names = universe_->get_cube_texture_library().GetNames();
}

unsigned int
TextureManager::GetCubeTextureId(std::string cube_texture_name) const {
  return universe_->get_cube_texture_library()
      .GetItemByName(cube_texture_name)
      ->getHandle()
      .getId();
}

void TextureManager::GetIblNames(std::vector<std::string> &ibl_names) const {
  ibl_names = universe_->get_ibl_library().GetNames();
}

const std::string &TextureManager::GetCurrentTextureName() const {
  return current_texture_name_;
}

const std::string &TextureManager::GetCurrentCubeTextureName() const {
  return current_cube_texture_name_;
}

const std::string &TextureManager::GetCurrentIblName() const {
  return current_ibl_name_;
}

void TextureManager::SetCurrentTexture(const std::string &name,
                                       const std::string &source_handler_uuid) {
  current_texture_name_ = name;
  state_change_signal_.Emit(source_handler_uuid);
}

void TextureManager::SetCurrentCubeTexture(
    const std::string &name, const std::string &source_handler_uuid) {
  current_cube_texture_name_ = name;
  state_change_signal_.Emit(source_handler_uuid);
}

void TextureManager::SetCurrentIbl(const std::string &name,
                                   const std::string &source_handler_uuid) {
  current_ibl_name_ = name;
  scene_->SetIbl(universe_->get_ibl_library().GetItemByName(current_ibl_name_));
  state_change_signal_.Emit(source_handler_uuid);
}

void TextureManager::LoadDdsIbl(const std::string &name,
                                const std::string &path,
                                const std::string &source_handler_uuid) {
  std::string irradiance_filename = path + "/" + name + "_irradiance.dds";
  std::string radiance_filename = path + "/" + name + "_radiance.dds";

  auto ibl = TextureFactory::ImportIBLFromDds(name, irradiance_filename,
                                              radiance_filename);
  universe_->AddIbl(std::move(ibl));

  scene_->SetIbl(universe_->get_ibl_library().GetItemByName(name));
  SetCurrentIbl(name);
  state_change_signal_.Emit(source_handler_uuid);
}

void TextureManager::LoadHdrIbl(const std::string &name,
                                const std::string &filename,
                                const std::string &source_handler_uuid) {
  auto ibl = TextureFactory::ImportIBLFromHdr(name, filename);
  universe_->AddIbl(std::move(ibl));

  scene_->SetIbl(universe_->get_ibl_library().GetItemByName(name));
  SetCurrentIbl(name);
  state_change_signal_.Emit(source_handler_uuid);
}

void TextureManager::ExportDdsIbl(const std::string &path,
                                  const std::string &base_name) {
  TextureFactory::ExportIbl(
      path, base_name,
      *universe_->get_ibl_library().GetItemByName(current_ibl_name_));
}

void TextureManager::ExportDdsRgbdIbl(const std::string &path,
                                      const std::string &base_name) {
  bool convert_to_rgbd = true;

  TextureFactory::ExportIbl(
      path, base_name,
      *universe_->get_ibl_library().GetItemByName(current_ibl_name_),
      convert_to_rgbd);
}

void TextureManager::ExportKtxIbl(const std::string &path,
                                  const std::string &base_name) {
  KtxTextureFactory::ExportIbl(
      path, base_name,
      *universe_->get_ibl_library().GetItemByName(current_ibl_name_),
      *universe_->get_texture_library().GetItemByName("brdf"));
}

void TextureManager::ExportKtxUastcIbl(const std::string &path,
                                       const std::string &base_name) {
  BasisUTextureFactory::ExportIbl(
      path, base_name,
      *universe_->get_ibl_library().GetItemByName(current_ibl_name_),
      *universe_->get_texture_library().GetItemByName("brdf"));
}
Signal<> &TextureManager::GetStateChangeSignal() {
  return state_change_signal_;
}

} // namespace orangutan
