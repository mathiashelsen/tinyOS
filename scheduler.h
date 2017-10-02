#ifndef _SCHEDULER_H
#define _SCHEDULER_H

typedef struct task
{
	uint32_t	stackPtr;
	void*		taskArgs;
	void*		taskFramePtr;
	task*		nextTask;
};

typedef struct scheduler
{
	int numTasks;
	int activeTask;
	task* rootTask;
};

int registerTask	( void (*func)(const void *), void* args );
int killTask		( int taskID );
int initScheduler	( );
int startScheduler	( );

#endif
