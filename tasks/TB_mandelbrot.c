#include "mandelbrot.h"

int main(void)
{
	struct mandelbrot_args args;
	args.r_start	= -2.0;
	args.r_end		= 2.0;
	args.i_start	= -1.0;
	args.i_end		= 1.0;
	args.max_radius	= 1000.0;
	args.N_r		= 100;
	args.N_i		= 100;
	args.N_iters	= 1000;

	mandelbrot( (void *)&args);

}
