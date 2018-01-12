#include "tangent_mapping.h"

void TangentMapping::start() {
    // use program
    program.use();

    // set camera and update it
    camera.setAspect((float) Screen::getWidth() / Screen::getHeight())
            .setEye(glm::vec3(30.0f))
            .update(program);

    // set light and update it
    light.setDirection(glm::vec3(-1.0f, 2.0f, 2.0f))
            .update(program);
}

void TangentMapping::update(const float deltaTime) {
    // clear screen
    clearScreenAll();

    // Arcball rotation
    arcballRotation();

    // draw teapot
    teapot.draw(program);
}

void TangentMapping::arcballRotation() {
    // define last touch motion and arcball vector
    static Touch::Motion lastMotion = Touch::getMotion();
    static glm::vec3 lastVector = arcballVector();

    // get current touch motion and arcball vector
    const Touch::Motion currentMotion = Touch::getMotion();
    const glm::vec3 currentVector = arcballVector();

    // check touch motions
    if (currentMotion != Touch::Motion::UP) {
        if (lastMotion != Touch::Motion::UP) {
            // check arcball vectors
            if (lastVector == currentVector) return;

            // compute rotation angle and axis
            const float angle = glm::acos(glm::clamp(glm::dot(lastVector, currentVector), -1.0f, 1.0f));
            const glm::vec3 axis = glm::inverse(glm::mat3(camera.getViewMatrix() * teapot.getWorldMatrix()))
                                   * glm::cross(lastVector, currentVector);

            // update world matrix of teapot
            teapot.setWorldMatrix(teapot.getWorldMatrix() * glm::rotate(angle, axis));
        }

        // update last arcball vector
        lastVector = currentVector;
    }

    // update last touch motion
    lastMotion = currentMotion;
}

glm::vec3 TangentMapping::arcballVector() const {
    // compute vector
    glm::vec3 vector(
            2.0f * Touch::getX() / Screen::getWidth() - 1.0f,
            2.0f * Touch::getY() / Screen::getHeight() - 1.0f,
            0.0f);

    // flip y-axis
    vector.y = -vector.y;

    // compute z-coordinate
    const float square = vector.x * vector.x + vector.y * vector.y;
    if (square < 1.0f) vector.z = sqrtf(1.0f - square);
    else vector = glm::normalize(vector);

    // return vector
    return vector;
}
