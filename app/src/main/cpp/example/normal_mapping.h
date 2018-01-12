#ifndef OPENGLES_NORMAL_MAPPING_H
#define OPENGLES_NORMAL_MAPPING_H

#include "utility/scene.h"

class NormalMapping : public Scene {
protected:
    virtual void start();
    virtual void update(const float deltaTime);
private:
    Shader vertexShader{ Shader::Type::VERTEX, AssetManager::readShader("normal_mapping_vs") };
    Shader fragmentShader{ Shader::Type::FRAGMENT, AssetManager::readShader("normal_mapping_fs") };
    Program program{ { vertexShader, fragmentShader } };
    Texture textureColor{ Texture::Type::ColorMap, AssetManager::readTexture("brick_color") };
    Texture textureNormal{ Texture::Type::NormalMap, AssetManager::readTexture("brick_normal") };
    Material material{ { textureColor, textureNormal } };
    Object wall{ AssetManager::readObject("wall"), material };
    Camera camera;
    Light light{ Light::Type::DIRECTIONAL };
};

#endif // OPENGLES_NORMAL_MAPPING_H
