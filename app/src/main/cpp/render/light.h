#ifndef OPENGLES_LIGHT_H
#define OPENGLES_LIGHT_H

#include "global.h"
#include "render/program.h"
#include "render/uniform.h"

class Light {
public:
    enum class Type{ DIRECTIONAL, POINT };
    Light(Type type);
    virtual void update(const Program& program) const;
    glm::vec3 getDiffuse() const;
    glm::vec3 getSpecular() const;
    glm::vec3 getAmbient() const;
    glm::vec3 getDirection() const;
    glm::vec3 getPosition() const;
    float getSize() const;
    float getNear() const;
    float getFar() const;
    Light& setDiffuse(const glm::vec3& diffuse);
    Light& setSpecular(const glm::vec3& specular);
    Light& setAmbient(const glm::vec3& ambient);
    Light& setDirection(const glm::vec3& direction);
    Light& setPosition(const glm::vec3& position);
    Light& setSize(const float size);
    Light& setNear(const float zNear);
    Light& setFar(const float zFar);
protected:
    Type type;
    glm::vec3 diffuse{ 0.9f };
    glm::vec3 specular{ 1.0f };
    glm::vec3 ambient{ 0.2f };
    glm::vec3 direction{ 0.0f };
    glm::vec3 position{ 0.0f };
    float size{ 50.0f };
    float zNear{ 10.0f };
    float zFar{ 100.0f };
    glm::mat4 viewMatrix{ 1.0f };
    glm::mat4 projMatrix{ 1.0f };
    std::vector<Uniform> uniforms{ {
            { Uniform::Type::MAT4, "lightViewMat", glm::value_ptr(viewMatrix) },
            { Uniform::Type::MAT4, "lightProjMat", glm::value_ptr(projMatrix) },
            { Uniform::Type::VEC3, "srcDiff", glm::value_ptr(diffuse) },
            { Uniform::Type::VEC3, "srcSpec", glm::value_ptr(specular) },
            { Uniform::Type::VEC3, "srcAmbi", glm::value_ptr(ambient) },
            { Uniform::Type::VEC3, "lightDir", glm::value_ptr(direction) },
            { Uniform::Type::VEC3, "lightPos", glm::value_ptr(position) }
    } };
private:
    void updateViewMatrix();
    void updateProjMatrix();
};

#endif // OPENGLES_LIGHT_H
