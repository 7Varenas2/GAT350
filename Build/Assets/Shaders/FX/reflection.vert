#version 430 core 
 
in layout(location = 0) vec3 vposition;
in layout(location = 2) vec3 vnormal;
 
out vec3 reflection_dir;
out vec3 refraction_dir;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform float refraction_index;
 
void main()
{
	vec3 position = vec3(model * vec4(vposition, 1));
	vec3 normal = normalize(mat3(model) * vnormal);

	vec3 camera_position = vec3(inverse(view)[3]); // -3 -3 -3
	vec3 view_dir = normalize(position - camera_position);
	reflection_dir = reflect(view_dir, normal);
	
	refraction_dir = refract(view_dir, normal, 1.0 / refraction_index);
	//refraction_dir = vec3(0);

	mat4 mvp = projection * view * model; 
	gl_Position = mvp * vec4(vposition, 1.0);
}
// 4x4
// (3x3) = rotation / scale