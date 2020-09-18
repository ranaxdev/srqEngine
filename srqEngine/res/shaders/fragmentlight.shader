#version 330 core
out vec4 fragColor;

in vec3 Normal;
in vec3 FragPos;

uniform vec3 lightColor;
uniform vec3 objColor;
uniform vec3 lightPos;

void main() {
	float ambientPower = 0.1;
	vec3 ambient = ambientPower * lightColor;

	vec3 norm = normalize(Normal);
	vec3 light_dir = normalize(lightPos - FragPos);
	float diff = max(dot(norm, light_dir), 0.0f);
	vec3 diffuse = diff * lightColor;

	vec3 result = (ambient + diffuse) * objColor;

	fragColor = vec4(result, 1.0f);
}