/*******************************(C) COPYRIGHT 2017 Wind��л���죩*********************************/
/**============================================================================
* @FileName    : Drive_Timer.c
* @Description : ��ʱ������	
* @Date        : 2017/10/13
* @By          : Wind��л���죩
* @Email       : 1659567673@ qq.com
* @Platform    : Keil uVision5 v5.20 (STM32L151CB)
* @Explain     : None
*=============================================================================*/

/* ͷ�ļ����� ----------------------------------------------------------------*/
#include "Drive_Timer.h"

/* ˽�к궨�� ----------------------------------------------------------------*/ 

/* ˽�У���̬���������� ------------------------------------------------------*/

/* ȫ�ֱ������� --------------------------------------------------------------*/ 
u16 Time3_PWM_Period = 0;

/* ȫ�ֺ�����д --------------------------------------------------------------*/
/**----------------------------------------------------------------------------
* @FunctionName  : TIM2_Init()
* @Description   : ��ʱ����ʼ��
* @Data          : 2017/10/13
* @Explain       : ����ʱ�� 
-------------------------------------------------------------------------------
None
------------------------------------------------------------------------------*/ 
void TIM2_Init(void)
{ 
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE); //ʱ��ʹ��
	
	//��ʱ��TIM3��ʼ��
	TIM_TimeBaseStructure.TIM_Prescaler = (u32)(Bsp_Clocks.PCLK1_Frequency /1000000) - 1; //����������ΪTIMxʱ��Ƶ�ʳ�����Ԥ��Ƶֵ
	TIM_TimeBaseStructure.TIM_Period = 0xffff - 1; //��������һ�������¼�װ�����Զ���װ�ؼĴ������ڵ�ֵ	
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; //����ʱ�ӷָ�:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM���ϼ���ģʽ
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure); //����ָ���Ĳ�����ʼ��TIMx��ʱ�������λ
 
	TIM_ITConfig(TIM2,TIM_IT_Update,ENABLE); //ʹ��ָ����TIMx�ж�,��������ж�
	
	//�ж����ȼ�NVIC����
	NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;  //TIM2�ж�
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;  //��ռ���ȼ� 
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;  //�����ȼ� 
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //IRQͨ����ʹ��
	NVIC_Init(&NVIC_InitStructure);  //��ʼ��NVIC�Ĵ���
	TIM_Cmd(TIM2, ENABLE);  //ʹ��TIMx	
}

/**----------------------------------------------------------------------------
* @FunctionName  : TIM4_Init()
* @Description   : ��ʱ����ʼ��
* @Data          : 2017/10/13
* @Explain       : �������߳�
-------------------------------------------------------------------------------
None
------------------------------------------------------------------------------*/ 
void TIM4_Init(void)
{	
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE); //ʱ��ʹ��
	
	//��ʱ��TIM3��ʼ��
	TIM_TimeBaseStructure.TIM_Prescaler = (u32)(Bsp_Clocks.PCLK1_Frequency /1000000) - 1; //����������ΪTIMxʱ��Ƶ�ʳ�����Ԥ��Ƶֵ
	TIM_TimeBaseStructure.TIM_Period = OS_TIME_SLICE - 1; //��������һ�������¼�װ�����Զ���װ�ؼĴ������ڵ�ֵ	
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; //����ʱ�ӷָ�:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM���ϼ���ģʽ
	TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure); //����ָ���Ĳ�����ʼ��TIMx��ʱ�������λ
 
	TIM_ITConfig(TIM4,TIM_IT_Update,ENABLE); //ʹ��ָ����TIMx�ж�,��������ж�
	
	//�ж����ȼ�NVIC����
	NVIC_InitStructure.NVIC_IRQChannel = TIM4_IRQn;  //TIM2�ж�
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = OS_THREAD_PRIMARY;  //��ռ���ȼ� 
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;  //�����ȼ� 
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //IRQͨ����ʹ��
	NVIC_Init(&NVIC_InitStructure);  //��ʼ��NVIC�Ĵ���
	TIM_Cmd(TIM4, ENABLE);  //ʹ��TIMx	
}	


