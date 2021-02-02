#version 330 core
in vec3 Normal;
in vec2 tc;
in vec3 FragPos;

out vec4 FragColor;


uniform sampler2D thetex;
uniform vec3 light_color;
uniform vec3 light_pos;
uniform float intensity;
void main() {
	// ambience lighting
	
	vec3 ambience = intensity * texture(thetex, tc).rgb;

	// diffuse lighting
	vec3 normal = normalize(Normal);
	vec3 light_dir = normalize(light_pos - FragPos);	
	float diffuse_factor = max(dot(normal, light_dir), 0.0f);
	vec3 diffuse = diffuse_factor * light_color * texture(thetex, tc).rgb;

	vec3 final = ambience + diffuse;
	FragColor = vec4(final, 1.0f);
}