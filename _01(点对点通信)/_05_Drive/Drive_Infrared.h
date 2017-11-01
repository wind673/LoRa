/*******************************(C) COPYRIGHT 2017 Wind��л���죩*********************************/
/**============================================================================
* @FileName    : Drive_Infrared.h
* @Description : ��������	
* @Date        : 2017/10/13
* @By          : Wind��л���죩
* @Email       : 1659567673@ qq.com
* @Platform    : Keil uVision5 v5.20 (STM32L151CB)
* @Explain     : None
*=============================================================================*/ 

/* ��ֹ�ص��� ----------------------------------------------------------------*/
#ifndef __DRIVE_Infrared_H
#define __DRIVE_Infrared_H  

/* ͷ�ļ����� ----------------------------------------------------------------*/  
#include "User_Library.h"  

/* ȫ�ֺ궨�� ----------------------------------------------------------------*/  
#define	INFRARED_CODE_MAX		500

/* �ṹ������ ----------------------------------------------------------------*/ 
typedef struct
{  
	u8 FSM;
	u16 Cnt; 
	u16 Lenth; 
	u16 TimeCode_Buff[INFRARED_CODE_MAX];
	
} Type_Infrared;  

/* ȫ�ֱ������� --------------------------------------------------------------*/  	
extern Type_Infrared Infrared;

/* ȫ�ֺ������� --------------------------------------------------------------*/  
void Infrared_Init(void); 
signed int Infrared_TimeCode_Send(u16 *Buff,u16 Lenth);
void Infrared_TimeCodeSend_Handle(void);


#endif
/*******************************(C) COPYRIGHT 2017 Wind��л���죩*********************************/



