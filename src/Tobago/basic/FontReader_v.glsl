#version 330 core
layout( location = 0) in vec2 spacecoord;
layout( location = 1) in vec2 theUV;

out vec2 UV;

void main(){
	UV = theUV;
	gl_Position.xyz = vec3(spacecoord,0);
}