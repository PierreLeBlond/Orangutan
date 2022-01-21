#include <GLFW/glfw3.h>
#include <nanogui/nanogui.h>

#include <iostream>
#include <memory>

#include "app/app.h"

const unsigned int kFormatSize = 8;
const unsigned int kDefaultWidth = 1600;
const unsigned int kDefaultHeight = 900;

int main(int argc, char *argv[]) {
  glfwInit();
  glfwSetTime(0);

  glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_API);

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
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

  App app;
  app.Init(window);

  glfwMaximizeWindow(window);

  int width = 0;
  int height = 0;
  glfwGetFramebufferSize(window, &width, &height);
  glViewport(0, 0, width, height);
  glfwSwapInterval(0);
  glfwSwapBuffers(window);

  while (!glfwWindowShouldClose(window)) {
    // Check if any events have been activated (key pressed, mouse moved etc.)
    // and call corresponding response functions
    glfwPollEvents();

    // Draw nanogui
    app.Draw();

    glfwSwapBuffers(window);
  }

  // Terminate GLFW, clearing any resources allocated by GLFW.
  glfwTerminate();

  return 0;
}
