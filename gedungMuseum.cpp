#include "gedungMuseum.h"
#include "balok.h"
#include "stb_image.h"
#include "objekGanesha.h"
#include <iostream>
#include <cmath>

#ifndef GL_CLAMP_TO_EDGE
#define GL_CLAMP_TO_EDGE 0x812F
#endif

// =========================================================================
// VARIABEL TEKSTUR
// =========================================================================
static GLuint museumSignTex = 0;
static GLuint posterPrasastiTex = 0;
static GLuint posterLegendaTex = 0;
static GLuint posterProklamasiTex = 0;
static GLuint posterPetaTex = 0;
static GLuint arcaGaneshaTex = 0;
static GLuint arcaDuaSisiTex = 0;

static bool texLoaded = false;

static GLuint loadTexture(const char* path) {
    GLuint tex = 0;
    int width, height, nrChannels;
    unsigned char *data = stbi_load(path, &width, &height, &nrChannels, 4);
    if (data) {
        glGenTextures(1, &tex);
        glBindTexture(GL_TEXTURE_2D, tex);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        stbi_image_free(data);
        std::cout << "Berhasil memuat tekstur: " << path << std::endl;
    } else {
        std::cout << "GAGAL memuat tekstur: " << path << std::endl;
    }
    return tex;
}

void initMuseumTextures() {
    if (texLoaded) return;
    stbi_set_flip_vertically_on_load(true);
    
    museumSignTex = loadTexture("museum_sign.jpg");
    posterPrasastiTex = loadTexture("poster_prasasti.jpg");
    posterLegendaTex = loadTexture("poster_legenda.jpg");
    posterProklamasiTex = loadTexture("poster_proklamasi.jpg");
    posterPetaTex = loadTexture("poster_peta.jpg");
    arcaGaneshaTex = loadTexture("arca_ganesha.jpg");
    arcaDuaSisiTex = loadTexture("arca_duasisi.jpg");

    texLoaded = true;
}

// =========================================================================
// HELPER: GAMBAR POSTER DENGAN TEKSTUR
// =========================================================================
static void gambarPosterTekstur(float xMin, float xMax, float yMin, float yMax, float zMin, float zMax, GLuint tex, int axis) {
    // axis: 0 = X face (dinding kanan, hadap ke dalam), 2 = Z face (dinding belakang, hadap depan)
    if (tex != 0) {
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, tex);
        glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
        
        if (axis == 2) { // Dinding belakang - hadap depan (Z+)
            glBegin(GL_QUADS);
            glNormal3f(0.0f, 0.0f, 1.0f);
            glTexCoord2f(0.0f, 0.0f); glVertex3f(xMin, yMin, zMax);
            glTexCoord2f(1.0f, 0.0f); glVertex3f(xMax, yMin, zMax);
            glTexCoord2f(1.0f, 1.0f); glVertex3f(xMax, yMax, zMax);
            glTexCoord2f(0.0f, 1.0f); glVertex3f(xMin, yMax, zMax);
            glEnd();
        } else if (axis == 0) { // Dinding kanan - hadap ke dalam ruangan (X-)
            // Gambar di sisi DALAM dinding kanan (menghadap ke kiri/ke dalam ruangan)
            float xFace = xMin; // Pakai xMin agar menonjol keluar dari frame, tidak tertutup di dalam kotak frame
            glBegin(GL_QUADS);
            glNormal3f(-1.0f, 0.0f, 0.0f);
            glTexCoord2f(0.0f, 0.0f); glVertex3f(xFace, yMin, zMax); // Kiri bawah (depan)
            glTexCoord2f(1.0f, 0.0f); glVertex3f(xFace, yMin, zMin); // Kanan bawah (belakang)
            glTexCoord2f(1.0f, 1.0f); glVertex3f(xFace, yMax, zMin); // Kanan atas (belakang)
            glTexCoord2f(0.0f, 1.0f); glVertex3f(xFace, yMax, zMax); // Kiri atas (depan)
            glEnd();
        }
        glDisable(GL_TEXTURE_2D);
    } else {
        // Fallback: kotak abu-abu
        gambarBalok(xMin, xMax, yMin, yMax, zMin, zMax, 0.3f, 0.3f, 0.3f);
    }
}

