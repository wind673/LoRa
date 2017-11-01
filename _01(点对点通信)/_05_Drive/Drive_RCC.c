/*******************************(C) COPYRIGHT 2017 Wind��л���죩*********************************/
/**============================================================================
* @FileName    : Drive_RCC.c
* @Description : ʱ������
* @Date        : 2017/10/16
* @By          : Wind��л���죩
* @Email       : 1659567673@ qq.com
* @Platform    : Keil uVision5 v5.20 (STM32L151CB)
* @Explain     : None
*=============================================================================*/

/* ͷ�ļ����� ----------------------------------------------------------------*/
#include "Drive_RCC.h"

/* ˽�к궨�� ----------------------------------------------------------------*/

/* ˽�У���̬���������� ------------------------------------------------------*/

/* ȫ�ֱ������� --------------------------------------------------------------*/

/* ȫ�ֺ�����д --------------------------------------------------------------*/
/**----------------------------------------------------------------------------
* @FunctionName  : RCC_Init()
* @Description   : �ⲿ�жϳ�ʼ��
* @Data          : 2017/10/13
* @Explain       : None
-------------------------------------------------------------------------------
None
------------------------------------------------------------------------------*/
void RCC_Init(void)
{
    //RCC reset
    RCC_DeInit();
    //Enable HSI
    RCC_HSICmd(ENABLE);
    //wait HSI
    while(RCC_GetFlagStatus(RCC_FLAG_HSIRDY) == RESET);
    //Set bus clock
    RCC_HCLKConfig(RCC_SYSCLK_Div1);
    RCC_PCLK1Config(RCC_HCLK_Div1);
    RCC_PCLK2Config(RCC_HCLK_Div1);
    //HSI16M PLL-> 64M
    RCC_PLLConfig(RCC_PLLSource_HSI, RCC_PLLMul_4, RCC_PLLDiv_2); //��Ƶ�ͱ�Ƶ
    RCC_PLLCmd(ENABLE);
    while(RCC_GetFlagStatus(RCC_FLAG_PLLRDY) == RESET);
    //Select PLL as system clock source
    RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);
    while(RCC_GetSYSCLKSource() != 0x0C);
}




/*******************************(C) COPYRIGHT 2017 Wind��л���죩*********************************/





