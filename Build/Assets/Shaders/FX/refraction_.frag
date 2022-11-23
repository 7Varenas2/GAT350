#version 430 core
 
in vec3 reflection_dir;
in vec3 refraction_dir;
 
out vec4 fcolor;
 
uniform float interp;
 
layout (binding = 0) uniform samplerCube cubeMap;
 
void main()
{
	vec3 reflect_color = texture(cubeMap, reflection_dir).rgb;
	vec3 refract_color = texture(cubeMap, refraction_dir).rgb;
	fcolor = vec4(mix(reflect_color, refract_color, interp), 1);
}
