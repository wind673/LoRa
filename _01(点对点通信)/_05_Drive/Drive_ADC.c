/*******************************(C) COPYRIGHT 2016 Wind��л���죩*********************************/
/**============================================================================
* @FileName    : Drive_ADC.c
* @Description : ADC��������
* @Date        : 2016/8/8
* @By          : Wind��л���죩
* @Email       : 1659567673@qq.com
* @Platform    : Keil uVision5 v5.20 (STM32F103RCT6)
* @Explain     : None
*=============================================================================*/

/* ͷ�ļ����� ----------------------------------------------------------------*/
#include "Drive_ADC.h"

/* ˽�к궨�� ----------------------------------------------------------------*/

/* ˽�У���̬���������� ------------------------------------------------------*/

/* ȫ�ֱ������� --------------------------------------------------------------*/

/* ȫ�ֺ�����д --------------------------------------------------------------*/
/**----------------------------------------------------------------------------
* @FunctionName  : ADC1_Init()
* @Description   : ADC1��ʼ��
* @Data          : 2016/8/8
* @Explain       : 
-------------------------------------------------------------------------------
None
------------------------------------------------------------------------------*/ 
void ADC1_Init(void)
{
    ADC_InitTypeDef ADC_InitStructure;
    GPIO_InitTypeDef GPIO_InitStructure;

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_ADC1, ENABLE);	 //ʹ��ADC1ͨ��ʱ��
    RCC_ADCCLKConfig(RCC_PCLK2_Div6);   //����ADC��Ƶ����6 72M/6=12,ADC���ʱ�䲻�ܳ���14M

    //PA1 ��Ϊģ��ͨ����������
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;		//ģ����������
    GPIO_Init(GPIOA, &GPIO_InitStructure);
    ADC_DeInit(ADC1);  //��λADC1

    ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;	//ADC����ģʽ:ADC1��ADC2�����ڶ���ģʽ
    ADC_InitStructure.ADC_ScanConvMode = DISABLE;	//ģ��ת�������ڵ�ͨ��ģʽ
    ADC_InitStructure.ADC_ContinuousConvMode = DISABLE;	//ģ��ת�������ڵ���ת��ģʽ
    ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;	//ת��������������ⲿ��������
    ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;	//ADC�����Ҷ���
    ADC_InitStructure.ADC_NbrOfChannel = 1;	//˳����й���ת����ADCͨ������Ŀ
    ADC_Init(ADC1, &ADC_InitStructure);	//����ADC_InitStruct��ָ���Ĳ�����ʼ������ADCx�ļĴ���
    ADC_Cmd(ADC1, ENABLE);	//ʹ��ָ����ADC1
    ADC_ResetCalibration(ADC1);	//ʹ�ܸ�λУ׼
    while(ADC_GetResetCalibrationStatus(ADC1));	//�ȴ���λУ׼����
    ADC_StartCalibration(ADC1);	 //����ADУ׼
    while(ADC_GetCalibrationStatus(ADC1));	 //�ȴ�У׼���� 
}

/**----------------------------------------------------------------------------
* @FunctionName  : ADC1_Get()
* @Description   : ���ADC1��ֵ
* @Data          : 2016/8/8
* @Explain       : 
-------------------------------------------------------------------------------
None
------------------------------------------------------------------------------*/ 
u16 ADC1_Get(void)
{
    ADC_RegularChannelConfig(ADC1, 1, 1, ADC_SampleTime_239Cycles5 );	//ADC1,ADCͨ��,����ʱ��Ϊ239.5����
    ADC_SoftwareStartConvCmd(ADC1, ENABLE);		//ʹ��ָ����ADC1�����ת����������
    while(!ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC ));//�ȴ�ת������
    return ADC_GetConversionValue(ADC1);	//�������һ��ADC1�������ת�����
}

/**----------------------------------------------------------------------------
* @FunctionName  : ADC1_Average_Get()
* @Description   : ���ADC1ƽ��ֵ
* @Data          : 2016/8/8
* @Explain       : 
-------------------------------------------------------------------------------
cnt:�������� 
------------------------------------------------------------------------------*/ 
u16 ADC1_Average_Get(u8 cnt)
{
    u32 temp_val = 0;
    u8 t;
    for(t = 0; t < cnt; t++)
    {
        temp_val += ADC1_Get();
    }
    return temp_val / cnt;
}

