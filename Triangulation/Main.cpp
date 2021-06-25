#include <windows.h>
#include <Shader.h>
#include <Buffer.h>
#include <iostream>

BOOL CALLBACK EnumWindowsProc(HWND hwnd, LPARAM lParam) {
    HWND p = FindWindowEx(hwnd, NULL, reinterpret_cast<LPCSTR>("SHELLDLL_DefView"), NULL);
    HWND *ret = (HWND *) lParam;

    if (p) {
// Gets the WorkerW Window after the current one.
        *ret = FindWindowEx(NULL, hwnd, reinterpret_cast<LPCSTR>("WorkerW"), NULL);
    }

    return true;
}

HWND GetWallpaperWindow() {
    // Fetch the Progman window
    HWND progman = FindWindow(reinterpret_cast<LPCSTR>("ProgMan"), NULL);
    // Send 0x052C to Progman. This message directs Progman to spawn a
    // WorkerW behind the desktop icons. If it is already there, nothing
    // happens.
    SendMessageTimeout(progman, 0x052C, 0, 0, SMTO_NORMAL, 1000, nullptr);
    // We enumerate all Windows, until we find one, that has the SHELLDLL_DefView
    // as a child.
    // If we found that window, we take its next sibling and assign it to workerw.
    HWND wallpaper_hwnd = nullptr;
    EnumWindows(EnumWindowsProc, (LPARAM) &wallpaper_hwnd);
    return wallpaper_hwnd;
}

int main() {
    // Get the HWND for the desktop background window
    HWND window = GetWallpaperWindow();
    HDC hdc = GetDC(window);
    PIXELFORMATDESCRIPTOR pfd = {
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
        wglMakeCurrent(hdc, hglrc);
        // OpenGL 1.1 is supported by default without needing to explicitly load functions
        if (!gladLoadGL()) {
            std::cout << "Failed to init GLAD\n";
        }
        Shader shader("../Assets/Shader.glsl");
        shader.bind();
        std::cout << shader.getErrorMessage();
        glLineWidth(1);
        glEnable(GL_LINE_SMOOTH);
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        while (true) {
            glClear(GL_COLOR_BUFFER_BIT);
            glClearColor(0.5, 1.0, 0.5, 1.0);
//           shader.setUniform2fv("coords", MAX_POINTS * sizeof(float) * 2, reinterpret_cast<const float *>(coords));
            glDrawArrays(GL_POINTS, 0, 1);
            SwapBuffers(hdc);
        }
        wglMakeCurrent(NULL, NULL);
        wglDeleteContext(hglrc);
        ReleaseDC(window, hdc);
    } else {
        std::cout << "Failed to create GL Context\n";
    }
}