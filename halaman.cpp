#include "halaman.h"
#include <cmath>

// =========================================================================
// HELPER: SATU HELAI DAUN (segitiga meruncing, condong ke atas dari tanah)
// panjang/lebar dalam satuan lokal; sudutTegak = derajat kemiringan dari tanah
// =========================================================================
static void gambarDaunTunggal(float panjang, float lebar, float sudutTegak, float r, float g, float b) {
    glPushMatrix();
    glRotatef(sudutTegak, 1.0f, 0.0f, 0.0f); // miringkan daun ke atas

    glColor3f(r, g, b);
    // Sisi depan
    glBegin(GL_TRIANGLES);
    glNormal3f(0.0f, 0.0f, 1.0f);
    glVertex3f(-lebar * 0.5f, 0.0f, 0.0f);
    glVertex3f( lebar * 0.5f, 0.0f, 0.0f);
    glVertex3f(0.0f, panjang, 0.0f);
    glEnd();
    // Sisi belakang (biar tetap kelihatan dari arah manapun, tidak ke-cull)
    glBegin(GL_TRIANGLES);
    glNormal3f(0.0f, 0.0f, -1.0f);
    glVertex3f(-lebar * 0.5f, 0.0f, 0.0f);
    glVertex3f(0.0f, panjang, 0.0f);
    glVertex3f( lebar * 0.5f, 0.0f, 0.0f);
    glEnd();

    glPopMatrix();
}

// =========================================================================
// HELPER: RUMPUN TANAMAN HIAS (kumpulan daun radial dari satu titik tanah)
// cx, cy, cz = posisi dasar rumpun di tanah; skala = ukuran keseluruhan
// =========================================================================
static void gambarRumpunTanaman(float cx, float cy, float cz, float skala) {
    glPushMatrix();
    glTranslatef(cx, cy, cz);
    glScalef(skala, skala, skala);

    const int jumlahDaun = 14;
    for (int i = 0; i < jumlahDaun; i++) {
        float sudutPutar = (360.0f / jumlahDaun) * i + (i % 2) * 8.0f;    // sebar 360 derajat + variasi
        float panjang     = 0.85f + 0.22f * ((i % 3) - 1);                 // daun lebih panjang/besar
        float lebar        = 0.11f + 0.03f * (i % 2);                      // daun lebih lebar
        float sudutTegak    = 28.0f + (i % 4) * 10.0f;                     // variasi kemiringan

        glPushMatrix();
        glRotatef(sudutPutar, 0.0f, 1.0f, 0.0f);
        if (i % 3 == 0) {
            // Daun merah/marun (seperti puring / croton)
            gambarDaunTunggal(panjang, lebar, sudutTegak, 0.55f, 0.10f, 0.08f);
        } else {
            // Daun hijau (tua/muda bervariasi)
            float tua = 0.30f + 0.10f * (i % 2);
            gambarDaunTunggal(panjang, lebar, sudutTegak, tua * 0.45f, tua + 0.25f, tua * 0.35f);
        }
        glPopMatrix();
    }

    glPopMatrix();
}

// =========================================================================
// TANAMAN DI SEKELILING HALAMAN
// Y = 0.0f (level tanah asli sesuai drawGround() di main.cpp).
// Posisi dipilih agar SELALU DI RUMPUT (di luar 3 zona paving drawRoad():
//   Zona A: X[-6,2]  Z semua      (jalan utama vertikal)
//   Zona B: X[-6,35] Z[-28,-18]   (tikungan horizontal, depan gedung museum)
//   Zona C: X[2,12]  Z[7.3,19.9]  (cabang pertigaan kanan)
// Ditempatkan di samping Batu Ratna (7.5,-12) dan di samping gedung museum
// (gedungMuseum, translate 3,0,-19, badan bangunan kira-kira X -8..14, Z -28..-44).
// =========================================================================
void gambarTanamanHalaman() {
    // Di samping Batu Ratna (kombinasi hijau-merah, ukuran besar)
    gambarRumpunTanaman(9.8f, 0.0f, -12.5f, 3.0f);
    gambarRumpunTanaman(5.0f, 0.0f, -13.8f, 2.7f);

    // Di samping gedung museum (sisi kiri & kanan bangunan, di luar zona paving)
    gambarRumpunTanaman(-10.0f, 0.0f, -38.0f, 3.0f);
    gambarRumpunTanaman(15.8f, 0.0f, -35.0f, 3.0f);

    // Di dekat pohon (20.0, 0.0, 1.0) -- digeser sedikit agar tidak menumpuk di batang pohon
    gambarRumpunTanaman(15.0f, 0.0f, 2.0f, 2.5f);
}

