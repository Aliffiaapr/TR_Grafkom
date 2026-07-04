#include <GLFW/glfw3.h>
#include <iostream>
#include <cmath>

const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

// Posisi kamera awal diatur agak mundur agar langsung melihat halaman museum
float cameraX = 0.0f, cameraY = 1.0f, cameraZ = 8.0f; 
float cameraFrontX = 0.0f, cameraFrontY = 0.0f, cameraFrontZ = -1.0f; 
float cameraUpX = 0.0f, cameraUpY = 1.0f, cameraUpZ = 0.0f;    

bool firstMouse = true;
float yaw = -90.0f; float pitch = 0.0f;  
float lastX = 800.0f / 2.0; float lastY = 600.0f / 2.0;
float deltaTime = 0.0f; float lastFrame = 0.0f;

// --- AREA MODULAR PROYEK MUSEUM SALATIGA ---

void gambarHalamanDanPaving() {
    // 1. Rumput Hijau Utama
    glBegin(GL_QUADS);
    glColor3f(0.3f, 0.6f, 0.3f);
    glVertex3f(-20.0f, -0.5f, -20.0f); glVertex3f(20.0f, -0.5f, -20.0f);
    glVertex3f(20.0f, -0.5f, 20.0f); glVertex3f(-20.0f, -0.5f, 20.0f);
    glEnd();

    // 2. Jalan Paving Blok Kiri (Abu-abu kecokelatan)
    glBegin(GL_QUADS);
    glColor3f(0.5f, 0.45f, 0.4f);
    glVertex3f(-5.0f, -0.49f, -10.0f); glVertex3f(-1.5f, -0.49f, -10.0f);
    glVertex3f(-1.5f, -0.49f, 10.0f);  glVertex3f(-5.0f, -0.49f, 10.0f);
    glEnd();
}

void gambarGedungMuseum() {
    // 1. Dinding Utama Gedung (Oranye Terang)
    glBegin(GL_QUADS);
    glColor3f(0.95f, 0.35f, 0.1f); 
    glVertex3f(-2.5f, -0.5f, -3.0f); glVertex3f(2.5f, -0.5f, -3.0f);
    glVertex3f(2.5f, 2.0f, -3.0f);  glVertex3f(-2.5f, 2.0f, -3.0f);
    glEnd();

    // 2. Tiang Penyangga Kiri & Kanan Depan (Putih)
    glColor3f(0.9f, 0.9f, 0.9f);
    glBegin(GL_QUADS);
    glVertex3f(-2.5f, -0.5f, -2.8f); glVertex3f(-2.1f, -0.5f, -2.8f); glVertex3f(-2.1f, 2.0f, -2.8f); glVertex3f(-2.5f, 2.0f, -2.8f);
    glVertex3f(2.1f, -0.5f, -2.8f);  glVertex3f(2.5f, -0.5f, -2.8f);  glVertex3f(2.5f, 2.0f, -2.8f);  glVertex3f(2.1f, 2.0f, -2.8f);
    glEnd();

    // 3. Atap Segitiga Depan (Genteng Cokelat)
    glBegin(GL_TRIANGLES);
    glColor3f(0.6f, 0.3f, 0.2f);
    glVertex3f(-3.0f, 2.0f, -2.7f); glVertex3f(3.0f, 2.0f, -2.7f); glVertex3f(0.0f, 3.0f, -2.7f);
    glEnd();

    // 4. Papan Nama Biru "MUSEUM SALATIGA"
    glBegin(GL_QUADS);
    glColor3f(0.0f, 0.2f, 0.6f);
    glVertex3f(-1.2f, 1.3f, -2.75f); glVertex3f(1.2f, 1.3f, -2.75f);
    glVertex3f(1.2f, 1.8f, -2.75f);  glVertex3f(-1.2f, 1.8f, -2.75f);
    glEnd();

    // 5. Pintu Kaca Utama (Hitam Transparan / Abu-abu gelap)
    glBegin(GL_QUADS);
    glColor3f(0.2f, 0.25f, 0.25f);
    glVertex3f(-0.8f, -0.5f, -2.9f); glVertex3f(0.8f, -0.5f, -2.9f);
    glVertex3f(0.8f, 1.0f, -2.9f);  glVertex3f(-0.8f, 1.0f, -2.9f);
    glEnd();
}

void gambarGazeboKiri() {
    // Tiang-tiang Kayu Gazebo (Cokelat Tua)
    glColor3f(0.4f, 0.2f, 0.1f);
    glLineWidth(5.0f);
    glBegin(GL_LINES);
    glVertex3f(-4.5f, -0.5f, -1.0f); glVertex3f(-4.5f, 1.2f, -1.0f);
    glVertex3f(-2.5f, -0.5f, -1.0f); glVertex3f(-2.5f, 1.2f, -1.0f);
    glEnd();

    // Atap Gazebo (Limasan Cokelat)
    glBegin(GL_TRIANGLES);
    glColor3f(0.5f, 0.25f, 0.15f);
    glVertex3f(-4.8f, 1.2f, -1.0f); glVertex3f(-2.2f, 1.2f, -1.0f); glVertex3f(-3.5f, 1.8f, -1.0f);
    glEnd();
}

