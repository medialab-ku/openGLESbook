#version 320 es

layout(vertices = 1) out;

uniform float tessLevel;

in vec3 v_position[];
in vec3 v_normal[];

struct PNT {
    vec3 P300, P030, P003; // corner control points
    vec3 P210, P120, P021, P012, P102, P201; // mid-edge control points
    vec3 P111; // inner control point
    vec3 N1, N2, N3; // normals
};
out patch PNT pnTri;

vec3 displace(vec3 p1, vec3 p2, vec3 n1);

void main() {
    pnTri.N1 = v_normal[0];
    pnTri.N2 = v_normal[1];
    pnTri.N3 = v_normal[2];

    pnTri.P300 = v_position[0];
    pnTri.P030 = v_position[1];
    pnTri.P003 = v_position[2];

    pnTri.P210 = displace(pnTri.P300, pnTri.P030, pnTri.N1);
    pnTri.P120 = displace(pnTri.P030, pnTri.P300, pnTri.N2);
    pnTri.P021 = displace(pnTri.P030, pnTri.P003, pnTri.N2);
    pnTri.P012 = displace(pnTri.P003, pnTri.P030, pnTri.N3);
    pnTri.P102 = displace(pnTri.P003, pnTri.P300, pnTri.N3);
    pnTri.P201 = displace(pnTri.P300, pnTri.P003, pnTri.N1);

    vec3 V = (pnTri.P300 + pnTri.P030 + pnTri.P003) / 3.0;
    vec3 E = (pnTri.P210 + pnTri.P120 + pnTri.P021
            + pnTri.P012 + pnTri.P102 + pnTri.P201) / 6.0;
    pnTri.P111 = E + (E - V) / 2.0;

    gl_TessLevelOuter[0] = tessLevel;
    gl_TessLevelOuter[1] = tessLevel;
    gl_TessLevelOuter[2] = tessLevel;
    gl_TessLevelInner[0] = tessLevel;
}

vec3 displace(vec3 p1, vec3 p2, vec3 n1) {
    return (2.0 * p1 + p2) / 3.0 - dot(n1, (p2 - p1) / 3.0) * n1;
}
