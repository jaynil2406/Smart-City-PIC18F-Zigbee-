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
#define CURSOR 0x0E
#define CURSOR_OFF 0x0C
#define LINE1    0x80  // FIRST LINE FOR LCD DISPLAY
#define LINE2	 0xC0  // SECOND LINE FOR LCD DISPLAY
#define BUSY 		PORTEbits.RE7	//Busy check.
#define DEBOUNCETIME  20

#define ON 0
#define OFF 1

#define SETKEY PORTGX.tbits.tb0
#define INCKEY PORTGX.tbits.tb1
#define DECKEY PORTGX.tbits.tb2

typedef union tbitfields
{
  struct 
{
unsigned tb0:1;
unsigned tb1:1;
unsigned tb2:1;
unsigned tb3:1;
unsigned tb4:1;
unsigned tb5:1;
unsigned tb6:1;
unsigned tb7:1;
}tbits;
unsigned char T_BYTE;
}T_BITS;

T_BITS PORTGX;
unsigned char INPUT_PS[2]={0xFF,0XFF};
unsigned char INPUT_DS[2]={0XFF,0XFF};


unsigned char flag=0,ConfigModeEntered=0,CheckPassword[3];


unsigned char F_TimerCounting=0;
unsigned int Increment=0,Decrement=0;
unsigned char F_Enter=0,F_Success=0;
unsigned char Enter=0;
unsigned int COUNT=0,ENTERCOUNT=0;
unsigned char DeviceId_arr[3]={0};
unsigned char Module_ID=0,SendId=0;
unsigned char Digit=0,addr=0,IdByte1=0,IdByte2=0,IdByte3=0,V_Temp=0;
unsigned int Num=0,flow_frequency=0,Flow_Rate=0,Time=0,Time2=0,ltr=0,T_Ltr=0,Pulse=0;
float totalLitres,flowLitres;


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
void Set_DeviceId(void);

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
        flow_frequency++;
      
        INT1_ISR();
    }
    if(INTCONbits.TMR0IE == 1 && INTCONbits.TMR0IF == 1)
    { 
        Time++;
        Time2++;
        if(Time>20){
            Time=0;
            Flow_Rate=(flow_frequency * 60 / 7);
            flow_frequency=0;
        }
        if(Time2>500){
            Time2=0;
            flowLitres=Flow_Rate/60;
            totalLitres += flowLitres;
        }
        //ltr+=(Flow_Rate/60);
        Nop();
        
         
        //Flow_Rate=0;
        ScanInput();
        if(F_TimerCounting==1)
		{
			if(INCKEY==ON)
				Increment++;
			else if(DECKEY==ON)
				Decrement++;
			else if((F_Enter==0) && (SETKEY==ON))
				Enter++;
		}
		
		else if((F_Enter==1)&&(SETKEY==ON))
		{
			ENTERCOUNT++;
      		if (ENTERCOUNT >= 100)
        	{
				flag=1;
			}
		}
        TMR0_ISR();
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
    lcd_clear();
    do{	
		F_Enter=1;
		LcdDisplay(LINE1,"    Go For      ");
        LcdDisplay(LINE2,"  Set Device ID ");
  		if(flag==1){	
			F_Enter=0;		
	   		Set_DeviceId();
	   		Enter=1;
	   	}
		COUNT++;	
	}while((COUNT<20)&&(Enter==0));
    F_TimerCounting=0;
	lcd_clear();
	F_Enter=0;
	Increment=0;
	Decrement=0;
	Enter=0;
	LcdCmd(CURSOR_OFF);
	F_TimerCounting=1;
    LcdDisplay(LINE1,"F.Rate:         ");
    LcdDisplay(LINE2,"T.Ltr:          ");
    while (1)
    {
        
        if((CRC==Rv_CRC) && (DATA_RX[0]=='!')){
            DATA_RX[0]=0;
            LED2=0;
            SendId=Read_b_eep2(0x02);
            data_TX_normal_FIFO[13]='!';
            data_TX_normal_FIFO[14]=ltr;
            data_TX_normal_FIFO[15]=SendId;
            Delay_ms(100);Delay_ms(100);Delay_ms(100);Delay_ms(100);Delay_ms(100);
            write_TX_normal_FIFO();
            LED2=1;
        }
        Num=Flow_Rate;
        if(Num >=0 && Num < 10){
            
            
            LcdCmd(0x8e);
            LcdData(Num+0x30);	
            LcdCmd(0x8d);
            LcdData(0+0x30);
            LcdCmd(0x8c);
            LcdData(0+0x30);
        }
        else if(Num >=10 && Num < 100){
            IdByte1=Num/10;
            IdByte2=Num%10; 
            
            
            LcdCmd(0x8d);
            LcdData(IdByte1+0x30);	
            LcdCmd(0x8e);
            LcdData(IdByte2+0x30);
            LcdCmd(0x8c);
            LcdData(0+0x30);	
           
           
        }
        else if(Num >=100 && Num < 1000){
            IdByte3=Num/100;
            V_Temp=Num%100;
            IdByte1=V_Temp/10;
            IdByte2=V_Temp%10; 

            	
            
            LcdCmd(0x8c);
            LcdData(IdByte3+0x30);	
            LcdCmd(0x8d);
            LcdData(IdByte1+0x30);	
            LcdCmd(0x8e);
            LcdData(IdByte2+0x30);	
            
        }

        ltr=totalLitres;
        if(ltr >=0 && ltr < 10){
            
            
            LcdCmd(0xce);
            LcdData(ltr+0x30);	
            LcdCmd(0xcd);
            LcdData(0+0x30);
            LcdCmd(0xcc);
            LcdData(0+0x30);
        }
        else if(ltr >=10 && ltr < 100){
            IdByte1=ltr/10;
            IdByte2=ltr%10; 
            
            
            LcdCmd(0xcd);
            LcdData(IdByte1+0x30);	
            LcdCmd(0xce);
            LcdData(IdByte2+0x30);
            LcdCmd(0xcc);
            LcdData(0+0x30);	
           
           
        }
        else if(ltr >=100 && ltr < 1000){
            IdByte3=ltr/100;
            V_Temp=ltr%100;
            IdByte1=V_Temp/10;
            IdByte2=V_Temp%10; 

            	
            
            LcdCmd(0xcc);
            LcdData(IdByte3+0x30);	
            LcdCmd(0xcd);
            LcdData(IdByte1+0x30);	
            LcdCmd(0xce);
            LcdData(IdByte2+0x30);	
            
        }
        /*
         //Flow_Rate = (flow_frequency * 60 / 7);
        //Nop();

       Num=Flow_Rate;
       ltr= T_Ltr;
       addr=0x8F;
      //addr1=0xCC
     //  if(Num==0){
     //      for(addr=0x8F;addr>0x88;addr--){
     //           LcdCmd(addr);
     //           LcdData('0');
     //      }
     //  }
       while(Num>0){
           Digit=Num%10;
           Num/=10;
           LcdCmd(addr);
           LcdData(Digit+0x30);
           addr--;
           
       }
       
       addr=0xCC;
       while(ltr>0){
           Digit=ltr%10;
           ltr/=10;
           LcdCmd(addr);
           LcdData(Digit+0x30);
           addr--;
       } 
        
        */
        
        
       //LcdCmd(LINE1+8);
       
     //  Flow_Rate
        Nop();  
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
    
   /*
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
    */
    unsigned char temp,x;
	
	x=0;
	temp=PORTG ;
	INPUT_DS[x]=temp|INPUT_PS[x];
	INPUT_PS[x]=temp;
	PORTGX.T_BYTE=INPUT_DS[x];
	x=x+1;
}
void Set_DeviceId(void){
    char i=0,j=0;
	unsigned char n=1,fail=0;
	unsigned int ID1=0;
    
    lcd_clear();
    LcdDisplay(LINE1,"  Device Id Is  ");
    LcdDisplay(LINE2,"      000       ");
    LcdCmd(LINE2+6);
	LcdCmd(CURSOR);
    while(SETKEY==ON);
	Delayms1(30);
    
    Increment=0;
	Decrement=0;
	Enter=0;
	F_TimerCounting=1;
    while(1){
        if(Increment>=DEBOUNCETIME){			
      		LcdCmd(LINE2 + 6 + i);
      		j++;
      		if(j>9)
      			j=0;      			
      		LcdCmd(CURSOR_OFF); 
      		LcdData(j%10 + 48);
            LcdCmd(LINE2 + 6 + i);
      		LcdCmd(CURSOR); 
      		while(INCKEY==0);
			Delayms1(30);     		
			Increment=0;
      	}
        if(Decrement>=DEBOUNCETIME){
			LcdCmd(LINE2 + 6 + i);
      		j--;
      		if(j<0)
      			j=9;      			
      		LcdCmd(CURSOR_OFF); 
      		LcdData(j%10 + 48);     		
            LcdCmd(LINE2 + 6 + i);
            LcdCmd(CURSOR); 
			while(DECKEY==0);      		
			Delayms1(30);
			Decrement=0;
      	}
        if(Enter >= DEBOUNCETIME){
            DeviceId_arr[i]=j;
            i++;    			
            LcdCmd(LINE2 + 6 + i);
            LcdCmd(CURSOR_OFF); 
            j=0; 
            while(SETKEY==0);
            Delayms1(30);
            Enter=0;
            if(i>2){
               i=0;
               LcdDisplay(LINE1,"Want to SAVE?   ");
               LcdDisplay(LINE2,"  >Yes     No   ");					      						

               Increment=0;
               Decrement=0;
               Enter=0;
               F_TimerCounting=1;
               while(1){
                   if(Increment>=DEBOUNCETIME){			
      						n++;
							NOP();NOP();NOP();NOP();
      						if(n>2)
      							n=1;      			      				
      						while(INCKEY==0);
							Delayms1(30);    
							if(n==1){
								//LcdDisplay(LINE1,"Want to SAVE?   ");
								LcdDisplay(LINE2,"  >Yes     No   ");					      						
							}
							else if(n==2){
								//LcdDisplay(LINE1,"Want to SAVE?   ");
								LcdDisplay(LINE2,"   Yes    >No   ");					      						
							} 		
							Increment=0;
      					}
      					if(Decrement >= DEBOUNCETIME){
							n--;
							NOP();NOP();NOP();NOP();
							if(n<1)
      							n=2;      			
							while(DECKEY==0);      		
							Delayms1(30);
							if(n==1){
								//LcdDisplay(LINE1,"Want to SAVE?   ");
								LcdDisplay(LINE2,"  >Yes     No   ");					      						
							}
							else if(n==2){
								//LcdDisplay(LINE1,"Want to SAVE?   ");
								LcdDisplay(LINE2,"   Yes    >No   ");					      						
							}
							Decrement=0;
      					}
                        if(Enter >= DEBOUNCETIME){ 
							while(SETKEY==0);    		 
							Delayms1(30);										
    						if(n==1){
					write_weight:
								for(i=0;i<3;i++){
									if(i==0)
										ID1=100 * DeviceId_arr[i];
									else if(i==1)
										ID1=10 * DeviceId_arr[i];
									else if(i==2)
										ID1=DeviceId_arr[i];
									
									Write_b_eep2(0x0064 + i,DeviceId_arr[i]);
         							Busy_eep2();
								}
								for(i=0;i<3;i++){
									if((Read_b_eep2(0x0064 + i)) == (DeviceId_arr[i])){
										if(i==2){
											F_TimerCounting=0;
											F_Success = 1;
											i=0;
											j=0;
											lcd_clear();
											LcdDisplay(LINE1,"Data Saved...   ");
											Delayms1(500);
											lcd_clear();															      						
											break;
										}
										continue;
									}
									else{
										fail++;
										if(fail > 2){										
											goto no;
										}
										goto write_weight;
									}	
								}
								if(F_Success == 1)
										break;
								Enter=0;     			
							}
							if(n==2){
							no:	      						    						     		
      							lcd_clear();
								LcdDisplay(LINE1,"  Device Id Is  ");
                                LcdDisplay(LINE2,"      000       ");
								LcdCmd(LINE2+6);
								LcdCmd(CURSOR);
								n=0;
								Increment=0;
								Decrement=0;
								Enter=0;
								F_TimerCounting=1;
								break;
							}
						}						                   
               }
            }
        }
        if(F_Success == 1){
            Module_ID=((DeviceId_arr[0]*100) + (DeviceId_arr[1]*10) + (DeviceId_arr[2]));
            Write_b_eep2(0x02,Module_ID);
			F_Success=0;
			F_TimerCounting=1;
			break; 
		}
		//LcdCmd(LINE2 + 3 + i); 
    }
}