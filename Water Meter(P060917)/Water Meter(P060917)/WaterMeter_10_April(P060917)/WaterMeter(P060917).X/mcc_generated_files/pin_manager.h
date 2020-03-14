/**
  @Generated Pin Manager Header File

  @Company:
    Microchip Technology Inc.

  @File Name:
    pin_manager.h

  @Summary:
    This is the Pin Manager file generated using MPLAB(c) Code Configurator

  @Description:
    This header file provides implementations for pin APIs for all pins selected in the GUI.
    Generation Information :
        Product Revision  :  MPLAB(c) Code Configurator - 4.35
        Device            :  PIC18F67K22
        Version           :  1.01
    The generated drivers are tested against the following:
        Compiler          :  XC8 1.35
        MPLAB             :  MPLAB X 3.40

    Copyright (c) 2013 - 2015 released Microchip Technology Inc.  All rights reserved.

    Microchip licenses to you the right to use, modify, copy and distribute
    Software only when embedded on a Microchip microcontroller or digital signal
    controller that is integrated into your product or third party product
    (pursuant to the sublicense terms in the accompanying license agreement).

    You should refer to the license agreement accompanying this Software for
    additional information regarding your rights and obligations.

    SOFTWARE AND DOCUMENTATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND,
    EITHER EXPRESS OR IMPLIED, INCLUDING WITHOUT LIMITATION, ANY WARRANTY OF
    MERCHANTABILITY, TITLE, NON-INFRINGEMENT AND FITNESS FOR A PARTICULAR PURPOSE.
    IN NO EVENT SHALL MICROCHIP OR ITS LICENSORS BE LIABLE OR OBLIGATED UNDER
    CONTRACT, NEGLIGENCE, STRICT LIABILITY, CONTRIBUTION, BREACH OF WARRANTY, OR
    OTHER LEGAL EQUITABLE THEORY ANY DIRECT OR INDIRECT DAMAGES OR EXPENSES
    INCLUDING BUT NOT LIMITED TO ANY INCIDENTAL, SPECIAL, INDIRECT, PUNITIVE OR
    CONSEQUENTIAL DAMAGES, LOST PROFITS OR LOST DATA, COST OF PROCUREMENT OF
    SUBSTITUTE GOODS, TECHNOLOGY, SERVICES, OR ANY CLAIMS BY THIRD PARTIES
    (INCLUDING BUT NOT LIMITED TO ANY DEFENSE THEREOF), OR OTHER SIMILAR COSTS.

*/


#ifndef PIN_MANAGER_H
#define PIN_MANAGER_H

#define INPUT   1
#define OUTPUT  0

#define HIGH    1
#define LOW     0

#define ANALOG      1
#define DIGITAL     0

#define PULL_UP_ENABLED      1
#define PULL_UP_DISABLED     0

// get/set LED1 aliases
#define LED1_TRIS               TRISAbits.TRISA0
#define LED1_LAT                LATAbits.LATA0
#define LED1_PORT               PORTAbits.RA0
#define LED1_ANS                ANCON0bits.ANSEL0
#define LED1_SetHigh()            do { LATAbits.LATA0 = 1; } while(0)
#define LED1_SetLow()             do { LATAbits.LATA0 = 0; } while(0)
#define LED1_Toggle()             do { LATAbits.LATA0 = ~LATAbits.LATA0; } while(0)
#define LED1_GetValue()           PORTAbits.RA0
#define LED1_SetDigitalInput()    do { TRISAbits.TRISA0 = 1; } while(0)
#define LED1_SetDigitalOutput()   do { TRISAbits.TRISA0 = 0; } while(0)
#define LED1_SetAnalogMode()  do { ANCON0bits.ANSEL0 = 1; } while(0)
#define LED1_SetDigitalMode() do { ANCON0bits.ANSEL0 = 0; } while(0)

// get/set LED2 aliases
#define LED2_TRIS               TRISAbits.TRISA1
#define LED2_LAT                LATAbits.LATA1
#define LED2_PORT               PORTAbits.RA1
#define LED2_ANS                ANCON0bits.ANSEL1
#define LED2_SetHigh()            do { LATAbits.LATA1 = 1; } while(0)
#define LED2_SetLow()             do { LATAbits.LATA1 = 0; } while(0)
#define LED2_Toggle()             do { LATAbits.LATA1 = ~LATAbits.LATA1; } while(0)
#define LED2_GetValue()           PORTAbits.RA1
#define LED2_SetDigitalInput()    do { TRISAbits.TRISA1 = 1; } while(0)
#define LED2_SetDigitalOutput()   do { TRISAbits.TRISA1 = 0; } while(0)
#define LED2_SetAnalogMode()  do { ANCON0bits.ANSEL1 = 1; } while(0)
#define LED2_SetDigitalMode() do { ANCON0bits.ANSEL1 = 0; } while(0)

