/*
 * THE FOLLOWING FIRMWARE IS PROVIDED: (1) "AS IS" WITH NO WARRANTY; AND 
 * (2)TO ENABLE ACCESS TO CODING INFORMATION TO GUIDE AND FACILITATE CUSTOMER.
 * CONSEQUENTLY, SEMTECH SHALL NOT BE HELD LIABLE FOR ANY DIRECT, INDIRECT OR
 * CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING FROM THE CONTENT
 * OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE CODING INFORMATION
 * CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
 * 
 * Copyright (C) SEMTECH S.A.
 */
/*! 
 * \file       bleeper.c
 * \brief        
 *
 * \version    1.0
 * \date       Nov 21 2012
 * \author     Miguel Luis
 */
#include <stdint.h> 
#include "spi.h"
#include "i2c.h" 
#include "bleeper.h"
#include "platform.h"

// System tick (1ms)
volatile uint32_t TickCounter = 0; 

void BoardInit( void )
{  	  
	Usart_MSG("初始化SysTick \r\n"); 
    /* Setup SysTick Timer for 1 us interrupts ( not too often to save power ) */
    if( SysTick_Config( SystemCoreClock / 1000 ) )
    {
        /* Capture error */ 
		Usart_MSG("SysTick 初始化失败 ！！！\r\n"); 
        while (1);
    }
	Usart_MSG("SysTick 初始化成功 ！！！\r\n"); 
	
	Usart_MSG("初始化SPI \r\n"); 
    // Initialize SPI
    SpiInit();     
	
}




/**
  * @brief  This function handles SysTick Handler.
  * @param  None
  * @retval None
  */
void SysTick_Handler(void)
{
	TickCounter ++;
}
















