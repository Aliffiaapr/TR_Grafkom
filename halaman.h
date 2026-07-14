#ifndef HALAMAN_H
#define HALAMAN_H

#include <GLFW/glfw3.h>

void gambarHalamanDanPaving();
void gambarTanamanHalaman(); // Dipanggil otomatis di dalam gambarHalamanDanPaving()
void gambarPohonKamboja(float cx, float cy, float cz, float skala);

// Barisan semak rimbun di sepanjang sumbu Z pada posisi X tetap (misal menyusuri pagar)
// xPos       = koordinat X tempat barisan berada (misal 23.0f)
// zMulai     = titik awal Z
// zAkhir     = titik akhir Z
// jumlah     = banyaknya rumpun yang ditanam di sepanjang barisan
void gambarSemakPagar(float xPos, float zMulai, float zAkhir, int jumlah);

#endif