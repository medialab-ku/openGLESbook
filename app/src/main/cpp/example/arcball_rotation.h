#ifndef OPENGLES_ARCBALL_ROTATION_H
#define OPENGLES_ARCBALL_ROTATION_H

#include "utility/scene.h"

class ArcballRotation : public Scene {
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
    void arcballRotation();
    glm::vec3 arcballVector() const;
};

#endif // OPENGLES_ARCBALL_ROTATION_H
