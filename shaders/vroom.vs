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

    vec3 newPos = vPos;

    // new vals for x, y, and z  generated by using uTime to get variation
    // sin() used on uTime to have values (for x, y, and z) within a defined range
    // or else the values of x, y, and z would continously increase.
    newPos.x += sin(uTime) * 2;
    // newPos.y += sin(uTime);
    // newPos.z += sin(uTime);

    float wiggleHeight = sin(numTriangles * 0.001);

    gl_Position = MVP * vec4(newPos, 1.0);
}