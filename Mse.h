#ifndef _MSE_H_

#define  _MSE_H_
#include "Common.h"
#include "RSL.h"
#include "Common.h"
#include "CoAPUri.h"
#include "LmeUtils.h"
#include "PLC.h"


//RSC
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


//��λ�Ȳ���(RSC_RESET			"1")
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

//�ڵ����   (RSC_NODE_MANAGE     "102")
#define RSI_ROLE_INFO       "1"
#define RSI_WHITE_LIST      "2"
#define RSI_ADD_PROFILE     "3"
#define RSI_DEL_PROFILE     "4"
#define RSI_QUERY_PROFILE   "5"
#define RSI_CLEAN_PROFILE   "6"

//�������(RSC_NET_MANAGE      "103")
#define RSI_START_NET       "1"
#define RSI_NET_FLAG        "2"
#define RSI_NET_LIST        "3"
#define RSI_HEART_BEAT      "4"
#define RSI_ROUTE_MODE      "5"

//���������(RSC_DATA_SERVE      "104")
#define RSI_UNICAST         "1"
#define RSI_SUB_NET_CAST    "2"
#define RSI_ENTIRE_NET_CAST "3"

typedef enum{
	RSI_NODE_INFO_QUERY_CODE=1,  //1,�ڵ���Ϣ��ѯ
	RSI_MAC_QUERY_CODE,          //2,�ڵ��ַ��ѯ
	RSI_MAC_SET_CODE,           //3,�ڵ��ַ����

	RSI_SOFTWARE_RESET=11,          //11,�����λ
	RSI_FACTORY_DATA_RESEET_CODE, //12,�ָ���������
	
	RSI_UART_CONFIG_CODE=21,       //21,��������

	RSI_SNID_QUERY_CODE=31,        //31,SNID��ѯ
	RSI_SNID_SET_CODE,          //32,SNID����
	RSI_BW_QUERY_CODE,            //33,�����ѯ
	RSI_BW_SET_CODE,          //34,��������
	RSI_TX_POWER_QUERY_CODE,    //35,���͹��ʲ�ѯ
	RSI_TX_POWER_SET_CODE,      //36,���͹�������

	RSI_WITHOUT_NET_NODE_SEARCH_CODE=1011,//1011�ڵ�����
	

	//�ڵ����   (RSC_NODE_MANAGE     "102")
	RSI_NODE_ROLE_QUERY_CODE = 1020,   //1020,�ڵ��ɫ��Ϣ��ѯ
	RSI_NODE_ROLE_SET_CODE = 1021,    //1021,�ڵ��ɫ����
	RSI_WHITE_LIST_SET_CODE=1022,  //1022������������
	RSI_ADD_PROFILE_CODE=1023,     //1023,��ӽڵ㵵��(�ڵ�MAC��ַ)
	RSI_DEL_PROFILE_CODE,     //1024,ɾ���ڵ㵵��
	RSI_QUERY_PROFILE_CODE,   //1025,��ѯ����
	RSI_CLEAN_ALL_PROFILE_CODE,  //1026,��յ���

	//�������(RSC_NET_MANAGE      "103")
	RSI_START_NET_CODE = 1031,             //1031,��������
	RSI_NETWORKING_STATUS_CODE,             //1032,��ѯ����״̬
	RSI_ROUTE_LIST_QUERY_CODE,            //1033��·���б���Ϣ��ѯ

	RSI_HEARTBEAT_INFO_QUERY_CODE,         //1034��������ѯ����
	RSI_HEARTBEAT_INFO_SET_CODE,          //1035,�������÷���

	//���������(RSC_DATA_SERVE      "104")
	RSI_UNICAST_COMMUNICATION_CODE = 1041, //1041,���ݵ�������
	RSI_SUBNET_BROADCAST_CODE_CODE,        //1042�������㲥����
	RSI_ENTIRE_NET_BROADCAST_CODE         //1043��ȫ���㲥����
}APP_To_PLbus_Attribute_MsgType_Code;


typedef struct{
	APP_To_PLbus_Attribute_MsgType_Code function_code;
	u8 *destAddr;
	u8 *payload_data;
	u16 payload_len;
	u16 message_id; 
}app_coap_para_t;
/**
 * Processing MSE message
 */
void MseProc(CoAPMessage *rxMsg, RSL *rsl,u8 *resPath);

/**
 * Processing APP message
 */

/**
* recv meesgae into coap type struct
*/
//int MsgTransfromCoapProc(u8 *pbuf, u16 dataLen, CoAPMessage *recv_msg,RSL *rsl);
u8  MsgTransfromCoapProc(char *uart_recv_buf, u16 dataLen, app_coap_para_t *coapPara);


/*Creat coap message*/
//u16 CreateCoapMessage(CoAPMessage *msg,u8 message_type, u8 method_code, char uri_path[], u8 *content_data, u16 content_length, u8 content_fmt, u8 *send_buf);

u16 CreateServiceCoapMessage(app_coap_para_t *coapPara, u8 *coap_buf);

u16 CreateDataSendCoapMessage(app_coap_para_t *coapPara, u8 *coap_buf);

#endif
