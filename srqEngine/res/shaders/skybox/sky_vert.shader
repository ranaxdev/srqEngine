#version 330 core
layout(location = 0) in vec3 aPos;

out vec3 tex_coords;

uniform mat4 u_P;
uniform mat4 u_V;

void main() {
	tex_coords = aPos;
	vec4 pos = u_P * u_V * vec4(aPos, 1.0f);
	gl_Position = pos.xyww;
}