void gambarCagarBudayaDepan() {
    // Batu Lingga/Yoni purbakala di tengah halaman depan (Abu-abu batu)
    glColor3f(0.5f, 0.5f, 0.5f);
    // Lapisan bawah (Pondasi lingkaran/kotak putih)
    glBegin(GL_QUADS);
    glColor3f(0.85f, 0.85f, 0.85f);
    glVertex3f(-0.5f, -0.5f, 2.0f); glVertex3f(0.5f, -0.5f, 2.0f);
    glVertex3f(0.5f, -0.2f, 2.0f);  glVertex3f(-0.5f, -0.2f, 2.0f);
    glEnd();
    // Batu Cagar Budayanya
    glBegin(GL_QUADS);
    glColor3f(0.4f, 0.4f, 0.4f);
    glVertex3f(-0.3f, -0.2f, 2.01f); glVertex3f(0.3f, -0.2f, 2.01f);
    glVertex3f(0.2f, 0.2f, 2.01f);   glVertex3f(-0.2f, 0.2f, 2.01f);
    glEnd();
}

void processInput(GLFWwindow *window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) glfwSetWindowShouldClose(window, true);
    float cameraSpeed = 4.0f * deltaTime; 
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) { cameraX += cameraSpeed * cameraFrontX; cameraY += cameraSpeed * cameraFrontY; cameraZ += cameraSpeed * cameraFrontZ; }
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) { cameraX -= cameraSpeed * cameraFrontX; cameraY -= cameraSpeed * cameraFrontY; cameraZ -= cameraSpeed * cameraFrontZ; }
    float rightX = cameraFrontY * cameraUpZ - cameraFrontZ * cameraUpY; float rightY = cameraFrontZ * cameraUpX - cameraFrontX * cameraUpZ; float rightZ = cameraFrontX * cameraUpY - cameraFrontY * cameraUpX;
    float len = std::sqrt(rightX*rightX + rightY*rightY + rightZ*rightZ); if(len > 0) { rightX /= len; rightY /= len; rightZ /= len; }
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) { cameraX -= rightX * cameraSpeed; cameraY -= rightY * cameraSpeed; cameraZ -= rightZ * cameraSpeed; }
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) { cameraX += rightX * cameraSpeed; cameraY += rightY * cameraSpeed; cameraZ += rightZ * cameraSpeed; }
}

void mouse_callback(GLFWwindow* window, double xposIn, double yposIn) {
    float xpos = static_cast<float>(xposIn); float ypos = static_cast<float>(yposIn);
    if (firstMouse) { lastX = xpos; lastY = ypos; firstMouse = false; }
    float xoffset = xpos - lastX; float yoffset = lastY - ypos; lastX = xpos; lastY = ypos;
    float sensitivity = 0.1f; xoffset *= sensitivity; yoffset *= sensitivity; yaw += xoffset; pitch += yoffset;
    if (pitch > 89.0f) pitch = 89.0f; if (pitch < -89.0f) pitch = -89.0f;
    float yawRad = yaw * M_PI / 180.0f; float pitchRad = pitch * M_PI / 180.0f;
    cameraFrontX = std::cos(yawRad) * std::cos(pitchRad); cameraFrontY = std::sin(pitchRad); cameraFrontZ = std::sin(yawRad) * std::cos(pitchRad);
    float len = std::sqrt(cameraFrontX*cameraFrontX + cameraFrontY*cameraFrontY + cameraFrontZ*cameraFrontZ); if(len > 0) { cameraFrontX /= len; cameraFrontY /= len; cameraFrontZ /= len; }
}

int main() {
    if (!glfwInit()) return -1;
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Simulasi 3D - Museum Salatiga", NULL, NULL);
    if (!window) { glfwTerminate(); return -1; }
    glfwMakeContextCurrent(window);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glfwSetCursorPosCallback(window, mouse_callback);
    glEnable(GL_DEPTH_TEST);

    while (!glfwWindowShouldClose(window)) {
        float currentFrame = static_cast<float>(glfwGetTime()); deltaTime = currentFrame - lastFrame; lastFrame = currentFrame;
        processInput(window);

        glClearColor(0.5f, 0.8f, 0.9f, 1.0f); // Langit Biru Cerah
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glMatrixMode(GL_PROJECTION); glLoadIdentity();
        double fovRad = 45.0 * M_PI / 180.0; double f = 1.0 / std::tan(fovRad / 2.0);
        double aspect = (double)SCR_WIDTH / (double)SCR_HEIGHT;
        double matrixProj[] = { f/aspect, 0, 0, 0, 0, f, 0, 0, 0, 0, 100.1/(0.1-100.0), -1, 0, 0, (2*100.0*0.1)/(0.1-100.0), 0 };
        glMultMatrixd(matrixProj);

        glMatrixMode(GL_MODELVIEW); glLoadIdentity();
        float fX = cameraFrontX, fY = cameraFrontY, fZ = cameraFrontZ;
        float rX = fY * cameraUpZ - fZ * cameraUpY; float rY = fZ * cameraUpX - fX * cameraUpZ; float rZ = fX * cameraUpY - fY * cameraUpX;
        float lenR = std::sqrt(rX*rX + rY*rY + rZ*rZ); if(lenR > 0) { rX /= lenR; rY /= lenR; rZ /= lenR; }
        float uX = rY * fZ - rZ * fY; float uY = rZ * fX - rX * fZ; float uZ = rX * fY - rY * fX;
        double matrixView[] = { rX, uX, -fX, 0, rY, uY, -fY, 0, rZ, uZ, -fZ, 0, -(rX*cameraX+rY*cameraY+rZ*cameraZ), -(uX*cameraX+uY*cameraY+uZ*cameraZ), (fX*cameraX+fY*cameraY+fZ*cameraZ), 1 };
        glMultMatrixd(matrixView);

        // --- PANGGIL SEMUA OBJEK LINGKUNGAN MUSEUM ---
        gambarHalamanDanPaving();
        gambarGedungMuseum();
        gambarGazeboKiri();
        gambarCagarBudayaDepan();

        glfwSwapBuffers(window); glfwPollEvents();
    }
    glfwTerminate(); return 0;
}
