
#ifndef __UTILS_H__
#define __UTILS_H__

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "adc.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"
typedef struct {
    unsigned int adc_vol; // ADC测量
    float vol;            // 实际电压

} RESIST;

#define DEBUG_UART_TIMEOUT 500
// IO口定义
#define DO_SET() HAL_GPIO_WritePin(MH_DO_GPIO_Port, MH_DO_Pin, GPIO_PIN_SET)
#define DO_RESET() HAL_GPIO_WritePin(MH_DO_GPIO_Port, MH_DO_Pin, GPIO_PIN_RESET)

#define TRIG_H HAL_GPIO_WritePin(TRIG_GPIO_Port, TRIG_Pin, GPIO_PIN_SET)
#define TRIG_L HAL_GPIO_WritePin(TRIG_GPIO_Port, TRIG_Pin, GPIO_PIN_RESET)

void Illumination_Test(void);
void Distance_Test(void);
#ifdef __cplusplus
}
#endif

#endif /* __UTILS_H__ */
