#include "example/disp_mapping.h"

void DispMapping::start() {
    // set patch vertices
    setPatchVertices(4);

    // use program
    program.use();

    // set camera
    camera.setAspect((float) Screen::getWidth() / Screen::getHeight())
            .setEye(glm::vec3(30.0f))
            .setAt(glm::vec3(0.0f, -10.0f, 0.0f));

    // set terrain
    terrain.setTessLevel(50.0f);
    terrain.setDispFactor(5.0f);
    terrain.setWorldMatrix(glm::rotate(glm::radians(-90.0f), glm::vec3(1.0f, 0.0f, 0.0f)));
}

void DispMapping::update(const float deltaTime) {
    // clear screen
    clearScreenAll();

    // rotate camera
    camera.setEye(glm::rotate(deltaTime * glm::radians(60.0f), camera.getUp())
                  * glm::vec4(camera.getEye(), 1.0))
            .update(program);

    // draw floor
    terrain.draw(program, Object::DrawType::PATCHES);
}
