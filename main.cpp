#include <GLFW/glfw3.h>
#include <iostream>
#include <cmath>

const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

// Posisi kamera awal diatur agak mundur dan tinggi agar langsung melihat bangunan dengan baik
float cameraX = 0.0f, cameraY = 1.2f, cameraZ = 7.0f; 
float cameraFrontX = 0.0f, cameraFrontY = 0.0f, cameraFrontZ = -1.0f; 
float cameraUpX = 0.0f, cameraUpY = 1.0f, cameraUpZ = 0.0f;    

bool firstMouse = true;
float yaw = -90.0f; float pitch = 0.0f;  
float lastX = 800.0f / 2.0; float lastY = 600.0f / 2.0;
float deltaTime = 0.0f; float lastFrame = 0.0f;

// --- FUNGSI BANTUAN UNTUK MEMBUAT KOTAK 3D (CUBE) DENGAN NORMAL ---
void gambarBalok(float xMin, float xMax, float yMin, float yMax, float zMin, float zMax, float r, float g, float b) {
    glColor3f(r, g, b);
    glBegin(GL_QUADS);
    
    // Depan
    glNormal3f(0.0f, 0.0f, 1.0f);
    glVertex3f(xMin, yMin, zMax); glVertex3f(xMax, yMin, zMax);
    glVertex3f(xMax, yMax, zMax); glVertex3f(xMin, yMax, zMax);
    
    // Belakang
    glNormal3f(0.0f, 0.0f, -1.0f);
    glVertex3f(xMin, yMin, zMin); glVertex3f(xMin, yMax, zMin);
    glVertex3f(xMax, yMax, zMin); glVertex3f(xMax, yMin, zMin);
    
    // Kiri
    glNormal3f(-1.0f, 0.0f, 0.0f);
    glVertex3f(xMin, yMin, zMin); glVertex3f(xMin, yMin, zMax);
    glVertex3f(xMin, yMax, zMax); glVertex3f(xMin, yMax, zMin);
    
    // Kanan
    glNormal3f(1.0f, 0.0f, 0.0f);
    glVertex3f(xMax, yMin, zMin); glVertex3f(xMax, yMax, zMin);
    glVertex3f(xMax, yMax, zMax); glVertex3f(xMax, yMin, zMax);
    
    // Atas
    glNormal3f(0.0f, 1.0f, 0.0f);
    glVertex3f(xMin, yMax, zMin); glVertex3f(xMin, yMax, zMax);
    glVertex3f(xMax, yMax, zMax); glVertex3f(xMax, yMax, zMin);
    
    // Bawah
    glNormal3f(0.0f, -1.0f, 0.0f);
    glVertex3f(xMin, yMin, zMin); glVertex3f(xMax, yMin, zMin);
    glVertex3f(xMax, yMin, zMax); glVertex3f(xMin, yMin, zMax);
    
    glEnd();
}

// --- AREA MODULAR PROYEK MUSEUM SALATIGA ---

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

