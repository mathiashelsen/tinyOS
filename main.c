#include "OS_Core/tinyOS.h"

#include "stm32f4xx_gpio.h"

int main(void)
{

	uint16_t rr = 0x8000;
	uint32_t t;
	setupIO( );
	for(;;)
	{
		for(t = 0; t < 1680000; t++)
		{

		}

		rr = rr >> 1;
		if( rr < 0x1000 )
		{
			rr = 0x8000;
		}

		GPIO_Write(GPIOD, rr);

	}
	return 0;
}
