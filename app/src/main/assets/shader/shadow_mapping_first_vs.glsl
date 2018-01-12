#version 300 es

uniform mat4 worldMat;
uniform mat4 lightViewMat, lightProjMat;

layout(location = 0) in vec3 position;

void main() {
    // draw shadow map
    gl_Position = lightProjMat * lightViewMat * worldMat * vec4(position, 1.0);
}
