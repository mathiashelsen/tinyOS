#ifndef _LOGMAP_H
#define _LOGMAP_H

#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <complex.h>

struct logMap_args
{
	double	r_start;
	double	r_end;
	int		N_r;
	int		N_iters;
	int		N_saves;
	double	*results;
} ;

void logMap( void * _args );

#endif
