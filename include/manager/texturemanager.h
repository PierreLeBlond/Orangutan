#ifndef ORANGUTAN_MANAGER_TEXTURE_MANAGER_H
#define ORANGUTAN_MANAGER_TEXTURE_MANAGER_H

#include "debug/visualdebugger.h"
#include "model/universe.h"
#include "patterns/observer/signal.h"

namespace orangutan {

class TextureManager {
public:
  TextureManager(Universe *universe, Scene *scene);

  void GetTextureNames(std::vector<std::string> &texture_names) const;
  unsigned int GetTextureId(std::string texture_name) const;
  void GetCubeTextureNames(std::vector<std::string> &cube_texture_names) const;
  unsigned int GetCubeTextureId(std::string cube_texture_name) const;
  void GetIblNames(std::vector<std::string> &ibl_names) const;
  [[nodiscard]] const std::string &GetCurrentTextureName() const;
  [[nodiscard]] const std::string &GetCurrentCubeTextureName() const;
  [[nodiscard]] const std::string &GetCurrentIblName() const;

  void SetCurrentTexture(const std::string &name,
                         const std::string &source_handler_uuid = "");
  void SetCurrentCubeTexture(const std::string &name,
                             const std::string &source_handler_uuid = "");
  void SetCurrentIbl(const std::string &name,
                     const std::string &source_handler_uuid = "");

  void LoadDdsIbl(const std::string &name, const std::string &path,
                  const std::string &state_change_signal_uuid = "");
  void LoadHdrIbl(const std::string &name, const std::string &filename,
                  const std::string &state_change_signal_uuid = "");

  void ExportDdsIbl(const std::string &path, const std::string &base_path);
  void ExportDdsRgbdIbl(const std::string &path, const std::string &base_path);
  void ExportKtxIbl(const std::string &path, const std::string &base_path);
  void ExportKtxUastcIbl(const std::string &path, const std::string &base_path);

  Signal<> &GetStateChangeSignal();

private:
  std::string current_texture_name_;
  std::string current_cube_texture_name_;
  std::string current_ibl_name_;

  Universe *universe_;
  Scene *scene_;

  VisualDebugger debug_;
  std::string display_texture_handler_id_;
  std::string display_cube_texture_handler_id_;
  std::string display_ibl_radiance_handler_id_;
  std::string display_ibl_irradiance_handler_id_;

  Signal<> state_change_signal_;
};

} // namespace orangutan

#endif // ORANGUTAN_MANAGER_TEXTURE_MANAGER_H
