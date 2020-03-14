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

// get/set C1A aliases
#define C1A_TRIS               TRISDbits.TRISD0
#define C1A_LAT                LATDbits.LATD0
#define C1A_PORT               PORTDbits.RD0
#define C1A_SetHigh()            do { LATDbits.LATD0 = 1; } while(0)
#define C1A_SetLow()             do { LATDbits.LATD0 = 0; } while(0)
#define C1A_Toggle()             do { LATDbits.LATD0 = ~LATDbits.LATD0; } while(0)
#define C1A_GetValue()           PORTDbits.RD0
#define C1A_SetDigitalInput()    do { TRISDbits.TRISD0 = 1; } while(0)
#define C1A_SetDigitalOutput()   do { TRISDbits.TRISD0 = 0; } while(0)

// get/set C2A aliases
#define C2A_TRIS               TRISDbits.TRISD1
#define C2A_LAT                LATDbits.LATD1
#define C2A_PORT               PORTDbits.RD1
#define C2A_SetHigh()            do { LATDbits.LATD1 = 1; } while(0)
#define C2A_SetLow()             do { LATDbits.LATD1 = 0; } while(0)
#define C2A_Toggle()             do { LATDbits.LATD1 = ~LATDbits.LATD1; } while(0)
#define C2A_GetValue()           PORTDbits.RD1
#define C2A_SetDigitalInput()    do { TRISDbits.TRISD1 = 1; } while(0)
#define C2A_SetDigitalOutput()   do { TRISDbits.TRISD1 = 0; } while(0)

// get/set C3A aliases
#define C3A_TRIS               TRISDbits.TRISD2
#define C3A_LAT                LATDbits.LATD2
#define C3A_PORT               PORTDbits.RD2
#define C3A_SetHigh()            do { LATDbits.LATD2 = 1; } while(0)
#define C3A_SetLow()             do { LATDbits.LATD2 = 0; } while(0)
#define C3A_Toggle()             do { LATDbits.LATD2 = ~LATDbits.LATD2; } while(0)
#define C3A_GetValue()           PORTDbits.RD2
#define C3A_SetDigitalInput()    do { TRISDbits.TRISD2 = 1; } while(0)
#define C3A_SetDigitalOutput()   do { TRISDbits.TRISD2 = 0; } while(0)

// get/set C4A aliases
#define C4A_TRIS               TRISDbits.TRISD3
#define C4A_LAT                LATDbits.LATD3
#define C4A_PORT               PORTDbits.RD3
#define C4A_SetHigh()            do { LATDbits.LATD3 = 1; } while(0)
#define C4A_SetLow()             do { LATDbits.LATD3 = 0; } while(0)
#define C4A_Toggle()             do { LATDbits.LATD3 = ~LATDbits.LATD3; } while(0)
#define C4A_GetValue()           PORTDbits.RD3
#define C4A_SetDigitalInput()    do { TRISDbits.TRISD3 = 1; } while(0)
#define C4A_SetDigitalOutput()   do { TRISDbits.TRISD3 = 0; } while(0)

// get/set C5A aliases
#define C5A_TRIS               TRISDbits.TRISD4
#define C5A_LAT                LATDbits.LATD4
#define C5A_PORT               PORTDbits.RD4
#define C5A_SetHigh()            do { LATDbits.LATD4 = 1; } while(0)
#define C5A_SetLow()             do { LATDbits.LATD4 = 0; } while(0)
#define C5A_Toggle()             do { LATDbits.LATD4 = ~LATDbits.LATD4; } while(0)
#define C5A_GetValue()           PORTDbits.RD4
#define C5A_SetDigitalInput()    do { TRISDbits.TRISD4 = 1; } while(0)
#define C5A_SetDigitalOutput()   do { TRISDbits.TRISD4 = 0; } while(0)

// get/set C6A aliases
#define C6A_TRIS               TRISDbits.TRISD5
#define C6A_LAT                LATDbits.LATD5
#define C6A_PORT               PORTDbits.RD5
#define C6A_SetHigh()            do { LATDbits.LATD5 = 1; } while(0)
#define C6A_SetLow()             do { LATDbits.LATD5 = 0; } while(0)
#define C6A_Toggle()             do { LATDbits.LATD5 = ~LATDbits.LATD5; } while(0)
#define C6A_GetValue()           PORTDbits.RD5
#define C6A_SetDigitalInput()    do { TRISDbits.TRISD5 = 1; } while(0)
#define C6A_SetDigitalOutput()   do { TRISDbits.TRISD5 = 0; } while(0)

