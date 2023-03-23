#version 330 core
in vec2 UV;
uniform sampler2D theTex;
out vec4 Color;

void main(){
		Color = texture2D(theTex, vec2( UV.x, 1 - UV.y) ); //Restas realizadas por CPU.
}