/*******************************(C) COPYRIGHT 2017 Wind��л���죩*********************************/
/**============================================================================
* @FileName    : Drive_Interrupt.c
* @Description : �жϷ���
* @Date        : 2016/8/8
* @By          : Wind��л���죩
* @Email       : 1659567673@qq.com
* @Platform    : Keil uVision5 v5.20 (STM32L151CB)
* @Explain     : None
*=============================================================================*/

/* ͷ�ļ����� ----------------------------------------------------------------*/
#include "Drive_Interrupt.h"

/* ˽�к궨�� ----------------------------------------------------------------*/

/* ˽�У���̬���������� ------------------------------------------------------*/

/* ȫ�ֱ������� --------------------------------------------------------------*/


/* ȫ�ֺ�����д --------------------------------------------------------------*/
/**----------------------------------------------------------------------------
* @FunctionName  : TIM2_IRQHandler()
* @Description   : ��ʱ��������
* @Data          : 2016/8/8
* @Explain       : ����ʱ��
-------------------------------------------------------------------------------
None
------------------------------------------------------------------------------*/
void TIM2_IRQHandler(void)
{ 
    TIM_ClearITPendingBit(TIM2, TIM_IT_Update); //���TIMx�����жϱ�־
    OS_TimeOver_Cnt ++; 
}



/**----------------------------------------------------------------------------
* @FunctionName  : TIM3_IRQHandler()
* @Description   : ��ʱ��������
* @Data          : 2016/8/8
* @Explain       : ����ϵͳ�߳�
-------------------------------------------------------------------------------
None
------------------------------------------------------------------------------*/
void TIM6_IRQHandler(void)
{
    TIM_ClearITPendingBit(TIM6, TIM_IT_Update); //���TIMx�����жϱ�־
    OSThread_5();
	
}


/**----------------------------------------------------------------------------
* @FunctionName  : TIM4_IRQHandler()
* @Description   : ��ʱ��������
* @Data          : 2016/8/8
* @Explain       : �������߳�
-------------------------------------------------------------------------------
None
------------------------------------------------------------------------------*/
void TIM4_IRQHandler(void)
{
    TIM_ClearITPendingBit(TIM4, TIM_IT_Update); //���TIMx�����жϱ�־
    OSThread_8();
}




/**----------------------------------------------------------------------------
* @FunctionName  : TIM7_IRQHandler()
* @Description   : ��ʱ��������
* @Data          : 2016/8/8
* @Explain       : None
-------------------------------------------------------------------------------
None
------------------------------------------------------------------------------*/
void TIM7_IRQHandler(void)
{
    TIM_ClearITPendingBit(TIM7, TIM_IT_Update); //���TIMx�����жϱ�־
	Infrared_TimeCodeSend_Handle();//���ⷢ��
}
 

/**----------------------------------------------------------------------------
* @FunctionName  : EXTI4_IRQHandler()
* @Description   : �ⲿ�жϷ�����
* @Data          : 2016/8/8
* @Explain       : None
-------------------------------------------------------------------------------
None
------------------------------------------------------------------------------*/
void EXTI4_IRQHandler(void)
{
    if(EXTI_GetITStatus(EXTI_Line4) != RESET)
    {	 
		
        EXTI_ClearITPendingBit(EXTI_Line4);	
    }	
	
	
}

/**----------------------------------------------------------------------------
* @FunctionName  : EXTI0_IRQHandler()
* @Description   : �ⲿ�жϷ�����
* @Data          : 2016/8/8
* @Explain       : None
-------------------------------------------------------------------------------
None
------------------------------------------------------------------------------*/
void EXTI0_IRQHandler(void)
{
    if(EXTI_GetITStatus(EXTI_Line0) != RESET)
    {	  
        EXTI_ClearITPendingBit(EXTI_Line0);	
    }	 
}

/**----------------------------------------------------------------------------
* @FunctionName  : EXTI1_IRQHandler()
* @Description   : �ⲿ�жϷ�����
* @Data          : 2016/8/8
* @Explain       : None
-------------------------------------------------------------------------------
None
------------------------------------------------------------------------------*/
void EXTI1_IRQHandler(void)
{
    if(EXTI_GetITStatus(EXTI_Line1) != RESET)
    {	  
        EXTI_ClearITPendingBit(EXTI_Line0);	
    }	 
}

/**----------------------------------------------------------------------------
* @FunctionName  : EXTI9_5_IRQHandler()
* @Description   : �ⲿ�жϷ�����
* @Data          : 2016/8/8
* @Explain       : None
-------------------------------------------------------------------------------
None
------------------------------------------------------------------------------*/
void EXTI9_5_IRQHandler(void)
{
    if(EXTI_GetITStatus(EXTI_Line6) != RESET)
    {	  
        EXTI_ClearITPendingBit(EXTI_Line6);	
    }	 
}


