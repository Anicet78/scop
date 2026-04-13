#version 330 core

in vec4 vertexColor;
out vec4 FragColor;

uniform float coloredOpacity;
uniform float smoothOpacity;
uniform float imgOpacity;

vec3 hsvToRgb(float h, float s, float v) {
	vec3 rgb = clamp(abs(mod(h * 6.0 + vec3(0.0, 4.0, 2.0), 6.0) - 3.0) - 1.0, 0.0, 1.0);
	return v * mix(vec3(1.0), rgb, s);
}

void main()
{
	FragColor = vec4(0, 0, 0, 1);

	if (coloredOpacity != 0.0f) {
		float hue = mod(float(gl_PrimitiveID) * 0.618033988749895, 1.0);
		float sat = 0.30 + mod(float(gl_PrimitiveID) * 0.211, 0.20);
		float val = 0.97 + mod(float(gl_PrimitiveID) * 0.137, 0.15);
		vec3 triangleColor = hsvToRgb(hue, sat, val) * coloredOpacity;
		FragColor.x += triangleColor.x;
		FragColor.y += triangleColor.y;
		FragColor.z += triangleColor.z;
	}
	if (smoothOpacity != 0.0f) {
		FragColor.x += vertexColor.x * smoothOpacity;
		FragColor.y += vertexColor.y * smoothOpacity;
		FragColor.z += vertexColor.z * smoothOpacity;
	}
}
