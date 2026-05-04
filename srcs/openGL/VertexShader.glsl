#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

out vec4 vertexColor;
out vec3 localPos;
out vec3 localNormal;

void main()
{
	gl_Position = projection * view * model * vec4(aPos, 1.0f);

	vec3 dir = aPos / max(length(aPos), 0.0001);
	vec3 cleanColor = 0.5 + 0.5 * dir;
	vertexColor = vec4(cleanColor, 1.0);

	localPos = aPos;
	localNormal = aNormal;
}
