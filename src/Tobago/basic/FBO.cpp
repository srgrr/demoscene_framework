#include "FBO.h"

FBO::FBO(GLsizei width, GLsizei height, bool dbo, bool qualite) 
{
	this->width = width;
	this->height = height;

	glGenFramebuffers(1, &theID);
	glBindFramebuffer(GL_FRAMEBUFFER, theID);

	//Create and attach color texture.
	texture = new TBO(GL_RGBA, width, height, GL_RGBA, GL_UNSIGNED_BYTE, 0, qualite);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texture->theID, 0);

	// The depth buffer (with renderbuffer)
/*	glGenRenderbuffers(1, &depthrenderbuffer);
	glBindRenderbuffer(GL_RENDERBUFFER, depthrenderbuffer);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, width, height);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, depthrenderbuffer); */

	if(dbo) {
		depthtexture = new TBO(GL_DEPTH_COMPONENT24, width, height, GL_DEPTH_COMPONENT, GL_FLOAT, 0, false);
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D,  depthtexture->theID, 0);
	}

	if(dbo) {
		GLenum DrawBuffers[2] = {GL_COLOR_ATTACHMENT0,GL_DEPTH_ATTACHMENT};
		glDrawBuffers(2, DrawBuffers); // "2" is the size of DrawBuffers
	} else {
		depthtexture = NULL;
		GLenum DrawBuffers[1] = {GL_COLOR_ATTACHMENT0};
		glDrawBuffers(1, DrawBuffers); // "1" is the size of DrawBuffers
	}

	// Always check that our framebuffer is ok
	if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) status = false;
	else status = true;

	#ifdef DEBUG_LOG
	if(!status) global::log.error("Error creating FBO");
	#endif

	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

FBO::FBO(GLsizei width, GLsizei height, TBO *tex, TBO *depth, bool qualite) 
{
	this->width = width;
	this->height = height;

	glGenFramebuffers(1, &theID);
	glBindFramebuffer(GL_FRAMEBUFFER, theID);

	texture = NULL;
	depthtexture = NULL;

	tex->load(GL_RGBA, width, height, GL_RGBA, GL_UNSIGNED_BYTE, 0, qualite);
	if(depth != NULL) depth->load(GL_DEPTH_COMPONENT24, width, height, GL_DEPTH_COMPONENT, GL_FLOAT, 0, false);

	// Set "renderedTexture" as our colour attachement #0
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, tex->theID, 0);
	if(depth != NULL) glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D,  depth->theID, 0);

	// Set the list of draw buffers.
	if(depth != NULL) {
		GLenum DrawBuffers[2] = {GL_COLOR_ATTACHMENT0, GL_DEPTH_ATTACHMENT};
		glDrawBuffers(2, DrawBuffers); // "1" is the size of DrawBuffers
	} else {
		GLenum DrawBuffers[1] = {GL_COLOR_ATTACHMENT0};
		glDrawBuffers(1, DrawBuffers); // "1" is the size of DrawBuffers
	}

	// Always check that our framebuffer is ok
	if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) status = false;
	else status = true;

	#ifdef DEBUG_LOG
	if(!status) global::log.error("Error creating FBO");
	#endif

	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void FBO::bind() 
{
	glBindFramebuffer(GL_FRAMEBUFFER, theID);				//bind buffer
	glViewport(0, 0, width, height);						//set viewport
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	//clean things
}

void FBO::unbind() 
{
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glViewport(0, 0, global::width, global::height);
}

void FBO::erase() {
	if(texture != NULL) texture->erase();
	if(depthtexture != NULL) depthtexture->erase();
//	glDeleteRenderbuffers(1, &depthrenderbuffer);
	glDeleteFramebuffers(1, &theID);
}

void FBO::bind_texture(int id) 
{
	texture->bind(id);
}
