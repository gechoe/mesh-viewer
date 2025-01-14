#version 400

layout (location = 0) in vec3 vPos;
layout (location = 1) in vec3 vNormal;
layout (location = 2) in vec3 vUV;

uniform mat3 NormalMatrix;
uniform mat4 ModelViewMatrix;
uniform mat4 MVP;
uniform bool HasUV;
uniform float uTime;

out float depth;
out vec3 newPos;

void main()
{
    newPos = vPos;

    // new vals for x, y, and z  generated by using uTime to get variation
    // sin() used on uTime to have values (for x, y, and z) within a defined range
    // or else the values of x, y, and z would continously increase.
    newPos.x += sin(uTime);
    newPos.y += sin(uTime);
    newPos.z += sin(uTime);

    depth = vPos.x;
    //vec3 = vec4(newPos, 1.0);
    //vec4(newPos + 0.05 * vNormal * sin(10 * uTime + newPos.x * 100.0), 1);

    gl_Position = MVP * vec4(vPos, 1.0);
}