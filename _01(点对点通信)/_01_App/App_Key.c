/*******************************(C) COPYRIGHT 2017 Wind（谢玉伸）*********************************/
/**============================================================================
* @FileName    : App_Key.c
* @Description : 按键	
* @Date        : 2016/10/14
* @By          : Wind（谢玉伸）
* @Email       : 1659567673@ qq.com
* @Platform    : Keil uVision5 v5.20 (STM32L151CB)
* @Explain     : None
*=============================================================================*/ 

/* 头文件包含 ----------------------------------------------------------------*/
#include "App_Key.h"  
 
/* 私有宏定义 ----------------------------------------------------------------*/

/* 私有（静态）函数声明 ------------------------------------------------------*/

/* 全局变量定义 --------------------------------------------------------------*/ 

/* 全局变量声明 --------------------------------------------------------------*/
  
/* 全局函数编写 --------------------------------------------------------------*/
/**----------------------------------------------------------------------------
* @FunctionName  : Key()     
* @Description   : None 
* @Data          : 2016/8/8
* @Explain       : None
------------------------------------------------------------------------------*/
void Key_Main(void)		
{        
	Key_Scan_Handle(); 
	
	 														
}		

void Key_Start(void)		
{        
	Key_Init(); 
	
} 			


Type_AppList App_Key = {Key_Main,NULL,Key_Start,NULL, \
						OS_STATE_ACTIVE,OS_THREAD_SYSTEM, \
						(uint8_t*)"Key",KEY_SCAN_GAP};	//KEY_SCAN_GAP 按键扫描间隔		
						
 




						
																				
/*******************************(C) COPYRIGHT 2017 Wind（谢玉伸）*********************************/
















