#ifndef _MANDELBROT_H
#define _MANDELBROT_H

#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <complex.h>

struct mandelbrot_args
{
	double	r_start;
	double	r_end;
	double  i_start;
	double  i_end;
	double	max_radius;
	int		N_r;
	int		N_i;
	int		N_iters;
} ;

void mandelbrot( void * _args );


#endif