// =========================================================================
// HELPER: BUNGA ORANYE KECIL (aksen warna seperti pada semak canna/bunga tasbih)
// =========================================================================
static void gambarBungaOranye(float cx, float cy, float cz, float skala) {
    glPushMatrix();
    glTranslatef(cx, cy, cz);
    glScalef(skala, skala, skala);

    // Batang kecil
    glColor3f(0.22f, 0.42f, 0.14f);
    glBegin(GL_TRIANGLES);
    glNormal3f(0.0f, 0.0f, 1.0f);
    glVertex3f(-0.03f, 0.0f, 0.0f);
    glVertex3f( 0.03f, 0.0f, 0.0f);
    glVertex3f( 0.0f, 0.55f, 0.0f);
    glEnd();

    // Kelopak-kelopak oranye di ujung, menyebar radial
    const int kelopak = 6;
    for (int i = 0; i < kelopak; i++) {
        float sudut = (360.0f / kelopak) * i;
        glPushMatrix();
        glTranslatef(0.0f, 0.55f, 0.0f);
        glRotatef(sudut, 0.0f, 1.0f, 0.0f);
        glRotatef(55.0f, 1.0f, 0.0f, 0.0f);
        glColor3f(0.95f, 0.45f, 0.05f);
        glBegin(GL_TRIANGLES);
        glNormal3f(0.0f, 0.0f, 1.0f);
        glVertex3f(-0.06f, 0.0f, 0.0f);
        glVertex3f( 0.06f, 0.0f, 0.0f);
        glVertex3f( 0.0f, 0.20f, 0.0f);
        glEnd();
        glPopMatrix();
    }

    glPopMatrix();
}

// =========================================================================
// BARISAN SEMAK RIMBUN DI SEPANJANG SUMBU Z (misal menyusuri pagar)
// xPos = posisi X tetap; zMulai/zAkhir = rentang Z; jumlah = banyak rumpun
// =========================================================================
void gambarSemakPagar(float xPos, float zMulai, float zAkhir, int jumlah) {
    if (jumlah < 2) jumlah = 2;
    float jarak = (zAkhir - zMulai) / (jumlah - 1);

    for (int i = 0; i < jumlah; i++) {
        float z = zMulai + jarak * i;
        float xJitter = ((i % 3) - 1) * 0.5f;      // sedikit maju-mundur agar tidak terlihat baris kaku
        float skala   = 2.0f + 0.5f * (i % 3);      // variasi ukuran rumpun antar posisi

        gambarRumpunTanaman(xPos + xJitter, 0.0f, z, skala);

        // Selingi dengan bunga oranye tiap beberapa rumpun, seperti aksen warna pada foto referensi
        if (i % 2 == 0) {
            gambarBungaOranye(xPos + xJitter - 0.6f, 0.0f, z + 0.3f, 1.4f);
        }
    }
}

// =========================================================================
// HELPER: SILINDER (untuk batang & cabang pohon kamboja, meruncing ke ujung)
// =========================================================================
static void gambarSilinderPohon(float radiusBawah, float radiusAtas, float tinggi, float r, float g, float b) {
    glColor3f(r, g, b);
    const int slices = 10;
    glBegin(GL_QUAD_STRIP);
    for (int i = 0; i <= slices; i++) {
        float angle = 2.0f * 3.14159f * i / slices;
        float x = cos(angle), z = sin(angle);
        glNormal3f(x, 0.3f, z);
        glVertex3f(x * radiusBawah, 0.0f, z * radiusBawah);
        glVertex3f(x * radiusAtas, tinggi, z * radiusAtas);
    }
    glEnd();
}

// =========================================================================
// HELPER: DAUN LEBAR (daun kamboja: lebih lebar & pendek dari daun rumput)
// =========================================================================
static void gambarDaunLebar(float panjang, float lebar, float r, float g, float b) {
    glColor3f(r, g, b);
    glBegin(GL_TRIANGLES);
    glNormal3f(0.0f, 0.6f, 0.8f);
    glVertex3f(-lebar * 0.5f, 0.0f, 0.0f);
    glVertex3f( lebar * 0.5f, 0.0f, 0.0f);
    glVertex3f(0.0f, panjang * 0.35f, panjang);
    glEnd();
    glBegin(GL_TRIANGLES);
    glNormal3f(0.0f, -0.6f, -0.8f);
    glVertex3f(-lebar * 0.5f, 0.0f, 0.0f);
    glVertex3f(0.0f, panjang * 0.35f, panjang);
    glVertex3f( lebar * 0.5f, 0.0f, 0.0f);
    glEnd();
}

