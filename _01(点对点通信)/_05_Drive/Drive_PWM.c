/*******************************(C) COPYRIGHT 2017 Wind��л���죩*********************************/
/**============================================================================
* @FileName    : Drive_PWM.c
* @Description : ��ʱ������
* @Date        : 2017/10/14
* @By          : Wind��л���죩
* @Email       : 1659567673@ qq.com
* @Platform    : Keil uVision5 v5.20 (STM32L151CB)
* @Explain     : None
*=============================================================================*/

/* ͷ�ļ����� ----------------------------------------------------------------*/
#include "Drive_PWM.h"

/* ˽�к궨�� ----------------------------------------------------------------*/

/* ˽�У���̬���������� ------------------------------------------------------*/

/* ȫ�ֱ������� --------------------------------------------------------------*/
u16 Time3_PWM_Period = 0;

/* ȫ�ֺ�����д --------------------------------------------------------------*/
/**----------------------------------------------------------------------------
* @FunctionName  : TIM3_PWM_Init()
* @Description   : PWM��ʼ��
* @Data          : 2017/10/13
* @Explain       : None
-------------------------------------------------------------------------------
None
------------------------------------------------------------------------------*/
void TIM3_PWM_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
    TIM_OCInitTypeDef TIM_OCInitStructure;
	
    /* ʹ������ʱ�� */  
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM9, ENABLE);//ʹ��TIM9ʱ��
    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOB, ENABLE);	//ʹ��GPIOB

    /* GPIO���� */  
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;		//ѡ������ 
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;  	//GPIO�������ù���
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP; 	//����ʽ���
    GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_UP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_40MHz; 
    GPIO_Init(GPIOA, &GPIO_InitStructure); 
    GPIO_PinAFConfig(GPIOA, GPIO_PinSource6, GPIO_AF_TIM9); //GPIO����TIM���ù���
	
    /* ʱ��������� */ 
    TIM_TimeBaseStructure.TIM_Prescaler = 40 - 1;				//Ԥ��Ƶ��Ϊ1 
    TIM_TimeBaseStructure.TIM_Period = 100 - 1;					//�Զ���װ�ؼĴ�������ֵΪ249 
    TIM_TimeBaseStructure.TIM_ClockDivision = 0; 				//ʱ�ӷָ�Ϊ0 
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up; //������ģʽ 
    TIM_TimeBaseInit(TIM9, &TIM_TimeBaseStructure);
	Time3_PWM_Period = TIM_TimeBaseStructure.TIM_Period;
	
    /* ����Ƚ����� */ 
    TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;  							//TIM�������1ģʽ
    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;  				//TIM�Ƚ����ʹ��
    TIM_OCInitStructure.TIM_Pulse = Time3_PWM_Period*0.5f - 1; 	//ռ�ձ�Ϊ50%
    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;   				//*����Ƚϼ��Ը�
    TIM_OC2Init(TIM9, &TIM_OCInitStructure); 
    TIM_OC2PreloadConfig(TIM9, TIM_OCPreload_Enable);							//*ʹ��TIM��CRR2�ϵ�Ԥװ�ؼĴ���
    TIM_ARRPreloadConfig(TIM9, ENABLE);											//*ʹ��TIM��ARR�ϵ�Ԥװ�ؼĴ�
    TIM_Cmd(TIM9, ENABLE);														//*ʹ������TIM
	
}


/**----------------------------------------------------------------------------
* @FunctionName  : TIM3_PWM_SetH()
* @Description   : PWM�ߵ�ƽռ�ձ�
* @Data          : 2017/10/13
* @Explain       : None
-------------------------------------------------------------------------------
None
------------------------------------------------------------------------------*/
void TIM3_PWM_SetH(float _Percent)
{ 
    TIM_OCInitTypeDef TIM_OCInitStructure; 
	
    /* ����Ƚ����� */ 
    TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;	//TIM�������1ģʽ
    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; 	//TIM�Ƚ����ʹ��
    TIM_OCInitStructure.TIM_Pulse = Time3_PWM_Period *_Percent - 1; 	//ռ�ձ�Ϊ50%
    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;	//*����Ƚϼ��Ը�
    TIM_OC2Init(TIM9, &TIM_OCInitStructure); 
    TIM_OC2PreloadConfig(TIM9, TIM_OCPreload_Enable);	//*ʹ��TIM��CRR2�ϵ�Ԥװ�ؼĴ���
    TIM_ARRPreloadConfig(TIM9, ENABLE);		//*ʹ��TIM��ARR�ϵ�Ԥװ�ؼĴ�
    TIM_Cmd(TIM9, ENABLE);		//*ʹ������TIM

}


/*******************************(C) COPYRIGHT 2017 Wind��л���죩*********************************/





