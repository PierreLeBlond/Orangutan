#ifndef ORANGUTAN_MANAGER_TEXTURE_MANAGER_H
#define ORANGUTAN_MANAGER_TEXTURE_MANAGER_H

#include <memory>

#include "debug/visualdebugger.h"
#include "model/universe.h"
#include "ui/canvas.h"

namespace orangutan {

class TextureManager {
 public:
  TextureManager(Universe* universe, Canvas* canvas, Scene* scene);

  void GetTextureNames(std::vector<std::string>& texture_names) const;
  void GetCubeTextureNames(std::vector<std::string>& cube_texture_names) const;
  void GetIblNames(std::vector<std::string>& ibl_names) const;
  [[nodiscard]] const std::string& GetCurrentTextureName() const;
  [[nodiscard]] const std::string& GetCurrentCubeTextureName() const;
  [[nodiscard]] const std::string& GetCurrentIblName() const;

  void SetCurrentTexture(const std::string& name,
                         const std::string& source_handler_uuid = "");
  void SetCurrentCubeTexture(const std::string& name,
                             const std::string& source_handler_uuid = "");
  void SetCurrentIbl(const std::string& name,
                     const std::string& source_handler_uuid = "");

  void ShowCurrentTexture();
  void HideCurrentTexture();

  void ShowCurrentCubeTexture();
  void HideCurrentCubeTexture();

  void ShowCurrentIblRadiance();
  void HideCurrentIblRadiance();

  void ShowCurrentIblIrradiance();
  void HideCurrentIblIrradiance();

  void LoadDdsIbl(const std::string& name, const std::string& path,
                  const std::string& state_change_signal_uuid = "");
  void LoadHdrIbl(const std::string& name, const std::string& filename,
                  const std::string& state_change_signal_uuid = "");
  void ExportDdsIbl(const std::string& name, const std::string& path,
                    const std::string& state_change_signal_uuid = "");
  void ExportDdsRgbdIbl(const std::string& name, const std::string& path,
                        const std::string& state_change_signal_uuid = "");

  Signal<>& GetStateChangeSignal();

 private:
  std::string current_texture_name_;
  std::string current_cube_texture_name_;
  std::string current_ibl_name_;

  Universe* universe_;
  Canvas* canvas_;
  Scene* scene_;

  VisualDebugger debug_;
  std::string display_texture_handler_id_;
  std::string display_cube_texture_handler_id_;
  std::string display_ibl_radiance_handler_id_;
  std::string display_ibl_irradiance_handler_id_;

  Signal<> state_change_signal_;
};

}  // namespace orangutan

#endif  // ORANGUTAN_MANAGER_TEXTURE_MANAGER_H
