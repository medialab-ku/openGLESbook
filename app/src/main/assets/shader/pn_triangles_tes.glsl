#version 320 es

layout(triangles) in;

uniform mat4 worldMat, viewMat, projMat;

struct PNT {
    vec3 P300, P030, P003; // corner control points
    vec3 P210, P120, P021, P012, P102, P201; // mid-edge control points
    vec3 P111; // inner control point
    vec3 N1, N2, N3; // normals
};
in patch PNT pnTri;

out vec3 v_normal;

void main() {
    // powers of barycentric coordinates
    float u1 = gl_TessCoord.x, v1 = gl_TessCoord.y, w1 = gl_TessCoord.z;
    float u2 = pow(u1, 2.0), v2 = pow(v1, 2.0), w2 = pow(w1, 2.0);
    float u3 = pow(u1, 3.0), v3 = pow(v1, 3.0), w3 = pow(w1, 3.0);

    // position
    vec3 position = vec3(0.0);
    position += pnTri.P300 * u3 + pnTri.P030 * v3 + pnTri.P003 * w3;
    position += pnTri.P210 * 3.0 * u2 * v1 + pnTri.P120 * 3.0 * u1 * v2;
    position += pnTri.P021 * 3.0 * v2 * w1 + pnTri.P012 * 3.0 * v1 * w2;
    position += pnTri.P102 * 3.0 * w2 * u1 + pnTri.P201 * 3.0 * w1 * u2;
    position += pnTri.P111 * 6.0 * u1 * v1 * w1;

    // normal
    vec3 normal = pnTri.N1 * u1 + pnTri.N2 * v1 + pnTri.N3 * w1;
    v_normal = normalize(transpose(inverse(mat3(worldMat))) * normal);

    // clip-space position
    gl_Position = projMat * viewMat * worldMat * vec4(position, 1.0);
}
