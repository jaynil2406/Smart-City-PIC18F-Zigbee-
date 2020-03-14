#include "mcc_generated_files/mcc.h"
#include "zigbee.h"

void Clear_Data(void){
    unsigned int n=0;
    for(n=0;n<=5;n++){
        DATA_RX[n]=0;
    }
}

void read_RX_FIFO(void)
{ 
	unsigned char temp = 0; 
	unsigned char i = 0; 
	
	temp=0;
	temp = temp | 0x04;                    // mask for disable receiving packets 
  	write_ZIGBEE_short(BBREG1, temp); 

	LENGTH=read_ZIGBEE_long(0x300);
	Nop();
	for(i=0; i<128; i++) 
  	{ 
   		if(i <  (1 + DATA_LENGHT + HEADER_LENGHT + 2 + 1 + 1)) 
     		data_RX_FIFO[i] = read_ZIGBEE_long(address_RX_FIFO + i);  // reading valid data from RX FIFO 
   		if(i >= (1 + DATA_LENGHT + HEADER_LENGHT + 2 + 1 + 1)) 
     		lost_data = read_ZIGBEE_long(address_RX_FIFO + i);        // reading invalid data from RX FIFO 
  	} 

  	DATA_RX[0] = data_RX_FIFO[HEADER_LENGHT + 1];               // coping valid data 
  	DATA_RX[1] = data_RX_FIFO[HEADER_LENGHT + 2];               // coping valid data 
  	DATA_RX[2] = data_RX_FIFO[HEADER_LENGHT + 3];               // coping valid data 
  	
    DATA_RX[3] = data_RX_FIFO[HEADER_LENGHT + 4];               // coping valid data
    DATA_RX[4] = data_RX_FIFO[HEADER_LENGHT + 5];               // coping valid data
  
    
    
    LQI   = data_RX_FIFO[1 + HEADER_LENGHT + DATA_LENGHT + 2];  // coping valid data 
  	RSSI2 = data_RX_FIFO[1 + HEADER_LENGHT + DATA_LENGHT + 3];  // coping valid data 

	temp=0;
  	temp = temp & (!0x04);                 // mask for enable receiving 
  	write_ZIGBEE_short(BBREG1, temp); 
} 
 
