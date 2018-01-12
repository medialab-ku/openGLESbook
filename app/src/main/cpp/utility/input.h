#ifndef OPENGLES_INPUT_H
#define OPENGLES_INPUT_H

#include "global.h"

class Screen {
private:
    static int width;
    static int height;
public:
    static void setWidth(const int width);
    static void setHeight(const int height);
    static int getWidth();
    static int getHeight();
};

class Touch {
public:
    enum class Motion { DOWN, MOVE, UP };
private:
    static Motion motion;
    static float x;
    static float y;
public:
    static void setMotion(const Motion motion);
    static void setX(const float x);
    static void setY(const float y);
    static Motion getMotion();
    static float getX();
    static float getY();
};

#endif // OPENGLES_INPUT_H
