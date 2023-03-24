#version 400

in vec3 phongReflec;

out vec4 FragColor;

void main()
{
   FragColor = vec4(phongReflec, 1.0);
}