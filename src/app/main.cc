#include <glad/glad.h>

#include <GLFW/glfw3.h>

#include <iostream>

#include "basisu_enc.h"

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "nfd.h"
#include <nfd_glfw3.h>

#include "app/app.h"
#include "ui/texturewindow.h"
#include "util/keyboard.h"

const unsigned int kFormatSize = 8;
const unsigned int kDefaultWidth = 1600;
const unsigned int kDefaultHeight = 900;

const std::unordered_map<int, orangutan::KeyState> kGlfwActionToKeyState = {
    {GLFW_PRESS, orangutan::kPressed},
    {GLFW_RELEASE, orangutan::kReleased},
    {GLFW_REPEAT, orangutan::kPressed},
    {GLFW_KEY_UNKNOWN, orangutan::kUnknow}};

int main(int argc, char *argv[]) {

  glfwInit();

  if (NFD_Init() != NFD_OKAY) {
    std::cerr << "Failed to init NFD" << std::endl;
    return -1;
  }

  // this gives NFD the wl_display* on Wayland; this is needed to set the parent
  // window
  if (!NFD_SetDisplayPropertiesFromGLFW()) {
    printf("NFD_SetDisplayPropertiesFromGLFW failed\n");
  }

  glfwSetTime(0);

  glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_API);

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  glfwWindowHint(GLFW_SAMPLES, 0);
  glfwWindowHint(GLFW_RED_BITS, kFormatSize);
  glfwWindowHint(GLFW_GREEN_BITS, kFormatSize);
  glfwWindowHint(GLFW_BLUE_BITS, kFormatSize);
  glfwWindowHint(GLFW_ALPHA_BITS, kFormatSize);
  glfwWindowHint(GLFW_STENCIL_BITS, kFormatSize);
  glfwWindowHint(GLFW_DEPTH_BITS, 3 * kFormatSize);
  glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);

  // Create a GLFWwindow object
  GLFWwindow *window = glfwCreateWindow(kDefaultWidth, kDefaultHeight,
                                        "Orangutan", nullptr, nullptr);
  if (window == nullptr) {
    std::cerr << "Failed to create GLFW window" << std::endl;
    glfwTerminate();
    return -1;
  }
  glfwMakeContextCurrent(window);

  glfwMaximizeWindow(window);

  int version = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
  if (version == 0) {
    printf("Failed to initialize OpenGL context\n");
    return -1;
  }

  // Successfully loaded OpenGL
  printf("Loaded OpenGL %d.%d\n", GLFW_VERSION_MAJOR, GLFW_VERSION_MINOR);

  int width = 0;
  int height = 0;
  glfwGetFramebufferSize(window, &width, &height);
  glViewport(0, 0, width, height);

  std::cout << "Initial window size : " << width << "x" << height << std::endl;

  glfwSwapInterval(0);
  glfwSwapBuffers(window);

  // Global opengl options
  glEnable(
      GL_TEXTURE_CUBE_MAP_SEAMLESS); // Avoid seams when precomputing cube maps

  basisu::basisu_encoder_init();

  // Event binding (before setting up imgui)
  /*auto cursor_pos_callback = [](GLFWwindow *window, double x, double y) {
    //canvas.(window, x, y);
    std::cout << "Cursor position : " << x << ":" << y << std::endl;
  };
  glfwSetCursorPosCallback(window, cursor_pos_callback);*/

  auto key_callback = [](GLFWwindow *window, int key, int scancode, int action,
                         int mods) {
    orangutan::KeyState key_state = kGlfwActionToKeyState.at(action);
    orangutan::Keyboard::instance().setState(key, key_state);
  };
  glfwSetKeyCallback(window, key_callback);

  // Setup Dear ImGui context
  IMGUI_CHECKVERSION();
  ImGui::CreateContext();
  ImGuiIO &io = ImGui::GetIO();
  io.ConfigFlags |=
      ImGuiConfigFlags_NavEnableKeyboard; // Enable Keyboard Controls
  io.ConfigFlags |=
      ImGuiConfigFlags_NavEnableGamepad; // Enable Gamepad Controls

  // Setup Platform/Renderer backends
  ImGui_ImplGlfw_InitForOpenGL(
      window, true); // Second param install_callback=true will install GLFW
                     // callbacks and chain to existing ones.
  ImGui_ImplOpenGL3_Init();

  orangutan::App app;
  app.Init();

  orangutan::TextureWindow textureWindow(app.get_texture_manager());

  //  orangutan::Canvas canvas;

  // Draw call binding

  while (!glfwWindowShouldClose(window)) {
    // Check if any events have been activated (key pressed, mouse moved etc.)
    // and call corresponding response functions
    glfwPollEvents();
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    textureWindow.Draw(window);

    ImGui::Render();

    int width = 0;
    int height = 0;
    glfwGetFramebufferSize(window, &width, &height);
    glViewport(0, 0, width, height);

    glClearColor(0, 0, 0, 0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Draw canvas
    app.Draw(width, height);

    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    glfwSwapBuffers(window);
  }

  NFD_Quit();

  ImGui_ImplOpenGL3_Shutdown();
  ImGui_ImplGlfw_Shutdown();
  ImGui::DestroyContext();

  // Terminate GLFW, clearing any resources allocated by GLFW.
  glfwDestroyWindow(window);
  glfwTerminate();

  return 0;
}
