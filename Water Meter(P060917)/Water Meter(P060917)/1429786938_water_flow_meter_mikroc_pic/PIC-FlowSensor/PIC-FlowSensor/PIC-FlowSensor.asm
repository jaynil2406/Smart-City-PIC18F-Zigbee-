
_main:
;PIC-FlowSensor.c,19 :: 		void main()
;PIC-FlowSensor.c,24 :: 		ANSELA = 0;                       // Configure PORTA pins as digital
	CLRF        ANSELA+0 
;PIC-FlowSensor.c,25 :: 		ANSELB = 0;                       // Configure PORTB pins as digital
	CLRF        ANSELB+0 
;PIC-FlowSensor.c,26 :: 		ANSELC = 0;                       // Configure PORTC pins as digital
	CLRF        ANSELC+0 
;PIC-FlowSensor.c,27 :: 		ADCON0 = 0;                       // A/D off
	CLRF        ADCON0+0 
;PIC-FlowSensor.c,28 :: 		ADCON1 = 0x0f;                    // all digital
	MOVLW       15
	MOVWF       ADCON1+0 
;PIC-FlowSensor.c,29 :: 		CM1CON0 = 0;                      // disable 18F46K22 comparator
	CLRF        CM1CON0+0 
;PIC-FlowSensor.c,30 :: 		CM2CON0 = 0;                      // disable 18F46K22 comparator
	CLRF        CM2CON0+0 
;PIC-FlowSensor.c,31 :: 		TRISB = 0;                        // PORTB is output
	CLRF        TRISB+0 
;PIC-FlowSensor.c,32 :: 		PORTB = 0x00;                     // Initialize PORTB
	CLRF        PORTB+0 
;PIC-FlowSensor.c,33 :: 		LATA = 0;                         // all off
	CLRF        LATA+0 
;PIC-FlowSensor.c,34 :: 		LATC = 0;                         // all off
	CLRF        LATC+0 
;PIC-FlowSensor.c,35 :: 		TRISA = 0xC0;                     // all output except OSC pins
	MOVLW       192
	MOVWF       TRISA+0 
;PIC-FlowSensor.c,36 :: 		TRISB = 0x00;                     // all output
	CLRF        TRISB+0 
;PIC-FlowSensor.c,37 :: 		TRISC = 0x01;                     // all output except RC0
	MOVLW       1
	MOVWF       TRISC+0 
;PIC-FlowSensor.c,38 :: 		Delay_ms(100);                    // Wait for LCD to stabilise
	MOVLW       3
	MOVWF       R11, 0
	MOVLW       138
	MOVWF       R12, 0
	MOVLW       85
	MOVWF       R13, 0
L_main0:
	DECFSZ      R13, 1, 0
	BRA         L_main0
	DECFSZ      R12, 1, 0
	BRA         L_main0
	DECFSZ      R11, 1, 0
	BRA         L_main0
	NOP
	NOP
;PIC-FlowSensor.c,39 :: 		Lcd_Init();                          // Initialize Lcd
	CALL        _Lcd_Init+0, 0
;PIC-FlowSensor.c,40 :: 		Lcd_Cmd(_LCD_CLEAR);                 // Clear display
	MOVLW       1
	MOVWF       FARG_Lcd_Cmd_out_char+0 
	CALL        _Lcd_Cmd+0, 0
;PIC-FlowSensor.c,41 :: 		Lcd_Cmd(_LCD_CURSOR_OFF);            // Turn cursor off
	MOVLW       12
	MOVWF       FARG_Lcd_Cmd_out_char+0 
	CALL        _Lcd_Cmd+0, 0