void pin_reset(void){ 
	RST=0;
	Delay_ms(10); 
	RST=1;
	Delay_ms(10); 
}
void RF_reset(void){                  
	write_ZIGBEE_short(RFCTL,0x04); 	//mask for RFRST bit  
	write_ZIGBEE_short(RFCTL,(!0x04)); 	//mask for RFRST bit 
	Delay_ms(20); 
}
void set_WAKE_from_pin(void) { 
	WAKE=0;// Wake Pin is Low                   
	write_ZIGBEE_short(RXFLUSH,0x60); 
  	write_ZIGBEE_short(WAKECON,0x80);//Immediate Wake Up Mode Enable  
}
void set_long_address(unsigned char * address){ 
	unsigned char i = 0;
	for(i = 0; i < 8; i++) 
  		write_ZIGBEE_short(EADR0 + i, address[i]);   // 0x05 address of EADR0 
}
void set_short_address(unsigned char * address){ 
	write_ZIGBEE_short(SADRL, address[0]); 
	write_ZIGBEE_short(SADRH, address[1]); 
}
void set_PAN_ID(unsigned char * address){ 
	write_ZIGBEE_short(PANIDL, address[0]); 
	write_ZIGBEE_short(PANIDH, address[1]); 
}
void init_ZIGBEE_nonbeacon(void){ 
	init_ZIGBEE_basic(); 
 	set_CCA_mode(1);     // Set CCA mode to ED and set threshold 
 	set_RSSI_mode(2);    // RSSI2 mode 
 	enable_interrupt();  // Enables all interrupts 
 	set_channel(15);     // Channel 11 
 	pin_wake();                             // Wake from pin 
 	RF_reset();
}
//Init ZIGBEE module 
void init_ZIGBEE_basic(void){ 
	write_ZIGBEE_short(PACON2, 0x98);   // Initialize FIFOEN = 1 and TXONTS = 0x6 
	write_ZIGBEE_short(TXSTBL, 0x95);   // Initialize RFSTBL = 0x9 
	write_ZIGBEE_long(RFCON1, 0x01);    // Initialize VCOOPT = 0x01 
	enable_PLL();                       // Enable PLL (PLLEN = 1) 
	write_ZIGBEE_long(RFCON6, 0x90);    // Initialize TXFIL = 1 and 20MRECVR = 1 
	write_ZIGBEE_long(RFCON7, 0x80);    // Initialize SLPCLKSEL = 0x2 (100 kHz Internal oscillator) 
	write_ZIGBEE_long(RFCON8, 0x10);    // Initialize RFVCO = 1 
	write_ZIGBEE_short(SLPCON0,0X02);
    write_ZIGBEE_long(SLPCON1, 0x21);   // Initialize CLKOUTEN = 1 and SLPCLKDIV = 0x01 
    write_ZIGBEE_long(TESTMODE, 0x0F);   // RSSIWAIT<1:0>: 111= GPIO0, GPIO1 andGPIO2 are configured to control an external PA and/or LNA
    
} 
// PLL 
void enable_PLL(void){ 
   write_ZIGBEE_long(RFCON2, 0x80);    // mask for PLL enable 
}
void set_CCA_mode(unsigned char CCA_mode)
{
	unsigned char temp = 0; 
	switch(CCA_mode)
	{ 
		case 1:                //ENERGY ABOVE THRESHOLD 
		{ 
			temp=0;
			temp = temp | 0x80;              //0x80 mask 
            temp = temp & 0xDF;              //0xDF mask 
            write_ZIGBEE_short(BBREG2, temp); 
            write_ZIGBEE_short(CCAEDTH, 0x60);//Set CCA ED threshold to -69 dBm 
        } 
        break; 

        case 2:                //CARRIER SENSE ONLY 
        { 
        	temp=0;
        	temp = temp | 0x40;               // 0x40 mask 
            temp = temp & 0x7F;               // 0x7F mask 
            write_ZIGBEE_short(BBREG2, temp); 
        
            temp=0;
            temp = temp | 0x38; 
            temp = temp & 0xFB; 
            write_ZIGBEE_short(BBREG2, temp); 
        } 
        break; 

        case 3:                //CARRIER SENSE AND ENERGY ABOVE THRESHOLD 
        { 
        	temp=0;
        	temp = temp | 0xC0;                //0xC0 mask 
            write_ZIGBEE_short(BBREG2, temp); 

        	temp=0;
            temp = temp | 0x38;                   // 0x38 mask 
            temp = temp & 0xFB;                   // 0xFB mask 
            write_ZIGBEE_short(BBREG2, temp); 

            write_ZIGBEE_short(CCAEDTH, 0x60);    //Set CCA ED threshold to -69 dBm 
        } 
        break; 
	} 
} 
//Set RSSI mode
//1 for RSSI1, 2 for RSSI2 mode   
void set_RSSI_mode(unsigned char RSSI_mode)
{        
	unsigned char temp = 0; 
	switch(RSSI_mode)
	{ 
		case 1: 
    	{ 
			temp=0;   
      		temp = temp | 0x80;               //0x80 mask for RSSI1 mode 
      		write_ZIGBEE_short(BBREG6, temp); 
    	} 
    	break; 
		
		case 2: 
    		write_ZIGBEE_short(BBREG6, 0x40);   //0x40 data for RSSI2 mode 
    	break; 
  	} 
}
void enable_interrupt(void) { 
	write_ZIGBEE_short(INTCON_M, 0xF7);  //0x00  all interrupts are enable 	
	
}  
void set_channel(unsigned char channel_number)
{               
	if((channel_number > 26) || (channel_number < 11)) 
		channel_number = 11; 

	switch(channel_number)
	{ 
    	case 11: 
    		write_ZIGBEE_long(RFCON0, 0x02);  //0x02 for 11. channel 
    	break; 
    	
    	case 12: 
    		write_ZIGBEE_long(RFCON0, 0x12);  //0x12 for 12. channel 
    	break; 
    
    	case 13: 
    		write_ZIGBEE_long(RFCON0, 0x22);  //0x22 for 13. channel 
    	break; 
    	case 14: 
    		write_ZIGBEE_long(RFCON0, 0x32);  //0x32 for 14. channel 
   	 	break; 
    	case 15: 
    		write_ZIGBEE_long(RFCON0, 0x42);  //0x42 for 15. channel 
    	break; 
    	case 16: 
   	 		write_ZIGBEE_long(RFCON0, 0x52);  //0x52 for 16. channel 
    	break; 
    	case 17: 
    		write_ZIGBEE_long(RFCON0, 0x62);  //0x62 for 17. channel 
    	break; 
    	case 18: 
    		write_ZIGBEE_long(RFCON0, 0x72);  //0x72 for 18. channel 
    	break; 
    	case 19: 
    		write_ZIGBEE_long(RFCON0, 0x82);  //0x82 for 19. channel 
    	break; 
    	case 20: 
    		write_ZIGBEE_long(RFCON0, 0x92);  //0x92 for 20. channel 
    	break; 
    	case 21: 
    		write_ZIGBEE_long(RFCON0, 0xA2);  //0xA2 for 21. channel 
    	break; 
    	case 22: 
    		write_ZIGBEE_long(RFCON0, 0xB2);  //0xB2 for 22. channel 
    	break; 
    	case 23: 
   	 		write_ZIGBEE_long(RFCON0, 0xC2);  //0xC2 for 23. channel 
    	break; 
    	case 24: 
    		write_ZIGBEE_long(RFCON0, 0xD2);  //0xD2 for 24. channel 
    	break; 
   	 	case 25: 
    		write_ZIGBEE_long(RFCON0, 0xE2);  //0xE2 for 25. channel 
    	break; 
    	case 26: 
    		write_ZIGBEE_long(RFCON0, 0xF2);  //0xF2 for 26. channel 
    	break; 
  	} 
	RF_reset(); 
} 
void pin_wake(void) { 
	WAKE=1; 
	Delay_ms(10); 
}
void nonbeacon_PAN_coordinator_device(void){ 
	unsigned char temp = 0; 

	temp=0;
	temp = temp | 0x08;                 // 0x08 mask for PAN coordinator 
  	write_ZIGBEE_short(RXMCR, temp); 

 	temp=0;
 	temp = temp & 0xDF;                 // 0xDF mask for CSMA-CA mode 
  	write_ZIGBEE_short(TXMCR, temp); 

  	write_ZIGBEE_short(ORDER, 0xFF);    // BO, SO are 15 
}

