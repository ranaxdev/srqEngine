#version 330 core
layout(location = 0) in vec3 vPos;
layout(location = 4) in vec4 aPos;

out float life;

uniform mat4 u_M;
uniform mat4 u_VP;
uniform float size;

void main() {
	vec4 pos = u_M * vec4(aPos.xyz, 1);
	pos.xy += size * (vPos.xy - vec2(0.5));
	gl_Position = u_VP * pos;
	life = aPos.w;
}