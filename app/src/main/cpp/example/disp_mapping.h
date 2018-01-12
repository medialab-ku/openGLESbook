#ifndef OPENGLES_DISP_MAPPING_H
#define OPENGLES_DISP_MAPPING_H

#include "utility/scene.h"

class DispMapping : public Scene {
protected:
    virtual void start();
    virtual void update(const float deltaTime);
private:
    Shader vertexShader{ Shader::Type::VERTEX, AssetManager::readShader("disp_mapping_vs") };
    Shader fragmentShader{ Shader::Type::FRAGMENT, AssetManager::readShader("disp_mapping_fs") };
    Shader tessControlShader{ Shader::Type::TESS_CONTROL, AssetManager::readShader("disp_mapping_tcs") };
    Shader tessEvaluationShader{ Shader::Type::TESS_EVALUATION, AssetManager::readShader("disp_mapping_tes") };
    Program program{ { vertexShader, fragmentShader, tessControlShader, tessEvaluationShader } };
    Texture colorMap{ Texture::Type::ColorMap, AssetManager::readTexture("terrain_color") };
    Texture dispMap{ Texture::Type::HeightMap, AssetManager::readTexture("terrain_height") };
    Material material{ { colorMap, dispMap } };
    Object terrain{ AssetManager::readObject("terrain"), material };
    Camera camera;
};

#endif // OPENGLES_DISP_MAPPING_H