/**----------------------------------------------------------------------------
* @FunctionName  : TIM6_Init()
* @Description   : ��ʱ����ʼ��
* @Data          : 2017/10/13
* @Explain       : ����ϵͳ�߳� 
-------------------------------------------------------------------------------
None
------------------------------------------------------------------------------*/ 
void TIM6_Init(void)
{
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM6, ENABLE); //ʱ��ʹ��
	
	//��ʱ��TIM6��ʼ��
	TIM_TimeBaseStructure.TIM_Prescaler = (u32)(Bsp_Clocks.PCLK1_Frequency /1000000) - 1; //����������ΪTIMxʱ��Ƶ�ʳ�����Ԥ��Ƶֵ
	TIM_TimeBaseStructure.TIM_Period = OS_TIME_SLICE - 1; //��������һ�������¼�װ�����Զ���װ�ؼĴ������ڵ�ֵ	
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; //����ʱ�ӷָ�:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM���ϼ���ģʽ
	TIM_TimeBaseInit(TIM6, &TIM_TimeBaseStructure); //����ָ���Ĳ�����ʼ��TIMx��ʱ�������λ
	
	TIM_ITConfig(TIM6,TIM_IT_Update,ENABLE); //ʹ��ָ����TIMx�ж�,��������ж�
	
	//�ж����ȼ�NVIC����
	NVIC_InitStructure.NVIC_IRQChannel = TIM6_IRQn;  //TIM�ж�
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = OS_THREAD_SYSTEM;  //��ռ���ȼ� 
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;  //�����ȼ� 
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //IRQͨ����ʹ��
	NVIC_Init(&NVIC_InitStructure);  //��ʼ��NVIC�Ĵ���
	TIM_Cmd(TIM6, ENABLE);  //ʹ��TIMx	
	
} 


/**----------------------------------------------------------------------------
* @FunctionName  : TIM9_PWM_Init()
* @Description   : PWM��ʼ��
* @Data          : 2017/10/14
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
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);//ʹ��TIMʱ��
    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);	//ʹ��GPIO

    /* GPIO���� */  
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;		//ѡ������ 
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;  	//GPIO�������ù���
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP; 	//����ʽ���
    GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_UP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_40MHz; 
    GPIO_Init(GPIOA, &GPIO_InitStructure); 
    GPIO_PinAFConfig(GPIOA, GPIO_PinSource6, GPIO_AF_TIM3); //GPIO����TIM���ù���
	
    /* ʱ��������� */ 
    TIM_TimeBaseStructure.TIM_Prescaler = (u32)(Bsp_Clocks.PCLK1_Frequency /1000000) - 1;	//Ԥ��Ƶ��Ϊ 
    TIM_TimeBaseStructure.TIM_Period = 26 - 1;	//�Զ���װ�ؼĴ�������ֵΪ26us
    TIM_TimeBaseStructure.TIM_ClockDivision = 0;	//ʱ�ӷָ�Ϊ0 
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up; //������ģʽ 
    TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);
	Time3_PWM_Period = TIM_TimeBaseStructure.TIM_Period;
	
    /* ����Ƚ����� */ 
    TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;	//TIM�������1ģʽ
    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;	//TIM�Ƚ����ʹ��
    TIM_OCInitStructure.TIM_Pulse = Time3_PWM_Period*0/100;	//ռ�ձ�Ϊ0%	
    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;	//*����Ƚϼ��Ը�	
    TIM_OC1Init(TIM3, &TIM_OCInitStructure); 	
    TIM_OC1PreloadConfig(TIM3, TIM_OCPreload_Enable);	//*ʹ��TIM��CRR2�ϵ�Ԥװ�ؼĴ���
    TIM_ARRPreloadConfig(TIM3, ENABLE);	//*ʹ��TIM��ARR�ϵ�Ԥװ�ؼĴ�
    TIM_Cmd(TIM3, ENABLE);	//*ʹ������TIM
	
}


