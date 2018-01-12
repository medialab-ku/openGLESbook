#ifndef OPENGLES_IMAGE_TEXTURING_H
#define OPENGLES_IMAGE_TEXTURING_H

#include "utility/scene.h"

class ImageTexturing : public Scene {
protected:
    virtual void start();
    virtual void update(const float deltaTime);
private:
    Shader vertexShader{ Shader::Type::VERTEX, AssetManager::readShader("image_texturing_vs") };
    Shader fragmentShader{ Shader::Type::FRAGMENT, AssetManager::readShader("image_texturing_fs") };
    Program program{ { vertexShader, fragmentShader } };
    Texture texture{ Texture::Type::ColorMap, AssetManager::readTexture("brick_color") };
    Material material{ { texture } };
    Object teapot{ AssetManager::readBinaryObject("teapot"), material };
    Camera camera;
};

#endif // OPENGLES_IMAGE_TEXTURING_H
