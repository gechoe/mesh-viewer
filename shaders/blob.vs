#version 400

layout (location = 0) in vec3 vPos;
layout (location = 1) in vec3 vNormal;
layout (location = 2) in vec3 vUV;

uniform mat3 NormalMatrix;
uniform mat4 ModelViewMatrix;
uniform mat4 MVP;
uniform bool HasUV;

out vec3 coloring;

void main() {
   vec3 vNormalPrime;
   vNormalPrime.x = (vNormal.x + 1) / 2;
   vNormalPrime.y = (vNormal.y + 1) / 2;
   vNormalPrime.z = (vNormal.z + 1) / 2;

   coloring = 0.2 * vNormalPrime + (1 - 0.2) * vNormalPrime;
   // FragColor = vec4(1.0, 0.0, 0.0, 1.0);

   gl_Position = MVP * vec4(vPos, 1.0);
}