#ifndef OPENGLES_MATERIAL_H
#define OPENGLES_MATERIAL_H

#include "global.h"
#include "render/program.h"
#include "render/uniform.h"
#include "render/texture.h"

class Material {
public:
    Material(const std::vector<Texture>& textures);
    virtual void update(const Program& program) const;
    glm::vec3 getSpecular() const;
    glm::vec3 getAmbient() const;
    glm::vec3 getEmissive() const;
    float getShininess() const;
    Material& setSpecular(const glm::vec3& specular);
    Material& setAmbient(const glm::vec3& ambient);
    Material& setEmissive(const glm::vec3& emissive);
    Material& setShininess(const float shininess);
protected:
    glm::vec3 specular{ 1.0f };
    glm::vec3 ambient{ 0.2f };
    glm::vec3 emissive{ 0.0f };
    float shininess{ 3.0f };
    std::vector<Uniform> uniforms{ {
            { Uniform::Type::VEC3, "matSpec", glm::value_ptr(specular) },
            { Uniform::Type::VEC3, "matAmbi", glm::value_ptr(ambient) },
            { Uniform::Type::VEC3, "matEmit", glm::value_ptr(emissive) },
            { Uniform::Type::FLOAT, "matSh", &shininess }
    } };
    std::vector<Texture> textures;
};

#endif // OPENGLES_MATERIAL_H
