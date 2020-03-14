/*
 * File:   10_April_WateMeterMain.c
 * Author: DiXiT
 *
 * Created on April 10, 2018, 3:17 PM
 */


#include "mcc_generated_files/mcc.h"
#include "zigbee.h"


void main(void) {
    Delay_ms(500);Delay_ms(500);Delay_ms(500);Delay_ms(500);Delay_ms(500);
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
    SerInit();
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
    ds = 10;
    return;
}
