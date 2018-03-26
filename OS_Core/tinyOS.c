#include "tinyOS.h"

#define RET_FROM_EXCP 0xFFFFFFF9

volatile uint16_t rr = 0x8000;
volatile uint32_t myStackPtr = 0x0;
volatile struct scheduler *kernelSch;


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


    // Enable the clock to the timer 
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE); // APB1 clock: 168MHz/4 = 42 MHz
	// 42 MHz / 4 (prescaler) / = 50Hz (every 20ms)

    TIM_TimeBaseInitTypeDef TIMInit		= {0, }; 
    TIMInit.TIM_Prescaler				= 64;
    TIMInit.TIM_CounterMode				= TIM_CounterMode_Up;
    TIMInit.TIM_Period					= 32813;
    TIMInit.TIM_ClockDivision			= TIM_CKD_DIV4;

    // Init but DON'T enable
    TIM_TimeBaseInit(TIM2, &TIMInit );

    // Trigger output on update
    //TIM_SelectOutputTrigger(TIM2, TIM_TRGOSource_Update);

    // Enable interrupt
	
    TIM_ITConfig( TIM2, TIM_IT_Update, ENABLE);
    TIM_ClearITPendingBit( TIM2, TIM_IT_Update);

	NVIC_PriorityGroupConfig( NVIC_PriorityGroup_4 );

    NVIC_InitTypeDef NVIC_InitStructure;
    NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 3; // Higher priority than TIM3_IRQn
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);

	TIM_Cmd(TIM2, ENABLE);

	return 0;
}

// Tried using attribute isr, naked , but that doesnt work at all
// -> Correct for addition to stack in the assembly
__attribute__ ((naked)) 
void TIM2_IRQHandler(void)
{
	asm volatile( "push {lr}\r\n");
    if( TIM_GetITStatus( TIM2, TIM_IT_Update) != RESET )
    {
		TIM_ClearITPendingBit( TIM2, TIM_IT_Update );
		TIM_Cmd(TIM2, DISABLE);




		rr = rr >> 1;
		if( rr < 0x1000 )
		{
			rr = 0x8000;
		}

		GPIO_Write(GPIOD, rr);
		TIM_Cmd(TIM2, ENABLE);
		uint32_t stackPtr;

		// Retrieve stack pointer value
		/*
		asm volatile(	"mov %0, sp\n\r"  :"=r" (stackPtr) : : "memory");

		switchToNextTask ( kernelSch );


		// Retrieve stack pointer value
		asm volatile(	"mov %0, sp\n\r"  :"=r" (stackPtr) : : "memory");
		*/


		TIM_Cmd(TIM2, ENABLE);
    }
	asm volatile( "pop {pc}\r\n");
}
