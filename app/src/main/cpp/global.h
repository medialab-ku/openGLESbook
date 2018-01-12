#ifndef OPENGLES_GLOBAL_H
#define OPENGLES_GLOBAL_H

#include <jni.h>
#include <android/asset_manager.h>
#include <android/asset_manager_jni.h>
#include <android/log.h>
#include <GLES3/gl32.h>
#include <GLES3/gl3ext.h>

#include <string>
#include <sstream>
#include <vector>
#include <unordered_map>
#include <regex>

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/transform.hpp>

#define LOG_TAG "OpenGL ES 3.2"
#define LOG_PRINT_DEBUG(...) __android_log_print(ANDROID_LOG_DEBUG, LOG_TAG, __VA_ARGS__)
#define LOG_PRINT_ERROR(...) __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, __VA_ARGS__)
#define SHADOW_MAP_SIZE 1024

struct Vertex {
    glm::vec3 pos; // position
    glm::vec3 nor; // normal
    glm::vec2 tex; // texture coordinates
    glm::vec3 tan; // tangent
};
typedef GLushort Index;

struct Texel {
    GLubyte r; // red
    GLubyte g; // green
    GLubyte b; // blue
    GLubyte a; // alpha
};

struct ObjData {
    std::vector<Vertex> vertices;
    std::vector<Index> indices;
};

struct TexData {
    std::vector<Texel> texels;
    GLsizei width;
    GLsizei height;
};
typedef TexData PngData;

#endif // OPENGLES_GLOBAL_H
