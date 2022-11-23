#version 430 core 
 
in layout(location = 0) vec3 vposition;
in layout(location = 2) vec3 vnormal;
 
out vec3 refraction_dir;
out vec3 reflection_dir;

uniform float refractiveIndex = 1.0;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform vec3 reflection_index;
 
void main()
{
	vec3 position = vec3(model * vec4(vposition, 1));
	vec3 normal = normalize(mat3(model) * vnormal);

	vec3 camera_position = vec3(inverse(view)[3]); // -3 -3 -3
	vec3 view_dir = normalize(position - camera_position);
	refraction_dir = refract(view_dir, normal, 1.5);

	reflection_dir = reflect(view_dir, normal);
	mat4 mvp = projection * view * model; // Model is breaking or not showing when multiplied
	gl_Position = mvp * vec4(vposition, 1.0);
}
// 4x4
// (3x3) = rotation / scale