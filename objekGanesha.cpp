#include "objekGanesha.h"

// Deklarasi untuk STB Image
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include <iostream>

// Fix error GL_CLAMP_TO_EDGE untuk MinGW Windows
#ifndef GL_CLAMP_TO_EDGE
#define GL_CLAMP_TO_EDGE 0x812F
#endif

// Variabel global untuk menyimpan ID tekstur
static GLuint ganeshaTex = 0;
static bool isTextureLoaded = false;

// Fungsi untuk memuat tekstur
void loadGaneshaTexture() {
    if (isTextureLoaded) return; // Mencegah load berulang-ulang tiap frame

    int width, height, nrChannels;
    // Balik gambar secara vertikal agar tidak terbalik (upside down) di OpenGL
    stbi_set_flip_vertically_on_load(true); 
    
    // Pastikan load dengan format 4 channel (RGBA) untuk mendukung transparansi PNG
    unsigned char *data = stbi_load("ganesha.png", &width, &height, &nrChannels, 4);

    if(data) {
        glGenTextures(1, &ganeshaTex);
        glBindTexture(GL_TEXTURE_2D, ganeshaTex);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        stbi_image_free(data);
        isTextureLoaded = true;
    } else {
        std::cout << "Gagal memuat file gambar ganesha.png! Pastikan file ada di folder yang sama dengan main.exe" << std::endl;
    }
}

// Fungsi menggambar balok (tetap dipertahankan untuk menggambar tatakan/meja)
void drawGaneshaBlock(float sx, float sy, float sz) {
    glBegin(GL_QUADS);
        // Depan
        glNormal3f(0.0f, 0.0f, 1.0f);
        glVertex3f(-sx/2, -sy/2,  sz/2); glVertex3f( sx/2, -sy/2,  sz/2);
        glVertex3f( sx/2,  sy/2,  sz/2); glVertex3f(-sx/2,  sy/2,  sz/2);
        // Belakang
        glNormal3f(0.0f, 0.0f, -1.0f);
        glVertex3f(-sx/2, -sy/2, -sz/2); glVertex3f(-sx/2,  sy/2, -sz/2);
        glVertex3f( sx/2,  sy/2, -sz/2); glVertex3f( sx/2, -sy/2, -sz/2);
        // Atas
        glNormal3f(0.0f, 1.0f, 0.0f);
        glVertex3f(-sx/2,  sy/2, -sz/2); glVertex3f(-sx/2,  sy/2,  sz/2);
        glVertex3f( sx/2,  sy/2,  sz/2); glVertex3f( sx/2,  sy/2, -sz/2);
        // Bawah
        glNormal3f(0.0f, -1.0f, 0.0f);
        glVertex3f(-sx/2, -sy/2, -sz/2); glVertex3f( sx/2, -sy/2, -sz/2);
        glVertex3f( sx/2, -sy/2,  sz/2); glVertex3f(-sx/2, -sy/2,  sz/2);
        // Kanan
        glNormal3f(1.0f, 0.0f, 0.0f);
        glVertex3f( sx/2, -sy/2, -sz/2); glVertex3f( sx/2,  sy/2, -sz/2);
        glVertex3f( sx/2,  sy/2,  sz/2); glVertex3f( sx/2, -sy/2,  sz/2);
        // Kiri
        glNormal3f(-1.0f, 0.0f, 0.0f);
        glVertex3f(-sx/2, -sy/2, -sz/2); glVertex3f(-sx/2, -sy/2,  sz/2);
        glVertex3f(-sx/2,  sy/2,  sz/2); glVertex3f(-sx/2,  sy/2, -sz/2);
    glEnd();
}

