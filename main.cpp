#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>

// =========================================================================
// VARIABLE KONTROL KAMERA (SKALA NORMAL, STABIL & HALUS)
// =========================================================================

// Posisi spawn awal (Berdiri di tengah jalan raya, agak mundur agar denah langsung terlihat)
glm::vec3 cameraPos   = glm::vec3(0.0f, 2.0f, 40.0f);
glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
glm::vec3 cameraUp    = glm::vec3(0.0f, 1.0f, 0.0f);

// Sudut hadap kamera (Yaw = Kanan/Kiri). -90 derajat agar langsung menghadap lurus ke depan jalan
float yaw   = -90.0f;
float pitch =   0.0f; // 0.0f artinya pandangan mata datar (tidak menunduk/mendongak)

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
    glColor3f(0.4f, 0.4f, 0.4f); // Abu-abu Paving block
    glBegin(GL_QUADS);
        // Jalan Utama Lurus Vertikal (Nilai Y dinaikkan 0.01f agar tekstur tidak flicker berkedip)
        glVertex3f(-6.0f, 0.01f, -40.0f); glVertex3f(-6.0f, 0.01f,  40.0f);
        glVertex3f( 2.0f, 0.01f,  40.0f); glVertex3f( 2.0f, 0.01f, -40.0f);

        // Tikungan Belokan Horizontal ke Kanan (Sesuai denah kertas kelompok)
        glVertex3f(-6.0f, 0.01f, -25.0f); glVertex3f(-6.0f, 0.01f, -15.0f);
        glVertex3f( 35.0f, 0.01f, -15.0f); glVertex3f( 35.0f, 0.01f, -25.0f);

        glVertex3f( 2.0f, 0.01f,  25.0f); // Titik 1 (Kiri-Bawah)
        glVertex3f( 2.0f, 0.01f,  14.0f); // Titik 2 (Kiri-Atas)
        glVertex3f( 12.0f, 0.01f,  14.0f); // Titik 3 (Kanan-Atas)
        glVertex3f( 12.0f, 0.01f,  25.0f); // Titik 4 (Kanan-Bawah)
    glEnd();
}

// =========================================================================
// FUNSI KAPLING BLOK DUMMY / WHITEBOXING PENANDA MAKET
// =========================================================================

void drawBangunanBesarAtas() {
    glColor3f(0.7f, 0.3f, 0.3f); // Merah Bata (Candi / Gedung Utama)
    drawCube(20.0f, 10.0f, 10.0f); //MENENTUKAN BESAR KECILNYA KUBUS
}

void drawRumahKiri() {
    // 🏠 AREA KAPLING KERJA KAMUS (Pindahkan kodingan detail rumahmu ke sini besok di branch 'rumah-oren')
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

    // Mengunci posisi Pitch datar agar kamera tidak mendongak ke langit/tanah secara tidak sengaja
    pitch = 0.0f;

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

    // --- TAMBAHKAN BARIS INI DI SINI ---
    // Mengatur warna latar belakang (langit). Formatnya (Red, Green, Blue, Alpha) dari 0.0f sampai 1.0f.
    // Angka di bawah ini akan menghasilkan warna Biru Langit Cerah (Sky Blue).
    glClearColor(0.53f, 0.81f, 0.92f, 1.0f);

    glEnable(GL_DEPTH_TEST);

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
            glTranslatef(3.0f, 5.0f, -30.0f);
            drawBangunanBesarAtas();
        glPopMatrix();

        // 2. Plotting Rumah Sedang Kiri (Ditaruh di kiri jalan X=-12, mundur Z=-20)
        glPushMatrix();
            glTranslatef(-12.0f, 2.5f, -20.0f);
            drawRumahKiri();
        glPopMatrix();

        // 3. Plotting Barisan 4 Kotak Dekorasi di Sisi Kiri Jalan (Loop otomatis rapi)
        for(int i = 0; i < 4; i++) {
            glPushMatrix();
                glTranslatef(-11.0f, 1.5f, -10.0f + (i * 8.0f));
                drawKotakKecilHijau();
            glPopMatrix();
        }

        // 4. Plotting Kotak-Kotak Kecil di Sisi Taman Sebelah Kanan Jalan
        glPushMatrix();
            glTranslatef(8.0f, 1.5f, -12.0f); // Taman kanan-atas
            drawKotakKecilHijau();
        glPopMatrix();

        glPushMatrix();
            glTranslatef(22.0f, 1.5f, -12.0f); // Taman kanan-pojok
            drawKotakKecilHijau();
        glPopMatrix();

        // =================================================================
        // BARU: Plotting Rumah Sedang di Depan Jalan Belokan
        // =================================================================
        glPushMatrix();
            // X=7.0f (di tengah jalan baru), Y=3.0f (pas di tanah), Z=9.0f (pinggir jalan baru)
            glTranslatef(17.0f, 3.0f, 20.0f);
            drawRumahSedangBaru();
        glPopMatrix();

        // Tukar frame buffer ke layar monitor dan periksa event sistem
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // Bersihkan resource memori GLFW sebelum keluar program
    glfwTerminate();
    return 0;
}
