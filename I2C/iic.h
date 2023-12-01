#ifndef __IIC_H
#define __IIC_H

#include "stm32f10x.h"

#define GPIO_PORT_I2C   GPIOB                   /* GPIO端口 */
#define RCC_I2C_PORT    RCC_APB2Periph_GPIOB    /* GPIO端口时钟 */
#define I2C_SCL_PIN     GPIO_Pin_6              /* SCL引脚 */
#define I2C_SDA_PIN     GPIO_Pin_7              /* SDA引脚 */

#define SET_I2C_SCL     GPIO_SetBits(GPIO_PORT_I2C, I2C_SCL_PIN)            /* 拉高 SCL */
#define RESET_I2C_SCL   GPIO_ResetBits(GPIO_PORT_I2C, I2C_SCL_PIN)          /* 拉低 SCL */

#define SET_I2C_SDA     GPIO_SetBits(GPIO_PORT_I2C, I2C_SDA_PIN)            /* 拉高 SDA */
#define RESET_I2C_SDA   GPIO_ResetBits(GPIO_PORT_I2C, I2C_SDA_PIN)          /* 拉低 SDA */

#define READ_I2C_SDA    GPIO_ReadInputDataBit(GPIO_PORT_I2C, I2C_SDA_PIN)   /* 读取 SDA */

void I2C_Start(void);
void I2C_Stop(void);
unsigned char I2C_Wait_Ack(void);
void I2C_Ack(void);
void I2C_Nack(void);
void I2C_Send_Byte(unsigned char data);
unsigned char I2C_Recv_Byte(void);
void I2C_Configuration(void);

#endif
