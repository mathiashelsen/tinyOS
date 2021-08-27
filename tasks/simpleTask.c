#include "stm32f4xx_gpio.h"

volatile uint16_t rr = 0x8000;

void simpleTask(void * _args)
{
    int i = 0;
    while(1)
    {
        rr = rr >> 1;
        if( rr < 0x1000 )
        {
                rr = 0x8000;
        }

        GPIO_Write(GPIOD, rr);

        for(i = 0; i < 100000 ; i+= 1){
        }
    }
}

void simpleTask2(void * _args)
{
    while(1)
    {
        rr = 0x8000;
        GPIO_Write(GPIOD, rr);
    }
}
