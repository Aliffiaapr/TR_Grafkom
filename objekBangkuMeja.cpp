#include "objekBangkuMeja.h"
#include "balok.h" // Wajib include ini agar bisa menggunakan gambarBalok

void drawBangkuMeja() {
    // WARNA KAYU UTAMA & CORAK
    float rKayu = 0.54f, gKayu = 0.27f, bKayu = 0.07f;               // Cokelat Utama
    float rKayuGelap = 0.35f, gKayuGelap = 0.18f, bKayuGelap = 0.04f;       // Rangka & Kaki
    float rGarisKayu = 0.25f, gGarisKayu = 0.12f, bGarisKayu = 0.02f;       // Warna Tekstur Serat Kayu

    // ==========================================
    // 1. PAPAN UTAMA MEJA (Mendatar di Atas)
    // ==========================================
    gambarBalok(-2.2f,  2.2f,  1.4f,  1.55f, -1.2f,  1.2f,  rKayu,  gKayu,  bKayu);

    // TEKSTUR GARIS PAPAN MEJA ATAS
    glLineWidth(2.0f);
    glColor3f(rGarisKayu, gGarisKayu, bGarisKayu);
    glBegin(GL_LINES);
    for (float z = -1.0f; z <= 1.0f; z += 0.25f) {
        glVertex3f(-2.2f, 1.551f, z);
        glVertex3f( 2.2f, 1.551f, z);
    }
    glEnd();

    // ==========================================
    // 2. PAPAN BANGKU DUDUKAN (DIBESARKAN & DIPERTEBAL)
    // ==========================================
    // Bangku Kiri (Z: -2.3f s/d -1.5f)
    gambarBalok(-2.2f,  2.2f,  0.6f,  0.8f, -2.3f, -1.5f,  rKayu,  gKayu,  bKayu);

    // Bangku Kanan (Z: 1.5f s/d 2.3f)
    gambarBalok(-2.2f,  2.2f,  0.6f,  0.8f,  1.5f,  2.3f,  rKayu,  gKayu,  bKayu);

    // ==========================================
    // PERBAIKAN TOTAL: TEKSTUR GARIS SERAT DI ATAS ALAS DUDUK BANGKU BARU
    // ==========================================
    glBegin(GL_LINES);
    // 1. Garis tekstur memanjang pas di permukaan Bangku Kiri (Z dari -2.2f sampai -1.6f)
    for (float z = -2.15f; z <= -1.65f; z += 0.15f) {
        glVertex3f(-2.2f, 0.801f, z);
        glVertex3f( 2.2f, 0.801f, z);
    }

    // 2. Garis tekstur memanjang pas di permukaan Bangku Kanan (Z dari 1.6f sampai 2.2f)
    for (float z = 1.65f; z <= 2.15f; z += 0.15f) {
        glVertex3f(-2.2f, 0.801f, z);
        glVertex3f( 2.2f, 0.801f, z);
    }
    glEnd();

    // ==========================================
    // 3. RANGKA PENYANGGA HORIZONTAL
    // ==========================================
    gambarBalok(-1.6f, -1.3f,  0.4f,  0.6f, -2.3f,  2.3f,  rKayuGelap, gKayuGelap, bKayuGelap);
    gambarBalok( 1.3f,  1.6f,  0.4f,  0.6f, -2.3f,  2.3f,  rKayuGelap, gKayuGelap, bKayuGelap);

    // ==========================================
    // 4. KAKI-KAKI MEJA (Struktur Penopang Silang)
    // ==========================================
    // Kaki Kiri
    gambarBalok(-1.6f, -1.3f,  0.0f,  1.4f, -0.9f, -0.6f,  rKayuGelap, gKayuGelap, bKayuGelap);
    gambarBalok(-1.6f, -1.3f,  0.0f,  1.4f,  0.6f,  0.9f,  rKayuGelap, gKayuGelap, bKayuGelap);

    // Kaki Kanan
    gambarBalok( 1.3f,  1.6f,  0.0f,  1.4f, -0.9f, -0.6f,  rKayuGelap, gKayuGelap, bKayuGelap);
    gambarBalok( 1.3f,  1.6f,  0.0f,  1.4f,  0.6f,  0.9f,  rKayuGelap, gKayuGelap, bKayuGelap);
}
