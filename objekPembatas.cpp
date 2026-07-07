#include "objekPembatas.h"

// Memanggil fungsi cetakan kubus dari main.cpp
extern void drawCube(float lebar, float tinggi, float panjang);

void drawPagarSegment(float panjangTotal) {
    // -----------------------------------------------------------------
    // 1. PILAR UTAMA (Kiri & Kanan) - Cokelat Muda / Khaki
    // -----------------------------------------------------------------
    glColor3f(0.76f, 0.60f, 0.42f); // Warna Cokelat Muda sesuai request sebelumnya

    // Pilar Kiri (Ada detail mahkota pilar di atasnya)
    glPushMatrix();
        glTranslatef(0.0f, 1.4f, 0.0f); // Tinggi pilar total 2.8 unit
        drawCube(0.8f, 2.8f, 0.8f);
        // Topi/Mahkota Pilar Kiri
        glTranslatef(0.0f, 1.45f, 0.0f);
        drawCube(0.95f, 0.15f, 0.95f);
    glPopMatrix();

    // Pilar Kanan
    glPushMatrix();
        glTranslatef(panjangTotal, 1.4f, 0.0f);
        drawCube(0.8f, 2.8f, 0.8f);
        // Topi/Mahkota Pilar Kanan
        glTranslatef(0.0f, 1.45f, 0.0f);
        drawCube(0.95f, 0.15f, 0.95f);
    glPopMatrix();

    // -----------------------------------------------------------------
    // 2. STRUKTUR BINGKAI BETON (Fondasi Bawah & Topi Atas Diperbesar)
    // -----------------------------------------------------------------
    // Fondasi Bawah (Sloof) - Abu-abu bersih
    glColor3f(0.8f, 0.8f, 0.8f);
    glPushMatrix();
        glTranslatef(panjangTotal / 2.0f, 0.2f, 0.0f);
        drawCube(panjangTotal - 0.8f, 0.4f, 0.6f);
    glPopMatrix();

    // Topi Atas Dinding (List Ban) - Cokelat Medium, Tebal & Menonjol
    glColor3f(0.59f, 0.41f, 0.24f);
    glPushMatrix();
        glTranslatef(panjangTotal / 2.0f, 2.5f, 0.0f);
        drawCube(panjangTotal - 0.8f, 0.35f, 0.65f); // Tebal 0.35f, menonjol di Z = 0.65f
    glPopMatrix();

    // -----------------------------------------------------------------
    // 3. BADAN UTAMA DINDING (Cokelat Muda - Kiri & Kanan Saja)
    // -----------------------------------------------------------------
    glColor3f(0.76f, 0.60f, 0.42f);

    // Kita bagi dinding jadi 2 blok solid (atas dan bawah area lubang)
    // Blok Dinding Bawah Lubang
    glPushMatrix();
        glTranslatef(panjangTotal / 2.0f, 0.9f, 0.0f); // Tinggi dari Y=0.4 sampai Y=1.4
        drawCube(panjangTotal - 0.8f, 1.0f, 0.5f);
    glPopMatrix();

    // Blok Dinding Atas Lubang
    glPushMatrix();
        glTranslatef(panjangTotal / 2.0f, 2.15f, 0.0f); // Tinggi dari Y=2.0 sampai Y=2.3
        drawCube(panjangTotal - 0.8f, 0.3f, 0.5f);
    glPopMatrix();

    // -----------------------------------------------------------------
    // 4. PATTERN: LUBANG KOTAK BALOK HORIZONTAL (ROSTER)
    // -----------------------------------------------------------------
    // Menggunakan teknik perulangan balok vertikal kecil di sepanjang sumbu X
    // pada ketinggian Y = 1.7f untuk memecah ruang kosong menjadi pola lubang balok

    float jarakAntarSekat = 1.2f; // Mengatur panjang lubang balok horizontal
    int jumlahSekat = (int)(panjangTotal / jarakAntarSekat);

    for (int i = 1; i <= jumlahSekat; i++) {
        float posX = i * jarakAntarSekat;

        // Proteksi agar sekat pembatas tidak menabrak tiang pilar utama
        if (posX > 0.6f && posX < (panjangTotal - 0.6f)) {
            glPushMatrix();
                // Mengisi ruang kosong di antara dinding bawah dan dinding atas (Tinggi 0.6f)
                glTranslatef(posX, 1.7f, 0.0f);
                drawCube(0.4f, 0.6f, 0.5f); // Lebar sekat 0.4f membuat celah kosong di antaranya berbentuk balok
            glPopMatrix();
        }
    }
}
