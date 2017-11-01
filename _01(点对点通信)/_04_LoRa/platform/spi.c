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
 * \file       spi.c
 * \brief      SPI hardware driver
 *
 * \version    1.0
 * \date       Feb 12 2010
 * \author     Miguel Luis
 */
#include "platform.h"
#include <stdint.h>
#if ( STM32F4XX )
    #include "stm32f4xx_spi.h"
#elif defined( STM32F2XX )
    #include "stm32f2xx_spi.h"
#elif defined( STM32F1XX )
    #include "stm32f10x_spi.h"
#else
    #include "stm32l1xx_spi.h"
#endif
#include "spi.h"


#define SPI_INTERFACE                               SPI1
#define SPI_CLK                                     RCC_APB2Periph_SPI1

#define SPI_PIN_SCK_PORT                            GPIOB
#define SPI_PIN_SCK_PORT_CLK                        RCC_AHBPeriph_GPIOB
#define SPI_PIN_SCK                                 GPIO_Pin_3
#define SPI_PIN_SCK_AF_SOURCE                       GPIO_PinSource3
#define SPI_PIN_SCK_AF                              GPIO_AF_SPI1

#define SPI_PIN_MISO_PORT                           GPIOB
#define SPI_PIN_MISO_PORT_CLK                       RCC_AHBPeriph_GPIOB
#define SPI_PIN_MISO                                GPIO_Pin_4
#define SPI_PIN_MISO_AF_SOURCE                      GPIO_PinSource4
#define SPI_PIN_MISO_AF                             GPIO_AF_SPI1

#define SPI_PIN_MOSI_PORT                           GPIOB
#define SPI_PIN_MOSI_PORT_CLK                       RCC_AHBPeriph_GPIOB
#define SPI_PIN_MOSI                                GPIO_Pin_5
#define SPI_PIN_MOSI_AF_SOURCE                      GPIO_PinSource5
#define SPI_PIN_MOSI_AF                             GPIO_AF_SPI1


#define	STM32_SPI_INTERNA 				 			0 //0.使用内置SPI   1.使用模拟SPI

#if STM32_SPI_INTERNA == 0 //使用内置SPI
void SpiInit( void )
{
    SPI_InitTypeDef SPI_InitStructure;
    GPIO_InitTypeDef GPIO_InitStructure;

    /* Enable peripheral clocks --------------------------------------------------*/
    /* Enable SPIy clock and GPIO clock for SPIy */
    RCC_AHBPeriphClockCmd(SPI_PIN_MISO_PORT_CLK | SPI_PIN_MOSI_PORT_CLK|
                           SPI_PIN_SCK_PORT_CLK, ENABLE);
    RCC_APB2PeriphClockCmd(SPI_CLK, ENABLE);

    /* GPIO configuration ------------------------------------------------------*/
    GPIO_PinAFConfig(SPI_PIN_SCK_PORT, SPI_PIN_SCK_AF_SOURCE, SPI_PIN_SCK_AF);
    GPIO_PinAFConfig(SPI_PIN_MOSI_PORT, SPI_PIN_MOSI_AF_SOURCE, SPI_PIN_MISO_AF);
    GPIO_PinAFConfig(SPI_PIN_MISO_PORT, SPI_PIN_MISO_AF_SOURCE, SPI_PIN_MOSI_AF);

    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_40MHz;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_DOWN;

    GPIO_InitStructure.GPIO_Pin = SPI_PIN_SCK;
    GPIO_Init( SPI_PIN_SCK_PORT, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pin = SPI_PIN_MOSI;
    GPIO_Init( SPI_PIN_MOSI_PORT, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pin = SPI_PIN_MISO;
    GPIO_Init( SPI_PIN_MISO_PORT, &GPIO_InitStructure);

    /* SPI_INTERFACE Config -------------------------------------------------------------*/
    SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
    SPI_InitStructure.SPI_Mode = SPI_Mode_Master;
    SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;
    SPI_InitStructure.SPI_CPOL = SPI_CPOL_Low;
    SPI_InitStructure.SPI_CPHA = SPI_CPHA_1Edge;
    SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;
    //    SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_16; // 32/16 MHz
    SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_4; // 32/4 MHz
    SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;
    SPI_InitStructure.SPI_CRCPolynomial = 7;
    SPI_Init(SPI_INTERFACE, &SPI_InitStructure);
    SPI_Cmd(SPI_INTERFACE, ENABLE);

}


uint8_t SpiInOut(uint8_t outData)
{
    /* Send SPIy data */
    SPI_I2S_SendData( SPI_INTERFACE, outData );
    while( SPI_I2S_GetFlagStatus( SPI_INTERFACE, SPI_I2S_FLAG_RXNE ) == RESET );
    return SPI_I2S_ReceiveData( SPI_INTERFACE );
}

#else //使用模拟SPI

void SpiInit( void )
{ 
    GPIO_InitTypeDef GPIO_InitStructure;

    /* Enable peripheral clocks --------------------------------------------------*/
    /* Enable SPIy clock and GPIO clock for SPIy */
    RCC_AHBPeriphClockCmd( SPI_PIN_MISO_PORT_CLK | SPI_PIN_MOSI_PORT_CLK |
                           SPI_PIN_SCK_PORT_CLK, ENABLE);

    /* GPIO configuration ------------------------------------------------------*/
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_40MHz;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_DOWN;

    GPIO_InitStructure.GPIO_Pin = SPI_PIN_SCK;
    GPIO_Init( SPI_PIN_SCK_PORT, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pin = SPI_PIN_MOSI;
    GPIO_Init( SPI_PIN_MOSI_PORT, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
    GPIO_InitStructure.GPIO_Pin = SPI_PIN_MISO;
    GPIO_Init( SPI_PIN_MISO_PORT, &GPIO_InitStructure); 
	
}

#define	SPI_CLK_H() 		GPIO_WriteBit(SPI_PIN_SCK_PORT,SPI_PIN_SCK,Bit_SET)
#define	SPI_CLK_L() 		GPIO_WriteBit(SPI_PIN_SCK_PORT,SPI_PIN_SCK,Bit_RESET)

#define	SPI_MOSI_H() 		GPIO_WriteBit(SPI_PIN_MOSI_PORT,SPI_PIN_MOSI,Bit_SET)
#define	SPI_MOSI_L() 		GPIO_WriteBit(SPI_PIN_MOSI_PORT,SPI_PIN_MOSI,Bit_RESET)

#define	SPI_MISO() 			GPIO_ReadInputDataBit(SPI_PIN_MISO_PORT,SPI_PIN_MISO)

#define SPI_DELAY_TIME_us			5

uint8_t SpiInOut(uint8_t ByteSend)
{	
	u8 i = 0;
	u8 ByteRead = 0;	
	
	SPI_CLK_L();	
	P_Out(A,5,0); 
	
	for(i = 0; i < 8; i ++)
    {	
        if(ByteSend & (0x80 >> i)) 
            SPI_MOSI_H();	//数据总线准备数据1
        else
            SPI_MOSI_L();   //数据总线准备数据0
		
        SPI_CLK_H(); //拉高sck  
		OSdelay_us(SPI_DELAY_TIME_us);
		
		if(SPI_MISO()) 		
            ByteRead |= (0x80 >> i);	//数据总线准备数据1 
		
        SPI_CLK_L();  //拉低sck  
		OSdelay_us(SPI_DELAY_TIME_us); 
    } 
	
	P_Out(A,5,1);
	
	return ByteRead; 
	
}
 



#endif











