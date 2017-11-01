/*******************************(C) COPYRIGHT 2017 Wind（谢玉伸）*********************************/
/**============================================================================
* @FileName    : User_Bsp.c
* @Description : None	
* @Date        : 2017/10/16
* @By          : Wind（谢玉伸）
* @Email       : 1659567673@ qq.com
* @Platform    : Keil uVision5 v5.20 (STM32L151CB)
* @Explain     : None
*=============================================================================*/ 

/* 头文件包含 ----------------------------------------------------------------*/  
#include "User_Bsp.h"   

/* 私有宏定义 ----------------------------------------------------------------*/ 

/* 私有（静态）函数声明 -------------------------------------------------------*/ 
			
/* 全局变量定义 --------------------------------------------------------------*/ 
RCC_ClocksTypeDef Bsp_Clocks = {0};		

/* 全局函数编写 --------------------------------------------------------------*/ 

/**---------------------------------------------------------------------------- 
* @FunctionName  : Bsp_InfoPrint()     			
* @Description   : 打印本地消息 				
* @Data          : 2017/10/16 
* @Explain       : None					
------------------------------------------------------------------------------*/ 	
static void Bsp_InfoPrint(void)
{  
	Usart_MSG("\r\n\r\n\r\n Start.......	 \r\n");
	Usart_MSG("-----------------------------------\r\n");
	Usart_MSG("Board:IntoRobot L6  \r\n");
	Usart_MSG("MCU  :STM32L151CB  \r\n");
	Usart_MSG("RAM  :16K	\r\n");
	Usart_MSG("ROM  :128K	 \r\n");
	Usart_MSG("SYSCLK_Frequency:%d	 \r\n",Bsp_Clocks.SYSCLK_Frequency);
	Usart_MSG("HCLK_Frequency	:%d	 \r\n",Bsp_Clocks.HCLK_Frequency);
	Usart_MSG("PCLK1_Frequency	:%d	 \r\n",Bsp_Clocks.PCLK1_Frequency);
	Usart_MSG("PCLK2_Frequency	:%d	 \r\n",Bsp_Clocks.PCLK2_Frequency);
	
	
	Usart_MSG("\r\n-----------------------------------\r\n\r\n\r\n");
	
}

/**---------------------------------------------------------------------------- 
* @FunctionName  : Bsp_Init()     			
* @Description   : None 				
* @Data          : 2017/10/16 
* @Explain       : None					
------------------------------------------------------------------------------*/ 	
void Bsp_Init(void)					
{		   
	/* 中断 --------------------------------*/   
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4); 
	
	/* 时钟 --------------------------------*/   
	SystemInit(); //初始化为默认时钟  
	RCC_Init();	//时钟初始化
	RCC_GetClocksFreq(&Bsp_Clocks); //获取时钟数据
	
	TIM2_Init();
	TIM6_Init();
	TIM4_Init(); 
		
	USART1_Init(9600);//串口1初始化 
	
	Bsp_InfoPrint();
	
}			



	
/*******************************(C) COPYRIGHT 2017 Wind（谢玉伸）*********************************/

 