// =========================================================================
// HELPER: RUMPUN DAUN DI UJUNG CABANG (khas kamboja: daun berumpun di pucuk)
// =========================================================================
static void gambarUjungDaunKamboja() {
    const int jumlah = 9;
    for (int i = 0; i < jumlah; i++) {
        float sudut = (360.0f / jumlah) * i;
        float panjang = 0.35f + 0.08f * (i % 3);
        float lebar = 0.14f + 0.03f * (i % 2);
        glPushMatrix();
        glRotatef(sudut, 0.0f, 1.0f, 0.0f);
        glRotatef(55.0f, 1.0f, 0.0f, 0.0f); // daun agak terkulai/mendatar seperti aslinya
        gambarDaunLebar(panjang, lebar, 0.12f, 0.42f, 0.10f);
        glPopMatrix();
    }
}

// =========================================================================
// HELPER: CABANG POHON KAMBOJA (rekursif, cabang tebal bercabang lagi)
// =========================================================================
static void gambarCabangKamboja(float panjang, float radius, int tingkat) {
    gambarSilinderPohon(radius, radius * 0.7f, panjang, 0.45f, 0.38f, 0.28f);

    glPushMatrix();
    glTranslatef(0.0f, panjang, 0.0f);

    if (tingkat <= 0) {
        gambarUjungDaunKamboja();
    } else {
        const int jumlahCabang = 3;
        for (int i = 0; i < jumlahCabang; i++) {
            float sudutPutar = (360.0f / jumlahCabang) * i + 20.0f * tingkat;
            glPushMatrix();
            glRotatef(sudutPutar, 0.0f, 1.0f, 0.0f);
            glRotatef(32.0f + (i % 2) * 10.0f, 1.0f, 0.0f, 0.0f); // cabang melebar khas kamboja
            gambarCabangKamboja(panjang * 0.65f, radius * 0.6f, tingkat - 1);
            glPopMatrix();
        }
    }
    glPopMatrix();
}

// =========================================================================
// POHON KAMBOJA / FRANGIPANI (batang tebal bercabang, daun berumpun di ujung)
// cx, cy, cz = posisi dasar di tanah; skala = ukuran keseluruhan
// =========================================================================
void gambarPohonKamboja(float cx, float cy, float cz, float skala) {
    glPushMatrix();
    glTranslatef(cx, cy, cz);
    glScalef(skala, skala, skala);

    // Batang utama
    gambarSilinderPohon(0.18f, 0.14f, 1.2f, 0.4f, 0.32f, 0.22f);

    glPushMatrix();
    glTranslatef(0.0f, 1.2f, 0.0f);
    const int jumlahCabangUtama = 3;
    for (int i = 0; i < jumlahCabangUtama; i++) {
        float sudutPutar = (360.0f / jumlahCabangUtama) * i;
        glPushMatrix();
        glRotatef(sudutPutar, 0.0f, 1.0f, 0.0f);
        glRotatef(30.0f, 1.0f, 0.0f, 0.0f);
        gambarCabangKamboja(0.9f, 0.11f, 1);
        glPopMatrix();
    }
    glPopMatrix();

    glPopMatrix();
}

void gambarHalamanDanPaving() {
    // 1. Rumput Hijau Utama
    glBegin(GL_QUADS);
    glNormal3f(0.0f, 1.0f, 0.0f);
    glColor3f(0.25f, 0.5f, 0.25f);
    glVertex3f(-20.0f, -0.5f, -20.0f); glVertex3f(20.0f, -0.5f, -20.0f);
    glVertex3f(20.0f, -0.5f, 20.0f); glVertex3f(-20.0f, -0.5f, 20.0f);
    glEnd();

    // 2. Jalan Paving Blok Depan Rumah (Abu-abu gelap)
    glBegin(GL_QUADS);
    glNormal3f(0.0f, 1.0f, 0.0f);
    glColor3f(0.45f, 0.43f, 0.4f);
    glVertex3f(-6.0f, -0.49f, -3.5f); glVertex3f(6.0f, -0.49f, -3.5f);
    glVertex3f(6.0f, -0.49f,  4.0f); glVertex3f(-6.0f, -0.49f,  4.0f);
    glEnd();
}