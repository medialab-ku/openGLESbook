#include "scene.h"

void Scene::run(const float deltaTime) {
    // start if not started
    if (!started) {
        // initial setting
        enableZBuffering();
        setColorMaskOn();
        setViewportToScreen();

        // start
        start();

        // change flag
        started = true;
    }

    // update
    update(deltaTime);
}

void Scene::enableZBuffering() const {
    // enable depth test (z-buffering)
    glEnable(GL_DEPTH_TEST);
}

void Scene::setColorMaskOn() const {
    // set color mask on
    glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);
}

void Scene::setColorMaskOff() const {
    // set color mask off
    glColorMask(GL_FALSE, GL_FALSE, GL_FALSE, GL_FALSE);
}

void Scene::setViewportToScreen() const {
    // set viewport to fit screen size
    glViewport(0, 0, Screen::getWidth(), Screen::getHeight());
}

void Scene::setViewportToTexture() const {
    // set viewport to fit default map size
    glViewport(0, 0, SHADOW_MAP_SIZE, SHADOW_MAP_SIZE);
}

void Scene::clearScreenAll() const {
    // clear color and depth buffer
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Scene::clearScreenColor() const {
    // clear color buffer
    glClear(GL_COLOR_BUFFER_BIT);
}

void Scene::clearScreenDepth() const {
    // clear depth buffer
    glClear(GL_DEPTH_BUFFER_BIT);
}

void Scene::setPatchVertices(int vertices) const {
    // set patch vertices
    glPatchParameteri(GL_PATCH_VERTICES, vertices);
}
