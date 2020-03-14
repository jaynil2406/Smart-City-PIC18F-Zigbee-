/*
 * File:   13_March_2018Main.c
 * Author: DiXiT Patel
 *
 * Created on 13 March, 2018, 1:35 PM
 *  Summary:
    This is the main file generated using PIC10 / PIC12 / PIC16 / PIC18 MCUs

    Description:
    This header file provides implementations for driver APIs for all modules selected in the GUI.
    Generation Information :
        Product Revision  :  PIC10 / PIC12 / PIC16 / PIC18 MCUs - 1.65
        Device            :  PIC18F67K22
        Driver Version    :  2.00
 */

#include "mcc_generated_files/mcc.h"
#include "zigbee.h"

#define ID_STORE_LOCATION   0x02
#define PREVEOS_STATUS_STORE_LOCATION 0x05
unsigned char  RECEIVE_OK=0,F_Buzzer=0,portread=0,tick=0,tick2=0;
unsigned char T_Calling,F_Calling;

#define MOTION PORTFbits.RF3
#define OFF_Light  1
unsigned char ALT_ON=0,F_MSG=0,Previous_Status=0,ID_READ_Store=0,F_LDR_STATUS=0;
unsigned int Time_start=0;
long signed int Delta=0;
unsigned int Value_LDR=0;

unsigned long Light=0;
float VoltageOutput=0,ResistanceLDR=0;
const float AdcRef=8.056640625e-4,R3=10e3,Vcc=3.3,Resistance0=990e3;