void gambarGedungMuseum() {
    // WARNA UTAMA (Sesuai Foto)
    float rOranye = 0.95f, gOranye = 0.32f, bOranye = 0.08f;
    float rAtap = 0.65f, gAtap = 0.32f, bAtap = 0.22f;
    float rPutih = 0.92f, gPutih = 0.92f, bPutih = 0.92f;

    // 1. STRUKTUR UTAMA DINDING GEDUNG (MENUTUP SELURUH SISI RUMAH)
    // Dinding Belakang (Menutup utuh dari ujung kiri ke kanan tanpa lubang)
    gambarBalok(-4.5f, 4.5f, -0.5f, 2.0f, -3.5f, -3.4f, rOranye, gOranye, bOranye);
    
    // Dinding Samping Kiri 
    gambarBalok(-4.55f, -4.5f, -0.5f, 2.0f, -3.5f, -2.5f, rOranye, gOranye, bOranye);
    
    // Dinding Samping Kanan
    gambarBalok(4.5f, 4.55f, -0.5f, 2.0f, -3.5f, -2.5f, rOranye, gOranye, bOranye);

    // Dinding Depan Sayap Kiri
    gambarBalok(-4.5f, -1.5f, -0.5f, 2.0f, -2.5f, -2.4f, rOranye, gOranye, bOranye);
    
    // Dinding Depan Sayap Kanan
    gambarBalok(1.5f, 4.5f, -0.5f, 2.0f, -2.5f, -2.4f, rOranye, gOranye, bOranye);

    // 2. BAGIAN TENGAH (TERAS / PORCH DEPAN UTAMA)
    // Dinding depan tengah tempat bersandar pintu (Kiri & Kanan lubang pintu)
    gambarBalok(-1.5f, -0.7f, -0.5f, 1.7f, -2.5f, -2.4f, rOranye, gOranye, bOranye);
    gambarBalok( 0.7f,  1.5f, -0.5f, 1.7f, -2.5f, -2.4f, rOranye, gOranye, bOranye);
    // Dinding atas teras (Tempat bersandarnya papan nama)
    gambarBalok(-1.5f,  1.5f,  1.7f, 2.5f, -2.5f, -2.4f, rOranye, gOranye, bOranye);
    
    // Menempel di balik dinding depan tengah agar bagian dalam ruangan berwarna putih
    gambarBalok(-1.5f, -0.7f, -0.5f, 1.7f, -2.53f, -2.51f, rPutih, gPutih, bPutih); // Sisi dalam kiri pintu
    gambarBalok( 0.7f,  1.5f, -0.5f, 1.7f, -2.53f, -2.51f, rPutih, gPutih, bPutih); // Sisi dalam kanan pintu
    gambarBalok(-1.5f,  1.5f,  1.7f, 2.0f, -2.53f, -2.51f, rPutih, gPutih, bPutih); // Sisi dalam atas pintu (batas tinggi ruangan Y=2.0f)
    // Lantai Teras (Maju menjorok ke depan dari Z -2.5 ke -1.2)
    gambarBalok(-1.6f, 1.6f, -0.5f, -0.45f, -2.5f, -1.2f, 0.85f, 0.85f, 0.85f);

    // Tiang Penyangga Kiri & Kanan Teras (Putih, tegak di bagian depan teras)
    gambarBalok(-1.5f, -1.3f, -0.45f, 2.5f, -1.3f, -1.1f, rPutih, gPutih, bPutih);
    gambarBalok( 1.3f,  1.5f, -0.45f, 2.5f, -1.3f, -1.1f, rPutih, gPutih, bPutih);

    // Papan Nama Biru "MUSEUM SALATIGA" (Ditempel di area atas depan tiang teras)
    gambarBalok(-1.1f, 1.1f, 1.8f, 2.3f, -1.25f, -1.23f, 0.05f, 0.25f, 0.6f);


    // 3. JENDELA KACA DEPAN (SAYAP KIRI & KANAN)
    // Jendela Sayap Kiri
    gambarBalok(-3.5f, -2.5f,  0.3f, 1.4f, -2.39f, -2.37f, rPutih, gPutih, bPutih);
    gambarBalok(-3.4f, -2.6f,  0.4f, 1.3f, -2.36f, -2.35f, 0.2f, 0.3f, 0.3f); 

    // Jendela Sayap Kanan
    gambarBalok( 2.5f,  3.5f,  0.3f, 1.4f, -2.39f, -2.37f, rPutih, gPutih, bPutih);
    gambarBalok( 2.6f,  3.4f,  0.4f, 1.3f, -2.36f, -2.35f, 0.2f, 0.3f, 0.3f);


    // 4. PINTU KACA TRANSPARAN (DIUBAH: Membuka Serong ke Luar Teras)
    // Daun Pintu Kiri (Engsel di X: -0.7, berayun keluar ke arah depan teras Z: -2.1)
    glBegin(GL_QUADS);
    glNormal3f(-0.3f, 0.0f, 0.95f); glColor4f(0.7f, 0.85f, 0.9f, 0.4f); // Alpha 0.4 bening cerah
    glVertex3f(-0.7f, -0.5f, -2.5f); glVertex3f(-1.1f, -0.5f, -2.1f);
    glVertex3f(-1.1f,  1.7f, -2.1f); glVertex3f(-0.7f,  1.7f, -2.5f);
    glEnd();

    // Daun Pintu Kanan (Engsel di X: 0.7, berayun keluar ke arah depan teras Z: -2.1)
    glBegin(GL_QUADS);
    glNormal3f(0.3f, 0.0f, 0.95f); glColor4f(0.7f, 0.85f, 0.9f, 0.4f);
    glVertex3f(0.7f, -0.5f, -2.5f); glVertex3f(1.1f, -0.5f, -2.1f);
    glVertex3f(1.1f,  1.7f, -2.1f); glVertex3f(0.7f,  1.7f, -2.5f);
    glEnd();

    // 5. STRUKTUR ATAP
    // A. Atap Segitiga Depan (Porch Tengah)
    glBegin(GL_TRIANGLES);
    glNormal3f(0.0f, 0.0f, 1.0f); glColor3f(rAtap, gAtap, bAtap);
    glVertex3f(-1.8f, 2.4f, -1.1f); glVertex3f(1.8f, 2.4f, -1.1f); glVertex3f(0.0f, 3.4f, -1.1f);
    glEnd();

    // Kemiringan Atap Tengah Kiri & Kanan
    glBegin(GL_QUADS);
    glNormal3f(-0.6f, 0.8f, 0.0f);
    glVertex3f(-1.8f, 2.4f, -1.1f); glVertex3f(0.0f, 3.4f, -1.1f);
    glVertex3f(0.0f, 3.4f, -2.5f);  glVertex3f(-1.8f, 2.4f, -2.5f);
    
    glNormal3f(0.6f, 0.8f, 0.0f);
    glVertex3f(0.0f, 3.4f, -1.1f);  glVertex3f(1.8f, 2.4f, -1.1f);
    glVertex3f(1.8f, 2.4f, -2.5f);  glVertex3f(0.0f, 3.4f, -2.5f);
    glEnd();

    // B. Atap Sayap Utama (Memanjang menutupi seluruh luas bangunan baru)
    glBegin(GL_QUADS);
    // Sisi Depan Atap Sayap Utama
    glNormal3f(0.0f, 0.6f, 0.8f); glColor3f(rAtap - 0.05f, gAtap - 0.05f, bAtap - 0.05f);
    glVertex3f(-4.8f, 1.9f, -2.3f); glVertex3f(4.8f, 1.9f, -2.3f);
    glVertex3f(4.8f,  3.1f, -3.0f); glVertex3f(-4.8f, 3.1f, -3.0f);
    
    // Sisi Belakang Atap Sayap Utama
    glNormal3f(0.0f, 0.6f, -0.8f);
    glVertex3f(-4.8f, 3.1f, -3.0f); glVertex3f(4.8f, 3.1f, -3.0f);
    glVertex3f(4.8f,  1.9f, -3.7f); glVertex3f(-4.8f, 1.9f, -3.7f);
    glEnd();
    
    // Penutup Segitiga Samping Atap
    glBegin(GL_TRIANGLES);
    glNormal3f(-1.0f, 0.0f, 0.0f);
    glVertex3f(-4.8f, 1.9f, -2.3f); glVertex3f(-4.8f, 3.1f, -3.0f); glVertex3f(-4.8f, 1.9f, -3.7f);
    glNormal3f(1.0f, 0.0f, 0.0f);
    glVertex3f(4.8f, 1.9f, -2.3f);  glVertex3f(4.8f, 1.9f, -3.7f);  glVertex3f(4.8f, 3.1f, -3.0f);
    glEnd();
}

