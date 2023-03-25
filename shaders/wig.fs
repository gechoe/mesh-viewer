#version 400

uniform sampler2D diffuseTexture;

in vec4 color;
in vec2 uv;

out vec4 FragColor;

void main()
{
    vec4 c = vec4(color * (texture(diffuseTexture, uv*10.0f).xyz, 1));
    FragColor = vec4(c);
}