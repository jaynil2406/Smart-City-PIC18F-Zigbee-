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

// get/set KEY1 aliases
#define KEY1_TRIS               TRISAbits.TRISA0
#define KEY1_LAT                LATAbits.LATA0
#define KEY1_PORT               PORTAbits.RA0
#define KEY1_ANS                ANCON0bits.ANSEL0
#define KEY1_SetHigh()            do { LATAbits.LATA0 = 1; } while(0)
#define KEY1_SetLow()             do { LATAbits.LATA0 = 0; } while(0)
#define KEY1_Toggle()             do { LATAbits.LATA0 = ~LATAbits.LATA0; } while(0)
#define KEY1_GetValue()           PORTAbits.RA0
#define KEY1_SetDigitalInput()    do { TRISAbits.TRISA0 = 1; } while(0)
#define KEY1_SetDigitalOutput()   do { TRISAbits.TRISA0 = 0; } while(0)
#define KEY1_SetAnalogMode()  do { ANCON0bits.ANSEL0 = 1; } while(0)
#define KEY1_SetDigitalMode() do { ANCON0bits.ANSEL0 = 0; } while(0)

// get/set KEY2 aliases
#define KEY2_TRIS               TRISAbits.TRISA1
#define KEY2_LAT                LATAbits.LATA1
#define KEY2_PORT               PORTAbits.RA1
#define KEY2_ANS                ANCON0bits.ANSEL1
#define KEY2_SetHigh()            do { LATAbits.LATA1 = 1; } while(0)
#define KEY2_SetLow()             do { LATAbits.LATA1 = 0; } while(0)
#define KEY2_Toggle()             do { LATAbits.LATA1 = ~LATAbits.LATA1; } while(0)
#define KEY2_GetValue()           PORTAbits.RA1
#define KEY2_SetDigitalInput()    do { TRISAbits.TRISA1 = 1; } while(0)
#define KEY2_SetDigitalOutput()   do { TRISAbits.TRISA1 = 0; } while(0)
#define KEY2_SetAnalogMode()  do { ANCON0bits.ANSEL1 = 1; } while(0)
#define KEY2_SetDigitalMode() do { ANCON0bits.ANSEL1 = 0; } while(0)

// get/set KEY3 aliases
#define KEY3_TRIS               TRISAbits.TRISA2
#define KEY3_LAT                LATAbits.LATA2
#define KEY3_PORT               PORTAbits.RA2
#define KEY3_ANS                ANCON0bits.ANSEL2
#define KEY3_SetHigh()            do { LATAbits.LATA2 = 1; } while(0)
#define KEY3_SetLow()             do { LATAbits.LATA2 = 0; } while(0)
#define KEY3_Toggle()             do { LATAbits.LATA2 = ~LATAbits.LATA2; } while(0)
#define KEY3_GetValue()           PORTAbits.RA2
#define KEY3_SetDigitalInput()    do { TRISAbits.TRISA2 = 1; } while(0)
#define KEY3_SetDigitalOutput()   do { TRISAbits.TRISA2 = 0; } while(0)
#define KEY3_SetAnalogMode()  do { ANCON0bits.ANSEL2 = 1; } while(0)
#define KEY3_SetDigitalMode() do { ANCON0bits.ANSEL2 = 0; } while(0)

// get/set KEY4 aliases
#define KEY4_TRIS               TRISAbits.TRISA3
#define KEY4_LAT                LATAbits.LATA3
#define KEY4_PORT               PORTAbits.RA3
#define KEY4_ANS                ANCON0bits.ANSEL3
#define KEY4_SetHigh()            do { LATAbits.LATA3 = 1; } while(0)
#define KEY4_SetLow()             do { LATAbits.LATA3 = 0; } while(0)
#define KEY4_Toggle()             do { LATAbits.LATA3 = ~LATAbits.LATA3; } while(0)
#define KEY4_GetValue()           PORTAbits.RA3
#define KEY4_SetDigitalInput()    do { TRISAbits.TRISA3 = 1; } while(0)
#define KEY4_SetDigitalOutput()   do { TRISAbits.TRISA3 = 0; } while(0)
#define KEY4_SetAnalogMode()  do { ANCON0bits.ANSEL3 = 1; } while(0)
#define KEY4_SetDigitalMode() do { ANCON0bits.ANSEL3 = 0; } while(0)

