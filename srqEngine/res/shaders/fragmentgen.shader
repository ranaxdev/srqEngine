#version 330 core
out vec4 FragColor;

in vec4 vertexColor;
in vec2 tc; //input tex coord from vertex shader

uniform sampler2D thetex;


void main() {

	FragColor = texture(thetex, tc);
}