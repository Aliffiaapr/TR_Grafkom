#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include "objekGanesha.h" // Tambahkan ini agar main.cpp kenal file Ganesha-mu
#include "objekPohon.h"
#include "objekBunga.h"
#include "objekSemak.h"
#include "objekPembatas.h"
#include "objekRumahPutih.h"
#include "objekBangku.h"
#include "objekTaman.h"
#include "cagarBudaya.h"
#include "gazeboKiri.h"
#include "gedungMuseum.h"
#include "balok.h"
#include "objekBangkuMeja.h"

// =========================================================================
// VARIABLE KONTROL KAMERA (SKALA NORMAL, STABIL & HALUS)
// =========================================================================

// Posisi spawn awal (Berdiri di tengah jalan raya, agak mundur agar denah langsung terlihat)
glm::vec3 cameraPos   = glm::vec3(0.0f, 2.0f, 22.0f);
glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
glm::vec3 cameraUp    = glm::vec3(0.0f, 1.0f, 0.0f);

// Sudut hadap kamera (Yaw = Kanan/Kiri). -90 derajat agar langsung menghadap lurus ke depan jalan
float yaw   = -90.0f;
float pitch =   0.0f; // 0.0f artinya pandangan mata datar (tidak menunduk/mendongak)

bool isDragging = false;
double lastX = 480.0;
double lastY = 270.0;

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods) {
    if (button == GLFW_MOUSE_BUTTON_LEFT) {
        if (action == GLFW_PRESS) {
            isDragging = true;
            glfwGetCursorPos(window, &lastX, &lastY);
        } else if (action == GLFW_RELEASE) {
            isDragging = false;
        }
    }
}

void cursor_position_callback(GLFWwindow* window, double xpos, double ypos) {
    if (isDragging) {
        double xoffset = xpos - lastX;
        double yoffset = lastY - ypos; // Terbalik: y berkisar dari bawah ke atas
        lastX = xpos;
        lastY = ypos;

        float sensitivity = 0.2f;
        xoffset *= sensitivity;
        yoffset *= sensitivity;

        yaw   += (float)xoffset;
        pitch += (float)yoffset;

        if (pitch > 89.0f) pitch = 89.0f;
        if (pitch < -89.0f) pitch = -89.0f;
    }
}

// --- PARAMETER SENSITIVITAS KECEPATAN DASAR ---
// Nilai di bawah ini diatur menggunakan acuan per detik (Standar Game Realistis)
float basisSpeed  = 8.0f;   // Kecepatan melangkah kaki normal (8 unit per detik)
float basisNengok = 65.0f;  // Kecepatan putar badan/rotasi nyaman (65 derajat per detik)

// Variabel pengontrol waktu untuk mengunci FPS agar pergerakan tidak melompat gasing
float deltaTime = 0.0f;	// Waktu jeda antar frame terakhir
float lastFrame = 0.0f;	// Waktu perekaman frame sebelumnya

// =========================================================================
// FUNGSI PEMBANTU MENGGAMBAR KUBUS CUSTOM (PENGGANTI GLUT)
// =========================================================================

