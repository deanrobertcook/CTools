/*
 * test_driver.c
 *
 *  Created on: May 30, 2015
 *      Author: deancook
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "src/timer/timer.h"
#include "src/utils/utils.h"

/*
 * The following section of code changes how the SLEEP macro is defined
 * Anything with the #define label is handled by the preprocessor, not by the
 * compiler, so we can then define macros differently depending on system
 * configurations!
 */
#ifdef WIN32
#include <windows.h>
#define SLEEP( s ) (Sleep( s * 1000 ))
#else
#include <unistd.h>
#define SLEEP( s ) (sleep( s ))
#endif

//testProc is an actual procedure, which we'll be executing
//as our test cases
typedef UTILS_BOOL_t TestProc_t(void);
typedef TestProc_t* TestProc_p_t;

typedef struct test_desc_s {
	TestProc_p_t	testProc;
	const char* 	str;
} TestDesc_t, *TestDesc_p_t;

static TestProc_t test01000;
static TestProc_t test02000;
static TestProc_t test03000;
static TestProc_t test04000;

//we can select which tests to run here
//perhaps think of a better mechanism later
static TestDesc_t testsToRun[] = {
	{test01000, "Test case 1000"},
	{test02000, "Test case 2000"},
	{test03000, "Test case 3000"},
	{test04000, "Test case 4000"},
};

int main(int argc, char **argv) {
	int rcode = EXIT_SUCCESS;
	int ind = 0;

	//we stop tests as soon as one fails
	for (ind = 0; rcode == EXIT_SUCCESS
		&& ind < UTILS_CARD(testsToRun); ++ind) {
		printf("%s\n", testsToRun[ind].str);
		//here, we run each test procedure
		if (!testsToRun[ind].testProc()) {
			printf("\tFAILED\n");
			rcode = EXIT_FAILURE;
		}
	}
	return rcode;
}

static UTILS_BOOL_t testDiff(const char* tag, time_t exp, time_t act) {
	size_t diff = (size_t)labs(exp - act);
	const char* stat;
	UTILS_BOOL_t rcode;

	if (diff == 1) {
		stat = "WARNING";
		rcode = UTILS_TRUE;
	} else if (diff > 1) {
		stat = "ERROR";
		rcode = UTILS_FALSE;
	} else {
		stat = "SUCCESS";
		rcode = UTILS_TRUE;
	}

	if (!rcode) {
		printf("\t%s: expected = %d, actual = %d: %s\n", tag, exp, act, stat);
	}
	return rcode;
}

/*
 * Testing function TIMER_create_timer()
 */
static UTILS_BOOL_t test01000(void) {
	UTILS_BOOL_t rcode = UTILS_FALSE;
	TIMER_p_t timer1 = TIMER_create_timer();
	TIMER_p_t timer2 = TIMER_create_timer();
	TIMER_p_t timer3 = TIMER_create_timer();

	if ( timer1 == timer2 || timer1 == timer3 || timer2 == timer3 )
		printf( "\tTIMER_create_timer does not return unique ID\n" );
	else if (
		timer1->startTime != 0 ||
		timer1->elapsedTime != 0 ||
		timer2->startTime != 0 ||
		timer2->elapsedTime != 0 ||
		timer3->startTime != 0 ||
		timer3->elapsedTime != 0
	)
		printf("\tTIMER_create_timer() does not properly initialise struct\n");
	else
		rcode = UTILS_TRUE;

	TIMER_destroy(timer1);
	TIMER_destroy(timer2);
	TIMER_destroy(timer3);

	return rcode;
}

/*
 * Test that the timer is properly destroyed
 */
static UTILS_BOOL_t test02000(void) {
	UTILS_BOOL_t rcode = UTILS_FALSE;

	TIMER_p_t timer = UTILS_NEW(TIMER_t);
	timer = TIMER_destroy(timer);

	/*
	 * There is no (easy) way to check that memory has been
	 * freed. Since the values at the memory location won't
	 * be overwritten immediately, it often will still contain
	 * the value you left it with. All you can do is check to
	 * see that the pointer has been set to NULL.
	 */

	if (timer == NULL) {
		rcode = UTILS_TRUE;
	}

	return rcode;
}

/*
 * Test to see a timer is started and reflects the time
 * it was started while running
 */
static UTILS_BOOL_t test03000(void) {
	UTILS_BOOL_t rcode = UTILS_FALSE;

	TIMER_p_t timer = UTILS_NEW(TIMER_t);

	TIMER_start(timer);
	time_t time_started = time(NULL);

	if (testDiff("03000", time_started, timer->startTime)) {
		rcode = UTILS_TRUE;
	}
	TIMER_destroy(timer);
	return rcode;
}

/*
 * Test to see that the elapsed time represents the actual
 * time elapsed since the timer was started
 */
static UTILS_BOOL_t test04000(void) {
	UTILS_BOOL_t rcode = UTILS_FALSE;
	TIMER_p_t timer = UTILS_NEW(TIMER_t);
	UTILS_INT16_t executionTime = 2;

	TIMER_start(timer);
	SLEEP(executionTime);
	TIMER_stop(timer);

	if (testDiff("04000", executionTime, timer->elapsedTime)) {
		rcode = UTILS_TRUE;
	}
	TIMER_destroy(timer);
	return rcode;
}














