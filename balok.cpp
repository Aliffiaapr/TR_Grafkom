#include "balok.h"

void gambarBalok(float xMin, float xMax, float yMin, float yMax, float zMin, float zMax, float r, float g, float b) {
    glColor3f(r, g, b);
    glBegin(GL_QUADS);
    
    // Depan
    glNormal3f(0.0f, 0.0f, 1.0f);
    glVertex3f(xMin, yMin, zMax); glVertex3f(xMax, yMin, zMax);
    glVertex3f(xMax, yMax, zMax); glVertex3f(xMin, yMax, zMax);
    
    // Belakang
    glNormal3f(0.0f, 0.0f, -1.0f);
    glVertex3f(xMin, yMin, zMin); glVertex3f(xMin, yMax, zMin);
    glVertex3f(xMax, yMax, zMin); glVertex3f(xMax, yMin, zMin);
    
    // Kiri
    glNormal3f(-1.0f, 0.0f, 0.0f);
    glVertex3f(xMin, yMin, zMin); glVertex3f(xMin, yMin, zMax);
    glVertex3f(xMin, yMax, zMax); glVertex3f(xMin, yMax, zMin);
    
    // Kanan
    glNormal3f(1.0f, 0.0f, 0.0f);
    glVertex3f(xMax, yMin, zMin); glVertex3f(xMax, yMax, zMin);
    glVertex3f(xMax, yMax, zMax); glVertex3f(xMax, yMin, zMax);
    
    // Atas
    glNormal3f(0.0f, 1.0f, 0.0f);
    glVertex3f(xMin, yMax, zMin); glVertex3f(xMin, yMax, zMax);
    glVertex3f(xMax, yMax, zMax); glVertex3f(xMax, yMax, zMin);
    
    // Bawah
    glNormal3f(0.0f, -1.0f, 0.0f);
    glVertex3f(xMin, yMin, zMin); glVertex3f(xMax, yMin, zMin);
    glVertex3f(xMax, yMin, zMax); glVertex3f(xMin, yMin, zMax);
    
    glEnd();
}