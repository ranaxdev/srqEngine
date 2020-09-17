#version 330 core
out vec4 fragColor;

uniform vec3 obj_light;
uniform vec3 lightColor;

void main() {
	fragColor = vec4(lightColor * obj_light, 1.0f);
}