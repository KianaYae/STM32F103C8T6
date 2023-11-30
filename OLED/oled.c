#include "codetab.h"
#include "iic.h"
#include "oled.h"

const u8 ChnCharMatchTable[] = 
{
    "状态：正常故障"
};

/**************************************************
* Desc:     OLED 写命令
* Para: In: I2C_Command: 命令
**************************************************/
static void WriteCmd(u8 I2C_Command)
{
    I2C_Start();
    I2C_Send_Byte(OLED_ADDRESS);
    I2C_Wait_Ack();
    I2C_Send_Byte(OLED_CMD);
    I2C_Wait_Ack();
    I2C_Send_Byte(I2C_Command); 
    I2C_Wait_Ack();
    I2C_Stop();
}

/**************************************************
* Desc:     OLED 写数据
* Para: In: I2C_Data: 数据
**************************************************/
static void WriteData(u8 I2C_Data)
{
    I2C_Start();
    I2C_Send_Byte(OLED_ADDRESS);
    I2C_Wait_Ack();
    I2C_Send_Byte(OLED_DATA);
    I2C_Wait_Ack();
    I2C_Send_Byte(I2C_Data); 
    I2C_Wait_Ack();
    I2C_Stop();
}

/**************************************************
* Desc:     OLED 厂家初始化
* Other:    不需更改参数
**************************************************/
static void OLED_CMDInit(void)
{
    WriteCmd(0xae);

    WriteCmd(0x20);
    WriteCmd(0x02);

    WriteCmd(0xb0);
    WriteCmd(0x00);
    WriteCmd(0x10);

    WriteCmd(0xc8);
    WriteCmd(0xa1);

    WriteCmd(0x40);

    WriteCmd(0x81);
    WriteCmd(0xef);

    WriteCmd(0xa8);
    WriteCmd(0x3f);

    WriteCmd(0xd3);
    WriteCmd(0x00);

    WriteCmd(0xd5);
    WriteCmd(0xf0);

    WriteCmd(0xd9);
    WriteCmd(0x22);

    WriteCmd(0xda);
    WriteCmd(0x12);

    WriteCmd(0xdb);
    WriteCmd(0x20);

    WriteCmd(0x8d);
    WriteCmd(0x14);

    WriteCmd(0xa4);
    WriteCmd(0xa6);

    WriteCmd(0xaf);
}

/**************************************************
* Desc:     设置 OLED 起始地址
* Para: In: col:    列地址
*           page:   页地址
**************************************************/
static void OLED_SetPos(u8 col, u8 page)
{
    WriteCmd(0xB0 + page);
    WriteCmd(((col & 0xF0) >> 4) | 0x10);
    WriteCmd(col & 0x0F);
}

/**************************************************
* Desc:     填充 OLED 屏幕
* Para: In: data: 填充数据
**************************************************/
static void OLED_Fill(u8 data)
{
    u8 page = 0, col = 0;
    
    for (; page < 8; page++)
    {
        WriteCmd(0xB0 + page);
        WriteCmd(0x00);
        WriteCmd(0x10);

        for (col = 0; col < 128; col++)
        {
            WriteData(data);
        }
    }
}

/**************************************************
* Desc:     显示英文字符串
* Para: In: col:    列地址
*           page:   页地址
*           ch[]:   字符串
**************************************************/
void OLED_ShowStr(u8 col, u8 page, u8 ch[])
{
   u8 i = 0;
   u8 m = 0, n = 0;
   u16 ind = 0;

   while (ch[i] != '\0')
   {
       ind = (ch[i] - 32) * EN_CHAR_IND / EN_CHAR_BYTES;

       for (m = 0; m < EN_CHAR_PAGE; m++)
       {
           OLED_SetPos(col, page + m);

           for (n = 0; n < EN_CHAR_COL; n++)
           {
               WriteData(ConsolasF8x16[ind + n + m * EN_CHAR_COL]);
           }
       }

       i += EN_CHAR_BYTES;
       col += EN_CHAR_COL;
   }
}

/**************************************************
* Desc:     显示中文字符串
* Para: In: col:    列地址
*           page:   页地址
*           ch[]:   字符串
* Other:    UTF-8 中文占 3 字节
**************************************************/
void OLED_ShowCHNCh(u8 col, u8 page, u8 ch[])
{
    u8 i = 0, j = 0;
    u8 m = 0, n = 0;
    u16 ind = 1;

    while (ch[i] != '\0')
    {
        j = 0;
        ind = 1;
        while (ChnCharMatchTable[j] != '\0')
        {
            if ((ChnCharMatchTable[j] == ch[i]) && (ChnCharMatchTable[j + 1] == ch[i + 1]) && (ChnCharMatchTable[j + 2] == ch[i + 2]))
            {
                ind = j * CHN_CHAR_IND / CHN_CHAR_BYTES;
                break;
            }
            j += CHN_CHAR_BYTES;
        }

        if (ind != 1)
        {
            for (m = 0; m < CHN_CHAR_PAGE; m++)
            {
                OLED_SetPos(col, page + m);
                for (n = 0; n < CHN_CHAR_COL; n++)
                {
                    WriteData(SongF16x16[ind + n + m * CHN_CHAR_COL]);
                }
            }
        }
        else    // 显示空白字符
        {
            for (m = 0; m < CHN_CHAR_PAGE; m++)
            {
                OLED_SetPos(col, page + m);
                for (n = 0; n < CHN_CHAR_COL; n++)
                {
                    WriteData(0x00);
                }
            }
        }
        i += CHN_CHAR_BYTES;
        col += CHN_CHAR_COL;
    }
}
