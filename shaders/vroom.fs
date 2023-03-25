#version 400

uniform float uTime;

in vec3 vNormalPrime;

out vec4 FragColor;

void main()
{
    vec3 color = vec3(0.2, 0.1, 0.2);
    FragColor = vec4(vNormalPrime.x, vNormalPrime.y, vNormalPrime.z, 1.0);
}