// =========================================================================
// HELPER: GAMBAR BALOK 3D DENGAN TEKSTUR DI DEPAN+BELAKANG
// Dipakai untuk arca agar terlihat dari segala arah (sisi samping warna solid)
// =========================================================================
static void gambarBalokTekstur(float xMin, float xMax, float yMin, float yMax, float zMin, float zMax, GLuint tex, float r, float g, float b) {
    // Sisi DEPAN dan BELAKANG: pakai tekstur
    if (tex != 0) {
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, tex);
        glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
        // Depan (Z+)
        glBegin(GL_QUADS);
        glNormal3f(0.0f, 0.0f, 1.0f);
        glTexCoord2f(0.0f, 0.0f); glVertex3f(xMin, yMin, zMax);
        glTexCoord2f(1.0f, 0.0f); glVertex3f(xMax, yMin, zMax);
        glTexCoord2f(1.0f, 1.0f); glVertex3f(xMax, yMax, zMax);
        glTexCoord2f(0.0f, 1.0f); glVertex3f(xMin, yMax, zMax);
        glEnd();
        // Belakang (Z-)
        glBegin(GL_QUADS);
        glNormal3f(0.0f, 0.0f, -1.0f);
        glTexCoord2f(1.0f, 0.0f); glVertex3f(xMin, yMin, zMin);
        glTexCoord2f(1.0f, 1.0f); glVertex3f(xMin, yMax, zMin);
        glTexCoord2f(0.0f, 1.0f); glVertex3f(xMax, yMax, zMin);
        glTexCoord2f(0.0f, 0.0f); glVertex3f(xMax, yMin, zMin);
        glEnd();
        glDisable(GL_TEXTURE_2D);
    } else {
        // Fallback: depan dan belakang juga pakai warna solid
        gambarBalok(xMin, xMax, yMin, yMax, zMin, zMax, r, g, b);
        return;
    }
    // Sisi SAMPING: warna solid (kiri, kanan, atas, bawah)
    glColor3f(r, g, b);
    // Kiri
    glBegin(GL_QUADS);
    glNormal3f(-1.0f, 0.0f, 0.0f);
    glVertex3f(xMin, yMin, zMin); glVertex3f(xMin, yMin, zMax);
    glVertex3f(xMin, yMax, zMax); glVertex3f(xMin, yMax, zMin);
    glEnd();
    // Kanan
    glBegin(GL_QUADS);
    glNormal3f(1.0f, 0.0f, 0.0f);
    glVertex3f(xMax, yMin, zMin); glVertex3f(xMax, yMax, zMin);
    glVertex3f(xMax, yMax, zMax); glVertex3f(xMax, yMin, zMax);
    glEnd();
    // Atas
    glBegin(GL_QUADS);
    glNormal3f(0.0f, 1.0f, 0.0f);
    glVertex3f(xMin, yMax, zMin); glVertex3f(xMin, yMax, zMax);
    glVertex3f(xMax, yMax, zMax); glVertex3f(xMax, yMax, zMin);
    glEnd();
    // Bawah
    glBegin(GL_QUADS);
    glNormal3f(0.0f, -1.0f, 0.0f);
    glVertex3f(xMin, yMin, zMin); glVertex3f(xMax, yMin, zMin);
    glVertex3f(xMax, yMin, zMax); glVertex3f(xMin, yMin, zMax);
    glEnd();
}


// =========================================================================
// HELPER: GAMBAR VITRIN KACA TRANSPARAN
// =========================================================================
static void gambarVitrinKaca(float xMin, float xMax, float yMin, float yMax, float zMin, float zMax) {
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // Panel Depan
    glBegin(GL_QUADS);
    glNormal3f(0.0f, 0.0f, 1.0f);
    glColor4f(0.75f, 0.88f, 0.95f, 0.3f);
    glVertex3f(xMin, yMin, zMax); glVertex3f(xMax, yMin, zMax);
    glVertex3f(xMax, yMax, zMax); glVertex3f(xMin, yMax, zMax);
    glEnd();

    // Panel Belakang
    glBegin(GL_QUADS);
    glNormal3f(0.0f, 0.0f, -1.0f);
    glColor4f(0.75f, 0.88f, 0.95f, 0.3f);
    glVertex3f(xMin, yMin, zMin); glVertex3f(xMin, yMax, zMin);
    glVertex3f(xMax, yMax, zMin); glVertex3f(xMax, yMin, zMin);
    glEnd();

    // Panel Kiri
    glBegin(GL_QUADS);
    glNormal3f(-1.0f, 0.0f, 0.0f);
    glColor4f(0.75f, 0.88f, 0.95f, 0.25f);
    glVertex3f(xMin, yMin, zMin); glVertex3f(xMin, yMin, zMax);
    glVertex3f(xMin, yMax, zMax); glVertex3f(xMin, yMax, zMin);
    glEnd();

    // Panel Kanan
    glBegin(GL_QUADS);
    glNormal3f(1.0f, 0.0f, 0.0f);
    glColor4f(0.75f, 0.88f, 0.95f, 0.25f);
    glVertex3f(xMax, yMin, zMin); glVertex3f(xMax, yMax, zMin);
    glVertex3f(xMax, yMax, zMax); glVertex3f(xMax, yMin, zMax);
    glEnd();

    glDisable(GL_BLEND);
}

