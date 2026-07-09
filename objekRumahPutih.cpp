#include "objekRumahPutih.h"
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

// Fungsi pembantu khusus untuk rumah putih
void drawBalokRumah(float r, float g, float b, float alpha) {
    glColor4f(r, g, b, alpha);
    glBegin(GL_TRIANGLES);
        // Depan
        glNormal3f(0.0f, 0.0f, 1.0f);
        glVertex3f(-0.5f, -0.5f,  0.5f); glVertex3f( 0.5f, -0.5f,  0.5f); glVertex3f( 0.5f,  0.5f,  0.5f);
        glVertex3f( 0.5f,  0.5f,  0.5f); glVertex3f(-0.5f,  0.5f,  0.5f); glVertex3f(-0.5f, -0.5f,  0.5f);
        // Belakang
        glNormal3f(0.0f, 0.0f, -1.0f);
        glVertex3f(-0.5f, -0.5f, -0.5f); glVertex3f(-0.5f,  0.5f, -0.5f); glVertex3f( 0.5f,  0.5f, -0.5f);
        glVertex3f( 0.5f,  0.5f, -0.5f); glVertex3f( 0.5f, -0.5f, -0.5f); glVertex3f(-0.5f, -0.5f, -0.5f);
        // Atas
        glNormal3f(0.0f, 1.0f, 0.0f);
        glVertex3f(-0.5f,  0.5f, -0.5f); glVertex3f(-0.5f,  0.5f,  0.5f); glVertex3f( 0.5f,  0.5f,  0.5f);
        glVertex3f( 0.5f,  0.5f,  0.5f); glVertex3f( 0.5f,  0.5f, -0.5f); glVertex3f(-0.5f,  0.5f, -0.5f);
        // Bawah
        glNormal3f(0.0f, -1.0f, 0.0f);
        glVertex3f(-0.5f, -0.5f, -0.5f); glVertex3f( 0.5f, -0.5f, -0.5f); glVertex3f( 0.5f, -0.5f,  0.5f);
        glVertex3f( 0.5f, -0.5f,  0.5f); glVertex3f(-0.5f, -0.5f,  0.5f); glVertex3f(-0.5f, -0.5f, -0.5f);
        // Kanan
        glNormal3f(1.0f, 0.0f, 0.0f);
        glVertex3f( 0.5f, -0.5f, -0.5f); glVertex3f( 0.5f,  0.5f, -0.5f); glVertex3f( 0.5f,  0.5f,  0.5f);
        glVertex3f( 0.5f,  0.5f,  0.5f); glVertex3f( 0.5f, -0.5f,  0.5f); glVertex3f( 0.5f, -0.5f, -0.5f);
        // Kiri
        glNormal3f(-1.0f, 0.0f, 0.0f);
        glVertex3f(-0.5f, -0.5f, -0.5f); glVertex3f(-0.5f, -0.5f,  0.5f); glVertex3f(-0.5f,  0.5f,  0.5f);
        glVertex3f(-0.5f,  0.5f,  0.5f); glVertex3f(-0.5f,  0.5f, -0.5f); glVertex3f(-0.5f, -0.5f, -0.5f);
    glEnd();
}

