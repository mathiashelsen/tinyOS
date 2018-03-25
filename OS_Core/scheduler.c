#include "scheduler.h"

extern uint32_t _estack;

int initScheduler	(
	struct scheduler *sch
	)
{
	sch->numTasks	= 0;
	sch->rootTask	= NULL;
	sch->active		= 0;

	sch->stackBase	= _estack - 0x400;
	sch->heapBase	= 0x20000000;

	sch->stackSize	= 0x100;
	sch->heapSize	= 0x100;

	return 0;
}

int createTask		(
	struct scheduler *sch,
	 void (*func)(void *), void* args )
{
	// "Kernel" allocate some space for the new task
	struct task *newTask	= malloc(sizeof(newTask));
	// Put the stack and heap at the right location
	newTask->stackPtr		= sch->stackBase - sch->numTasks*sch->stackSize;
	newTask->heapPtr		= sch->heapBase  + sch->numTasks*sch->heapSize;
	newTask->taskFunc		= func;
	//newTask->pcValue		= (uint32_t) func;
	newTask->taskArgs		= args;
	newTask->taskFlags.activated = 0;
	newTask->taskFlags.running = 0;

	if(sch->rootTask == NULL)
	{
		// First task is the root task, it's also the last task
		sch->rootTask = newTask;
		sch->lastTask = newTask;
		sch->currentTask = newTask;
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


int switchToNextTask (
	struct scheduler *sch )
{
	uint32_t stackPtr;
	struct task *nextTask;

	if(sch->active == 0)
	{
		sch->active	= 1;

		nextTask = sch->rootTask;
	}
	else
	{
		// Save extra registers
		asm volatile(	"push {r4-r11}\n\r" : : );

		// Retrieve stack pointer value
		asm volatile(	"mov %0, sp\n\r"  :"=r" (stackPtr) : : "memory");
		
		(sch->currentTask)->stackPtr = stackPtr;

		nextTask = (sch->currentTask)->nextTask;
	}

	if(nextTask->taskFlags.activated == 0)
	{
		sch->currentTask = nextTask;
		stackPtr = (sch->currentTask)->stackPtr;

		// Return stack pointer
		asm volatile(	"mov sp, %0\n\r" : : "r" (stackPtr) : "memory");

		nextTask->taskFlags.activated	= 1;
		nextTask->taskFlags.running		= 1;

		nextTask->taskFunc(nextTask->taskArgs);
	}
	else
	{
		// Read back extra registers
		asm volatile(	"pop {r4-r11}\n\r" : : );
	}

	return 1;
}
