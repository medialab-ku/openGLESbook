#version 300 es
precision mediump float;

uniform samplerCube cubeMap;

in vec3 v_normal, v_view;

layout(location = 0) out vec4 fragColor;

void main() {
    // normalization
    vec3 normal = normalize(v_normal);
    vec3 view = normalize(v_view);

    // reflection vector
    vec3 refl = 2.0 * normal * dot(normal, view) - view;

    // output color from cube map texture
    fragColor = texture(cubeMap, refl);
}
