#ifndef __LMEUTILS_H__
#define __LMEUTILS_H__
/*------------------------------------------------
 uS延时函数，使用晶振12M，大致延时长度?T =t x 2+5 uS 
------------------------------------------------*/
void DelayUs2x(unsigned char t);
/*------------------------------------------------
 mS延时函数，这里使用晶振12M，精确延时请使用汇编
------------------------------------------------*/
void Delay_Ms(unsigned char t);

/*
 * String to BCD bytes, return number of coded bytes
 */
u8 str2bcd(char *str, u8 len, u8 *buf);

/*
 * BCD bytes to string, return string length
 */
u8 bcd2str(u8 *buf, u8 len, char *str);


/**
 * hex/string convertion
 */
u8 str2hex(char *str, u8 len, u8 *buf);
u8 hex2str(u8 *buf, u8 len, char *prefix, char *str);

u8 isNumber(char *str);
u8 isHex(char *str);

void Itoa(long n, char s[]);

void toLower(char *s);
void toUpper(char *s);

#endif