void ScanInput(void);


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
        Time_start++;
        if( tick > 20 ){
			ScanInput();
			tick = 0;
		}
        if(F_BUZZER==1){
            tick2++;
            ALARM=1;
            if(tick2>200){
               tick2=0;
               F_BUZZER=0;
               ALARM=0;
               Nop();
            }
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
    Delay_ms(100);Delay_ms(100);
    Delay_ms(100);Delay_ms(100);
    SYSTEM_Initialize();
    Delay_ms(10);
	InitSPI();
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
    Delay_ms(100);
    ID_READ=PORTD;
    Previous_Status=Read_b_eep(PREVEOS_STATUS_STORE_LOCATION);
    ID_READ_Store=Read_b_eep(ID_STORE_LOCATION);
    if(ID_READ_Store == ID_READ ){
        if(Previous_Status == 1){
           F_MSG=1;
        }
        else if(Previous_Status == 2){
            F_MSG=2;
        }
        else if(Previous_Status == 3){
            F_MSG=3;
        }
        else{
            F_MSG=0;
        }
    }else{
        Write_b_eep(PREVEOS_STATUS_STORE_LOCATION,0xFF);
        ID_READ_Store=0;
        Previous_Status=0;
    }
   /*
    while(1){
        
        LED1=1;
        RELAY=0;
        Delay_ms(1000);Delay_ms(1000);Delay_ms(100);
        Delay_ms(1000);Delay_ms(1000);Delay_ms(1000);
       // LED1=0;
       // RELAY=1;
        Delay_ms(1000);Delay_ms(1000);Delay_ms(1000);
        Delay_ms(1000);Delay_ms(1000);Delay_ms(1000);
        Delay_ms(1000);Delay_ms(1000);Delay_ms(1000);
        Delay_ms(1000);Delay_ms(1000);Delay_ms(1000);
         Value_LDR=ADC_GetConversion(6);
         VoltageOutput=((float) Value_LDR) * AdcRef;
         ResistanceLDR = (VoltageOutput * R3)/(Vcc - VoltageOutput);
         Light = (unsigned long)((100 - ((ResistanceLDR / Resistance0)*100)) * 1000);
         Delta= Light - OFF_Light;
         Delta=Delta/1000;
         Nop();
    }
    */
    while(1){
        if(ID_SET == 1){
                LED1=0;
                ID_SET=0;
                ID_READ=PORTD;
                Write_b_eep(ID_STORE_LOCATION,ID_READ);
                Write_b_eep(ID_STORE_LOCATION,ID_READ);
                data_TX_normal_FIFO[13]='#';
                data_TX_normal_FIFO[14]=ID_READ;
                write_TX_normal_FIFO();
                LED1=1;
                Delay_ms(20);Delay_ms(20);
        }

        if((CRC == Rv_CRC) && (DATA_RX[0]=='#') ){
            if(DATA_RX[1]=='O'){
                LED3=0;
                Delay_ms(100);Delay_ms(100);Delay_ms(100);
                LED3=1;
            }
            else if(DATA_RX[1]=='E'){
                LED4=0;
                Delay_ms(100);Delay_ms(100);Delay_ms(100);
                LED4=1;
            }
             Clear_Data(); 
        }
        if((CRC == Rv_CRC) && (DATA_RX[0]=='$') ){
            if((DATA_RX[1]=='M') && (DATA_RX[2]=='1')){
               F_MSG=1;
               Write_b_eep(PREVEOS_STATUS_STORE_LOCATION,F_MSG);
            }
            else if((DATA_RX[1]=='M') && (DATA_RX[2]=='2')){
               F_MSG=2; 
               Write_b_eep(PREVEOS_STATUS_STORE_LOCATION,F_MSG);
            }
             else if((DATA_RX[1]=='M') && (DATA_RX[2]=='3')){
                F_MSG=3;  
                Write_b_eep(PREVEOS_STATUS_STORE_LOCATION,F_MSG);
            }
             else if(DATA_RX[1]=='L'){
                  
                 if(DATA_RX[2]==ID_READ){
                   LED1=1;
	 	           RELAY=0;
                   Delay_ms(1000);Delay_ms(1000);Delay_ms(100);
                   Delay_ms(1000);Delay_ms(1000);Delay_ms(1000);
                   LED1=0;
	 	           RELAY=1;
                   Delay_ms(1000);Delay_ms(1000);Delay_ms(1000);
                   Delay_ms(1000);Delay_ms(1000);Delay_ms(1000);
                   Delay_ms(1000);Delay_ms(1000);Delay_ms(1000);
                   Delay_ms(1000);Delay_ms(1000);Delay_ms(1000);
                   Delay_ms(1000);Delay_ms(1000);Delay_ms(1000);
                   Delay_ms(1000);Delay_ms(1000);Delay_ms(1000);
                   Delay_ms(1000);Delay_ms(1000);Delay_ms(1000);
                   Delay_ms(1000);Delay_ms(1000);Delay_ms(1000);
                    Value_LDR=ADC_GetConversion(6);
                    VoltageOutput=((float) Value_LDR) * AdcRef;
                    ResistanceLDR = (VoltageOutput * R3)/(Vcc - VoltageOutput);
                    Light = (unsigned long)((100 - ((ResistanceLDR / Resistance0)*100)) * 1000);
                    Delta= Light - OFF_Light;
                    Delta=Delta/1000;
                   // Delay_ms(1000);Delay_ms(1000);Delay_ms(1000);
                   // Delay_ms(1000);Delay_ms(1000);Delay_ms(1000);
                    LED1=1;
	 	            RELAY=0;
                    LED4=0;
                    F_LDR_STATUS=1;
                 }
             }
             Clear_Data(); 
        }
        if(F_Calling == 1){
           F_Calling=0;
           F_BUZZER=1;
           ID_READ=Read_b_eep(ID_STORE_LOCATION);
           data_TX_normal_FIFO[13]='$';
           data_TX_normal_FIFO[14]=ID_READ;
           data_TX_normal_FIFO[15]='C';
           write_TX_normal_FIFO();
            Nop();
            Nop();
        }
        if( F_MSG==1){
             LED1=0;
             RELAY=1;
             F_MSG=0;
             ALT_ON=0;
        }
        else if( F_MSG==2){
             LED1=1;
	 	     RELAY=0;
             F_MSG=0;
             ALT_ON=0;
        }
        else if( F_MSG==3){
            if((ID_READ%2)==0){
                 LED1=0;
                 RELAY=1;
                 ALT_ON=0;
            }
            else{
                ALT_ON=1;
            }
           F_MSG=0;  
        }
        
        
        if((ALT_ON==1)&&(MOTION==1)){
             LED1=0;
             RELAY=1;
             Time_start=0;
        }
        
        if((ALT_ON==1)&&(MOTION==0)){
             if(Time_start>1000){
                LED1=1;
	 	        RELAY=0;  
                Time_start=0;
             }
        }
        if(F_LDR_STATUS==1){
           F_LDR_STATUS=0;
           if(Delta >4 && Delta<=95){
              data_TX_normal_FIFO[13]='$';
              data_TX_normal_FIFO[14]=ID_READ;
              data_TX_normal_FIFO[15]='1';
              write_TX_normal_FIFO();
              Delay_ms(100);
              LED4=1;
           }
           else{
             data_TX_normal_FIFO[13]='$';
             data_TX_normal_FIFO[14]=ID_READ;
             data_TX_normal_FIFO[15]='0';
             write_TX_normal_FIFO();
             Delay_ms(100);
             LED4=1;
           }
           Nop();
           Nop();
        }
    }
}
void ScanInput(void){
    
    portread = PORTE;
    
    if((portread & 0x04)!=0){
        T_Calling=0;
        F_Calling=0;
    }
    else if(F_Calling!= 2){
        T_Calling++;
    }
    
    if(T_Calling > DEBOUNCETIME){
		F_Calling = 1;
		T_Calling = 0;
	}
}
/*
  while(1){
        
         Value_LDR=ADC_GetConversion(6);
         VoltageOutput=((float) Value_LDR) * AdcRef;
         
         ResistanceLDR = (VoltageOutput * R3)/(Vcc - VoltageOutput);
         
         Light = (unsigned long)((100 - ((ResistanceLDR / Resistance0)*100)) * 1000);
         
         Delta=OFF_Light - Light;
         Nop();
        
    }
 */