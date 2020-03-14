/**
  Generated Main Source File

  Company:
    Microchip Technology Inc.

  File Name:
    main.c

  Summary:
    This is the main file generated using PIC10 / PIC12 / PIC16 / PIC18 MCUs

  Description:
    This header file provides implementations for driver APIs for all modules selected in the GUI.
    Generation Information :
        Product Revision  :  PIC10 / PIC12 / PIC16 / PIC18 MCUs - 1.65
        Device            :  PIC18F67K22
        Driver Version    :  2.00
*/

/*
    (c) 2016 Microchip Technology Inc. and its subsidiaries. You may use this
    software and any derivatives exclusively with Microchip products.

    THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER
    EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY IMPLIED
    WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS FOR A
    PARTICULAR PURPOSE, OR ITS INTERACTION WITH MICROCHIP PRODUCTS, COMBINATION
    WITH ANY OTHER PRODUCTS, OR USE IN ANY APPLICATION.

    IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE,
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND
    WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS
    BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO THE
    FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS IN
    ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF ANY,
    THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.

    MICROCHIP PROVIDES THIS SOFTWARE CONDITIONALLY UPON YOUR ACCEPTANCE OF THESE
    TERMS.
*/

#include "mcc_generated_files/mcc.h"
#include "zigbee.h"

#define RS   RS_PORT
#define RW   RW_PORT
#define EN   EN_PORT
#define LINE1    0x80  // FIRST LINE FOR LCD DISPLAY
#define LINE2	 0xC0  // SECOND LINE FOR LCD DISPLAY
#define BUSY 		PORTEbits.RE7	//Busy check.
unsigned char RECEIVE_OK=0;
unsigned char id=0;
unsigned char RxBuffer[100];
unsigned char i=0;
unsigned char Sent_sms=0;
unsigned char RXcounter=0,WaitForReceive=0,F_WaitForReceive=0,Chksum=0;

//*****sms variable**********//
const unsigned char ATCheck[3]={'A','T',0x0D};
const unsigned char Set_Responce[5]={'A','T','V','1',0x0D};
const unsigned char echo_off[6]={'A','T','E','0',0x0D};
const unsigned char Enable_Result_Code[10]={'A','T','+','C','M','E','E','=','2',0x0D};
const unsigned char Get_Baud[8]={'A','T','+','I','P','R','?',0x0D};
const unsigned char Manufacturer_Id[4]={'A','T','I',0x0D};
const unsigned char IMEI[7]={'A','T','+','G','S','N',0x0D};
const unsigned char Sim_Status[9]={'A','T','+','C','P','I','N','?',0x0D};
const unsigned char Delet_All_SMS[12]={'A','T','+','C','M','G','D','=','1',0x2C,'4',0x0D};
const unsigned char SMSread[10]={'A','T','+','C','M','G','R','=','1',0X0D};

unsigned char SMS_format[10]={'A','T','+','C','M','G','F','=','1',0x0D};
//unsigned char SET_CHAR[10]={'C','S','C','S','=','"','G','S','M','"'};
unsigned char SEND_SMS[21]={'A','T','+','C','M','G','S','=','"','9','4','2','7','8','5','2','0','2','5','"',0x0D};
unsigned char msg[6]={'H','e','l','l','o',0x0D};
unsigned char Emeregency[21]={'I','D',' ',0x00,' ','i','s',' ','i','n',' ','E','m','e','r','g','e','n','c','y',0x0D};
unsigned char Emeregency2[22]={'I','D',' ',0x00,0x00,' ','i','s',' ','i','n',' ','E','m','e','r','g','e','n','c','y',0x0D};
unsigned char Emeregency3[23]={'I','D',' ',0x00,0x00,0x00,' ','i','s',' ','i','n',' ','E','m','e','r','g','e','n','c','y',0x0D};
unsigned char send[2]={0x1A,0x0D};
unsigned char SMSsender[13];

unsigned char Number[15]={'A','T','D','9','4','2','7','8','5','2','0','2','5',';',0x0D};
unsigned char Call[6]={'A','T','C','L','C',0x0D};
unsigned char Call_Cut[4]={'A','T','H',0x0D};
unsigned char Device_ID,IDByte1=0,IDByte2=0,IDByte3=0,V_Temp=0,ds=0;


