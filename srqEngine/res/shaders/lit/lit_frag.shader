// Fragment shader for objects affected by light sources
#version 330 core
in vec3 Normal;
in vec3 FragPos;

out vec4 FragColor;

uniform vec3 obj_color;
uniform vec3 light_color;
uniform vec3 light_pos;
uniform vec3 view_pos;
uniform float intensity;
void main() {
	// ambience lighting
	
	vec3 ambience = intensity * light_color;

	// diffuse lighting
	vec3 normal = normalize(Normal);
	vec3 light_dir = normalize(light_pos - FragPos);
	float diffuse_factor = max(dot(normal, light_dir), 0.0f);
	vec3 diffuse = diffuse_factor * light_color;

	// specular lighting
	float spec_intensity = 0.6f;
	vec3 view_dir = normalize(view_pos - FragPos);
	vec3 reflection = reflect(-light_dir, normal);
	float spec_factor = pow(max(dot(view_dir, reflection), 0.0f), 32);
	vec3 specular = spec_intensity * spec_factor * light_color;

	vec3 final = (ambience + diffuse + specular) * obj_color;
	FragColor = vec4(final, 1.0f);
}
