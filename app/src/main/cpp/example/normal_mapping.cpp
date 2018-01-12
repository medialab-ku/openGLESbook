#include "normal_mapping.h"

void NormalMapping::start() {
    // use program
    program.use();

    // set camera and update it
    camera.setAspect((float) Screen::getWidth() / Screen::getHeight())
            .setEye(glm::vec3(30.0f))
            .setAt(glm::vec3(0.0f, 0.0f, -5.0f))
            .update(program);

    // set light and update it
    light.setDirection(glm::vec3(0.0f, 1.0f, 2.0f))
            .update(program);
}

void NormalMapping::update(const float deltaTime) {
    // clear screen
    clearScreenAll();

    // draw wall
    wall.draw(program);
}
