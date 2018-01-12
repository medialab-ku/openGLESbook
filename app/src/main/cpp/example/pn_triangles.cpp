#include "example/pn_triangles.h"

void PN_Triangles::start() {
    // set patch vertices
    setPatchVertices(3);

    // use program
    program.use();

    // set camera
    camera.setAspect((float) Screen::getWidth() / Screen::getHeight())
            .setEye(glm::vec3(20.0f));

    // set tessellation level
    boar.setTessLevel(10.0f);
}

void PN_Triangles::update(const float deltaTime) {
    // clear screen
    clearScreenAll();

    // rotate camera
    camera.setEye(glm::rotate(deltaTime * glm::radians(60.0f), camera.getUp())
                  * glm::vec4(camera.getEye(), 1.0))
            .update(program);

    // draw boar
    boar.draw(program, Object::DrawType::PATCHES);
}
