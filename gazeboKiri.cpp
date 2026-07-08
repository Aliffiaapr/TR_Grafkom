#include "gazeboKiri.h"
#include "balok.h"

void gambarGazeboKiri() {
    float rKayu = 0.35f, gKayu = 0.18f, bKayu = 0.08f;
    
    gambarBalok(-4.8f, -4.6f, -0.5f, 1.2f, -1.5f, -1.3f, rKayu, gKayu, bKayu);
    gambarBalok(-3.2f, -3.0f, -0.5f, 1.2f, -1.5f, -1.3f, rKayu, gKayu, bKayu);
    gambarBalok(-4.8f, -4.6f, -0.5f, 1.2f,  1.3f,  1.5f, rKayu, gKayu, bKayu);
    gambarBalok(-3.2f, -3.0f, -0.5f, 1.2f,  1.3f,  1.5f, rKayu, gKayu, bKayu);

    glBegin(GL_TRIANGLES);
    glColor3f(0.45f, 0.22f, 0.12f);
    
    glNormal3f(0.0f, 0.5f, 0.8f);
    glVertex3f(-5.0f, 1.2f, 1.7f); glVertex3f(-2.8f, 1.2f, 1.7f); glVertex3f(-3.9f, 1.9f, 0.0f);
    
    glNormal3f(0.8f, 0.5f, 0.0f);
    glVertex3f(-2.8f, 1.2f, 1.7f); glVertex3f(-2.8f, 1.2f, -1.7f); glVertex3f(-3.9f, 1.9f, 0.0f);
    
    glNormal3f(0.0f, 0.5f, -0.8f);
    glVertex3f(-2.8f, 1.2f, -1.7f); glVertex3f(-5.0f, 1.2f, -1.7f); glVertex3f(-3.9f, 1.9f, 0.0f);
    
    glNormal3f(-0.8f, 0.5f, 0.0f);
    glVertex3f(-5.0f, 1.2f, -1.7f); glVertex3f(-5.0f, 1.2f, 1.7f); glVertex3f(-3.9f, 1.9f, 0.0f);
    glEnd();
}