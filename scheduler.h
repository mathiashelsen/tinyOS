#ifndef _SCHEDULER_H
#define _SCHEDULER_H

typedef struct task
{
	uint32_t	stackPtr;
	void*		taskArgs;
	void*		taskFramePtr;
	task*		nextTask;
}

typedef struct scheduler
{
	int numTasks;
	int activeTask;
	task* rootTask;
}

int registerTask	( scheduler*, void (*func)(const void *), void* args );
int killTask		( scheduler*, int taskID );
int initScheduler	( scheduler* );
int startScheduler	( scheduler* );

#endif
