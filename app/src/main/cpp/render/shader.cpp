#include "shader.h"

Shader::Shader(const Shader::Type type, const std::string& source) {
    // create
    create(type);

    // set source
    setSource(source);

    // compile
    compile();
}

GLuint Shader::getId() const {
    return id;
}

void Shader::create(const Shader::Type type) {
    // create shader
    switch (type) {
        case Type::VERTEX:
            LOG_PRINT_DEBUG("Create vertex shader");
            id = glCreateShader(GL_VERTEX_SHADER);
            break;
        case Type::FRAGMENT:
            LOG_PRINT_DEBUG("Create fragment shader");
            id = glCreateShader(GL_FRAGMENT_SHADER);
            break;
        case Type::TESS_CONTROL:
            LOG_PRINT_DEBUG("Create tessellation control shader");
            id = glCreateShader(GL_TESS_CONTROL_SHADER);
            break;
        case Type::TESS_EVALUATION:
            LOG_PRINT_DEBUG("Create tessellation evaluation shader");
            id = glCreateShader(GL_TESS_EVALUATION_SHADER);
            break;
    }
    if (!id) LOG_PRINT_ERROR("Fail to create shader");
}

void Shader::setSource(const std::string &source) const {
    LOG_PRINT_DEBUG("Set source of shader");

    // set shader source
    const GLchar* glSource = source.c_str();
    glShaderSource(id, 1, &glSource, NULL);
}

void Shader::compile() const {
    LOG_PRINT_DEBUG("Compile shader");

    // compile shader
    glCompileShader(id);

    // check compile status
    GLint status;
    glGetShaderiv(id, GL_COMPILE_STATUS, &status);
    if (!status) {
        GLint infoLogLength;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &infoLogLength);
        if (infoLogLength > 0) {
            GLchar* infoLog = new GLchar[infoLogLength];
            glGetShaderInfoLog(id, infoLogLength, NULL, infoLog);
            LOG_PRINT_ERROR("Fail to compile shader: %s", infoLog);
            delete[] infoLog;
        }
    }
}
