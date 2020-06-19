#ifndef _PLC_H_
#define _PLC_H_

// Node type (role)
#define PLC_MASTER	    (1)
#define PLC_SLAVE	    (0)

// Protocol
#define nPLBus		    (1)
#define hPLBus		    (2)
#define PLBus512	    (3)
#define gHPLC		    (4)
#define sHPLC		    (5)

// Profile
#define APP_HOME		'h'
#define APP_INDUSTRY	'i'

// Index into config buffer
#define INDX_ROLE		(0)
#define INDX_PROTO		(1)
#define INDX_APP		(2)
#define INDX_VER		(3)
#define INDX_YEAR		(4)
#define INDX_MONTH		(6)
#define INDX_DAY		(7)
#define INDX_ID			(8)
#define INDX_APS		(9)
#define INDX_NWK		(10)
#define INDX_LL			(11)


typedef struct {
	u8 baudrate; //�����ʣ� 0x00��ʾ1200,0x01��ʾ2400��0x02��ʾ4800,0x03��ʾ9600,
	            //0x04��ʾ19200��0x05��ʾ38400��0x06��ʾ57600��0x07��ʾ115200
	u8 parity;	   //У��λ��0-none, 1=odd, 2=even
	u8 uart_save_flag; //�����־��0-���浽flash�У�1-���浽flash��
} UART_CONFIG;
typedef struct {
    u8 role;          //0=slave, 1=master
    u8 proto;         //1=nPLBus,��ʾխ���ز�
                      //2=hPLBus,��ʾ�����ز�
                      //3=PLBus512,
                      //4=gHLC,
                      //5=sHPLC,  Ӧ�ó�����.x��ʾ,.hn?��ʾ?��ͥ����,.i��ʾ��ҵ����
    u8 app_profile;   //��h�� - home, 'i' = industry
    u8 chip_type;     //оƬ���ͣ�0-3460CC,1-34600DE
    u8 fw_ver[6];
                      //fw_ver[0]�汾��λ
                      //fw_ver[1]�汾��λ
                      //fw_ver[2]���λ��fw_ver[3]���λ
                      //fw_ver[4]��ʾ�·ݣ�fw_ver[5]��ʾ�գ�ʱ����Ϣ����BCD���룬MSB����
    u8 nwk_ver[3];    //��ʾ�����汾��Ϣ,Nxxxx
    u8 layer_ver[2];  //��ʾ�ײ�汾��Ϣ��xxxx 
    u8 reserv[8];     //������Ϣ
} NODE_INFO;

typedef struct {
   	u16 did;		// did
	  u16 addr;		// short addr
   	u8 bw;			// 1=3Mhz,2=2.2Mhz
	  u8 mode;		//1=low speed, 2=mid spped, 3=hi speed
	  u8 tx_power;	//0=low,1=mid,2=hi
	  u8 reserv[5];	// reserved		
} PLC_CONFIG;


#endif/*#ifndef _PLC_H_*/

