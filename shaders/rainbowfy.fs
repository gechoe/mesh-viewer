#version 400

in float depth;
in vec3 newPos;

out vec4 FragColor;

void main()
{
    // FragColor = vec4(1.0, 0.0, 0.0, 1.0);
    vec3 colorOne = vec3(0.4 + newPos.x, 0.4 + newPos.y, 0.97 + newPos.z);
    vec3 colorTwo = vec3(0.82 + newPos.x, 0.26 + newPos.y, 0.77 + newPos.z);

    vec3 mixedColor = mix(colorOne, colorTwo, depth);
    FragColor = vec4(mixedColor, 1.0);
}