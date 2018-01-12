#version 320 es

layout(quads) in;

uniform sampler2D heightMap;
uniform float dispFactor;
uniform mat4 worldMat, viewMat, projMat;

in vec3 es_position[];
in vec2 es_texCoord[];

out vec2 v_texCoord;

void main() {
    float u = gl_TessCoord.x;
    float v = gl_TessCoord.y;

    // bilinearly interpolated object-space position
    vec3 lowerPos = mix(es_position[0], es_position[1], u);
    vec3 upperPos = mix(es_position[2], es_position[3], u);
    vec3 position = mix(lowerPos, upperPos, v);

    // bilinearly interpolated texture coordinates
    vec2 lowerTex = mix(es_texCoord[0], es_texCoord[1], u);
    vec2 upperTex = mix(es_texCoord[2], es_texCoord[3], u);
    v_texCoord = mix(lowerTex, upperTex, v);

    // get height from height map
    float height = texture(heightMap, v_texCoord).z;

    // add height to position with displacement factor
    position += dispFactor * vec3(0.0, 0.0, height);

    // clip-space position
    gl_Position = projMat * viewMat * worldMat * vec4(position, 1.0);
}
