#include "camera.h"

Camera::Camera() {
    // update view matrix and projection matrix
    updateViewMatrix();
    updateProjMatrix();
}

void Camera::update(const Program& program) const {
    // update uniforms
    for (const Uniform& uniform : uniforms) uniform.update(program);
}

glm::mat4 Camera::getViewMatrix() const {
    return viewMatrix;
}

glm::vec3 Camera::getEye() const {
    return eye;
}

glm::vec3 Camera::getAt() const {
    return at;
}

glm::vec3 Camera::getUp() const {
    return up;
}

float Camera::getFovy() const {
    return fovy;
}

float Camera::getAspect() const {
    return aspect;
}

float Camera::getZNear() const {
    return zNear;
}

float Camera::getZFar() const {
    return zFar;
}

Camera& Camera::setEye(const glm::vec3& eye) {
    this->eye = eye;
    updateViewMatrix();
    return *this;
}

Camera& Camera::setAt(const glm::vec3& at) {
    this->at = at;
    updateViewMatrix();
    return *this;
}

Camera& Camera::setUp(const glm::vec3& up) {
    this->up = up;
    updateViewMatrix();
    return *this;
}

Camera& Camera::setFovy(const float fovy) {
    this->fovy = fovy;
    updateProjMatrix();
    return *this;
}

Camera& Camera::setAspect(const float aspect) {
    this->aspect = aspect;
    updateProjMatrix();
    return *this;
}

Camera& Camera::setNear(const float zNear) {
    this->zNear = zNear;
    updateProjMatrix();
    return *this;
}

Camera& Camera::setFar(const float zFar) {
    this->zFar = zFar;
    updateProjMatrix();
    return *this;
}

void Camera::updateViewMatrix() {
    // update view matrix
    viewMatrix = glm::lookAt(eye, at, up);
}

void Camera::updateProjMatrix() {
    // update projection matrix
    projMatrix = glm::perspective(fovy, aspect, zNear, zFar);
}
