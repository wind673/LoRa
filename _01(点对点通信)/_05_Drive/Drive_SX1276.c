/*******************************(C) COPYRIGHT 2017 Wind（谢玉伸）*********************************/
/**============================================================================
* @FileName    : Drive_SX1276.c
* @Description : SX1276 - Lora驱动
* @Date        : 2017/10/16
* @By          : Wind（谢玉伸）
* @Email       : 1659567673@ qq.com
* @Platform    : Keil uVision5 v5.20 (STM32L151CB)
* @Explain     : None
*=============================================================================*/

/* 头文件包含 ----------------------------------------------------------------*/
#include "Drive_SX1276.h"
#include "platform.h"

/* 私有宏定义 ----------------------------------------------------------------*/
#define BUFFER_SIZE                                 100 // Define the payload size here

/* 私有（静态）函数声明 ------------------------------------------------------*/

/* 全局变量定义 --------------------------------------------------------------*/
static uint16_t BufferSize = 5;			// RF buffer size
static uint8_t Buffer[BUFFER_SIZE] = {0};					// RF buffer

uint8_t EnableMaster = false; 				// Master/Slave selection

tRadioDriver *Radio = NULL;

const uint8_t PingMsg[] = "PING";
const uint8_t PongMsg[] = "PONG";
u8 MasterFlag = 0;

/* 全局函数编写 --------------------------------------------------------------*/
/**----------------------------------------------------------------------------
* @FunctionName  : SX1276_Init()
* @Description   : SX1276 - Lora初始化
* @Data          : 2017/10/16
* @Explain       : None
-------------------------------------------------------------------------------
None
------------------------------------------------------------------------------*/
void SX1276_Init(void)
{
    BoardInit( );
    
    Radio = RadioDriverInit( ); 
	
    SX1276Init( ); 
	SX1276LoRaSetRFPower(20); 
    SX1276StartRx( ); 
    Usart_MSG("\r\nStartRx开始接收 \r\n");
	
}





void OnMaster( void )
{
    uint8_t i;
    
    switch( Radio->Process( ) )
    {
    case RF_RX_TIMEOUT:
        // Send the next PING frame
		Usart_MSG("发送 PING \r\n");
	
        Buffer[0] = 'P';
        Buffer[1] = 'I';
        Buffer[2] = 'N';
        Buffer[3] = 'G';
        for( i = 4; i < BufferSize; i++ )
        {
            Buffer[i] = i - 4;
        }
        SX1276SetTxPacket( Buffer, BufferSize );
        break;
    case RF_RX_DONE:
        SX1276GetRxPacket( Buffer, ( uint16_t* )&BufferSize );
    
        if( BufferSize > 0 )
        {
			Usart_MSG("Receive: %s",Buffer);	 
            if( strncmp( ( const char* )Buffer, ( const char* )PongMsg, 4 ) == 0 )
            {
                // Indicates on a LED that the received frame is a PONG
				Usart_MSG("接收到 PONG，再次发送 PING \r\n"); 
				
                // Send the next PING frame            
                Buffer[0] = 'P';
                Buffer[1] = 'I';
                Buffer[2] = 'N';
                Buffer[3] = 'G';
                // We fill the buffer with numbers for the payload 
                for( i = 4; i < BufferSize; i++ )
                {
                    Buffer[i] = i - 4;
                }
                SX1276SetTxPacket( Buffer, BufferSize );
            }
            else if( strncmp( ( const char* )Buffer, ( const char* )PingMsg, 4 ) == 0 )
            { 
				// A master already exists then become a slave
				Usart_MSG("主机退出，变成从机 \r\n");
                EnableMaster = false; 
            }
        }            
        break;
    case RF_TX_DONE:
        // Indicates on a LED that we have sent a PING
		Usart_MSG("开始接收 \r\n"); 
        SX1276StartRx( );
        break;
    default:
		if(MasterFlag != 1)
		{
			MasterFlag = 1;
			Usart_MSG("OnMaster:None... \r\n");
		}
        break;
    }
}


void OnSlave( void )
{
    uint8_t i;

    switch( Radio->Process() )
    {
    case RF_RX_DONE:
        SX1276GetRxPacket( Buffer, ( uint16_t* )&BufferSize );
    
        if( BufferSize > 0 )
        {
			Usart_MSG("Receive: %s",Buffer); 
            if( strncmp( ( const char* )Buffer, ( const char* )PingMsg, 4 ) == 0 )
            {
                // Indicates on a LED that the received frame is a PING
				Usart_MSG("接收到 PING，再次发送 PONG \r\n"); 
				
               // Send the reply to the PONG string
                Buffer[0] = 'P';
                Buffer[1] = 'O';
                Buffer[2] = 'N';
                Buffer[3] = 'G';
                // We fill the buffer with numbers for the payload 
                for( i = 4; i < BufferSize; i++ )
                {
                    Buffer[i] = i - 4;
                }

                SX1276SetTxPacket( Buffer, BufferSize );
            }
        }
        break;
    case RF_TX_DONE:
        // Indicates on a LED that we have sent a PONG 
		Usart_MSG("开始接收  \r\n"); 
        SX1276StartRx();
        break;
    default:
		if(MasterFlag != 2)
		{
			MasterFlag = 2;
			Usart_MSG("OnSlave:None... \r\n");
		} 
        break;
    }
}



/*******************************(C) COPYRIGHT 2017 Wind（谢玉伸）*********************************/

















