#ifndef _COAP_H_
#define _COAP_H_

#include "Common.h"
#include "CoAPUri.h"


#define COAP_VER			1	// CoAP version
#define COAP_TKL			2	// TKL default

// CoAP Configurations
#define COAP_MAX_OPTIONS	5	// max options in a message
#define COAP_MAX_OPTLEN		30	// opt value max size

// Funtion return error code
typedef enum {
	COAP_OK				= 0,
	COAP_ERROR			= 1, // general error	
	COAP_INVALID		= 2, // invalid error
	COAP_NULL			= 3, // null error
	COAP_TOO_MANY_OPTS	= 4, // too many options
	COAP_EMPTY_OPTIONS	= 5, // 0 options in message 
	COAP_OPT_NOT_FOUND	= 6	 // specified opt not found in opt list
} CoAP_RetCode;

// Escapse sequence
#define ESC_CHAR	 		'\x1b'  // ESC char
#define ESC_STRING			"\n\?\x1b\x1b\x1b\x1b\n\a"	/*0A 3F 1B 1B 1B 1B 0A 07*/
#define ESC_LEN				8

// Message type
typedef enum {
	COAP_TYPE_CON	= 0,
	COAP_TYPE_NON = 1,
	COAP_TYPE_ACK	= 2,
	COAP_TYPE_RST	= 3
} CoAP_TypeEnum;

// Method code
// 0.dd
typedef enum {
	COAP_EMPTY_MSG  =	0x00,	//0.0
	COAP_REQ_GET		=	0x01,	//0.1
	COAP_REQ_POST		=	0x02,	//0.2
	COAP_REQ_PUT		=	0x03,	//0.3
	COAP_REQ_DELETE		=	0x04	//0.4
} CoAP_MethodEnum;

// 2.dd, positive response
typedef enum {
	COAP_ACK_CREATED	=	0x41,	//2.01, succefully created
	COAP_ACK_DELETED	=	0x42,	//2.02, deleted
	COAP_ACK_VALID		=	0x43,	//2.03, valid
	COAP_ACK_CHANGED	=	0x44,	//2.04, changed
	COAP_ACK_CONTENT	=	0x45	//2.05, content
} CoAP_AckCode;


typedef enum {
	// 4.dd, request error
	COAP_BAD_REQUEST	=	0x80,	//4.0, bad request
	COAP_UNAUTHORIZED	=	0x81,	//4.1
	COAP_BAD_OPTION		=	0x82,	//4.2
	COAP_FORBIDDEN		=	0x83,
	COAP_NOT_FOUND		=	0x84,
	COAP_BAD_METHOD		=	0x85,
	COAP_BAD_DATA		=	0x86,	// data not accepted
	COAP_BAD_FORMAT		=	0x8f,
	// 5.dd, server error
	COAP_SERVER_ERROR		= 0xa0,	//5.00, Error in server
	COAP_NOT_IMPLEMENTED	= 0xa1,	//5.01, not supported by server
	COAP_SERVICE_UNAVAIL	= 0xa3,	//5.03, service currently not available
	COAP_INVALID_PROXY		 =0xa5	//5.05, proxying not supported
} CoAP_ResCode;

// Options
typedef enum {
	COAP_OPT_RSV0			= 0,	// reserved
	COAP_OPT_MATCH			= 1,	// If match
	COAP_OPT_URI_HOST		= 3,	// uri-host
	COAP_OPT_ETAG			= 4,	// ETag
	COAP_OPT_NONE_MATCH		= 5,	// If none match
	COAP_OPT_URI_PORT		= 7,	// Uri-port
	COAP_OPT_LOC_PATH		= 8,	// Location-path
	COAP_OPT_URI_PATH		= 11,	// Uri-path
	COAP_OPT_FORMAT			= 12,	// Content-format
	COAP_OPT_MAX_AGE		= 14,	// Max-age
	COAP_OPT_URI_QUERY		= 15,	// Uri-query
	COAP_OPT_ACCEPT			= 17,	// Accept
	COAP_OPT_LOC_QUERY		= 20,	// Location-query
	COAP_OPT_PROXY_URI		= 35,	// Proxy-uri
	COAP_OPT_PROXY_SCHEME	= 39,	// Proxy-scheme
	COAP_OPT_SIZE1			= 60	// Size1
} CoAP_OptEnum;
 
// Content format
typedef enum {
	COAP_FMT_TEXT		= 0,	// 文本,默认utf8
	COAP_FMT_LINK		= 40,	//
	COAP_FMT_XML		= 41,	//
	COAP_FMT_OCTETS		= 42,	//Application/octet-stream，字节序列
	COAP_FMT_EXI		= 47,	//
	COAP_FMT_JSON		= 50,	//
	COAP_FMT_TLV		= 51	//
} CoAP_FormatEnum;

// Message header
typedef struct {
	u8 tkl:4;
	u8 type:2;
	u8 ver:2;
	u8 method;
	u16 id; 		// Note: transmit in network byte order, i.e., MSB first
} CoAPHeader;

// Message option
typedef struct {
	u16 opt_code;  	// opt code
	u8 opt_len;
	u8 opt_val[COAP_MAX_OPTLEN+1]; // hold value bytes
} CoAPOption;

// CoAP message struct
typedef struct {
	CoAPHeader hdr;
	u8 token[8];
	u8 num_opts;
	CoAPOption options[COAP_MAX_OPTIONS];
	u8 *pl_ptr; // ptr to payload buffer
	u16 pl_len; // payload length
} CoAPMessage;

/**
 * Construct CoAP message struct for specified type, method and uri 
 */
void CoAPCreateMessage(CoAPMessage *msg, u8 type, u8 method, CoAPUri *uri);

/**
 * Add string option to message's opt list. 
 */
void CoAPPutStrOption(CoAPMessage *msg, u16 opt_code, u8 *str);

/**
 * Add UINT option to message's opt list
 */
void CoAPPutIntOption(CoAPMessage *msg, u16 opt_code, u16 val);

/**
 * Add option into message's option list. val is in byte array.
 * Return COAP_TOO_MANY_OPTS if list is full.
 */
Ret CoAPPutOption(CoAPMessage *msg, u16 opt_code, u8 *val, u8 len);

/**
 * Put data content. Note: data content is in seperate buffer
 */
void CoAPPutData(CoAPMessage *msg, u8 *buf, u16 len, u8 fmt);

/**
 * Put string data content. Note: data content is in seperate buffer
 */
void CoAPPutStrData(CoAPMessage *msg, char *str);

/**
 * Construct response message
 */
void CoAPResponse(CoAPMessage *req, CoAPMessage *res,u8 type,u8 method);

/**
 * Convert CoAP message struct into bytes for transmit.
 * Return encoded length
 */
u16 CoAP2Bytes(CoAPMessage *msg, u8 *buf);

/**
 * Decode received bytes into message struct. Return OK or error code
 */
Ret CoAPFromBytes(u8 *buf, u16 buf_len, CoAPMessage *msg);

/**
 * Get option ptr in message width specified opt code
 */
CoAPOption *CoAPGetOption(CoAPMessage *msg, u16 opt_code);

/*
 * Construct Uri struct from message. Return OK or error code
 */
Ret CoAPGetUri(CoAPMessage *msg, CoAPUri *uri);

#endif
