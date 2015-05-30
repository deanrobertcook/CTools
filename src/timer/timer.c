/*
 * timer.c
 *
 *  Created on: May 26, 2015
 *      Author: deancook
 */

#include "timer.h"

TIMER_p_t TIMER_create_timer(void) {
	TIMER_p_t timer = UTILS_NEW(TIMER_t);
	timer->startTime = 0;
	timer->elapsedTime = 0;
	return timer;
}

TIMER_p_t TIMER_destroy(TIMER_p_t timer) {
	timer = UTILS_free(timer);
	return timer;
}

size_t TIMER_start(TIMER_p_t timer) {
	timer->startTime = time(NULL);
	timer->elapsedTime = 0;
	return 0;
}

size_t TIMER_stop(TIMER_p_t timer) {
	TIMER_interrogate(timer);
	timer->startTime = 0;
	return timer->elapsedTime;
}

size_t TIMER_interrogate(TIMER_p_t timer) {
	timer->elapsedTime += time(NULL) - timer->startTime;
	return timer->elapsedTime;
}

size_t TIMER_restart(TIMER_p_t timer) {
	TIMER_interrogate(timer);
	timer->startTime = time(NULL);
	return timer->elapsedTime;
}

size_t TIMER_reset(TIMER_p_t timer) {
	if (timer->startTime != 0) {
		timer->startTime = time(NULL);
	}
	timer->elapsedTime = 0;
	return 0;
}
