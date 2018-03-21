#include "logMap.h"


void logMap( void * _args )
{
	printf("Helllo world!\n");
	struct logMap_args *args = (struct logMap_args *) _args;
	double r_step = (args->r_end - args->r_start)/((double)args->N_r - 1.0);
	double x, r;
	int i, j, N;

	args->results = 0;
	N = sizeof(double)*(args->N_r)*(args->N_saves);
	args->results = malloc(N);
	printf("Allocated pointer at %p\n", args->results);

	
	for(i = 0; i < args->N_r; i++)
	{
		x = 0.5;
		r = args->r_start + ((double)i)*r_step;

		for(j = 0; j < args->N_iters; j++)
		{
			x = r*x*(1.0 - x);
			if( j >= args->N_saves )
			{
				(args->results)[i*args->N_saves + j] = x;
			}
		}
		
	}	
}

