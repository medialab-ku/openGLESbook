#ifndef OPENGLES_TEXTURE_H
#define OPENGLES_TEXTURE_H

#include "global.h"
#include "render/program.h"
#include "render/uniform.h"

class Texture {
public:
    enum class Type { ColorMap = 0, NormalMap = 1, ShadowMap = 2, CubeMap = 3, HeightMap = 4 };
    Texture(const Type type, const TexData& texData = TexData());
    virtual void update(const Program &program) const;
    GLuint getId() const;
protected:
    Type type{ Type::ColorMap };
    GLuint id{ 0 };
    Uniform uniform{ Uniform::Type::INT, "", nullptr };
private:
    void create();
    void setUniform();
    void setData(const TexData& texData) const;
};

#endif // OPENGLES_TEXTURE_H
