#include "objekTaman.h"
#include <GLFW/glfw3.h>
#include <cmath>

// ==========================================
// FUNGSI PEMBANTU INTERN: SILINDER (Untuk Batang & Tiang)
// ==========================================
void drawSilinderTaman(float radius, float tinggi, float r, float g, float b) {
    glColor3f(r, g, b);
    int slices = 16;

    // Sisi Tegak Silinder
    glBegin(GL_QUAD_STRIP);
    for (int i = 0; i <= slices; i++) {
        float angle = 2.0f * 3.14159f * i / slices;
        float x = cos(angle) * radius;
        float z = sin(angle) * radius;

        glNormal3f(cos(angle), 0.0f, sin(angle));
        glVertex3f(x, 0.0f, z);
        glVertex3f(x, tinggi, z);
    }
    glEnd();

    // Penutup Atas Silinder
    glBegin(GL_TRIANGLE_FAN);
    glNormal3f(0.0f, 1.0f, 0.0f);
    glVertex3f(0.0f, tinggi, 0.0f);
    for (int i = 0; i <= slices; i++) {
        float angle = 2.0f * 3.14159f * i / slices;
        glVertex3f(cos(angle) * radius, tinggi, sin(angle) * radius);
    }
    glEnd();
}

// ==========================================
// FUNGSI PEMBANTU INTERN: KERUCUT/BOLA (Untuk Daun)
// ==========================================
void drawKerucutDaun(float radius, float tinggi, float r, float g, float b) {
    glColor3f(r, g, b);
    int slices = 16;

    glBegin(GL_TRIANGLE_FAN);
    glNormal3f(0.0f, 1.0f, 0.0f);
    glVertex3f(0.0f, tinggi, 0.0f); // Titik Puncak
    for (int i = 0; i <= slices; i++) {
        float angle = 2.0f * 3.14159f * i / slices;
        glNormal3f(cos(angle), 0.5f, sin(angle));
        glVertex3f(cos(angle) * radius, 0.0f, sin(angle) * radius);
    }
    glEnd();
}

// ==========================================
// 1. OBJEK POHON RINDANG BERUNDAK
// ==========================================
void drawPohonTaman(float posX, float posY, float posZ, float skala) {
    glPushMatrix();
    glTranslatef(posX, posY, posZ);
    glScalef(skala, skala, skala);

    // Batas bawah tanah rata Y = 0
    // Batang Pohon (Cokelat)
    drawSilinderTaman(0.15f, 0.8f, 0.4f, 0.25f, 0.15f);

    // Daun Lapisan 1 (Bawah - Hijau Tua)
    glPushMatrix();
    glTranslatef(0.0f, 0.7f, 0.0f);
    drawKerucutDaun(0.8f, 1.0f, 0.0f, 0.45f, 0.1f);
    glPopMatrix();

    // Daun Lapisan 2 (Tengah - Hijau Cerah)
    glPushMatrix();
    glTranslatef(0.0f, 1.3f, 0.0f);
    drawKerucutDaun(0.6f, 0.8f, 0.0f, 0.55f, 0.15f);
    glPopMatrix();

    // Daun Lapisan 3 (Puncak - Hijau Muda)
    glPushMatrix();
    glTranslatef(0.0f, 1.8f, 0.0f);
    drawKerucutDaun(0.4f, 0.6f, 0.1f, 0.65f, 0.2f);
    glPopMatrix();

    glPopMatrix();
}

// ==========================================
// 2. OBJEK LAMPU TAMAN MINIMALIS MODERN
// ==========================================
void drawLampuTaman(float posX, float posY, float posZ) {
    glPushMatrix();
    glTranslatef(posX, posY, posZ);

    // Dudukan Pondasi Bawah (Hitam)
    glPushMatrix();
    glTranslatef(0.0f, 0.05f, 0.0f);
    glScalef(0.2f, 0.1f, 0.2f);
    // Asumsi fungsi pembantu kotak standar, jika tidak ada ganti dengan BALOK/QUADS biasa
    glColor3f(0.1f, 0.1f, 0.1f);
    glBegin(GL_QUADS);
        glVertex3f(-0.5f, 0.5f, 0.5f); glVertex3f(0.5f, 0.5f, 0.5f); glVertex3f(0.5f, -0.5f, 0.5f); glVertex3f(-0.5f, -0.5f, 0.5f);
        glVertex3f(-0.5f, 0.5f, -0.5f); glVertex3f(0.5f, 0.5f, -0.5f); glVertex3f(0.5f, -0.5f, -0.5f); glVertex3f(-0.5f, -0.5f, -0.5f);
        glVertex3f(-0.5f, 0.5f, -0.5f); glVertex3f(-0.5f, 0.5f, 0.5f); glVertex3f(-0.5f, -0.5f, 0.5f); glVertex3f(-0.5f, -0.5f, -0.5f);
        glVertex3f(0.5f, 0.5f, -0.5f); glVertex3f(0.5f, 0.5f, 0.5f); glVertex3f(0.5f, -0.5f, 0.5f); glVertex3f(0.5f, -0.5f, -0.5f);
        glVertex3f(-0.5f, 0.5f, -0.5f); glVertex3f(0.5f, 0.5f, -0.5f); glVertex3f(0.5f, 0.5f, 0.5f); glVertex3f(-0.5f, 0.5f, 0.5f);
    glEnd();
    glPopMatrix();

    // Tiang Lampu Tinggi (Hitam/Abu Gelap)
    drawSilinderTaman(0.04f, 1.2f, 0.15f, 0.15f, 0.15f);

    // Rumah Lampu / Kap Atas (Kotak Hitam)
    glPushMatrix();
    glTranslatef(0.0f, 1.3f, 0.0f);
    glScalef(0.18f, 0.15f, 0.18f);
    glColor3f(0.1f, 0.1f, 0.1f);
    glBegin(GL_QUADS);
        glVertex3f(-0.5f, 0.5f, 0.5f); glVertex3f(0.5f, 0.5f, 0.5f); glVertex3f(0.5f, -0.5f, 0.5f); glVertex3f(-0.5f, -0.5f, 0.5f);
        glVertex3f(-0.5f, 0.5f, -0.5f); glVertex3f(0.5f, 0.5f, -0.5f); glVertex3f(0.5f, -0.5f, -0.5f); glVertex3f(-0.5f, -0.5f, -0.5f);
    glEnd();
    glPopMatrix();

    // Inti Bohlam Lampu (Kuning Glow)
    glPushMatrix();
    glTranslatef(0.0f, 1.18f, 0.0f);
    glScalef(0.12f, 0.12f, 0.12f);
    glColor3f(1.0f, 0.9f, 0.4f); // Kuning hangat
    glBegin(GL_QUADS);
        glVertex3f(-0.5f, 0.5f, 0.5f); glVertex3f(0.5f, 0.5f, 0.5f); glVertex3f(0.5f, -0.5f, 0.5f); glVertex3f(-0.5f, -0.5f, 0.5f);
        glVertex3f(-0.5f, 0.5f, -0.5f); glVertex3f(0.5f, 0.5f, -0.5f); glVertex3f(0.5f, -0.5f, -0.5f); glVertex3f(-0.5f, -0.5f, -0.5f);
    glEnd();
    glPopMatrix();

    glPopMatrix();
}


