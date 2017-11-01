/*******************************(C) COPYRIGHT 2017 Wind��л���죩*********************************/
/**============================================================================
* @FileName    : User_Stdafx.h
* @Description : ���Ⱥ궨��
* @Date        : 2017/8/6
* @By          : Wind��л���죩
* @Email       : 1659567673@ qq.com
* @Platform    : Keil uVision5 v5.20 (STM32L151CB)
* @Explain     : �ṹ�� ���������ļ�
*=============================================================================*/

/* ��ֹ�ص��� ----------------------------------------------------------------*/
#ifndef __USER_STDAFX_H
#define __USER_STDAFX_H

/* ͷ�ļ����� ----------------------------------------------------------------*/
#include "stm32l1xx.h"

/* ȫ�����Ⱥ궨�� ------------------------------------------------------------*/  
#define USART_MSG_EN		1



/* ����ֵ���� ------------------------------------*/ 
#ifndef true
#define	true						1	 
#endif

#ifndef false
#define	false						0	  
#endif

#ifndef bool
#define	bool						unsigned char	  
#endif


/* �ؼ��ֶ��� --------------------------------------*/ 
typedef unsigned  char			u8;	
typedef unsigned  short int    	u16;
typedef unsigned  int  			u32;	
typedef unsigned  long int  	u64;	

typedef signed  char			int8;	
typedef signed  short int    	int16;	
typedef signed  int  			int32;	
typedef signed  long int  		int64;	
	
/* �ṹ������ ----------------------------------------------------------------*/
//typedef struct
//{ 
//	
//} Type_XXX;  



/* ���������� ----------------------------------------------------------------*/
typedef union
{   
	signed char			_char;  
	uint8_t  			uint8_t;     
	
} Union_8;

typedef union
{  
	signed short int	_short_int; 
	uint16_t	  		_uint16_t;   
	
	signed char			_char[2];
	uint8_t	  			uint8_t[2];
   
} Union_16;

typedef union
{
	signed int			_int;
	float 				_float;  
    uint32_t	  		_uint32_t;
	 
	signed short int 	_short_int[2];
	uint16_t	 	 	_uint16_t[2];
	
    uint8_t	  			uint8_t[4];
    signed char			_char[4]; 
	
} Union_32;

typedef union
{
	double 				_double; 
	signed long int  	_long_int;
		
	signed int			_int[2];
	float 				_float[2];
    uint32_t	  		_uint32_t[2]; 
		
	signed short int 	_short_int[4];
	uint16_t	 		_uint16_t[4];
		
    uint8_t	  			uint8_t[8];
    signed char			_char[8]; 
	
} Union_64;			



/* ȫ�ֱ������� --------------------------------------------------------------*/

/* ȫ�ֺ������� --------------------------------------------------------------*/





#endif
/*******************************(C) COPYRIGHT 2017 Wind��л���죩*********************************/