// get/set LED3 aliases
#define LED3_TRIS               TRISAbits.TRISA2
#define LED3_LAT                LATAbits.LATA2
#define LED3_PORT               PORTAbits.RA2
#define LED3_ANS                ANCON0bits.ANSEL2
#define LED3_SetHigh()            do { LATAbits.LATA2 = 1; } while(0)
#define LED3_SetLow()             do { LATAbits.LATA2 = 0; } while(0)
#define LED3_Toggle()             do { LATAbits.LATA2 = ~LATAbits.LATA2; } while(0)
#define LED3_GetValue()           PORTAbits.RA2
#define LED3_SetDigitalInput()    do { TRISAbits.TRISA2 = 1; } while(0)
#define LED3_SetDigitalOutput()   do { TRISAbits.TRISA2 = 0; } while(0)
#define LED3_SetAnalogMode()  do { ANCON0bits.ANSEL2 = 1; } while(0)
#define LED3_SetDigitalMode() do { ANCON0bits.ANSEL2 = 0; } while(0)

// get/set LED4 aliases
#define LED4_TRIS               TRISAbits.TRISA3
#define LED4_LAT                LATAbits.LATA3
#define LED4_PORT               PORTAbits.RA3
#define LED4_ANS                ANCON0bits.ANSEL3
#define LED4_SetHigh()            do { LATAbits.LATA3 = 1; } while(0)
#define LED4_SetLow()             do { LATAbits.LATA3 = 0; } while(0)
#define LED4_Toggle()             do { LATAbits.LATA3 = ~LATAbits.LATA3; } while(0)
#define LED4_GetValue()           PORTAbits.RA3
#define LED4_SetDigitalInput()    do { TRISAbits.TRISA3 = 1; } while(0)
#define LED4_SetDigitalOutput()   do { TRISAbits.TRISA3 = 0; } while(0)
#define LED4_SetAnalogMode()  do { ANCON0bits.ANSEL3 = 1; } while(0)
#define LED4_SetDigitalMode() do { ANCON0bits.ANSEL3 = 0; } while(0)

// get/set BUZZER aliases
#define BUZZER_TRIS               TRISAbits.TRISA4
#define BUZZER_LAT                LATAbits.LATA4
#define BUZZER_PORT               PORTAbits.RA4
#define BUZZER_SetHigh()            do { LATAbits.LATA4 = 1; } while(0)
#define BUZZER_SetLow()             do { LATAbits.LATA4 = 0; } while(0)
#define BUZZER_Toggle()             do { LATAbits.LATA4 = ~LATAbits.LATA4; } while(0)
#define BUZZER_GetValue()           PORTAbits.RA4
#define BUZZER_SetDigitalInput()    do { TRISAbits.TRISA4 = 1; } while(0)
#define BUZZER_SetDigitalOutput()   do { TRISAbits.TRISA4 = 0; } while(0)

// get/set RELAY aliases
#define RELAY_TRIS               TRISAbits.TRISA5
#define RELAY_LAT                LATAbits.LATA5
#define RELAY_PORT               PORTAbits.RA5
#define RELAY_ANS                ANCON0bits.ANSEL4
#define RELAY_SetHigh()            do { LATAbits.LATA5 = 1; } while(0)
#define RELAY_SetLow()             do { LATAbits.LATA5 = 0; } while(0)
#define RELAY_Toggle()             do { LATAbits.LATA5 = ~LATAbits.LATA5; } while(0)
#define RELAY_GetValue()           PORTAbits.RA5
#define RELAY_SetDigitalInput()    do { TRISAbits.TRISA5 = 1; } while(0)
#define RELAY_SetDigitalOutput()   do { TRISAbits.TRISA5 = 0; } while(0)
#define RELAY_SetAnalogMode()  do { ANCON0bits.ANSEL4 = 1; } while(0)
#define RELAY_SetDigitalMode() do { ANCON0bits.ANSEL4 = 0; } while(0)

