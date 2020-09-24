/* Fragment shader for objects affected by light sources */
#version 330 core
out vec4 fragColor;

in vec3 normal;
in vec3 fragPos;

uniform vec3 lightPos;
uniform vec3 objectColor;
uniform vec3 lightColor;


void main() {

	// ambience
	float ambience = 0.1;
	vec3 ambient = ambience * lightColor;

	// diffuse
	vec3 norm = normalize(normal);
	vec3 lightDir = normalize(lightPos - fragPos);
	float d = max(dot(norm, lightDir), 0.0f);
	vec3 diffuse = d * lightColor;


	vec3 result = (ambient + diffuse) * objectColor;
	fragColor = vec4(result, 1.0f);
}