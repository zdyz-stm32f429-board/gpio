/**
  ******************************************************************************
  * @file        : xxx.h
  * @author      : ZJY
  * @version     : V1.0
  * @date        : 20xx-xx-xx
  * @brief       : 
  * @attattention: None
  ******************************************************************************
  * @history     :
  *         V1.0 : 1.xxx
  *
  *
  ******************************************************************************
  */
#ifndef __SYS_CONFIG_H__
#define __SYS_CONFIG_H__

#ifdef __cplusplus
 extern "C" {
#endif /* __cplusplus */

/* Includes ------------------------------------------------------------------*/

/* Exported define -----------------------------------------------------------*/
/* 使用的芯片 */
#define SOC_SERIES_STM32F4

#define USING_RTOS                      0

#define SYS_CONFIG_NAME_MAX             8

#define LOG_ASSERT_ENABLE               1
#if (LOG_ASSERT_ENABLE == 0)
    #define NODEBUG
#endif

/* LOG configure define */
#define USING_LOG                       1
#define LOG_OUTPUT_LVL_D
#define LOG_OUTPUT_LVL                  7
#define LOG_LINE_BUF_SIZE               128

/* Kernel configure define */
#define USING_HW_ATOMIC

/* Exported typedef ----------------------------------------------------------*/

/* Exported macro ------------------------------------------------------------*/

/* Exported variable prototypes ----------------------------------------------*/

/* Exported function prototypes ----------------------------------------------*/

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __SYS_CONFIG_H__ */