/**----------------------------------------------------------------------------
* @FunctionName  : TIM9_PWM_SetH()
* @Description   : PWM�ߵ�ƽռ�ձ�
* @Data          : 2017/10/14
* @Explain       : None
-------------------------------------------------------------------------------
None
------------------------------------------------------------------------------*/
void TIM3_PWM_SetH(u8 _Percent)
{ 
    TIM_OCInitTypeDef TIM_OCInitStructure;  
	
    /* ����Ƚ����� */ 
    TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;	//TIM�������1ģʽ
    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;	//TIM�Ƚ����ʹ��
    TIM_OCInitStructure.TIM_Pulse = Time3_PWM_Period*_Percent/100;	//ռ�ձ�Ϊ50%	
    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;	//*����Ƚϼ��Ը�
    TIM_OC1Init(TIM3, &TIM_OCInitStructure); 
    TIM_OC1PreloadConfig(TIM3, TIM_OCPreload_Enable);	//*ʹ��TIM��CRR2�ϵ�Ԥװ�ؼĴ���
    TIM_ARRPreloadConfig(TIM3, ENABLE);	//*ʹ��TIM��ARR�ϵ�Ԥװ�ؼĴ� 
    TIM_Cmd(TIM3, ENABLE);	//*ʹ������TIM 
	
}




/**----------------------------------------------------------------------------
* @FunctionName  : TIM7_Init()
* @Description   : ��ʱ����ʼ��
* @Data          : 2017/10/13
* @Explain       : None
-------------------------------------------------------------------------------
None
------------------------------------------------------------------------------*/ 
void TIM7_Init(void)
{  
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure;  
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM7, ENABLE); //ʱ��ʹ��
	 
	//��ʱ��TIM6��ʼ��
	TIM_TimeBaseStructure.TIM_Prescaler = (u32)(Bsp_Clocks.PCLK1_Frequency /1000000) - 1; //����������ΪTIMxʱ��Ƶ�ʳ�����Ԥ��Ƶֵ
	TIM_TimeBaseStructure.TIM_Period = 0xffff - 1; //��������һ�������¼�װ�����Զ���װ�ؼĴ������ڵ�ֵ	
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; //����ʱ�ӷָ�:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM���ϼ���ģʽ
	TIM_TimeBaseInit(TIM7, &TIM_TimeBaseStructure); //����ָ���Ĳ�����ʼ��TIMx��ʱ�������λ
	
	TIM_ITConfig(TIM7,TIM_IT_Update,ENABLE); //ʹ��ָ����TIMx�ж�,��������ж�
	
	//�ж����ȼ�NVIC����
	NVIC_InitStructure.NVIC_IRQChannel = TIM7_IRQn;  //TIM�ж�
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = OS_THREAD_PRIMARY - 1;  //��ռ���ȼ� 
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;  //�����ȼ� 
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //IRQͨ����ʹ��
	NVIC_Init(&NVIC_InitStructure);  //��ʼ��NVIC�Ĵ���
	TIM_ARRPreloadConfig(TIM7, DISABLE);      //�������Զ����ع��� 
	TIM_Cmd(TIM7, DISABLE);  //ʹ��TIMx	 
	
}
 

/**----------------------------------------------------------------------------
* @FunctionName  : TIM7_Time_Set()
* @Description   : ��ʱ�����ö�ʱʱ��
* @Data          : 2017/10/13
* @Explain       : None
-------------------------------------------------------------------------------
Time	:��ʱʱ��	0.�رն�ʱ��
------------------------------------------------------------------------------*/ 
void TIM7_Time_Set(u16 Time)
{   
	TIM_Cmd(TIM7, DISABLE);  //ʧ��TIMx	 
	
	if(Time == 0)  return;  
	TIM_SetAutoreload(TIM7,Time);	
	TIM_SetCounter(TIM7,0);			
	
	TIM_Cmd(TIM7, ENABLE);  //ʧ��TIMx	 
}





/*******************************(C) COPYRIGHT 2017 Wind��л���죩*********************************/

























