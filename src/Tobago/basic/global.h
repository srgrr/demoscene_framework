#pragma once
#ifndef Base_global_h
#define Base_global_h

//#include "GL/glfw.h"
#include "timer.h"

#ifdef DEBUG_LOG
#include "log.h"
#endif

//glm::vec3 nos arregla el dia,y tiene overload de operadores para hacer lo que usted quiera con ellos !
namespace global {
	extern int      width;
    extern int      height;

	//Desired framerate
	extern unsigned char      fps;
	//Saves the demo current time.
	extern double   currentTime;
	//Frame increment.
	extern double	dt;

	extern float quad[12];
	extern GLushort quad_I[6];

	//If debugging, log file.
	#ifdef DEBUG_LOG
	extern Log      log;
	#endif

};

#endif
