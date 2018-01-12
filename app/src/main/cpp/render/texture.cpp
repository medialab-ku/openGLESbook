#include "texture.h"

Texture::Texture(const Texture::Type type, const TexData& texData) : type(type) {

    // create
    create();

    // set uniform
    setUniform();

    // set data
    setData(texData);
}

void Texture::update(const Program& program) const {
    // active and bind texture
    switch (type) {
        case Type::ColorMap:
            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, id);
            break;
        case Type::NormalMap:
            glActiveTexture(GL_TEXTURE1);
            glBindTexture(GL_TEXTURE_2D, id);
            break;
        case Type::ShadowMap:
            glActiveTexture(GL_TEXTURE2);
            glBindTexture(GL_TEXTURE_2D, id);
            break;
        case Type::CubeMap:
            glActiveTexture(GL_TEXTURE3);
            glBindTexture(GL_TEXTURE_CUBE_MAP, id);
            break;
        case Type::HeightMap:
            glActiveTexture(GL_TEXTURE4);
            glBindTexture(GL_TEXTURE_2D, id);
            break;
    }

    // update uniform
    uniform.update(program);
}

GLuint Texture::getId() const {
    return id;
}

void Texture::create() {
    LOG_PRINT_DEBUG("Create texture");

    // generate texture
    glGenTextures(1, &id);
    if (!id) LOG_PRINT_ERROR("Fail to create texture");
}

void Texture::setUniform() {
    // set uniform
    switch (type) {
        case Type::ColorMap:
            uniform = Uniform(Uniform::Type::INT, "colorMap", &type);
            break;
        case Type::NormalMap:
            uniform = Uniform(Uniform::Type::INT, "normalMap", &type);
            break;
        case Type::ShadowMap:
            uniform = Uniform(Uniform::Type::INT, "shadowMap", &type);
            break;
        case Type::CubeMap:
            uniform = Uniform(Uniform::Type::INT, "cubeMap", &type);
            break;
        case Type::HeightMap:
            uniform = Uniform(Uniform::Type::INT, "heightMap", &type);
            break;
    }
}

void Texture::setData(const TexData& texData) const {
    // check type
    switch (type) {
        case Type::ColorMap:
            LOG_PRINT_DEBUG("Set color map texture data");

            // bind texture
            glBindTexture(GL_TEXTURE_2D, id);

            // set texture data
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, texData.width, texData.height,
                         0, GL_RGBA, GL_UNSIGNED_BYTE, texData.texels.data());
            glGenerateMipmap(GL_TEXTURE_2D);

            // set texture parameters
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
            break;
        case Type::NormalMap:
            LOG_PRINT_DEBUG("Set normal map texture data");

            // bind texture
            glBindTexture(GL_TEXTURE_2D, id);

            // set texture data
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, texData.width, texData.height,
                         0, GL_RGBA, GL_UNSIGNED_BYTE, texData.texels.data());

            // set texture parameters
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
            break;
        case Type::ShadowMap:
            LOG_PRINT_DEBUG("Set shadow map texture data");

            // bind texture
            glBindTexture(GL_TEXTURE_2D, id);

            // set texture data
            glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT16, SHADOW_MAP_SIZE, SHADOW_MAP_SIZE,
                         0, GL_DEPTH_COMPONENT, GL_UNSIGNED_SHORT, NULL);

            // set texture parameters
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_MODE, GL_COMPARE_REF_TO_TEXTURE);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_FUNC, GL_LEQUAL);
            break;
        case Type::CubeMap:
            LOG_PRINT_DEBUG("Set cube map texture data");

            // bind texture
            glBindTexture(GL_TEXTURE_CUBE_MAP, id);

            // set texture data
            for (unsigned int i = 0; i < 6; i++)
                glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGBA, texData.width, texData.height,
                             0, GL_RGBA, GL_UNSIGNED_BYTE, texData.texels.data() + texData.texels.size() * i / 6);

            // set texture parameters
            glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            break;
        case Type::HeightMap:
            LOG_PRINT_DEBUG("Set height map texture data");

            // bind texture
            glBindTexture(GL_TEXTURE_2D, id);

            // set texture data
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, texData.width, texData.height,
                         0, GL_RGBA, GL_UNSIGNED_BYTE, texData.texels.data());

            // set texture parameters
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
            break;
    }
}
