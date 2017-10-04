#include "tinyOS.h"

int setupIO( )
{
	// Very particular to STM32

	RCC_DeInit();
 
    /* enable clock to GPIOC */
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);

	GPIO_InitTypeDef gpio_init;
	gpio_init.GPIO_Pin		= GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;
	gpio_init.GPIO_Mode		= GPIO_Mode_OUT;
	gpio_init.GPIO_Speed	= GPIO_Speed_2MHz;
	gpio_init.GPIO_OType	= GPIO_OType_PP;
	gpio_init.GPIO_PuPd		= GPIO_PuPd_NOPULL;

	GPIO_Init( GPIOD , &gpio_init);

	return 0;
}
