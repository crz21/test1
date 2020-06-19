// Utils.c - Utilities
#define _CRT_SECURE_NO_WARNINGS

#include "Common.h"
#include <string.h>
#include <stdio.h>

/*------------------------------------------------
 uS延时函数，使用晶振12M，精确延时请使用汇编,大致延时
 长度T=tx2+5 uS 
------------------------------------------------*/
void DelayUs2x(unsigned char t)
{   
 	while(--t);
}

/*------------------------------------------------
 mS延时函数，使用晶振12M，精确延时请使用汇编
------------------------------------------------*/
void Delay_Ms(unsigned char t)
{
    while(t--){
        //大致延时1mS
        DelayUs2x(245);
        DelayUs2x(245);
    }
}

/**
 * String to BCD bytes. Return number of coded bytes.
 * 1 byte holds 2 BCD digits. If odd number of digits, the low 4 bits of last byte is set to 0x0f。
*/
u8 str2bcd(char *str, u8 len, u8 *buf)
{
	int i;
	u8 sz, remainder, j;

	sz = len >> 1;
    remainder = len & 0x01;
	j = 0;
   	// 转BCD码
   	for (i = 0; i < sz; i++) {
    	buf[i] = ((str[j++] - '0') << 4) | (str[j++]-'0');
	}
   	// 如果存在余数，需要填f
   	if (remainder > 0) {
		buf[i] = ((str[j++] - '0') << 4) | 0x0f;
	}

   	return (sz+remainder);
}

/**
 * Decode BCD bytes to string, return string length
 */
u8 bcd2str(u8 *buf, u8 len, char *str)
{
	int i;
	u8 j, b;

	j = 0;
	for (i = 0; i < len; i++) {
		b = buf[i];
		str[j++] = '0'+ (b >> 4);
		b &= 0x0f;
		if (b == 15)
			break;
		str[j++] = '0' + b;
	}

	str[j] = 0;

	return j;
}

// Decimal value of hex digit   
u8 hex_val(char hex)
{
	if ((hex >= '0') && (hex <= '9'))
		return (hex - '0');
	else if ((hex >= 'a') && (hex <= 'f'))
		return (hex - 'a' + 10);
	else if ((hex >= 'A') && (hex <= 'F'))
		return (hex - 'A' + 10);

	return 0;
}


/**
 * Encode hex string "0123456789abcdef" into bytes, 2 digits into one byte.
 * len must be even. 
 * The string may starts with "0x" or "oX"
 * 返回编码后的字节数 
*/
u8 str2hex(char *str, u8 len, u8 buf[])
{
	int i;
	u8 sz, j;
	char *p;

	p = str;
	if (*p == '0' && (*(p+1) == 'x' || *(p+1) == 'X'))
		p += 2;

	sz = len >> 1;
	j = 0;
   	// 转HEX码
   	for (i = 0; i < sz; i++) {
    	buf[i] = (hex_val(p[j++]) << 4) | hex_val(p[j++]);
	}
 	// 
   	return sz;
}

/**
 * Decode HEX in buffer to string。
 * 返回解码后的长度
 */
u8 hex2str(u8 *buf, u8 len, char *prefix, char *str)
{
	u8 i, j;
	u8 b;

	j = 0;
	if (prefix != NULL) {
		strcpy(str,prefix);
		j = strlen(prefix);
	}
		
	for (i = 0; i < len; i++) {
		b = buf[i] >> 4;
		if (b <= 9)
			str[j++] = '0'+ b;
		else {
			str[j++] = 'a' + b-10;
		}

		b = buf[i] & 0x0f;
		if (b <= 9)
			str[j++] = '0'+ b;
		else {
			str[j++] = 'a' + b-10;
		}
	}

	str[j] = 0; 

	return j;
}

u8 isNumber(char *s)
{
	char c;
	while(*s != 0) {
		c = *s++;
		if (c < '0' || c > '9')
			return 0;
	} 

	return 1;
}


u8 isHex(char *s)
{
	char *hex = "0123456789abcdefABCDEF";
	char c;

	if (*s != '0' || (*(s+1) != 'x' && *(s+1) != 'X')) 
		return 0;

	s += 2;
	while (*s != 0) { 
		c = *s++;
		if (strchr(hex,c) == NULL)
			return 0;
	}

	return 1;
}


void Itoa(long n,char s[])
{
	int i,j;
	long sign;
	char tmp[12];

	if((sign=n)<0)//记录符号
		n=-n;//使n成为正数

	i=0;
	do {
		tmp[i++]=n%10+'0';//取下一个数字
	} while ((n/=10)>0);//删除该数字

	if(sign<0)
		tmp[i++]='-';
	
	i--;
	j = 0;
	while(i >= 0)
		s[j++] = tmp[i--];

	s[j] = '\0';

}


#define isUpper(x) (x>='A' && x<='Z') //判断是大写字符。
#define isLower(x) (x>='a' && x<='z') //判断是小写字符。
#define toLowerCase(x) (x-'A'+'a')//转为小写
#define toUpperCase(x) (x-'a'+'A')//转为大写 

void toLower(char *s)
{
	int i;

	if (s[0] == 0)
		return;

	for(i = 0; s[i]; i++) {
		if (isUpper(s[i])) 
			s[i] = toLowerCase(s[i]); //如果是大写字符，转为小写。
	}
}

void toUpper(char *s)
{
	int i;

	if (s[0] == 0)
		return;

	for(i = 0; s[i]; i++) {
		if (isLower(s[i])) 
			s[i] = toUpperCase(s[i]); 
	}
}








