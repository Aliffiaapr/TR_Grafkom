#ifndef GEDUNGMUSEUM_H
#define GEDUNGMUSEUM_H

#include <GLFW/glfw3.h>

// Inisialisasi tekstur museum (panggil sekali di main sebelum render loop)
void initMuseumTextures();

// Fungsi utama menggambar gedung museum lengkap (exterior + interior)
void gambarGedungMuseum();

#endif