// get/set C7A aliases
#define C7A_TRIS               TRISDbits.TRISD6
#define C7A_LAT                LATDbits.LATD6
#define C7A_PORT               PORTDbits.RD6
#define C7A_SetHigh()            do { LATDbits.LATD6 = 1; } while(0)
#define C7A_SetLow()             do { LATDbits.LATD6 = 0; } while(0)
#define C7A_Toggle()             do { LATDbits.LATD6 = ~LATDbits.LATD6; } while(0)
#define C7A_GetValue()           PORTDbits.RD6
#define C7A_SetDigitalInput()    do { TRISDbits.TRISD6 = 1; } while(0)
#define C7A_SetDigitalOutput()   do { TRISDbits.TRISD6 = 0; } while(0)

// get/set C8A aliases
#define C8A_TRIS               TRISDbits.TRISD7
#define C8A_LAT                LATDbits.LATD7
#define C8A_PORT               PORTDbits.RD7
#define C8A_SetHigh()            do { LATDbits.LATD7 = 1; } while(0)
#define C8A_SetLow()             do { LATDbits.LATD7 = 0; } while(0)
#define C8A_Toggle()             do { LATDbits.LATD7 = ~LATDbits.LATD7; } while(0)
#define C8A_GetValue()           PORTDbits.RD7
#define C8A_SetDigitalInput()    do { TRISDbits.TRISD7 = 1; } while(0)
#define C8A_SetDigitalOutput()   do { TRISDbits.TRISD7 = 0; } while(0)

// get/set E_CALL aliases
#define E_CALL_TRIS               TRISEbits.TRISE2
#define E_CALL_LAT                LATEbits.LATE2
#define E_CALL_PORT               PORTEbits.RE2
#define E_CALL_SetHigh()            do { LATEbits.LATE2 = 1; } while(0)
#define E_CALL_SetLow()             do { LATEbits.LATE2 = 0; } while(0)
#define E_CALL_Toggle()             do { LATEbits.LATE2 = ~LATEbits.LATE2; } while(0)
#define E_CALL_GetValue()           PORTEbits.RE2
#define E_CALL_SetDigitalInput()    do { TRISEbits.TRISE2 = 1; } while(0)
#define E_CALL_SetDigitalOutput()   do { TRISEbits.TRISE2 = 0; } while(0)

// get/set LDR aliases
#define LDR_TRIS               TRISFbits.TRISF1
#define LDR_LAT                LATFbits.LATF1
#define LDR_PORT               PORTFbits.RF1
#define LDR_ANS                ANCON0bits.ANSEL6
#define LDR_SetHigh()            do { LATFbits.LATF1 = 1; } while(0)
#define LDR_SetLow()             do { LATFbits.LATF1 = 0; } while(0)
#define LDR_Toggle()             do { LATFbits.LATF1 = ~LATFbits.LATF1; } while(0)
#define LDR_GetValue()           PORTFbits.RF1
#define LDR_SetDigitalInput()    do { TRISFbits.TRISF1 = 1; } while(0)
#define LDR_SetDigitalOutput()   do { TRISFbits.TRISF1 = 0; } while(0)
#define LDR_SetAnalogMode()  do { ANCON0bits.ANSEL6 = 1; } while(0)
#define LDR_SetDigitalMode() do { ANCON0bits.ANSEL6 = 0; } while(0)

// get/set WAKE aliases
#define WAKE_TRIS               TRISFbits.TRISF2
#define WAKE_LAT                LATFbits.LATF2
#define WAKE_PORT               PORTFbits.RF2
#define WAKE_ANS                ANCON0bits.ANSEL7
#define WAKE_SetHigh()            do { LATFbits.LATF2 = 1; } while(0)
#define WAKE_SetLow()             do { LATFbits.LATF2 = 0; } while(0)
#define WAKE_Toggle()             do { LATFbits.LATF2 = ~LATFbits.LATF2; } while(0)
#define WAKE_GetValue()           PORTFbits.RF2
#define WAKE_SetDigitalInput()    do { TRISFbits.TRISF2 = 1; } while(0)
#define WAKE_SetDigitalOutput()   do { TRISFbits.TRISF2 = 0; } while(0)
#define WAKE_SetAnalogMode()  do { ANCON0bits.ANSEL7 = 1; } while(0)
#define WAKE_SetDigitalMode() do { ANCON0bits.ANSEL7 = 0; } while(0)

