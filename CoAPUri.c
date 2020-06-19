/*-----------------------------------------------
  Uaps.c - Uaps message handling routines

------------------------------------------------*/
#include <stdlib.h>
#include <string.h>

#include "Common.h"
#include "CoAP.h"
#include "CoAPUri.h"
#include "LmeUtils.h"

u8 CoAPCreateUri(CoAPUri *uri, u8 *host, u8 hasPort, u16 port, u8 *path, u8 *query)
{
	u8 len;

	uri->host[0] = '\0';
	uri->hasPort  = 0;
	uri->path[0] = '\0';
	uri->query[0] = '\0';

	if (host != NULL) {
		len = strlen(host);
		memcpy(uri->host,host,len);
		uri->host[len] = 0;
	}

	uri->hasPort = hasPort;
	uri->port = port;

	if (path != NULL) {
		len = strlen(path);
		memcpy(uri->path,path,len);
		uri->path[len] = 0;
	}

	if (query != NULL) {
		len = strlen(query);
		memcpy(uri->query,query,len);
		uri->query[len] = 0;
	}

	return COAP_OK;
}




