/*******************************(C) COPYRIGHT 2017 Wind��л���죩*********************************/
/**============================================================================
* @FileName    : Drive_Infrared.c
* @Description : ��������	
* @Date        : 2017/10/13
* @By          : Wind��л���죩
* @Email       : 1659567673@ qq.com
* @Platform    : Keil uVision5 v5.20 (STM32L151CB)
* @Explain     : None
*=============================================================================*/

/* ͷ�ļ����� ----------------------------------------------------------------*/
#include "Drive_Infrared.h"

/* ˽�к궨�� ----------------------------------------------------------------*/

/* ˽�У���̬���������� ------------------------------------------------------*/

/* ȫ�ֱ������� --------------------------------------------------------------*/
Type_Infrared Infrared = {0};	

/* ȫ�ֺ�����д --------------------------------------------------------------*/
/**----------------------------------------------------------------------------
* @FunctionName  : Infrared_Init()
* @Description   : �����ʼ��
* @Data          : 2017/10/13
* @Explain       : None
-------------------------------------------------------------------------------
None
------------------------------------------------------------------------------*/ 
void Infrared_Init(void)
{   
	TIM3_PWM_Init();//���ͺ����õ�PWM�ز�	  
	TIM7_Init();//���ͺ����ö�ʱ��
}	





/**----------------------------------------------------------------------------
* @FunctionName  : Infrared_TimeCode_Send()
* @Description   : ���ⷢ��
* @Data          : 2017/10/13
* @Explain       : None
-------------------------------------------------------------------------------
None
------------------------------------------------------------------------------*/ 
signed int Infrared_TimeCode_Send(u16 *Buff,u16 Lenth)	
{     
	u16 i = 0; 
	
	Infrared.Lenth = Lenth;
	Infrared.Cnt = 0; 
	Infrared.FSM = 1;//��һ�����ݷ���  Infrared.FSM = 1
	
	for(i = 0;i < Lenth;i ++)
	{	
		Infrared.TimeCode_Buff[i] = Buff[i]; //ת������
	} 	
	
	TIM7_Time_Set(10);//��ʱ 
	
	return 0;
}	





/**----------------------------------------------------------------------------
* @FunctionName  : Infrared_TimeCodeSend_Handle()
* @Description   : ���ⷢ�ʹ�����
* @Data          : 2017/10/13
* @Explain       : None
-------------------------------------------------------------------------------
None
------------------------------------------------------------------------------*/ 
void Infrared_TimeCodeSend_Handle(void)
{       
	u16 time = Infrared.TimeCode_Buff[Infrared.Cnt];
	
	if(time == 0)
	{
		time = 1; //��ֹ���ݹرն�ʱ��
	}
	
	switch(Infrared.FSM)	
	{	
		case 0:	//��		 
			if(Infrared.Cnt < Infrared.Lenth) 
			{	
				TIM3_PWM_SetH(0);//���ͱպ϶�
				Infrared.FSM = 1; 				 	
			} 
			break;	
			
		case 1:	//��   
			if(Infrared.Cnt < Infrared.Lenth) 
			{
				TIM3_PWM_SetH(33);//����PWM��	 
				Infrared.FSM = 0; 
				
			}  
			break;  
	}	  
	
	if(Infrared.Cnt >= Infrared.Lenth) 
	{	
		TIM7_Time_Set(0);//�رն�ʱ��
		TIM3_PWM_SetH(0);	 
		Infrared.Lenth = 0;//������� 
		Infrared.Cnt = 0;	
		Infrared.FSM = 0;  	
	}
	else
	{
		Infrared.Cnt ++;  
		TIM7_Time_Set(time);//��ʱ 
	}
	
}	




 
/*******************************(C) COPYRIGHT 2017 Wind��л���죩*********************************/




















