/*
 * timer.h
 *
 *	The TIMER module provides methods to create, destroy, start
 *	and stop a timer which we can use in other modules to measure
 *	running time of our algorithms. All functions are prepended
 *	with TIMER_ so as not to conflict with any other functions that
 *	share similar names (like start())
 *
 *  Created on: May 26, 2015
 *      Author: deancook
 */

#ifndef TIMER_H
#define TIMER_H

#include <stdlib.h>
#include <time.h>
#include "utils.h"

/**
 * Structure to encapsulate a timer. It contains a variable
 * startTime to hold the time at which the timer was started
 * (0 if the timer has not been started or is paused) and a
 * variable timeElapsed to show how much time has passed since
 * the timer was started
 *
 * The struct should be in the header file so that other modules
 * can use it
 **/
typedef struct timer_s {
	time_t startTime;
	size_t elapsedTime;
} TIMER_t, *TIMER_p_t; //I still don't quite understand why we do this

/**
 * Creates a timer and returns a pointer to it. The pointer is
 * to be used when calling other functions, and should be destroyed
 * using TIMER_destroy() when done.
 */
TIMER_p_t TIMER_create_timer(void);

/**
 * Destroys an instance of a timer that we no longer need
 *
 */
TIMER_p_t TIMER_destroy(TIMER_p_t);

/**
 * Starts a timer, resetting any elapsed time to 0
 *
 * @return 0
 */
size_t TIMER_start(TIMER_p_t);

/*
 * Stops or pauses a timer. To start the timer, maintaining the elapsed
 * time, use TIMER_restart(), to restart it from 0, call TIMER_start()
 * again.
 *
 * @return the ellapsed time
 */
size_t TIMER_stop(TIMER_p_t);

/**
 * Returns the elapsed time for a timer
 */
size_t TIMER_interrogate(TIMER_p_t);

/*
 * Starts a timer again, while maintaining the elapsed time
 *
 * @return the elapsed time when restarted
 */
size_t TIMER_restart(TIMER_p_t);

/*
 * Sets the elapsed time of a timer to 0. If the timer is running
 * the timer will not be stopped
 */
size_t TIMER_reset(TIMER_p_t);



#endif /* SRC_TIMER_TIMER_H_ */
