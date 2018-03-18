#include "scheduler.h"

int initScheduler	(
	struct scheduler *sch
	)
{
	sch->numTasks	= 0;
	sch->rootTask	= NULL;

	return 0;
}

int createTask		(
	struct scheduler *sch,
	 void (*func)(const void *), void* args )
{
	// "Kernel" allocate some space for the new task
	struct task *newTask	= malloc(sizeof(newTask));
	// Put the stack and heap at the right location
	newTask->stackPtr		= sch->stackBase - sch->numTasks*sch->stackSize;
	newTask->heapPtr		= sch->heapBase  + sch->numTasks*sch->heapSize;
	newTask->pcValue		= (uint32_t) func;
	newTask->taskArgs		= args;
	newTask->taskFlags.activated = 0;
	newTask->taskFlags.running = 0;

	if(sch->rootTask == NULL)
	{
		// First task is the root task, it's also the last task
		sch->rootTask = newTask;
		sch->lastTask = newTask;
		// It will also succeed itself for the scheduler
		newTask->nextTask = newTask;
	}else{
		// The new task will be added to the end of the list,
		// thus the next task is the rootTask, etc.
		newTask->nextTask		= sch->rootTask;
		sch->lastTask->nextTask	= newTask;
		sch->lastTask			= newTask;
	}
	
	sch->numTasks++;

	// Exit with great success!
	return sch->numTasks;
}
