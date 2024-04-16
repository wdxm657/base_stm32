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

// 光敏初始化
void Illumination_Initial(void) {
    HAL_GPIO_WritePin(GPIOA, MH_VCC_Pin, GPIO_PIN_SET);
    HAL_GPIO_WritePin(GPIOA, MH_GND_Pin, GPIO_PIN_RESET);
    HAL_Delay(500);
}

// 测试函数当电压小于1.5v时D0输出低电平光敏电阻上的LED指示灯被点亮
void Illumination_Test(void) {
    printf(
        "illumination src(0-4095) val :  %d illumination cvt(0-3.3v) val : %f\r\n",
        resist_data.adc_vol, resist_data.vol);
    if (resist_data.vol < 1.5) {
        // DO_SET();
    } else {
        // DO_RESET();
    }
}

unsigned int s1;
unsigned int s2;
float distance;
//===============================================读取距离
void Distance_Test(void) {
    // htim2.Instance->CNT = 0;
    // /* USER CODE END WHILE */
    // TRIG_L;
    // TRIG_H;
    // HAL_Delay(1);
    // TRIG_L;

    // while (HAL_GPIO_ReadPin(ECHO_GPIO_Port, ECHO_Pin) == GPIO_PIN_RESET)
    //     s1 = htim2.Instance->CNT;
    // while (HAL_GPIO_ReadPin(ECHO_GPIO_Port, ECHO_Pin) == GPIO_PIN_SET)
    //     s2 = htim2.Instance->CNT;
    // distance = (s2 - s1) * 0.034 / 2;
    // printf("Distance is : %0.1fcm\r\n", distance);
}

void RTC_Time_Test(RTC_DateTypeDef* GetData, RTC_TimeTypeDef* GetTime) {
    HAL_RTC_GetDate(&hrtc, GetData, RTC_FORMAT_BIN); // 获取日期
    HAL_RTC_GetTime(&hrtc, GetTime, RTC_FORMAT_BIN); // 获取时间

    /* Display date Format : yy/mm/dd */
    printf("%02d/%02d/%02d\r\n", 2000 + GetData->Year, GetData->Month,
           GetData->Date);
    if (GetData->WeekDay == 01) {
        printf("Monday\r\n");
    } else if (GetData->WeekDay == 02) {
        printf("Tuesday\r\n");
    } else if (GetData->WeekDay == 03) {
        printf("Wednesday\r\n");
    } else if (GetData->WeekDay == 04) {
        printf("Thursday\r\n");
    } else if (GetData->WeekDay == 05) {
        printf("Friday\r\n");
    } else if (GetData->WeekDay == 06) {
        printf("Saturday\r\n");
    } else if (GetData->WeekDay == 07) {
        printf("Sunday\r\n");
    }
    /* Display time Format : hh:mm:ss */
    printf("%02d:%02d:%02d\r\n", GetTime->Hours, GetTime->Minutes,
           GetTime->Seconds);

    printf("\r\n");

    HAL_Delay(1000);
}

void Pwm_Test(void) {
    uint16_t Pwm = 0;
    while (Pwm < 999) {
        Pwm++;
        __HAL_TIM_SetCompare(&htim2, TIM_CHANNEL_1, Pwm); // 设置比较值
        HAL_Delay(1); // 延时1ms不然改变太快
    }
    while (Pwm) {
        Pwm--;
        __HAL_TIM_SetCompare(&htim2, TIM_CHANNEL_1, Pwm); // 设置比较值
        HAL_Delay(1); // 延时1ms不然改变太快
    }
}

void Rev_Forw_Test(void) {
    // AIN 1   0       0       1
    // AIN 2   0       1       0
    //        STOP  REVERSE FORWARD
    printf("A  REVERSE\r\n");
    HAL_GPIO_WritePin(GPIOA, DRV_AIN1_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(GPIOA, DRV_AIN2_Pin, GPIO_PIN_SET);
    HAL_Delay(1000);
    printf("A  STOP\r\n");
    HAL_GPIO_WritePin(GPIOA, DRV_AIN1_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(GPIOA, DRV_AIN2_Pin, GPIO_PIN_RESET);
    HAL_Delay(1000);
    printf("A  FORWARD\r\n");
    HAL_GPIO_WritePin(GPIOA, DRV_AIN1_Pin, GPIO_PIN_SET);
    HAL_GPIO_WritePin(GPIOA, DRV_AIN2_Pin, GPIO_PIN_RESET);
    HAL_Delay(1000);
}

uint8_t Uart1_RxBuff[256];
uint8_t Uart1_Rx_Cnt = 0;
uint8_t aRxBuffer;
void HAL_UART_RxCpltCallback(UART_HandleTypeDef* huart) {
    if (strcmp((const char*)Uart1_RxBuff, "go stm32!") == 0) {
        // flag = 1;
        printf("start....\r\n");
    }
    if (strcmp((const char*)Uart1_RxBuff, "stop stm32!") == 0) {
        //  flag = 0;
        printf("stop....\r\n");
    }
    if (Uart1_Rx_Cnt >= 255) // 溢出判断
    {
        Uart1_Rx_Cnt = 0;
        memset(Uart1_RxBuff, 0x00, sizeof(Uart1_RxBuff));
        printf("overflow....\r\n");
    } else {
        Uart1_RxBuff[Uart1_Rx_Cnt++] = aRxBuffer; // 接收数据转存

        if ((Uart1_RxBuff[Uart1_Rx_Cnt - 1] == 0x0A)
            && (Uart1_RxBuff[Uart1_Rx_Cnt - 2] == 0x0D)) // 判断结束位
        {
            printf("Uart1_RxBuff %s\r\n", Uart1_RxBuff);
            printf("Uart1_Rx_Cnt %d\r\n", Uart1_Rx_Cnt);
            Uart1_Rx_Cnt = 0;
            memset(Uart1_RxBuff, 0x00, sizeof(Uart1_RxBuff)); // 6清空数组
        }
    }

    HAL_UART_Receive_IT(&huart1, (uint8_t*)&aRxBuffer, 1); // 再开启接收中断
}
