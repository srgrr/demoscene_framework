#pragma once

#ifndef Scene_manager_h
#define Scene_manager_h

#include "basic/timer.h"
#include <map>
#include <vector>
#include <queue>
#include <list>
#include <algorithm>

struct happening {
	double start;
	double end;
	int priority;
	void (*pre_f)(void);
	void (*post_f)(void);
	void (*draw_f)(double);
	void (*update_f)(double);
	bool started;
	bool ended;
};

static bool sort_happening(list<happening>::iterator i, list<happening>::iterator j) { //lowest priority comes first.
	return (i->priority < j->priority);
}

class SceneManager {
public:
	SceneManager(double *t);

	void addEvent(double start,					//start second
				  double end,					//end second
				  float priority,				//priority (lower execute first!)
				  void (*pre_f)(void),			//pre function (executed just before start)
				  void (*post_f)(void),			//post function (just after end)
				  void (*draw_f)(double),		//function called in the main loop.
				  void (*update_f)(double)		//function called in the timer update.
				 );

	void render();

	void update();

private:
	double *time;
	list<happening> events;
};

#endif