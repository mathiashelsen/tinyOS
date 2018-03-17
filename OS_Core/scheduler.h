#ifndef _SCHEDULER_H
#define _SCHEDULER_H

#include <stdint.h>

struct taskFlags_str
{
	unsigned int activated : 1; // Has the function been fed the input variables?
	unsigned int running   : 1; // Is the function allowed to run by the scheduler?
};

struct task
{
	struct taskFlags_str	taskFlags
	uint32_t				stackPtr;
	uint32_t				pcValue;
	void*					taskArgs;
	struct task*			nextTask;
};

struct scheduler
{
	int numTasks;
	int activeTask;
	struct task* rootTask;
};

int createTask		( void (*func)(const void *), void* args );
int killTask		( int taskID );
int initScheduler	( );
int startScheduler	( );

#endif
