// Vertex shader for objects that are light sources
#version 330 core
layout(location = 0) in vec3 aPos;
layout(location = 1) in vec2 aTex;

uniform mat4 u_VP;
uniform mat4 u_M;

void main() {
	gl_Position = u_VP * u_M * vec4(aPos, 1.0f);
}