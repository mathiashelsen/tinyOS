#include "logMap.h"


void logMap( void * _args )
{
	struct logMap_args *args = (struct logMap_args *) _args;
	double r_step = (args->r_end - args->r_start)/((double)args->N_r - 1.0);
	args->results = malloc(sizeof(double)*(args->N_r)*(args->N_saves));
	double x, r;
	int i, j, k;

	for(i = 0; i < args->N_r; i++)
	{
		x = 0.5;
		r = args->r_start + ((double)i)*r_step;

		for(j = 0; j < args->N_iters; j++)
		{
			x = r*x*(1.0 - x);
			if( j >= (args->N_iters - args->N_saves) )
			{
				(args->results)[i*args->N_saves + k] = x;
				k++;
			}else{
				k = 0;
			}
		}
		
	}	

	for( ; ; )
	{

	}
}

