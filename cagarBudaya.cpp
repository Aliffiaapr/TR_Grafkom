#include "cagarBudaya.h"
#include "balok.h"
#include <GLFW/glfw3.h>
#include "stb_image.h"
#include <iostream>
#include <cmath>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif



// Variable placeholder untuk tekstur ganesha/batu nanti
static GLuint texBatuYoni = 0;
static GLuint texBatuRatna = 0;
static GLuint texBatuHitam = 0;

// =========================================================================
// CODE UNTUK BILLBOARD (Agar gambar PNG selalu berputar menghadap kamera)
// =========================================================================
void terapkanBillboardY() {
    float modelview[16];
    glGetFloatv(GL_MODELVIEW_MATRIX, modelview);

    // Ambil posisi X, Y, Z objek saat ini dari matriks modelview
    float posX = modelview[12];
    float posY = modelview[13];
    float posZ = modelview[14];

    // Reset bagian rotasi matriks menjadi matriks identitas (0 derajat)
    // Ini yang membuat bidang 2D selalu tegak dan menghadap kamera secara dinamis
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (i == j) modelview[i * 4 + j] = 1.0f;
            else modelview[i * 4 + j] = 0.0f;
        }
    }

    // Kembalikan posisi koordinat aslinya agar objek tidak berpindah tempat
    modelview[12] = posX;
    modelview[13] = posY;
    modelview[14] = posZ;

    // Load kembali matriks yang sudah di-reset rotasinya ke OpenGL
    glLoadMatrixf(modelview);
}

GLuint loadTextureCB(const char* filename) {
    GLuint textureID;
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);
    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    
    int width, height, nrChannels;
    stbi_set_flip_vertically_on_load(true);
    unsigned char *data = stbi_load(filename, &width, &height, &nrChannels, 0);
    
    if (data) {
        GLenum format = (nrChannels == 4) ? GL_RGBA : GL_RGB;
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        std::cout << "Berhasil memuat tekstur cagar budaya: " << filename << std::endl;
    } else {
        std::cout << "GAGAL memuat tekstur cagar budaya: " << filename << std::endl;
    }
    stbi_image_free(data);
    return textureID;
}

// 2. Inisialisasi File PNG ke masing-masing ID Tekstur
void initCagarBudayaTextures() {
    // Silakan sesuaikan nama file PNG hasil potonganmu di bawah ini
    texBatuYoni = loadTextureCB("yoni_kecil.png"); 
    texBatuRatna  = loadTextureCB("batu_ratna.png");
    texBatuHitam  = loadTextureCB("batu_hitam.png");
}

// FUNGSI UTILITAS: Menggambar Balok yang Otomatis Ditempeli Tekstur Gambar
void gambarBalokBertekstur(float x1, float x2, float y1, float y2, float z1, float z2) {
    glBegin(GL_QUADS);
        // Sisi Depan
        glTexCoord2f(0.0f, 0.0f); glVertex3f(x1, y1, z2);
        glTexCoord2f(1.0f, 0.0f); glVertex3f(x2, y1, z2);
        glTexCoord2f(1.0f, 1.0f); glVertex3f(x2, y2, z2);
        glTexCoord2f(0.0f, 1.0f); glVertex3f(x1, y2, z2);

        // Sisi Belakang
        glTexCoord2f(1.0f, 0.0f); glVertex3f(x1, y1, z1);
        glTexCoord2f(1.0f, 1.0f); glVertex3f(x1, y2, z1);
        glTexCoord2f(0.0f, 1.0f); glVertex3f(x2, y2, z1);
        glTexCoord2f(0.0f, 0.0f); glVertex3f(x2, y1, z1);

        // Sisi Atas
        glTexCoord2f(0.0f, 1.0f); glVertex3f(x1, y2, z1);
        glTexCoord2f(0.0f, 0.0f); glVertex3f(x1, y2, z2);
        glTexCoord2f(1.0f, 0.0f); glVertex3f(x2, y2, z2);
        glTexCoord2f(1.0f, 1.0f); glVertex3f(x2, y2, z1);

        // Sisi Bawah
        glTexCoord2f(1.0f, 1.0f); glVertex3f(x1, y1, z1);
        glTexCoord2f(0.0f, 1.0f); glVertex3f(x2, y1, z1);
        glTexCoord2f(0.0f, 0.0f); glVertex3f(x2, y1, z2);
        glTexCoord2f(1.0f, 0.0f); glVertex3f(x1, y1, z2);

        // Sisi Kanan
        glTexCoord2f(1.0f, 0.0f); glVertex3f(x2, y1, z1);
        glTexCoord2f(1.0f, 1.0f); glVertex3f(x2, y2, z1);
        glTexCoord2f(0.0f, 1.0f); glVertex3f(x2, y2, z2);
        glTexCoord2f(0.0f, 0.0f); glVertex3f(x2, y1, z2);

        // Sisi Kiri
        glTexCoord2f(0.0f, 0.0f); glVertex3f(x1, y1, z1);
        glTexCoord2f(1.0f, 0.0f); glVertex3f(x1, y1, z2);
        glTexCoord2f(1.0f, 1.0f); glVertex3f(x1, y2, z2);
        glTexCoord2f(0.0f, 1.0f); glVertex3f(x1, y2, z1);
    glEnd();
}

