#version 330 core
layout(location = 0) in vec3 aPos;
layout(location = 1) in vec2 aTex;
layout(location = 2) in vec3 aNormal;

out vec2 tc; // texture coord output
out vec3 FragPos;
out vec3 Normal;

uniform mat4 u_VP;
uniform mat4 u_M;

void main() {

	FragPos = vec3(u_M * vec4(aPos, 1.0f));
	gl_Position = u_VP * vec4(FragPos, 1.0f);
	Normal = mat3(transpose(inverse(u_M))) * aNormal;
	tc = aTex;
}
