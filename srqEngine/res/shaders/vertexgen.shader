#version 330 core
layout(location = 0) in vec3 aPos;
layout(location = 1) in vec2 texCoord;
out vec4 vertexColor;
out vec2 tex_C;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main() {
	gl_Position = projection * view * model * vec4(aPos, 1.0f);
	vertexColor = vec4(0.5f, 0.5f, 0.5f, 1.0f);
	tex_C = texCoord;
}