// get/set RB0 procedures
#define RB0_SetHigh()    do { LATBbits.LATB0 = 1; } while(0)
#define RB0_SetLow()   do { LATBbits.LATB0 = 0; } while(0)
#define RB0_Toggle()   do { LATBbits.LATB0 = ~LATBbits.LATB0; } while(0)
#define RB0_GetValue()         PORTBbits.RB0
#define RB0_SetDigitalInput()   do { TRISBbits.TRISB0 = 1; } while(0)
#define RB0_SetDigitalOutput()  do { TRISBbits.TRISB0 = 0; } while(0)

// get/set RST aliases
#define RST_TRIS               TRISCbits.TRISC6
#define RST_LAT                LATCbits.LATC6
#define RST_PORT               PORTCbits.RC6
#define RST_SetHigh()            do { LATCbits.LATC6 = 1; } while(0)
#define RST_SetLow()             do { LATCbits.LATC6 = 0; } while(0)
#define RST_Toggle()             do { LATCbits.LATC6 = ~LATCbits.LATC6; } while(0)
#define RST_GetValue()           PORTCbits.RC6
#define RST_SetDigitalInput()    do { TRISCbits.TRISC6 = 1; } while(0)
#define RST_SetDigitalOutput()   do { TRISCbits.TRISC6 = 0; } while(0)

// get/set CS aliases
#define CS_TRIS               TRISEbits.TRISE2
#define CS_LAT                LATEbits.LATE2
#define CS_PORT               PORTEbits.RE2
#define CS_SetHigh()            do { LATEbits.LATE2 = 1; } while(0)
#define CS_SetLow()             do { LATEbits.LATE2 = 0; } while(0)
#define CS_Toggle()             do { LATEbits.LATE2 = ~LATEbits.LATE2; } while(0)
#define CS_GetValue()           PORTEbits.RE2
#define CS_SetDigitalInput()    do { TRISEbits.TRISE2 = 1; } while(0)
#define CS_SetDigitalOutput()   do { TRISEbits.TRISE2 = 0; } while(0)

// get/set WAKE aliases
#define WAKE_TRIS               TRISGbits.TRISG3
#define WAKE_LAT                LATGbits.LATG3
#define WAKE_PORT               PORTGbits.RG3
#define WAKE_ANS                ANCON2bits.ANSEL17
#define WAKE_SetHigh()            do { LATGbits.LATG3 = 1; } while(0)
#define WAKE_SetLow()             do { LATGbits.LATG3 = 0; } while(0)
#define WAKE_Toggle()             do { LATGbits.LATG3 = ~LATGbits.LATG3; } while(0)
#define WAKE_GetValue()           PORTGbits.RG3
#define WAKE_SetDigitalInput()    do { TRISGbits.TRISG3 = 1; } while(0)
#define WAKE_SetDigitalOutput()   do { TRISGbits.TRISG3 = 0; } while(0)
#define WAKE_SetAnalogMode()  do { ANCON2bits.ANSEL17 = 1; } while(0)
#define WAKE_SetDigitalMode() do { ANCON2bits.ANSEL17 = 0; } while(0)

// get/set IO_RG4 aliases
#define IO_RG4_TRIS               TRISGbits.TRISG4
#define IO_RG4_LAT                LATGbits.LATG4
#define IO_RG4_PORT               PORTGbits.RG4
#define IO_RG4_ANS                ANCON2bits.ANSEL16
#define IO_RG4_SetHigh()            do { LATGbits.LATG4 = 1; } while(0)
#define IO_RG4_SetLow()             do { LATGbits.LATG4 = 0; } while(0)
#define IO_RG4_Toggle()             do { LATGbits.LATG4 = ~LATGbits.LATG4; } while(0)
#define IO_RG4_GetValue()           PORTGbits.RG4
#define IO_RG4_SetDigitalInput()    do { TRISGbits.TRISG4 = 1; } while(0)
#define IO_RG4_SetDigitalOutput()   do { TRISGbits.TRISG4 = 0; } while(0)
#define IO_RG4_SetAnalogMode()  do { ANCON2bits.ANSEL16 = 1; } while(0)
#define IO_RG4_SetDigitalMode() do { ANCON2bits.ANSEL16 = 0; } while(0)

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