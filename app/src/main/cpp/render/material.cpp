#include "material.h"

Material::Material(const std::vector<Texture>& textures) : textures(textures) {

}

void Material::update(const Program& program) const {
    // update uniforms
    for (const Uniform& uniform : uniforms) uniform.update(program);

    // update textures
    for (const Texture& texture : textures) texture.update(program);
}

glm::vec3 Material::getSpecular() const {
    return specular;
}

glm::vec3 Material::getAmbient() const {
    return ambient;
}

glm::vec3 Material::getEmissive() const {
    return emissive;
}

float Material::getShininess() const {
    return shininess;
}

Material& Material::setSpecular(const glm::vec3& specular) {
    this->specular = specular;
    return *this;
}

Material& Material::setAmbient(const glm::vec3& ambient) {
    this->ambient = ambient;
    return *this;
}

Material& Material::setEmissive(const glm::vec3& emissive) {
    this->emissive = emissive;
    return *this;
}

Material& Material::setShininess(const float shininess) {
    this->shininess = shininess;
    return *this;
}
