#version 400

in vec3 coloring;

out vec4 FragColor;

void main()
{
   FragColor = vec4(coloring, 0.5);
}