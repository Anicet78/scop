#version 330 core

in vec4 vertexColor;
in vec3 localNormal;
in vec3 localPos;
out vec4 FragColor;

uniform float coloredOpacity;
uniform float smoothOpacity;
uniform float imgOpacity;
uniform sampler2D tex;

vec3 hsvToRgb(float h, float v) {
	vec3 rgb = clamp(abs(mod(h * 6.0 + vec3(0.0, 4.0, 2.0), 6.0) - 3.0) - 1.0, 0.0, 1.0);
	return v * mix(vec3(1.0), rgb, 0.0);
}

void main()
{
	FragColor = vec4(0, 0, 0, 1);

	if (coloredOpacity != 0.0f) {
		float hue = mod(float(gl_PrimitiveID) * 0.618033988749895, 1.0);
		float val = 0.15 + mod(float(gl_PrimitiveID) * 0.900, 0.55);
		vec3 triangleColor = hsvToRgb(hue, val) * coloredOpacity;
		FragColor.x += triangleColor.x;
		FragColor.y += triangleColor.y;
		FragColor.z += triangleColor.z;
	}
	if (smoothOpacity != 0.0f) {
		FragColor.x += vertexColor.x * smoothOpacity;
		FragColor.y += vertexColor.y * smoothOpacity;
		FragColor.z += vertexColor.z * smoothOpacity;
	}
	if (imgOpacity != 0.0f) {
		vec3 blend = pow(abs(localNormal), vec3(8.0f));
		blend /= (blend.x + blend.y + blend.z);
		vec4 tx = texture(tex, localPos.yz);
		vec4 ty = texture(tex, localPos.xz);
		vec4 tz = texture(tex, localPos.xy);
		vec4 imgColor = tx * blend.x + ty * blend.y + tz * blend.z;
		FragColor += imgColor * imgOpacity;
	}
}