// =========================================================================
// HELPER: GAMBAR RAK SEGITIGA A-FRAME (ref 3)
// =========================================================================
static void gambarRakSegitiga(float cx, float yBase, float cz) {
    float rKayu = 0.25f, gKayu = 0.13f, bKayu = 0.08f;
    gambarBalok(cx - 0.6f, cx - 0.55f, yBase, yBase + 1.6f, cz - 0.25f, cz - 0.2f, rKayu, gKayu, bKayu);
    gambarBalok(cx + 0.55f, cx + 0.6f, yBase, yBase + 1.6f, cz - 0.25f, cz - 0.2f, rKayu, gKayu, bKayu);
    gambarBalok(cx - 0.6f, cx - 0.55f, yBase, yBase + 1.6f, cz + 0.2f, cz + 0.25f, rKayu, gKayu, bKayu);
    gambarBalok(cx + 0.55f, cx + 0.6f, yBase, yBase + 1.6f, cz + 0.2f, cz + 0.25f, rKayu, gKayu, bKayu);

    float rRak = 0.9f, gRak = 0.9f, bRak = 0.9f;
    gambarBalok(cx - 0.55f, cx + 0.55f, yBase + 0.1f, yBase + 0.14f, cz - 0.25f, cz + 0.25f, rRak, gRak, bRak);
    gambarBalok(cx - 0.2f, cx + 0.1f, yBase + 0.14f, yBase + 0.3f, cz - 0.1f, cz + 0.1f, 0.55f, 0.5f, 0.45f);

    gambarBalok(cx - 0.45f, cx + 0.45f, yBase + 0.45f, yBase + 0.49f, cz - 0.22f, cz + 0.22f, rRak, gRak, bRak);
    gambarBalok(cx - 0.15f, cx + 0.15f, yBase + 0.49f, yBase + 0.62f, cz - 0.08f, cz + 0.08f, 0.5f, 0.47f, 0.42f);

    gambarBalok(cx - 0.35f, cx + 0.35f, yBase + 0.8f, yBase + 0.84f, cz - 0.2f, cz + 0.2f, rRak, gRak, bRak);
    gambarBalok(cx - 0.1f, cx + 0.1f, yBase + 0.84f, yBase + 0.96f, cz - 0.06f, cz + 0.06f, 0.52f, 0.48f, 0.43f);

    gambarBalok(cx - 0.25f, cx + 0.25f, yBase + 1.15f, yBase + 1.19f, cz - 0.18f, cz + 0.18f, rRak, gRak, bRak);
    gambarBalok(cx - 0.06f, cx + 0.06f, yBase + 1.19f, yBase + 1.28f, cz - 0.04f, cz + 0.04f, 0.48f, 0.45f, 0.4f);
}

// =========================================================================
// HELPER: ARCA DUA SISI (ref 10) - LEBIH DETAIL
// =========================================================================
static void gambarArcaDuaSisi(float cx, float yBase, float cz, float scale) {
    // Balok 3D tebal dengan tekstur arca di depan & belakang, sisi samping warna batu
    gambarBalokTekstur(cx - 0.3f*scale, cx + 0.3f*scale,
                       yBase, yBase + 1.3f*scale,
                       cz - 0.15f*scale, cz + 0.15f*scale,
                       arcaDuaSisiTex, 0.5f, 0.48f, 0.42f);
}

// =========================================================================
// HELPER: ARCA GANESHA (ref 11) - LEBIH DETAIL
// =========================================================================
static void gambarArcaGanesha(float cx, float yBase, float cz, float scale) {
    // Balok 3D tebal dengan tekstur Ganesha di depan & belakang, sisi samping warna batu gelap
    gambarBalokTekstur(cx - 0.35f*scale, cx + 0.35f*scale,
                       yBase, yBase + 1.2f*scale,
                       cz - 0.2f*scale, cz + 0.2f*scale,
                       arcaGaneshaTex, 0.18f, 0.18f, 0.18f);
}

