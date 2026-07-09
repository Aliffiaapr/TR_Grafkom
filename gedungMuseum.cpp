#include "gedungMuseum.h"
#include "balok.h"

void gambarGedungMuseum() {
    // ==========================================
    // GLOBAL SCALE
    // ==========================================
    glPushMatrix();
    glScalef(2.5f, 3.5f, 3.8f);

    // WARNA UTAMA
    float rOranye = 0.95f, gOranye = 0.32f, bOranye = 0.08f;
    float rAtap = 0.65f, gAtap = 0.32f, bAtap = 0.22f;
    float rPutih = 0.92f, gPutih = 0.92f, bPutih = 0.92f;

    // ==========================================
    // PERBAIKAN TOTAL: LANTAI DI ATAS TANAH & PATTERN DI ATAS LANTAI
    // ==========================================
    // 1. Alas Lantai Interior (Warna Putih, Berada dari Y = 0.0f sampai 0.05f di atas tanah)
    gambarBalok(-4.5f, 4.5f, 0.0f, 0.05f, -6.5f, -2.5f, 0.95f, 0.95f, 0.95f);

    // 2. Garis Corak Ubin Segi Empat Mendatar (Ditaruh di Y = 0.051f agar tidak tenggelam)
    glLineWidth(2.0f);
    glColor3f(0.3f, 0.3f, 0.3f);
    glBegin(GL_LINES);

    // Garis Vertikal Corak Ubin (Membujur sepanjang sumbu Z)
    for (float i = -4.5f; i <= 4.5f; i += 0.5f) {
        glVertex3f(i, 0.051f, -6.5f);
        glVertex3f(i, 0.051f, -2.5f);
    }

    // Garis Horizontal Corak Ubin (Melintang sepanjang sumbu X)
    for (float j = -6.5f; j <= -2.5f; j += 0.5f) {
        glVertex3f(-4.5f, 0.051f, j);
        glVertex3f( 4.5f, 0.051f, j);
    }
    glEnd();

    // ==========================================
    // 1. STRUKTUR UTAMA DINDING GEDUNG (TINGGI TEPAT Y = 2.5f)
    // ==========================================
    // Dinding Belakang Utama
    gambarBalok(-4.5f, 4.5f, -0.5f, 2.5f, -6.5f, -6.4f, rOranye, gOranye, bOranye);

    // Dinding Samping Kiri & Kanan
    gambarBalok(-4.55f, -4.5f, -0.5f, 2.5f, -6.5f, -2.5f, rOranye, gOranye, bOranye);
    gambarBalok(4.5f, 4.55f, -0.5f, 2.5f, -6.5f, -2.5f, rOranye, gOranye, bOranye);

    // Dinding Depan Samping Kiri & Kanan
    gambarBalok(-4.5f, -1.5f, -0.5f, 2.5f, -2.5f, -2.4f, rOranye, gOranye, bOranye);
    gambarBalok(1.5f, 4.5f, -0.5f, 2.5f, -2.5f, -2.4f, rOranye, gOranye, bOranye);

    // ==========================================
    // 2. BAGIAN TENGAH & TIANG DEPAN
    // ==========================================
    gambarBalok(-1.5f, -0.7f, -0.5f, 1.7f, -2.5f, -2.4f, rOranye, gOranye, bOranye);
    gambarBalok( 0.7f,  1.5f, -0.5f, 1.7f, -2.5f, -2.4f, rOranye, gOranye, bOranye);
    gambarBalok(-1.5f,  1.5f,  1.7f, 2.5f, -2.5f, -2.4f, rOranye, gOranye, bOranye);

    gambarBalok(-1.5f, -0.7f, -0.5f, 1.7f, -2.53f, -2.51f, rPutih, gPutih, bPutih);
    gambarBalok( 0.7f,  1.5f, -0.5f, 1.7f, -2.53f, -2.51f, rPutih, gPutih, bPutih);
    gambarBalok(-1.5f,  1.5f,  1.7f, 2.0f, -2.53f, -2.51f, rPutih, gPutih, bPutih);
    gambarBalok(-1.6f, 1.6f, -0.5f, -0.45f, -2.5f, -1.2f, 0.85f, 0.85f, 0.85f);

    // Tiang putih vertikal depan
    gambarBalok(-1.5f, -1.3f, -0.45f, 2.5f, -1.3f, -1.1f, rPutih, gPutih, bPutih);
    gambarBalok( 1.3f,  1.5f, -0.45f, 2.5f, -1.3f, -1.1f, rPutih, gPutih, bPutih);

    // Papan hiasan biru
    gambarBalok(-1.1f, 1.1f, 1.9f, 2.5f, -1.25f, -1.23f, 0.05f, 0.25f, 0.6f);

    // ==========================================
    // 3. JENDELA KACA DEPAN
    // ==========================================
    gambarBalok(-3.5f, -2.5f,  0.3f, 1.6f, -2.39f, -2.37f, rPutih, gPutih, bPutih);
    gambarBalok(-3.4f, -2.6f,  0.4f, 1.5f, -2.36f, -2.35f, 0.2f, 0.3f, 0.3f);
    gambarBalok( 2.5f,  3.5f,  0.3f, 1.6f, -2.39f, -2.37f, rPutih, gPutih, bPutih);
    gambarBalok( 2.6f,  3.4f,  0.4f, 1.5f, -2.36f, -2.35f, 0.2f, 0.3f, 0.3f);

    // ==========================================
    // 4. PINTU KACA TRANSPARAN
    // ==========================================
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

    // ==========================================
    // 5. STRUKTUR ATAP
    // ==========================================
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

    glPopMatrix();
}
