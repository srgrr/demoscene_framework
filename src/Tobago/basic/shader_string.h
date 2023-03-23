#include "GL/glew.h"
#include "GL/glfw.h" //Prueba a quitarlo y veras que error mas vengamonjas da.
#pragma once
#ifndef DEBUG_LOG
/*
	Esta funcion no devuelve ningun log ni hostias.
	Si funciona funciona,si no,pues te jodes.
	Esta pensada para cuando ya tengamos la seguridad de que todo va bien.
	Paralelamente,voy a codear una cosa sencillita que lea archivos de shaders y
	devuelva un unico archivo con cosas como los (char *) que hay ahora en geostuff.

	Aparte de eso,perdon por ser tan pesado con los putos triangulitos,pero es lo mas comodo
	para probar a ver si va o no va.
*/
//GLuint SShader(const GLchar *vertex ,const GLchar *fragment);

class SShader
{
	public :
		GLuint p , vert , frag;
		SShader(){};
		SShader(const GLchar *vertex, const GLchar *fragment);
		void use();
};
#endif