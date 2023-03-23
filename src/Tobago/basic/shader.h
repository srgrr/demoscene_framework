//
//  shader.h
//  Lynx1
//

#pragma once
#ifdef DEBUG_LOG
#ifndef shader_h
#define shader_h

#include "GL/glew.h"
#include "GL/glfw.h"
#include "global.h"
#include <cstdio>
#include <cstdlib>

class Shader {
public:
    Shader() { };
    Shader(char *vertex, char *fragment); //load, compile and link the shaders at one call.
    Shader(const char *vertex, const char *fragment, bool verbose); //load, compile and link the shaders LOAD FROM MEMORY, VERBOSE NOT IMPLEMENTED.
    bool load(char *vertex, char *fragment); //returns true if everything is ok.
	void loadmemory(const char *vertex, const char *fragment);
    bool compile(); //returns true if everything ok.
    bool link(); //returns true if everything ok.
	//void getV(GLuint BID , char *name_t);
    void use();
    //void unuse();
	GLuint getUniform(char *name);

    void uni_float(char *name, float value);
    void uni_int(char *name, int value);
	GLuint p;
private:
    GLuint v, f;
    const char *vv, *ff;
    char *textFileRead(char *fn);
    bool printShaderInfoLog(GLuint obj); //returns true if error.
    bool printProgramInfoLog(GLuint obj); //returns true if error.
};

#endif
#endif
