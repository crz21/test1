/***************************************************************************************

  Copyright (C), 2012-2016, ZHANGYA

 ***************************************************************************************
  File Name     : endpoints.h
  Version       : Initial Draft
  Author        : zhangya
  Created       : 2019/1/4
  Last Modified :
  Description   : endpoints.c header file
  Function List :
  History       :
  1.Date        : 2019/1/4
    Author      : zhangya
    Modification: Created file

***************************************************************************************/
#ifndef __ENDPOINTS_H__
#define __ENDPOINTS_H__

/*------------------------------------------------------------------------------ *
 * ------------------------ $external variables                           *
 *------------------------------------------------------------------------------ */

/*------------------------------------------------------------------------------ *
 * ----------------------- $external routine prototypes                  *
 *------------------------------------------------------------------------------ */

/*------------------------------------------------------------------------------ *
 * ----------------------- $internal routine prototypes                  *
 *------------------------------------------------------------------------------ */
//RSC
#define RSC_BASIC			""
#define RSC_RESET			"1"
#define RSC_UART_CONFIG		"2"
#define RSC_PLC_CONFIG		"3"
#define RSC_TEST_MODE		"5"
#define RSC_MSG_RELAY		"10"
#define RSC_PUBLIC_MANAGE   "101"
#define RSC_NODE_MANAGE     "102"
#define RSC_NET_MANAGE      "103"
#define RSC_DATA_SERVE      "104"

// Basic service
#define RSI_NODE_INFO		"1"		// node info
#define RSI_MAC				"2"		// mac
#define RSI_COMPILE_TIME    "3"     //编译时间

//复位等操作(RSC_RESET			"1")
#define RSI_RESET           "1"
#define RSI_FACTORY         "2"
#define RSI_UPGRADE         "3"

// Uart (RSC_UART_CONFIG		"2")
#define RSI_UART_CONFIG		"1"
#define RSI_UART_BAUD		"2"

//RSC_PLC_CONFIG		"3"
#define RSI_SNID            "1"
#define RSI_BW              "2"
#define RSI_TX_POWER        "3"

//RSC_TEST_MODE		"5"
#define RSI_TEST_VER        "0"
#define RSI_TEST_LOAD_ENAB       "3"
#define RSI_TEST_CONFIG     "4"
#define RSI_TEST_INFO       "5"
#define RSI_READ_TEST_INFO       "7"
#define RSI_TEST_ENAB       "8" 
#define RSI_TEST_MAC        "10"

//#define RSC_PUBLIC_MANAGE   "101"
#define RSI_NODE_SEARCH     "1"
#define RSI_REGISTER_MODE   "2"
#define RSI_COMMU_MODE      "3"

//节点管理   (RSC_NODE_MANAGE     "102")
#define RSI_ROLE_INFO       "1"
#define RSI_WHITE_LIST      "2"
#define RSI_ADD_PROFILE     "3"
#define RSI_DEL_PROFILE     "4"
#define RSI_QUERY_PROFILE   "5"
#define RSI_CLEAN_PROFILE   "6"

//网络管理(RSC_NET_MANAGE      "103")
#define RSI_START_NET       "1"
#define RSI_NET_FLAG        "2"
#define RSI_NET_LIST        "3"
#define RSI_HEART_BEAT      "4"
#define RSI_ROUTE_MODE      "5"

//数据项服务(RSC_DATA_SERVE      "104")
#define RSI_UNICAST         "1"
#define RSI_SUB_NET_CAST    "2"
#define RSI_ENTIRE_NET_CAST "3"


/*============================数据长度========================*/
#define ROLE_INFO_LEN               (1)
#define WHITE_ENABLE_LEN            (1)
#define NET_FINISH_FLAG_LEN         (1)
#define ROUTE_UPDATE_LEN            (1)
#define DW_MODE_LEN                 (1)
#define TX_POWER_LEN                (1)
#define COMMON_MODE_LEN             (1)
#define BATE_CFG_LEN                (3)
#define EXPEL_ALL_FINISH_LEN        (1)

/*------------------------------------------------------------------------------ *
 * ------------------------ $project-wide global variables                *
 *------------------------------------------------------------------------------ */
typedef enum{
    COAP_FSH_OWN_CTR = 0,   
    COAP_FSH_MAC_CTR,       /*保存MAC地址*/
    COAP_BATE_CTR,          /*串口波特率*/
    COAP_RESET_CTR,         /*模块复位*/
    /* ....  */
    COAP_LED_CTR,
    COAP_WHITE_LIST_CTR,    /*白名单*/
    COAP_NODE_SEARCH,       /*节点搜索*/
    /* ....  */
	  COAP_NODE_REGIST,
    COAP_MAX_CTR   = 31
}coap_ctr_e;

/*------------------------------------------------------------------------------ *
 * ------------------------ $module-wide global variables                 *
 *------------------------------------------------------------------------------ */

/*------------------------------------------------------------------------------ *
 * ------------------------ $constants                                    *
 *------------------------------------------------------------------------------ */
extern U32 g_coapCtr;
/*------------------------------------------------------------------------------ *
 * ----------------------- $macros                                       *
 *------------------------------------------------------------------------------ */

/*------------------------------------------------------------------------------ *
 * ----------------------  $routines' implementations                    *
 *------------------------------------------------------------------------------ */

extern U8 is_coap(U8 * pData, U16 len, U8 ** pIndex, U16 * pLen);

extern u8 coap_msg_proc(CoAPMessage *rxMsg, RSL *rsl, u8 from);

extern u8 coap_data_proc(u8 * pData, U16 len, RSL *rsl);

extern u8 StrToMac(u8 *pbDest, u8 *pbSrc);

#endif /* __ENDPOINTS_H__ */

/*========================endfild=========================*/
