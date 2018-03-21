#include "logMap.h"


void logMap( void * _args )
{
	printf("Hello!\n");
	struct logMap_args *args = (struct logMap_args *) _args;
	double r_step = (args->r_end - args->r_start)/((double)args->N_r - 1.0);
	double *res = *(args->results);
	double x, r;
	int i, j;
	
	for(i = 0; i < args->N_r; i++)
	{
		x = 0.5;
		r = args->r_start + ((double)i)*r_step;

		for(j = 0; j < args->N_iters; j++)
		{
			x = r*x*(1.0 - x);
			if( j >= args->N_saves )
			{
				res[i*args->N_saves + j] = x;
			}
		}
		
	}	
}

