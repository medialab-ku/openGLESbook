#include "input.h"

int Screen::width = 1;
int Screen::height = 1;

void Screen::setWidth(const int width) {
    Screen::width = width;
}

void Screen::setHeight(const int height) {
    Screen::height = height;
}

int Screen::getWidth() {
    return width;
}

int Screen::getHeight() {
    return height;
}

Touch::Motion Touch::motion = Touch::Motion::UP;
float Touch::x = 0.0f;
float Touch::y = 0.0f;

void Touch::setMotion(const Touch::Motion motion) {
    Touch::motion = motion;
}

void Touch::setX(const float x) {
    Touch::x = x;
}

void Touch::setY(const float y) {
    Touch::y = y;
}

Touch::Motion Touch::getMotion() {
    return motion;
}

float Touch::getX() {
    return x;
}

float Touch::getY() {
    return y;
}
