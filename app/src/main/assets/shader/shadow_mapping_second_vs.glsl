#version 300 es

uniform mat4 worldMat, viewMat, projMat;
uniform mat4 lightViewMat, lightProjMat;
uniform vec3 lightPos;

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 normal;
layout(location = 2) in vec2 texCoord;

out vec3 v_normal, v_light;
out vec2 v_texCoord;
out vec4 v_shadowCoord;

const mat4 tempMat = mat4(
        0.5, 0.0, 0.0, 0.0,
        0.0, 0.5, 0.0, 0.0,
        0.0, 0.0, 0.5, 0.0,
        0.5, 0.5, 0.5, 1.0
);

void main() {
    // world-space normal
    v_normal = normalize(transpose(inverse(mat3(worldMat))) * normal);

    // world-space position
    vec3 worldPos = (worldMat * vec4(position, 1.0)).xyz;

    // world-space light vector
    v_light = normalize(lightPos - worldPos);

    // texture coordinates
    v_texCoord = texCoord;

    // clip-space position
    gl_Position = projMat * viewMat * vec4(worldPos, 1.0);

    // shadow coordinates with bias
    v_shadowCoord = tempMat * lightProjMat * lightViewMat * vec4(worldPos, 1.0);
}
