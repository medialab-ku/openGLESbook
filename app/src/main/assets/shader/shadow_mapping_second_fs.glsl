#version 300 es
precision mediump float;
precision mediump sampler2DShadow;

uniform sampler2D colorMap;
uniform sampler2DShadow shadowMap;
uniform vec3 srcDiff;

in vec3 v_normal, v_light;
in vec2 v_texCoord;
in vec4 v_shadowCoord;

layout(location = 0) out vec4 fragColor;

const float bias = 0.005;

void main() {
    // normalization
    vec3 normal = normalize(v_normal);
    vec3 light = normalize(v_light);

    // diffuse term
    vec3 matDiff = texture(colorMap, v_texCoord).rgb;
    vec3 diff = max(dot(normal, light), 0.0) * srcDiff * matDiff;

    // visibility with bias
    vec4 biasVec = vec4(0.0, 0.0, bias * v_shadowCoord.w, 0.0);
    float visibility = textureProj(shadowMap, v_shadowCoord - biasVec);

    // output color using diffuse term with visibility
    fragColor = vec4(visibility * diff, 1.0);
}
