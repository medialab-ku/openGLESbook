#version 300 es

uniform mat4 worldMat, viewMat, projMat;
uniform vec3 eyePos, lightDir;

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 normal;
layout(location = 2) in vec2 texCoord;
layout(location = 3) in vec3 tangent;

out vec3 v_viewTS, v_lightTS;
out vec2 v_texCoord;

void main() {
    // world-space position
    vec3 worldPos = (worldMat * vec4(position, 1.0)).xyz;

    // world-space TBN
    vec3 Nor = normalize(transpose(inverse(mat3(worldMat))) * normal);
    vec3 Tan = normalize(transpose(inverse(mat3(worldMat))) * tangent);
    vec3 Bin = cross(Nor, Tan);

    // TBN matrix
    mat3 tbnMat = transpose(mat3(Tan, Bin, Nor)); // row major

    // tangent-space view vector
    v_viewTS = tbnMat * normalize(eyePos - worldPos);

    // tangent-space light vector
    v_lightTS = tbnMat * normalize(lightDir);

    // texture coordinates
    v_texCoord = texCoord;

    // clip-space position
    gl_Position = projMat * viewMat * vec4(worldPos, 1.0);
}
