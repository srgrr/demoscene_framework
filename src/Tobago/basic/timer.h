//
//  timer.h
//  Base
//

#ifndef timer_h
#define timer_h

#ifndef NO_SOUND
#include "SoundHandler.h"
#endif

//#include "GL/glfw.h"
#include "global.h"

//Implements a basic timer to control framerate & updates.
class Timer {
    public:
		//Constructor, creates a timer without update function.
		Timer();

		//Constructor, creates a timer, the function specified will be called every FRAME_LENGHT time.
        Timer(int (*update_foo)(void));

		#ifndef NO_SOUND
		//Song to get time from (instead of global time).
		void getTimeFrom(SoundHandler *f);
		#endif

		void setUpdateF(int (*update_foo)(void));

		//Updates the timer and calls update function if needed. This should be called every frame.
        void update();

		double fps;
        int MAX_ITERATIONS;
        double lastTime;
        double cumulativeTime;
        double FRAME_LENGHT;
		int (*update_f)(void);

		#ifndef NO_SOUND
		SoundHandler *somelier;
		#endif
};

#endif
