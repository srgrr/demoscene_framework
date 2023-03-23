#include "scenemanager.h"


SceneManager::SceneManager(double *t) {
	time = t;
}

void SceneManager::addEvent(double start,				//start second
						    double end,					//end second
						    float priority,				//priority (lower execute first!)
						    void (*pre_f)(void),			//pre function (executed just before start)
						    void (*post_f)(void),		//post function (just after end)
						    void (*draw_f)(double),		//function called in the main loop.
					 	    void (*update_f)(double)		//function called in the timer update.
						   ) {
	happening t;

	t.start = start;
	t.end = end;
	t.priority = priority;
	t.pre_f = pre_f;
	t.post_f = post_f;
	t.draw_f = draw_f;
	t.update_f = update_f;
	t.started = false;
	t.ended = false;

	events.push_back(t);
}

void SceneManager::render() {
	//supose events sorted.
	vector<list<happening>::iterator> sorted;

	for(list<happening>::iterator it=events.begin(); it != events.end(); it++) {
		if(it->start <= *time && it->end >= *time) { //if event is inside time range, push it!
			sorted.push_back(it);
		} else if(it->end < *time && it->ended == false) { //if end already happened but not ended, end it.
			if(it->post_f != NULL) it->post_f();
			it->ended = true;
		}
		/*
		if(it->end > time) {	//if event end time is less than actual time we delete it (maybe not necessary, or troublesome).
			events.erase(it);
		}*/
	}

	//Order tasks to do with priority (lowest first).
	sort(sorted.begin(), sorted.end(), sort_happening);

	//Do the tasks.
	for(int i=0; i<sorted.size(); i++) {
		if(sorted[i]->started == false) { //if it has not been started, call PRE function.
			if(sorted[i]->pre_f != NULL) sorted[i]->pre_f();
			sorted[i]->started = true;
		}
		if(sorted[i]->draw_f != NULL) sorted[i]->draw_f( (*time - sorted[i]->start) / (sorted[i]->end - sorted[i]->start) );
	}
}

void SceneManager::update() {
	vector<list<happening>::iterator> sorted;

	for(list<happening>::iterator it=events.begin(); it != events.end(); it++) {
		if(it->start <= *time &&  it->end >= *time && it->ended == false) {
			sorted.push_back(it);
		}
	}

	sort(sorted.begin(), sorted.end(), sort_happening);

	for(int i=0; i<sorted.size(); i++) {
		if(sorted[i]->update_f != NULL) sorted[i]->update_f( (*time - sorted[i]->start) / (sorted[i]->end - sorted[i]->start) );
	}
}