void drawCube(float lebar, float tinggi, float panjang) { //INI CETAKAN KUBUSNYA
    // Menggambar bentuk dasar kubus 3D dengan ukuran dinamis sesuai input skala parameter
    glPushMatrix();
        glScalef(lebar, tinggi, panjang);
        glBegin(GL_QUADS);
            // Sisi Depan
            glVertex3f(-0.5f, -0.5f,  0.5f); glVertex3f( 0.5f, -0.5f,  0.5f);
            glVertex3f( 0.5f,  0.5f,  0.5f); glVertex3f(-0.5f,  0.5f,  0.5f);
            // Sisi Belakang
            glVertex3f(-0.5f, -0.5f, -0.5f); glVertex3f(-0.5f,  0.5f, -0.5f);
            glVertex3f( 0.5f,  0.5f, -0.5f); glVertex3f( 0.5f, -0.5f, -0.5f);
            // Sisi Atas
            glVertex3f(-0.5f,  0.5f, -0.5f); glVertex3f(-0.5f,  0.5f,  0.5f);
            glVertex3f( 0.5f,  0.5f,  0.5f); glVertex3f( 0.5f,  0.5f, -0.5f);
            // Sisi Bawah
            glVertex3f(-0.5f, -0.5f, -0.5f); glVertex3f( 0.5f, -0.5f, -0.5f);
            glVertex3f( 0.5f, -0.5f,  0.5f); glVertex3f(-0.5f, -0.5f,  0.5f);
            // Sisi Kanan
            glVertex3f( 0.5f, -0.5f, -0.5f); glVertex3f( 0.5f,  0.5f, -0.5f);
            glVertex3f( 0.5f,  0.5f,  0.5f); glVertex3f( 0.5f, -0.5f,  0.5f);
            // Sisi Kiri
            glVertex3f(-0.5f, -0.5f, -0.5f); glVertex3f(-0.5f, -0.5f,  0.5f);
            glVertex3f(-0.5f,  0.5f,  0.5f); glVertex3f(-0.5f,  0.5f, -0.5f);
        glEnd();
    glPopMatrix();
}

// =========================================================================
// FUNGSI MENGGAMBAR ENVIRONMENT FONDASI MAP (TANAH & JALAN)
// =========================================================================

void drawGround() {
    glColor3f(0.2f, 0.5f, 0.2f); // Hijau Rumput
    glBegin(GL_QUADS);
        glVertex3f(-50.0f, 0.0f, -50.0f);
        glVertex3f(-50.0f, 0.0f,  50.0f);
        glVertex3f( 50.0f, 0.0f,  50.0f);
        glVertex3f( 50.0f, 0.0f, -50.0f);
    glEnd();
}

void drawRoad() {
    // -----------------------------------------------------------------
    // 1. DASARAN JALAN / NAT SEMEN (Lapis Bawah Berwarna Cokelat Tanah)
    // -----------------------------------------------------------------
    glColor3f(0.35f, 0.35f, 0.35f); // WARNA DI BAWAH PAVING
    glPushMatrix();
        // Jalan Utama Lurus Vertikal
        glBegin(GL_QUADS);
            glVertex3f(-6.0f, 0.01f, -40.0f); glVertex3f(-6.0f, 0.01f,  40.0f);
            glVertex3f( 2.0f, 0.01f,  40.0f); glVertex3f( 2.0f, 0.01f, -40.0f);
        glEnd();

        // PERBAIKAN: Tikungan Belokan Horizontal DIMUNDURKAN sejauh 3 unit (Z dikurangi 3.0f)
        glBegin(GL_QUADS);
            glVertex3f(-6.0f,  0.01f, -28.0f); glVertex3f(-6.0f,  0.01f, -18.0f);
            glVertex3f( 35.0f, 0.01f, -18.0f); glVertex3f( 35.0f, 0.01f, -28.0f);
        glEnd();

        // Blok Pertigaan Tambahan Kanan Bawah
        glBegin(GL_QUADS);
            glVertex3f( 2.0f,  0.01f,  7.3f); glVertex3f( 2.0f,  0.01f,  19.9f);
            glVertex3f( 12.0f, 0.01f,  19.9f); glVertex3f( 12.0f, 0.01f,  7.3f);
        glEnd();
    glPopMatrix();

    // -----------------------------------------------------------------
    // 2. PROSES REPLIKASI BLOK PAVING BERPOLA (MURNI GEOMETRI 3D)
    // -----------------------------------------------------------------
    glColor3f(0.5f, 0.5f, 0.5f); // Warna Abu-abu Tua Sedang (Pas)

    // Ukuran satu unit paving block kecil
    float lebarPaving  = 0.8f;
    float panjangPaving = 0.4f;
    float tebalPaving   = 0.02f;

    float celah = 0.05f;
    int baris = 0;

    // LOOP A: JALAN UTAMA VERTIKAL (Dari Z = -40.0f sampai Z = 40.0f)
    for (float posZ = -40.0f; posZ < 40.0f; posZ += (panjangPaving + celah)) {
        baris++;
        float offsetX = (baris % 2 == 0) ? 0.0f : (lebarPaving / 2.0f);

        for (float posX = -6.0f; posX < 2.0f; posX += (lebarPaving + celah)) {
            if (posX + offsetX + (lebarPaving/2.0f) <= 2.0f && posX + offsetX - (lebarPaving/2.0f) >= -6.0f) {
                glPushMatrix();
                    glTranslatef(posX + offsetX, 0.02f, posZ);
                    drawCube(lebarPaving, tebalPaving, panjangPaving);
                glPopMatrix();
            }
        }
    }

    // ==========================================
    // PERBAIKAN: LOOP B DIMUNDURKAN SAMA PAS (Z dikurangi 3.0f)
    // ==========================================
    for (float posX = 2.0f; posX < 35.0f; posX += (panjangPaving + celah)) {
        baris++;
        float offsetZ = (baris % 2 == 0) ? 0.0f : (lebarPaving / 2.0f);

        // Batas Z mundur dari (-25.0f s/d -15.0f) menjadi (-28.0f s/d -18.0f)
        for (float posZ = -28.0f; posZ < -18.0f; posZ += (lebarPaving + celah)) {
            // Batas IF mundur dari (-14.9f dan -25.1f) menjadi (-17.9f dan -28.1f)
            if (posZ + offsetZ + (lebarPaving/2.0f) <= -17.9f && posZ + offsetZ - (lebarPaving/2.0f) >= -28.1f) {
                glPushMatrix();
                    glTranslatef(posX, 0.02f, posZ + offsetZ);
                    drawCube(panjangPaving, tebalPaving, lebarPaving);
                glPopMatrix();
            }
        }
    }

    //INI JALAN PALING DEPAN MENUJU RUMAH PUTIH
    for (float posX = 2.0f; posX < 12.0f; posX += (panjangPaving + celah)) {
        baris++;
        float offsetZ = (baris % 2 == 0) ? 0.0f : (lebarPaving / 2.0f);

        for (float posZ = 8.0f; posZ < 19.8f; posZ += (lebarPaving + celah)) {
            if (posZ + offsetZ + (lebarPaving/2.0f) <= 25.1f && posZ + offsetZ - (lebarPaving/2.0f) >= 7.3f) {
                glPushMatrix();
                    glTranslatef(posX, 0.02f, posZ + offsetZ);
                    drawCube(panjangPaving, tebalPaving, lebarPaving);
                glPopMatrix();
            }
        }
    }
}