void SerInit(void);
void Sprint(unsigned char *datas,unsigned char length);
void SprintRom(const unsigned char *datas,unsigned char length);
void ClearRxBytes(void);
void Module_Init(void);
void Calling(void);
void Message_Send_Frame_1(void);
void Message_Send_Frame_2(void);
void Message_Send_Frame_3(void);
void lcd_stop_scroll(void);			//To stop lcd scrolling.
void lcd_scroll(void);				//To start lcd scrolling.
void lcd_off_cursor(void);			//To off lcd cursor.	
void lcd_on_cursor(void);			//To on lcd cursor.
void lcd_off_blinkcursor(void);		//To off lcd cursor blinking.
void lcd_on_blinkcursor(void);		//To on lcd cursor blinking.
void LcdData(char value);		    //To display data on lcd.
void LcdCmd(char value);			//To give commands to lcd.
void lcd_clear();					//To clear lcd data/screen.
void LcdInit(void);				    //To init lcd.
void LcdReady(void);
void LcdDisplay(unsigned char LINE,const unsigned char *string);
void Clear_ReceiveBytes(void);
void DeleteAllSms(void);
//void Delaysec(unsigned char i);



void interrupt INTERRUPT_InterruptManagerHigh (void)
{
   // interrupt handler
    if(INTCONbits.INT0IE == 1 && INTCONbits.INT0IF == 1)
    {
       INTTRUPT=read_ZIGBEE_short(0X31);
        //INTCONbits.GIE=1;
        if((INTTRUPT & 0x08)==0x08){
               INTCONbits.GIE=0;
               read_RX_FIFO();
               INTCONbits.GIE=1;
               CRC=Xor_check(DATA_RX,NUM);
   			   Rv_CRC=(((unsigned int)DATA_RX[NUM+1]<<8) | DATA_RX[NUM+0]);
                if((CRC==Rv_CRC) && (DATA_RX[0]=='#')){
            Store_DATA[0]=DATA_RX[1];
            Clear_Data(); 
            if(Read_b_eep(Store_DATA[0]) == Store_DATA[0]){
               LED1=0;
                data_TX_normal_FIFO[13]='#';
	 	        data_TX_normal_FIFO[14]='E';
		       // write_TX_normal_FIFO(); 
                Send_Frame=1;
                Delay_ms(50);
               LED1=1;
            }
            else{
                Write_b_eep(Store_DATA[0],Store_DATA[0]);
                LED2=0;
                data_TX_normal_FIFO[13]='#';
                data_TX_normal_FIFO[14]='O';
                Send_Frame_2=1;
               // write_TX_normal_FIFO();
                Delay_ms(50);
                LED2=1;
            }
            
            if(Send_Frame==1){
               Send_Frame=0;
               write_TX_normal_FIFO();
            }
            if(Send_Frame_2==1){
               Send_Frame_2=0;
               write_TX_normal_FIFO();
            }
        }
        
        
              
        }
       
        INT0_ISR();
    }
    else if(PIE1bits.RC1IE == 1 && PIR1bits.RC1IF == 1)
    {
      
        RxBuffer[id] = RCREG;                //receive the id serially at RCREG
	        	if((RxBuffer[0] == '$') && (ds != 5)){
		        	id++;
		        	if(id>50){
		        		WaitForReceive = 0;
		        	}
		        }
		        if(ds == 10){
			        id++;
			        if(id>RXcounter){
			        	WaitForReceive = 0;
			        }
		        }
        if((RxBuffer[3] == 'C') && (RxBuffer[4] == 'M')){
            F_WaitForReceive=1;
        }
		    PIR1bits.RCIF=0;   
    }
}

