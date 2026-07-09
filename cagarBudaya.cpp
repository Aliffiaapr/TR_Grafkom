#include "cagarBudaya.h"
#include "balok.h"

void gambarCagarBudayaDepan() {
    // ==========================================
    // GLOBAL SCALE (DITURUNKAN KE 1.8f AGAR AGAK KECIL SEDIKIT)
    // ==========================================
    glPushMatrix();
    glScalef(1.8f, 1.8f, 1.8f);

    // 3 Lapis Balok Struktur Cagar Budaya
    gambarBalok(-0.6f, 0.6f, -0.5f, -0.2f, 2.0f, 3.2f, 0.85f, 0.85f, 0.85f);
    gambarBalok(-0.4f, 0.4f, -0.2f,  0.2f, 2.2f, 3.0f, 0.45f, 0.45f, 0.45f);
    gambarBalok(-0.2f, 0.2f,  0.2f,  0.4f, 2.4f, 2.8f, 0.50f, 0.50f, 0.50f);

    // ==========================================
    // SELESAI POP MATRIX
    // ==========================================
    glPopMatrix();
}
