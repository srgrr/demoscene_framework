#include "setup.h"
#include <iostream>
#include <stdlib.h>
using namespace std;

void OGL::init(int w	, int h , 
	int r , int g , int b , 
	int alpha , int depth , int stencil , 
	char *name , int version , int aa , int mode ) 
{
	global::width = w;
	global::height = h;
	#ifdef DEBUG_LOG 
	if(		!glfwInit()		)
	{
		cerr << "glfwInit fail'd" << endl;
		exit ( EXIT_FAILURE );
	}

	glfwOpenWindowHint(GLFW_FSAA_SAMPLES, aa);
	glfwOpenWindowHint(GLFW_OPENGL_VERSION_MAJOR, version);
	glfwOpenWindowHint(GLFW_OPENGL_VERSION_MINOR, 1);
	glfwEnable( GLFW_STICKY_KEYS );
	if( !glfwOpenWindow( w , h, r,g,b,alpha, depth,stencil, mode ) )
	{
		cerr << "glfwOpenWindow fail'd" << endl;
		glfwTerminate();
		exit( EXIT_FAILURE );
	}
	glEnable( GL_DEPTH_TEST );
	glDepthFunc( GL_LESS );
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	if( glewInit()!=GLEW_OK )
	{
		cerr << "glewInit fail'd" << endl;
		glfwTerminate();
		exit( EXIT_FAILURE );
	}
	#else
	glfwInit();
	glfwOpenWindowHint(GLFW_FSAA_SAMPLES, aa);
	glfwOpenWindowHint(GLFW_OPENGL_VERSION_MAJOR, version);
	glfwOpenWindowHint(GLFW_OPENGL_VERSION_MINOR, 1);
	glfwEnable( GLFW_STICKY_KEYS );
	//glfwOpenWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwOpenWindow(w,h,r,g,b,alpha,depth,stencil,mode);
	glEnable( GL_DEPTH_TEST);
	glDepthFunc( GL_LEQUAL );
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glewInit();
	#endif

	glfwSetWindowSizeCallback(resizecalback);

	glfwSetWindowTitle( name );
}

void GLFWCALL resizecalback( int width, int height ) {
	global::width = width;
	global::height = height;
	glViewport(0, 0, width, height); //dunou if necessary.
}