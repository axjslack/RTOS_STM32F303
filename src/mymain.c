#include "FreeRTOS.h"
#include "list.h"
#include "task.h"
#include "queue.h"

/* Including Header of Hardware Library */

#include "stm32f3_discovery.h"
#include "stm32f30x.h"


static uint64_t u64Ticks; 
//u64IdleTicksCnt;

void vMyTaskLed1(void *pvParameters)
{

	for(;;)
	{
		STM_EVAL_LEDOn(LED8);	
		vTaskDelay(500);
		GPIO_SetBits(GPIOF, GPIO_Pin_6);
		STM_EVAL_LEDOff(LED8);
		GPIO_ResetBits(GPIOF, GPIO_Pin_6);	
		vTaskDelay(500);
	}

}

void vMyTaskLed2(void *pvParameters)
{

	for(;;)
	{
		STM_EVAL_LEDOn(LED3);
		vTaskDelay(1000);
		STM_EVAL_LEDOff(LED3);
		vTaskDelay(1000);
	}

}





void myInit()
{
	STM_EVAL_LEDInit(LED8);
	STM_EVAL_LEDInit(LED5);
	STM_EVAL_LEDInit(LED3);
}


void vApplicationIdleHook( void )
{
  STM_EVAL_LEDOn(LED5);
}

int main()
{

	xTaskHandle  rtosTaskHandleArray[10];

	myInit();
	//xTaskCreate( vTaskLED1, ( signed char * ) "LED1", configMINIMAL_STACK_SIZE, NULL, 2, ( xTaskHandle * ) NULL);
	xTaskCreate( vMyTaskLed1, ( const char * ) "LED1", configMINIMAL_STACK_SIZE, NULL, 3, &rtosTaskHandleArray[0]);
	xTaskCreate( vMyTaskLed2, ( const char * ) "LED2", configMINIMAL_STACK_SIZE, NULL, 3, &rtosTaskHandleArray[1]);
	vTaskStartScheduler();

}

// Non ho ancora capito a cosa serve, ma si incazza se non glielo passo
void vApplicationTickHook( void ) {
    ++u64Ticks;
}

void vApplicationMallocFailedHook( void ) {
    configASSERT( 0 );  // Latch on any failure / error.
}


