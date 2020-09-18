#version 330 core
layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 aNormal;

out vec3 Normal;
out vec3 FragPos;

uniform mat4 u_M;
uniform mat4 u_VP;

void main() {
	gl_Position = u_VP * u_M * vec4(aPos, 1.0f);
	FragPos = vec3(u_M * vec4(aPos, 1.0f));
	Normal = aNormal;
}
