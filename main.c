#include "OS_Core/tinyOS.h"
#include "OS_Core/scheduler.h"
#include "../tasks/logMap.h"
#include "../tasks/mandelbrot.h"

#include "stm32f4xx_gpio.h"

extern volatile struct scheduler *kernelSch;

int main(void)
{

	struct logMap_args logMapArgs;
	logMapArgs.r_start	= 0.0;
	logMapArgs.r_end		= 4.0;
	logMapArgs.N_r		= 100.0;
	logMapArgs.N_iters	= 1000.0;
	logMapArgs.N_saves	= 100;


	struct mandelbrot_args mandelbrotArgs;
	mandelbrotArgs.r_start	= -2.0;
	mandelbrotArgs.r_end		= 2.0;
	mandelbrotArgs.i_start	= -1.0;
	mandelbrotArgs.i_end		= 1.0;
	mandelbrotArgs.max_radius	= 1000.0;
	mandelbrotArgs.N_r		= 100;
	mandelbrotArgs.N_i		= 100;
	mandelbrotArgs.N_iters	= 1000;


	struct scheduler process_0;

	initScheduler( &process_0 );

	createTask( &process_0, &logMap, &logMapArgs);
	createTask( &process_0, &mandelbrot, &mandelbrotArgs);

	kernelSch = &process_0;
	setupIO( );

	for(;;)
	{
	}

	return 0;
}
