#include "scheduler.h"

const struct scheduler mainScheduler;
struct scheduler * const sPtr = &mainScheduler;

int initScheduler	( )
{
	/*
	sPtr->numTasks		= 0;
	sPtr->activeTask	= 0;
	sPtr->
	*/
	return 0;
}

int createTask		( void (*func)(const void *), void* args )
{

struct task
{
	struct taskFlags_str	taskFlags
	uint32_t				stackPtr;
	uint32_t				pcValue;
	void*					taskArgs;
	struct task*			nextTask;
};

}
