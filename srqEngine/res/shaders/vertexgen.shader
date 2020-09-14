#version 330 core
layout(location = 0) in vec3 aPos;
layout(location = 1) in vec2 aTex;

out vec2 tc; // texture coord output
out vec4 vertexColor;
uniform mat4 u_VP;
uniform mat4 u_M;

void main() {

	gl_Position = u_VP * u_M * vec4(aPos, 1.0f);
	vertexColor = vec4(aPos,1.0f) * 0.5 + vec4(0.5f,0.5f,0.5f, 1.0f);
	tc = aTex;
}
