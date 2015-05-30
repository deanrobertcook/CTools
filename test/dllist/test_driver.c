#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>
#include "src/timer/timer.h"
#include "src/utils/utils.h"
#include "src/dllist/dllist.h"

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
static TestProc_t test01100;
static TestProc_t test03000;
static TestProc_t test04000;
static TestProc_t test05000;

//we can select which tests to run here
//perhaps think of a better mechanism later
static TestDesc_t testsToRun[] = {
  {test01000, "Test case 1000"},
  {test01100, "Test case 1100"},
  {test03000, "Test case 3000"},
  {test04000, "Test case 4000"},
  {test05000, "Test case 5000"},
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

/*
 * Test to see that a new list can be created
 */
static UTILS_BOOL_t test01000(void) {
  UTILS_BOOL_t rcode = UTILS_FALSE;
  list_p_t list = DLLIST_create_list();

  if (list != NULL)
    rcode = UTILS_TRUE;

  list = DLLIST_destroy_list(list);
  
  return rcode;
}


/*
 * Test to see that a new list has a length of 0
 */
static UTILS_BOOL_t test01100(void) {
  UTILS_BOOL_t rcode = UTILS_FALSE;
  list_p_t list = DLLIST_create_list();

  if (DLLIST_length(list) == 0)
    rcode = UTILS_TRUE;

  list = DLLIST_destroy_list(list);
  
  return rcode;
}

/*
 * A new item can be added to the list
 */
static UTILS_BOOL_t test03000(void) {
  UTILS_BOOL_t rcode = UTILS_FALSE;
  list_p_t list = DLLIST_create_list();

  item_p_t item1 = UTILS_NEW(item_t);
  item1->data = "Test 1";

  list = DLLIST_append_item(list, 0, item1);

  if (DLLIST_length(list) == 1)
    rcode = UTILS_TRUE;
  
  list = DLLIST_destroy_list(list);
  
  return rcode;
}

/*
 * An item can be deleted from the list and the list
 * is then the correct size;
 */
 
static UTILS_BOOL_t test04000(void) {
  UTILS_BOOL_t rcode = UTILS_FALSE;
  list_p_t list = DLLIST_create_list();

  item_p_t item1 = UTILS_NEW(item_t);
  item1->data = "Test 1";
  item_p_t item2 = UTILS_NEW(item_t);
  item2->data = "Test 2";
  
  list = DLLIST_append_item(list, 0, item1);
  list = DLLIST_append_item(list, 1, item2);
  
  assert(DLLIST_length(list) == 2);

  list = DLLIST_remove_item(list, 1);

  if(DLLIST_length(list) == 1)
    rcode = UTILS_TRUE;
  
  list = DLLIST_destroy_list(list);
  
  return rcode;
}

/*
 * An item can be retrieved from the list
 */
 
static UTILS_BOOL_t test05000(void) {
  UTILS_BOOL_t rcode = UTILS_FALSE;
  list_p_t list = DLLIST_create_list();

  item_p_t item1 = UTILS_NEW(item_t);
  item1->data = "Test 1";
  item_p_t item2 = UTILS_NEW(item_t);
  item2->data = "Test 2";
  
  list = DLLIST_append_item(list, 0, item1);
  list = DLLIST_append_item(list, 1, item2);
  
  item_p_t retrievedItem = DLLIST_get_item(list, 1);
  if(retrievedItem->data == item2->data)
    rcode = UTILS_TRUE;
  
  list = DLLIST_destroy_list(list);
  
  return rcode;
}
