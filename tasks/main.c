#include "logMap.h"

int main(void)
{
	int i = 0, j, N;
	struct logMap_args args;
	args.r_start	= 0.0;
	args.r_end		= 4.0;
	args.N_r		= 100.0;
	args.N_iters	= 1000.0;
	args.N_saves	= 100;
	N				= 100*100;

	double *results = malloc(sizeof(double)*N);
	args.results = &results;
	printf("Data should be stored at %p\n", results);

	double r ;
	double r_step = (args.r_end - args.r_start)/((double)args.N_r - 1.0);

	logMap( (void*)&args );


//	for(i = 0; i < args.N_r; i++)
//	{
//		r = args.r_start + ((double)i)*r_step;
//		for(j = 0; j < args.N_saves; j++)
//		{
//				printf("%f\t%f\n", r, results[i*args.N_saves + j]);;
//		}
//		printf("\n");
//		
//	}	

	printf("Data should be freed at %p\n", results);
	free(results);
}
