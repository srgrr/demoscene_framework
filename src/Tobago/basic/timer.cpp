#include "timer.h"

Timer::Timer()
{
	this->update_f = NULL;
	lastTime = 0.0f;
    cumulativeTime = 0.0f;
    FRAME_LENGHT = 1.0f/global::fps;
	MAX_ITERATIONS = 10;
	#ifndef NO_SOUND
	somelier = NULL;
	#endif
}

Timer::Timer(int (*update_foo)(void))
{
	this->update_f = update_foo;
	lastTime = 0.0f;
    cumulativeTime = 0.0f;
    FRAME_LENGHT = 1.0f/global::fps;
	MAX_ITERATIONS = 10;
	#ifndef NO_SOUND
	somelier = NULL;
	#endif
}

#ifndef NO_SOUND
void Timer::getTimeFrom(SoundHandler *f) {
	somelier = f;
}
#endif

void Timer::setUpdateF(int (*update_foo)(void)) {
	this->update_f = update_foo;
}

void Timer::update() {
    int iterations = 0;

	#ifndef NO_SOUND
	if(somelier == NULL) global::currentTime = glfwGetTime();
	else {
		global::currentTime = somelier->SoundTime();
	}
	#endif

	#ifdef NO_SOUND
	global::currentTime = glfwGetTime();
	#endif

    global::dt = global::currentTime-lastTime; //1/dt = x fps
	fps = 1.0/global::dt;
    cumulativeTime += global::dt; // * 0.001f;
    lastTime = global::currentTime;
	while (cumulativeTime > FRAME_LENGHT) {
		if(update_f != NULL) update_f(); // Ya funciona !
		cumulativeTime -= FRAME_LENGHT;
        iterations++;
		if(iterations > MAX_ITERATIONS) {
			#ifdef DEBUG_LOG
            global::log.error("Timer max iterations achieved");
			#endif
            break;
        }
    }
}
