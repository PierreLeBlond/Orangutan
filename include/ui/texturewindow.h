#ifndef ORANGUTAN_UI_TEXTURE_WINDOW_H
#define ORANGUTAN_UI_TEXTURE_WINDOW_H

#include <glad/glad.h>

#include <GLFW/glfw3.h>

#include "nfd.h"

#include "manager/texturemanager.h"

namespace orangutan {

class TextureWindow {
public:
  TextureWindow(TextureManager *texture_manager);
  void Draw(GLFWwindow *window);

private:
  void DrawTextureCombo(
      const std::string &label, const std::vector<std::string> &texture_names,
      const std::string &current_texture_name, unsigned int current_texture_id,
      const std::function<void(const std::string &)> &on_texture_picked);

  void OpenLoadDialog(
      const std::string &label, const nfdu8filteritem_t *filters,
      unsigned int filterCount, GLFWwindow *window,
      const std::function<void(const std::string &, const std::string &)>
          &on_path_picked);

  void OpenSaveDialog(
      const std::string &label, const nfdu8filteritem_t *filters,
      unsigned int filterCount, GLFWwindow *window,
      const std::function<void(const std::string &, const std::string &)>
          &on_path_picked);

  TextureManager *texture_manager_;
};

} // namespace orangutan

#endif // ORANGUTAN_UI_TEXTURE_WINDOW_H
