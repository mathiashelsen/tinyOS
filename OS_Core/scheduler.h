#ifndef _SCHEDULER_H
#define _SCHEDULER_H

#include <stdint.h>

struct task
{
	uint32_t	stackPtr;
	void*		taskArgs;
	void*		taskFramePtr;
	struct task*		nextTask;
};

struct scheduler
{
	int numTasks;
	int activeTask;
	struct task* rootTask;
};

int registerTask	( void (*func)(const void *), void* args );
int killTask		( int taskID );
int initScheduler	( );
int startScheduler	( );

#endif
