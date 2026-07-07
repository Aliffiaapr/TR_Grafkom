#include "objekBunga.h"
#include <cmath> // Supaya komputer bisa hitung rotasi melingkar (sin/cos)

// Fungsi pembantu membuat balok otomatis anti-bolong
void drawBungaCube(float sx, float sy, float sz) {
    glBegin(GL_QUADS);
        // Depan
        glNormal3f(0.0f, 0.0f, 1.0f);
        glVertex3f(-sx/2, -sy/2,  sz/2); glVertex3f( sx/2, -sy/2,  sz/2);
        glVertex3f( sx/2,  sy/2,  sz/2); glVertex3f(-sx/2,  sy/2,  sz/2);
        // Belakang
        glNormal3f(0.0f, 0.0f, -1.0f);
        glVertex3f(-sx/2, -sy/2, -sz/2); glVertex3f(-sx/2,  sy/2, -sz/2);
        glVertex3f( sx/2,  sy/2, -sz/2); glVertex3f( sx/2, -sz/2, -sz/2);
        // Atas
        glNormal3f(0.0f, 1.0f, 0.0f);
        glVertex3f(-sx/2,  sy/2, -sz/2); glVertex3f(-sx/2,  sy/2,  sz/2);
        glVertex3f( sx/2,  sy/2,  sz/2); glVertex3f( sx/2,  sy/2, -sz/2);
        // Bawah
        glNormal3f(0.0f, -1.0f, 0.0f);
        glVertex3f(-sx/2, -sy/2, -sz/2); glVertex3f( sx/2, -sz/2, -sz/2);
        glVertex3f( sx/2, -sz/2,  sz/2); glVertex3f(-sx/2, -sz/2,  sz/2);
        // Kanan
        glNormal3f(1.0f, 0.0f, 0.0f);
        glVertex3f( sx/2, -sz/2, -sz/2); glVertex3f( sx/2,  sy/2, -sz/2);
        glVertex3f( sx/2,  sy/2,  sz/2); glVertex3f( sx/2, -sz/2,  sz/2);
        // Kiri
        glNormal3f(-1.0f, 0.0f, 0.0f);
        glVertex3f(-sx/2, -sz/2, -sz/2); glVertex3f(-sx/2, -sz/2,  sz/2);
        glVertex3f(-sx/2,  sy/2,  sz/2); glVertex3f(-sx/2,  sy/2, -sz/2);
    glEnd();
}

void drawPohonMungil() {
    glDisable(GL_CULL_FACE);
    glEnable(GL_DEPTH_TEST);

    glPushMatrix();
        // =================================================================
        // 1. TANGKAI BUNGA (Hijau Zaitun Kalem - Kontras dengan Rumput)
        // =================================================================
        glColor3f(0.45f, 0.62f, 0.25f); // Warna Olive Green yang estetik
        glPushMatrix();
            glTranslatef(0.0f, 0.75f, 0.0f);
            drawBungaCube(0.15f, 1.5f, 0.15f);
        glPopMatrix();

        // =================================================================
        // 2. DAUN KIRI & KANAN (Warna SERAGAM dengan Tangkai)
        // =================================================================
        glColor3f(0.45f, 0.62f, 0.25f); // Warna Olive Green yang sama persis
        // Daun Kanan
        glPushMatrix();
            glTranslatef(0.2f, 0.6f, 0.0f);
            glRotatef(-25.0f, 0.0f, 0.0f, 1.0f);
            drawBungaCube(0.4f, 0.1f, 0.2f);
        glPopMatrix();

        // Daun Kiri
        glPushMatrix();
            glTranslatef(-0.2f, 0.8f, 0.0f);
            glRotatef(25.0f, 0.0f, 0.0f, 1.0f);
            drawBungaCube(0.4f, 0.1f, 0.2f);
        glPopMatrix();

        // =================================================================
        // 3. KELOPAK MAHKOTA BUNGA (Ganti ke PINK Pastel Cerah & Cantik)
        // =================================================================
        glTranslatef(0.0f, 1.5f, 0.0f);

        glColor3f(0.9f, 0.3f, 0.5f); // Warna Pink Blossom yang cerah dan pop-out
        int jumlahKelopak = 6;
        for (int i = 0; i < jumlahKelopak; i++) {
            glPushMatrix();
                glRotatef(i * (360.0f / jumlahKelopak), 0.0f, 1.0f, 0.0f);
                glRotatef(-35.0f, 1.0f, 0.0f, 0.0f);
                glTranslatef(0.0f, 0.25f, 0.2f);
                drawBungaCube(0.3f, 0.5f, 0.1f);
            glPopMatrix();
        }

        // =================================================================
        // 4. INTI / SARI BUNGA (Kuning Oranye Emas)
        // =================================================================
        glColor3f(1.0f, 0.75f, 0.1f); // Warna Kuning hangat yang serasi dengan pink
        glPushMatrix();
            drawBungaCube(0.25f, 0.25f, 0.25f);
        glPopMatrix();

    glPopMatrix();

    glEnable(GL_CULL_FACE);
}
