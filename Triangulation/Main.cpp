#include "Window/Window.h"
#include <Shader.h>
#include <Buffer.h>
#include <iostream>
#include <windows.h>

static void frameBufferSize(GLFWwindow *window, int width, int height) {
    glViewport(0, 0, width, height);
}

static void mousePositionCallback(GLFWwindow *window, double x, double y) {
}

static void mouseButtonCallback(GLFWwindow *window, int button, int action, int mods) {
}

BOOL CALLBACK EnumWindowsProc(HWND hwnd, LPARAM lParam) {
    HWND p = FindWindowEx(hwnd, NULL, reinterpret_cast<LPCSTR>(L"SHELLDLL_DefView"), NULL);
    HWND *ret = (HWND *) lParam;

    if (p) {
// Gets the WorkerW Window after the current one.
        *ret = FindWindowEx(NULL, hwnd, reinterpret_cast<LPCSTR>(L"WorkerW"), NULL);
    }

    return true;
}

HWND GetWallpaperWindow() {
    // Fetch the Progman window
    HWND progman = FindWindow(reinterpret_cast<LPCSTR>(L"ProgMan"), NULL);
    // Send 0x052C to Progman. This message directs Progman to spawn a
    // WorkerW behind the desktop icons. If it is already there, nothing
    // happens.
    SendMessageTimeout(progman, 0x052C, 0, 0, SMTO_NORMAL, 1000, nullptr);
    // We enumerate all Windows, until we find one, that has the SHELLDLL_DefView
    // as a child.
    // If we found that window, we take its next sibling and assign it to workerw.
    HWND wallpaper_hwnd = nullptr;
    EnumWindows(EnumWindowsProc, (LPARAM) &wallpaper_hwnd);
    // Return the handle you're looking for.
    return wallpaper_hwnd;
}

// You can also use `int main()`
int APIENTRY WinMain(HINSTANCE hCurrentInst, HINSTANCE hPreviousInst, LPSTR lpszCmdLine, int nCmdShow) {
    // Get the HWND for the desktop background window
    HWND window = GetWallpaperWindow();

    // Get the drawing context
    HDC hdc = GetDC(window);

    // The pixel format to use for OpenGL
    PIXELFORMATDESCRIPTOR pfd =
            {
                    sizeof(PIXELFORMATDESCRIPTOR),
                    1,
                    PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER,    // Flags
                    PFD_TYPE_RGBA,        // The kind of framebuffer. RGBA or palette.
                    32,                   // Colordepth of the framebuffer.
                    0, 0, 0, 0, 0, 0,
                    0,
                    0,
                    0,
                    0, 0, 0, 0,
                    24,                   // Number of bits for the depthbuffer
                    8,                    // Number of bits for the stencilbuffer
                    0,                    // Number of Aux buffers in the framebuffer.
                    PFD_MAIN_PLANE,
                    0,
                    0, 0, 0
            };

    // Try setting the pixel format, this will be =0 if this fails
    int format = ChoosePixelFormat(hdc, &pfd);

    SetPixelFormat(hdc, format, &pfd);

    // Create the OpenGL context
    if (HGLRC hglrc = wglCreateContext(hdc)) {
        // Make context current for this thread
        wglMakeCurrent(hdc, hglrc);

        // Load OpenGL fuction pointers
        // OpenGL 1.1 is supported by default without needing to explicitly load functions

        // Load with glad2
        if (!gladLoadGL()) {
            std::cout << "Failed to init GLAD\n";
            return;
            // Loading OpenGL functions failed
        }
        hader shader("../Assets/Shader.glsl");
        shader.bind();
        std::cout << shader.getErrorMessage();
        glLineWidth(1);
        glEnable(GL_LINE_SMOOTH);
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        #define MAX_POINTS 1
        #define POINT_SPEED 0.0005

        struct Point {
            float x = 0, y = 0, dirX = 0, dirY = 0;
        };

        Point coords[MAX_POINTS] = {};

        for (int i = 0; i < MAX_POINTS; i++) {
            coords[i].dirX = float(rand() - RAND_MAX / 2) / RAND_MAX;
            coords[i].dirY = float(rand() - RAND_MAX / 2) / RAND_MAX;
        }

        while (true) {
            // Perform rendering

            // Swap the front and back buffers
            SwapBuffers(hdc);
        }

        // After the loop ends, unset the context and delete it
        wglMakeCurrent(NULL, NULL);
        wglDeleteContext(hglrc);
        ReleaseDC(window, hdc);
    } else {
        std::cout << "Failed to create GL Context\n";
    }
}

int main() {

    while (window.windowIsAlive()) {
        for (int i = 0; i < MAX_POINTS; i++) {
            auto coord = coords[i];
            coords[i].x += coord.dirX * POINT_SPEED;
            coords[i].y += coord.dirY * POINT_SPEED;
        }
        glClear(GL_COLOR_BUFFER_BIT);
        shader.setUniform1f("time", glfwGetTime());
        shader.setUniform2fv("coords", MAX_POINTS * sizeof(float) * 2, reinterpret_cast<const float *>(coords));
        glDrawArrays(GL_POINTS, 0, 1);
        if (glfwGetKey(window.getWindow(), GLFW_KEY_ESCAPE) == GLFW_PRESS)
            window.destroyWindow();
        window.updateWindow();
    }
}