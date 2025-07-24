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
    
    pin_id = gpio_get("PB.0");
    
    gpio_set_mode(pin_id, PIN_OUTPUT_PP, PIN_PULL_UP);
    
    while (1)
    {
        gpio_write(pin_id, 0);
        HAL_Delay(500);
        gpio_write(pin_id, 1);
        HAL_Delay(500);
    }
}