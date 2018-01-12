#version 300 es
precision mediump float;

in vec3 v_normal;
in vec2 v_texCoord;

layout(location = 0) out vec4 fragColor;

void main() {
    // output color using vertex normal
    fragColor = vec4(0.5 * v_normal + 0.5, 1.0);
}
