#include "OS_Core/tinyOS.h"

#include "stm32f4xx_gpio.h"

extern volatile uint32_t myStackPtr;

int calcFact(int n)
{
	if(n == 1)
	{
		return n;
	} else {
		return n*calcFact(n-1);
	}
}

int main(void)
{
	int i = 2;
	int j = 0;
	int z = 0;
	setupIO( );

	for(;;)
	{
		//j = calcFact(i);
		j = (int) &calcFact;
		asm volatile(	"bx %0\n\r" : : "r" (j) : "memory");
		z = (int) myStackPtr;

		if(j == z)
			j = 2;

		i++;
		if( i > 100 )
			i = 2;
	}
	return 0;
}
