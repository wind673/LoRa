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
 * \file       sx1276-Hal.c
 * \brief      SX1276 Hardware Abstraction Layer
 *
 * \version    2.0.B2 
 * \date       Nov 21 2012
 * \author     Miguel Luis
 *
 * Last modified by Miguel Luis on Jun 19 2013
 */
#include <stdint.h>
#include <stdbool.h> 

#include "platform.h"

#if defined( USE_SX1276_RADIO )

#include "spi.h"
#include "sx1276-Hal.h"

/*!
 * SX1276 RESET I/O definitions
 */

#define RESET_IOPORT                                GPIOB
#define RESET_PIN                                   GPIO_Pin_9

/*!
 * SX1276 SPI NSS I/O definitions
 */
#define NSS_IOPORT                                  GPIOA
#define NSS_PIN                                     GPIO_Pin_15

/*!
 * SX1276 DIO pins  I/O definitions
 */
#define DIO0_IOPORT                                 GPIOC
#define DIO0_PIN                                    GPIO_Pin_13

#define DIO1_IOPORT                                 GPIOB
#define DIO1_PIN                                    GPIO_Pin_0

#define DIO2_IOPORT                                 GPIOB
#define DIO2_PIN                                    GPIO_Pin_1

#define DIO3_IOPORT                                 GPIOB                               
#define DIO3_PIN                                    GPIO_Pin_6

#define DIO4_IOPORT                                 GPIOB                                   
#define DIO4_PIN                                    GPIO_Pin_7

#define DIO5_IOPORT                                 GPIOB  
#define DIO5_PIN                                    GPIO_Pin_8

#define RXTX_IOPORT                                 GPIOA                                
#define RXTX_PIN                                    GPIO_Pin_8
//#define RX_IOPORT                                   GPIOC                                 
//#define RX_PIN                                      GPIO_Pin_0
//#define TX_IOPORT                                   GPIOC                                 
//#define TX_PIN                                      GPIO_Pin_1


void SX1276InitIo( void )
{
    GPIO_InitTypeDef GPIO_InitStructure;
	
    RCC_AHBPeriphClockCmd( RCC_AHBPeriph_GPIOA | RCC_AHBPeriph_GPIOB |
                            RCC_AHBPeriph_GPIOC, ENABLE );

    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_40MHz;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_UP;
    
    // Configure NSS as output
    GPIO_WriteBit( NSS_IOPORT, NSS_PIN, Bit_SET );
    GPIO_InitStructure.GPIO_Pin = NSS_PIN;
    GPIO_Init( NSS_IOPORT, &GPIO_InitStructure );

    // Configure radio DIO as inputs
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_40MHz;

    // Configure DIO0
    GPIO_InitStructure.GPIO_Pin =  DIO0_PIN;
    GPIO_Init( DIO0_IOPORT, &GPIO_InitStructure );
    
    // Configure DIO1
    GPIO_InitStructure.GPIO_Pin =  DIO1_PIN;
    GPIO_Init( DIO1_IOPORT, &GPIO_InitStructure );
    
    // Configure DIO2
    GPIO_InitStructure.GPIO_Pin =  DIO2_PIN;
    GPIO_Init( DIO2_IOPORT, &GPIO_InitStructure );
    
    // REAMARK: DIO3/4/5 configured are connected to IO expander

    // Configure DIO3 as input
    GPIO_InitStructure.GPIO_Pin =  DIO3_PIN;
    GPIO_Init( DIO3_IOPORT, &GPIO_InitStructure );
    
    // Configure DIO4 as input
    GPIO_InitStructure.GPIO_Pin =  DIO4_PIN;
    GPIO_Init( DIO4_IOPORT, &GPIO_InitStructure );
    
    // Configure DIO5 as input
    GPIO_InitStructure.GPIO_Pin =  DIO5_PIN;
    GPIO_Init( DIO5_IOPORT, &GPIO_InitStructure );
    
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_40MHz;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_UP;
	
    GPIO_InitStructure.GPIO_Pin =  RXTX_PIN;
    GPIO_Init( RXTX_IOPORT, &GPIO_InitStructure );
	
//    GPIO_InitStructure.GPIO_Pin =  RX_PIN;
//    GPIO_Init( RX_IOPORT, &GPIO_InitStructure );

//    GPIO_InitStructure.GPIO_Pin =  TX_PIN;
//    GPIO_Init( TX_IOPORT, &GPIO_InitStructure );
	
}

