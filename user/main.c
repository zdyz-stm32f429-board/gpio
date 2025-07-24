/**
 ******************************************************************************
 * @file    main.c
 * @author  xxx
 * @brief   main.c.
 ******************************************************************************
 */
/* Includes ------------------------------------------------------------------*/
#include "board.h"
#include "gpio.h"
#include "EventRecorder.h"
#include <stdio.h>

/* Private typedef -----------------------------------------------------------*/

/* Private define ------------------------------------------------------------*/
#define KEY0_PIN_ID        (115)
#define KEY1_PIN_ID        (114)
#define KEY2_PIN_ID        ( 45)
#define WKUP_PIN_ID        (  0)
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
    gpio_set_mode(16, PIN_OUTPUT_PP, PIN_PULL_UP);
    gpio_set_mode(17, PIN_OUTPUT_PP, PIN_PULL_UP);
    gpio_write(16, 1);
    gpio_write(17, 1);
    
    /* set key gpio mode */
    gpio_set_mode(KEY0_PIN_ID, PIN_INPUT, PIN_PULL_UP);
    gpio_set_mode(KEY1_PIN_ID, PIN_INPUT, PIN_PULL_UP);
    gpio_set_mode(KEY2_PIN_ID, PIN_INPUT, PIN_PULL_UP);
    gpio_set_mode(WKUP_PIN_ID, PIN_INPUT, PIN_PULL_DOWN);
    
    gpio_attach_irq(KEY0_PIN_ID, PIN_IRQ_MODE_FALLING, key0_handle, NULL);
    gpio_irq_enable(KEY0_PIN_ID, 1);
    
    gpio_attach_irq(KEY1_PIN_ID, PIN_IRQ_MODE_FALLING, key1_handle, NULL);
    gpio_irq_enable(KEY1_PIN_ID, 1);
    
    gpio_attach_irq(KEY2_PIN_ID, PIN_IRQ_MODE_FALLING, key2_handle, NULL);
    gpio_irq_enable(KEY2_PIN_ID, 1);
    
    gpio_attach_irq(WKUP_PIN_ID, PIN_IRQ_MODE_RISING, wkup_key_handle, NULL);
    gpio_irq_enable(WKUP_PIN_ID, 1);
    
    while (1)
    {
        gpio_write(16, 0);
        gpio_write(17, 1);
        HAL_Delay(500);
        gpio_write(16, 1);
        gpio_write(17, 0);
        HAL_Delay(500);
    }
}