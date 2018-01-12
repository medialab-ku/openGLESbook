#include "phong_lighting.h"

void PhongLighting::start() {
    // use program
    program.use();

    // set camera
    camera.setAspect((float) Screen::getWidth() / Screen::getHeight())
            .setEye(glm::vec3(30.0f));

    // set light and update it
    light.setDirection(glm::vec3(1.0f))
            .update(program);
}

void PhongLighting::update(const float deltaTime) {
    // clear screen
    clearScreenAll();

    // rotate camera
    camera.setEye(glm::rotate(deltaTime * glm::radians(60.0f), camera.getUp())
                  * glm::vec4(camera.getEye(), 1.0))
            .update(program);

    // draw teapot
    teapot.draw(program);
}
