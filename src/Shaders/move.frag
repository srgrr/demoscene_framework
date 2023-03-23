#version 330 core
out vec4 color;
in float alpha;

void main() {
	
	color = vec4(0.55,0.55,0.55, alpha);
}