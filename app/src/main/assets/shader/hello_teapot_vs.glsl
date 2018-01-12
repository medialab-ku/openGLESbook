#version 300 es

uniform mat4 worldMat, viewMat, projMat;

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 normal;
layout(location = 2) in vec2 texCoord;

out vec3 v_normal;
out vec2 v_texCoord;

void main() {
    // clip-space position
    gl_Position = projMat * viewMat * worldMat * vec4(position, 1.0);

    // world-space vertex normal
    v_normal = normalize(transpose(inverse(mat3(worldMat))) * normal);

    // texture coordinates
    v_texCoord = texCoord;
}
