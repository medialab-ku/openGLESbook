#ifndef OPENGLES_PN_TRIANGLES_H
#define OPENGLES_PN_TRIANGLES_H

#include "utility/scene.h"

class PN_Triangles : public Scene {
protected:
    virtual void start();
    virtual void update(const float deltaTime);
private:
    Shader vertexShader{ Shader::Type::VERTEX, AssetManager::readShader("pn_triangles_vs") };
    Shader fragmentShader{ Shader::Type::FRAGMENT, AssetManager::readShader("pn_triangles_fs") };
    Shader tessControlShader{ Shader::Type::TESS_CONTROL, AssetManager::readShader("pn_triangles_tcs") };
    Shader tessEvaluationShader{ Shader::Type::TESS_EVALUATION, AssetManager::readShader("pn_triangles_tes") };
    Program program{ { vertexShader, fragmentShader, tessControlShader, tessEvaluationShader } };
    Object boar{ AssetManager::readBinaryObject("boar") };
    Camera camera;
};

#endif // OPENGLES_PN_TRIANGLES_H
