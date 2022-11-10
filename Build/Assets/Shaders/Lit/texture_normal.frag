#version 430 core

in vec3 position;
in vec2 texcoord;
in mat3 tbn;

out vec4 fcolor; // pixel to draw

struct Light
{
	vec3 ambient;
	vec3 color;
	vec4 position;
};

struct Material
{
	vec3 color;
	float shininess;
	vec2 uv_tiling;
	vec2 uv_offset;
};
 
uniform Light light;
uniform Material material;

layout (binding = 0) uniform sampler2D diffuseMap; // Diffuse map
layout (binding = 1) uniform sampler2D normalMap; // Specular map
layout (binding = 2) uniform sampler2D immisiveMap; // Immisive map

void phong(vec3 position, vec3 normal, out vec3 ambient, out vec3 diffuse, out vec3 specular)
{
	// Ambient
	ambient = light.ambient * material.color;

	// Calculate light direction (unit vector)
	vec3 light_dir = normalize(vec3 (light.position) - position);

	// Calculate light intensity with dot product (normal * light direction)
	float intensity = max(dot(light_dir, normal),0);
	diffuse = light.color * material.color * intensity;

	// SPECULAR
	specular = vec3(0);
	if (intensity > 0)
	{
		vec3 reflection = reflect(-light_dir, normal);
		vec3 view_dir = normalize(-vec3(position));
		intensity = max(dot(reflection, view_dir), 0);
		intensity = pow(intensity, material.shininess);
		specular = light.color * material.color * intensity;
	}

}

void main()
{

	vec2 ttexcoord = (texcoord * material.uv_tiling) + material.uv_offset;
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;

	vec3 normal = texture(normalMap, ttexcoord).rgb; // Originally 0 - 1 
	normal = (normal * 2) - 1; // Currently 0 - 2 , bc of multiplication with 2, but adding - 1 makes its -1 - 1
	normal = normalize(tbn * normal);

	phong(position, normal, ambient, diffuse, specular);

	vec4 texture_color = texture(diffuseMap, ttexcoord);

	//fcolor = texture_color; // No Lighting
	fcolor = vec4(ambient + diffuse, 1) * texture_color + vec4(specular,1); // Lighting
}