void SX1276SetReset( uint8_t state )
{
    GPIO_InitTypeDef GPIO_InitStructure;

    if( state == RADIO_RESET_ON )
    {
        // Set RESET pin to 1
        GPIO_WriteBit( RESET_IOPORT, RESET_PIN, Bit_SET );

        // Configure RESET as output
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
        GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
        GPIO_InitStructure.GPIO_Speed = GPIO_Speed_40MHz; 
        GPIO_InitStructure.GPIO_Pin = RESET_PIN;
        GPIO_Init( RESET_IOPORT, &GPIO_InitStructure );
    }
    else
    {  
        // Configure RESET as input
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;   
        GPIO_InitStructure.GPIO_Speed = GPIO_Speed_40MHz;
        GPIO_InitStructure.GPIO_Pin =  RESET_PIN;
        GPIO_Init( RESET_IOPORT, &GPIO_InitStructure ); 
    }
}

void SX1276Write( uint8_t addr, uint8_t data )
{
    SX1276WriteBuffer( addr, &data, 1 );
}

void SX1276Read( uint8_t addr, uint8_t *data )
{
    SX1276ReadBuffer( addr, data, 1 );
}

void SX1276WriteBuffer( uint8_t addr, uint8_t *buffer, uint8_t size )
{
    uint8_t i;

    //NSS = 0;
    GPIO_WriteBit( NSS_IOPORT, NSS_PIN, Bit_RESET );

    SpiInOut( addr | 0x80 );
    for( i = 0; i < size; i++ )
    {
        SpiInOut( buffer[i] );
    }

    //NSS = 1;
    GPIO_WriteBit( NSS_IOPORT, NSS_PIN, Bit_SET );
}

void SX1276ReadBuffer( uint8_t addr, uint8_t *buffer, uint8_t size )
{
    uint8_t i;

    //NSS = 0;
    GPIO_WriteBit( NSS_IOPORT, NSS_PIN, Bit_RESET );

    SpiInOut( addr & 0x7F );

    for( i = 0; i < size; i++ )
    {
        buffer[i] = SpiInOut( 0 );
    }

    //NSS = 1;
    GPIO_WriteBit( NSS_IOPORT, NSS_PIN, Bit_SET );
}

void SX1276WriteFifo( uint8_t *buffer, uint8_t size )
{
    SX1276WriteBuffer( 0, buffer, size );
}

void SX1276ReadFifo( uint8_t *buffer, uint8_t size )
{
    SX1276ReadBuffer( 0, buffer, size );
}

inline uint8_t SX1276ReadDio0( void )
{
    return GPIO_ReadInputDataBit( DIO0_IOPORT, DIO0_PIN );
}

inline uint8_t SX1276ReadDio1( void )
{
    return GPIO_ReadInputDataBit( DIO1_IOPORT, DIO1_PIN );
}

inline uint8_t SX1276ReadDio2( void )
{
    return GPIO_ReadInputDataBit( DIO2_IOPORT, DIO2_PIN );
}

inline uint8_t SX1276ReadDio3( void )
{ 
    return GPIO_ReadInputDataBit( DIO3_IOPORT, DIO3_PIN );
 
}

inline uint8_t SX1276ReadDio4( void )
{ 
    return GPIO_ReadInputDataBit( DIO4_IOPORT, DIO4_PIN );
 
}

inline uint8_t SX1276ReadDio5( void )
{ 
    return GPIO_ReadInputDataBit( DIO5_IOPORT, DIO5_PIN );
	
}

inline void SX1276WriteRxTx( uint8_t txEnable )
{ 
    if( txEnable != 0 )
    {
        GPIO_WriteBit( RXTX_IOPORT, RXTX_PIN, Bit_RESET ); //TX
    }
    else
    {
        GPIO_WriteBit( RXTX_IOPORT, RXTX_PIN, Bit_SET ); //RX
    }
 
}



#endif // USE_SX1276_RADIO


