/**
  ******************************************************************************
  * @copyright   : Copyright To Hangzhou Dinova EP Technology Co.,Ltd
  * @file        : xxxx.c
  * @author      : ZJY
  * @version     : V1.0
  * @data        : 20xx-xx-xx
  * @brief       : 
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
#include "stm32_gpio.h"

#include "stimer.h"
#include "gpio_key.h"
#include "SEGGER_RTT.h"
#include "log.h"

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
static void Error_Handler(void);
static void SystemClock_Config(void);
static void rtt_output_handler(const char *msg, size_t len);

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
    SystemClock_Config();
    
    /* Initialize all configured peripherals */
    stm32_gpio_init();
    
    SEGGER_RTT_Init();
    log_register_handler("rtt", rtt_output_handler);
    log_enable_handler("rtt");
    
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
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 15;
  RCC_OscInitStruct.PLL.PLLN = 216;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 4;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Activate the Over-Drive mode
  */
  if (HAL_PWREx_EnableOverDrive() != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5) != HAL_OK)
  {
    Error_Handler();
  }
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

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
    /* User can add his own implementation to report the HAL error return state */
    __disable_irq();
    while (1)
    {
        
    }
}

/**
 * RTT输出处理器
 */
static void rtt_output_handler(const char *msg, size_t len)
{
    SEGGER_RTT_ASM_WriteSkipNoLock(0, msg, len);
}
/* Private functions ---------------------------------------------------------*/