/**----------------------------------------------------------------------------
* @FunctionName  : ADC_Init()
* @Description   : ADC��ʼ��
* @Data          : 2016/8/8
* @Explain       : 
-------------------------------------------------------------------------------
None
------------------------------------------------------------------------------*/ 
void ADC2_Init(void)
{
    ADC_InitTypeDef ADC_InitStructure;
    GPIO_InitTypeDef GPIO_InitStructure;

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_ADC2, ENABLE);	 //ʹ��ADC1ͨ��ʱ��
    RCC_ADCCLKConfig(RCC_PCLK2_Div6);   //����ADC��Ƶ����6 72M/6=12,ADC���ʱ�䲻�ܳ���14M

    //PA1 ��Ϊģ��ͨ����������
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;		//ģ����������
    GPIO_Init(GPIOA, &GPIO_InitStructure);
    ADC_DeInit(ADC2);  //��λADC1

    ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;	//ADC����ģʽ:ADC1��ADC2�����ڶ���ģʽ
    ADC_InitStructure.ADC_ScanConvMode = DISABLE;	//ģ��ת�������ڵ�ͨ��ģʽ
    ADC_InitStructure.ADC_ContinuousConvMode = DISABLE;	//ģ��ת�������ڵ���ת��ģʽ
    ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;	//ת��������������ⲿ��������
    ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;	//ADC�����Ҷ���
    ADC_InitStructure.ADC_NbrOfChannel = 1;	//˳����й���ת����ADCͨ������Ŀ
    ADC_Init(ADC2, &ADC_InitStructure);	//����ADC_InitStruct��ָ���Ĳ�����ʼ������ADCx�ļĴ���
    ADC_Cmd(ADC2, ENABLE);	//ʹ��ָ����ADC1
    ADC_ResetCalibration(ADC2);	//ʹ�ܸ�λУ׼
    while(ADC_GetResetCalibrationStatus(ADC2));	//�ȴ���λУ׼����
    ADC_StartCalibration(ADC2);	 //����ADУ׼
    while(ADC_GetCalibrationStatus(ADC2));	 //�ȴ�У׼���� 
}

/**----------------------------------------------------------------------------
* @FunctionName  : ADC2_Get()
* @Description   : ���ADC��ֵ
* @Data          : 2016/8/8
* @Explain       : 
-------------------------------------------------------------------------------
None
------------------------------------------------------------------------------*/ 
u16 ADC2_Get(void)
{
    ADC_RegularChannelConfig(ADC2, 1, 1, ADC_SampleTime_239Cycles5);	//ADCͨ��,����ʱ��Ϊ239.5����
    ADC_SoftwareStartConvCmd(ADC2, ENABLE);		//ʹ��ָ����ADC�����ת����������
    while(!ADC_GetFlagStatus(ADC2, ADC_FLAG_EOC ));//�ȴ�ת������
    return ADC_GetConversionValue(ADC2);	//�������һ��ADC�������ת�����
}

/**----------------------------------------------------------------------------
* @FunctionName  : ADC2_Average_Get()
* @Description   : ���ADCƽ��ֵ
* @Data          : 2016/8/8
* @Explain       : 
-------------------------------------------------------------------------------
cnt:�������� 
------------------------------------------------------------------------------*/ 
u16 ADC2_Average_Get(u8 cnt)
{
    u32 temp_val = 0;
    u8 t;
    for(t = 0; t < cnt; t++)
    {
        temp_val += ADC2_Get();
    }
    return temp_val / cnt;
}




/**----------------------------------------------------------------------------
* @FunctionName  : ADC_Value_Get()
* @Description   : ���ADC��ת��ֵ
* @Data          : 2017/8/4
* @Explain       : 
-------------------------------------------------------------------------------
None
------------------------------------------------------------------------------*/ 
float ADC_Value_Get(u8 ch)
{
	float value = 0;
	if(ch == 1)
	{
		ADC_RegularChannelConfig(ADC1, ADC_Channel_1, 1, ADC_SampleTime_239Cycles5);	//ADCͨ��,����ʱ��Ϊ239.5����
		ADC_SoftwareStartConvCmd(ADC1, ENABLE);		//ʹ��ָ����ADC�����ת����������
		while(!ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC));//�ȴ�ת������
		value = ADC_GetConversionValue(ADC1)*3.3f/4096;	//�������һ��ADC�������ת�����
	}
	else if(ch == 0)
	{
		ADC_RegularChannelConfig(ADC2, ADC_Channel_0, 1, ADC_SampleTime_239Cycles5 );	//ADCͨ��,����ʱ��Ϊ239.5����
		ADC_SoftwareStartConvCmd(ADC2, ENABLE);		//ʹ��ָ����ADC�����ת����������
		while(!ADC_GetFlagStatus(ADC2, ADC_FLAG_EOC ));//�ȴ�ת������
		value = ADC_GetConversionValue(ADC2)*3.3f/4096;	//�������һ��ADC�������ת�����
	}
	return value;
	
}


/*******************************(C) COPYRIGHT 2016 Wind��л���죩*********************************/


















