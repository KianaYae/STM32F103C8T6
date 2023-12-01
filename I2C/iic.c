#include "iic.h"

/**************************************************
* Desc:     I2C 延时函数
* Para: In: us: 微秒数
* Other:    延时 n 微秒(大致)
**************************************************/
static void I2C_Delay_us(u8 us)
{
    u8 i = 0;
    while (us--)
    {
        for (i = 0; i < 14; i++);
    }
}

/**************************************************
* Desc:     I2C 起始信号
**************************************************/
void I2C_Start(void)
{
    SET_I2C_SDA;
    SET_I2C_SCL;
    I2C_Delay_us(5);
    RESET_I2C_SDA;
    I2C_Delay_us(5);
    RESET_I2C_SCL;
}

/**************************************************
* Desc:     I2C 停止信号
**************************************************/
void I2C_Stop(void)
{
    RESET_I2C_SDA;
    SET_I2C_SCL;
    I2C_Delay_us(5);
    SET_I2C_SDA;
    I2C_Delay_us(5);
}

/**************************************************
* Desc:     I2C 等待应答信号
* Return:   0: 应答成功
*           1: 应答失败
**************************************************/
u8 I2C_Wait_Ack(void)
{
    u8 timeout = 0;

    SET_I2C_SDA;
    I2C_Delay_us(5);
    SET_I2C_SCL;
    I2C_Delay_us(5);

    while (READ_I2C_SDA)
    {
        timeout++;
        if (timeout > 250)
        {
            I2C_Stop();
            return 1;
        }
    }

    RESET_I2C_SCL;
    I2C_Delay_us(5);

    return 0;
}

/**************************************************
* Desc:     I2C 应答信号
* Other:    SCL 单个脉冲信号的高电平期间, SDA 保持低
**************************************************/
void I2C_Ack(void)
{
    RESET_I2C_SDA;
    I2C_Delay_us(5);
    SET_I2C_SCL;
    I2C_Delay_us(5);
    RESET_I2C_SCL;
    I2C_Delay_us(5);
    SET_I2C_SDA;        // 释放数据总线
}

/**************************************************
* Desc:     I2C 非应答信号
* Other:    SCL 单个脉冲信号的高电平期间, SDA 保持高
**************************************************/
void I2C_Nack(void)
{
    SET_I2C_SDA;
    I2C_Delay_us(5);
    SET_I2C_SCL;
    I2C_Delay_us(5);
    RESET_I2C_SCL;
    I2C_Delay_us(5);
}

/**************************************************
* Desc:     I2C 发送字节
* Other:    1 字节 8 位, SCL 产生 8 个脉冲信号
**************************************************/
void I2C_Send_Byte(u8 data)
{
    u8 i = 0;

    RESET_I2C_SCL;

    for (i = 0; i < 8; i++)
    {
        if (data & 0x80)
        {
            SET_I2C_SDA;
        }
        else
        {
            RESET_I2C_SDA;
        }
        data <<= 1;
        I2C_Delay_us(5);

        SET_I2C_SCL;
        I2C_Delay_us(5);
        RESET_I2C_SCL;
        I2C_Delay_us(5);
    }
}

/**************************************************
* Desc:     I2C 接收字节
* Return:   接收到的字节数据
* Other:    1 字节 8 位, SCL 产生 8 个脉冲信号
**************************************************/
u8 I2C_Recv_Byte(void)
{
    u8 i = 0, value = 0;

    for (i = 0; i < 8; i++)
    {
        value <<= 1;

        SET_I2C_SCL;
        I2C_Delay_us(5);

        if (READ_I2C_SDA)
        {
            value += 1;
        }

        RESET_I2C_SCL;
        I2C_Delay_us(5);
    }

    return value;
}

/**************************************************
* Desc:     I2C 端口配置初始化
**************************************************/
void I2C_Configuration(void)
{
    RCC_APB2PeriphClockCmd(RCC_I2C_PORT, ENABLE);

    GPIO_InitTypeDef GPIO_InitStructure;

    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_Out_OD;
    GPIO_InitStructure.GPIO_Pin   = I2C_SCL_PIN | I2C_SDA_PIN;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;

    GPIO_Init(GPIO_PORT_I2C, &GPIO_InitStructure);  
}