// =========================================================================
// HELPER: ARTEFAK BATU (Candi mini / stupa)
// =========================================================================
static void gambarBatuCandi(float cx, float yBase, float cz, float scale) {
    float r = 0.5f, g = 0.48f, b = 0.45f;
    gambarBalok(cx - 0.2f*scale, cx + 0.2f*scale, yBase, yBase + 0.15f*scale, cz - 0.2f*scale, cz + 0.2f*scale, r, g, b);
    gambarBalok(cx - 0.15f*scale, cx + 0.15f*scale, yBase + 0.15f*scale, yBase + 0.3f*scale, cz - 0.15f*scale, cz + 0.15f*scale, r-0.05f, g-0.05f, b-0.05f);
    gambarBalok(cx - 0.1f*scale, cx + 0.1f*scale, yBase + 0.3f*scale, yBase + 0.5f*scale, cz - 0.1f*scale, cz + 0.1f*scale, r, g, b);
    gambarBalok(cx - 0.05f*scale, cx + 0.05f*scale, yBase + 0.5f*scale, yBase + 0.6f*scale, cz - 0.05f*scale, cz + 0.05f*scale, r-0.02f, g-0.02f, b-0.02f);
}

// =========================================================================
// FUNGSI INTERIOR MUSEUM
// =========================================================================
static void gambarInteriorMuseum() {
    // Koordinat interior museum: X: -4.5 sampai 4.5, Y: 0.0 sampai 2.5, Z: -6.5 sampai -2.5

    // A. DINDING INTERIOR
    float rKrem = 0.88f, gKrem = 0.8f, bKrem = 0.55f;
    gambarBalok(-4.45f, 4.45f, 0.05f, 2.45f, -6.45f, -6.42f, rKrem, gKrem, bKrem); // Belakang
    gambarBalok(-4.48f, -4.45f, 0.05f, 2.45f, -6.45f, -2.55f, rKrem, gKrem, bKrem); // Kiri
    gambarBalok(4.45f, 4.48f, 0.05f, 2.45f, -6.45f, -2.55f, rKrem, gKrem, bKrem); // Kanan

    // B. MEJA DISPLAY
    // Belakang
    gambarBalok(-4.0f, 4.0f, 0.05f, 0.55f, -6.38f, -5.5f, 0.12f, 0.12f, 0.12f);
    gambarBalok(-4.1f, 4.1f, 0.55f, 0.62f, -6.4f, -5.4f, 0.93f, 0.91f, 0.88f);
    // Kiri (Dimundurkan Z-nya agar tidak tumpang tindih dengan meja belakang)
    gambarBalok(-4.38f, -3.5f, 0.05f, 0.55f, -5.3f, -3.0f, 0.12f, 0.12f, 0.12f);
    gambarBalok(-4.4f, -3.4f, 0.55f, 0.62f, -5.35f, -2.9f, 0.93f, 0.91f, 0.88f);
    // Kanan (Dimundurkan Z-nya agar tidak tumpang tindih dengan meja belakang)
    gambarBalok(3.5f, 4.38f, 0.05f, 0.55f, -5.3f, -3.0f, 0.12f, 0.12f, 0.12f);
    gambarBalok(3.4f, 4.4f, 0.55f, 0.62f, -5.35f, -2.9f, 0.93f, 0.91f, 0.88f);

    // C. ARTEFAK BATU DI ATAS MEJA BELAKANG (Detail Diperbaiki)
    gambarBatuCandi(-3.3f, 0.62f, -5.9f, 0.8f);
    gambarBatuCandi(-2.4f, 0.62f, -5.8f, 0.6f);
    
    // Artefak besar bermotif
    gambarBatuCandi(-1.5f, 0.62f, -5.9f, 1.2f);
    gambarBatuCandi(-0.3f, 0.62f, -5.8f, 0.7f);
    gambarBatuCandi(0.8f, 0.62f, -5.9f, 1.0f);
    gambarBatuCandi(1.8f, 0.62f, -5.8f, 0.8f);
    gambarBatuCandi(2.8f, 0.62f, -5.9f, 1.1f);
    gambarBatuCandi(3.6f, 0.62f, -5.8f, 0.7f);

    // D. VITRIN KACA
    gambarVitrinKaca(-0.8f, 0.2f, 0.62f, 1.9f, -6.2f, -5.6f);
    gambarBatuCandi(-0.3f, 0.62f, -5.9f, 0.5f); // dalam vitrin 1
    
    gambarVitrinKaca(2.3f, 3.3f, 0.62f, 1.9f, -6.2f, -5.6f);
    gambarBatuCandi(2.8f, 0.62f, -5.9f, 0.6f); // dalam vitrin 2

    // E. ARTEFAK MEJA SAMPING KIRI
    gambarBatuCandi(-4.0f, 0.62f, -5.3f, 0.8f);
    gambarBatuCandi(-4.0f, 0.62f, -4.4f, 0.6f);
    gambarBatuCandi(-4.0f, 0.62f, -3.6f, 0.7f);

    // F. ARTEFAK MEJA SAMPING KANAN
    gambarBatuCandi(4.0f, 0.62f, -5.3f, 0.7f);
    gambarBatuCandi(4.0f, 0.62f, -4.3f, 0.6f);
    gambarBatuCandi(4.0f, 0.62f, -3.5f, 0.9f);

    // G. POSTER / BANNER DENGAN TEKSTUR BARU
    // 1. Poster Prasasti Plumpungan
    gambarBalok(-3.8f, -2.2f, 1.0f, 2.3f, -6.40f, -6.38f, 0.1f, 0.1f, 0.1f); // Frame
    gambarPosterTekstur(-3.75f, -2.25f, 1.05f, 2.25f, -6.39f, -6.37f, posterPrasastiTex, 2);

    // 2. Poster Legenda Salatiga
    gambarBalok(-1.8f, -0.2f, 1.0f, 2.3f, -6.40f, -6.38f, 0.1f, 0.1f, 0.1f); // Frame
    gambarPosterTekstur(-1.75f, -0.25f, 1.05f, 2.25f, -6.39f, -6.37f, posterLegendaTex, 2);

    // 3. Poster Pembacaan Proklamasi (Dinding kanan, hadap kiri)
    gambarBalok(4.43f, 4.45f, 1.0f, 2.3f, -5.5f, -4.0f, 0.1f, 0.1f, 0.1f); // Frame
    gambarPosterTekstur(4.42f, 4.44f, 1.05f, 2.25f, -5.45f, -4.05f, posterProklamasiTex, 0);

    // (Rak segitiga dihapus agar tidak tumpang tindih)

    // I. ARCA DUDUK DI VITRIN KIRI
    gambarBalok(-4.3f, -3.6f, 0.05f, 0.6f, -3.6f, -3.0f, 0.1f, 0.1f, 0.1f); // pedestal
    gambarBatuCandi(-3.95f, 0.6f, -3.3f, 1.0f); // arca
    gambarVitrinKaca(-4.25f, -3.65f, 0.6f, 1.6f, -3.55f, -3.05f); // kaca

    // J. TENGAH RUANGAN (ref 9, 10, 11)
    
    // --- J1. Vitrin Kaca Berdiri Tinggi (ref 9) ---
    // Dipindah ke X = -2.5 agar tidak menutupi poster Legenda Salatiga
    gambarBalok(-2.9f, -2.1f, 0.05f, 0.12f, -5.2f, -4.6f, 0.08f, 0.08f, 0.08f);
    gambarBalok(-2.9f, -2.1f, 1.7f, 1.77f, -5.2f, -4.6f, 0.08f, 0.08f, 0.08f);
    gambarVitrinKaca(-2.88f, -2.12f, 0.12f, 1.7f, -5.18f, -4.62f);
    // Rak kaca di dalam
    glEnable(GL_BLEND);
    glColor4f(0.8f, 0.9f, 0.95f, 0.35f);
    glBegin(GL_QUADS);
    glVertex3f(-2.85f, 0.5f, -5.15f); glVertex3f(-2.15f, 0.5f, -5.15f); glVertex3f(-2.15f, 0.5f, -4.65f); glVertex3f(-2.85f, 0.5f, -4.65f);
    glVertex3f(-2.85f, 0.95f, -5.15f); glVertex3f(-2.15f, 0.95f, -5.15f); glVertex3f(-2.15f, 0.95f, -4.65f); glVertex3f(-2.85f, 0.95f, -4.65f);
    glVertex3f(-2.85f, 1.35f, -5.15f); glVertex3f(-2.15f, 1.35f, -5.15f); glVertex3f(-2.15f, 1.35f, -4.65f); glVertex3f(-2.85f, 1.35f, -4.65f);
    glEnd();
    glDisable(GL_BLEND);
    // Isi vitrin dengan artefak prasasti (balok 3D bertekstur yang tebal agar terlihat)
    gambarBalokTekstur(-2.7f, -2.3f, 0.15f, 1.55f, -5.05f, -4.75f, posterPrasastiTex, 0.5f, 0.45f, 0.4f);

    // --- J2. Arca Dua Sisi (ref 10) ---
    gambarBalok(0.3f, 1.3f, 0.05f, 0.08f, -4.8f, -4.0f, 0.85f, 0.88f, 0.9f); // alas kaca
    gambarBalok(0.55f, 1.05f, 0.08f, 0.35f, -4.6f, -4.2f, 0.08f, 0.08f, 0.08f); // pedestal
    gambarArcaDuaSisi(0.8f, 0.35f, -4.4f, 1.0f);
    gambarBalok(0.55f, 1.05f, 0.08f, 0.3f, -4.0f, -3.95f, 0.9f, 0.9f, 0.88f); // label

    // --- J3. Arca Ganesha Hitam (ref 11) ---
    gambarBalok(2.0f, 3.0f, 0.05f, 0.45f, -5.0f, -4.2f, 0.08f, 0.08f, 0.08f); // pedestal
    gambarArcaGanesha(2.5f, 0.45f, -4.6f, 1.0f);

    // K. POJOK RUANGAN (ref 13, 14)
    
    // --- K1. Pojok Kiri Belakang: Yoni (ref 13) ---
    gambarBalok(-4.3f, -3.2f, 0.05f, 0.45f, -6.3f, -5.5f, 0.12f, 0.12f, 0.12f); // meja base
    gambarBalok(-4.35f, -3.15f, 0.45f, 0.52f, -6.35f, -5.45f, 0.93f, 0.91f, 0.88f); // meja top
    
    // Detail Yoni Stone
    float yoniX = -3.75f, yoniY = 0.52f, yoniZ = -5.9f;
    gambarBalok(yoniX-0.3f, yoniX+0.3f, yoniY, yoniY+0.2f, yoniZ-0.3f, yoniZ+0.3f, 0.6f, 0.58f, 0.55f); // alas
    gambarBalok(yoniX-0.25f, yoniX+0.25f, yoniY+0.2f, yoniY+0.4f, yoniZ-0.25f, yoniZ+0.25f, 0.58f, 0.56f, 0.53f); // badan
    // Spout (cerat) Yoni menonjol ke depan
    gambarBalok(yoniX-0.1f, yoniX+0.1f, yoniY+0.2f, yoniY+0.35f, yoniZ+0.25f, yoniZ+0.45f, 0.58f, 0.56f, 0.53f);
    // Lingga (silinder tengah direpresentasikan kotak kecil tinggi)
    gambarBalok(yoniX-0.1f, yoniX+0.1f, yoniY+0.4f, yoniY+0.65f, yoniZ-0.1f, yoniZ+0.1f, 0.5f, 0.48f, 0.45f);

    // Foto-foto di dinding pojok kiri
    gambarBalok(-4.47f, -4.46f, 1.3f, 2.1f, -6.3f, -5.7f, 0.9f, 0.88f, 0.8f);
    gambarBalok(-4.47f, -4.46f, 1.0f, 1.7f, -5.55f, -5.1f, 0.2f, 0.2f, 0.2f);
    gambarBalok(-3.8f, -3.2f, 1.4f, 2.0f, -6.43f, -6.42f, 0.15f, 0.15f, 0.15f);

    // --- K2. Kiosk Multimedia: MEPET DINDING KANAN (X=4.45), dekat pintu ---
    gambarBalok(4.15f, 4.45f, 0.05f, 2.0f, -3.2f, -2.7f, 0.05f, 0.2f, 0.5f); // Kiosk body
    gambarBalok(4.17f, 4.43f, 1.1f, 1.75f, -2.69f, -2.68f, 0.8f, 0.82f, 0.85f); // Layar
    gambarBalok(4.20f, 4.40f, 0.85f, 1.0f, -2.69f, -2.68f, 0.85f, 0.75f, 0.2f); // Keyboard pad
    gambarBalok(4.25f, 4.35f, 0.3f, 0.6f, -2.69f, -2.68f, 0.2f, 0.6f, 0.9f); // Speaker/detail

    // L. PLAFON / LANGIT-LANGIT PUTIH
    gambarBalok(-4.5f, 4.5f, 2.45f, 2.5f, -6.5f, -2.5f, 0.95f, 0.95f, 0.95f);
}