// =========================================================================
// FUNSI KAPLING BLOK DUMMY / WHITEBOXING PENANDA MAKET
// =========================================================================

void drawBangunanBesarAtas() {
    glColor3f(0.7f, 0.3f, 0.3f); // Merah Bata (Candi / Gedung Utama)
    drawCube(20.0f, 10.0f, 10.0f); //MENENTUKAN BESAR KECILNYA KUBUS
}

void drawRumahKiri() {
    // AREA KAPLING KERJA KAMUS (Pindahkan kodingan detail rumahmu ke sini besok di branch 'rumah-oren')
    glColor3f(0.9f, 0.5f, 0.0f); // Warna Oren
    drawCube(6.0f, 5.0f, 6.0f);
}

void drawKotakKecilHijau() {
    glColor3f(0.1f, 0.4f, 0.1f); // Hijau Tua (Penanda dekorasi/pohon/gazebo)
    drawCube(2.0f, 3.0f, 2.0f);
}

void drawRumahSedangBaru() {
    glColor3f(0.8f, 0.6f, 0.2f); // Warna Cokelat Muda / Krem Emas sebagai pembeda
    // Ukuran sedang: Lebar 10, Tinggi 6, Panjang 8
    drawCube(10.0f, 6.0f, 8.0f);
}

// =========================================================================
// LOGIKA SINKRONISASI INPUT JALAN & ROTASI (HALUS CONCURRENT)
// =========================================================================

