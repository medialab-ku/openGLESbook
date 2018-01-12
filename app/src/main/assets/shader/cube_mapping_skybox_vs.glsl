#version 300 es

uniform mat4 worldMat, viewMat, projMat;

layout(location = 0) in vec3 position;

out vec3 v_texCoord;

void main() {
    // texture coordinates
    v_texCoord = position;

    // clip-space position
    gl_Position = projMat * viewMat * worldMat * vec4(position, 1.0);
}
