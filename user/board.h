/**
  ******************************************************************************
  * @copyright   : Copyright To Hangzhou Dinova EP Technology Co.,Ltd
  * @file        : xxx.h
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
#ifndef __BOARD_H__
#define __BOARD_H__

#ifdef __cplusplus
 extern "C" {
#endif /* __cplusplus */

/* Includes ------------------------------------------------------------------*/
#ifdef STM32F429xx
#include "stm32f4xx_hal.h"
#elif STM32G474xx
#include "stm32g4xx_hal.h"
#endif

#include "sys_def.h"

/* Exported define -----------------------------------------------------------*/
#define KEY0_PIN_ID                     (115)
#define KEY1_PIN_ID                     (114)
#define KEY2_PIN_ID                     ( 45)
#define WKUP_PIN_ID                     (  0)

#define LED_RED_PIN_ID                  (16)
#define LED_BLUE_PIN_ID                 (17)

/* Exported typedef ----------------------------------------------------------*/

/* Exported macro ------------------------------------------------------------*/

/* Exported variable prototypes ----------------------------------------------*/

/* Exported function prototypes ----------------------------------------------*/
void board_init(void);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __BOARD_H__ */

