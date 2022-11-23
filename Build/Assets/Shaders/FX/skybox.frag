#version 430 core

in vec3 texcoord;

out vec4 fcolor; // pixel to draw

uniform samplerCube cubeMap;

void main()
{
	fcolor = texture(cubeMap, texcoord);

}
