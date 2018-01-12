#ifndef OPENGLES_HELLO_TEAPOT_H
#define OPENGLES_HELLO_TEAPOT_H

#include "utility/scene.h"

class HelloTeapot : public Scene {
protected:
    virtual void start();
    virtual void update(const float deltaTime);
private:
    Shader vertexShader{ Shader::Type::VERTEX, AssetManager::readShader("hello_teapot_vs") };
    Shader fragmentShader{ Shader::Type::FRAGMENT, AssetManager::readShader("hello_teapot_fs") };
    Program program{ { vertexShader, fragmentShader } };
    Object teapot{ AssetManager::readBinaryObject("teapot") };
    Camera camera;
};

#endif // OPENGLES_HELLO_TEAPOT_H
