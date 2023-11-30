#ifndef __OLED_H
#define __OLED_H

#define OLED_ADDRESS    (0x78)
#define OLED_CMD        (0x00)
#define OLED_DATA       (0x40)

#define EN_CHAR_COL     (8)
#define EN_CHAR_PAGE    (2)
#define EN_CHAR_BYTES   (1)
#define EN_CHAR_IND     ((EN_CHAR_COL) * (EN_CHAR_PAGE))

#define CHN_CHAR_COL    (16)
#define CHN_CHAR_PAGE   (2)
#define CHN_CHAR_BYTES  (3)
#define CHN_CHAR_IND    ((CHN_CHAR_COL) * (CHN_CHAR_PAGE))

void OLED_ShowStr(unsigned char col, unsigned char page, unsigned char ch[]);
void OLED_ShowCHNCh(unsigned char col, unsigned char page, unsigned char ch[]);

#endif
