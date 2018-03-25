#ifndef _SCHEDULER_H
#define _SCHEDULER_H

#include <stdint.h>
#include <stdlib.h>
#include "tinyOS.h"

struct taskFlags_str
{
	unsigned int activated : 1; // Has the function been fed the input variables?
	unsigned int running   : 1; // Is the function allowed to run by the scheduler?
};

struct task
{
	struct taskFlags_str	taskFlags;
	uint32_t				stackPtr;
	uint32_t				heapPtr;
	void					(*taskFunc)(void *);
	void*					taskArgs;
	struct task*			nextTask;
};

struct scheduler
{
	uint32_t numTasks;
	char     active;

	uint32_t stackBase;
	uint32_t stackSize;
	uint32_t heapBase;
	uint32_t heapSize;
	
	struct task* rootTask;		// First task to run
	struct task* currentTask;	// Will be required for umalloc;
	struct task* lastTask;		// New tasks get appended to the list
};

int createTask		(
	struct scheduler *sch,
	 void (*func)(void *), void* args );

void switchToNextTask (
	struct scheduler *sch );

int killTask		(
	struct scheduler *sch,
	int taskID 
	);

int initScheduler	(
	struct scheduler *sch
	);

int startScheduler	( );

#endif
