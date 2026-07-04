#include <GLFW/glfw3.h>
#include <iostream>

// Fungsi untuk membaca input keyboard
void processInput(GLFWwindow *window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

int main() {
    // 1. Inisialisasi GLFW
    if (!glfwInit()) {
        std::cout << "Gagal menginisialisasi GLFW" << std::endl;
        return -1;
    }

    // 2. Buat Jendela Aplikasi (Lebar: 800, Tinggi: 600)
    GLFWwindow* window = glfwCreateWindow(800, 600, "Proyek Grafkom - Kamera 360", NULL, NULL);
    if (!window) {
        std::cout << "Gagal membuat jendela GLFW" << std::endl;
        glfwTerminate();
        return -1;
    }

    // 3. Aktifkan Context Jendela
    glfwMakeContextCurrent(window);

    // 4. Loop Utama Aplikasi (Akan terus berjalan sampai jendela ditutup)
    while (!glfwWindowShouldClose(window)) {
        // Cek Input
        processInput(window);

        // Mewarnai latar belakang layar (Warna Biru Kehijauan / Teal)
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // Tukar buffer layar dan cek event (seperti gerakan mouse/keyboard)
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // 5. Bersihkan memori saat aplikasi ditutup
    glfwTerminate();
    return 0;
}
