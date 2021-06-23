#include "Window/Window.h"
#include <Shader.h>
#include <Buffer.h>
#include <iostream>

static void frameBufferSize(GLFWwindow *window, int width, int height) {
    glViewport(0, 0, width, height);
}

static void mousePositionCallback(GLFWwindow *window, double x, double y) {
}

static void mouseButtonCallback(GLFWwindow *window, int button, int action, int mods) {
}

int main() {
    auto windowSettings = new WindowSettings;
    windowSettings->setWidth(1600);
    windowSettings->setHeight(800);
    windowSettings->setFocused(true);
    windowSettings->setResizable(true);
    windowSettings->setSwapInterval(0);
    windowSettings->setDecorated(true);
    windowSettings->setWindowMode(WINDOW_MODE_NORMAL);
    windowSettings->setCentered(true);
    windowSettings->setTransparent(false);
    windowSettings->setShouldMultiSample(true);
    windowSettings->setSampleSize(2);

    Window window(windowSettings);

    glfwSetFramebufferSizeCallback(window.getWindow(), frameBufferSize);
    glfwSetCursorPosCallback(window.getWindow(), mousePositionCallback);
    glfwSetMouseButtonCallback(window.getWindow(), mouseButtonCallback);

    Shader shader("../Assets/Shader.glsl");
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

    for(int i = 0; i < MAX_POINTS; i++){
        coords[i].dirX = float(rand() - RAND_MAX / 2) / RAND_MAX;
        coords[i].dirY = float(rand() - RAND_MAX / 2) / RAND_MAX;
    }

    while(window.windowIsAlive()){
        for(int i = 0; i < MAX_POINTS; i++){
            auto coord = coords[i];
            coords[i].x += coord.dirX * POINT_SPEED;
            coords[i].y += coord.dirY * POINT_SPEED;
            if(coord.x < -1 || coord.x > 1.0)
                coords[i].dirX = -coord.dirX;
            if(coord.y < -1 || coord.y > 1.0)
                coords[i].dirY = -coord.dirY;
        }
        glClear(GL_COLOR_BUFFER_BIT);
        shader.setUniform1f("time", glfwGetTime());
        shader.setUniform2fv("coords", MAX_POINTS * sizeof(float) * 2, reinterpret_cast<const float *>(coords));
        glDrawArrays(GL_POINTS, 0, 1);
        if(glfwGetKey(window.getWindow(), GLFW_KEY_ESCAPE) == GLFW_PRESS)
            window.destroyWindow();
        window.updateWindow();
    }
}