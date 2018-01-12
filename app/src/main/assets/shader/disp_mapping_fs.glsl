#version 320 es
precision mediump float;

uniform sampler2D colorMap;

in vec2 v_texCoord;

layout(location = 0) out vec4 fragColor;

void main() {
    // output color from color map
    fragColor = vec4(texture(colorMap, v_texCoord).rgb, 1.0);
}