;PIC-FlowSensor.c,42 :: 		Lcd_Out(1,1,"FR:          L/m");    // Print text to Lcd, 2nd row, 1st column
	MOVLW       1
	MOVWF       FARG_Lcd_Out_row+0 
	MOVLW       1
	MOVWF       FARG_Lcd_Out_column+0 
	MOVLW       ?lstr1_PIC-FlowSensor+0
	MOVWF       FARG_Lcd_Out_text+0 
	MOVLW       hi_addr(?lstr1_PIC-FlowSensor+0
	MOVWF       FARG_Lcd_Out_text+1 
	CALL        _Lcd_Out+0, 0
;PIC-FlowSensor.c,43 :: 		UART1_Init(9615);                    //Initialize UART module
	MOVLW       129
	MOVWF       SPBRG+0 
	BSF         TXSTA+0, 2, 0
	CALL        _UART1_Init+0, 0
;PIC-FlowSensor.c,44 :: 		Delay_ms(20);
	MOVLW       130
	MOVWF       R12, 0
	MOVLW       221
	MOVWF       R13, 0
L_main1:
	DECFSZ      R13, 1, 0
	BRA         L_main1
	DECFSZ      R12, 1, 0
	BRA         L_main1
	NOP
	NOP
;PIC-FlowSensor.c,45 :: 		UART1_Write_Text("Start");
	MOVLW       ?lstr2_PIC-FlowSensor+0
	MOVWF       FARG_UART1_Write_Text_uart_text+0 
	MOVLW       hi_addr(?lstr2_PIC-FlowSensor+0
	MOVWF       FARG_UART1_Write_Text_uart_text+1 
	CALL        _UART1_Write_Text+0, 0
;PIC-FlowSensor.c,46 :: 		UART1_Write(13);
	MOVLW       13
	MOVWF       FARG_UART1_Write_data_+0 
	CALL        _UART1_Write+0, 0
;PIC-FlowSensor.c,47 :: 		UART1_Write(10);
	MOVLW       10
	MOVWF       FARG_UART1_Write_data_+0 
	CALL        _UART1_Write+0, 0
;PIC-FlowSensor.c,48 :: 		T0CON = 0x86;                     // T0 on, 16 bit, prescaler 128
	MOVLW       134
	MOVWF       T0CON+0 
;PIC-FlowSensor.c,49 :: 		T1CON = 0x85;                     // T1 on, ext input, no prescale
	MOVLW       133
	MOVWF       T1CON+0 
;PIC-FlowSensor.c,50 :: 		T1GCON = 0x00;                    // no gating
	CLRF        T1GCON+0 
;PIC-FlowSensor.c,51 :: 		while(1){
L_main2:
;PIC-FlowSensor.c,52 :: 		TMR0H = 0x0b;                 // Timer set for 999856us
	MOVLW       11
	MOVWF       TMR0H+0 
;PIC-FlowSensor.c,53 :: 		TMR0L = 0xe5;
	MOVLW       229
	MOVWF       TMR0L+0 
;PIC-FlowSensor.c,54 :: 		INTCON.TMR0IF = 0;            // reset time-out indicator
	BCF         INTCON+0, 2 
;PIC-FlowSensor.c,55 :: 		frequency = 0;                // initialise count
	CLRF        main_frequency_L0+0 
	CLRF        main_frequency_L0+1 
	CLRF        main_frequency_L0+2 
	CLRF        main_frequency_L0+3 
;PIC-FlowSensor.c,56 :: 		TMR1L = 0;                    // reset to 0
	CLRF        TMR1L+0 
;PIC-FlowSensor.c,57 :: 		TMR1H = 0;                    // reset to 0
	CLRF        TMR1H+0 
;PIC-FlowSensor.c,58 :: 		PIR1.TMR1IF = 0;              // initialise
	BCF         PIR1+0, 0 
;PIC-FlowSensor.c,59 :: 		while(!INTCON.TMR0IF){        // wait for 1 second time-out
L_main4:
	BTFSC       INTCON+0, 2 
	GOTO        L_main5
;PIC-FlowSensor.c,60 :: 		if(PIR1.TMR1IF){          // monitor frequency count overflow
	BTFSS       PIR1+0, 0 
	GOTO        L_main6
;PIC-FlowSensor.c,61 :: 		PIR1.TMR1IF=0;        // reset overflow
	BCF         PIR1+0, 0 
;PIC-FlowSensor.c,62 :: 		frequency += 65536;   // increment count high bytes
	MOVLW       0
	ADDWF       main_frequency_L0+0, 1 
	MOVLW       0
	ADDWFC      main_frequency_L0+1, 1 
	MOVLW       1
	ADDWFC      main_frequency_L0+2, 1 
	MOVLW       0
	ADDWFC      main_frequency_L0+3, 1 
;PIC-FlowSensor.c,63 :: 		}
L_main6:
;PIC-FlowSensor.c,64 :: 		}
	GOTO        L_main4
L_main5:
;PIC-FlowSensor.c,65 :: 		freq_low = (TMR1H << 8) + TMR1L;  // collect frequency bytes
	MOVF        TMR1H+0, 0 
	MOVWF       main_freq_low_L0+1 
	CLRF        main_freq_low_L0+0 
	CLRF        main_freq_low_L0+2 
	CLRF        main_freq_low_L0+3 
	MOVLW       0
	MOVWF       main_freq_low_L0+2 
	MOVWF       main_freq_low_L0+3 
	MOVF        TMR1L+0, 0 
	ADDWF       main_freq_low_L0+0, 1 
	MOVLW       0
	ADDWFC      main_freq_low_L0+1, 1 
	MOVLW       0
	MOVWF       main_freq_low_L0+2 
	MOVWF       main_freq_low_L0+3 
;PIC-FlowSensor.c,66 :: 		frequency += freq_low;            // collect frequency bytes
	MOVF        main_freq_low_L0+0, 0 
	ADDWF       main_frequency_L0+0, 0 
	MOVWF       R0 
	MOVF        main_freq_low_L0+1, 0 
	ADDWFC      main_frequency_L0+1, 0 
	MOVWF       R1 
	MOVF        main_freq_low_L0+2, 0 
	ADDWFC      main_frequency_L0+2, 0 
	MOVWF       R2 
	MOVF        main_freq_low_L0+3, 0 
	ADDWFC      main_frequency_L0+3, 0 
	MOVWF       R3 
	MOVF        R0, 0 
	MOVWF       main_frequency_L0+0 
	MOVF        R1, 0 
	MOVWF       main_frequency_L0+1 
	MOVF        R2, 0 
	MOVWF       main_frequency_L0+2 
	MOVF        R3, 0 
	MOVWF       main_frequency_L0+3 
;PIC-FlowSensor.c,67 :: 		flowrate=frequency/7.5;           //Obtain flow rate from frequency (7.5 from datasheet of flow sensor) for L/Hour * 60 & for L/sec / by 60
	CALL        _Longword2Double+0, 0
	MOVLW       0
	MOVWF       R4 
	MOVLW       0
	MOVWF       R5 
	MOVLW       112
	MOVWF       R6 
	MOVLW       129
	MOVWF       R7 
	CALL        _Div_32x32_FP+0, 0
	CALL        _Double2Longword+0, 0
;PIC-FlowSensor.c,68 :: 		LongWordToStr(flowrate,flowratetext);  //Convert integer to String
	MOVF        R0, 0 
	MOVWF       FARG_LongWordToStr_input+0 
	MOVF        R1, 0 
	MOVWF       FARG_LongWordToStr_input+1 
	MOVF        R2, 0 
	MOVWF       FARG_LongWordToStr_input+2 
	MOVF        R3, 0 
	MOVWF       FARG_LongWordToStr_input+3 
	MOVLW       main_flowratetext_L0+0
	MOVWF       FARG_LongWordToStr_output+0 
	MOVLW       hi_addr(main_flowratetext_L0+0
	MOVWF       FARG_LongWordToStr_output+1 
	CALL        _LongWordToStr+0, 0
;PIC-FlowSensor.c,69 :: 		Lcd_Out(1,4,flowratetext);
	MOVLW       1
	MOVWF       FARG_Lcd_Out_row+0 
	MOVLW       4
	MOVWF       FARG_Lcd_Out_column+0 
	MOVLW       main_flowratetext_L0+0
	MOVWF       FARG_Lcd_Out_text+0 
	MOVLW       hi_addr(main_flowratetext_L0+0
	MOVWF       FARG_Lcd_Out_text+1 
	CALL        _Lcd_Out+0, 0
;PIC-FlowSensor.c,70 :: 		UART1_write_text(flowratetext);
	MOVLW       main_flowratetext_L0+0
	MOVWF       FARG_UART1_Write_Text_uart_text+0 
	MOVLW       hi_addr(main_flowratetext_L0+0
	MOVWF       FARG_UART1_Write_Text_uart_text+1 
	CALL        _UART1_Write_Text+0, 0
;PIC-FlowSensor.c,71 :: 		}
	GOTO        L_main2
;PIC-FlowSensor.c,72 :: 		}
	GOTO        $+0
; end of _main
