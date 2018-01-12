#include "program.h"

Program::Program(const std::vector<Shader>& shaders) {
    // create
    create();

    // attach shaders
    attachShaders(shaders);

    // link
    link();
}

void Program::use() const {
    // use program
    glUseProgram(id);
}

GLuint Program::getId() const {
    return id;
}

void Program::create() {
    LOG_PRINT_DEBUG("Create program");

    // create program
    id = glCreateProgram();
    if (!id) LOG_PRINT_ERROR("Fail to create program");
}

void Program::attachShaders(const std::vector<Shader>& shaders) const {
    LOG_PRINT_DEBUG("Attach shaders to program");

    // attach shaders
    for (const Shader& shader : shaders) glAttachShader(id, shader.getId());
}

void Program::link() const {
    LOG_PRINT_DEBUG("Link program");

    // link program
    glLinkProgram(id);

    // check link status
    GLint status;
    glGetProgramiv(id, GL_LINK_STATUS, &status);
    if (!status) {
        GLint infoLogLength;
        glGetProgramiv(id, GL_INFO_LOG_LENGTH, &infoLogLength);
        if (infoLogLength > 0) {
            GLchar* infoLog = new GLchar[infoLogLength];
            glGetProgramInfoLog(id, infoLogLength, NULL, infoLog);
            LOG_PRINT_ERROR("Fail to link program: %s", infoLog);
            delete[] infoLog;
        }
    }
}
