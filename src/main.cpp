#include <cstdio>
#include <iostream>

#include <GL/glew.h>

#include <GLFW/glfw3.h>
#include "draw.cpp"

void desenhaTriangulo();
void desenhaQuadrado(float initialPos);
void desenhaInvasores();
void initializeInvaders();
void initializeStars();
void desenhaEstrelas();
void desenhaWin();

int main()
{	
  if (!glfwInit())
  {
    std::cout << "Erro ao inicializar o GLFW" << std::endl;
    return 1;
  }

  GLFWwindow* Window = glfwCreateWindow(Width, Height, "Space Invaders", nullptr, nullptr);

  if (!Window)
  {
    std::cout << "Erro ao criar janela" << std::endl;
    glfwTerminate();
    return 1;
  }

  glfwMakeContextCurrent(Window);
  glfwSwapInterval(1);

  if (glewInit() != GLEW_OK)
  {
    std::cout << "Erro ao inicializar o GLEW" << std::endl;
    glfwTerminate();
    return 1;
  }

  GLint GLMajorVersion = 0;
  GLint GLMinorVersion = 0;
  glGetIntegerv(GL_MAJOR_VERSION, &GLMajorVersion);
  glGetIntegerv(GL_MINOR_VERSION, &GLMinorVersion);	
  std::cout << "OpenGL Version  : " << GLMajorVersion << "." << GLMinorVersion << std::endl;

  std::cout << "OpenGL Vendor   : " << glGetString(GL_VENDOR) << std::endl;
  std::cout << "OpenGL Renderer : " << glGetString(GL_RENDERER) << std::endl;
  std::cout << "OpenGL Version  : " << glGetString(GL_VERSION) << std::endl;
  std::cout << "GLSL Version    : " << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;

  glClearColor(0.0f, 0.0f, 0.0f, 0.0);
  initializeInvaders();

  srand(static_cast<unsigned int>(time(nullptr)));

  initializeStars();

  while (!glfwWindowShouldClose(Window) && !gameOver) {
    glClear(GL_COLOR_BUFFER_BIT);

    processInput(Window);

    if ( numInvadersAlive == 0) {
      desenhaWin();
    }
    desenhaEstrelas();
    desenhaTriangulo();
    desenhaBala();
    desenhaInvasores();
    checaColisao();
    moveInvasores();

    glfwSwapBuffers(Window);
    glfwPollEvents();
  }
  if (gameOver) {
    std::cout << "Game Over!" << std::endl;
  }

  glfwTerminate();

  return 0;
}
