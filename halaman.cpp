#include "halaman.h"

void gambarHalamanDanPaving() {
    // 1. Rumput Hijau Utama
    glBegin(GL_QUADS);
    glNormal3f(0.0f, 1.0f, 0.0f);
    glColor3f(0.25f, 0.5f, 0.25f);
    glVertex3f(-20.0f, -0.5f, -20.0f); glVertex3f(20.0f, -0.5f, -20.0f);
    glVertex3f(20.0f, -0.5f, 20.0f); glVertex3f(-20.0f, -0.5f, 20.0f);
    glEnd();

    // 2. Jalan Paving Blok Depan Rumah (Abu-abu gelap)
    glBegin(GL_QUADS);
    glNormal3f(0.0f, 1.0f, 0.0f);
    glColor3f(0.45f, 0.43f, 0.4f);
    glVertex3f(-6.0f, -0.49f, -3.5f); glVertex3f(6.0f, -0.49f, -3.5f);
    glVertex3f(6.0f, -0.49f,  4.0f); glVertex3f(-6.0f, -0.49f,  4.0f);
    glEnd();
}