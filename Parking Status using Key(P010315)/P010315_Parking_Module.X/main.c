
#include "mcc_generated_files/mcc.h"
#include "zigbee.h"

#define KEY1   KEY1_PORT
#define KEY2   KEY2_PORT
#define KEY3   KEY3_PORT
#define KEY4   KEY4_PORT


#define KEY1_ID   1
#define KEY2_ID   2
#define KEY3_ID   3
#define KEY4_ID   4


unsigned char tick=0;
unsigned char T_KEY1=0,T_KEY2=0,T_KEY3=0,T_KEY4=0;
unsigned char F_KEY1=0,F_KEY2=0,F_KEY3=0,F_KEY4=0;
unsigned char F_Send_Frame1=0;
unsigned char ZigBee_Receive_Buffer[6];

void ScanInput(void);
void Zigbee_data_Store_Buffer(void);


void interrupt INTERRUPT_InterruptManagerHigh (void)
{
   // interrupt handler
    if(INTCONbits.INT0IE == 1 && INTCONbits.INT0IF == 1)
    {
         INTTRUPT=read_ZIGBEE_short(0X31);
        //INTCONbits.GIE=1;
        if((INTTRUPT & 0x08)==0x08)     //Receive Frame From ZigBee Module 
        {
            INTCONbits.GIE=0;
            read_RX_FIFO();
            INTCONbits.GIE=1;
            CRC=Xor_check(DATA_RX,NUM);
            Rv_CRC=(((unsigned int)DATA_RX[NUM+1]<<8) | DATA_RX[NUM+0]);
            Zigbee_data_Store_Buffer();   
        }   
        INT0_ISR();
    }
    else
    {
        //Unhandled Interrupt
    }
}

void interrupt low_priority INTERRUPT_InterruptManagerLow (void)
{
    // interrupt handler
    if(INTCONbits.TMR0IE == 1 && INTCONbits.TMR0IF == 1)
    {
        tick++;
        if( tick > 20 ){
			ScanInput();
			tick = 0;
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

    Delay_ms(100);Delay_ms(100);
    Delay_ms(100);Delay_ms(100);
    SYSTEM_Initialize();                    // Initialization MCU related I/O and Other Functions
    InitSPI();                              // Initialization for SPI Communication
	Delay_ms(10);
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
    Count1=1;
 	Count2=1;
 	Delay_ms(10);
    ID_SET=1;
    INTERRUPT_GlobalInterruptHighEnable();
    INTERRUPT_GlobalInterruptLowEnable();
    INTERRUPT_PeripheralInterruptEnable();
    LED1=1;
    while (1)
    {
        
        if( CRC == Rv_CRC ){
            Clear_Data();
            if((ZigBee_Receive_Buffer[0]=='*') && (F_KEY1==1)){
                
                LED1=1;
                data_TX_normal_FIFO[13]='*';
                data_TX_normal_FIFO[14]=KEY1_ID;
		        data_TX_normal_FIFO[15]=1;
		        write_TX_normal_FIFO();
            }
            else if((ZigBee_Receive_Buffer[0]=='*') && (F_KEY2==1)){
                
                LED1=1;
                data_TX_normal_FIFO[13]='*';
                data_TX_normal_FIFO[14]=KEY2_ID;
		        data_TX_normal_FIFO[15]=1;
		        write_TX_normal_FIFO();
            }
            else if((ZigBee_Receive_Buffer[0]=='*') && (F_KEY3==1)){
                
                LED1=1;
                data_TX_normal_FIFO[13]='*';
                data_TX_normal_FIFO[14]=KEY3_ID;
		        data_TX_normal_FIFO[15]=1;
		        write_TX_normal_FIFO();
            }
            else if((ZigBee_Receive_Buffer[0]=='*') && (F_KEY4==1)){
                
                LED1=1;
                data_TX_normal_FIFO[13]='*';
                data_TX_normal_FIFO[14]=KEY4_ID;
		        data_TX_normal_FIFO[15]=1;
		        write_TX_normal_FIFO();
            }
            else{
                LED1=0;
            }
        /*data_TX_normal_FIFO[13]='#';
	 	data_TX_normal_FIFO[14]='P';
		data_TX_normal_FIFO[15]='Q';
		write_TX_normal_FIFO();
		Nop();
		Count2=~Count2;
	    LED1=Count2;
	    Delay_ms(10);
	    Delay_ms(10);
	    Delay_ms(10);
	    Delay_ms(10);
         */
        } 
    }
}
void ScanInput(void){
    unsigned char  portread=0;
    
    portread = PORTA;
    
    if((portread & 0x01)!=0){
        T_KEY1=0;
        F_KEY1=0;
    }
    else if(F_KEY1!= 2){
        T_KEY1++;
    }
    
    if((portread & 0x02)!=0){
        T_KEY2=0;
        F_KEY2=0;
    }
    else if(F_KEY2!= 2){
        T_KEY2++;
    }
    
    if((portread & 0x04)!=0){
        T_KEY3=0;
        F_KEY3=0;
    }
    else if(F_KEY3!= 2){
        T_KEY3++;
    }
    
    if((portread & 0x08)!=0){
        T_KEY4=0;
        F_KEY4=0;
    }
    else if(F_KEY4!= 2){
        T_KEY4++;
    }
    
    
    
    if(T_KEY1 > DEBOUNCETIME){
	   F_KEY1 = 1;
	   T_KEY1 = 0;
	}
    if(T_KEY2 > DEBOUNCETIME){
	   F_KEY2 = 1;
	   T_KEY2 = 0;
	}
    if(T_KEY3 > DEBOUNCETIME){
	   F_KEY3 = 1;
	   T_KEY3 = 0;
	}
    if(T_KEY4 > DEBOUNCETIME){
	   F_KEY4 = 1;
	   T_KEY4 = 0;
	}
    
    
}
void Zigbee_data_Store_Buffer(void){
     
    unsigned char a;
    for(a=0;a<=5;a++){
        ZigBee_Receive_Buffer[a] = DATA_RX[a];
    }
    
}
