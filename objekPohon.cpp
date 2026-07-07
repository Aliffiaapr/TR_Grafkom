#include "objekPohon.h"


// Fungsi pembantu membuat balok otomatis yang anti-bolong & anti-cullface
void drawPohonCubeOtomatis(float sx, float sy, float sz) {
    glPushMatrix();
        glScalef(sx, sy, sz); // Atur skala Ukuran Panjang, Tinggi, Lebar

        // Menggambar kubus murni 6 sisi otomatis bawaan OpenGL
        glBegin(GL_QUADS);
            // Depan
            glNormal3f(0.0f, 0.0f, 1.0f);
            glVertex3f(-0.5f, -0.5f,  0.5f); glVertex3f( 0.5f, -0.5f,  0.5f);
            glVertex3f( 0.5f,  0.5f,  0.5f); glVertex3f(-0.5f,  0.5f,  0.5f);
            // Belakang
            glNormal3f(0.0f, 0.0f, -1.0f);
            glVertex3f(-0.5f, -0.5f, -0.5f); glVertex3f(-0.5f,  0.5f, -0.5f);
            glVertex3f( 0.5f,  0.5f, -0.5f); glVertex3f( 0.5f, -0.5f, -0.5f);
            // Atas
            glNormal3f(0.0f, 1.0f, 0.0f);
            glVertex3f(-0.5f,  0.5f, -0.5f); glVertex3f(-0.5f,  0.5f,  0.5f);
            glVertex3f( 0.5f,  0.5f,  0.5f); glVertex3f( 0.5f,  0.5f, -0.5f);
            // Bawah
            glNormal3f(0.0f, -1.0f, 0.0f);
            glVertex3f(-0.5f, -0.5f, -0.5f); glVertex3f( 0.5f, -0.5f, -0.5f);
            glVertex3f( 0.5f, -0.5f,  0.5f); glVertex3f(-0.5f, -0.5f,  0.5f);
            // Kanan
            glNormal3f(1.0f, 0.0f, 0.0f);
            glVertex3f( 0.5f, -0.5f, -0.5f); glVertex3f( 0.5f,  0.5f, -0.5f);
            glVertex3f( 0.5f,  0.5f,  0.5f); glVertex3f( 0.5f, -0.5f,  0.5f);
            // Kiri
            glNormal3f(-1.0f, 0.0f, 0.0f);
            glVertex3f(-0.5f, -0.5f, -0.5f); glVertex3f(-0.5f, -0.5f,  0.5f);
            glVertex3f(-0.5f,  0.5f,  0.5f); glVertex3f(-0.5f,  0.5f, -0.5f);
        glEnd();
    glPopMatrix();
}

void drawObjekPohon() {
    // Matikan Cull Face sementara khusus untuk objek ini agar tidak bolong transparan
    glDisable(GL_CULL_FACE);
    glEnable(GL_DEPTH_TEST);

    glPushMatrix();
        // 1. BATANG POHON (Lebar 1.2, Tinggi 6.0, Tebal 1.2)
        glColor3f(0.45f, 0.28f, 0.15f);
        glPushMatrix();
            // Naik 3.0f (setengah dari tinggi balok 6.0) agar dasarnya pas menempel di tanah
            glTranslatef(0.0f, 3.0f, 0.0f);
            drawPohonCubeOtomatis(1.2f, 6.0f, 1.2f);
        glPopMatrix();

        // 2. DAUN LAYER 1 (Rindang Bawah)
        glColor3f(0.0f, 0.4f, 0.1f);
        glPushMatrix();
            glTranslatef(0.0f, 6.5f, 0.0f);
            drawPohonCubeOtomatis(5.0f, 2.0f, 5.0f);
        glPopMatrix();

        // 3. DAUN LAYER 2 (Tengah)
        glColor3f(0.0f, 0.5f, 0.15f);
        glPushMatrix();
            glTranslatef(0.0f, 8.0f, 0.0f);
            drawPohonCubeOtomatis(3.8f, 1.8f, 3.8f);
        glPopMatrix();

        // 4. DAUN LAYER 3 (Pucuk)
        glColor3f(0.1f, 0.6f, 0.2f);
        glPushMatrix();
            glTranslatef(0.0f, 9.2f, 0.0f);
            drawPohonCubeOtomatis(2.2f, 1.2f, 2.2f);
        glPopMatrix();

    glPopMatrix();

    // Aktifkan kembali Cull Face setelah pohon selesai digambar biar objek main.cpp lainnya tidak rusak
    glEnable(GL_CULL_FACE);
}
