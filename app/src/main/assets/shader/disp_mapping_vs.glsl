#version 320 es

layout(location = 0) in vec3 position;
layout(location = 2) in vec2 texCoord;

out vec3 v_position;
out vec2 v_texCoord;

void main() {
    // object-space position
    v_position = position;

    // texture coordinates
    v_texCoord = texCoord;
}