void gambarGazeboKiri() {
    float rKayu = 0.35f, gKayu = 0.18f, bKayu = 0.08f;
    
    // 4 TIANG GAZEBO (Disesuaikan memanjang ke depan-belakang pada sumbu Z agar membentuk letter L dengan rumah)
    gambarBalok(-4.8f, -4.6f, -0.5f, 1.2f, -1.5f, -1.3f, rKayu, gKayu, bKayu); // Tiang Belakang Kiri
    gambarBalok(-3.2f, -3.0f, -0.5f, 1.2f, -1.5f, -1.3f, rKayu, gKayu, bKayu); // Tiang Belakang Kanan
    gambarBalok(-4.8f, -4.6f, -0.5f, 1.2f,  1.3f,  1.5f, rKayu, gKayu, bKayu); // Tiang Depan Kiri
    gambarBalok(-3.2f, -3.0f, -0.5f, 1.2f,  1.3f,  1.5f, rKayu, gKayu, bKayu); // Tiang Depan Kanan

    // ATAP GAZEBO (Limas Segiempat disesuaikan menutupi formasi tiang yang memanjang)
    glBegin(GL_TRIANGLES);
    glColor3f(0.45f, 0.22f, 0.12f);
    // Depan
    glNormal3f(0.0f, 0.5f, 0.8f);
    glVertex3f(-5.0f, 1.2f, 1.7f); glVertex3f(-2.8f, 1.2f, 1.7f); glVertex3f(-3.9f, 1.9f, 0.0f);
    // Kanan
    glNormal3f(0.8f, 0.5f, 0.0f);
    glVertex3f(-2.8f, 1.2f, 1.7f); glVertex3f(-2.8f, 1.2f, -1.7f); glVertex3f(-3.9f, 1.9f, 0.0f);
    // Belakang
    glNormal3f(0.0f, 0.5f, -0.8f);
    glVertex3f(-2.8f, 1.2f, -1.7f); glVertex3f(-5.0f, 1.2f, -1.7f); glVertex3f(-3.9f, 1.9f, 0.0f);
    // Kiri
    glNormal3f(-0.8f, 0.5f, 0.0f);
    glVertex3f(-5.0f, 1.2f, -1.7f); glVertex3f(-5.0f, 1.2f, 1.7f); glVertex3f(-3.9f, 1.9f, 0.0f);
    glEnd();
}

