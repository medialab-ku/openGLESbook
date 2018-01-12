#ifndef OPENGLES_CAMERA_H
#define OPENGLES_CAMERA_H

#include "global.h"
#include "render/program.h"
#include "render/uniform.h"

class Camera {
public:
    Camera();
    virtual void update(const Program& program) const;
    glm::mat4 getViewMatrix() const;
    glm::vec3 getEye() const;
    glm::vec3 getAt() const;
    glm::vec3 getUp() const;
    float getFovy() const;
    float getAspect() const;
    float getZNear() const;
    float getZFar() const;
    Camera& setEye(const glm::vec3& eye);
    Camera& setAt(const glm::vec3& at);
    Camera& setUp(const glm::vec3& up);
    Camera& setFovy(const float fovy);
    Camera& setAspect(const float aspect);
    Camera& setNear(const float zNear);
    Camera& setFar(const float zFar);
protected:
    glm::vec3 eye{ 0.0f };
    glm::vec3 at{ 0.0f };
    glm::vec3 up{ 0.0f, 1.0f, 0.0f };
    float fovy{ glm::radians(60.0f) };
    float aspect{ 1.0f };
    float zNear{ 5.0f };
    float zFar{ 300.0f };
    glm::mat4 viewMatrix{ 1.0f };
    glm::mat4 projMatrix{ 1.0f };
    std::vector<Uniform> uniforms{
            { Uniform::Type::VEC3, "eyePos", glm::value_ptr(eye) },
            { Uniform::Type::MAT4, "viewMat", glm::value_ptr(viewMatrix) },
            { Uniform::Type::MAT4, "projMat", glm::value_ptr(projMatrix) }
    };
private:
    void updateViewMatrix();
    void updateProjMatrix();
};

#endif // OPENGLES_CAMERA_H
