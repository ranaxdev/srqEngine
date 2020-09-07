#version 330 core
out vec4 FragColor;

in vec4 vertexColor;
in vec2 tex_C;

uniform sampler2D logoTex;

void main() {
	vec4 texColor = texture(logoTex, tex_C);
	FragColor = texColor;
}