// Tx power 
// 0-31 possible variants 
void set_TX_power(unsigned char power){
	if((power < 0) || (power > 31)) 
		power = 31; 
	
	power = 31 - power;                              //0 max, 31 min -> 31 max, 0 min 
	power = ((power & 0b00011111) << 3) & 0b11111000;// calculating power 
	write_ZIGBEE_long(RFCON3, power); 
} 

// Frame format filter 
// 1 all frames, 2 command only, 3 data only, 4 beacon only 
void set_frame_format_filter(unsigned char fff_mode)
{ 
	unsigned char temp = 0; 
	switch(fff_mode) 
  	{ 
   		case 1: 
   		{ 
	   		temp=0;
	   		temp = temp & (!0x0E);                  // mask for all frames 
    		write_ZIGBEE_short(RXFLUSH, temp); 
   		} 
   		break; 
   		case 2: 
   		{ 
	   		temp=0;
	   		temp = temp & (!0x06);                  // mask for command only 
    		temp = temp | 0x08;                     // mask for command only 
    		write_ZIGBEE_short(RXFLUSH, temp); 
   		} 
   		break; 
		case 3: 
   		{ 
 			temp=0;
 			temp = temp & (!0x0A);                  // mask for data only 
    		temp = temp | 0x04;                     // mask for data only 
    		write_ZIGBEE_short(RXFLUSH, temp); 
   		} 
   		break; 
		
		case 4: 
   		{ 
	   		temp=0;
	   		temp = temp & (!0x0C);                  // mask for beacon only 
    		temp = temp | 0x02;                     // mask for beacon only 
    		write_ZIGBEE_short(RXFLUSH, temp); 
   		} 
   		break; 
  	} 
} 
// Reception mode 
// 1 normal, 2 error, 3 promiscuous mode 
void set_reception_mode(unsigned char r_mode)
{   
	unsigned char temp=0;
	switch(r_mode) 
  	{ 
   		case 1: 
   		{ 
			temp=0;
			temp = temp & (!0x03);          // mask for normal mode 
    		write_ZIGBEE_short(RXMCR, temp); 
   		} 
   		break; 

   		case 2: 
   		{ 
  			temp=0;
  			temp = temp & (!0x01);          // mask for error mode 
    		temp = temp | 0x02;             // mask for error mode 
    		write_ZIGBEE_short(RXMCR, temp); 
   		} 
   		break; 
		case 3: 
   		{ 
  			temp=0;
  			temp = temp & (!0x02);                // mask for promiscuous mode 
    		temp = temp | 0x01;                   // mask for promiscuous mode 
    		write_ZIGBEE_short(RXMCR, temp); 
   		} 
   	break; 
   	} 
}
void write_TX_normal_FIFO(void){ 
   unsigned char i = 0,n = 0; 
	
   data_TX_normal_FIFO[0]  = HEADER_LENGHT; 
   data_TX_normal_FIFO[1]  = HEADER_LENGHT + DATA_LENGHT; 
   data_TX_normal_FIFO[2]  = 0x01;                     // control frame  
   data_TX_normal_FIFO[3]  = 0x88; 
   data_TX_normal_FIFO[4]  = SEQ_NUMBER;               // sequence number 
   data_TX_normal_FIFO[5]  = PAN_ID_2[1];              // destinatoin pan 
   data_TX_normal_FIFO[6]  = PAN_ID_2[0]; 
   data_TX_normal_FIFO[7]  = ADDRESS_short_2[0];       // destination address  
   data_TX_normal_FIFO[8]  = ADDRESS_short_2[1];  
   data_TX_normal_FIFO[9]  = PAN_ID_1[0];              // source pan 
   data_TX_normal_FIFO[10] = PAN_ID_1[1]; 
   data_TX_normal_FIFO[11] = ADDRESS_short_1[0];       // source address 
   data_TX_normal_FIFO[12] = ADDRESS_short_1[1]; 

   for(n=0,ii=13;n<NUM;n++,ii++){
       DATA_TX[n] = data_TX_normal_FIFO[ii];
   }
   TX_CRC = Xor_check(DATA_TX,NUM);
   data_TX_normal_FIFO[NUM + 12 + 1] = (TX_CRC & 0x00FF);
   data_TX_normal_FIFO[NUM + 12 + 2] = ( (TX_CRC & 0xFF00) >> 8 );
   
	
   for(i = 0; i < (HEADER_LENGHT + DATA_LENGHT + 2); i++) 
   { 
		write_ZIGBEE_long(address_TX_normal_FIFO + i, data_TX_normal_FIFO[i]); // write frame into normal FIFO 
   		Delay_ms(10);
   } 
   set_not_ACK(); 
   set_not_encrypt(); 
   start_transmit();
} 

