#include "objekBangku.h" // Pastikan nama header sesuai
#include <GLFW/glfw3.h>

// ==========================================
// FUNGSI PEMBANTU INTERNAL (MENGGAMBAR BALOK)
// ==========================================
void drawBalokKhususBangku(float r, float g, float b) {
    glColor3f(r, g, b);
    glBegin(GL_QUADS);
        // Sisi Depan
        glNormal3f(0.0f, 0.0f, 1.0f);
        glVertex3f(-0.5f, -0.5f,  0.5f); glVertex3f( 0.5f, -0.5f,  0.5f); glVertex3f( 0.5f,  0.5f,  0.5f); glVertex3f(-0.5f,  0.5f,  0.5f);
        // Sisi Belakang
        glNormal3f(0.0f, 0.0f, -1.0f);
        glVertex3f(-0.5f, -0.5f, -0.5f); glVertex3f(-0.5f,  0.5f, -0.5f); glVertex3f( 0.5f,  0.5f, -0.5f); glVertex3f( 0.5f, -0.5f, -0.5f);
        // Sisi Atas
        glNormal3f(0.0f, 1.0f, 0.0f);
        glVertex3f(-0.5f,  0.5f, -0.5f); glVertex3f(-0.5f,  0.5f,  0.5f); glVertex3f( 0.5f,  0.5f,  0.5f); glVertex3f( 0.5f,  0.5f, -0.5f);
        // Sisi Bawah
        glNormal3f(0.0f, -1.0f, 0.0f);
        glVertex3f(-0.5f, -0.5f, -0.5f); glVertex3f( 0.5f, -0.5f, -0.5f); glVertex3f( 0.5f, -0.5f,  0.5f); glVertex3f(-0.5f, -0.5f,  0.5f);
        // Sisi Kanan
        glNormal3f(1.0f, 0.0f, 0.0f);
        glVertex3f( 0.5f, -0.5f, -0.5f); glVertex3f( 0.5f,  0.5f, -0.5f); glVertex3f( 0.5f,  0.5f,  0.5f); glVertex3f( 0.5f, -0.5f,  0.5f);
        // Sisi Kiri
        glNormal3f(-1.0f, 0.0f, 0.0f);
        glVertex3f(-0.5f, -0.5f, -0.5f); glVertex3f(-0.5f, -0.5f,  0.5f); glVertex3f(-0.5f,  0.5f,  0.5f); glVertex3f(-0.5f,  0.5f, -0.5f);
    glEnd();
}

// ==========================================
// FUNGSI UTAMA: MENGGAMBAR BANGKU KAYU (DIPERBESAR GLOBAL)
// ==========================================
void drawBangkuKayu(float posX, float posY, float posZ, bool pakeSandaran) {
    glPushMatrix();

    // 1. Atur posisi koordinat bangku di dunia 3D
    glTranslatef(posX, posY, posZ);

    // ==========================================
    // BARU: PENYETELAN SKALA GLOBAL (DIPERBESAR 1.5 KALI LIPAT)
    // Ditulis tepat setelah glTranslatef agar membesar pas di titik koordinatnya
    // ==========================================
    glScalef(1.5f, 1.5f, 1.5f);

    // Memutar kursi agar default-nya langsung menghadap ke kiri
    glRotatef(-90.0f, 0.0f, 1.0f, 0.0f);

    // Warna Cokelat Kayu Natural
    float r = 0.55f, g = 0.32f, b = 0.18f;
    // Warna Penyangga Sandaran (Lebih Gelap)
    float rb = 0.3f, gb = 0.18f, bb = 0.1f;

    // ------------------------------------------
    // A. KAKI-KAKI BANGKU (4 Buah Kaki Tegak Lurus)
    // ------------------------------------------
    glPushMatrix(); glTranslatef(-0.9f, 0.325f, 0.35f); glScalef(0.12f, 0.65f, 0.12f); drawBalokKhususBangku(r, g, b); glPopMatrix();
    glPushMatrix(); glTranslatef(0.9f, 0.325f, 0.35f); glScalef(0.12f, 0.65f, 0.12f); drawBalokKhususBangku(r, g, b); glPopMatrix();
    glPushMatrix(); glTranslatef(-0.9f, 0.325f, -0.35f); glScalef(0.12f, 0.65f, 0.12f); drawBalokKhususBangku(r, g, b); glPopMatrix();
    glPushMatrix(); glTranslatef(0.9f, 0.325f, -0.35f); glScalef(0.12f, 0.65f, 0.12f); drawBalokKhususBangku(r, g, b); glPopMatrix();

    // ------------------------------------------
    // B. PAPAN ALAS DUDUKAN (3 Bilah Papan Ukuran Besar)
    // ------------------------------------------
    glPushMatrix();
    glTranslatef(0.0f, 0.67f, 0.0f);
    glPushMatrix(); glTranslatef(0.0f, 0.0f, -0.24f); glScalef(2.2f, 0.06f, 0.18f); drawBalokKhususBangku(r, g, b); glPopMatrix();
    glPushMatrix(); glTranslatef(0.0f, 0.0f, 0.0f); glScalef(2.2f, 0.06f, 0.18f); drawBalokKhususBangku(r, g, b); glPopMatrix();
    glPushMatrix(); glTranslatef(0.0f, 0.0f, 0.24f); glScalef(2.2f, 0.06f, 0.18f); drawBalokKhususBangku(r, g, b); glPopMatrix();
    glPopMatrix();

    // ------------------------------------------
    // C. STRUKTUR SANDARAN (Miring Ergonomis -12 Derajat)
    // ------------------------------------------
    if (pakeSandaran) {
        glPushMatrix();
        glTranslatef(0.0f, 0.67f, -0.35f);
        glRotatef(-12.0f, 1.0f, 0.0f, 0.0f); // Merebah ke belakang

        // Tiang Penyangga Kiri & Kanan
        glPushMatrix(); glTranslatef(-0.8f, 0.38f, -0.01f); glScalef(0.08f, 0.8f, 0.06f); drawBalokKhususBangku(rb, gb, bb); glPopMatrix();
        glPushMatrix(); glTranslatef(0.8f, 0.38f, -0.01f); glScalef(0.08f, 0.8f, 0.06f); drawBalokKhususBangku(rb, gb, bb); glPopMatrix();

        // 4 Bilah Papan Sandaran Berjejer ke Atas
        glPushMatrix(); glTranslatef(0.0f, 0.18f, -0.05f); glScalef(2.2f, 0.12f, 0.04f); drawBalokKhususBangku(r, g, b); glPopMatrix();
        glPushMatrix(); glTranslatef(0.0f, 0.35f, -0.05f); glScalef(2.2f, 0.12f, 0.04f); drawBalokKhususBangku(r, g, b); glPopMatrix();
        glPushMatrix(); glTranslatef(0.0f, 0.52f, -0.05f); glScalef(2.2f, 0.12f, 0.04f); drawBalokKhususBangku(r, g, b); glPopMatrix();
        glPushMatrix(); glTranslatef(0.0f, 0.69f, -0.05f); glScalef(2.2f, 0.12f, 0.04f); drawBalokKhususBangku(r, g, b); glPopMatrix();

        glPopMatrix();
    }

    glPopMatrix();
}
