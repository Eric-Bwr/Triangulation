#include "Window.h"

Window::Window(WindowSettings *windowSettings) : windowSettings(windowSettings) {
    if(!glfwInit()){
        errorCode = FAILED_INIT_GLFW;
        windowShouldClose = true;
    }
    vidmode = glfwGetVideoMode(glfwGetPrimaryMonitor());
    initHints();
    constructWindow();
    if(!window){
        errorCode = FAILED_INIT_WINDOW;
        destroyWindow();
    }
    glfwMakeContextCurrent(window);
    if(!gladLoadGL()){
        errorCode = FAILED_INIT_GLAD;
        destroyWindow();
    }
    glVersion = (char *) glGetString(GL_VERSION);
    glfwSwapInterval(windowSettings->getSwapInterval());
    setIcon();
    if(windowSettings->shouldMultiSample()){
        glEnable(GL_MULTISAMPLE);
    }

}

void Window::initHints() {
    if(windowSettings->isFloating())
        glfwWindowHint(GLFW_FLOATING, GLFW_TRUE);
    if (windowSettings->shouldCheckVersion()) {
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, windowSettings->getMajorVersion());
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, windowSettings->getMinorVersion());
        glfwWindowHint(GLFW_OPENGL_PROFILE, windowSettings->getProfile());
    }
    if(!windowSettings->isFocused())
        glfwWindowHint(GLFW_FOCUSED, GLFW_FALSE);
    if (windowSettings->isResizable())
        glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);
    else
        glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
    if(windowSettings->shouldMultiSample())
        glfwWindowHint(GLFW_SAMPLES, windowSettings->getSampleSize());
    if(!windowSettings->isDecorated())
        glfwWindowHint(GLFW_DECORATED, GLFW_FALSE);
    if(windowSettings->isTransparent()) {
        glfwWindowHint(GLFW_TRANSPARENT_FRAMEBUFFER, GLFW_TRUE);
    }
}

void Window::constructWindow() {
    if (windowSettings->getWindowMode() == WINDOW_MODE_NORMAL ||
        windowSettings->getWindowMode() == WINDOW_MODE_BORDERLESS ||
        windowSettings->getWindowMode() == WINDOW_MODE_FULLSCREEN_BORDERLESS ||
        windowSettings->getWindowMode() == WINDOW_MODE_BORDERLESS_MAX_SIZE) {
        window = glfwCreateWindow(windowSettings->getWidth(), windowSettings->getHeight(),
                                  windowSettings->getTitle(), nullptr, nullptr);
    } else if (windowSettings->getWindowMode() == WINDOW_MODE_MAX_SIZE) {
        windowSettings->setLocation(0, 0);
        window = glfwCreateWindow(vidmode->width, vidmode->height,
                                  windowSettings->getTitle(), nullptr, nullptr);
    }else if (windowSettings->getWindowMode() == WINDOW_MODE_FULLSCREEN){
        window = glfwCreateWindow(vidmode->width, vidmode->height, windowSettings->getTitle(), glfwGetPrimaryMonitor(), nullptr);
    }
    if(windowSettings->getWindowMode() != WINDOW_MODE_MAX_SIZE && windowSettings->getWindowMode() != WINDOW_MODE_BORDERLESS_MAX_SIZE && windowSettings->getWindowMode() !=  WINDOW_MODE_FULLSCREEN_BORDERLESS) {
        if (windowSettings->isCentered())
            glfwSetWindowPos(window, (vidmode->width / 2) - (windowSettings->getWidth() / 2), (vidmode->height / 2) - (windowSettings->getHeight() / 2));
        else
            glfwSetWindowPos(window, windowSettings->getXLocation(), windowSettings->getYLocation());
    }
}

void Window::setIcon() {
    std::string iconPath = windowSettings->getIcon();
    if (!(iconPath.empty())) {
        auto icon = new Texture(iconPath.c_str());
        if(icon->getErrors().failedToLocate){
            errorCode = FAILED_TO_LOCATE_ICON_DATA;
            return;
        }
        if(icon->getErrors().failedToAllocate){
            errorCode = FAILED_TO_ALLOCATE_ICON_DATA;
            return;
        }
        if(icon->getErrors().failedToReadData){
            errorCode = FAILED_TO_LOAD_ICON_DATA;
            return;
        }
        if(icon->getErrors().failedToGetTextureType){
            errorCode = FAILED_TO_GET_TEXTURE_TYPE;
            return;
        }
        GLFWimage images[1];
        images[0].width = icon->getWidth();
        images[0].height = icon->getHeight();
        images[0].pixels = icon->getData();
        if (images[0].pixels == nullptr){
            errorCode = FAILED_TO_LOAD_ICON_DATA;
            return;
        } else {
            glfwSetWindowIcon(window, 1, images);
        }
        free(images[0].pixels);
    }
}

void Window::updateWindow() {
    glfwSwapBuffers(window);
    glfwPollEvents();
    if(glfwWindowShouldClose(window))
        windowShouldClose = true;
}

void Window::destroyWindow() {
    windowShouldClose = true;
    glfwDestroyWindow(window);
}

Window::~Window() = default;