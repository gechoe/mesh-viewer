#version 400

uniform float uTime;

in vec3 vNormalPrime;

out vec4 FragColor;

void main()
{
    vec3 color = vec3(0.2, 0.1, 0.2);
    FragColor = vec4(vNormalPrime.x + abs(sin(uTime)),
        vNormalPrime.y + (abs(sin(uTime)) / 2),
        vNormalPrime.z + abs(sin(uTime)), 1.0);
}