void drawRumahPutih() {
    glPushMatrix();

    // ==========================================
    // PENYETELAN SKALA GLOBAL (DIPERBESAR & DIPERTINGGI)
    // ==========================================
    // X=1.6f (Makin Lebar Kanan-Kiri), Y=1.8f (Makin Tinggi), Z=1.6f (Makin Lebar Depan-Belakang)
    glScalef(1.6f, 1.8f, 1.6f);

    // Rotasi agar menghadap kiri
    glRotatef(-90.0f, 0.0f, 1.0f, 0.0f);

    // ==========================================
    // 1. LANTAI UTAMA RUANGAN & JALAN
    // ==========================================
    glPushMatrix();
    glTranslatef(0.0f, 0.05f, 0.0f);
    glScalef(4.8f, 0.1f, 4.8f);
    drawBalokRumah(1.0f, 1.0f, 1.0f, 1.0f);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.0f, 0.05f, 2.7f);
    glScalef(1.0f, 0.1f, 0.6f);
    drawBalokRumah(1.0f, 1.0f, 1.0f, 1.0f);
    glPopMatrix();

    glLineWidth(2.0f);
    glColor3f(0.6f, 0.6f, 0.6f);
    glBegin(GL_LINES);
    for (float i = -2.4f; i <= 2.4f; i += 0.6f) {
        glVertex3f(i, 0.101f, -2.4f);
        glVertex3f(i, 0.101f,  2.4f);
        glVertex3f(-2.4f, 0.101f, i);
        glVertex3f( 2.4f, 0.101f, i);
    }
    glVertex3f(-0.5f, 0.101f, 2.4f); glVertex3f(-0.5f, 0.101f, 3.0f);
    glVertex3f( 0.0f, 0.101f, 2.4f); glVertex3f( 0.0f, 0.101f, 3.0f);
    glVertex3f( 0.5f, 0.101f, 2.4f); glVertex3f( 0.5f, 0.101f, 3.0f);

    for (float j = 2.4f; j <= 3.0f; j += 0.6f) {
        glVertex3f(-0.5f, 0.101f, j);
        glVertex3f( 0.5f, 0.101f, j);
    }
    glEnd();

    // ==========================================
    // 2. TERAS MENGELILINGI BANGUNAN
    // ==========================================
    glPushMatrix(); { glTranslatef(-2.7f, 0.1f, 0.0f); glScalef(0.6f, 0.2f, 5.4f); drawBalokRumah(0.2f, 0.2f, 0.2f, 1.0f); } glPopMatrix();
    glPushMatrix(); { glTranslatef(-2.65f, 0.3f, 0.0f); glScalef(0.5f, 0.2f, 5.3f); drawBalokRumah(0.3f, 0.3f, 0.3f, 1.0f); } glPopMatrix();

    glPushMatrix(); { glTranslatef(2.7f, 0.1f, 0.0f); glScalef(0.6f, 0.2f, 5.4f); drawBalokRumah(0.2f, 0.2f, 0.2f, 1.0f); } glPopMatrix();
    glPushMatrix(); { glTranslatef(2.65f, 0.3f, 0.0f); glScalef(0.5f, 0.2f, 5.3f); drawBalokRumah(0.3f, 0.3f, 0.3f, 1.0f); } glPopMatrix();

    glPushMatrix(); { glTranslatef(0.0f, 0.1f, -2.7f); glScalef(4.8f, 0.2f, 0.6f); drawBalokRumah(0.2f, 0.2f, 0.2f, 1.0f); } glPopMatrix();
    glPushMatrix(); { glTranslatef(0.0f, 0.3f, -2.65f); glScalef(4.8f, 0.2f, 0.5f); drawBalokRumah(0.3f, 0.3f, 0.3f, 1.0f); } glPopMatrix();

    glPushMatrix(); { glTranslatef(-1.45f, 0.1f, 2.7f); glScalef(1.9f, 0.2f, 0.6f); drawBalokRumah(0.2f, 0.2f, 0.2f, 1.0f); } glPopMatrix();
    glPushMatrix(); { glTranslatef(-1.425f, 0.3f, 2.65f); glScalef(1.95f, 0.2f, 0.5f); drawBalokRumah(0.3f, 0.3f, 0.3f, 1.0f); } glPopMatrix();
    glPushMatrix(); { glTranslatef(1.45f, 0.1f, 2.7f); glScalef(1.9f, 0.2f, 0.6f); drawBalokRumah(0.2f, 0.2f, 0.2f, 1.0f); } glPopMatrix();
    glPushMatrix(); { glTranslatef(1.425f, 0.3f, 2.65f); glScalef(1.95f, 0.2f, 0.5f); drawBalokRumah(0.3f, 0.3f, 0.3f, 1.0f); } glPopMatrix();

    // ==========================================
    // 3. PRASASTI BATU DI TENGAH RUANGAN
    // ==========================================
    glPushMatrix(); {
        glPushMatrix(); glTranslatef(0.0f, 0.15f, 0.0f); glScalef(1.2f, 0.1f, 1.2f); drawBalokRumah(0.1f, 0.1f, 0.1f, 1.0f); glPopMatrix();
        glPushMatrix(); glTranslatef(0.0f, 0.25f, 0.0f); glScalef(0.9f, 0.1f, 0.9f); drawBalokRumah(0.15f, 0.15f, 0.15f, 1.0f); glPopMatrix();
        glPushMatrix(); glTranslatef(0.0f, 0.7f, 0.0f); glScalef(0.5f, 0.8f, 0.5f); drawBalokRumah(0.55f, 0.55f, 0.55f, 1.0f); glPopMatrix();
    } glPopMatrix();

    // ==========================================
    // 4. TIANG UTAMA / STRUKTUR
    // ==========================================
    glPushMatrix(); {
        glPushMatrix(); { glTranslatef(-2.4f, 1.7f, 2.4f); glScalef(0.2f, 3.2f, 0.2f); drawBalokRumah(1.0f, 1.0f, 1.0f, 1.0f); } glPopMatrix();
        glPushMatrix(); { glTranslatef(2.4f, 1.7f, 2.4f); glScalef(0.2f, 3.2f, 0.2f); drawBalokRumah(1.0f, 1.0f, 1.0f, 1.0f); } glPopMatrix();
        glPushMatrix(); { glTranslatef(-2.4f, 1.7f, -2.4f); glScalef(0.2f, 3.2f, 0.2f); drawBalokRumah(1.0f, 1.0f, 1.0f, 1.0f); } glPopMatrix();
        glPushMatrix(); { glTranslatef(2.4f, 1.7f, -2.4f); glScalef(0.2f, 3.2f, 0.2f); drawBalokRumah(1.0f, 1.0f, 1.0f, 1.0f); } glPopMatrix();
        glPushMatrix(); { glTranslatef(0.0f, 3.3f, 0.0f); glScalef(5.2f, 0.2f, 5.2f); drawBalokRumah(1.0f, 1.0f, 1.0f, 1.0f); } glPopMatrix();
    } glPopMatrix();

    // ==========================================
    // 5. DINDING KACA & PINTU (Transparan)
    // ==========================================
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glPushMatrix(); { glTranslatef(0.0f, 1.6f, -2.38f); glScalef(4.6f, 3.0f, 0.04f); drawBalokRumah(0.7f, 0.9f, 1.0f, 0.3f); } glPopMatrix();
    glPushMatrix(); { glTranslatef(-2.38f, 1.6f, 0.0f); glScalef(0.04f, 3.0f, 4.6f); drawBalokRumah(0.7f, 0.9f, 1.0f, 0.3f); } glPopMatrix();
    glPushMatrix(); { glTranslatef(2.38f, 1.6f, 0.0f); glScalef(0.04f, 3.0f, 4.6f); drawBalokRumah(0.7f, 0.9f, 1.0f, 0.3f); } glPopMatrix();

    glPushMatrix(); { glTranslatef(-1.7f, 1.6f, 2.38f); glScalef(1.2f, 3.0f, 0.04f); drawBalokRumah(0.7f, 0.9f, 1.0f, 0.3f); } glPopMatrix();
    glPushMatrix(); { glTranslatef(1.7f, 1.6f, 2.38f); glScalef(1.2f, 3.0f, 0.04f); drawBalokRumah(0.7f, 0.9f, 1.0f, 0.3f); } glPopMatrix();
    glPushMatrix(); { glTranslatef(0.0f, 1.3f, 2.38f); glScalef(1.0f, 2.4f, 0.02f); drawBalokRumah(0.7f, 0.9f, 1.0f, 0.2f); } glPopMatrix();

    glDisable(GL_BLEND);
    glPushMatrix(); { glTranslatef(-0.5f, 1.3f, 2.39f); glScalef(0.04f, 2.4f, 0.04f); drawBalokRumah(1.0f, 1.0f, 1.0f, 1.0f); } glPopMatrix();
    glPushMatrix(); { glTranslatef(0.5f, 1.3f, 2.39f); glScalef(0.04f, 2.4f, 0.04f); drawBalokRumah(1.0f, 1.0f, 1.0f, 1.0f); } glPopMatrix();
    glPushMatrix(); { glTranslatef(0.0f, 2.48f, 2.39f); glScalef(1.0f, 0.04f, 0.04f); drawBalokRumah(1.0f, 1.0f, 1.0f, 1.0f); } glPopMatrix();
    glPushMatrix(); { glTranslatef(0.0f, 0.12f, 2.39f); glScalef(1.0f, 0.04f, 0.04f); drawBalokRumah(1.0f, 1.0f, 1.0f, 1.0f); } glPopMatrix();

    glPushMatrix(); { glTranslatef(0.0f, 1.3f, 2.39f); glScalef(0.03f, 2.4f, 0.03f); drawBalokRumah(1.0f, 1.0f, 1.0f, 1.0f); } glPopMatrix();
    glPushMatrix(); { glTranslatef(0.0f, 1.3f, 2.39f); glScalef(1.0f, 0.03f, 0.03f); drawBalokRumah(1.0f, 1.0f, 1.0f, 1.0f); } glPopMatrix();

    glPopMatrix();
}

