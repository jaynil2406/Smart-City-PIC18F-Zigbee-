/*
   Author      : Er.Badhusha Arabusha
   Compiler    : mikroC PRO for PIC v.6.5.0
   MCU         : PIC 18F46K22
   Flow Sensor : Sea YF-S201   Connect @ Pin 15
   Oscillator  : 20 MHz
*/

// Lcd module connections

sbit LCD_RS at LATB4_bit;
sbit LCD_EN at LATB5_bit;
sbit LCD_D4 at LATB0_bit;
sbit LCD_D5 at LATB1_bit;
sbit LCD_D6 at LATB2_bit;
sbit LCD_D7 at LATB3_bit;

// Pin direction

sbit LCD_RS_Direction at TRISB4_bit;
sbit LCD_EN_Direction at TRISB5_bit;
sbit LCD_D7_Direction at TRISB3_bit;
sbit LCD_D6_Direction at TRISB2_bit;
sbit LCD_D5_Direction at TRISB1_bit;
sbit LCD_D4_Direction at TRISB0_bit;

void main()
{
unsigned long frequency,flowrate;
unsigned long freq_low;                // low word of frequency count
char flowratetext[11];                 // buffer for ASCII conversion
     ANSELA = 0;                       // Configure PORTA pins as digital
     ANSELB = 0;                       // Configure PORTB pins as digital
     ANSELC = 0;                       // Configure PORTC pins as digital
     ADCON0 = 0;                       // A/D off
     ADCON1 = 0x0f;                    // all digital
     CM1CON0 = 0;                      // disable 18F46K22 comparator
     CM2CON0 = 0;                      // disable 18F46K22 comparator
     TRISB = 0;                        // PORTB is output
     PORTB = 0x00;                     // Initialize PORTB
     LATA = 0;                         // all off
     LATC = 0;                         // all off
     TRISA = 0xC0;                     // all output except OSC pins
     TRISB = 0x00;                     // all output
     TRISC = 0x01;                     // all output except RC0
     Delay_ms(100);                    // Wait for LCD to stabilise
     Lcd_Init();                          // Initialize Lcd
     Lcd_Cmd(_LCD_CLEAR);                 // Clear display
     Lcd_Cmd(_LCD_CURSOR_OFF);            // Turn cursor off
     Lcd_Out(1,1,"FR:          L/m");    // Print text to Lcd, 2nd row, 1st column
     UART1_Init(9615);                    //Initialize UART module
     Delay_ms(20);
     UART1_Write_Text("Start");
     UART1_Write(13);
     UART1_Write(10);
     T0CON = 0x86;                     // T0 on, 16 bit, prescaler 128
     T1CON = 0x85;                     // T1 on, ext input, no prescale
     T1GCON = 0x00;                    // no gating
     while(1){
         TMR0H = 0x0b;                 // Timer set for 999856us
         TMR0L = 0xe5;
         INTCON.TMR0IF = 0;            // reset time-out indicator
         frequency = 0;                // initialise count
         TMR1L = 0;                    // reset to 0
         TMR1H = 0;                    // reset to 0
         PIR1.TMR1IF = 0;              // initialise
         while(!INTCON.TMR0IF){        // wait for 1 second time-out
             if(PIR1.TMR1IF){          // monitor frequency count overflow
                 PIR1.TMR1IF=0;        // reset overflow
                 frequency += 65536;   // increment count high bytes
             }
         }
         freq_low = (TMR1H << 8) + TMR1L;  // collect frequency bytes
         frequency += freq_low;            // collect frequency bytes
         flowrate=frequency/7.5;           //Obtain flow rate from frequency (7.5 from datasheet of flow sensor) for L/Hour * 60 & for L/sec / by 60
         LongWordToStr(flowrate,flowratetext);  //Convert integer to String
         Lcd_Out(1,4,flowratetext);
         UART1_write_text(flowratetext);
     }
}