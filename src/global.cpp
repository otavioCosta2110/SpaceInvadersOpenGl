

#include <GL/glew.h>

#include <GLFW/glfw3.h>
#include <cstdio>
#include <cstdlib>
#include <vector>
const int Width = 1200;
const int Height = 900;

const int numColumns = 10; 
const int numRows = 2;   

const int numInvadersTotal = numColumns * numRows;
int numInvadersAlive = numInvadersTotal;
std::vector<float> invaderX(numInvadersTotal, 0.0f);
std::vector<float> invaderY(numInvadersTotal, 0.8f); 
bool invaderAlive[numInvadersTotal] = { true };

float trianguloTamY = 0.05f;
float trianguloTamX = 0.05f;

float trianguloY = 1.8f;
float trianguloX = 0.0f;

float balaTamY = 0.05f;
float balaTamX = 0.05f;
float balaY = -1;
float balaX = 0;
bool balaAtiva = false;
float lastShotTime = 0.0;
float bulletCooldown = 0.7;

float quadradoTamY = 0.05f;
float quadradoTamX = 0.05f;

float velocidade = 0.02f;
float velocidadeBala = 0.03f;

float limiteInvasores = -0.75f;
bool gameOver = false;
                          
void checaColisao() {
    for (int i = 0; i < numInvadersTotal; ++i) {
        if (!invaderAlive[i]) continue;

        if (balaAtiva && balaX > invaderX[i] - 0.05f && balaX < invaderX[i] + 0.05f &&
            balaY > invaderY[i] - 0.05f && balaY < invaderY[i] + 0.05f) {

            invaderAlive[i] = false; 
            numInvadersAlive--;
            balaAtiva = false;       
        }
    }
}

void atiraBala() {
    float currentTime = glfwGetTime();
    
    if (!balaAtiva && (currentTime - lastShotTime >= bulletCooldown)) {
        balaAtiva = true;
        balaY = -0.6f;  
        balaX = trianguloX;  
        lastShotTime = currentTime;
    }
}

void desenhaBala() {
    float currentTime = glfwGetTime();
    if (currentTime - lastShotTime >= bulletCooldown) {
        balaAtiva = false;
    }
    if (!balaAtiva) {
      balaY = -0.6f;
      balaX = trianguloX;
      return;
    }; 

    glPushMatrix();
    glTranslatef(balaX, balaY, 0.0f);

    glBegin(GL_QUADS);
    glColor3f(0.0f, 0.3f, 0.9f);
    glVertex2f(-0.02f, 0.05f);
    glVertex2f(0.02f, 0.05f);
    glVertex2f(0.02f, -0.05f);
    glVertex2f(-0.02f, -0.05f);
    glEnd();

    glPopMatrix();

    balaY += velocidadeBala;

    if (balaY > 1.0f) {
        balaAtiva = false;
    }
}


void moveInvasores() {
    static bool moveRight = true;
    float velocidadeBase = 0.02f;
    float velocidadeInvasores = velocidadeBase / numInvadersAlive * 2;

    for (int i = 0; i < numInvadersTotal; ++i) {
        if (!invaderAlive[i]) continue;

        if (moveRight) {
            invaderX[i] += velocidadeInvasores;
        } else {
            invaderX[i] -= velocidadeInvasores;
        }

        if (invaderY[i] <= limiteInvasores) {
            gameOver = true;
        }
    }

    for (int i = 0; i < numInvadersTotal; ++i) {
        if (invaderX[i] > 1.0f || invaderX[i] < -1.0f) {
            moveRight = !moveRight; 

            for (int j = 0; j < numInvadersTotal; ++j) {
                invaderY[j] -= 0.1f;
            }
            break; 
        }
    }

}

bool isBalaCooldown(){
    float currentTime = glfwGetTime();
    return (currentTime - lastShotTime >= bulletCooldown);
}
