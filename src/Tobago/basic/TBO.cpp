#include "TBO.h"

TBO::TBO() {
	glEnable(GL_TEXTURE_2D);
	glGenTextures(1, &theID);
	glBindTexture(GL_TEXTURE_2D, theID);
	glBindTexture(GL_TEXTURE_2D, 0);
}

TBO::TBO(GLint internalFormat, GLsizei width, GLsizei height, GLenum format, GLenum type, const GLvoid* data, bool goodfiltering) {
	glEnable(GL_TEXTURE_2D);
	glGenTextures(1, &theID);
	glBindTexture(GL_TEXTURE_2D, theID);

	load(internalFormat, width, height, format, type, data, goodfiltering);

	glBindTexture(GL_TEXTURE_2D, 0);
}

TBO::TBO(char* filename, bool goodfiltering) {
	glEnable(GL_TEXTURE_2D);
	glGenTextures(1, &theID);
	glBindTexture(GL_TEXTURE_2D, theID);

	load(filename, goodfiltering);

	glBindTexture(GL_TEXTURE_2D, 0);
}

void TBO::load(GLint internalFormat, GLsizei width, GLsizei height, GLenum format, GLenum type, const GLvoid* data, bool goodfiltering) {
	glEnable(GL_TEXTURE_2D); //just in case...
	glBindTexture(GL_TEXTURE_2D, theID);

	if(goodfiltering) {
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); //GL_LINEAR_MIPMAP_LINEAR); 
		//glGenerateMipmap(GL_TEXTURE_2D);
	} else {
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST); 
	}
	if(data == NULL) glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, width, height, 0, format, type, 0);
	glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, width, height, 0, format, type, data);

	glBindTexture(GL_TEXTURE_2D, 0); //just in case...
}

void TBO::load(char* filename, bool goodfiltering) {
	unsigned char* image;
	unsigned w, h;
	unsigned error;
	
	error = LodePNG_decode32_file(&image, &w, &h, filename);
	#ifdef DEBUG_LOG
	if(error) global::log.error("Error loading PNG");
	#endif
	glPixelStorei(GL_UNPACK_ALIGNMENT,1);

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, theID);

	if(goodfiltering) {
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); //GL_LINEAR_MIPMAP_LINEAR); 
		//glGenerateMipmap(GL_TEXTURE_2D);
	} else {
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST); 
	}

	glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA,w,h,0, GL_RGBA,GL_UNSIGNED_BYTE,image);
	free(image);

	glBindTexture(GL_TEXTURE_2D, 0);
}

void TBO::bind(int id) {
	// Bind our texture in Texture Unit 0
	glActiveTexture(GL_TEXTURE0+id);
	glBindTexture(GL_TEXTURE_2D, theID);
}

void TBO::qualite(bool qualite) {
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, theID);

	if(qualite) {
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); //GL_LINEAR_MIPMAP_LINEAR); 
		//glGenerateMipmap(GL_TEXTURE_2D);
	} else {
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST); 
	}


}

void TBO::erase() {
	glDeleteTextures(1, &theID);
//	glDisable(GL_TEXTURE_2D); //not sure...
}