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
#ifndef __DRIVE_GPIO_H
#define __DRIVE_GPIO_H  

/* ͷ�ļ����� ----------------------------------------------------------------*/  
#include "User_Library.h"  

/* ȫ�ֺ궨�� ----------------------------------------------------------------*/   
#define P_Out(GPIO_X,_BIT,_VALUE)		(_VALUE?GPIO_WriteBit(GPIO##GPIO_X,GPIO_Pin_##_BIT,Bit_SET):GPIO_WriteBit(GPIO##GPIO_X,GPIO_Pin_##_BIT,Bit_RESET))   
#define P_Out_Value(GPIO_X,_BIT)		(GPIO_ReadOutputDataBit(GPIO##GPIO_X,GPIO_Pin_##_BIT)?1:0)   

#define P_In_Value(GPIO_X,_BIT)			(GPIO_ReadInputDataBit(GPIO##GPIO_X,GPIO_Pin_##_BIT)?1:0)   


/* �ṹ������ ----------------------------------------------------------------*/ 

/* ȫ�ֱ������� --------------------------------------------------------------*/ 

/* ȫ�ֺ������� --------------------------------------------------------------*/  
void GPIO_Test_Init(void);  
void GPIO_Key_Init(void);
void GPIO_LED_Init(void);  
void GPIO_Infrared_Init(void);
	
#endif
/*******************************(C) COPYRIGHT 2017 Wind��л���죩*********************************/



