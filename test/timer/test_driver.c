/*
 * test_driver.c
 *
 *  Created on: May 30, 2015
 *      Author: deancook
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "timer.h"
#include "utils.h"

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
//static TestProc_t test02000;

//we can select which tests to run here
//perhaps think of a better mechanism later
static TestDesc_t testsToRun[] = {
	{test01000, "Test case 1000"}
//	{test02000, "Test case 2000"}
};

int main(int argc, char **argv) {
	int rcode = EXIT_SUCCESS;
	int ind = 0;

	//we stop tests as soon as one fails
	for (ind = 0; rcode == EXIT_SUCCESS
		&& ind < UTILS_CARD(testsToRun); ++ind) {

		printf("%s\n", testsToRun[ind].str);
		//here, we run each test procedure
		if (!testsToRun[ind].testProc) {
			printf( "%s failed\n", testsToRun[ind].str);
			rcode = EXIT_FAILURE;
		}
	}
	return rcode;
}

static size_t testDiff(const char* tag, time_t exp, time_t act) {
	size_t diff = (size_t)labs(exp - act);
	const char* stat = "SUCCESS";

	if (diff == 1)
		stat = "WARNING";
	else if (diff > 1)
		stat = "ERROR";
	else
		;

	printf("\t%s: expected = %21d, actual = %21d: %s\n", tag, exp, act, stat);
	return diff;
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














