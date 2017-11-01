/*******************************(C) COPYRIGHT 2017 Wind��л���죩*********************************/
/**============================================================================
* @FileName    : App_Infrared.c
* @Description : None	
* @Date        : 2017/10/13
* @By          : Wind��л���죩
* @Email       : 1659567673@ qq.com
* @Platform    : Keil uVision5 v5.20 (STM32L151CB)
* @Explain     : None
*=============================================================================*/ 

/* ͷ�ļ����� ----------------------------------------------------------------*/
#include "App_Infrared.h"  

/* ˽�к궨�� ----------------------------------------------------------------*/

/* ˽�У���̬���������� ------------------------------------------------------*/

/* ȫ�ֱ������� --------------------------------------------------------------*/
 
/* ȫ�ֱ������� --------------------------------------------------------------*/
  
/* ȫ�ֺ�����д --------------------------------------------------------------*/
/**----------------------------------------------------------------------------
* @FunctionName  : Infrared()     
* @Description   : None 
* @Data          : 2016/8/8
* @Explain       : ����ң�ط���
------------------------------------------------------------------------------*/
void Infrared_Main(void)		
{	 
	static u8 cnt = 0,flag = 0; 
	
	if(Key_State_Get(0,KEY_MODE_SHORT))
	{    
		Infrared_TimeCode_Send((u16 *)Infrared_TimeCodeDemo_Buff,sizeof(Infrared_TimeCodeDemo_Buff)/2);	 
		
		LED_Temp_Set(1,100,LED_MODE_FLASH,3);  
		Key_State_Clear(0); 
	}
	
	if(Key_State_Get(0,KEY_MODE_LONG))
	{ 	  
		if(cnt)
			TIM3_PWM_SetH(50);	 
		else
			TIM3_PWM_SetH(0);	 
		
		flag = !flag; 
		
		LED_Temp_Set(3,100,LED_MODE_FLASH,10);  
		
		while(Key_State_Get(0,KEY_MODE_LONG));	
	} 
	 
}		


void Infrared_Start(void)		
{    
	Infrared_Init();	 
	
	
}			

Type_AppList App_Infrared = {Infrared_Main,NULL,Infrared_Start,NULL, \
							OS_STATE_ACTIVE,OS_THREAD_FREE, \
							(uint8_t*)"Infrared",100};			
																
								
							
							
							

						
/*******************************(C) COPYRIGHT 2017 Wind��л���죩*********************************/



							
							
							
							
							
							
							
							
							
							

