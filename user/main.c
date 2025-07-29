/**
  ******************************************************************************
  * @file        : main.c
  * @author      : ZJY
  * @version     : V1.0
  * @date        : 2024-09-26
  * @brief       : Main program body
  * @attention   : None
  ******************************************************************************
  * @history     :
  *         V1.0 : 1.xxx
  *
  *
  ******************************************************************************
  */
/* Includes ------------------------------------------------------------------*/
#include "board.h"
#include "gpio.h"
#include "EventRecorder.h"
#include <stdio.h>

/* Private typedef -----------------------------------------------------------*/

/* Private define ------------------------------------------------------------*/

/* Private macro -------------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/
size_t pin_id = 0;
/* Private function prototypes -----------------------------------------------*/

/* Private functions ---------------------------------------------------------*/

/* Exported functions --------------------------------------------------------*/
/**
 * @brief  Main program
 * @param  None
 * @retval None
 */
int main(void)
{ 
    board_init();
    
    EventRecorderInitialize(EventRecordAll, 1);
    EventRecorderStart();
    HAL_Delay(500); // 等待系统稳定
    
    pin_id = gpio_get("PB.0");
    
    /* set led gpio mode */
    gpio_set_mode(LED_RED_PIN_ID, PIN_OUTPUT_PP, PIN_PULL_UP);
    gpio_set_mode(LED_BLUE_PIN_ID, PIN_OUTPUT_PP, PIN_PULL_UP);
    gpio_write(LED_RED_PIN_ID, 1);
    gpio_write(LED_BLUE_PIN_ID, 1);
    
    while (1)
    {
        gpio_write(LED_RED_PIN_ID, 0);
        gpio_write(LED_BLUE_PIN_ID, 1);
        HAL_Delay(500);
        gpio_write(LED_RED_PIN_ID, 1);
        gpio_write(LED_BLUE_PIN_ID, 0);
        HAL_Delay(500);
    }
}
