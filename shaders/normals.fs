#version 400

in vec3 vNormalPrime;

out vec4 FragColor;

void main()
{
   // FragColor = vec4(1.0, 0.0, 0.0, 1.0);
   FragColor = vec4(vNormalPrime.x, vNormalPrime.y, vNormalPrime.z, 1.0);
}
