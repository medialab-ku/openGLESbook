#ifndef OPENGLES_UNIFORM_H
#define OPENGLES_UNIFORM_H

#include "global.h"
#include "render/program.h"

class Uniform {
public:
    enum class Type { INT, FLOAT, VEC3, MAT4 };
    Uniform(const Type type, const std::string& name, const GLvoid* const value);
    virtual void update(const Program& program) const;
    Uniform& setType(const Type type);
    Uniform& setName(const std::string& name);
    Uniform& setValue(const GLvoid* const value);
protected:
    Type type{ Type::INT };
    std::string name{ "" };
    const GLvoid* value{ nullptr };
};

#endif // OPENGLES_UNIFORM_H