void interrupt low_priority INTERRUPT_InterruptManagerLow (void)
{
    // interrupt handler
    if(INTCONbits.TMR0IE == 1 && INTCONbits.TMR0IF == 1)
    {
         Nilp++;
        if(Nilp>=200){
            Nilp=0;
            LED4=~LED4;
        }
        TMR0_ISR();
    }
    else
    {
        //Unhandled Interrupt
    }
}
void main(void)
{
    // Initialize the device
    SYSTEM_Initialize();
    INTERRUPT_GlobalInterruptHighEnable();
    INTERRUPT_GlobalInterruptLowEnable();
    INTERRUPT_PeripheralInterruptEnable();
    Delay_ms(10);
	InitSPI();
	Delay_ms(10);
    SerInit();
	pin_reset();                            // Activate reset from pin 
    RF_reset();                             // RF reset 	
 	set_WAKE_from_pin(); 					// Set wake from pin 
	
  	set_long_address(ADDRESS_long_2);       // Set long address 
  	set_short_address(ADDRESS_short_2);     // Set short address 
  	set_PAN_ID(PAN_ID_2);                   // Set PAN_ID 
  	//DATA_RX[0]=read_ZIGBEE_short(PANIDL);
  	init_ZIGBEE_nonbeacon();				// Initialize ZigBee module
  	         
  	nonbeacon_PAN_coordinator_device(); 
 	set_TX_power(31);                       // Set max TX power 
  	set_frame_format_filter(1);             // 1 all frames, 3 data frame only 
  	set_reception_mode(1); 
  	pin_wake();
    ds = 10;
    Module_Init();
    Delay_ms(10);
    LcdInit();
    Delay_ms(10);
    Count1=1;
 	Count2=1;
    ID_SET=1;
    Clear_ReceiveBytes();
    
    lcd_off_cursor();
	lcd_clear();
	LcdDisplay(LINE1,"    philbrick     ");
    LcdDisplay(LINE2,"  Technologies    ");
    Delayms(300);Delayms(300);Delayms(300);Delayms(300);
    while(1){
        LcdDisplay(LINE1,"Waiting for SMS    ");
        LcdDisplay(LINE2,"                   ");
		ClearRxBytes();
		WaitForReceive = 1;	
		id=0;
		RXcounter = 16;
		Delayms(1);
        if(F_WaitForReceive == 1){
            F_WaitForReceive=0;
            lcd_clear();
            LcdDisplay(LINE1,"One New Message    ");
            Delayms(300);Delayms(300);Delayms(300);Delayms(300);
            Delayms(300);Delayms(300);Delayms(300);Delayms(300);
          /*
            for(i=0;i<11;i++){
			    SMSsender[i]=SMSread[i];
		    }
            SMSsender[8]=RxBuffer[14];	
            ClearRxBytes();
            WaitForReceive = 1;	
            id=0;
            RXcounter = 88;
            Delayms(1);
            Sprint(&SMSread,13);	
            while(WaitForReceive);
          */
            Nop( );
            Nop( );
        }
       
        if((CRC==Rv_CRC) && (DATA_RX[0]=='$')){
            Store_DATA[0]=DATA_RX[1];
            Store_DATA[1]=DATA_RX[2];
            Clear_Data();
            if(Store_DATA[1]=='C'){
                if(Store_DATA[0]<10 && Store_DATA[0]>=1){
                   Store_DATA[0]+=0x30;
                   Emeregency[3]=Store_DATA[0];
                   Message_Send_Frame_1();
                   lcd_clear();
                   LcdDisplay(LINE1,"  ID    is in ");
                   LcdCmd(0x85);
                   LcdData(Emeregency[3]);
                   LcdDisplay(LINE2,"   Emergency  ");
                   Delayms(300);Delayms(300);Delayms(300);Delayms(300);
                }
                else if(Store_DATA[0]>=10 && Store_DATA[0]<100){
                    IDByte1=Store_DATA[0] / 10;
                    IDByte2=Store_DATA[0] % 10;
                    Emeregency2[3]=IDByte1 + 0x30;
                    Emeregency2[4]=IDByte2 + 0x30;
                    Message_Send_Frame_2();
                    lcd_clear();
                    LcdDisplay(LINE1,"  ID    is in ");
                    LcdCmd(0x85);
                    LcdData(Emeregency2[3]);
                    LcdCmd(0x86);
                    LcdData(Emeregency2[4]);
                    LcdDisplay(LINE2,"   Emergency  ");
                    Delayms(300);Delayms(300);Delayms(300);Delayms(300);
                }
                else if(Store_DATA[0]>=100 && Store_DATA[0]<=255){
                    IDByte3=Store_DATA[0] / 100;
                    V_Temp =Store_DATA[0] % 100;
                    IDByte2=V_Temp/10;
			        IDByte1=V_Temp%10;
                    Emeregency3[3]=IDByte3 + 0x30;
                    Emeregency3[4]=IDByte2 + 0x30;
                    Emeregency3[5]=IDByte1 + 0x30;
                    Message_Send_Frame_3();
                    lcd_clear();
                    LcdDisplay(LINE1,"  ID     is in ");
                    LcdCmd(0x85);
                    LcdData(Emeregency3[3]);
                    LcdCmd(0x86);
                    LcdData(Emeregency3[4]);
                    LcdCmd(0x87);
                    LcdData(Emeregency3[5]);
                    LcdDisplay(LINE2,"   Emergency  ");
                    Delayms(300);Delayms(300);Delayms(300);Delayms(300);
                    
                }
               
            }   
             
        }
    }
/*
    while (1)
    {
        data_TX_normal_FIFO[13]='#';
	 	data_TX_normal_FIFO[14]='P';
		data_TX_normal_FIFO[15]='Q';
		write_TX_normal_FIFO();
		Nop();
		Count2=~Count2;
	    PORTAbits.RA0=Count2;
	    Delay_ms(10);
	    Delay_ms(10);
	    Delay_ms(10);
	    Delay_ms(10);
        if((RECEIVE_OK==1) && (DATA_RX[0]=='#')){
            RECEIVE_OK=0;
            Clear_Data(); 
            LED4=~LED4;
            Delay_ms(10);
	        Delay_ms(10);
	        Delay_ms(10);
	        Delay_ms(10);
        }
       
    }
*/
    
}
void SerInit(void){
	
	SPBRG=20;                                  //value 64,
	TXSTAbits.BRGH=1;
	Nop( );Nop( );Nop( );
	TXSTAbits.SYNC=0;
 	Nop( );Nop( );Nop( );
    TXSTAbits.TX9=0;
	Nop( );Nop( );Nop( );
 	RCSTAbits.SPEN=1;
 	Nop( );Nop( );Nop( );
 	RCSTAbits.CREN=1;   
 	Nop( );Nop( );Nop( );
 	TXSTAbits.TXEN=1;
    Nop( );Nop( );Nop( ); 	
 	PIE1bits.TXIE=0;    
 	Nop( );Nop( );Nop( );
 	PIE1bits.RCIE=1;    
 	Nop( );Nop( );Nop( );
 	INTCONbits.GIE=1;   
 	Nop( );Nop( );Nop( );
 	INTCONbits.PEIE=1;
 	Nop( );Nop( );Nop( );
 	TRISCbits.TRISC7=1;             			 //RX
 	Nop( );Nop( );Nop( );
 	TRISCbits.TRISC6=0;			                 //TX
 	Nop( );Nop( );Nop( );
}
void Sprint(unsigned char *datas,unsigned char length){

        unsigned char i=0,j=0;

        for(i=0;i<length;i++){
                TXREG = datas[i];
                while(PIR1bits.TXIF == 0);
                Delayms(50);
        }

}
void SprintRom(const unsigned char *datas,unsigned char length){
		
       unsigned char i=0,j=0;

        for(i=0;i<length;i++){
	        	//PIR1bits.TXIF = 0;
                TXREG = datas[i];
                while(PIR1bits.TXIF == 0);
                Delayms(50);
        }

}
void ClearRxBytes(void){

        unsigned char i=0;

        for(i=0;i<100;i++){
                        RxBuffer[i] = 0xFF;
        }
}
void Module_Init(void){
    /*
    SprintRom(&ATCheck,3);
    Delayms(2);
    SprintRom(&Set_Responce,5);
    Delayms(2);
    SprintRom(&echo_off,6);
    Delayms(2);
    SprintRom(&Enable_Result_Code,10);
    Delayms(2);
    SprintRom(&Get_Baud,8);
    Delayms(2);
    SprintRom(&Manufacturer_Id,4);
    Delayms(2);
    SprintRom(&IMEI,7);
    Delayms(2);
    SprintRom(&Sim_Status,9);
    Delayms(2);
    SprintRom(&Delet_All_SMS,12);
    */

	
	ClearRxBytes();
    WaitForReceive = 1;	
	id=0;
	RXcounter = 5;
	SprintRom(&ATCheck,3);
	while(WaitForReceive);
    Nop();
    ClearRxBytes();
    DeleteAllSms();	
    lcd_clear();
}
void DeleteAllSms(void){

lcd_clear();
LcdDisplay(LINE2,"Deleting SMS    ");	
		    WaitForReceive = 1;	
			id=0;
			ClearRxBytes();
			RXcounter = 5;
			SprintRom(&Delet_All_SMS,12);	
			while(WaitForReceive);
			Delayms(300);
			Delayms(1);
		    ClearRxBytes();
		    LcdDisplay(LINE2,"All SMS deleted ");
		    Delayms(300);Delayms(300);Delayms(300);Delayms(300);
		    lcd_clear();
		    //LcdDisplay(LINE1,"Waiting For SMS");
		
}
void Calling(void){
     Delayms(2);
     Sprint(&Number,15);
     Delayms(2);
     Sprint(&Call,6);
     Delayms(2);
}
void Message_Send_Frame_1(void){
     Delayms(2); 
     Sprint(&SMS_format,10);
     Delayms(2);
     Sprint(&SEND_SMS,21);
     Delayms(2);
     Sprint(&Emeregency,21);
     Delayms(2);
     Sprint(&send,3);
     Delayms(2);
}
void Message_Send_Frame_2(void){
     Delayms(2);
     Sprint(&SMS_format,10);
     Delayms(2);
     Sprint(&SEND_SMS,21);
     Delayms(2);
     Sprint(&Emeregency2,22);
     Delayms(2);
     Sprint(&send,3);
     Delayms(2);
}
void Message_Send_Frame_3(void){
     Delayms(2);
     Sprint(&SMS_format,10);
     Delayms(2);
     Sprint(&SEND_SMS,21);
     Delayms(2);
     Sprint(&Emeregency3,23);
     Delayms(2);
     Sprint(&send,3);
     Delayms(2);
}
/********************************************************************
                        LCD INITILIZATION 
*********************************************************************/
void scroll()
{
	LcdCmd(0x07);
}

