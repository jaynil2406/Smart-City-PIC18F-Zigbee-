
/////////////////////////////////////////
////// short address registers  /////////
/////////////////////////////////////////
#define RXMCR     0x00
#define PANIDL    0x01
#define PANIDH    0x02
#define SADRL     0x03
#define SADRH     0x04
#define EADR0     0x05
#define EADR1     0x06
#define EADR2     0x07
#define EADR3     0x08
#define EADR4     0x09
#define EADR5     0x0A
#define EADR6     0x0B
#define EADR7     0x0C
#define RXFLUSH   0x0D
#define ORDER     0x10
#define TXMCR     0x11
#define ACKTMOUT  0x12
#define ESLOTG1   0x13
#define SYMTICKL  0x14
#define SYMTICKH  0x15
#define PACON0    0x16
#define PACON1    0x17
#define PACON2    0x18
#define TXBCON0   0x1A
#define TXNCON    0x1B
#define TXG1CON   0x1C
#define TXG2CON   0x1D
#define ESLOTG23  0x1E
#define ESLOTG45  0x1F
#define ESLOTG67  0x20
#define TXPEND    0x21
#define WAKECON   0x22
#define FRMOFFSET 0x23
#define TXSTAT    0x24
#define TXBCON1   0x25
#define GATECLK   0x26
#define TXTIME    0x27
#define HSYMTMRL  0x28
#define HSYMTMRH  0x29
#define SOFTRST   0x2A
#define SECCON0   0x2C
#define SECCON1   0x2D
#define TXSTBL    0x2E
#define RXSR      0x30
#define INTSTAT   0x31
#define INTCON_M  0x32
#define GPIO      0x33
#define TRISGPIO  0x34
#define SLPACK    0x35
#define RFCTL     0x36
#define SECCR2    0x37
#define BBREG0    0x38
#define BBREG1    0x39
#define BBREG2    0x3A
#define BBREG3    0x3B
#define BBREG4    0x3C
#define BBREG6    0x3E
#define CCAEDTH   0x3F


///////////////////////////////////////////
//////// long address registers  //////////
///////////////////////////////////////////
#define RFCON0    0x200
#define RFCON1    0x201
#define RFCON2    0x202
#define RFCON3    0x203
#define RFCON5    0x205
#define RFCON6    0x206
#define RFCON7    0x207
#define RFCON8    0x208
#define SLPCAL0   0x209
#define SLPCAL1   0x20A
#define SLPCAL2   0x20B
#define RFSTATE   0x20F
#define RSSI      0x210
#define SLPCON0   0x211
#define SLPCON1   0x220
#define WAKETIMEL 0x222
#define WAKETIMEH 0x223
#define REMCNTL   0x224
#define REMCNTH   0x225
#define MAINCNT0  0x226
#define MAINCNT1  0x227
#define MAINCNT2  0x228
#define MAINCNT3  0x229

#define TESTMODE  0x22F

#define ASSOEADR0 0x230
#define ASSOEADR1 0x231
#define ASSOEADR2 0x232
#define ASSOEADR3 0x233
#define ASSOEADR4 0x234
#define ASSOEADR5 0x235
#define ASSOEADR6 0x236
#define ASSOEADR7 0x237
#define ASSOSADR0 0x238
#define ASSOSADR1 0x239
#define UPNONCE0  0x240
#define UPNONCE1  0x241
#define UPNONCE2  0x242
#define UPNONCE3  0x243
#define UPNONCE4  0x244
#define UPNONCE5  0x245
#define UPNONCE6  0x246
#define UPNONCE7  0x247
#define UPNONCE8  0x248
#define UPNONCE9  0x249
#define UPNONCE10 0x24A
#define UPNONCE11 0x24B
#define UPNONCE12 0x24C


/************PORTF & PORTC to Zigbee***********/
#define RST 	RST_PORT      // RESET FOR ZIGBEE(OUTPUT)
#define WAKE	WAKE_PORT    // WAKE UP FOR ZIGBEE (OUTPUT)
#define CLK		PORTCbits.RC3 // CLOCK FOR ZIGBEE (OUTPUT)
#define D_IN	PORTCbits.RC4 // DATA  FROM ZIGBEE (INPUT)
#define D_OUT	PORTCbits.RC5 // DATA  OUT FOR ZIGBEE (OUTPUT)
#define INTQ	PORTCbits.RC2  // INTTRUPPT FROM ZEGBEE (INPUT)
#define CS      CS_PORT  // CHIP SELECT FOR ZIGBEE

#define NUM 3
#define DEBOUNCETIME 10
#define LED1   LED1_PORT
#define LED2   LED2_PORT
#define LED3   LED3_PORT
#define LED4   LED4_PORT
#define RELAY  RELAY_PORT
#define BUZZER  BUZZER_PORT 