void set_not_ACK(void)
{ 
	unsigned char temp = 0; 
	temp = temp & (!0x04); //0x04 mask for set not ACK 
	write_ZIGBEE_short(TXNCON, temp); 
}  
void set_not_encrypt(void)
{ 
	unsigned char temp = 0; 
	temp = temp & (!0x02);                // mask for set not encrypt 
	write_ZIGBEE_short(TXNCON, temp); 
} 
//Transmit packet  
void start_transmit(void)
{ 
	CHECK=0;
	CHECK = CHECK | 0x01;                // mask for start transmit 
	write_ZIGBEE_short(TXNCON,CHECK);
	
	CHECK=0;
	while(read_ZIGBEE_short(0x31)!=0x01);
	CHECK = read_ZIGBEE_short(INTSTAT);// CHECK WHETHER TRANSMISSION INTTRUPT OCCURED??
	Nop();
	CHECK = 0;
	CHECK = read_ZIGBEE_short(TXSTAT);// CHECK NUMBER OF TRANSMISSION
	Nop();
} 
void write_ZIGBEE_short( unsigned char address, unsigned char data_r){ 
	CS=0;
	address = ((address << 1) & 0b01111111) | 0x01; // calculating addressing mode 
 	SPI_Write(address);       // addressing register 
 	SPI_Write(data_r);        // write data in register 
 	CS=1;
} 
unsigned char read_ZIGBEE_short(unsigned char address) { 
	unsigned char data_r = 0;
	
	CS=0;
	address = (address << 1) & 0b01111110;      // calculating addressing mode 
 	SPI_Write(address);                        // addressing register 
 	data_r = SPI_Read();           // read data from register 
 	CS=1;
 	
 	return data_r; 
} 
void write_ZIGBEE_long(unsigned int address,unsigned char data_r){ 
 	unsigned char address_high = 0, address_low = 0; 
 
 	CS=0;
 	address_high = (((unsigned char)(address >> 3)) & 0b01111111) | 0x80;  // calculating addressing mode 
 	address_low  = (((unsigned char)(address << 5)) & 0b11100000) | 0x10;  // calculating addressing mode 
 	SPI_Write(address_high);           // addressing register 
 	SPI_Write(address_low);            // addressing register 
 	SPI_Write(data_r);
 	CS=1;                 // write data in registerr 
} 
unsigned char read_ZIGBEE_long(unsigned int address){ 
	unsigned char data_r = 0; 
 	unsigned char address_high = 0, address_low = 0; 

 
	CS=0;
 	address_high = ((unsigned char)(address >> 3) & 0b01111111) | 0x80;  //calculating addressing mode 
 	address_low  = ((unsigned char)(address << 5) & 0b11100000);         //calculating addressing mode 
 	SPI_Write(address_high);            // addressing register 
 	SPI_Write(address_low);             // addressing register 
 	data_r = SPI_Read();    // read data from register 	
 	CS=1;
 	return data_r; 
} 


