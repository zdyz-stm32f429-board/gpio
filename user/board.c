/**
  ******************************************************************************
  * @copyright   : Copyright To Hangzhou Dinova EP Technology Co.,Ltd
  * @file        : xxxx.c
  * @author      : ZJY
  * @version     : V1.0
  * @data        : 20xx-xx-xx
  * @brief       : 
  * @attattention: None
  ******************************************************************************
  * @history     :
  *         V1.0 : 1.xxx
  *
  *
  ******************************************************************************
  */
/* Includes ------------------------------------------------------------------*/
#include "board.h"
#include "stm32_clk.h"
#include "stm32_gpio.h"

#include "stimer.h"
#include "gpio_key.h"

#if defined(SOC_SERIES_STM32F1)
    #include "stm32f1xx.h"
#elif defined(SOC_SERIES_STM32F4)
    #include "stm32f4xx.h"
#elif defined(SOC_SERIES_STM32G4)
    #include "stm32g4xx.h"
#else
#error "Please select first the soc series used in your application!"    
#endif
/* Private typedef -----------------------------------------------------------*/

/* Private define ------------------------------------------------------------*/

/* Private macro -------------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/
gpio_key_cfg_t key_cfg[] = {
    {
        .pin_id = KEY0_PIN_ID,
        .active_low = 1,
    },
    {
        .pin_id = KEY1_PIN_ID,
        .active_low = 1,
    },
    {
        .pin_id = KEY2_PIN_ID,
        .active_low = 1,
    },
    {
        .pin_id = WKUP_PIN_ID,
        .active_low = 0,
    }
};

key_t key[KEY_ID_MAX];

/* Exported variables  -------------------------------------------------------*/

/* Private function prototypes -----------------------------------------------*/

/* Exported functions --------------------------------------------------------*/
/**
  * @brief  
  * @param  
  * @retval 
  * @note   
  */
void board_init(void)
{
    /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
    HAL_Init();
    
    /* Configure the system clock */
    stm32_clk_init();
    
    /* Initialize all configured peripherals */
    stm32_gpio_init();
    
    stimer_init(HAL_GetTick);
    
    /* gpio 按键注册 */
    gpio_key_register(&key[0], KEY0, &key_cfg[0]);
    gpio_key_register(&key[1], KEY1, &key_cfg[1]);
    gpio_key_register(&key[2], KEY2, &key_cfg[2]);
    gpio_key_register(&key[3], WKUP_KEY, &key_cfg[3]);
    
    key_init();
    key_start(&key[KEY0]);
    key_start(&key[KEY1]);
    key_start(&key[KEY2]);
    key_start(&key[WKUP_KEY]);
}

/**
  * Initializes the Global MSP.
  */
void HAL_MspInit(void)
{
#if defined(SOC_SERIES_STM32F1)
    __HAL_RCC_AFIO_CLK_ENABLE();
    __HAL_AFIO_REMAP_SWJ_NOJTAG(); /* NOJTAG: JTAG-DP Disabled and SW-DP Enabled */
#else
    __HAL_RCC_SYSCFG_CLK_ENABLE();
#endif
    
    __HAL_RCC_PWR_CLK_ENABLE();
}
/* Private functions ---------------------------------------------------------*/


