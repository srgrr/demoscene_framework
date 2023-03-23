#version 330 core
layout(location = 0) in vec3 ap;
uniform mat4 scal;
out float alpha;

void main() {
	vec4 op = vec4( ap , 1);
	gl_Position = scal * op;
	alpha = scal[0].x;
}