void processInput(GLFWwindow *window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    // MENGALIKAN INPUT DENGAN DELTATIME (Kunci utama penstabil pergerakan normal)
    float currentSpeed       = basisSpeed * deltaTime;   // Kecepatan jalan konstan
    float currentNengokSpeed = basisNengok * deltaTime;  // Kecepatan toleh konstan halus

    // 1. TOMBOL NAVIGASI MELANGKAH JALAN (W, A, S, D)
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) // MAJU
        cameraPos += currentSpeed * cameraFront;
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) // MUNDUR
        cameraPos -= currentSpeed * cameraFront;
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) // STRAFE/GESER KIRI
        cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * currentSpeed;
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) // STRAFE/GESER KANAN
        cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * currentSpeed;

    // 2. TOMBOL PUTAR BADAN TOLEH 360 DERAJAT (TOMBOL PANAH KIRI/KANAN)
    if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS) { // NENGOK KIRI
        yaw -= currentNengokSpeed;
    }
    if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS) { // NENGOK KANAN
        yaw += currentNengokSpeed;
    }

    // Kalkulasi proyeksi matematika vektor arah pandang baru
    glm::vec3 front;
    front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    front.y = sin(glm::radians(pitch));
    front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    cameraFront = glm::normalize(front);
}


// Fungsi ini akan otomatis dipanggil setiap kali jendela desktop diubah ukurannya
void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    // 1. Atur ulang ukuran Viewport (kanvas tempat OpenGL menggambar)
    glViewport(0, 0, width, height);

    // 2. Atur ulang Proyeksi Kamera agar objek tidak gepeng/distorsi
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    // Hitung ulang Aspect Ratio yang baru (Lebar / Tinggi)
    float aspectRatio = (height == 0) ? 1.0f : (float)width / (float)height;

    // Masukkan kembali FOV kamera Anda (misal 65.0f yang kita pakai kemarin)
    // Jika Anda memakai GLM:
    glm::mat4 projection = glm::perspective(glm::radians(65.0f), aspectRatio, 0.1f, 100.0f);
    glLoadMatrixf(&projection[0][0]);

    // Kembalikan ke mode ModelView untuk menggambar objek
    glMatrixMode(GL_MODELVIEW);
}



// =========================================================================
// INTIPROGRAM UTAMA DAN RENDER ENGINE LOOP
// =========================================================================

