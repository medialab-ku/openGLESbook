#ifndef OPENGLES_TANGENT_MAPPING_H
#define OPENGLES_TANGENT_MAPPING_H

#include "utility/scene.h"

class TangentMapping : public Scene {
protected:
    virtual void start();
    virtual void update(const float deltaTime);
private:
    Shader vertexShader{ Shader::Type::VERTEX, AssetManager::readShader("tangent_mapping_vs") };
    Shader fragmentShader{ Shader::Type::FRAGMENT, AssetManager::readShader("tangent_mapping_fs") };
    Program program{ { vertexShader, fragmentShader } };
    Texture textureColor{ Texture::Type::ColorMap, AssetManager::readTexture("brick_color") };
    Texture textureNormal{ Texture::Type::NormalMap, AssetManager::readTexture("brick_normal") };
    Material material{ { textureColor, textureNormal } };
    Object teapot{ AssetManager::readBinaryObject("teapot"), material };
    Camera camera;
    Light light{ Light::Type::DIRECTIONAL };
    void arcballRotation();
    glm::vec3 arcballVector() const;
};

#endif // OPENGLES_TANGENT_MAPPING_H
