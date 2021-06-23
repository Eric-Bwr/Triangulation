#include "Window/Window.h"
#include <Shader.h>
#include <Buffer.h>

static void frameBufferSize(GLFWwindow *window, int width, int height) {
    glViewport(0, 0, width, height);
}

static void mousePositionCallback(GLFWwindow *window, double x, double y) {
}

static void mouseButtonCallback(GLFWwindow *window, int button, int action, int mods) {
}

int main() {
    auto windowSettings = new WindowSettings;
    windowSettings->setWidth(1920);
    windowSettings->setHeight(1080);
    windowSettings->setFocused(false);
    windowSettings->setResizable(false);
    windowSettings->setSwapInterval(0);
    windowSettings->setDecorated(true);
    windowSettings->setWindowMode(WINDOW_MODE_NORMAL);
    windowSettings->setCentered(true);
    windowSettings->setTransparent(true);
    windowSettings->setShouldMultiSample(true);
    windowSettings->setSampleSize(2);

    Window window(windowSettings);
    glfwWindowHint(, GLFW_TRUE);

    glfwSetFramebufferSizeCallback(window.getWindow(), frameBufferSize);
    glfwSetCursorPosCallback(window.getWindow(), mousePositionCallback);
    //glfwSetMouseButtonCallback(window.getWindow(), mouseButtonCallback);

    Shader shader("../Assets/Shader.glsl");
    shader.bind();
    glLineWidth(1);
    glEnable(GL_LINE_SMOOTH);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    while(window.windowIsAlive()){
        glClear(GL_COLOR_BUFFER_BIT);
        shader.setUniform1f("time", glfwGetTime());
        glDrawArrays(GL_POINTS, 0, 1);
        //if(glfwGetKey(window.getWindow(), GLFW_KEY_ESCAPE) == GLFW_PRESS)
        //    window.destroyWindow();
        window.updateWindow();
    }
}