void gambarCagarBudayaDepan() {
    // Pondasi Bulat/Kotak Putih di Depan
    gambarBalok(-0.6f, 0.6f, -0.5f, -0.2f, 2.0f, 3.2f, 0.85f, 0.85f, 0.85f);
    // Batu Cagar Budaya Purbakala (Yoni)
    gambarBalok(-0.4f, 0.4f, -0.2f,  0.2f, 2.2f, 3.0f, 0.45f, 0.45f, 0.45f);
    gambarBalok(-0.2f, 0.2f,  0.2f,  0.4f, 2.4f, 2.8f, 0.50f, 0.50f, 0.50f);
}

// --- LOGIKA KONTROL KEYBOARD & MOUSE INTERAKTIF ---

void processInput(GLFWwindow *window) {
    if (glfwGetKey(window, GLFW_KEY_X) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }

    float cameraSpeed = 3.5f * deltaTime; 
    
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) { 
        cameraX += cameraSpeed * cameraFrontX; 
        cameraY += cameraSpeed * cameraFrontY; 
        cameraZ += cameraSpeed * cameraFrontZ; 
    }
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) { 
        cameraX -= cameraSpeed * cameraFrontX; 
        cameraY -= cameraSpeed * cameraFrontY; 
        cameraZ -= cameraSpeed * cameraFrontZ; 
    }
    
    float rightX = cameraFrontY * cameraUpZ - cameraFrontZ * cameraUpY; 
    float rightY = cameraFrontZ * cameraUpX - cameraFrontX * cameraUpZ; 
    float rightZ = cameraFrontX * cameraUpY - cameraFrontY * cameraUpX;
    float len = std::sqrt(rightX*rightX + rightY*rightY + rightZ*rightZ); 
    if(len > 0) { rightX /= len; rightY /= len; rightZ /= len; }
    
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) { 
        cameraX -= rightX * cameraSpeed; 
        cameraY -= rightY * cameraSpeed; 
        cameraZ -= rightZ * cameraSpeed; 
    }
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) { 
        cameraX += rightX * cameraSpeed; 
        cameraY += rightY * cameraSpeed; 
        cameraZ += rightZ * cameraSpeed; 
    }
}