// get/set RB0 procedures
#define RB0_SetHigh()    do { LATBbits.LATB0 = 1; } while(0)
#define RB0_SetLow()   do { LATBbits.LATB0 = 0; } while(0)
#define RB0_Toggle()   do { LATBbits.LATB0 = ~LATBbits.LATB0; } while(0)
#define RB0_GetValue()         PORTBbits.RB0
#define RB0_SetDigitalInput()   do { TRISBbits.TRISB0 = 1; } while(0)
#define RB0_SetDigitalOutput()  do { TRISBbits.TRISB0 = 0; } while(0)

// get/set RB1 procedures
#define RB1_SetHigh()    do { LATBbits.LATB1 = 1; } while(0)
#define RB1_SetLow()   do { LATBbits.LATB1 = 0; } while(0)
#define RB1_Toggle()   do { LATBbits.LATB1 = ~LATBbits.LATB1; } while(0)
#define RB1_GetValue()         PORTBbits.RB1
#define RB1_SetDigitalInput()   do { TRISBbits.TRISB1 = 1; } while(0)
#define RB1_SetDigitalOutput()  do { TRISBbits.TRISB1 = 0; } while(0)

// get/set CS aliases
#define CS_TRIS               TRISCbits.TRISC0
#define CS_LAT                LATCbits.LATC0
#define CS_PORT               PORTCbits.RC0
#define CS_SetHigh()            do { LATCbits.LATC0 = 1; } while(0)
#define CS_SetLow()             do { LATCbits.LATC0 = 0; } while(0)
#define CS_Toggle()             do { LATCbits.LATC0 = ~LATCbits.LATC0; } while(0)
#define CS_GetValue()           PORTCbits.RC0
#define CS_SetDigitalInput()    do { TRISCbits.TRISC0 = 1; } while(0)
#define CS_SetDigitalOutput()   do { TRISCbits.TRISC0 = 0; } while(0)

// get/set RST aliases
#define RST_TRIS               TRISCbits.TRISC1
#define RST_LAT                LATCbits.LATC1
#define RST_PORT               PORTCbits.RC1
#define RST_SetHigh()            do { LATCbits.LATC1 = 1; } while(0)
#define RST_SetLow()             do { LATCbits.LATC1 = 0; } while(0)
#define RST_Toggle()             do { LATCbits.LATC1 = ~LATCbits.LATC1; } while(0)
#define RST_GetValue()           PORTCbits.RC1
#define RST_SetDigitalInput()    do { TRISCbits.TRISC1 = 1; } while(0)
#define RST_SetDigitalOutput()   do { TRISCbits.TRISC1 = 0; } while(0)

// get/set IO_RD1 aliases
#define IO_RD1_TRIS               TRISDbits.TRISD1
#define IO_RD1_LAT                LATDbits.LATD1
#define IO_RD1_PORT               PORTDbits.RD1
#define IO_RD1_SetHigh()            do { LATDbits.LATD1 = 1; } while(0)
#define IO_RD1_SetLow()             do { LATDbits.LATD1 = 0; } while(0)
#define IO_RD1_Toggle()             do { LATDbits.LATD1 = ~LATDbits.LATD1; } while(0)
#define IO_RD1_GetValue()           PORTDbits.RD1
#define IO_RD1_SetDigitalInput()    do { TRISDbits.TRISD1 = 1; } while(0)
#define IO_RD1_SetDigitalOutput()   do { TRISDbits.TRISD1 = 0; } while(0)

// get/set IO_RE0 aliases
#define IO_RE0_TRIS               TRISEbits.TRISE0
#define IO_RE0_LAT                LATEbits.LATE0
#define IO_RE0_PORT               PORTEbits.RE0
#define IO_RE0_SetHigh()            do { LATEbits.LATE0 = 1; } while(0)
#define IO_RE0_SetLow()             do { LATEbits.LATE0 = 0; } while(0)
#define IO_RE0_Toggle()             do { LATEbits.LATE0 = ~LATEbits.LATE0; } while(0)
#define IO_RE0_GetValue()           PORTEbits.RE0
#define IO_RE0_SetDigitalInput()    do { TRISEbits.TRISE0 = 1; } while(0)
#define IO_RE0_SetDigitalOutput()   do { TRISEbits.TRISE0 = 0; } while(0)

