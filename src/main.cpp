#include <cstdio>
#include <iostream>

#include <GL/glew.h>

#include <GLFW/glfw3.h>
#include "keyControl.cpp"

void desenhaTriangulo();
void desenhaQuadrado(float initialPos);
void desenhaInvasores();
void initializeInvaders();

const int numStars = 100;

float starX[numStars];
float starY[numStars];

void initializeStars();
void desenhaEstrelas();

int main()
{	
  if (!glfwInit())
  {
    std::cout << "Erro ao inicializar o GLFW" << std::endl;
    return 1;
  }

  GLFWwindow* Window = glfwCreateWindow(Width, Height, "ProgramaOpengl1", nullptr, nullptr);

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

  // Ler a versão do OpenGL para imprimir na tela
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


void desenhaTriangulo(){
  glPushMatrix();
  glTranslatef(0.0f + trianguloX, 1.0f - trianguloY, 0.0f);

  glBegin(GL_TRIANGLES);

  glColor3f(1.0f, 0.0f, 0.0f);

  glVertex2f(0.0f, trianguloTamX);
  glVertex2f(trianguloTamX, -trianguloTamY);
  glVertex2f(-trianguloTamX, -trianguloTamY);

  glEnd();

  glPopMatrix();
}

void initializeInvaders() {
    float startX = -0.9f;  
    float startY = 0.8f;   
    float spacingX = 0.2f;
    float spacingY = 0.2f;

    int index = 0; 
    for (int row = 0; row < numRows; ++row) {
        for (int col = 0; col < numColumns; ++col) {
            invaderX[index] = startX + col * spacingX; 
            invaderY[index] = startY - row * spacingY;
            invaderAlive[index] = true;  
            ++index;
        }
    }
}

void desenhaInvasores() {
    for (int i = 0; i < numInvadersTotal; ++i) {
        if (!invaderAlive[i]) continue;

        glPushMatrix();
        glTranslatef(invaderX[i], invaderY[i], 0.0f);

        glBegin(GL_QUADS);
        glColor3f(0.0f, 0.3f, 0.0f);
        glVertex2f(-0.04f, 0.04f);
        glVertex2f(0.04f, 0.04f);
        glVertex2f(0.04f, -0.04f);
        glVertex2f(-0.04f, -0.04f);
        glEnd();

        glPopMatrix();
    }
}

void initializeStars() {
    for (int i = 0; i < numStars; ++i) {
        starX[i] = static_cast<float>(rand()) / RAND_MAX * 2.0f - 1.0f;
        starY[i] = static_cast<float>(rand()) / RAND_MAX * 2.0f - 1.0f;
    }
}

void desenhaEstrelas() {
    glColor3f(1.0f, 1.0f, 1.0f); 
    glBegin(GL_POINTS);

    for (int i = 0; i < numStars; ++i) {
        glVertex2f(starX[i], starY[i]); 
    }

    glEnd();
}
