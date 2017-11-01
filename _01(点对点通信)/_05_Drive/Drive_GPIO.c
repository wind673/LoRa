/*******************************(C) COPYRIGHT 2017 Wind��л���죩*********************************/
/**============================================================================
* @FileName    : Drive_GPIO.c
* @Description : None
* @Date        : 2016/8/7
* @By          : Wind��л���죩
* @Email       : 1659567673@ qq.com
* @Platform    : Keil uVision5 v5.20 (STM32L151CB)
* @Explain     : None
*=============================================================================*/

/* ͷ�ļ����� ----------------------------------------------------------------*/
#include "Drive_GPIO.h"

/* ˽�к궨�� ----------------------------------------------------------------*/

/* ˽�У���̬���������� ------------------------------------------------------*/

/* ȫ�ֱ������� --------------------------------------------------------------*/

/* ȫ�ֺ�����д --------------------------------------------------------------*/
/**----------------------------------------------------------------------------
* @FunctionName  : GPIO_Test_Init()
* @Description   : None
* @Data          : 2016/8/7
* @Explain       : 
-------------------------------------------------------------------------------
None
------------------------------------------------------------------------------*/ 
void GPIO_Test_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);     
	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_40MHz;
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;
	GPIO_Init(GPIOA, &GPIO_InitStructure);    
	
} 

/**----------------------------------------------------------------------------
* @FunctionName  : GPIO_Key_Init()     
* @Description   : �����ĳ�ʼ������ 
* @Data          : 2016/7/19
* @Explain       : PB2
------------------------------------------------------------------------------*/ 
void GPIO_Key_Init(void)
{ 
	GPIO_InitTypeDef GPIO_InitStructure;
	
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOB, ENABLE);     
	 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_40MHz;
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	
}


/**----------------------------------------------------------------------------
* @FunctionName  : GPIO_LED_Init()     
* @Description   : LED�ĳ�ʼ������ 
* @Data          : 2016/7/19
* @Explain       : R = PA0,  G = PA1,	B = PB11
------------------------------------------------------------------------------*/ 
void GPIO_LED_Init(void)
{ 
	GPIO_InitTypeDef GPIO_InitStructure;
	
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);     
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOB, ENABLE);  
	 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_40MHz;
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1;
	GPIO_Init(GPIOA, &GPIO_InitStructure); 
    
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;	 
	GPIO_Init(GPIOB, &GPIO_InitStructure);	 
	
}

 
/**----------------------------------------------------------------------------
* @FunctionName  : GPIO_Infrared_Init()     
* @Description   : ����IO�ڵĳ�ʼ������ 
* @Data          : 2016/10/14
* @Explain       : ����ʹ��
------------------------------------------------------------------------------*/ 
void GPIO_Infrared_Init(void)
{ 
	GPIO_InitTypeDef GPIO_InitStructure;
	
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);     
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_40MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure); 
	
}

 



/*******************************(C) COPYRIGHT 2017 Wind��л���죩*********************************/


