// get/set IO_RE1 aliases
#define IO_RE1_TRIS               TRISEbits.TRISE1
#define IO_RE1_LAT                LATEbits.LATE1
#define IO_RE1_PORT               PORTEbits.RE1
#define IO_RE1_SetHigh()            do { LATEbits.LATE1 = 1; } while(0)
#define IO_RE1_SetLow()             do { LATEbits.LATE1 = 0; } while(0)
#define IO_RE1_Toggle()             do { LATEbits.LATE1 = ~LATEbits.LATE1; } while(0)
#define IO_RE1_GetValue()           PORTEbits.RE1
#define IO_RE1_SetDigitalInput()    do { TRISEbits.TRISE1 = 1; } while(0)
#define IO_RE1_SetDigitalOutput()   do { TRISEbits.TRISE1 = 0; } while(0)

// get/set IO_RE2 aliases
#define IO_RE2_TRIS               TRISEbits.TRISE2
#define IO_RE2_LAT                LATEbits.LATE2
#define IO_RE2_PORT               PORTEbits.RE2
#define IO_RE2_SetHigh()            do { LATEbits.LATE2 = 1; } while(0)
#define IO_RE2_SetLow()             do { LATEbits.LATE2 = 0; } while(0)
#define IO_RE2_Toggle()             do { LATEbits.LATE2 = ~LATEbits.LATE2; } while(0)
#define IO_RE2_GetValue()           PORTEbits.RE2
#define IO_RE2_SetDigitalInput()    do { TRISEbits.TRISE2 = 1; } while(0)
#define IO_RE2_SetDigitalOutput()   do { TRISEbits.TRISE2 = 0; } while(0)

// get/set IO_RE3 aliases
#define IO_RE3_TRIS               TRISEbits.TRISE3
#define IO_RE3_LAT                LATEbits.LATE3
#define IO_RE3_PORT               PORTEbits.RE3
#define IO_RE3_SetHigh()            do { LATEbits.LATE3 = 1; } while(0)
#define IO_RE3_SetLow()             do { LATEbits.LATE3 = 0; } while(0)
#define IO_RE3_Toggle()             do { LATEbits.LATE3 = ~LATEbits.LATE3; } while(0)
#define IO_RE3_GetValue()           PORTEbits.RE3
#define IO_RE3_SetDigitalInput()    do { TRISEbits.TRISE3 = 1; } while(0)
#define IO_RE3_SetDigitalOutput()   do { TRISEbits.TRISE3 = 0; } while(0)

// get/set IO_RE4 aliases
#define IO_RE4_TRIS               TRISEbits.TRISE4
#define IO_RE4_LAT                LATEbits.LATE4
#define IO_RE4_PORT               PORTEbits.RE4
#define IO_RE4_SetHigh()            do { LATEbits.LATE4 = 1; } while(0)
#define IO_RE4_SetLow()             do { LATEbits.LATE4 = 0; } while(0)
#define IO_RE4_Toggle()             do { LATEbits.LATE4 = ~LATEbits.LATE4; } while(0)
#define IO_RE4_GetValue()           PORTEbits.RE4
#define IO_RE4_SetDigitalInput()    do { TRISEbits.TRISE4 = 1; } while(0)
#define IO_RE4_SetDigitalOutput()   do { TRISEbits.TRISE4 = 0; } while(0)

// get/set IO_RE5 aliases
#define IO_RE5_TRIS               TRISEbits.TRISE5
#define IO_RE5_LAT                LATEbits.LATE5
#define IO_RE5_PORT               PORTEbits.RE5
#define IO_RE5_SetHigh()            do { LATEbits.LATE5 = 1; } while(0)
#define IO_RE5_SetLow()             do { LATEbits.LATE5 = 0; } while(0)
#define IO_RE5_Toggle()             do { LATEbits.LATE5 = ~LATEbits.LATE5; } while(0)
#define IO_RE5_GetValue()           PORTEbits.RE5
#define IO_RE5_SetDigitalInput()    do { TRISEbits.TRISE5 = 1; } while(0)
#define IO_RE5_SetDigitalOutput()   do { TRISEbits.TRISE5 = 0; } while(0)