void stop_scroll()
{
	LcdCmd(0x04);
	Delayms(10);
	LcdCmd(0x01);
}

void lcd_off_cursor(void)
{
	LcdCmd(0x0C);	
}

void lcd_on_cursor(void)
{
	LcdCmd(0x0E);	
}
void LcdData(char value)
{
   PORTE=value;   
   RS=1;
   Nop();
   EN=1;
   Delayms(5);
   EN=0;
}
void LcdCmd(char value)
{
   PORTE=value;   
   RS=0;
   Nop();
   EN=1;
   Delayms(5);
   EN=0;
}

void lcd_clear()
{
	LcdCmd(0x01);	
}

void LcdInit(void)
{
   LcdCmd(0x38);
   Delayms(10);
   LcdCmd(0x0E);
   Delayms(10);
   LcdCmd(0x01);
   Delayms(10);
   LcdCmd(0x80);
   Delayms(10);
}

void LcdReady(void){
   
   PORTE=0X00;     
   TRISE=0XFF;   
   RS=0;
   RW=1;
   while(BUSY==1)
	{
      EN=0;
      Delayms(10);
      EN=1;
   	}
   PORTE=0X00;
   TRISE=0X00;
}

void LcdDisplay(unsigned char LINE,const unsigned char *string)
{
	unsigned char data;
	LcdCmd(LINE);
	
	while(*string != '\0')
   {
	   	LcdData(*string);
    	string++;
   } 
}
void Clear_ReceiveBytes(void){

        unsigned char i=0;

        for(i=0;i<30;i++){
            RxBuffer[i] = 0xFF;
        }
}


