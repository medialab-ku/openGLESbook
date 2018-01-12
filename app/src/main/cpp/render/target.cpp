#include "target.h"

RenderTarget::RenderTarget() {
    // create
    create();
}

void RenderTarget::useDefault() {
    // bind default framebuffer
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void RenderTarget::use() const {
    // bind framebuffer
    glBindFramebuffer(GL_FRAMEBUFFER, id);
}

void RenderTarget::create() {
    LOG_PRINT_DEBUG("Create render target");

    // generate frame buffer
    glGenFramebuffers(1, &id);
    if (!id) LOG_PRINT_ERROR("Fail to create frame buffer");

    // bind framebuffer
    glBindFramebuffer(GL_FRAMEBUFFER, id);

    // disable read and write
    GLenum none = GL_NONE;
    glReadBuffer(none);
    glDrawBuffers(1, &none);

    // bind default framebuffer
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void RenderTarget::setColorTarget(const Texture& texture) const {
    // bind framebuffer
    glBindFramebuffer(GL_FRAMEBUFFER, id);

    // set frame buffer texture attachment
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0,
                           GL_TEXTURE_2D, texture.getId(), 0);

    // bind default framebuffer
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void RenderTarget::setDepthTarget(const Texture& texture) const {
    // bind framebuffer
    glBindFramebuffer(GL_FRAMEBUFFER, id);

    // set frame buffer texture attachment
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT,
                           GL_TEXTURE_2D, texture.getId(), 0);

    // bind default framebuffer
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}