// =========================================================================
// OBJEK 1: YONI KECIL (Sebelah Gazebo)
// =========================================================================
void gambarYoniKecil() {
    glPushMatrix();
        glTranslatef(0.0f, 0.0f, 2.6f);
        
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, texBatuYoni);
        glColor4f(1.0f, 1.0f, 1.0f, 1.0f); // Agar warna asli gambar PNG keluar

       // Susunan Balok Pembentuk Struktur Yoni Kecil
        gambarBalokBertekstur(-0.5f, 0.5f, -0.5f, -0.2f, -0.5f, 0.5f);
        gambarBalokBertekstur(-0.4f, 0.4f, -0.2f, 0.2f, -0.4f, 0.4f);
        gambarBalokBertekstur(-0.5f, 0.5f, 0.2f, 0.5f, -0.5f, 0.5f);
        gambarBalokBertekstur(-0.15f, 0.15f, 0.15f, 0.45f, 0.5f, 0.8f);

        glDisable(GL_TEXTURE_2D);
    glPopMatrix();
}

// =========================================================================
// OBJEK 2: YONI BESAR (Dekat Pagar / Paling Kanan)
// =========================================================================
void gambarYoniBesar() {
    glPushMatrix();
        glTranslatef(0.0f, 0.0f, 2.6f);

        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, texBatuYoni);
        glColor4f(1.0f, 1.0f, 1.0f, 1.0f);

        // Strukturnya mirip Yoni Kecil, namun dimensinya atau skalanya bisa kamu bedakan langsung di fungsi ini
        gambarBalokBertekstur(-0.6f, 0.6f, -0.5f, -0.1f, -0.6f, 0.6f); // Lebih besar
        gambarBalokBertekstur(-0.45f, 0.45f, -0.1f, 0.4f, -0.45f, 0.45f);
        gambarBalokBertekstur(-0.6f, 0.6f, 0.4f, 0.7f, -0.6f, 0.6f);
        gambarBalokBertekstur(-0.18f, 0.18f, 0.3f, 0.65f, 0.6f, 0.95f); // Pancuran cerat besar

        glDisable(GL_TEXTURE_2D);
    glPopMatrix();
}

// =========================================================================
// OBJEK 3: BATU RATNA (Tatakan 3D Statis + Arca 2D Billboard Menghadap Kamera)
// =========================================================================
void gambarBatuRatna() {
    glPushMatrix();
        // 1. Atur koordinat posisi utama objek cagar budaya di peta
        glTranslatef(0.0f, -0.5f, 2.6f); 
        
        // -----------------------------------------------------------------
        // BAGIAN B: BADAN ARCA RATNA (2D Billboard - Selalu Ikut Kamera seperti Ganesha)
        // -----------------------------------------------------------------
        glPushMatrix();
            // Naikkan posisi arca setinggi 0.15f agar berdiri pas di atas tatakan balok tadi
            glTranslatef(0.0f, 0.1f, 0.0f);
            
            // Panggil fungsi billboard sumbu Y agar gambar selalu menghadap ke kamera
            terapkanBillboardY();

            glEnable(GL_TEXTURE_2D);
            glBindTexture(GL_TEXTURE_2D, texBatuRatna); // Memanggil file PNG transparan Batu Ratna
            
            // WAJIB AKTIF: Mengaktifkan Alpha Blending agar background kotak hitam hilang total
            glEnable(GL_BLEND);
            glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
            glEnable(GL_ALPHA_TEST);            // Mengabaikan pixel hitam/transparan agar tidak ditulis ke Depth Buffer
            glAlphaFunc(GL_GREATER, 0.1f);      //render pixel transparansi > 10%

            glColor4f(1.0f, 1.0f, 1.0f, 1.0f);

            // Menggambar plat bidang datar tempat menempelnya gambar PNG transparan
            // Ukuran bisa disesuaikan (Lebar: 0.7, Tinggi: 0.8)
            glBegin(GL_QUADS);
                glTexCoord2f(0.0f, 0.0f); glVertex3f(-2.2f, 0.00f, 0.0f); // Kiri bawah
                glTexCoord2f(1.0f, 0.0f); glVertex3f( 2.2f, 0.00f, 0.0f); // Kanan bawah
                glTexCoord2f(1.0f, 1.0f); glVertex3f( 2.2f, 2.60f, 0.0f); // Kanan atas
                glTexCoord2f(0.0f, 1.0f); glVertex3f(-2.2f, 2.60f, 0.0f); // Kiri atas
            glEnd();

            glDisable(GL_ALPHA_TEST);
            glDisable(GL_BLEND);
            glDisable(GL_TEXTURE_2D);
        glPopMatrix();

    glPopMatrix();
}

// =========================================================================
// OBJEK 4: BATU HITAM (Dekat Rumah Putih - Balok Berdiri Tinggi)
// =========================================================================
void gambarBatuHitam() {
    glPushMatrix();
        glTranslatef(0.0f, 0.0f, 2.6f);

        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, texBatuHitam);
        glColor4f(1.0f, 1.0f, 1.0f, 1.0f);

        // Membuat bentuk batu prasasti tegak vertikal (X langsing, Y tinggi, Z proporsional)
        gambarBalokBertekstur(-0.25f, 0.25f, -0.5f, 0.8f, -0.25f, 0.25f);

        glDisable(GL_TEXTURE_2D);
    glPopMatrix();
}