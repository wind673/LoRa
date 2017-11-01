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
#include "Drive_LED.h"

/* ˽�к궨�� ----------------------------------------------------------------*/  
#define	LED_NUM			3

/* ˽�У���̬���������� ------------------------------------------------------*/ 

/* ȫ�ֱ������� --------------------------------------------------------------*/     
static u16 LED_Scan_Time_ms[LED_NUM] = {0};

static u8	LED_Temp_Mode[LED_NUM] 			= {0};
static u8 	LED_Temp_Cnt[LED_NUM] 			= {0};
static u16 	LED_Temp_GapTime[LED_NUM]		= {0};  
static u8	LED_Default_Mode[LED_NUM] 		= {0}; 
static u16 	LED_Default_GapTime[LED_NUM]	= {0}; 

/* ȫ�ֺ�����д --------------------------------------------------------------*/ 
void LED_Init(void)
{
	GPIO_LED_Init();		 
	LED_Set(0,0);
	LED_Set(1,0);
	LED_Set(2,0);
	
	LED_Default_Set(0,300,LED_MODE_FLASH);
//	LED_Default_Set(1,200,LED_MODE_FLASH);
//	LED_Default_Set(2,600,LED_MODE_FLASH);
	
	LED_Temp_Set(0,50,LED_MODE_FLASH,0);
	LED_Temp_Set(1,50,LED_MODE_FLASH,0);
	LED_Temp_Set(2,50,LED_MODE_FLASH,0);
}
 

/**----------------------------------------------------------------------------
* @FunctionName  : LED_Temp_Set()
* @Description   : ������̬
* @Data          : 2017/9/21
* @Explain       : 
-------------------------------------------------------------------------------
LED_n LED 		LED���
GapTime			��˸ʱ��
Mode			ģʽ��0LED_MODE_OFF.����	LED_MODE_ON.����  LED_MODE_FLASH����˸
Cnt				����

ʾ��:	 		LED_Temp_Set(0,50,LED_MODE_FLASH,5);//��˸5��		
------------------------------------------------------------------------------*/ 
void LED_Temp_Set(u8 LED_n,u16 GapTime,u8 Mode,u8 Cnt)
{ 
	LED_Temp_GapTime[LED_n] 	= GapTime;
	LED_Temp_Mode[LED_n] 		= Mode;
	LED_Temp_Cnt[LED_n] 		= Cnt; 
}
 

/**----------------------------------------------------------------------------
* @FunctionName  : LED_Default_Set()
* @Description   : ���ó�̬
* @Data          : 2017/9/21
* @Explain       : 
-------------------------------------------------------------------------------
LED_n LED 		LED���
GapTime			��˸ʱ��
Mode			ģʽ��0LED_MODE_OFF.����	LED_MODE_ON.����  LED_MODE_FLASH����˸
------------------------------------------------------------------------------*/ 
void LED_Default_Set(u8 LED_n,u16 GapTime,u8 Mode)
{ 
	LED_Default_GapTime[LED_n] 	= GapTime;
	LED_Default_Mode[LED_n] 	= Mode; 
	
} 


/**----------------------------------------------------------------------------
* @FunctionName  : LED_Handle()
* @Description   : LED������
* @Data          : 2017/9/21
* @Explain       : 
-------------------------------------------------------------------------------
�˺�������main�з���ִ��
------------------------------------------------------------------------------*/ 
void LED_Scan_Handle(void)	
{     
	u8 LED_n = 0;
	
	for(LED_n = 0;LED_n < LED_NUM;LED_n ++)
	{
		if(LED_Scan_Time_ms[LED_n] == 0)//ʱ�䵽
		{  
			if(LED_Temp_Cnt[LED_n] == 0)	//���г�̬
			{
				if(LED_Default_Mode[LED_n] == LED_MODE_OFF)			LED_Set(LED_n,0);	
				else if(LED_Default_Mode[LED_n] == LED_MODE_ON)		LED_Set(LED_n,1);		 		
				else if(LED_Default_Mode[LED_n] == LED_MODE_FLASH)	LED_Set(LED_n,2);		 
				else if(LED_Temp_Mode[LED_n] == LED_MODE_OVER)		{LED_Set(LED_n,2);LED_Temp_Mode[LED_n] = 0;}
				
				LED_Scan_Time_ms[LED_n] = LED_Default_GapTime[LED_n];  
			}
			else//������̬
			{
				if(LED_Temp_Mode[LED_n] == LED_MODE_OFF)			LED_Set(LED_n,0);	
				else if(LED_Temp_Mode[LED_n] == LED_MODE_ON)		LED_Set(LED_n,1);		 		
				else if(LED_Temp_Mode[LED_n] == LED_MODE_FLASH)		LED_Set(LED_n,2);		 
				else if(LED_Temp_Mode[LED_n] == LED_MODE_OVER)		{LED_Set(LED_n,2);LED_Temp_Mode[LED_n] = 0;}
				
				LED_Scan_Time_ms[LED_n] = LED_Temp_GapTime[LED_n];  
				LED_Temp_Cnt[LED_n] --;	
			}	
			 
		}
		else
			LED_Scan_Time_ms[LED_n] --;
	} 
}	 



/**----------------------------------------------------------------------------
* @FunctionName  : LED_Set()
* @Description   : LED����ֵ
* @Data          : 2017/9/21
* @Explain       : 
-------------------------------------------------------------------------------
0.��	1.��	2.��ת
------------------------------------------------------------------------------*/ 
void LED_Set(u8 Led_x,u8 Value)
{
	switch(Led_x)
	{	
		case 0:	
			if(Value == 0) 
				LED_R(LED_OFF);
			else if(Value == 1)
				LED_R(LED_ON); 
			else if(Value == 2) 
				LED_R(LED_Get(Led_x));	
			break;
			
		case 1: 
			if(Value == 0) 
				LED_G(LED_OFF);
		else if(Value == 1)
				LED_G(LED_ON);	
		else if(Value == 2) 
				LED_G(LED_Get(Led_x));	
			break;
		
		case 2:	
			if(Value == 0) 
				LED_B(LED_OFF);
			else if(Value == 1)
				LED_B(LED_ON);	
			else if(Value == 2) 
				LED_B(LED_Get(Led_x));	
			break;
			
	}	
	
}

/**----------------------------------------------------------------------------
* @FunctionName  : LED_Set()
* @Description   : ��ȡLED��ֵ
* @Data          : 2017/9/21
* @Explain       : 
-------------------------------------------------------------------------------
None
------------------------------------------------------------------------------*/ 
u8 LED_Get(u8 Led_x)
{
	u8 _return = 0;
	
	switch(Led_x)
	{	
		case 0:	if(LED_R_Value) _return = LED_ON; else _return = LED_OFF;	break;
		case 1:	if(LED_G_Value) _return = LED_ON; else _return = LED_OFF;	break;
		case 2: if(LED_B_Value) _return = LED_ON; else _return = LED_OFF;	break;
	}	
	
	return _return;	
	
}


/*******************************(C) COPYRIGHT 2017 Wind��л���죩*********************************/


















