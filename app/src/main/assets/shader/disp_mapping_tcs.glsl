#version 320 es

layout(vertices = 4) out;

uniform float tessLevel;

in vec3 v_position[];
in vec2 v_texCoord[];

out vec3 es_position[];
out vec2 es_texCoord[];

void main() {
    // object-space position
    es_position[gl_InvocationID] = v_position[gl_InvocationID];

    // texture coordinates
    es_texCoord[gl_InvocationID] = v_texCoord[gl_InvocationID];

    // tessellation levels
    gl_TessLevelOuter[0] = tessLevel;
    gl_TessLevelOuter[1] = tessLevel;
    gl_TessLevelOuter[2] = tessLevel;
    gl_TessLevelOuter[3] = tessLevel;
    gl_TessLevelInner[0] = tessLevel;
    gl_TessLevelInner[1] = tessLevel;
}
