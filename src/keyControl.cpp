
#include <cstdio>

#include <GL/glew.h>

#include <GLFW/glfw3.h>
#include "global.cpp"

void processInput(GLFWwindow* window) {
  if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
    glfwSetWindowShouldClose(window, true);
  }

  if (trianguloX > -(1.0f + trianguloTamX)){
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
      trianguloX -= velocidade;
    }
  }

  if(trianguloX < 1.0f + trianguloTamX ){
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
      trianguloX += velocidade;
    }
  }

  if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
    atiraBala();
  }
}