// get/set R1 aliases
#define R1_TRIS               TRISFbits.TRISF3
#define R1_LAT                LATFbits.LATF3
#define R1_PORT               PORTFbits.RF3
#define R1_ANS                ANCON1bits.ANSEL8
#define R1_SetHigh()            do { LATFbits.LATF3 = 1; } while(0)
#define R1_SetLow()             do { LATFbits.LATF3 = 0; } while(0)
#define R1_Toggle()             do { LATFbits.LATF3 = ~LATFbits.LATF3; } while(0)
#define R1_GetValue()           PORTFbits.RF3
#define R1_SetDigitalInput()    do { TRISFbits.TRISF3 = 1; } while(0)
#define R1_SetDigitalOutput()   do { TRISFbits.TRISF3 = 0; } while(0)
#define R1_SetAnalogMode()  do { ANCON1bits.ANSEL8 = 1; } while(0)
#define R1_SetDigitalMode() do { ANCON1bits.ANSEL8 = 0; } while(0)

// get/set R2 aliases
#define R2_TRIS               TRISFbits.TRISF4
#define R2_LAT                LATFbits.LATF4
#define R2_PORT               PORTFbits.RF4
#define R2_ANS                ANCON1bits.ANSEL9
#define R2_SetHigh()            do { LATFbits.LATF4 = 1; } while(0)
#define R2_SetLow()             do { LATFbits.LATF4 = 0; } while(0)
#define R2_Toggle()             do { LATFbits.LATF4 = ~LATFbits.LATF4; } while(0)
#define R2_GetValue()           PORTFbits.RF4
#define R2_SetDigitalInput()    do { TRISFbits.TRISF4 = 1; } while(0)
#define R2_SetDigitalOutput()   do { TRISFbits.TRISF4 = 0; } while(0)
#define R2_SetAnalogMode()  do { ANCON1bits.ANSEL9 = 1; } while(0)
#define R2_SetDigitalMode() do { ANCON1bits.ANSEL9 = 0; } while(0)

// get/set R3 aliases
#define R3_TRIS               TRISFbits.TRISF5
#define R3_LAT                LATFbits.LATF5
#define R3_PORT               PORTFbits.RF5
#define R3_ANS                ANCON1bits.ANSEL10
#define R3_SetHigh()            do { LATFbits.LATF5 = 1; } while(0)
#define R3_SetLow()             do { LATFbits.LATF5 = 0; } while(0)
#define R3_Toggle()             do { LATFbits.LATF5 = ~LATFbits.LATF5; } while(0)
#define R3_GetValue()           PORTFbits.RF5
#define R3_SetDigitalInput()    do { TRISFbits.TRISF5 = 1; } while(0)
#define R3_SetDigitalOutput()   do { TRISFbits.TRISF5 = 0; } while(0)
#define R3_SetAnalogMode()  do { ANCON1bits.ANSEL10 = 1; } while(0)
#define R3_SetDigitalMode() do { ANCON1bits.ANSEL10 = 0; } while(0)

// get/set R4 aliases
#define R4_TRIS               TRISFbits.TRISF6
#define R4_LAT                LATFbits.LATF6
#define R4_PORT               PORTFbits.RF6
#define R4_ANS                ANCON1bits.ANSEL11
#define R4_SetHigh()            do { LATFbits.LATF6 = 1; } while(0)
#define R4_SetLow()             do { LATFbits.LATF6 = 0; } while(0)
#define R4_Toggle()             do { LATFbits.LATF6 = ~LATFbits.LATF6; } while(0)
#define R4_GetValue()           PORTFbits.RF6
#define R4_SetDigitalInput()    do { TRISFbits.TRISF6 = 1; } while(0)
#define R4_SetDigitalOutput()   do { TRISFbits.TRISF6 = 0; } while(0)
#define R4_SetAnalogMode()  do { ANCON1bits.ANSEL11 = 1; } while(0)
#define R4_SetDigitalMode() do { ANCON1bits.ANSEL11 = 0; } while(0)

// get/set R5 aliases
#define R5_TRIS               TRISFbits.TRISF7
#define R5_LAT                LATFbits.LATF7
#define R5_PORT               PORTFbits.RF7
#define R5_ANS                ANCON0bits.ANSEL5
#define R5_SetHigh()            do { LATFbits.LATF7 = 1; } while(0)
#define R5_SetLow()             do { LATFbits.LATF7 = 0; } while(0)
#define R5_Toggle()             do { LATFbits.LATF7 = ~LATFbits.LATF7; } while(0)
#define R5_GetValue()           PORTFbits.RF7
#define R5_SetDigitalInput()    do { TRISFbits.TRISF7 = 1; } while(0)
#define R5_SetDigitalOutput()   do { TRISFbits.TRISF7 = 0; } while(0)
#define R5_SetAnalogMode()  do { ANCON0bits.ANSEL5 = 1; } while(0)
#define R5_SetDigitalMode() do { ANCON0bits.ANSEL5 = 0; } while(0)

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