#version 330 core
layout (location = 0) in vec3 aPos;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

out vec4 vertexColor;

void main()
{
	gl_Position = projection * view * model * vec4(aPos, 1.0f);
	vec3 dir = aPos / max(length(aPos), 0.0001);
	vec3 cleanColor = 0.5 + 0.5 * dir;
	vertexColor = vec4(cleanColor, 1.0);
}
