# OLED

128 * 64 像素，4线

使用 OLED_CMDInit() 前建议延时 1000 ms 左右

WriteCmd() 和 WriteData 需要用到模拟 I2C 里的时序函数

OLED 显示使用页地址模式

OLED_ShowCHNCh() 的中文字库在 codetab.h 里，需要用 PCtoLCD 生成，字宽 = CHN_CHAR_COL，字高 / 8 = CHN_CHAR_PAGE，中文用 UTF-8 编码时每个字符占 3 字节，用 GB2312 编码时每个字符占 2 字节，对应 CHN_CHAR_BYTES