/**----------------------------------------------------------------------------
* @FunctionName  : USART1_IRQHandler()
* @Description   : �����жϷ�����
* @Data          : 2016/8/8
* @Explain       : None
-------------------------------------------------------------------------------
None
------------------------------------------------------------------------------*/
void USART1_IRQHandler()
{
	if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)  //�����ж�
	{ 
		
		
		
		USART_ClearITPendingBit(USART1, USART_IT_RXNE); //���TIMx�����жϱ�־ 
    } 	
	
}





/**----------------------------------------------------------------------------
* @FunctionName  : None
* @Description   : Ӳ�������ж�
* @Data          : 2016/8/8
* @Explain       : None
-------------------------------------------------------------------------------
None
------------------------------------------------------------------------------*/
// From Joseph Yiu, minor edits by FVH
// hard fault handler in C,
// with stack frame location as input parameter
// called from HardFault_Handler in file xxx.s
void HardFault_Handler_C( unsigned int *args )
{
#if 0
    int8_t s[100];
    unsigned int stacked_r0;
    unsigned int stacked_r1;
    unsigned int stacked_r2;
    unsigned int stacked_r3;
    unsigned int stacked_r12;
    unsigned int stacked_lr;
    unsigned int stacked_pc;
    unsigned int stacked_psr;

    stacked_r0 = ( ( unsigned long) args[0] );
    stacked_r1 = ( ( unsigned long) args[1] );
    stacked_r2 = ( ( unsigned long) args[2] );
    stacked_r3 = ( ( unsigned long) args[3] );

    stacked_r12 = ( ( unsigned long) args[4] );
    stacked_lr = ( ( unsigned long) args[5] );
    stacked_pc = ( ( unsigned long) args[6] );
    stacked_psr = ( ( unsigned long) args[7] );

    sprintf( s, "\n\n[Hard fault handler - all numbers in hex]\n" );
    sprintf( s, "R0 = %x\n", stacked_r0 );
    sprintf( s, "R1 = %x\n", stacked_r1 );
    sprintf( s, "R2 = %x\n", stacked_r2 );
    sprintf( s, "R3 = %x\n", stacked_r3 );
    sprintf( s, "R12 = %x\n", stacked_r12 );
    sprintf( s, "LR [R14] = %x  subroutine call return address\n", stacked_lr );
    sprintf( s, "PC [R15] = %x  program counter\n", stacked_pc );
    sprintf( s, "PSR = %x\n", stacked_psr );
    sprintf( s, "BFAR = %x\n", ( *( ( volatile unsigned long * )( 0xE000ED38 ) ) ) );
    sprintf( s, "CFSR = %x\n", ( *( ( volatile unsigned long * )( 0xE000ED28 ) ) ) );
    sprintf( s, "HFSR = %x\n", ( *( ( volatile unsigned long * )( 0xE000ED2C ) ) ) );
    sprintf( s, "DFSR = %x\n", ( *( ( volatile unsigned long * )( 0xE000ED30 ) ) ) );
    sprintf( s, "AFSR = %x\n", ( *( ( volatile unsigned long * )( 0xE000ED3C ) ) ) );
    sprintf( s, "SCB_SHCSR = %x\n", SCB->SHCSR );
#endif
    /* Go to infinite loop when Hard Fault exception occurs */
    while( 1 )
    {
    }
}

/**
  * @brief  This function handles NMI exception.
  * @param  None
  * @retval None
  */
void NMI_Handler(void)
{
}

/**
  * @brief  This function handles Hard Fault exception.
  * @param  None
  * @retval None
  */
void HardFault_Handler(void)
{
  /* Go to infinite loop when Hard Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Memory Manage exception.
  * @param  None
  * @retval None
  */
void MemManage_Handler(void)
{
  /* Go to infinite loop when Memory Manage exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Bus Fault exception.
  * @param  None
  * @retval None
  */
void BusFault_Handler(void)
{
  /* Go to infinite loop when Bus Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Usage Fault exception.
  * @param  None
  * @retval None
  */
void UsageFault_Handler(void)
{
  /* Go to infinite loop when Usage Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles SVCall exception.
  * @param  None
  * @retval None
  */
void SVC_Handler(void)
{
}

/**
  * @brief  This function handles Debug Monitor exception.
  * @param  None
  * @retval None
  */
void DebugMon_Handler(void)
{
}

/**
  * @brief  This function handles PendSVC exception.
  * @param  None
  * @retval None
  */
void PendSV_Handler(void)
{
}



/*******************************(C) COPYRIGHT 2017 Wind��л���죩*********************************/





