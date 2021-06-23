#pragma once

enum WindowMode{
    WINDOW_MODE_FULLSCREEN,WINDOW_MODE_FULLSCREEN_BORDERLESS,WINDOW_MODE_NORMAL,WINDOW_MODE_BORDERLESS,WINDOW_MODE_MAX_SIZE,WINDOW_MODE_BORDERLESS_MAX_SIZE
};

class WindowSettings{
public:
    inline void setX(float x){this->x = x;}
    inline void setY(float y){this->y = y;}
    inline void setWidth(float width){this->width = width;}
    inline void setHeight(float height){this->height = height;}
    inline void setLocation(float x,float y){this->x = x,this->y = y;}
    inline void setSize(float width,float height){this->width = width,this->height = height;}
    inline void setResizable(bool resizable){this->resizable = resizable;}
    inline void setTitle(char* title){this->title = title;}
    inline void setWindowMode(WindowMode windowMode){this->windowMode = windowMode;}
    inline void setSwapInterval(int swapInterval){this->swapInterval = swapInterval;}
    inline void setCentered(bool centered){this->centered = centered;}
    inline void setFocused(bool focused){this->focused = focused;}
    inline void setVersionMajor(int major){this->major = major;}
    inline void setVersionMinor(int minor){this->minor = minor;}
    inline void setProfile(int profile){this->profile = profile;}
    inline void setCheckVersion(bool checkVersion){this->checkVersion = checkVersion;}
    inline void setIcon(char* path){this->icon = path;}
    inline void setShouldAutoScale(bool autoScale){this->autoScale = autoScale;}
    inline void setSampleSize(int sampleSize){this->sampleSize = sampleSize;}
    inline void setShouldMultiSample(bool sample){this->sample = sample;}
    inline void setTransparent(bool transparent){this->transparent = transparent;}
    inline void setFloating(bool floating){this->floating = floating;}
    inline void setDecorated(bool decorated){this->decorated = decorated;}

    inline char* getTitle(){return title;}
    inline float getXLocation(){return x;}
    inline float getYLocation(){return y;}
    inline float getWidth(){return width;}
    inline float getHeight(){return height;}
    inline bool shouldAutoScale(){return autoScale;}
    inline bool isResizable(){return resizable;}
    inline int getSwapInterval(){return swapInterval;}
    inline WindowMode getWindowMode(){return windowMode;}
    inline bool isCentered(){return centered;}
    inline bool isFocused(){return focused;}
    inline int getMajorVersion(){return major;}
    inline int getMinorVersion(){return minor;}
    inline int getProfile(){return profile;}
    inline bool shouldCheckVersion(){return checkVersion;}
    inline char* getIcon(){return icon;}
    inline int getSampleSize(){return sampleSize;}
    inline bool shouldMultiSample(){return sample;}
    inline bool isTransparent(){return transparent;}
    inline bool isFloating(){return floating;}
    inline bool isDecorated(){return decorated;}
private:
    float x = 0,y = 0;
    float width = 200,height = 200;
    bool resizable = true;
    char* title = "";
    int swapInterval = 1;
    WindowMode windowMode= WINDOW_MODE_NORMAL;
    int major = 4;
    int minor = 6;
    int profile = 0x00032001;
    char* icon = (char*) "";
    int sampleSize = 0;
    bool transparent = true,
    floating = false,
    sample = false,
    autoScale = false,
    centered = false,
    checkVersion = false,
    focused = true,
    decorated = true;
};