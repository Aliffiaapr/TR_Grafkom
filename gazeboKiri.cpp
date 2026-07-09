#include "gazeboKiri.h"
#include "balok.h"
#include <GLFW/glfw3.h> // Pastikan library GLFW/OpenGL disertakan

void gambarGazeboKiri() {
    float rKayu = 0.35f, gKayu = 0.18f, bKayu = 0.08f; // Cokelat gelap untuk tiang & pagar

    // WARNA ALAS: Cokelat kayu terang kontras
    float rAlas = 0.65f, gAlas = 0.42f, bAlas = 0.23f;
    // WARNA GARIS PAPAN: Cokelat pekat untuk sela-sela lantai
    float rGarisAlas = 0.25f, gGarisAlas = 0.12f, bGarisAlas = 0.02f;

    // Warna abu-abu semen untuk lantai teras dasar
    float rSemen = 0.55f, gSemen = 0.55f, bSemen = 0.55f;

    glPushMatrix();

    // 1. KEMBALIKAN KE KOORDINAT SEMULA AFTER SCALE
    glTranslatef(-3.9f, 0.0f, 0.0f);

    // 2. PERBESAR KELEBARAN (X = 3.2f, Z = 3.2f) DAN TINGGI MELEJIT (Y = 4.0f)
    glScalef(3.2f, 4.0f, 3.2f);

    // 3. TARIK TITIK PUSAT OBJEK (X = -3.9) KE POROS DUNIA (0,0,0) UNTUK DI-SCALE
    glTranslatef(3.9f, 0.0f, 0.0f);

    // =================================================================
    // 1. LANTAI TERAS SEMEN DASAR (Diperluas sedikit agar pondasi kuat)
    // =================================================================
    gambarBalok(-5.2f, -2.6f, 0.0f, 0.05f, -1.9f, 1.9f, rSemen, gSemen, bSemen);

    // =================================================================
    // 2. IMPLEMENTASI IDE 1: ALAS DUDUK MELUBER KELUAR TIANG (LEBIH LUAS)
    // Koordinat X diperlebar ke (-5.0f s/d -2.8f) & Z diperlebar ke (-1.7f s/d 1.7f)
    // =================================================================
    gambarBalok(-5.0f, -2.8f, 0.2f, 0.3f, -1.7f, 1.7f, rAlas, gAlas, bAlas);

    // =================================================================
    // 3. IMPLEMENTASI IDE 2: TEKSTUR GARIS PAPAN GRID (MEMPERTEGAS SKALA LUAS)
    // Ditaruh pas di tinggi Y = 0.301f (di atas alas sedikit agar tidak berkedip)
    // =================================================================
    glLineWidth(1.5f);
    glColor3f(rGarisAlas, gGarisAlas, bGarisAlas);
    glBegin(GL_LINES);
    // Membuat guratan garis sekat papan kayu membujur dari belakang ke depan
    for (float x = -4.9f; x <= -2.9f; x += 0.3f) {
        glVertex3f(x, 0.301f, -1.69f);
        glVertex3f(x, 0.301f,  1.69f);
    }
    glEnd();

    // ==========================================
    // 4. TIANG-TIANG GAZEBO (MENAPAK DI ATAS SEMEN)
    // ==========================================
    gambarBalok(-4.8f, -4.7f, 0.05f, 1.2f, -1.5f, -1.4f, rKayu, gKayu, bKayu);
    gambarBalok(-3.1f, -3.0f, 0.05f, 1.2f, -1.5f, -1.4f, rKayu, gKayu, bKayu);
    gambarBalok(-4.8f, -4.7f, 0.05f, 1.2f,  1.4f,  1.5f, rKayu, gKayu, bKayu);
    gambarBalok(-3.1f, -3.0f, 0.05f, 1.2f,  1.4f,  1.5f, rKayu, gKayu, bKayu);

    // ==========================================
    // 5. PAGAR HORIZONTAL 3 LAPIS KAYU
    // ==========================================
    float yLapis[3][2] = {
        {0.32f, 0.38f}, // Papan 1
        {0.40f, 0.46f}, // Papan 2
        {0.48f, 0.54f}  // Papan 3
    };

    for (int i = 0; i < 3; i++) {
        float yMin = yLapis[i][0];
        float yMax = yLapis[i][1];

        // Pagar Horizontal Sisi KIRI
        gambarBalok(-4.8f, -4.7f, yMin, yMax, -1.4f, 1.4f, rKayu, gKayu, bKayu);

        // Pagar Horizontal Sisi BELAKANG
        gambarBalok(-4.7f, -3.1f, yMin, yMax, -1.5f, -1.4f, rKayu, gKayu, bKayu);

        // Pagar Horizontal Sisi DEPAN LOKAL
        gambarBalok(-4.7f, -3.1f, yMin, yMax, 1.4f, 1.5f, rKayu, gKayu, bKayu);
    }

    // ==========================================
    // 6. KOMPONEN ATAP PIRAMIDA GAZEBO
    // ==========================================
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

    glPopMatrix();
}