void InitSPI(void){
    SSP1CON1bits.SSPM0 =  0;
	SSP1CON1bits.SSPM1 =  0;
	SSP1CON1bits.SSPM2 =  0;
	SSP1CON1bits.SSPM3 =  0;
	
	TRISCbits.TRISC5 = 0; // SDO
	TRISCbits.TRISC3 = 0; //SCK Master
	SSP1CON1bits.SSPEN = 1;
//	PIE1bits.SSPIE = 1;
	
	SSP1STATbits.SMP = 1; 
	SSP1CON1bits.CKP = 0;//ideal low state                 0
	SSP1STATbits.CKE = 1;//data transmitted on rising edge  1
	delay(10);
}
void SPI_Write( unsigned char command){
	unsigned  char response;
	SSP1BUF = command;   
   	while(!SSP1STATbits.BF); 
   	response = SSP1BUF;              
}
unsigned char SPI_Read( void ){
	unsigned char TempVar;
  	SSP1BUF = 0xff;
  	while(!SSP1STATbits.BF); 
  	TempVar = SSP1BUF;
  	PIR1bits.SSP1IF = 0;
  	return ( TempVar );  
}
void delay(unsigned int dly){
	unsigned int l;
	for(l=0;l<dly;l++);
}
void Delay_ms( unsigned int time){
	unsigned int x,y=0;
	while(++time < 10000);
}
void Delayms(unsigned int time)
{               
	int k,l;
    for(k=0;k<time;k++)
    for(l=0;l<=500;l++);
    Nop();
    Nop();
}
void Delaysec(unsigned int i){
	unsigned int x;
		for(x=0;x<i;x++)
		{
			Delayms1(250);
			Delayms1(250);
			Delayms1(250);
			Delayms1(250);
		}
}
void Delayms1(unsigned int time){                //Function to provide delay
	
	unsigned int i,j;
	for(i=0;i<time;i++)
    	for(j=0;j<=500;j++);
}
unsigned short Xor_check(unsigned char *data_value, unsigned char length)
{
	unsigned short xor_value = 0x8d0d;
	unsigned short xor=0x00;
	while(length --)
	{
		xor_value ^= *data_value++;
	}
	xor=xor_value;
	return(xor);
}
void Store_ID(){
	
	if(Read_b_eep(Store_DATA[0])==Store_DATA[0]){
	       data_TX_normal_FIFO[13]='#';
	       data_TX_normal_FIFO[14]='O';
	       
           Nop();
    }     
	else{
		  data_TX_normal_FIFO[13]='#';
	      data_TX_normal_FIFO[14]='O';
		  Write_b_eep(Store_DATA[0],Store_DATA[0]); 
          Store_DATA[0]=0xFF;
	}	   
}
void Write_b_eep(unsigned int badd, unsigned char data){
    char GIE_BIT_VAL = 0;
    EEADR = (badd & 0x0FF);
    EEDATA = data;
    EECON1bits.EEPGD = 0;
    EECON1bits.CFGS = 0;
    EECON1bits.WREN = 1;
    GIE_BIT_VAL = INTCONbits.GIE;
    INTCONbits.GIE = 0;
    EECON2 = 0x55;
    EECON2 = 0xAA;
    EECON1bits.WR = 1;
    while(EECON1bits.WR);
    INTCONbits.GIE = GIE_BIT_VAL;
    EECON1bits.WREN = 0;    
    
}
unsigned char Read_b_eep(unsigned int badd){
    
    EEADR = (badd & 0x0FF);
    EECON1bits.CFGS = 0;
    EECON1bits.EEPGD = 0;
    EECON1bits.RD = 1;
    Nop();
    Nop();
    return (EEDATA);
}
void Busy_eep(void){
    
    while(EECON1bits.WR);
}