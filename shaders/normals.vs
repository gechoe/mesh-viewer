#version 400

layout (location = 0) in vec3 vPos;
layout (location = 1) in vec3 vNormal;
layout (location = 2) in vec3 vUV;

uniform mat3 NormalMatrix;
uniform mat4 ModelViewMatrix;
uniform mat4 MVP;
uniform bool HasUV;

out vec3 vNormalPrime;

void main() {
   vNormalPrime.x = (vNormal.x + 1) / 2;
   vNormalPrime.y = (vNormal.y + 1) / 2;
   vNormalPrime.z = (vNormal.z + 1) / 2;

   gl_Position = MVP * vec4(vPos, 1.0);
}
