
#include "FreeRTOS.h"
#include "task.h"
#include "timers.h"
#include "semphr.h"

/*
The content of the freertos include directory

croutine.h
event_groups.h
FreeRTOSConfig.h
FreeRTOS.h
list.h
mpu_wrappers.h
portable.h
projdefs.h
queue.h
semphr.h
StackMacros.h  
stdint.readme  
task.h  
timers.h
*/

#include "stm32f30x.h"
#include "stm32f3_discovery.h"


static uint64_t u64Ticks=0; 
static uint64_t u64IdleTicksCnt=0; 

static void Delay(__IO uint32_t nTime);

static void TimingDelay_Decrement(void);

void SysTick_Handler(void);

/* Private variables ---------------------------------------------------------*/
  RCC_ClocksTypeDef RCC_Clocks;
__IO uint32_t TimingDelay = 0;

/* Private function prototypes -----------------------------------------------*/
void TimingDelay_Decrement(void);
void Delay(__IO uint32_t nTime);

/* Private functions ---------------------------------------------------------*/



/* ----- SysTick definitions ----------------------------------------------- */

#define SYSTICK_FREQUENCY_HZ       1000

/* ----- LED definitions --------------------------------------------------- */

/* STM32F3DISCOVERY definitions (the GREEN LED) */
/* Adjust them for your own board. */

#define BLINK_PORT      GPIOE
#define BLINK_PIN       15
#define BLINK_RCC_BIT   RCC_AHBPeriph_GPIOE

#define BLINK_TICKS     SYSTICK_FREQUENCY_HZ/2


static __IO uint32_t uwTimingDelay;

void Delay(__IO uint32_t nTime)
{
  uwTimingDelay = nTime;
  while (uwTimingDelay != 0)
    ;
}

/**
 * @brief  Decrements the TimingDelay variable.
 * @param  None
 * @retval None
 */
void
TimingDelay_Decrement(void)
{
  if (uwTimingDelay != 0x00)
    {
      uwTimingDelay--;
    }
}

// ----------------------------------------------------------------------------

/**
 * @brief  This function is the SysTick Handler.
 * @param  None
 * @retval None
 */
/*void SysTick_Handler(void)
{
  TimingDelay_Decrement();
}*/

// ----------------------------------------------------------------------------




static void vLedTask ( void *pvParameters )
	{
		
		int seconds = 0;
		RCC_GetClocksFreq(&RCC_Clocks);
  		SysTick_Config(RCC_Clocks.HCLK_Frequency / SYSTICK_FREQUENCY_HZ);

  		/* GPIO Periph clock enable */
  		RCC_AHBPeriphClockCmd(BLINK_RCC_BIT, ENABLE);

  		GPIO_InitTypeDef GPIO_InitStructure;

		/* Configure pin in output push/pull mode */
		GPIO_InitStructure.GPIO_Pin = (1 << BLINK_PIN);
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
		GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
		GPIO_Init(BLINK_PORT, &GPIO_InitStructure);
		
		while(1)
			{
			/* Assume the LED is active low */

			/* Turn on led by setting the pin low */
			GPIO_ResetBits(BLINK_PORT, (1 << BLINK_PIN));

			Delay(BLINK_TICKS);

			/* Turn off led by setting the pin high */
			GPIO_SetBits(BLINK_PORT, (1 << BLINK_PIN));

			Delay(BLINK_TICKS);

			++seconds;

			}
	}

/* Task table */
xTaskHandle  rtosTaskHandleArray[10];


int main(void)
{
	
	xTaskCreate ( vLedTask, ( const char * ) "LED", configMINIMAL_STACK_SIZE, NULL, 3, &rtosTaskHandleArray[1]);
	vTaskStartScheduler();


}

// This FreeRTOS callback function gets called once per tick (default = 1000Hz).
// ---------------------------------------------------------------------------- 
void vApplicationTickHook( void ) {
    ++u64Ticks;
}

// This FreeRTOS call-back function gets when no other task is ready to execute.
// On a completely unloaded system this is getting called at over 2.5MHz!
// ---------------------------------------------------------------------------- 
void vApplicationIdleHook( void ) {
    ++u64IdleTicksCnt;
}

// A required FreeRTOS function.
// ---------------------------------------------------------------------------- 
void vApplicationMallocFailedHook( void ) {
    configASSERT( 0 );  // Latch on any failure / error.
}