// ==========================================
// FUNGSI PEMBANTU INTERN: KOTAK DAN SEGIEMPAT (Untuk Kelopak Bunga)
// ==========================================
void drawKelopakBunga(float r, float g, float b, float size) {
    glColor3f(r, g, b);
    glBegin(GL_QUADS);
        glNormal3f(0.0f, 1.0f, 0.0f);
        glVertex3f(-size, 0.0f, -size);
        glVertex3f(-size, 0.0f,  size);
        glVertex3f( size, 0.0f,  size);
        glVertex3f( size, 0.0f, -size);
    glEnd();
}

// ==========================================
// 3. OBJEK SEMAK-SEMAK BULAT (BUSH)
// Menggunakan tumpukan bola-bola/kerucut tumpul hijau agar bertekstur alami
// ==========================================
void drawSemakTaman(float posX, float posY, float posZ, float skala) {
    glPushMatrix();
    glTranslatef(posX, posY, posZ);
    glScalef(skala, skala, skala);

    // Bola utama di tengah
    glPushMatrix();
    glTranslatef(0.0f, 0.2f, 0.0f);
    drawKerucutDaun(0.4f, 0.4f, 0.0f, 0.35f, 0.05f); // Menggunakan fungsi drawKerucutDaun sebelumnya
    glPopMatrix();

    // Rumpun kecil di sisi kiri
    glPushMatrix();
    glTranslatef(-0.25f, 0.15f, 0.1f);
    drawKerucutDaun(0.3f, 0.3f, 0.0f, 0.4f, 0.08f);
    glPopMatrix();

    // Rumpun kecil di sisi kanan
    glPushMatrix();
    glTranslatef(0.25f, 0.15f, -0.1f);
    drawKerucutDaun(0.3f, 0.3f, 0.0f, 0.38f, 0.06f);
    glPopMatrix();

    // Rumpun kecil di sisi depan
    glPushMatrix();
    glTranslatef(0.1f, 0.12f, 0.25f);
    drawKerucutDaun(0.25f, 0.25f, 0.0f, 0.45f, 0.1f);
    glPopMatrix();

    glPopMatrix();
}

// ==========================================
// 4. OBJEK TANAMAN BUNGA KECIL
// Terdiri dari batang hijau tegak dan kelopak warna-warni melingkar
// ==========================================
void drawBungaTaman(float posX, float posY, float posZ, float rBunga, float gBunga, float bBunga) {
    glPushMatrix();
    glTranslatef(posX, posY, posZ);

    // Batang Tangkai Bunga (Hijau)
    drawSilinderTaman(0.015f, 0.3f, 0.1f, 0.5f, 0.1f); // Menggunakan fungsi drawSilinderTaman sebelumnya

    // Kepala Bunga (Dinaikkan ke ujung tangkai Y=0.3f)
    glPushMatrix();
    glTranslatef(0.0f, 0.3f, 0.0f);

    // Inti Tengah Bunga (Kuning)
    drawKelopakBunga(1.0f, 0.8f, 0.0f, 0.03f);

    // Kelopak 1 & 2 (Membentuk Tanda Tambah)
    glPushMatrix(); glRotatef(30.0f, 0.0f, 1.0f, 0.0f); drawKelopakBunga(rBunga, gBunga, bBunga, 0.06f); glPopMatrix();
    glPushMatrix(); glRotatef(90.0f, 0.0f, 1.0f, 0.0f); drawKelopakBunga(rBunga, gBunga, bBunga, 0.06f); glPopMatrix();
    glPushMatrix(); glRotatef(150.0f, 0.0f, 1.0f, 0.0f); drawKelopakBunga(rBunga, gBunga, bBunga, 0.06f); glPopMatrix();

    glPopMatrix();
    glPopMatrix();
}
