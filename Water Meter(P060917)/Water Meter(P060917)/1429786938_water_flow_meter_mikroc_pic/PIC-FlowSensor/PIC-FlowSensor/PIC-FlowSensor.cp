#line 1 "D:/Badhusha's Electronic Laboratory/Peripheral Interface Controller/PIC Projects/PIC-FlowSensor.c"


sbit LCD_RS at LATB4_bit;
sbit LCD_EN at LATB5_bit;
sbit LCD_D4 at LATB0_bit;
sbit LCD_D5 at LATB1_bit;
sbit LCD_D6 at LATB2_bit;
sbit LCD_D7 at LATB3_bit;



sbit LCD_RS_Direction at TRISB4_bit;
sbit LCD_EN_Direction at TRISB5_bit;
sbit LCD_D7_Direction at TRISB3_bit;
sbit LCD_D6_Direction at TRISB2_bit;
sbit LCD_D5_Direction at TRISB1_bit;
sbit LCD_D4_Direction at TRISB0_bit;

void main()
{
unsigned long frequency,flowrate;
unsigned long freq_low;
char flowratetext[11];
 ANSELA = 0;
 ANSELB = 0;
 ANSELC = 0;
 ADCON0 = 0;
 ADCON1 = 0x0f;
 CM1CON0 = 0;
 CM2CON0 = 0;
 TRISB = 0;
 PORTB = 0x00;
 LATA = 0;
 LATC = 0;
 TRISA = 0xC0;
 TRISB = 0x00;
 TRISC = 0x01;
 Delay_ms(100);
 Lcd_Init();
 Lcd_Cmd(_LCD_CLEAR);
 Lcd_Cmd(_LCD_CURSOR_OFF);
 Lcd_Out(1,1,"FR:          L/m");
 UART1_Init(9615);
 Delay_ms(20);
 UART1_Write_Text("Start");
 UART1_Write(13);
 UART1_Write(10);
 T0CON = 0x86;
 T1CON = 0x85;
 T1GCON = 0x00;
 while(1){
 TMR0H = 0x0b;
 TMR0L = 0xe5;
 INTCON.TMR0IF = 0;
 frequency = 0;
 TMR1L = 0;
 TMR1H = 0;
 PIR1.TMR1IF = 0;
 while(!INTCON.TMR0IF){
 if(PIR1.TMR1IF){
 PIR1.TMR1IF=0;
 frequency += 65536;
 }
 }
 freq_low = (TMR1H << 8) + TMR1L;
 frequency += freq_low;
 flowrate=frequency/7.5;
 LongWordToStr(flowrate,flowratetext);
 Lcd_Out(1,4,flowratetext);
 UART1_write_text(flowratetext);
 }
}
