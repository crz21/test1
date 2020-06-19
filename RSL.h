#ifndef _RSL_H_

#define _RSL_H_

#include "Common.h"
#include "CoAP.h"

#define AEI_MAX_LEN 		12		// AEI最大长度
#define PATHSEG_MAX_LEN		10
#define PATH_MAX_SEGS		2
#define NODA_MAX_LEN		20
#define GWI_MAX_LEN			12

// String compression type
#define ENC_TYPE_STR		0
#define ENC_TYPE_BCD		1
#define ENC_TYPE_HEX		2

typedef struct {
	u8 len; // uncoded length
	char seg[PATHSEG_MAX_LEN+1];
} PATHSEG;

typedef struct {
	u8 valid;
	u8 hasPort;/* 0：MSE(节点内部的一个逻辑实体)       */
	u16 port;
	char aei[AEI_MAX_LEN+1];
	u8 segNum;
	PATHSEG path[PATH_MAX_SEGS];
	char noda[NODA_MAX_LEN+1];
	char gwi[GWI_MAX_LEN+1];
} RSL;

/**
 * Convert RSL struct from string expression. Return OK or error code
 * String format: [[AEI][@port]]/seg1/seg2/.../name
 */
Ret RslFromStr(RSL *rsi, char *str);

/**
 * Convert RSL struct to string. Return ok or error code
 */
Ret Rsl2Str(RSL *rsi, char buf[]);

/**
 * Convert RSL struct to bytes, return byte array length
 */
u8 Rsl2Bytes(RSL *rsi, u8 enc, u8 buf[]);

/**
 * Construct RSL struct from bytes, return OK or error code
 */
Ret RslFromBytes(RSL *rsi, u8 buf[], u8 len);

/**
 * Convert RSL struct to option struct, return OK or error code
 */
Ret Rsl2Option(RSL *rsi, u8 enc, u8 opt_code, CoAPOption *opt);

/**
 * Convert CoAPOpton (URI_PATH) into RSL, return OK or error 
 */
Ret RslFromOpt(CoAPOption *opt, RSL *rsl);

/**
 * Get resPath in supplied buffer. 
 * Return COAP_NULL if resPath is empty, otherwise return COAP_OK
 */
Ret RslGetPath(RSL *rsl, char buf[]);

/**
 * Return resName ptr in rsl. Return NULL if empty. 
 */
char *RslGetName(RSL *rsl);

Ret Str2Bytes(char *s, u8 buf[]);

u8 Bytes2Str(u8 buf[], char *s);

#endif