// get/set IO_RE6 aliases
#define IO_RE6_TRIS               TRISEbits.TRISE6
#define IO_RE6_LAT                LATEbits.LATE6
#define IO_RE6_PORT               PORTEbits.RE6
#define IO_RE6_SetHigh()            do { LATEbits.LATE6 = 1; } while(0)
#define IO_RE6_SetLow()             do { LATEbits.LATE6 = 0; } while(0)
#define IO_RE6_Toggle()             do { LATEbits.LATE6 = ~LATEbits.LATE6; } while(0)
#define IO_RE6_GetValue()           PORTEbits.RE6
#define IO_RE6_SetDigitalInput()    do { TRISEbits.TRISE6 = 1; } while(0)
#define IO_RE6_SetDigitalOutput()   do { TRISEbits.TRISE6 = 0; } while(0)

// get/set IO_RE7 aliases
#define IO_RE7_TRIS               TRISEbits.TRISE7
#define IO_RE7_LAT                LATEbits.LATE7
#define IO_RE7_PORT               PORTEbits.RE7
#define IO_RE7_SetHigh()            do { LATEbits.LATE7 = 1; } while(0)
#define IO_RE7_SetLow()             do { LATEbits.LATE7 = 0; } while(0)
#define IO_RE7_Toggle()             do { LATEbits.LATE7 = ~LATEbits.LATE7; } while(0)
#define IO_RE7_GetValue()           PORTEbits.RE7
#define IO_RE7_SetDigitalInput()    do { TRISEbits.TRISE7 = 1; } while(0)
#define IO_RE7_SetDigitalOutput()   do { TRISEbits.TRISE7 = 0; } while(0)

// get/set RS aliases
#define RS_TRIS               TRISFbits.TRISF1
#define RS_LAT                LATFbits.LATF1
#define RS_PORT               PORTFbits.RF1
#define RS_ANS                ANCON0bits.ANSEL6
#define RS_SetHigh()            do { LATFbits.LATF1 = 1; } while(0)
#define RS_SetLow()             do { LATFbits.LATF1 = 0; } while(0)
#define RS_Toggle()             do { LATFbits.LATF1 = ~LATFbits.LATF1; } while(0)
#define RS_GetValue()           PORTFbits.RF1
#define RS_SetDigitalInput()    do { TRISFbits.TRISF1 = 1; } while(0)
#define RS_SetDigitalOutput()   do { TRISFbits.TRISF1 = 0; } while(0)
#define RS_SetAnalogMode()  do { ANCON0bits.ANSEL6 = 1; } while(0)
#define RS_SetDigitalMode() do { ANCON0bits.ANSEL6 = 0; } while(0)

// get/set RW aliases
#define RW_TRIS               TRISFbits.TRISF2
#define RW_LAT                LATFbits.LATF2
#define RW_PORT               PORTFbits.RF2
#define RW_ANS                ANCON0bits.ANSEL7
#define RW_SetHigh()            do { LATFbits.LATF2 = 1; } while(0)
#define RW_SetLow()             do { LATFbits.LATF2 = 0; } while(0)
#define RW_Toggle()             do { LATFbits.LATF2 = ~LATFbits.LATF2; } while(0)
#define RW_GetValue()           PORTFbits.RF2
#define RW_SetDigitalInput()    do { TRISFbits.TRISF2 = 1; } while(0)
#define RW_SetDigitalOutput()   do { TRISFbits.TRISF2 = 0; } while(0)
#define RW_SetAnalogMode()  do { ANCON0bits.ANSEL7 = 1; } while(0)
#define RW_SetDigitalMode() do { ANCON0bits.ANSEL7 = 0; } while(0)

// get/set EN aliases
#define EN_TRIS               TRISFbits.TRISF3
#define EN_LAT                LATFbits.LATF3
#define EN_PORT               PORTFbits.RF3
#define EN_ANS                ANCON1bits.ANSEL8
#define EN_SetHigh()            do { LATFbits.LATF3 = 1; } while(0)
#define EN_SetLow()             do { LATFbits.LATF3 = 0; } while(0)
#define EN_Toggle()             do { LATFbits.LATF3 = ~LATFbits.LATF3; } while(0)
#define EN_GetValue()           PORTFbits.RF3
#define EN_SetDigitalInput()    do { TRISFbits.TRISF3 = 1; } while(0)
#define EN_SetDigitalOutput()   do { TRISFbits.TRISF3 = 0; } while(0)
#define EN_SetAnalogMode()  do { ANCON1bits.ANSEL8 = 1; } while(0)
#define EN_SetDigitalMode() do { ANCON1bits.ANSEL8 = 0; } while(0)

