/* Vertex shader for objects that are affected by light sources */
#version 330 core
layout(location = 0) in vec3 aPos;
layout(location = 1) in vec2 aTex;
layout(location = 2) in vec3 aNorm;

// fragment uniforms
out vec3 fragPos;
out vec3 normal;

// MVP uniforms
uniform mat4 u_VP;
uniform mat4 u_M;

void main() {
	
	fragPos = vec3(u_M * vec4(aPos, 1.0f));
	normal = aNorm;

	gl_Position = u_VP * u_M * vec4(aPos, 1.0f);

}

