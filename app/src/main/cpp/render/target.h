#ifndef OPENGLES_TARGET_H
#define OPENGLES_TARGET_H

#include "global.h"
#include "render/texture.h"

class RenderTarget {
public:
    RenderTarget();
    static void useDefault();
    void use() const;
    void setColorTarget(const Texture& texture) const;
    void setDepthTarget(const Texture& texture) const;
protected:
    GLuint id;
private:
    void create();
};

#endif // OPENGLES_TARGET_H
