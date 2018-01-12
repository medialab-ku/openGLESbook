#ifndef OPENGLES_CUBE_MAPPING_H
#define OPENGLES_CUBE_MAPPING_H

#include "utility/scene.h"

class CubeMapping : public Scene {
protected:
    virtual void start();
    virtual void update(const float deltaTime);
private:
    RenderTarget renderTarget;
    Shader shadow1VertexShader{ Shader::Type::VERTEX, AssetManager::readShader("shadow_mapping_first_vs") };
    Shader shadow1FragmentShader{ Shader::Type::FRAGMENT, AssetManager::readShader("shadow_mapping_first_fs") };
    Shader shadow2VertexShader{ Shader::Type::VERTEX, AssetManager::readShader("shadow_mapping_second_vs") };
    Shader shadow2FragmentShader{ Shader::Type::FRAGMENT, AssetManager::readShader("shadow_mapping_second_fs") };
    Shader skyboxVertexShader{ Shader::Type::VERTEX, AssetManager::readShader("cube_mapping_skybox_vs") };
    Shader skyboxFragmentShader{ Shader::Type::FRAGMENT, AssetManager::readShader("cube_mapping_skybox_fs") };
    Shader teapotVertexShader{ Shader::Type::VERTEX, AssetManager::readShader("cube_mapping_teapot_vs") };
    Shader teapotFragmentShader{ Shader::Type::FRAGMENT, AssetManager::readShader("cube_mapping_teapot_fs") };
    Program shadow1Program{ { shadow1VertexShader, shadow1FragmentShader } };
    Program shadow2Program{ { shadow2VertexShader, shadow2FragmentShader } };
    Program skyboxProgram{ { skyboxVertexShader, skyboxFragmentShader } };
    Program teapotProgram{ { teapotVertexShader, teapotFragmentShader } };
    Texture shadowMap{ Texture::Type::ShadowMap };
    Texture chessColor{ Texture::Type::ColorMap, AssetManager::readTexture("chess_color") };
    Texture chessNormal{ Texture::Type::NormalMap, AssetManager::readTexture("chess_normal") };
    Texture islandCube{ Texture::Type::CubeMap, AssetManager::readCubeTexture("island") };
    Material chess{ { chessColor, chessNormal } };
    Material island{ { islandCube } };
    Object floor{ AssetManager::readObject("floor"), chess };
    Object skybox{ AssetManager::readObject("skybox"), island };
    Object teapot{ AssetManager::readBinaryObject("teapot"), island };
    Camera camera;
    Light light{ Light::Type::POINT };
    void arcballRotation();
    glm::vec3 arcballVector() const;
};

#endif // OPENGLES_CUBE_MAPPING_H