unsigned char INTTRUPT;
unsigned char Count1,Count2;
unsigned char LENGTH;
unsigned char CHECK;
unsigned char DATA;
unsigned char data_r;
unsigned char DATA_TX[NUM];
unsigned char LQI = 0, RSSI2 = 0, SEQ_NUMBER = 0x23; 
unsigned char DATA_RX[NUM+2], data_TX_normal_FIFO[(NUM+2) +11 + 2];
unsigned char data_RX_FIFO[1 + 11+ (NUM+2) + 2 + 1 + 1], lost_data = 0;

unsigned int address_RX_FIFO = 0x300; 
unsigned int address_TX_normal_FIFO = 0x000; 
const unsigned char DATA_LENGHT =  NUM+2;
const unsigned char HEADER_LENGHT = 11; 
     
unsigned char ADDRESS_short_1[] = {1,1};
unsigned char ADDRESS_long_1[]  = {1,1,1,1,1,1,1,1}; 
unsigned char ADDRESS_short_2[] = {2,2};               // Destination address 
unsigned char ADDRESS_long_2[]  = {2,2,2,2,2,2,2,2}; 

unsigned char PAN_ID_1[] = {3,3};                      // Source PAN ID 
unsigned char PAN_ID_2[] = {3,3}; 

unsigned char Device_ID=0,T_Input=0,F_Input=0;

unsigned char Portread=0,InputRead=0;
unsigned char F_IdSet=0;
#define PAN_Coordinatior
//#define Coordinatior

unsigned char i,ii,d;

unsigned int Rv_CRC=0,TX_CRC=0;
unsigned short CRC=0;
unsigned char Store_DATA[4],Store=0;


#ifdef PAN_Coordinatior
#define PAN_ID 0x2525
#define Short_Add 0x1200
//#define Long_Add 0x0000000025251212
#endif


#ifdef Coordinatior
#define PAN_ID 0x2525
#define Short_Add 0x1200
//#define Long_Add 0x0000000025251212
#endif

char slave_add;
unsigned char ERROR=0,F_ERROR,Count_LED,T=0;
unsigned int T_ERROR=0;
unsigned char F_SetID=0,ID_SET=0, T_ID_Send=0,TX_ID=0,Tick=0,Trick=0;
char i,value,VALUE;
char address;
unsigned int ckeck=0;
unsigned char Nilp=0;
unsigned char ID_READ=0,F_ID_Send=0,F_BUZZER=0, T_BUZZER=0,F_ID_SEND=0,Send_Frame=0,Send_Frame_2=0;


void Clear_Data(void);

void pin_reset(void) ;
void RF_reset(void);
void set_WAKE_from_pin(void);
void set_long_address(unsigned char * address);
void set_short_address(unsigned char * address);
void set_PAN_ID(unsigned char * address);
void init_ZIGBEE_nonbeacon(void);
void init_ZIGBEE_basic(void);
void set_CCA_mode(unsigned char CCA_mode);
void set_RSSI_mode(unsigned char RSSI_mode);
void enable_interrupt(void);
void set_channel(unsigned char channel_number);
void pin_wake(void);
void nonbeacon_PAN_coordinator_device(void);
void nonbeacon_coordinator_device(void);
void set_TX_power(unsigned char power);
void set_frame_format_filter(unsigned char fff_mode);
void set_reception_mode(unsigned char r_mode);
void read_RX_FIFO(void);

void set_not_ACK(void);
void set_not_encrypt(void);
void start_transmit(void);


void write_ZIGBEE_short(unsigned char address, unsigned char data_r);
unsigned char read_ZIGBEE_short(unsigned char address) ;
void write_ZIGBEE_long(unsigned int address, unsigned char data_r);
unsigned char read_ZIGBEE_long(unsigned int address);

void Read_long_address(unsigned char * address);

void delay(unsigned int dly);
void Delay_ms(unsigned int time);
void Delayms(unsigned int time);
void Delayms1(unsigned int time);
void InitSPI(void);
void SPI_Write( unsigned char command);
unsigned char SPI_Read( void );


void Scanoutput();


void SoftWareReste(void);
void PWR_reset(void);
void BB_reset(void);
void MAC_reset(void);
void software_reset(void);

void nonbeacon_device(void);
void set_ACK(void);

void set_encrypt(void);


void set_IFS_recomended(void);
void set_IFS_default(void);


void   flush_RX_FIFO_pointer(void);
void read_RX_FIFO(void);
void write_TX_normal_FIFO(void);




void pin_wake(void) ;
void enable_PLL(void);
void disable_PLL(void);


unsigned short Xor_check(unsigned char *data_value, unsigned char length);
void ScanInput(void);
void initialWireless(void);
void ZigBee_Transmit_Frame ( char *ucharpointerDataFrame,  char ucharLengthOfDataFrame,  int uintDestinationShortAdd, char ucharSequenceNo);
void ZigBee_Initialise (void);
void InitMRF24J40(void);
void InitMRF24J402(void);