/*******************************(C) COPYRIGHT 2017 Wind��л���죩*********************************/
/**============================================================================
* @FileName    : Drive_EXTI.c
* @Description : �ⲿ�ж�����	
* @Date        : 2016/8/8
* @By          : Wind��л���죩
* @Email       : 1659567673@ qq.com
* @Platform    : Keil uVision5 v5.20 (STM32L151CB)
* @Explain     : None
*=============================================================================*/

/* ͷ�ļ����� ----------------------------------------------------------------*/
#include "Drive_EXTI.h"

/* ˽�к궨�� ----------------------------------------------------------------*/

/* ˽�У���̬���������� ------------------------------------------------------*/

/* ȫ�ֱ������� --------------------------------------------------------------*/

/* ȫ�ֺ�����д --------------------------------------------------------------*/
/**----------------------------------------------------------------------------
* @FunctionName  : EXTI4_Init()
* @Description   : �ⲿ�жϳ�ʼ��
* @Data          : 2017/10/13
* @Explain       : None
-------------------------------------------------------------------------------
None
------------------------------------------------------------------------------*/ 
void EXTI4_Init(void)
{ 
    GPIO_InitTypeDef GPIO_InitStructure;
    EXTI_InitTypeDef EXTI_InitStructure;
    NVIC_InitTypeDef NVIC_InitStructure;
	
    //��ʼ��PA0�ܽ�
    /* Enable GPIOA clock */
    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);//��PB��ʱ��
    /* Configure PA0 pin as input floating */
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;//����
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;//���գ�������������
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;//�ܽ�	
    GPIO_Init(GPIOA, &GPIO_InitStructure);//��ʼ��	
	
    /* Enable SYSCFG clock */
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE); 
    SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOA, EXTI_PinSource4); 
    EXTI_InitStructure.EXTI_Line = EXTI_Line4;//�ж���  
    EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;//�ⲿ�ж�
    EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising_Falling;//�½��ش��� 
    EXTI_InitStructure.EXTI_LineCmd = ENABLE;
    EXTI_Init(&EXTI_InitStructure);//��ʼ��	
	
    /* Enable and set EXTI0 Interrupt to the lowest priority */
    NVIC_InitStructure.NVIC_IRQChannel = EXTI4_IRQn;//�ⲿ�ж�0����
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x04;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x00;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);  
}



 
/*******************************(C) COPYRIGHT 2017 Wind��л���죩*********************************/





