/*
 * utils.c
 *
 *  Created on: May 26, 2015
 *      Author: deancook
 */

#include "utils.h"

void *UTILS_malloc(size_t size) {
	void *mem = malloc(size);
	if (mem == NULL && size > 0) {
		abort();
	}
	return mem;
}

void *UTILS_calloc(size_t numCells, size_t cellSize) {
	void *mem = calloc(numCells, cellSize);
	if (mem == NULL && numCells * cellSize > 0) {
		abort();
	}
	return mem;
}

void *UTILS_realloc(void *mem, size_t size) {
	mem = realloc(mem, size);
	if (mem == NULL && size > 0) {
		abort();
	}
	return mem;
}

void *UTILS_free(void* mem) {
	free(mem);
	return NULL;
}
