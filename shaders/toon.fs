#version 400

in float intensity;

out vec4 FragColor;

void main()
{
	vec4 color;

	if (intensity > 0.95) {
		color = vec4(0.78, 0.5, 1.0, 1.0); // Lightest pink-red color
	} else if (intensity > 0.5) {
		color = vec4(0.46, 0.3, 0.6, 1.0); // Second lightest pink-red color
	} else if (intensity > 0.25) {
		color = vec4(0.3, 0.2, 0.4, 1.0); // Second darkest pink-red color
	} else {
		color = vec4(0.1, 0, 0.2, 1.0); // Darkest pink-red color
	}

	FragColor = color;
}