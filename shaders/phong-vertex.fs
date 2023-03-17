#version 400

in vec3 phongReflec;

out vec4 FragColor;

void main()
{
   FragColor = vec4(phongReflec.x, phongReflec.y, phongReflec.z, 1.0);
}
