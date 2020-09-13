#version 330 core
layout(location = 0) in vec3 aPos;


out vec4 vertexColor;
uniform mat4 u_VP;

void main() {
	gl_Position = u_VP * vec4(aPos, 1.0f);
	vertexColor = vec4(1.0f,0.0f,0.0f, 1.0f);
	
}