#include <GLFW/glfw3.h>
#include <iostream>
#include <cmath>

const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

float cameraX = 0.0f, cameraY = 0.5f, cameraZ = 5.0f; 
float cameraFrontX = 0.0f, cameraFrontY = 0.0f, cameraFrontZ = -1.0f; 
float cameraUpX = 0.0f, cameraUpY = 1.0f, cameraUpZ = 0.0f;    

bool firstMouse = true;
float yaw   = -90.0f; 
float pitch =  0.0f;  
float lastX =  800.0f / 2.0;
float lastY =  600.0f / 2.0;
float deltaTime = 0.0f; 
float lastFrame = 0.0f;

void processInput(GLFWwindow *window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    float cameraSpeed = 2.5f * deltaTime; 
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
        cameraX += cameraSpeed * cameraFrontX; cameraY += cameraSpeed * cameraFrontY; cameraZ += cameraSpeed * cameraFrontZ;
    }
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
        cameraX -= cameraSpeed * cameraFrontX; cameraY -= cameraSpeed * cameraFrontY; cameraZ -= cameraSpeed * cameraFrontZ;
    }
    float rightX = cameraFrontY * cameraUpZ - cameraFrontZ * cameraUpY;
    float rightY = cameraFrontZ * cameraUpX - cameraFrontX * cameraUpZ;
    float rightZ = cameraFrontX * cameraUpY - cameraFrontY * cameraUpX;
    float len = std::sqrt(rightX*rightX + rightY*rightY + rightZ*rightZ);
    if(len > 0) { rightX /= len; rightY /= len; rightZ /= len; }

    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
        cameraX -= rightX * cameraSpeed; cameraY -= rightY * cameraSpeed; cameraZ -= rightZ * cameraSpeed;
    }
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
        cameraX += rightX * cameraSpeed; cameraY += rightY * cameraSpeed; cameraZ += rightZ * cameraSpeed;
    }
}

void mouse_callback(GLFWwindow* window, double xposIn, double yposIn) {
    float xpos = static_cast<float>(xposIn);
    float ypos = static_cast<float>(yposIn);
    if (firstMouse) { lastX = xpos; lastY = ypos; firstMouse = false; }
    float xoffset = xpos - lastX; float yoffset = lastY - ypos; 
    lastX = xpos; lastY = ypos;
    float sensitivity = 0.1f; xoffset *= sensitivity; yoffset *= sensitivity;
    yaw += xoffset; pitch += yoffset;
    if (pitch > 89.0f) pitch = 89.0f; if (pitch < -89.0f) pitch = -89.0f;
    float yawRad = yaw * M_PI / 180.0f; float pitchRad = pitch * M_PI / 180.0f;
    cameraFrontX = std::cos(yawRad) * std::cos(pitchRad);
    cameraFrontY = std::sin(pitchRad);
    cameraFrontZ = std::sin(yawRad) * std::cos(pitchRad);
    float len = std::sqrt(cameraFrontX*cameraFrontX + cameraFrontY*cameraFrontY + cameraFrontZ*cameraFrontZ);
    if(len > 0) { cameraFrontX /= len; cameraFrontY /= len; cameraFrontZ /= len; }
}

int main() {
    if (!glfwInit()) return -1;
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Simulasi 3D - Rumah dan Pohon Sederhana", NULL, NULL);
    if (!window) { glfwTerminate(); return -1; }
    glfwMakeContextCurrent(window);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glfwSetCursorPosCallback(window, mouse_callback);
    glEnable(GL_DEPTH_TEST);

    while (!glfwWindowShouldClose(window)) {
        float currentFrame = static_cast<float>(glfwGetTime());
        deltaTime = currentFrame - lastFrame; lastFrame = currentFrame;
        processInput(window);

        glClearColor(0.5f, 0.8f, 0.9f, 1.0f); // Warna langit biru
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

        // 1. LANTAI TANAH (Hijau Rumput)
        glBegin(GL_QUADS);
        glColor3f(0.2f, 0.6f, 0.2f);
        glVertex3f(-15.0f, -0.5f, -15.0f); glVertex3f(15.0f, -0.5f, -15.0f); glVertex3f(15.0f, -0.5f, 15.0f); glVertex3f(-15.0f, -0.5f, 15.0f);
        glEnd();

        // 2. BADAN RUMAH (Kotak Krem / Oranye Muda)
        glBegin(GL_QUADS);
        glColor3f(0.9f, 0.7f, 0.5f);
        glVertex3f(-0.8f, -0.5f, -2.0f); glVertex3f(0.8f, -0.5f, -2.0f); glVertex3f(0.8f, 0.5f, -2.0f); glVertex3f(-0.8f, 0.5f, -2.0f);
        glEnd();

        // 3. ATAP RUMAH (Segitiga Merah)
        glBegin(GL_TRIANGLES);
        glColor3f(0.8f, 0.2f, 0.1f);
        glVertex3f(-1.0f, 0.5f, -2.0f); glVertex3f(1.0f, 0.5f, -2.0f); glVertex3f(0.0f, 1.2f, -2.0f);
        glEnd();

        // 4. PINTU RUMAH (Kotak Cokelat)
        glBegin(GL_QUADS);
        glColor3f(0.4f, 0.2f, 0.0f);
        glVertex3f(-0.2f, -0.5f, -1.99f); glVertex3f(0.2f, -0.5f, -1.99f); glVertex3f(0.2f, 0.1f, -1.99f); glVertex3f(-0.2f, 0.1f, -1.99f);
        glEnd();

        // 5. POHON - BATANG (Cokelat)
        glBegin(GL_QUADS);
        glColor3f(0.5f, 0.3f, 0.1f);
        glVertex3f(1.8f, -0.5f, -2.5f); glVertex3f(2.0f, -0.5f, -2.5f); glVertex3f(2.0f, 0.3f, -2.5f); glVertex3f(1.8f, 0.3f, -2.5f);
        glEnd();

        // 6. POHON - DAUN (Segitiga Hijau Tua)
        glBegin(GL_TRIANGLES);
        glColor3f(0.1f, 0.4f, 0.1f);
        glVertex3f(1.4f, 0.3f, -2.5f); glVertex3f(2.4f, 0.3f, -2.5f); glVertex3f(1.9f, 1.3f, -2.5f);
        glEnd();

        glfwSwapBuffers(window); glfwPollEvents();
    }
    glfwTerminate(); return 0;
}
