#ifndef _COAPBLK_H_

#define _COAPBLK_H_

#include "Common.h"
#include "CoAP.h"

typedef struct {
	u8 bf;
	u8 blkn;
	u16 len;
} CoAPBlk_t;


#endif
