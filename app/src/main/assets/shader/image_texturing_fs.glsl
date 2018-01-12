#version 300 es
precision mediump float;

uniform sampler2D colorMap;

in vec2 v_texCoord;

layout(location = 0) out vec4 fragColor;

void main() {
    // output color from texture image
    fragColor = texture(colorMap, v_texCoord);
}
