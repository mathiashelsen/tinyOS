#include "mandelbrot.h"

void mandelbrot(void *_args)
{
	struct mandelbrot_args *args = (struct mandelbrot_args *) _args;

	double r_0		= args->r_start;
	double r_step	= (args->r_end - args->r_start)/(args->N_r - 1.0);
	double i_0		= args->i_start;
	double i_step	= (args->i_end - args->i_start)/(args->N_i - 1.0);
	int i, j, k;

	for(i = 0; i < args->N_i; i++)
	{
		for(j = 0; j < args->N_r; j++)
		{
			double complex c	= (r_0 + r_step*(double)j)
				+ I * (i_0 + i_step*(double)i);
			double complex z	= 0.0;
			double radius		= 0.0;

			k					= 0;
			while(k < args->N_iters && radius < args->max_radius)
			{
				z      = z*z + c;
				radius = cabs(z);
			}
			if(radius < args->max_radius)
			{
				printf("%e\t%e\n", creal(c), cimag(c));
			}
		}

	}

}
