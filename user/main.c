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
static void key0_handle(void *args)
{
    printf("key0_down!\r\n");
}

static void key1_handle(void *args)
{
    printf("key1_down!\r\n");
}

static void key2_handle(void *args)
{
    printf("key2_down!\r\n");
}

static void wkup_key_handle(void *args)
{
    printf("wkup_key_down!\r\n");
}
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
    
    /* set key gpio mode */
    gpio_attach_irq(KEY0_PIN_ID, PIN_EVENT_FALLING_EDGE, key0_handle, NULL);
    gpio_irq_enable(KEY0_PIN_ID, 1);
    
    gpio_attach_irq(KEY1_PIN_ID, PIN_EVENT_FALLING_EDGE, key1_handle, NULL);
    gpio_irq_enable(KEY1_PIN_ID, 1);
    
    gpio_attach_irq(KEY2_PIN_ID, PIN_EVENT_FALLING_EDGE, key2_handle, NULL);
    gpio_irq_enable(KEY2_PIN_ID, 1);
    
    gpio_attach_irq(WKUP_PIN_ID, PIN_EVENT_RISING_EDGE, wkup_key_handle, NULL);
    gpio_irq_enable(WKUP_PIN_ID, 1);
    
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
