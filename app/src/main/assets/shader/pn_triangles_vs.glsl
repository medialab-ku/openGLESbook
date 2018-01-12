#version 320 es

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 normal;

out vec3 v_position;
out vec3 v_normal;

void main() {
    // object-space position
    v_position = position;

    // object-space normal
    v_normal = normal;
}
