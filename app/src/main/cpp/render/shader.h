#ifndef OPENGLES_SHADER_H
#define OPENGLES_SHADER_H

#include "global.h"

class Shader {
public:
    enum class Type { VERTEX, FRAGMENT, TESS_CONTROL, TESS_EVALUATION };
    Shader(const Type type, const std::string& source);
    GLuint getId() const;
protected:
    GLuint id{ 0 };
private:
    void create(const Shader::Type type);
    void setSource(const std::string &source) const;
    void compile() const;
};


#endif // OPENGLES_SHADER_H
