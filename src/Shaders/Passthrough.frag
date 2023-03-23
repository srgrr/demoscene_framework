#version 330 core

in vec2 UV;

out vec4 color;

uniform sampler2D renderedTexture;

void main(){
	color = texture( renderedTexture, vec2( UV.x, 1-UV.y ) );
	//color.xyz = texture( renderedTexture, vec2(1/UV.x, 1/UV.y) ).xyz ;
	//color.xyz = texture( renderedTexture, UV ).xyz ;
	//color.xyz = vec3(1.0f,0.0f,0.0f);
	//color.z = color.x+color.y;
	//color.w = 1.0f;
}