void drawObjectGanesha() {
    // Pastikan tekstur sudah diload sebelum digambar
    if (!isTextureLoaded) {
        loadGaneshaTexture();
    }

    glEnable(GL_DEPTH_TEST);
    glPushMatrix();

    // ==========================================
    // 1. BAGIAN TATAKAN (Tanpa Tekstur Gambar)
    // ==========================================
    glDisable(GL_TEXTURE_2D); // Matikan tekstur sebentar untuk gambar balok polos

    // Balok Putih (alas dasar paling bawah)
    glColor3f(1.0f, 1.0f, 1.0f);
    glPushMatrix();
        glTranslatef(0.0f, -1.6f, 0.0f);
        drawGaneshaBlock(6.0f, 0.6f, 6.0f);
    glPopMatrix();

    // Tatakan Abu-abu (tempat Ganesha duduk)
    glColor3f(0.3f, 0.3f, 0.3f);
    glPushMatrix();
        glTranslatef(0.0f, -1.0f, 0.0f);
        drawGaneshaBlock(5.0f, 0.6f, 5.0f);
        glTranslatef(0.0f, 0.4f, 0.0f);
        drawGaneshaBlock(4.0f, 0.4f, 4.0f);
    glPopMatrix();

    glColor3f(0.7f, 0.7f, 0.7f); 
    
    // Tentukan ukuran balok peninggi baru di sini
    float balokLebarX = 2.2f; 
    float balokTinggiY = 2.1f; // Ketinggian balok peninggi (Ubah ini jika ingin lebih tinggi/rendah)
    float balokTebalZ  = 2.2f; 

    glPushMatrix();
        // Posisi Y dihitung agar menapak pas di atas permukaan tatakan terakhir
        // Tatakan terakhir berada di Y = -1.0f + 0.4f = -0.6f dengan tinggi permukaan atas di -0.4f
        // Karena drawGaneshaBlock sifatnya centered (dibagi 2), kita geser ke tengah-tengah tinggi balok baru
        glTranslatef(0.0f, -0.4f + (balokTinggiY / 2.0f), 0.0f);
        drawGaneshaBlock(balokLebarX, balokTinggiY, balokTebalZ);
    glPopMatrix();

    // ==========================================
    // BAGIAN ARCA: OPSI 2 (Y-AXIS BILLBOARDING)
    // ==========================================
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, ganeshaTex);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glColor4f(1.0f, 1.0f, 1.0f, 1.0f);

    float w = 2.0f; 
    float h = 5.2f; 

    glPushMatrix();
        // 1. Geser posisi ke atas meja tatakan dulu
        glTranslatef(0.0f, -0.4f + balokTinggiY, 0.0f);

        // 2. TRICK BILLBOARD: Ambil matriks kamera saat ini dan reset rotasinya
        float modelview[16];
        glGetFloatv(GL_MODELVIEW_MATRIX, modelview);
        
        // Reset rotasi sumbu X, Y, Z objek agar selalu sejajar lurus dengan mata kamera
        modelview[0] = 1.0f; modelview[1] = 0.0f; modelview[2] = 0.0f;
        modelview[4] = 0.0f; modelview[5] = 1.0f; modelview[6] = 0.0f;
        modelview[8] = 0.0f; modelview[9] = 0.0f; modelview[10] = 1.0f;
        
        glLoadMatrixf(modelview); // Terapkan matriks yang sudah di-reset rotasinya

        float offsetDuduk = -0.3f;

        // 3. Gambar cukup 1 sisi datar (dia akan berputar otomatis mengikuti kamera)
        glBegin(GL_QUADS);
            glNormal3f(0.0f, 0.0f, 1.0f);
            glTexCoord2f(0.0f, 0.0f); glVertex3f(-w, 0.0f, 0.0f);
            glTexCoord2f(1.0f, 0.0f); glVertex3f( w, 0.0f, 0.0f);
            glTexCoord2f(1.0f, 1.0f); glVertex3f( w, h,    0.0f);
            glTexCoord2f(0.0f, 1.0f); glVertex3f(-w, h,    0.0f);
        glEnd();
    glPopMatrix();

    // Matikan blending dan tekstur agar objek selanjutnya tidak ikut transparan
    glDisable(GL_BLEND);
    glDisable(GL_TEXTURE_2D);

    glPopMatrix();
}