void mouse_callback(GLFWwindow* window, double xposIn, double yposIn) {
    float xpos = static_cast<float>(xposIn); float ypos = static_cast<float>(yposIn);
    if (firstMouse) { lastX = xpos; lastY = ypos; firstMouse = false; }
    
    float xoffset = xpos - lastX; float yoffset = lastY - ypos; 
    lastX = xpos; lastY = ypos;
    
    float sensitivity = 0.1f; 
    xoffset *= sensitivity; yoffset *= sensitivity; 
    yaw += xoffset; pitch += yoffset;
    
    if (pitch > 89.0f) pitch = 89.0f; 
    if (pitch < -89.0f) pitch = -89.0f;
    
    float yawRad = yaw * M_PI / 180.0f; float pitchRad = pitch * M_PI / 180.0f;
    cameraFrontX = std::cos(yawRad) * std::cos(pitchRad); 
    cameraFrontY = std::sin(pitchRad); 
    cameraFrontZ = std::sin(yawRad) * std::cos(pitchRad);
    
    float len = std::sqrt(cameraFrontX*cameraFrontX + cameraFrontY*cameraFrontY + cameraFrontZ*cameraFrontZ); 
    if(len > 0) { cameraFrontX /= len; cameraFrontY /= len; cameraFrontZ /= len; }
}

int main() {
    if (!glfwInit()) return -1;
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Simulasi 3D Realistis - Museum Salatiga", NULL, NULL);
    if (!window) { glfwTerminate(); return -1; }
    
    glfwMakeContextCurrent(window);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED); 
    glfwSetCursorPosCallback(window, mouse_callback);
    
    // KONFIGURASI PENCAHAYAAN (LIGHTING EFFECT) & DEPTH TEST
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);       
    glEnable(GL_LIGHT0);         
    glEnable(GL_COLOR_MATERIAL); 
    glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    while (!glfwWindowShouldClose(window)) {
        float currentFrame = static_cast<float>(glfwGetTime()); 
        deltaTime = currentFrame - lastFrame; lastFrame = currentFrame;
        
        processInput(window);

        glClearColor(0.55f, 0.75f, 0.9f, 1.0f); // Warna Langit Biru Cerah
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        GLfloat light_position[] = { 6.0f, 12.0f, 8.0f, 1.0f };
        GLfloat light_ambient[]  = { 0.45f, 0.45f, 0.45f, 1.0f }; 
        GLfloat light_diffuse[]  = { 0.85f, 0.85f, 0.85f, 1.0f }; 
        glLightfv(GL_LIGHT0, GL_POSITION, light_position);
        glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
        glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);

        // MATRIKS PROYEKSI PERSPEKTIF 3D
        glMatrixMode(GL_PROJECTION); glLoadIdentity();
        double fovRad = 45.0 * M_PI / 180.0; double f = 1.0 / std::tan(fovRad / 2.0);
        double aspect = (double)SCR_WIDTH / (double)SCR_HEIGHT;
        double matrixProj[] = { f/aspect, 0, 0, 0, 0, f, 0, 0, 0, 0, 100.1/(0.1-100.0), -1, 0, 0, (2*100.0*0.1)/(0.1-100.0), 0 };
        glMultMatrixd(matrixProj);

        // MATRIKS VIEW (Kamera)
        glMatrixMode(GL_MODELVIEW); glLoadIdentity();
        float fX = cameraFrontX, fY = cameraFrontY, fZ = cameraFrontZ;
        float rX = fY * cameraUpZ - fZ * cameraUpY; float rY = fZ * cameraUpX - fX * cameraUpZ; float rZ = fX * cameraUpY - fY * cameraUpX;
        float lenR = std::sqrt(rX*rX + rY*rY + rZ*rZ); if(lenR > 0) { rX /= lenR; rY /= lenR; rZ /= lenR; }
        float uX = rY * fZ - rZ * fY; float uY = rZ * fX - rX * fZ; float uZ = rX * fY - rY * fX;
        double matrixView[] = { rX, uX, -fX, 0, rY, uY, -fY, 0, rZ, uZ, -fZ, 0, -(rX*cameraX+rY*cameraY+rZ*cameraZ), -(uX*cameraX+uY*cameraY+uZ*cameraZ), (fX*cameraX+fY*cameraY+fZ*cameraZ), 1 };
        glMultMatrixd(matrixView);

        // --- MERENDER SEMUA OBJEK KE LAYAR ---
        gambarHalamanDanPaving();
        gambarGedungMuseum();
        gambarGazeboKiri();
        gambarCagarBudayaDepan();

        glfwSwapBuffers(window); 
        glfwPollEvents();
    }
    glfwTerminate(); 
    return 0;
}