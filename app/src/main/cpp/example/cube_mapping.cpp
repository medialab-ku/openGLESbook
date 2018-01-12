#include "example/cube_mapping.h"

void CubeMapping::start() {
    // set shadow map to render target
    renderTarget.setDepthTarget(shadowMap);

    // set camera aspect and position
    camera.setAspect((float) Screen::getWidth() / Screen::getHeight())
            .setEye(glm::vec3(30.0f));

    // set light position
    light.setPosition(glm::vec3(30.0f));

    // lower floor
    floor.setWorldMatrix(glm::translate(glm::vec3(0.0f, -10.0f, 0.0f)));
}

void CubeMapping::update(const float deltaTime) {
    // arcball rotation
    arcballRotation();

    // rotate camera
    camera.setEye(glm::rotate(deltaTime * glm::radians(30.0f), camera.getUp())
                    * glm::vec4(camera.getEye(), 1.0));

    // first pass - create shadow map
    {
        // use render target
        renderTarget.use();

        // set viewport and color mask
        setViewportToTexture();
        setColorMaskOff();

        // clear screen depth
        clearScreenDepth();

        // create shadow map using floor and teapot
        shadow1Program.use();
        shadowMap.update(shadow1Program);
        light.update(shadow1Program);
        floor.draw(shadow1Program);
        teapot.draw(shadow1Program);
    }

    // second pass - draw objects
    {
        // use default render target
        renderTarget.useDefault();

        // set viewport and color mask
        setViewportToScreen();
        setColorMaskOn();

        // clear screen
        clearScreenAll();

        // draw floor with shadow mapping
        shadow2Program.use();
        shadowMap.update(shadow2Program);
        camera.update(shadow2Program);
        light.update(shadow2Program);
        floor.draw(shadow2Program);

        // draw sky box with simple cube mapping
        skyboxProgram.use();
        camera.update(skyboxProgram);
        skybox.draw(skyboxProgram);

        // draw teapot with environment cube mapping
        teapotProgram.use();
        camera.update(teapotProgram);
        teapot.draw(teapotProgram);
    }
}

void CubeMapping::arcballRotation() {
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

glm::vec3 CubeMapping::arcballVector() const {
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
