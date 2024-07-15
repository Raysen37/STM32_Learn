#include "bsp_IIC.h"


/*
 *  ��������I2C_Delay
 *  ����������ʹ�������ʽ��ʱ
 *  ���������t-->��ʱ�¼�
 *  �����������
 *  ����ֵ����
*/
void I2C_Delay(uint32_t t)
{
    volatile uint32_t tmp = t;
    while(tmp--);
}

/*
 *  ��������I2C_GPIO_ReInit
 *  ������������ģ��I2C��SCL��SDA���Ž������³�ʼ��
 *  �����������
 *  �����������
 *  ����ֵ����
*/
void I2C_GPIO_ReInit(void)
{

    //GPIO_InitTypeDef GPIO_InitStruct = {0};

    /* GPIO Ports Clock Enable */
    __HAL_RCC_GPIOB_CLK_ENABLE();
    
    
    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.Mode = GPIO_MODE_OUTPUT_OD;
    GPIO_InitStructure.Pin = GPIO_PIN_6 | GPIO_PIN_7;
    GPIO_InitStructure.Speed = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStructure);
}
/*
 *  ��������I2C_Start
 *  ����������ģ�ⷢ��I2C�Ŀ�ʼ�ź�-->��SCL�ĸߵ�ƽ�£�SDA�ĵ�ƽ�ɸߵ��ͱ仯
 *  �����������
 *  �����������
 *  ����ֵ����
*/
void I2C_Start(void)
{
    SCL_H;
    SDA_H;
    I2C_Delay(100);
    SDA_L;
    I2C_Delay(100);
}

/*
 *  ��������I2C_Stop
 *  ����������ģ�ⷢ��I2C��ֹͣ�ź�-->��SCL�ĸߵ�ƽ�£�SDA�ĵ�ƽ�ɵ͵��߱仯
 *  �����������
 *  �����������
 *  ����ֵ����
*/
void I2C_Stop(void)
{
    SCL_H;
    SDA_L;
    I2C_Delay(100);
    SDA_H;
    I2C_Delay(100);
}

/*
 *  ��������I2C_GetAck
 *  ����������ģ��I2C��ȡ���豸����Ӧ�ź�-->��SCL�ĸߵ�ƽ�£����豸��SDA����
 *  �����������
 *  �����������
 *  ����ֵ���ɹ��õ���Ӧ����0�����򷵻�-1
*/
int I2C_GetAck(void)
{
    uint8_t i = 0;
    SCL_L;
    SDA_H;
    I2C_Delay(100);
    SCL_H;
    while(SDA_IN != 0)
    {
        i++;
        if(i == 100)
        {
            SCL_L;
            return -1;
        }
        I2C_Delay(10);
    }
    SCL_L;
    return 0;
}

/*
 *  ��������I2C_ACK
 *  ����������ģ��I2C����һ��Ӧ���źţ��ڵھŸ�ʱ�ӽ�SDA����
 *  �����������
 *  �����������
 *  ����ֵ����
*/
void I2C_ACK(void)
{
    SCL_L;
    SDA_L;
    I2C_Delay(100);
    SCL_H;
    I2C_Delay(100);
}

/*
 *  ��������I2C_NACK
 *  ����������ģ��I2C����һ����Ӧ���źţ��ڵھŸ�ʱ�ӽ�SDA����
 *  �����������
 *  �����������
 *  ����ֵ����
*/
void I2C_NACK(void)
{
    SCL_L;
    SDA_H;
    I2C_Delay(100);
    SCL_H;
    I2C_Delay(100);
}

/*
 *  ��������I2C_WriteByte
 *  ����������ģ��I2C����һ���ֽڵ�����
 *  ���������data-->Ҫ���ͳ�ȥ�����ݣ���Χ0~255
 *  �����������
 *  ����ֵ����
*/
void I2C_WriteByte(uint8_t data)
{
    uint8_t i = 0;
    for(i=0; i<8; i++)
    {
        SCL_L;
        I2C_Delay(100);
        if(data & 0x80)
        {
            SDA_H;
        }
        else
        {
            SDA_L;
        }
        data <<= 1; // ����1bit���ݺ�Ҫ�������ݣ���data�Ĵθ�λ��λ�����λ
        SCL_H;
        I2C_Delay(100);
    }
    I2C_GetAck();
}

/*
 *  ��������I2C_ReadByte
 *  ����ֵ�����ض�ȡ��������
 *  ���������ack-->���ݴ˲����ж��ڶ���һ���ֽ�֮���Ƿ񷢳�Ӧ���ź�
 *  �����������
*/
uint8_t I2C_ReadByte(uint8_t ack)
{
    uint8_t i = 0;
    uint8_t data = 0;
    
    SDA_H;
    for(i=0; i<8; i++)
    {
        SCL_L;
        I2C_Delay(100);
        SCL_H;
        I2C_Delay(100);
        data <<= 1; // ��������ǰ��Ҫ����һ����������1λ�����������������һλ����
        if(SDA_IN == 1)    
        {                 
            data++;
        }
        else
        {
            data = data;
        }
    }
    
    // ����ack�����Ƿ񷢳�Ӧ��
    if(ack == 0)
    {
        I2C_ACK();
    }
    else if(ack == 1)
    {
        I2C_NACK();
    }
    
    return data;
}

