#include "OS_Core/tinyOS.h"
#include "OS_Core/scheduler.h"
#include "../tasks/logMap.h"
#include "../tasks/mandelbrot.h"
#include "../tasks/simpleTask.h"

#include "stm32f4xx_gpio.h"

extern volatile struct scheduler *kernelSch;

int main(void)
{
	struct scheduler process_0;

	initScheduler( &process_0 );

	createTask( &process_0, &simpleTask,  NULL);
	createTask( &process_0, &simpleTask2, NULL);

	kernelSch = &process_0;
	setupIO( );

	for(;;)
	{
	}

	return 0;
}
