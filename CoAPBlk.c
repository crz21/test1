/*-----------------------------------------------
  SIZE.c - 

------------------------------------------------*/

#include <stdlib.h>
#include <string.h>

#include "Common.h"
#include "CoAPBlk.h"

/**
 * Construct SIZE struct
 */
void NewBlock(CoAPBlk_t *blk, u8 bf, u8 blkn, u16 len)
{
	blk->bf = bf;
	blk->blkn = blkn;
	blk->len = len;
}

void BlkFromBytes(CoAPBlk_t *blk, u8 buf[])
{
	blk->bf = buf[0] >> 7;
	blk->blkn = (buf[0] & 0x7f) >> 3;
	blk->len = buf[0] & 0x07;
 	blk->len = (blk->len << 8) + (buf[1] & 0xff);
}

/**
 * Convert Block struct to bytes, return byte array length
 */
u8 Blk2Bytes(CoAPBlk_t *blk, u8 buf[])
{
	buf[0] = (blk->bf << 7) + (blk->blkn << 3) + (u8)((blk->len >> 8) & 0x07);
	buf[1] = (u8)(blk->len & 0xff);

	return 2;
}

/**
 * Convert Block struct to option struct, return OK or error code
 */
Ret Blk2Option(CoAPBlk_t *blk, u8 opt_code, CoAPOption *opt)
{
	opt->opt_code = opt_code;
	opt->opt_len = Blk2Bytes(blk,opt->opt_val);

	return COAP_OK;
}

