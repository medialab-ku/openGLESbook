#version 320 es
precision mediump float;

in vec3 v_normal;

layout(location = 0) out vec4 fragColor;

void main() {
    // output color using vertex normal
    fragColor = vec4(0.5 * v_normal + 0.5, 1.0);
}
