#ifndef OPENGLES_SCENE_H
#define OPENGLES_SCENE_H

#include "global.h"
#include "utility/asset.h"
#include "utility/input.h"
#include "render/target.h"
#include "render/shader.h"
#include "render/program.h"
#include "render/texture.h"
#include "render/material.h"
#include "render/object.h"
#include "render/camera.h"
#include "render/light.h"

class Scene {
public:
    void run(const float deltaTime);
protected:
    virtual void start() = 0;
    virtual void update(const float deltaTime) = 0;
    void enableZBuffering() const;
    void setColorMaskOn() const;
    void setColorMaskOff() const;
    void setViewportToScreen() const;
    void setViewportToTexture() const;
    void clearScreenAll() const;
    void clearScreenColor() const;
    void clearScreenDepth() const;
    void setPatchVertices(int vertices) const;
private:
    bool started{ false };
};

#endif // OPENGLES_SCENE_H
