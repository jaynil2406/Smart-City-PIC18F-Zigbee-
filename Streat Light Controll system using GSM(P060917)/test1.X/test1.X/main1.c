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
         Nilp++;
        if(Nilp>=200){
            Nilp=0;
            LED2=~LED2;
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
    }
    */
     while(1){
       if(DATA_RX[0]=='#'){
            DATA_RX[0]=0x00;
           Count2=~Count2;
            PORTAbits.RA0=Count2;
            Delay_ms(10);
            Delay_ms(10);
            Delay_ms(10);
            Delay_ms(10);  
        }
       Clear_Data(); 
    }
}
/**
 End of File
*/