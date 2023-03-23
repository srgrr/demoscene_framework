#version 330 core

layout(location = 0) in vec3 Position;
layout(location = 1) in vec3 vcolor;
out vec3 FColor;
uniform mat4 mitad;

void main()
{
	vec4 v = vec4(Position,1);
	gl_Position = (mitad*v);
	FColor = vcolor + gl_Position.xyz * 4;
}