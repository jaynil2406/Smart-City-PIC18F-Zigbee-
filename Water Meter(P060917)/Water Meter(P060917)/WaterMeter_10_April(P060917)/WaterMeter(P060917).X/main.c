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
#define CURSER 0x0e
#define CLEARCURSER 0x0c
#define LINE1    0x80  // FIRST LINE FOR LCD DISPLAY
#define LINE2	 0xC0  // SECOND LINE FOR LCD DISPLAY
#define BUSY 		PORTEbits.RE7	//Busy check.
#define DEBOUNCETIME  20
unsigned char F_SET_KEY=0,F_INC_KEY=0,F_DEC_KEY=0;
unsigned char T_SET_KEY=0,T_INC_KEY=0,T_DEC_KEY=0;
unsigned int ConfigMode=0;
unsigned char Flag=0,ConfigModeEntered=0,CheckPassword[3];

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
void ScanInput(void);
void DisplayMenu(void);

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
               Nop();
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
    if(INTCON3bits.INT1IE == 1 && INTCON3bits.INT1IF == 1)
    {
        INT1_ISR();
    }
    else if(INTCONbits.TMR0IE == 1 && INTCONbits.TMR0IF == 1)
    {
        ScanInput();
        if(F_SET_KEY==1)
			{
				if(ConfigModeEntered==0)
    			{
					Flag=1;
					ConfigModeEntered=1;
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
    Delay_ms(500);Delay_ms(500);Delay_ms(500);Delay_ms(500);Delay_ms(500);
    // Initialize the device
    SYSTEM_Initialize();
    INTERRUPT_GlobalInterruptHighEnable();
    INTERRUPT_GlobalInterruptLowEnable();
    INTERRUPT_PeripheralInterruptEnable();
    Delay_ms(100);
    LcdInit();
    Delay_ms(10);
    lcd_off_cursor();
	lcd_clear();
	LcdDisplay(LINE1,"    philbrick     ");
    LcdDisplay(LINE2,"  Technologies    ");
    Delayms(300);Delayms(300);Delayms(300);Delayms(300);
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
    LcdDisplay(LINE1," Press SET KEY  ");
    LcdDisplay(LINE2,"To Set DEVICE ID");
    Delay_ms(500);
    while (1)
    {
        ConfigMode++;
		if(ConfigMode<100)
		{
			Delayms1(1);
			LcdDisplay(LINE1," Press SET KEY  ");
            LcdDisplay(LINE2,"To Set DEVICE ID");
			
			if(Flag==1)
			{
                
				DisplayMenu();
			}
		}
        
       
        
    }
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
void ScanInput(void){
    unsigned char portread = PORTG;
    
    if((portread & 0x01)==0){
        T_SET_KEY++;
    }
    else if(F_SET_KEY!= 2){
        T_SET_KEY=0;
        F_SET_KEY=0;
        
    }
    
    if((portread & 0x02)==0){
        T_INC_KEY++;
    }
    else if(F_INC_KEY!= 2){
        T_INC_KEY=0;
        F_INC_KEY=0;
        
    }
    
    if((portread & 0x04)==0){
        T_DEC_KEY++;
    }
    else if(F_DEC_KEY!= 2){
        T_DEC_KEY=0;
        F_DEC_KEY=0;
        
    }
    
    if(T_SET_KEY > DEBOUNCETIME){
	   F_SET_KEY = 1;
	   T_SET_KEY = 0;
	}
    if(T_INC_KEY > DEBOUNCETIME){
	   F_INC_KEY = 1;
	   T_INC_KEY = 0;
	}
    if(T_DEC_KEY > DEBOUNCETIME){
	   F_DEC_KEY = 1;
	   T_DEC_KEY = 0;
	}
}
void DisplayMenu(void){
    unsigned char i=0,j=0,k=0,inc=0,INC=0,DEC=0,EXIT=0,FirstChange=0;
	char key=0;
	LcdDisplay(LINE1,"     SET ID     ");
	LcdDisplay(LINE2,"                ");
	
	LcdCmd(0xc5);
	LcdCmd(CURSER);
    while(1){
        if(F_SET_KEY==1&&inc==1)
		{
				LcdCmd(0xc5+i);
				LcdData('*');
				CheckPassword[i]=key;
				i++;
				
				inc=0;
				key=0;
				FirstChange=0;
				LcdCmd(0xc5+i);
				LcdCmd(CURSER);
		while(F_SET_KEY==0);
		}
        if(F_INC_KEY==1)
		{
			
			inc=1;
				if(FirstChange==1)
				{
					key++;
					if(key==10)
						key=0;
				}
			FirstChange=1;	
			LcdCmd(0xc5+i);
			LcdData(key+48);
			LcdCmd(0xc5+i);
			LcdCmd(CURSER);
			
		
		while(F_INC_KEY==0);
		}
		if(F_DEC_KEY==1)
		{
			
			inc=1;
			if(FirstChange==1)
			{	
				key--;
				if(key==-1)
					key=9;
			}
		
			FirstChange=1;
			
			LcdCmd(0xc5+i);
			LcdData(key+48);
			
			LcdCmd(0xc5+i);
			LcdCmd(CURSER);
			
		while(F_DEC_KEY==0);
		}
        if(i>3)
		{
			LcdCmd(CLEARCURSER);
            
        }
    }
    
}