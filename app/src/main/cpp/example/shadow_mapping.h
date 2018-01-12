#ifndef OPENGLES_SHADOW_MAPPING_H
#define OPENGLES_SHADOW_MAPPING_H

#include "utility/scene.h"

class ShadowMapping : public Scene {
protected:
    virtual void start();
    virtual void update(const float deltaTime);
private:
    RenderTarget renderTarget;
    Shader shadow1VertexShader{ Shader::Type::VERTEX, AssetManager::readShader("shadow_mapping_first_vs") };
    Shader shadow1FragmentShader{ Shader::Type::FRAGMENT, AssetManager::readShader("shadow_mapping_first_fs") };
    Shader shadow2VertexShader{ Shader::Type::VERTEX, AssetManager::readShader("shadow_mapping_second_vs") };
    Shader shadow2FragmentShader{ Shader::Type::FRAGMENT, AssetManager::readShader("shadow_mapping_second_fs") };
    Program shadow1Program{ { shadow1VertexShader, shadow1FragmentShader } };
    Program shadow2Program{ { shadow2VertexShader, shadow2FragmentShader } };
    Texture shadowMap{ Texture::Type::ShadowMap };
    Texture chessColor{ Texture::Type::ColorMap, AssetManager::readTexture("chess_color") };
    Texture brickColor{ Texture::Type::ColorMap, AssetManager::readTexture("brick_color") };
    Material chess{ { chessColor } };
    Material brick{ { brickColor } };
    Object floor{ AssetManager::readObject("floor"), chess };
    Object teapot{ AssetManager::readBinaryObject("teapot"), brick };
    Camera camera;
    Light light{ Light::Type::POINT };
    void arcballRotation();
    glm::vec3 arcballVector() const;
};

#endif // OPENGLES_SHADOW_MAPPING_H