// =========================================================================
// FUNGSI UTAMA GAMBAR GEDUNG MUSEUM (EXTERIOR + INTERIOR)
// =========================================================================
void gambarGedungMuseum() {
    glPushMatrix();
    glScalef(2.5f, 3.5f, 3.8f);

    float rOranye = 0.95f, gOranye = 0.32f, bOranye = 0.08f;
    float rAtap = 0.65f, gAtap = 0.32f, bAtap = 0.22f;
    float rPutih = 0.92f, gPutih = 0.92f, bPutih = 0.92f;

    // Lantai
    gambarBalok(-4.5f, 4.5f, 0.0f, 0.05f, -6.5f, -2.5f, 0.95f, 0.95f, 0.95f);

    // Garis Ubin
    glLineWidth(2.0f);
    glColor3f(0.3f, 0.3f, 0.3f);
    glBegin(GL_LINES);
    for (float i = -4.5f; i <= 4.5f; i += 0.5f) {
        glVertex3f(i, 0.051f, -6.5f); glVertex3f(i, 0.051f, -2.5f);
    }
    for (float j = -6.5f; j <= -2.5f; j += 0.5f) {
        glVertex3f(-4.5f, 0.051f, j); glVertex3f( 4.5f, 0.051f, j);
    }
    glEnd();

    // Dinding Luar
    gambarBalok(-4.5f, 4.5f, -0.5f, 2.5f, -6.5f, -6.4f, rOranye, gOranye, bOranye);
    gambarBalok(-4.55f, -4.5f, -0.5f, 2.5f, -6.5f, -2.5f, rOranye, gOranye, bOranye);
    gambarBalok(4.5f, 4.55f, -0.5f, 2.5f, -6.5f, -2.5f, rOranye, gOranye, bOranye);
    gambarBalok(-4.5f, -1.5f, -0.5f, 2.5f, -2.5f, -2.4f, rOranye, gOranye, bOranye);
    gambarBalok(1.5f, 4.5f, -0.5f, 2.5f, -2.5f, -2.4f, rOranye, gOranye, bOranye);

    // Pilar Depan
    gambarBalok(-1.5f, -0.7f, -0.5f, 1.7f, -2.5f, -2.4f, rOranye, gOranye, bOranye);
    gambarBalok( 0.7f,  1.5f, -0.5f, 1.7f, -2.5f, -2.4f, rOranye, gOranye, bOranye);
    gambarBalok(-1.5f,  1.5f,  1.7f, 2.5f, -2.5f, -2.4f, rOranye, gOranye, bOranye);
    gambarBalok(-1.5f, -0.7f, -0.5f, 1.7f, -2.53f, -2.51f, rPutih, gPutih, bPutih);
    gambarBalok( 0.7f,  1.5f, -0.5f, 1.7f, -2.53f, -2.51f, rPutih, gPutih, bPutih);
    gambarBalok(-1.5f,  1.5f,  1.7f, 2.0f, -2.53f, -2.51f, rPutih, gPutih, bPutih);
    gambarBalok(-1.6f, 1.6f, -0.5f, -0.45f, -2.5f, -1.2f, 0.85f, 0.85f, 0.85f);
    gambarBalok(-1.5f, -1.3f, -0.45f, 2.5f, -1.3f, -1.1f, rPutih, gPutih, bPutih);
    gambarBalok( 1.3f,  1.5f, -0.45f, 2.5f, -1.3f, -1.1f, rPutih, gPutih, bPutih);

    // Papan Nama Museum
    if (museumSignTex != 0) {
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, museumSignTex);
        glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
        glBegin(GL_QUADS);
        glNormal3f(0.0f, 0.0f, 1.0f);
        glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.1f, 1.9f, -1.22f);
        glTexCoord2f(1.0f, 0.0f); glVertex3f( 1.1f, 1.9f, -1.22f);
        glTexCoord2f(1.0f, 1.0f); glVertex3f( 1.1f, 2.5f, -1.22f);
        glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.1f, 2.5f, -1.22f);
        glEnd();
        glDisable(GL_TEXTURE_2D);
    } else {
        gambarBalok(-1.1f, 1.1f, 1.9f, 2.5f, -1.25f, -1.23f, 0.05f, 0.25f, 0.6f);
    }

    // Jendela
    gambarBalok(-3.5f, -2.5f,  0.3f, 1.6f, -2.39f, -2.37f, rPutih, gPutih, bPutih);
    gambarBalok(-3.4f, -2.6f,  0.4f, 1.5f, -2.36f, -2.35f, 0.2f, 0.3f, 0.3f);
    gambarBalok( 2.5f,  3.5f,  0.3f, 1.6f, -2.39f, -2.37f, rPutih, gPutih, bPutih);
    gambarBalok( 2.6f,  3.4f,  0.4f, 1.5f, -2.36f, -2.35f, 0.2f, 0.3f, 0.3f);

    // Pintu Kaca
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glBegin(GL_QUADS);
    glNormal3f(-0.3f, 0.0f, 0.95f); glColor4f(0.7f, 0.85f, 0.9f, 0.4f);
    glVertex3f(-0.7f, -0.5f, -2.5f); glVertex3f(-1.1f, -0.5f, -2.1f);
    glVertex3f(-1.1f,  1.7f, -2.1f); glVertex3f(-0.7f,  1.7f, -2.5f);
    glEnd();
    glBegin(GL_QUADS);
    glNormal3f(0.3f, 0.0f, 0.95f); glColor4f(0.7f, 0.85f, 0.9f, 0.4f);
    glVertex3f(0.7f, -0.5f, -2.5f); glVertex3f(1.1f, -0.5f, -2.1f);
    glVertex3f(1.1f,  1.7f, -2.1f); glVertex3f(0.7f,  1.7f, -2.5f);
    glEnd();
    glDisable(GL_BLEND);

    // Atap
    glBegin(GL_TRIANGLES);
    glNormal3f(0.0f, 0.0f, 1.0f); glColor3f(rAtap, gAtap, bAtap);
    glVertex3f(-1.8f, 2.4f, -1.1f); glVertex3f(1.8f, 2.4f, -1.1f); glVertex3f(0.0f, 3.4f, -1.1f);
    glEnd();
    glBegin(GL_QUADS);
    glNormal3f(-0.6f, 0.8f, 0.0f);
    glVertex3f(-1.8f, 2.4f, -1.1f); glVertex3f(0.0f, 3.4f, -1.1f);
    glVertex3f(0.0f, 3.4f, -2.5f);  glVertex3f(-1.8f, 2.4f, -2.5f);
    glNormal3f(0.6f, 0.8f, 0.0f);
    glVertex3f(0.0f, 3.4f, -1.1f);  glVertex3f(1.8f, 2.4f, -1.1f);
    glVertex3f(1.8f, 2.4f, -2.5f);  glVertex3f(0.0f, 3.4f, -2.5f);
    glEnd();
    glBegin(GL_QUADS);
    glNormal3f(0.0f, 0.6f, 0.8f); glColor3f(rAtap - 0.05f, gAtap - 0.05f, bAtap - 0.05f);
    glVertex3f(-4.8f, 2.5f, -2.3f); glVertex3f(4.8f, 2.5f, -2.3f);
    glVertex3f(4.8f,  3.7f, -4.4f); glVertex3f(-4.8f, 3.7f, -4.4f);
    glNormal3f(0.0f, 0.6f, -0.8f);
    glVertex3f(-4.8f, 3.7f, -4.4f); glVertex3f(4.8f, 3.7f, -4.4f);
    glVertex3f(4.8f,  2.5f, -6.5f); glVertex3f(-4.8f, 2.5f, -6.5f);
    glEnd();
    glBegin(GL_TRIANGLES);
    glNormal3f(-1.0f, 0.0f, 0.0f);
    glVertex3f(-4.8f, 2.5f, -2.3f); glVertex3f(-4.8f, 3.7f, -4.4f); glVertex3f(-4.8f, 2.5f, -6.5f);
    glNormal3f(1.0f, 0.0f, 0.0f);
    glVertex3f(4.8f, 2.5f, -2.3f);  glVertex3f(4.8f, 2.5f, -6.5f);  glVertex3f(4.8f, 3.7f, -4.4f);
    glEnd();

    // Interior
    gambarInteriorMuseum();

    glPopMatrix();
}
