#include <windows.h>
#include <Shader.h>
#include <Buffer.h>
#include <iostream>
#include <cmath>

BOOL CALLBACK EnumWindowsProc(HWND hwnd, LPARAM lParam) {
    HWND p = FindWindowEx(hwnd, NULL, reinterpret_cast<LPCSTR>("SHELLDLL_DefView"), NULL);
    HWND *ret = (HWND *) lParam;
    if (p)
        *ret = FindWindowEx(NULL, hwnd, reinterpret_cast<LPCSTR>("WorkerW"), NULL);
    return true;
}

HWND GetWallpaperWindow() {
    HWND progman = FindWindow(reinterpret_cast<LPCSTR>("ProgMan"), NULL);
    SendMessageTimeout(progman, 0x052C, 0, 0, SMTO_NORMAL, 1000, nullptr);
    HWND wallpaper_hwnd = nullptr;
    EnumWindows(EnumWindowsProc, (LPARAM) &wallpaper_hwnd);
    return wallpaper_hwnd;
}

typedef const char* (WINAPI* PFNWGLGETEXTENSIONSSTRINGEXTPROC) (void);
typedef BOOL(WINAPI* PFNWGLSWAPINTERVALEXTPROC) (int interval);

int main() {
    HWND window = GetWallpaperWindow();
    HDC hdc = GetDC(window);
    PIXELFORMATDESCRIPTOR pfd = {
                    sizeof(PIXELFORMATDESCRIPTOR),
                    1,
                    PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER,    // Flags
                    PFD_TYPE_RGBA,
                    24,
                    0, 0, 0, 0, 0, 0,
                    0,
                    0,
                    0,
                    0, 0, 0, 0,
                    0,
                    0,
                    0,
                    PFD_MAIN_PLANE,
                    0,
                    0, 0, 0
            };
    int format = ChoosePixelFormat(hdc, &pfd);
    SetPixelFormat(hdc, format, &pfd);
    if (HGLRC hglrc = wglCreateContext(hdc)) {
        wglMakeCurrent(hdc, hglrc);
        if (!gladLoadGL()) {
            std::cout << "Failed to init GLAD\n";
        }
        if (strstr(((PFNWGLGETEXTENSIONSSTRINGEXTPROC) wglGetProcAddress("wglGetExtensionsStringEXT"))(), "WGL_EXT_swap_control") != NULL)
            ((PFNWGLSWAPINTERVALEXTPROC) wglGetProcAddress("wglSwapIntervalEXT"))(1);
        Shader shader("../Assets/Shader.glsl");
        shader.bind();
        std::cout << shader.getErrorMessage();
        glLineWidth(1);
        glPointSize(10);
        glEnable(GL_LINE_SMOOTH);
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        POINT mouse;
        //glViewport(0, 0, 1920 * 2, 1080);
        const int POINTS = 100;
        float coords[POINTS * 2] = {};
        float coordsDir[POINTS * 2] = {};
        for(int i = 0; i < POINTS * 2; i += 2){
            coords[i] = (float(rand()) / RAND_MAX * 2) - 1;
            coords[i + 1] = (float(rand()) / RAND_MAX * 2)  - 1;
            coordsDir[i] = (float(rand()) / RAND_MAX * 2)  - 1;
            coordsDir[i + 1] = (float(rand()) / RAND_MAX * 2)  - 1;
        }
        shader.setUniform1f("points", POINTS);
        while (!(GetKeyState(VK_ESCAPE) & 0x8000)) {
            for(int i = 0; i < POINTS * 2; i += 2){
                coords[i] += coordsDir[i] * 0.005;
                coords[i + 1] += coordsDir[i + 1] * 0.005;
            }
            GetCursorPos(&mouse);
            glClear(GL_COLOR_BUFFER_BIT);
            glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
            shader.setUniform2f("mouse", mouse.x, mouse.y);
            shader.setUniform2fv("coords", POINTS * sizeof(float) * 2, reinterpret_cast<const float *>(coords));
            glDrawArrays(GL_POINTS, 0, 1);
            Sleep(1);
            SwapBuffers(hdc);
        }
        wglMakeCurrent(nullptr, nullptr);
        wglDeleteContext(hglrc);
        ReleaseDC(window, hdc);
    } else {
        std::cout << "Failed to create GL Context\n";
    }
}