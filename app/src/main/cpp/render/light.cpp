#include "light.h"

Light::Light(Light::Type type) : type(type) {
    // update view matrix and projection matrix
    updateViewMatrix();
    updateProjMatrix();
}

void Light::update(const Program& program) const {
    // update uniforms
    for (const Uniform& uniform : uniforms) uniform.update(program);
}

glm::vec3 Light::getDiffuse() const {
    return diffuse;
}

glm::vec3 Light::getSpecular() const {
    return specular;
}

glm::vec3 Light::getAmbient() const {
    return ambient;
}

glm::vec3 Light::getDirection() const {
    return direction;
}

glm::vec3 Light::getPosition() const {
    return position;
}

float Light::getSize() const {
    return size;
}

float Light::getNear() const {
    return zNear;
}

float Light::getFar() const {
    return zFar;
}

Light& Light::setDiffuse(const glm::vec3& diffuse) {
    this->diffuse = diffuse;
    return *this;
}

Light& Light::setSpecular(const glm::vec3& specular) {
    this->specular = specular;
    return *this;
}

Light& Light::setAmbient(const glm::vec3& ambient) {
    this->ambient = ambient;
    return *this;
}

Light& Light::setDirection(const glm::vec3& direction) {
    this->direction = direction;
    updateViewMatrix();
    return *this;
}

Light& Light::setPosition(const glm::vec3& position) {
    this->position = position;
    updateViewMatrix();
    updateProjMatrix();
    return *this;
}

Light &Light::setSize(const float size) {
    this->size = size;
    updateProjMatrix();
    return *this;
}

Light &Light::setNear(const float zNear) {
    this->zNear = zNear;
    updateViewMatrix();
    updateProjMatrix();
    return *this;
}

Light &Light::setFar(const float zFar) {
    this->zFar = zFar;
    updateViewMatrix();
    updateProjMatrix();
    return *this;
}

void Light::updateViewMatrix() {
    // update view matrix
    switch (type) {
        case Type::DIRECTIONAL:
            viewMatrix = glm::lookAt((zNear + zFar) / 2.0f * glm::normalize(direction),
                                     glm::vec3(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
            break;
        case Type::POINT:
            viewMatrix = glm::lookAt(position, glm::vec3(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
            break;
    }
}

void Light::updateProjMatrix() {
    // update projection matrix
    switch (type) {
        case Type::DIRECTIONAL:
            projMatrix = glm::ortho(-size / 2.0f, size / 2.0f, -size / 2.0f, size / 2.0f,
                                    zNear, zFar);
            break;
        case Type::POINT:
            projMatrix = glm::perspective(glm::radians(60.0f), 1.0f, zNear, zFar);
            break;
    }
}
