#version 400

layout (location = 0) in vec3 vPos;
layout (location = 1) in vec3 vNormal;

uniform mat4 MVP;
uniform float uTime;
uniform int numTriangles;

out vec3 vNormalPrime;

void main() {
    vNormalPrime.x = sin((vNormal.x + 1));
    vNormalPrime.y = sin((vNormal.y + 1) / 2);
    vNormalPrime.z = sin((vNormal.z + 1));

    float wiggleHeight = sin(numTriangles * 0.001);

    vec3 pos = vPos + wiggleHeight * abs(cos(100000 * uTime + vPos.x * 100.0));
    gl_Position = MVP * vec4(pos, 1.0);
}