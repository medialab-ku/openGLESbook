#version 300 es
precision mediump float;

uniform samplerCube cubeMap;

in vec3 v_texCoord;

layout(location = 0) out vec4 fragColor;

void main() {
    // output color from cube map texture
    fragColor = texture(cubeMap, v_texCoord);
}
