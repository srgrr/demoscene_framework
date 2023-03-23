#pragma once
#include <GL/glew.h>
#include <GL/glfw.h>
#include "lodepng/lodepng.h"
#include "basic/global.h"

class TBO {
public:
	//Creates empty texture, (fill with load).
	TBO();
	
	//Creates texture from array.
	TBO(GLint internalFormat, GLsizei width, GLsizei height, GLenum format, GLenum type, const GLvoid* data, bool goodfiltering);
	
	//Creates texture from PNG.
	TBO(char* filename, bool goodfiltering);
	

	void load(GLint internalFormat, GLsizei width, GLsizei height, GLenum format, GLenum type, const GLvoid* data, bool goodfiltering);

	void load(char* filename, bool goodfiltering);

	//Binds to TextureUnit id
	void bind(int id);

	//Set filtering...
	void qualite(bool qualite);
	
	//erases it?
	void erase();

	//texture name.
	GLuint theID;
};