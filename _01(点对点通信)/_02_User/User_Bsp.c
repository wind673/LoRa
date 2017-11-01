/*******************************(C) COPYRIGHT 2017 Wind��л���죩*********************************/
/**============================================================================
* @FileName    : User_Bsp.c
* @Description : None	
* @Date        : 2017/10/16
* @By          : Wind��л���죩
* @Email       : 1659567673@ qq.com
* @Platform    : Keil uVision5 v5.20 (STM32L151CB)
* @Explain     : None
*=============================================================================*/ 

/* ͷ�ļ����� ----------------------------------------------------------------*/  
#include "User_Bsp.h"   

/* ˽�к궨�� ----------------------------------------------------------------*/ 

/* ˽�У���̬���������� -------------------------------------------------------*/ 
			
/* ȫ�ֱ������� --------------------------------------------------------------*/ 
RCC_ClocksTypeDef Bsp_Clocks = {0};		

/* ȫ�ֺ�����д --------------------------------------------------------------*/ 

/**---------------------------------------------------------------------------- 
* @FunctionName  : Bsp_InfoPrint()     			
* @Description   : ��ӡ������Ϣ 				
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
	/* �ж� --------------------------------*/   
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4); 
	
	/* ʱ�� --------------------------------*/   
	SystemInit(); //��ʼ��ΪĬ��ʱ��  
	RCC_Init();	//ʱ�ӳ�ʼ��
	RCC_GetClocksFreq(&Bsp_Clocks); //��ȡʱ������
	
	TIM2_Init();
	TIM6_Init();
	TIM4_Init(); 
		
	USART1_Init(9600);//����1��ʼ�� 
	
	Bsp_InfoPrint();
	
}			



	
/*******************************(C) COPYRIGHT 2017 Wind��л���죩*********************************/

 















