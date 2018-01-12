#include "uniform.h"

Uniform::Uniform(const Uniform::Type type, const std::string& name, const GLvoid* const value) {
    this->type = type;
    this->name = name;
    this->value = value;
}

void Uniform::update(const Program& program) const {
    // get location
    GLint loc = glGetUniformLocation(program.getId(), name.c_str());
    if (loc < 0) return;

    // update uniform data
    switch (type) {
        case Type::INT:
            glUniform1iv(loc, 1, (const GLint*) value);
            break;
        case Type::FLOAT:
            glUniform1fv(loc, 1, (const GLfloat*) value);
            break;
        case Type::VEC3:
            glUniform3fv(loc, 1, (const GLfloat*) value);
            break;
        case Type::MAT4:
            glUniformMatrix4fv(loc, 1, GL_FALSE, (const GLfloat*) value);
            break;
    }
}

Uniform& Uniform::setType(const Uniform::Type type) {
    this->type = type;
    return *this;
}

Uniform& Uniform::setName(const std::string& name) {
    this->name = name;
    return *this;
}

Uniform& Uniform::setValue(const GLvoid* const value) {
    this->value = value;
    return *this;
}
