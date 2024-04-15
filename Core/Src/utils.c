#include "utils.h"

int fputc(int ch, FILE* f) {
    HAL_UART_Transmit(&huart1, (unsigned char*)&ch, 1, DEBUG_UART_TIMEOUT);
    return ch;
}

int fgetc(FILE* f) {
    unsigned char ch = 0;
    HAL_UART_Receive(&huart1, &ch, 1, DEBUG_UART_TIMEOUT);
    return ch;
}

//===============================================us延时函数
void delay_us(unsigned int us) // 主频72M
{
    unsigned int delay = (HAL_RCC_GetHCLKFreq() / 4000000 * us);
    while (delay--) { ; }
}

RESIST resist_data;
// ADC回调函数
void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef* hadc) {
    resist_data.adc_vol = HAL_ADC_GetValue(hadc);       // 获取ADC转换结果
    resist_data.vol = resist_data.adc_vol * 3.3 / 4095; // 转换为电压值
}

// 测试函数当电压小于0.5v时D0输出低电平光敏电阻上的LED指示灯被点亮
void Illumination_Test(void) {
    printf(
        "illumination src(0-4095) val :  %d illumination cvt(0-3.3v) val : %f\r\n",
        resist_data.adc_vol, resist_data.vol);
    if (resist_data.vol < 1.5) {
        DO_SET();
    } else {
        DO_RESET();
    }
}

unsigned int s1;
unsigned int s2;
float distance;
//===============================================读取距离
void Distance_Test(void) {
    htim2.Instance->CNT = 0;
    /* USER CODE END WHILE */
    TRIG_L;
    TRIG_H;
    HAL_Delay(1);
    TRIG_L;

    while (HAL_GPIO_ReadPin(ECHO_GPIO_Port, ECHO_Pin) == GPIO_PIN_RESET)
        s1 = htim2.Instance->CNT;
    while (HAL_GPIO_ReadPin(ECHO_GPIO_Port, ECHO_Pin) == GPIO_PIN_SET)
        s2 = htim2.Instance->CNT;
    distance = (s2 - s1) * 0.034 / 2;
    printf("Distance is : %0.1fcm\r\n", distance);
}