// get/set WAKE aliases
#define WAKE_TRIS               TRISFbits.TRISF4
#define WAKE_LAT                LATFbits.LATF4
#define WAKE_PORT               PORTFbits.RF4
#define WAKE_ANS                ANCON1bits.ANSEL9
#define WAKE_SetHigh()            do { LATFbits.LATF4 = 1; } while(0)
#define WAKE_SetLow()             do { LATFbits.LATF4 = 0; } while(0)
#define WAKE_Toggle()             do { LATFbits.LATF4 = ~LATFbits.LATF4; } while(0)
#define WAKE_GetValue()           PORTFbits.RF4
#define WAKE_SetDigitalInput()    do { TRISFbits.TRISF4 = 1; } while(0)
#define WAKE_SetDigitalOutput()   do { TRISFbits.TRISF4 = 0; } while(0)
#define WAKE_SetAnalogMode()  do { ANCON1bits.ANSEL9 = 1; } while(0)
#define WAKE_SetDigitalMode() do { ANCON1bits.ANSEL9 = 0; } while(0)

// get/set SET aliases
#define SET_TRIS               TRISGbits.TRISG0
#define SET_LAT                LATGbits.LATG0
#define SET_PORT               PORTGbits.RG0
#define SET_SetHigh()            do { LATGbits.LATG0 = 1; } while(0)
#define SET_SetLow()             do { LATGbits.LATG0 = 0; } while(0)
#define SET_Toggle()             do { LATGbits.LATG0 = ~LATGbits.LATG0; } while(0)
#define SET_GetValue()           PORTGbits.RG0
#define SET_SetDigitalInput()    do { TRISGbits.TRISG0 = 1; } while(0)
#define SET_SetDigitalOutput()   do { TRISGbits.TRISG0 = 0; } while(0)

// get/set INC aliases
#define INC_TRIS               TRISGbits.TRISG1
#define INC_LAT                LATGbits.LATG1
#define INC_PORT               PORTGbits.RG1
#define INC_ANS                ANCON2bits.ANSEL19
#define INC_SetHigh()            do { LATGbits.LATG1 = 1; } while(0)
#define INC_SetLow()             do { LATGbits.LATG1 = 0; } while(0)
#define INC_Toggle()             do { LATGbits.LATG1 = ~LATGbits.LATG1; } while(0)
#define INC_GetValue()           PORTGbits.RG1
#define INC_SetDigitalInput()    do { TRISGbits.TRISG1 = 1; } while(0)
#define INC_SetDigitalOutput()   do { TRISGbits.TRISG1 = 0; } while(0)
#define INC_SetAnalogMode()  do { ANCON2bits.ANSEL19 = 1; } while(0)
#define INC_SetDigitalMode() do { ANCON2bits.ANSEL19 = 0; } while(0)

// get/set DEC aliases
#define DEC_TRIS               TRISGbits.TRISG2
#define DEC_LAT                LATGbits.LATG2
#define DEC_PORT               PORTGbits.RG2
#define DEC_ANS                ANCON2bits.ANSEL18
#define DEC_SetHigh()            do { LATGbits.LATG2 = 1; } while(0)
#define DEC_SetLow()             do { LATGbits.LATG2 = 0; } while(0)
#define DEC_Toggle()             do { LATGbits.LATG2 = ~LATGbits.LATG2; } while(0)
#define DEC_GetValue()           PORTGbits.RG2
#define DEC_SetDigitalInput()    do { TRISGbits.TRISG2 = 1; } while(0)
#define DEC_SetDigitalOutput()   do { TRISGbits.TRISG2 = 0; } while(0)
#define DEC_SetAnalogMode()  do { ANCON2bits.ANSEL18 = 1; } while(0)
#define DEC_SetDigitalMode() do { ANCON2bits.ANSEL18 = 0; } while(0)

/**
   @Param
    none
   @Returns
    none
   @Description
    GPIO and peripheral I/O initialization
   @Example
    PIN_MANAGER_Initialize();
 */
void PIN_MANAGER_Initialize (void);

/**
 * @Param
    none
 * @Returns
    none
 * @Description
    Interrupt on Change Handling routine
 * @Example
    PIN_MANAGER_IOC();
 */
void PIN_MANAGER_IOC(void);



#endif // PIN_MANAGER_H
/**
 End of File
*/