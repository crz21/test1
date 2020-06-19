#ifndef _COAP_URI_H_
#define _COAP_URI_H_

#include "Common.h"

// Config
#define URI_HOST_LEN	20	// Max uncoded str length
#define URI_PATH_LEN	50	//
#define URI_QUERY_LEN	20

typedef struct {
	u8 host[URI_HOST_LEN+1]; 	// Uncoded str, add 0x00 to end
	u8 hasPort;
	u16 port;
	u8 path[URI_PATH_LEN+1]; 	// byte array, need to convert to RESI
	u8 query[URI_QUERY_LEN+1]; 	// Uncoded str, add 0x00 to end
} CoAPUri;

u8 CoAPCreateUri(CoAPUri *uri, u8 *host, u8 hasPort, u16 port, u8 *path, u8 *query);
#endif
