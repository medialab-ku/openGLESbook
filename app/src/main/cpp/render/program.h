#ifndef OPENGLES_PROGRAM_H
#define OPENGLES_PROGRAM_H

#include "global.h"
#include "render/shader.h"

class Program {
public:
    Program(const std::vector<Shader>& shaders);
    void use() const;
    GLuint getId() const;
protected:
    GLuint id{ 0 };
private:
    void create();
    void attachShaders(const std::vector<Shader>& shaders) const;
    void link() const;
};


#endif // OPENGLES_PROGRAM_H