void drawAtapRumahPutih() {
    glPushMatrix();

    // ==========================================
    // PENYETELAN SKALA ATAP (WAJIB SAMA DENGAN BADAN RUMAH)
    // ==========================================
    glScalef(1.6f, 1.8f, 1.6f);

    glRotatef(-90.0f, 0.0f, 1.0f, 0.0f);

    // ------------------------------------------
    // 1. LAPISAN PERTAMA: TRAPESIUM KELILING
    // ------------------------------------------
    glColor4f(0.4f, 0.4f, 0.4f, 1.0f);
    glBegin(GL_QUADS);
        glNormal3f(0.0f, 1.0f, 0.0f);
        glVertex3f(-2.4f,  3.6f, -2.4f);
        glVertex3f(-2.4f,  3.6f,  2.4f);
        glVertex3f( 2.4f,  3.6f,  2.4f);
        glVertex3f( 2.4f,  3.6f, -2.4f);

        glNormal3f(0.0f, -1.0f, 0.0f);
        glVertex3f(-2.7f,  2.9f,  2.7f);
        glVertex3f( 2.7f,  2.9f,  2.7f);
        glVertex3f( 2.7f,  2.9f, -2.7f);
        glVertex3f(-2.7f,  2.9f, -2.7f);

        glNormal3f(0.0f, 0.5f, 0.866f);
        glVertex3f(-2.7f,  2.9f,  2.7f);
        glVertex3f( 2.7f,  2.9f,  2.7f);
        glVertex3f( 2.4f,  3.6f,  2.4f);
        glVertex3f(-2.4f,  3.6f,  2.4f);

        glNormal3f(0.0f, 0.5f, -0.866f);
        glVertex3f( 2.7f,  2.9f, -2.7f);
        glVertex3f(-2.7f,  2.9f, -2.7f);
        glVertex3f(-2.4f,  3.6f, -2.4f);
        glVertex3f( 2.4f,  3.6f, -2.4f);

        glNormal3f(0.866f, 0.5f, 0.0f);
        glVertex3f( 2.7f,  2.9f,  2.7f);
        glVertex3f( 2.7f,  2.9f, -2.7f);
        glVertex3f( 2.4f,  3.6f, -2.4f);
        glVertex3f( 2.4f,  3.6f,  2.4f);

        glNormal3f(-0.866f, 0.5f, 0.0f);
        glVertex3f(-2.7f,  2.9f, -2.7f);
        glVertex3f(-2.7f,  2.9f,  2.7f);
        glVertex3f(-2.4f,  3.6f,  2.4f);
        glVertex3f(-2.4f,  3.6f, -2.4f);
    glEnd();

    // ------------------------------------------
    // 2. LAPISAN KEDUA: LIMAS SEGIEMPAT
    // ------------------------------------------
    glColor4f(0.25f, 0.25f, 0.25f, 1.0f);
    float pX = 0.0f, pY = 4.6f, pZ = 0.0f;

    glBegin(GL_TRIANGLES);
        glNormal3f(0.0f, 0.5f, 0.866f);
        glVertex3f(-2.4f, 3.605f,  2.4f);
        glVertex3f( 2.4f, 3.605f,  2.4f);
        glVertex3f( pX,   pY,      pZ);

        glNormal3f(0.866f, 0.5f, 0.0f);
        glVertex3f( 2.4f, 3.605f,  2.4f);
        glVertex3f( 2.4f, 3.605f, -2.4f);
        glVertex3f( pX,   pY,      pZ);

        glNormal3f(0.0f, 0.5f, -0.866f);
        glVertex3f( 2.4f, 3.605f, -2.4f);
        glVertex3f(-2.4f, 3.605f, -2.4f);
        glVertex3f( pX,   pY,      pZ);

        glNormal3f(-0.866f, 0.5f, 0.0f);
        glVertex3f(-2.4f, 3.605f, -2.4f);
        glVertex3f(-2.4f, 3.605f,  2.4f);
        glVertex3f( pX,   pY,      pZ);
    glEnd();

    glPopMatrix();
}
