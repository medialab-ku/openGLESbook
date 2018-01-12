#ifndef OPENGLES_PHONG_LIGHTING_H
#define OPENGLES_PHONG_LIGHTING_H

#include "utility/scene.h"

class PhongLighting : public Scene {
protected:
    virtual void start();
    virtual void update(const float deltaTime);
private:
    Shader vertexShader{ Shader::Type::VERTEX, AssetManager::readShader("phong_lighting_vs") };
    Shader fragmentShader{ Shader::Type::FRAGMENT, AssetManager::readShader("phong_lighting_fs") };
    Program program{ { vertexShader, fragmentShader } };
    Texture texture{ Texture::Type::ColorMap, AssetManager::readTexture("brick_color") };
    Material material{ { texture } };
    Object teapot{ AssetManager::readBinaryObject("teapot"), material };
    Camera camera;
    Light light{ Light::Type::DIRECTIONAL };
};

#endif // OPENGLES_PHONG_LIGHTING_H
