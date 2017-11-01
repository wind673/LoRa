/*******************************(C) COPYRIGHT 2017 Wind��л���죩*********************************/
/**============================================================================
* @FileName    : Drive_GPIO.h
* @Description : None	
* @Date        : 2016/8/7
* @By          : Wind��л���죩
* @Email       : 1659567673@ qq.com
* @Platform    : Keil uVision5 v5.20 (STM32L151CB)
* @Explain     : None
*=============================================================================*/ 

/* ��ֹ�ص��� ----------------------------------------------------------------*/
#ifndef __DRIVE_LED_H
#define __DRIVE_LED_H  

/* ͷ�ļ����� ----------------------------------------------------------------*/  
#include "User_Library.h"  

/* ȫ�ֺ궨�� ----------------------------------------------------------------*/  
#define LED_ON						(0)
#define LED_OFF						(1)

#define LED_MODE_OFF				(0) 
#define LED_MODE_ON					(1)  
#define LED_MODE_OVER				(2) //��ת  
#define LED_MODE_FLASH				(3) //��˸


#define LED_R(_VALUE)				P_Out(A,0,_VALUE) //����ֵ
#define LED_R_Value					P_Out_Value(A,0) //ֵ		

#define LED_G(_VALUE)				P_Out(A,1,_VALUE) //����ֵ
#define LED_G_Value 				P_Out_Value(A,1) //ֵ		

#define LED_B(_VALUE)				P_Out(B,12,_VALUE) //����ֵ
#define LED_B_Value 				P_Out_Value(B,12) //ֵ		 
									




/* �ṹ������ ----------------------------------------------------------------*/   

/* ȫ�ֱ������� --------------------------------------------------------------*/  

/* ȫ�ֺ������� --------------------------------------------------------------*/  
void LED_Init(void);    
 
void LED_Temp_Set(u8 LED_n,u16 GapTime,u8 Mode,u8 Cnt);
void LED_Default_Set(u8 LED_n,u16 GapTime,u8 Mode);

void LED_Scan_Handle(void);   
u8 LED_Get(u8 Led_x);
void LED_Set(u8 Led_x,u8 Value);	



#endif
/*******************************(C) COPYRIGHT 2017 Wind��л���죩*********************************/