int main() { 
    if (!glfwInit()) return -1;

    GLFWwindow* window = glfwCreateWindow(960, 540, "Proyek 3D GLFW - Kalibrasi Sukses", NULL, NULL);
    if (!window) {
        glfwTerminate();
        return -1;  
    }
    glfwMakeContextCurrent(window);

    if (window == NULL) {
    // ... kode penanganan error window ...
}

    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetMouseButtonCallback(window, mouse_button_callback);
    glfwSetCursorPosCallback(window, cursor_position_callback);

    // --- TAMBAHKAN BARIS INI DI SINI ---
    // Mengatur warna latar belakang (langit). Formatnya (Red, Green, Blue, Alpha) dari 0.0f sampai 1.0f.
    // Angka di bawah ini akan menghasilkan warna Biru Langit Cerah (Sky Blue).
    glClearColor(0.53f, 0.81f, 0.92f, 1.0f);

    glEnable(GL_DEPTH_TEST);

    // Inisialisasi tekstur museum (papan nama "MUSEUM SALATIGA")
    initMuseumTextures();
    initCagarBudayaTextures();

    // LOOP GAME UTAMA (Berjalan terus-menerus sebelum window ditutup/silang)
    while (!glfwWindowShouldClose(window)) {

        // --- PROSES MENGHITUNG DURASI WAKTU ANTAR FRAME (DELTATIME CORES) ---
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        // Baca deteksi tombol keyboard
        processInput(window);

        // Bersihkan layar belakang grafis
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glLoadIdentity();

        // -----------------------------------------------------------------
        // KONFIGURASI PROYEKSI LENSA KAMERA PERSPEKTIF
        // -----------------------------------------------------------------
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        glm::mat4 projection = glm::perspective(glm::radians(65.0f), 960.0f / 540.0f, 0.1f, 100.0f);
        glLoadMatrixf(glm::value_ptr(projection));

        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();

        // -----------------------------------------------------------------
        // MATRIKS NAVIGASI POSISI PANDANGAN MATA (LOOK-AT MATRICES)
        // -----------------------------------------------------------------
        glm::mat4 view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
        glLoadMatrixf(glm::value_ptr(view));

        // -----------------------------------------------------------------
        // PROSES DRAWING & PLOTTING STRUKTUR DUNIA SESUAI KOORDINAT DENAH
        // -----------------------------------------------------------------
        drawGround();
        drawRoad();

        // 1. Plotting Gedung Besar Atas (Ditaruh di kanan X=10, mundur Z=-32)
        // Nilai Y=5.0f diatur pas agar dasarnya tepat menempel di permukaan tanah (10/2)
        glPushMatrix();
            glTranslatef(3.0f, 0.0f, -19.0f);
            gambarGedungMuseum(); //GEDUNG MUSEUM
        glPopMatrix();


        glPushMatrix();
            glTranslatef(-6.0f, 0.0f, -30.0f);
            // 2. Putar balik sebesar 90 derajat pada sumbu Y agar menghadap ke depan
            glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
            drawBangkuKayu(-3.5f, 0.1f, 4.0f, true); //INI BANGKU DEPAN RUMAH MUSEUM
        glPopMatrix();



        // 2. Plotting Rumah Sedang Kiri (Ditaruh di kiri jalan X=-12, mundur Z=-20)
        glPushMatrix();
            glTranslatef(-9.0f, 0.1f, -20.0f);
            gambarGazeboKiri(); // INI GAZEBO KIRI
        glPopMatrix();

        // LOKASI 1: Sebelah Gazebo Kiri - batu yoni kecil
        glPushMatrix();
            glTranslatef(-11.0f, 1.0f, -17.5f); // Y diubah ke 1.0f agar menapak tanah
            glScalef(2.5f, 2.5f, 2.5f);
            gambarYoniKecil(); // Memanggil fungsi bentuk dari cagarBudaya.cpp
        glPopMatrix();

        // LOKASI 2: Dekat Rumah Putih - batu hitam
        glPushMatrix();
            glTranslatef(5.0f, 1.0f, -2.5f); // X digeser kanan, Z disesuaikan agar mundur mendekati rumah putih
            glScalef(2.5f, 2.5f, 2.5f);
            gambarBatuHitam();
        glPopMatrix();

        // LOKASI 3: Depan Bangku - batu ratna bulat
        glPushMatrix();
            glTranslatef(7.5f, 1.0f, -12.0f);
            glScalef(2.5f, 2.5f, 2.5f);
            gambarBatuRatna();
        glPopMatrix();

        // LOKASI 4: Dekat Pagar - batu yoni besar
        glPushMatrix();
            glTranslatef(17.5f, 1.0f, -20.0f); // Z disamakan dengan Biru (-17.0f), X diperbesar biar mepet pagar
            glScalef(2.5f, 2.5f, 2.5f);
            gambarYoniBesar();
        glPopMatrix();

        glPushMatrix();
            glTranslatef(-10.0f, 0.0f, -5.5f);
            drawBangkuMeja(); //INI BANGKU MEJA SAMPING GAZEBO
        glPopMatrix();

        glPushMatrix();
            glTranslatef(-11.0f, 1.5f, 5.0f);
            drawObjectGanesha(); //INI OBJEK GANESHA
        glPopMatrix();

        glPushMatrix();
            glTranslatef(-11.0f, 0.0f, 16.0f);
            drawObjekPohon(); //INI OBJEK POHON SAMPING GANESHA
        glPopMatrix();
        glPushMatrix();
            glTranslatef(-17.0f, 0.0f, 19.0f);
            drawObjekPohon(); //INI OBJEK POHON SAMPING GANESHA
        glPopMatrix();

        glPushMatrix();
            glTranslatef(-9.0f, 0.0f, 16.0f);
            drawPohonMungil(); //INI OBJEK BUNGAAAA
        glPopMatrix();
        glPushMatrix();
            glTranslatef(-11.0f, 0.0f, 18.0f);
            objekSemak(); //INI OBJEK SEMAK
        glPopMatrix();


        // 4. Plotting Kotak-Kotak Kecil di Sisi Taman Sebelah Kanan Jalan
        glPushMatrix();
            glTranslatef(8.0f, 0.0f, 15.0f); // Taman kanan-atas
            //kosong
        glPopMatrix();

        glPushMatrix();
            glTranslatef(22.0f, 1.5f, 12.0f); // Taman kanan-pojok
            drawPohonTaman(2.0f, 0.0f, 12.0f, 1.2f); // INI OBEJK POHON BESAR
        glPopMatrix();



        // ==========================================
        // STRUKTUR RUMAH PUTIH (DIPERBESAR & PROPORSIONAL)
        // ==========================================
        glPushMatrix();
            // 1. Pindahkan posisi rumah ke koordinat dunia
            glTranslatef(15.5f, 0.0f, 14.0f);
            // 2. Perbesar rumah sebesar 1.4 kali lipat (X, Y, Z)
            glScalef(1.4f, 1.4f, 1.4f);
            drawRumahPutih(); // RUMAH PUTIH
        glPopMatrix();

        glPushMatrix();
            // 1. Pindahkan posisi atap (Y dinaikkan ke 0.7f agar pas menempel di atas rumah yang meninggi)
            glTranslatef(15.5f, 0.7f, 14.0f);
            // 2. Perbesar atap dengan nilai skala yang SAMA PERSIS (1.4 kali lipat)
            glScalef(1.4f, 1.4f, 1.4f);
            drawAtapRumahPutih(); // ATAP RUMAH PUTIH
        glPopMatrix();


        glPushMatrix();
            glTranslatef(22.0f, 0.0f, 24.0f);
            drawObjekPohon(); //INI OBJEK POHON SAMPING RUMHA PUTIH
        glPopMatrix();


         glPushMatrix();
            glTranslatef(11.0f, 0.0f, 14.0f);
            drawBangkuKayu(-3.5f, 0.1f, 4.0f, true); //INI BANGKU DEPAN RUMAH PUTIH
        glPopMatrix();

        glPushMatrix();
            max: glTranslatef(20.0f, 0.0f, 22.0f);
            objekSemak(); //INI OBJEK semak KANAN
        glPopMatrix();
        glPushMatrix();
            glTranslatef(15.0f, 0.0f, 22.0f);
            objekSemak(); //INI OBJEK semak KANAN
        glPopMatrix();
        glPushMatrix();
            glTranslatef(10.0f, 0.0f, 22.0f);
            objekSemak(); //INI OBJEK semak KANAN
        glPopMatrix();


        // PAGAR KIRI DEPAN
        glPushMatrix();
            glTranslatef(-21.5f, 0.0f, 22.0f); // Posisi belakang
            drawPagarSegment(15.0f);            // Pagar mendatar (Sumbu X) sepanjang 15 unit
        glPopMatrix();

        // PAGAR KANAN DEPAN
        glPushMatrix();
            glTranslatef(5.0f, 0.0f, 25.0f); // Pas di batas utara jalan baru
            drawPagarSegment(20.0f);           // Memanjang 20 unit ke kanan
        glPopMatrix();

        glPushMatrix();
            // Start dari ujung kiri pagar depan (X = -21.5f), ditarik mundur ke belakang
            glTranslatef(-21.5f, 0.0f, 22.0f);
            // PUTAR 90 DERAJAT agar jalur pagarnya memanjang ke arah Sumbu Z (Mundur)
            glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
            drawPagarSegment(50.0f); // Sesuaikan panjangnya mundur ke belakang (misal 40 unit)
        glPopMatrix();

        // =================================================================
        // PAGAR SAMPING KANAN (Menutup Area Rumah Baru ke Belakang)
        // =================================================================
        glPushMatrix();
            // Start dari ujung kanan pagar depan (X = 5.0f + panjang 20.0f = 25.0f)
            glTranslatef(25.0f, 0.0f, 25.0f);
            // PUTAR 90 DERAJAT agar jalur pagarnya memanjang sejajar sumbu samping (Z)
            glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
            drawPagarSegment(50.0f); // Sesuaikan panjang mundur ke belakang
        glPopMatrix();



        // Tukar frame buffer ke layar monitor dan periksa event sistem
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // Bersihkan resource memori GLFW sebelum keluar program
    glfwTerminate();
    return 0;
}
