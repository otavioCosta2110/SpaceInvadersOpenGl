#include <cstdio>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "keyControl.cpp"

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

void initializeStars() {
    for (int i = 0; i < numStars; ++i) {
        starX[i] = static_cast<float>(rand()) / RAND_MAX * 2.0f - 1.0f;
        starY[i] = static_cast<float>(rand()) / RAND_MAX * 2.0f - 1.0f;
    }
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

void desenhaInvasores() {
    for (int i = 0; i < numInvadersTotal; ++i) {
        if (!invaderAlive[i]) continue;

        glPushMatrix();
        glTranslatef(invaderX[i], invaderY[i], 0.0f);

        glBegin(GL_QUADS);
        glColor3f(1.0f, 1.0f, 1.0f);
        glVertex2f(-0.04f, 0.04f);
        glVertex2f(0.04f, 0.04f);
        glVertex2f(0.04f, -0.04f);
        glVertex2f(-0.04f, -0.04f);

        glVertex2f(-0.06f, 0.02f);
        glVertex2f(-0.04f, 0.02f);
        glVertex2f(-0.04f, -0.02f);
        glVertex2f(-0.06f, -0.02f);

        glVertex2f(0.06f, 0.02f);
        glVertex2f(0.04f, 0.02f);
        glVertex2f(0.04f, -0.02f);
        glVertex2f(0.06f, -0.02f);

        glVertex2f(-0.03f, -0.06f);
        glVertex2f(-0.01f, -0.06f);
        glVertex2f(-0.01f, -0.04f);
        glVertex2f(-0.03f, -0.04f);

        glVertex2f(0.03f, -0.06f);
        glVertex2f(0.01f, -0.06f);
        glVertex2f(0.01f, -0.04f);
        glVertex2f(0.03f, -0.04f);
        glEnd();

        glPopMatrix();
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

// 💀💀💀
void desenhaWin() {
    glPushMatrix(); 
    
    glBegin(GL_LINES);
    
    glVertex2f(-0.05f, 0.05f);  
    glVertex2f(-0.03f, -0.05f); 

    glVertex2f(-0.03f, -0.05f);
    glVertex2f(0.0f, 0.02f);

    glVertex2f(0.0f, 0.02f);
    glVertex2f(0.03f, -0.05f);

    glVertex2f(0.03f, -0.05f);
    glVertex2f(0.05f, 0.05f);
    
    glEnd();

    glTranslatef(0.2f, 0.0f, 0.0f);

    glBegin(GL_LINES);

    glVertex2f(-0.01f, 0.05f);  
    glVertex2f(-0.01f, -0.05f);

    glEnd();

    glTranslatef(0.2f, 0.0f, 0.0f);

    glBegin(GL_LINES);
    
    glVertex2f(-0.05f, 0.05f);  
    glVertex2f(-0.05f, -0.05f); 

    glVertex2f(-0.05f, 0.05f);  
    glVertex2f(0.05f, -0.05f); 

    glVertex2f(0.05f, 0.05f);  
    glVertex2f(0.05f, -0.05f);

    glEnd();

    glPopMatrix(); 
}

