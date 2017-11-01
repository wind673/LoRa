/*******************************(C) COPYRIGHT 2017 Wind（谢玉伸）*********************************/
/**============================================================================
* @FileName    : User_Stdafx.h
* @Description : 优先宏定义
* @Date        : 2017/8/6
* @By          : Wind（谢玉伸）
* @Email       : 1659567673@ qq.com
* @Platform    : Keil uVision5 v5.20 (STM32L151CB)
* @Explain     : 结构体 联合体存放文件
*=============================================================================*/

/* 防止重调用 ----------------------------------------------------------------*/
#ifndef __USER_STDAFX_H
#define __USER_STDAFX_H

/* 头文件包含 ----------------------------------------------------------------*/
#include "stm32l1xx.h"

/* 全局优先宏定义 ------------------------------------------------------------*/  
#define USART_MSG_EN		1



/* 常用值定义 ------------------------------------*/ 
#ifndef true
#define	true						1	 
#endif

#ifndef false
#define	false						0	  
#endif

#ifndef bool
#define	bool						unsigned char	  
#endif


/* 关键字定义 --------------------------------------*/ 
typedef unsigned  char			u8;	
typedef unsigned  short int    	u16;
typedef unsigned  int  			u32;	
typedef unsigned  long int  	u64;	

typedef signed  char			int8;	
typedef signed  short int    	int16;	
typedef signed  int  			int32;	
typedef signed  long int  		int64;	
	
/* 结构体声明 ----------------------------------------------------------------*/
//typedef struct
//{ 
//	
//} Type_XXX;  



/* 联合体声明 ----------------------------------------------------------------*/
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



/* 全局变量声明 --------------------------------------------------------------*/

/* 全局函数声明 --------------------------------------------------------------*/





#endif
/*******************************(C) COPYRIGHT 2017 Wind（谢玉伸）*********************************/













