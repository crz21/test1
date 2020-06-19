#ifndef __LMEUTILS_H__
#define __LMEUTILS_H__
/*------------------------------------------------
 uS��ʱ������ʹ�þ���12M��������ʱ����?T =t x 2+5 uS 
------------------------------------------------*/
void DelayUs2x(unsigned char t);
/*------------------------------------------------
 mS��ʱ����������ʹ�þ���12M����ȷ��ʱ��ʹ�û��
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