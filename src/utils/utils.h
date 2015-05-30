/*
 * utils.h
 *
 *  Created on: May 26, 2015
 *      Author: deancook
 */

#ifndef UTILS_H
#define UTILS_H

#include <stdlib.h>

/*
 * Makes booleans a little more readable
 */
#define UTILS_TRUE		(1)
#define UTILS_FALSE		(0)

/*
 * We can later make this macro a little bit more advanced,
 * and then we don't have to change everywhere it's defined
 */
#define UTILS_ASSERT( exp ) (assert( (exp) ))

/*
 * Tells us the cardinality (length) of an array
 */
#define UTILS_CARD( arr ) (sizeof((arr))/sizeof(*(arr)))

/*
 * Provides us dynamic memory for a new object pointer
 * Much like the new keyword in Java or C++
 */
#define UTILS_NEW( type ) ((type *)UTILS_malloc( sizeof(type) ))

/*
 * The next two macros give us the ability to easily create new
 * strings, assigning memory to them
 */
#define UTILS_NEW_STR( str ) \
 (strcpy( (char *)CDA_malloc( strlen( (str) ) + 1 ), (str) ))

#define UTILS_NEW_STR_IF( str ) \
 ((str) == NULL ? NULL : CDA_NEW_STR( (str) ))

/*
 * These custom defined types help us improve portability of our code
 */
typedef int				UTILS_BOOL_t;
typedef signed char 	UTILS_INT8_t;
typedef unsigned char 	UTILS_UINT8_t;
typedef signed int		UTILS_INT16_t;
typedef unsigned int 	UTILS_UINT16_t;
typedef signed long		UTILS_INT32_t;
typedef unsigned long	UTILS_UINT32_t;

/*
 * The prototypes for our utility methods
 * This acts like a nice interface for other modules
 */
void *UTILS_malloc(size_t);
void *UTILS_calloc(size_t, size_t);
void *UTILS_realloc(void*, size_t);
void *UTILS_free(void*);

#endif
