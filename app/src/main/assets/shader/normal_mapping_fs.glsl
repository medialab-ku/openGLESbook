#version 300 es
precision mediump float;

uniform sampler2D colorMap, normalMap;
uniform vec3 matSpec, matAmbi, matEmit; // Ms, Ma, Me
uniform float matSh; // shininess
uniform vec3 srcDiff, srcSpec, srcAmbi; // Sd, Ss, Sa
uniform vec3 lightDir; // directional light

in vec3 v_view;
in vec2 v_texCoord;

layout(location = 0) out vec4 fragColor;

void main() {
    // fetch normal from normal map
    vec3 normal = normalize(2.0 * texture(normalMap, v_texCoord).xyz - 1.0);

    // normalization
    vec3 view = normalize(v_view);
    vec3 light = normalize(lightDir);

    // diffuse term
    vec3 matDiff = texture(colorMap, v_texCoord).rgb;
    vec3 diff = max(dot(normal, light), 0.0) * srcDiff * matDiff;

    // specular term
    vec3 refl = 2.0 * normal * dot(normal, light) - light;
    vec3 spec = pow(max(dot(refl, view), 0.0), matSh) * srcSpec * matSpec;

    // ambient term
    vec3 ambi = srcAmbi * matAmbi;

    // output color using phong lighting
    fragColor = vec4(diff + spec + ambi + matEmit, 1.0);
}
