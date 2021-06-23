#pragma once

#include <Texture.h>
#include <GLFW/glfw3.h>
#include "WindowSettings.h"

#define FAILED_TO_LOAD_ICON_DATA -1
#define FAILED_TO_LOCATE_ICON_DATA -2
#define FAILED_TO_ALLOCATE_ICON_DATA -3
#define FAILED_TO_GET_TEXTURE_TYPE -4
#define FAILED_INIT_GLFW -5
#define FAILED_INIT_GLAD -6
#define FAILED_INIT_WINDOW -7

class Window{
public:
    explicit Window(WindowSettings* windowSettings);
    ~Window();
    void updateWindow();
    void destroyWindow();
    inline void setWindowIsAlive(bool windowShouldClose) { this->windowShouldClose = !windowShouldClose; }
    inline bool windowIsAlive() const { return !windowShouldClose; }
    inline GLFWwindow* getWindow(){ return window; }
    inline char* getGLVersion(){ return glVersion; }
    inline int getErrorCode() const{ return errorCode; }
    inline WindowSettings* getWindowSettings() { return windowSettings; };
    inline const GLFWvidmode* getMonitorInformation(){return vidmode;}
private:
    GLFWwindow* window;
    const GLFWvidmode *vidmode;
    WindowSettings* windowSettings;
    void initHints();
    void constructWindow();
    void setIcon();
    char* glVersion;
    bool windowShouldClose = false;
    int errorCode = 0;
};