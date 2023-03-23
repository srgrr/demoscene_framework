#include "shader_string.h"

/*GLuint SShader(const GLchar *vertex ,const GLchar *fragment)
{
	GLuint vert = glCreateShader(GL_VERTEX_SHADER);
	GLuint frag = glCreateShader(GL_FRAGMENT_SHADER);
	GLuint program;
	glShaderSource(vert,1,&vertex,NULL);
	glShaderSource(frag,1,&fragment,NULL);
	glCompileShader(vert);
	glCompileShader(frag);
	program = glCreateProgram();
	glAttachShader(program,vert);
	glAttachShader(program,frag);
	glLinkProgram(program);
	return program;
}*/
#ifndef DEBUG_LOG
SShader::SShader(const GLchar *vertex, const GLchar *fragment)
{
	vert = glCreateShader(GL_VERTEX_SHADER);
	frag = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(vert,1,&vertex,NULL);
	glShaderSource(frag,1,&fragment,NULL);
	glCompileShader(vert);
	glCompileShader(frag);
	p = glCreateProgram();
	glAttachShader(p,vert);
	glAttachShader(p,frag);
	glLinkProgram(p);	
}

void SShader::use()
{
	glUseProgram(p);	
}
#endif