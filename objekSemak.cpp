#ifdef _WIN32
#include <windows.h>
#endif

#include <GL/gl.h>
#include "objekSemak.h"


// Fungsi pembantu kubus mandiri khusus untuk file semak
void drawSemakCube(float sx, float sy, float sz) {
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

// Fungsi internal membuat 1 gundukan semak bulat tinggi
void drawSatuSemakBulatTinggi() {
    // 1. Dasar bawah (Hijau Sangat Tua / Gelap)
    glColor3f(0.02f, 0.25f, 0.05f);
    glPushMatrix();
        glTranslatef(0.0f, 0.3f, 0.0f);
        drawSemakCube(2.4f, 0.6f, 2.4f);
    glPopMatrix();

    // 2. Badan tengah bawah (Hijau Daun Alami)
    glColor3f(0.0f, 0.42f, 0.08f);
    glPushMatrix();
        glTranslatef(0.0f, 0.9f, 0.0f);
        drawSemakCube(2.8f, 0.8f, 2.8f);
    glPopMatrix();

    // 3. Pundak tengah atas (Hijau Medium Ringan)
    glColor3f(0.0f, 0.55f, 0.12f);
    glPushMatrix();
        glTranslatef(0.0f, 1.6f, 0.0f);
        drawSemakCube(2.4f, 0.7f, 2.4f);
    glPopMatrix();

    // 4. Pucuk kepala semak (Hijau Pupus Muda Cerah)
    glColor3f(0.2f, 0.7f, 0.2f);
    glPushMatrix();
        glTranslatef(0.0f, 2.0f, 0.0f);
        drawSemakCube(1.6f, 0.4f, 1.6f);
    glPopMatrix();
}

void objekSemak() {
    glDisable(GL_CULL_FACE);
    glEnable(GL_DEPTH_TEST);

    glPushMatrix();
        // -----------------------------------------------------------------
        // BARISAN SEMAK BULAT TINGGI (3 BOLA BERDEMPETAN)
        // -----------------------------------------------------------------
        // Semak Tengah
        glPushMatrix();
            drawSatuSemakBulatTinggi();
        glPopMatrix();

        // Semak Kanan
        glPushMatrix();
            glTranslatef(1.6f, 0.0f, -0.3f);
            glScalef(0.9f, 0.9f, 0.9f);
            drawSatuSemakBulatTinggi();
        glPopMatrix();

        // Semak Kiri
        glPushMatrix();
            glTranslatef(-1.6f, 0.0f, -0.3f);
            glScalef(0.9f, 0.9f, 0.9f);
            drawSatuSemakBulatTinggi();
        glPopMatrix();

        // -----------------------------------------------------------------
        // -----------------------------------------------------------------
        // PAS 5 BUNGA MERAH - SUDAH DIMAJUKAN AGAR MENYEMBUL KELUAR SEMAK
        // -----------------------------------------------------------------
        glColor3f(1.0f, 0.0f, 0.0f); // Warna Merah Cabai Menyala

        // 1. BUNGA PUNCAK UTAMA (Paling atas di tengah semak utama)
        glPushMatrix();
            glTranslatef(0.0f, 1.7f, 0.95f); // Z dimajukan dari 0.65f ke 0.95f
            drawSemakCube(0.22f, 0.22f, 0.22f);
        glPopMatrix();

        // 2. BUNGA KIRI ATAS (Sayap kiri, posisi sedang-tinggi)
        glPushMatrix();
            glTranslatef(-0.7f, 0.8f, 1.5f); // Z dimajukan dari 0.75f ke 1.05f
            drawSemakCube(0.18f, 0.18f, 0.18f);
        glPopMatrix();

        // 3. BUNGA KANAN ATAS (Sayap kanan, posisi sedang-tinggi)
        glPushMatrix();
            glTranslatef(1.1f, 1.1f, 1.4f); // Z dimajukan dari 0.75f ke 1.05f
            drawSemakCube(0.18f, 0.18f, 0.18f);
        glPopMatrix();

        // 4. BUNGA KIRI BAWAH (Sayap kiri depan, posisi rendah melebar)
        glPushMatrix();
            glTranslatef(-1.8f, 0.7f, 1.0f); // Z dimajukan dari 0.9f ke 1.15f
            drawSemakCube(0.2f, 0.2f, 0.2f);
        glPopMatrix();

        glPushMatrix();
            glTranslatef(0.5f, 0.9f, 1.5f);
            drawSemakCube(0.2f, 0.2f, 0.2f);
        glPopMatrix();

        // 5. BUNGA KANAN BAWAH (Sayap kanan depan, posisi rendah melebar)
        glPushMatrix();
            glTranslatef(1.8f, 0.7f, 1.15f); // Z dimajukan dari 0.9f ke 1.15f
            drawSemakCube(0.2f, 0.2f, 0.2f);
        glPopMatrix();

    glPopMatrix();
    glEnable(GL_CULL_FACE);
}
