/*******************************(C) COPYRIGHT 2017 Wind（谢玉伸）*********************************/
/**============================================================================
* @FileName    : Drive_Key.c
* @Description : 按键
* @Date        : 2017/10/14
* @By          : Wind（谢玉伸）
* @Email       : 1659567673@ qq.com
* @Platform    : Keil uVision5 v5.15 (STM32L151CB)
* @Explain     : None
*=============================================================================*/

/* 头文件包含 ----------------------------------------------------------------*/
#include "Drive_Key.h"

/* 私有宏定义 ----------------------------------------------------------------*/ 

/* 私有（静态）函数声明 ------------------------------------------------------*/ 

/* 全局变量定义 --------------------------------------------------------------*/  
Type_Key Key[KEY_NUM] = {0};

/* 全局函数编写 --------------------------------------------------------------*/
/**----------------------------------------------------------------------------
* @FunctionName  : Key_Init()
* @Description   : 按键初始化
* @Data          : 2017/9/21
* @Explain       : 
-------------------------------------------------------------------------------
None
------------------------------------------------------------------------------*/
void Key_Init(void)
{  
	u8 i = 0;
	
	GPIO_Key_Init(); 
	
	for(i = 0;i < KEY_NUM;i ++)	
		Key[i].Value = 1;
		
}	
 

/**----------------------------------------------------------------------------
* @FunctionName  : Key_Value_Get()
* @Description   : 获取所有按键值
* @Data          : 2017/9/21
* @Explain       : 
-------------------------------------------------------------------------------
返回所有按键当前值
------------------------------------------------------------------------------*/
static u16 Key_Value_Get(void)
{ 
	u16 Temp_Key = 0;
	
	if(PIN_KEY_0) Temp_Key |= (u16)0x0001 << 0;		
//	if(PIN_KEY_1) Temp_Key |= (u16)0x0001 << 1;		
//	if(PIN_KEY_2) Temp_Key |= (u16)0x0001 << 2;		
//	if(PIN_KEY_3) Temp_Key |= (u16)0x0001 << 3;		
//	if(PIN_KEY_4) Temp_Key |= (u16)0x0001 << 4;		
//	if(PIN_KEY_5) Temp_Key |= (u16)0x0001 << 5;		
//	if(PIN_KEY_6) Temp_Key |= (u16)0x0001 << 6;		
//	if(PIN_KEY_7) Temp_Key |= (u16)0x0001 << 7;		
//	if(PIN_KEY_8) Temp_Key |= (u16)0x0001 << 8;
//	if(PIN_KEY_9) Temp_Key |= (u16)0x0001 << 9;
	
	return Temp_Key;	
}	



/**----------------------------------------------------------------------------
* @FunctionName  : Key_State_Get()
* @Description   : 获取按键状态
* @Data          : 2017/9/21
* @Explain       : 
-------------------------------------------------------------------------------
KeyNum	: 	
	KeyNum ,0~9 	 

State	:	
	短按 KEY_MODE_SHORT				
	长按 KEY_MODE_LONG 

return 	:	0.没有按下			1.按下了
------------------------------------------------------------------------------*/
u8 Key_State_Get(u8 KeyNum,u8 State)
{ 
	if(Key[KeyNum].State & State)	
	{ 
		return 1;
	}		  
	else
		return 0; 
}	
  
/**----------------------------------------------------------------------------
* @FunctionName  : Key_State_Clear()
* @Description   : 清除按键状态
* @Data          : 2017/9/21
* @Explain       : 
-------------------------------------------------------------------------------
KeyNum	: 	
	KeyNum ,0~9 	  
------------------------------------------------------------------------------*/
void Key_State_Clear(u8 KeyNum)
{  
	Key[KeyNum].State &= ~KEY_MODE_SHORT; //清除短按，长按会自动清除 Key[i].State &= ~KEY_MODE_SHORT; //清除短按，长按会自动清除  
	Key[KeyNum].Cnt = 0;	 	
}	
 





/**----------------------------------------------------------------------------
* @FunctionName  : Key_Scan_Handle()
* @Description   : 按键扫描函数
* @Data          : 2017/9/21
* @Explain       : 
-------------------------------------------------------------------------------
None
------------------------------------------------------------------------------*/
void Key_Scan_Handle(void)
{   
	u8 i = 0;
	u16 Temp_Key = 0; 
	
	Temp_Key = Key_Value_Get();		//获取当前所有按键的状态值 
	for(i = 0;i < KEY_NUM;i ++)
	{	
		if(Temp_Key & (u16)0x0001 << i)//被按下
		{
			if(Key[i].Cnt < 0xff) 
				Key[i].Cnt ++;	
			
			if(Key[i].Cnt > KEY_CNT_LONG)	
			{
				Key[i].State |= KEY_MODE_LONG; 		//长按
				Key[i].State &= ~KEY_MODE_SHORT;	//自动清除短按   
			}	
		}
		else //没有按下
		{ 
			if(Key[i].Cnt > KEY_CNT_SHORT && Key[i].Cnt < KEY_CNT_LONG) 
			{
				Key[i].State |= KEY_MODE_SHORT;	//短按    	
			}      
			
			Key[i].State &= ~KEY_MODE_LONG;	//自动清除长按  	
			Key[i].Cnt = 0;	 	
		}				
	}	 
	
	 
	 
} 




/*******************************(C) COPYRIGHT 2017 Wind（谢玉伸）*********************************/
























