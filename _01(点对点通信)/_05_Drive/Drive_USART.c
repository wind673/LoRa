/*******************************(C) COPYRIGHT 2017 Wind��л���죩*********************************/
/**============================================================================
* @FileName    : Drive_USART.c
* @Description : None
* @Date        : 2016/11/11
* @By          : Wind��л���죩
* @Email       : 1659567673@ qq.com
* @Platform    : Keil uVision5 v5.15 (STM32F103)
* @Explain     : None
*=============================================================================*/

/* ͷ�ļ����� ----------------------------------------------------------------*/
#include "Drive_USART.h" 

/* ˽�к궨�� ----------------------------------------------------------------*/
//�������´���,֧��printf����,������Ҫѡ��use MicroLIB
#pragma import(__use_no_semihosting)
//��׼����Ҫ��֧�ֺ���
struct __FILE
{
    int handle;
};

FILE __stdout;
//����_sys_exit()�Ա���ʹ�ð�����ģʽ
void _sys_exit(int x)
{
    x = x;
}
//�ض���fputc����
int fputc(int ch, FILE *f)
{
    USART1->DR = (uint8_t) ch;
    while((USART1->SR & 0X40) == 0); //ѭ������,ֱ���������
	
    return ch;
}

/* ˽�У���̬���������� ------------------------------------------------------*/

/* ȫ�ֱ������� --------------------------------------------------------------*/

/* ȫ�ֺ�����д --------------------------------------------------------------*/
/**----------------------------------------------------------------------------
* @FunctionName  : USART1_Init()
* @Description   : None
* @Data          : 2016/11/11
* @Explain       : None
------------------------------------------------------------------------------*/
void USART1_Init(uint32_t bound)
{
    //GPIO�˿�����
    GPIO_InitTypeDef GPIO_InitStructure;
    USART_InitTypeDef USART_InitStructure;
    NVIC_InitTypeDef NVIC_InitStructure;
	
    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);	//ʹ��USART1��GPIOAʱ��
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE); 
	
	//connect PA.9 to usart1's tx
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource9, GPIO_AF_USART1);
	//connect PA.10 to usart1's rx
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource10, GPIO_AF_USART1);
	
	/* Configure USART Tx as alternate function push-pull */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_40MHz;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
    
	/* Configure USART Rx as alternate function push-pull */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	
    //USART2 NVIC ����	
    NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 4; //��ռ���ȼ�3
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;		//�����ȼ�3
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQͨ��ʹ��
    NVIC_Init(&NVIC_InitStructure);	//����ָ���Ĳ�����ʼ��VIC�Ĵ���
	
    //USART ��ʼ������	 
    USART_InitStructure.USART_BaudRate = bound;//���ڲ�����
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;//�ֳ�Ϊ8λ���ݸ�ʽ
    USART_InitStructure.USART_StopBits = USART_StopBits_1;//һ��ֹͣλ
    USART_InitStructure.USART_Parity = USART_Parity_No;//����żУ��λ
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//��Ӳ������������
    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//�շ�ģʽ
	
    USART_Init(USART1, &USART_InitStructure); //��ʼ������1
    USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);//�������ڽ����ж�
    USART_Cmd(USART1, ENABLE);            
	while(USART_GetFlagStatus(USART1, USART_FLAG_TC) != SET){}; //�ȴ����ͽ��� 		
}




/**----------------------------------------------------------------------------
* @FunctionName  : USART_Str_Send()
* @Description   : ���ڷ����ַ���
* @Data          : 2016/11/15
* @Explain       : None
------------------------------------------------------------------------------*/
void USART_Str_Send(USART_TypeDef* USARTx,uint8_t *Str)
{
	u16 i = 0; 
	u16 lenth = strlen((char*)Str);
    for(i = 0; i < lenth; i ++)
    {
		while(USART_GetFlagStatus(USARTx, USART_FLAG_TC) != SET){}; //�ȴ����ͽ��� 		
        USART_SendData(USARTx, (u16)Str[i]); //����λ����������	
       
    } 
}	

/**----------------------------------------------------------------------------
* @FunctionName  : Usart_Null()
* @Description   : �մ���
* @Data          : 2017/10/18
* @Explain       : None
------------------------------------------------------------------------------*/
void Usart_Null(char *str,...)
{  
	return;
}




/*******************************(C) COPYRIGHT 2017 Wind��л���죩*********************************/








