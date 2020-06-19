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
	u8 baudrate; //波特率， 0x00表示1200,0x01表示2400，0x02表示4800,0x03表示9600,
	            //0x04表示19200，0x05表示38400，0x06表示57600，0x07表示115200
	u8 parity;	   //校验位，0-none, 1=odd, 2=even
	u8 uart_save_flag; //保存标志，0-不存到flash中，1-保存到flash中
} UART_CONFIG;
typedef struct {
    u8 role;          //0=slave, 1=master
    u8 proto;         //1=nPLBus,表示窄带载波
                      //2=hPLBus,表示高速载波
                      //3=PLBus512,
                      //4=gHLC,
                      //5=sHPLC,  应用场景用.x表示,.hn?表示?家庭网络,.i表示工业网络
    u8 app_profile;   //’h’ - home, 'i' = industry
    u8 chip_type;     //芯片类型，0-3460CC,1-34600DE
    u8 fw_ver[6];
                      //fw_ver[0]版本高位
                      //fw_ver[1]版本低位
                      //fw_ver[2]年高位、fw_ver[3]年低位
                      //fw_ver[4]表示月份，fw_ver[5]表示日，时间信息按照BCD编码，MSB传输
    u8 nwk_ver[3];    //表示网络层版本信息,Nxxxx
    u8 layer_ver[2];  //表示底层版本信息，xxxx 
    u8 reserv[8];     //保留信息
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

