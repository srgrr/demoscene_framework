#pragma once
#include <GL/glew.h>
#include <GL/glfw.h>
#include "basic/Buffer_Object.h"
#include "basic/TBO.h"
#include "basic/global.h"

//Modificarla para poder añadir Coloratachments y depthbuffers y pollas como te de la gana, sin límite.
class FBO {
private:
//	GLuint depthrenderbuffer;
	GLsizei width, height;
	bool deltex;

public:
	TBO *texture;
	TBO *depthtexture;
	bool status;

	FBO(GLsizei width, GLsizei height, bool bdo, bool qualite);

	FBO(GLsizei width, GLsizei height, TBO *tex, TBO *depth, bool qualite);

	void bind();

	void unbind();

	void erase();

	void bind_texture(int id);

	//FBO id
	GLuint theID;
};