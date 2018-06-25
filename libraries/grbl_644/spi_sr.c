/*
  spi_txpos.c - Low level functions for sending and recieving coordinates via the SPI
	by -cm 7/2016  (not a Part of Grbl)
*/


#include "grbl_644.h"

#define SPI_TIMEOUT_SLOW 64
#define SPI_TIMEOUT_FAST 16

#ifdef SPI_SR

bool spi_wait_to(uint8_t timeout){
// liefert TRUE wenn Timeout-Fehler
// klassisches Polling von SPIF bleibt nach Stopp der Motoren
// (Abschalten der Timer-IRQs) 
// aus unerfindlichem Grund manchmal hängen:
/*
  while(!(SPSR & (1<<SPIF))){
  	};
*/
  // Wait for transmission complete with timeout
  uint8_t count;
	for(count = 0; count < timeout; count++) {
		if (SPSR & ((1<<SPIF)|(1<<WCOL))) {
			break;
			}			
		}
	return (count >= timeout);
}


void spi_init(){
  // configure SPI
	// DDRs und PullUps für Strobe-Port (Schieberegister) setzen
	// separate Strobes für HC165 und HC595
	STROBE_DDR |= (1<<STROBE_INP)|(1<<STROBE_OUT); 
	STROBE_PORT |= (1<<STROBE_INP);		// HC165 active low, deshalb 1
	STROBE_PORT &= ~(1<<STROBE_OUT);	// HC595 active high, deshalb 0
	// DDRs und PullUps für SPI-Port setzen
	SPI_PORT |= (1<<SPI_SS)|(1<<SPI_MISO);	
	SPI_DDR |= (1<<SPI_SS)|(1<<SPI_MOSI)|(1<<SPI_SCK);
	sr_inputs_0 = 0;
	sr_inputs_1 = 0;
	sr_inputs_2 = 0;
	sr_inputs_3 = 0;
	sr_inputs_unused = 0;
	SR_ENA_PORT |= (1 << SR_ENA_BIT);		// HC595 /OE, active low, zuerst auf high!
  SR_ENA_DDR |= (1 << SR_ENA_BIT);    // Set as output pins
  spi_txrx_inout();
	SR_ENA_PORT &= ~(1 << SR_ENA_BIT);	// Bit auf low, enabled, LED an
}
	
	
void spi_start_disp(){
// für Display
	SPCR = (1<<SPE)|(1<<MSTR)|(1<<SPR0);
	//SPSR = (1<<SPI2X);
	SPSR &= ~(1<<SPI2X); // 2x-Bit SPI2X für schnellere Übertragung löschen, SCK = 1 MHz
	SPI_PORT &= ~(1<<SPI_SS);
}

void spi_end() {
	SPCR = (1<<MSTR)|(1<<SPR1);
  SPI_PORT |= (1<<SPI_SS);
}


void spi_txrx_inout() {
// wird regelmäßig in protocol_main_loop() aufgerufen -cm
// transmit sr_outputs and receive sr_inputs
// schiebt 16 Bit aus sr_outpus_0/_1 in Hardware-SR
// und holt 16 Bit aus Hardware-SRs in sr_inputs_0/_1/_2/_3
		
	
  // SPI-Init für Hardware-SR Output 74HC595, schneller SCK 2 MHz
  // Enable SPI, Master, Prescaler 4, Sample on rising edge for HC595   
  SPCR = (1<<SPE)|(1<<MSTR)|(1<<SPR0);  
	SPSR |= (1<<SPI2X); // 2x-Bit SPI2X für schnellere Übertragung setzen

	// zuerst Daten für 2. SR
	SPDR = sr_outputs_1; // tx data
  if (spi_wait_to(SPI_TIMEOUT_FAST)) {    // TRUE wenn kurzes Timeout erreicht
  	#ifdef debug_spi
    	printPgmString(PSTR("[MSG:SPI TX0 TIMEOUT]\r\n"));
    #endif
  	spi_end();
  	return;
  }
  
	// zuerst Daten für 2. SR
	SPDR = sr_outputs_0; // tx data
  if (spi_wait_to(SPI_TIMEOUT_FAST)) {    // TRUE wenn kurzes Timeout erreicht
  	#ifdef debug_spi
    	printPgmString(PSTR("[MSG:SPI TX1 TIMEOUT]\r\n"));
    #endif
  	spi_end();
  	return;
  }

	STROBE_PORT |= (1<<STROBE_OUT);  // strobe SR 74HC595, Ausgänge setzen
	__asm__("nop\n\t"); 
	__asm__("nop\n\t"); 
	STROBE_PORT &= ~(1<<STROBE_OUT);

  // Input 74HC165
  // Enable SPI, Master, Prescaler 4, Sample on falling edge for HC165 |(1<<CPOL)
  // SPCR = (1<<SPE)|(1<<MSTR);
  
	//SPSR &= ~(1<<SPI2X); // 2x-Bit SPI2X für schnellere Übertragung löschen, SCK = 1 MHz
	
	STROBE_PORT &= ~(1<<STROBE_INP);  // parallel load SR 74HC165, active low
	__asm__("nop\n\t"); 
	__asm__("nop\n\t"); 
	STROBE_PORT |= (1<<STROBE_INP);
	
	// Wg. Zuverlässigkeit und Entprellung: Vergleiche mit vorherigem Wert. 
	// Erst wenn beide gleich, in sr_intputs übernehmen
	// 1. Byte vom SR direkt an MISO
	SPDR = 0; // dummy to start rx
  if (spi_wait_to(SPI_TIMEOUT_FAST)) {    // TRUE wenn kurzes Timeout erreicht
  	#ifdef debug_spi
    	printPgmString(PSTR("[MSG:SPI RX0 TIMEOUT]\r\n"));
    #endif
  	spi_end();
  	return;
  }
  sr_inputs_0_new = ~SPDR;
  if (sr_inputs_0_new == sr_inputs_0_old){
    sr_inputs_0 = sr_inputs_0_new;
  }
  sr_inputs_0_old = sr_inputs_0_new;
  
	// 2. Byte vom SR
	SPDR = 0; // dummy to start rx
  if (spi_wait_to(SPI_TIMEOUT_FAST)) {    // TRUE wenn kurzes Timeout erreicht
  	#ifdef debug_spi
    	printPgmString(PSTR("[MSG:SPI RX1 TIMEOUT]\r\n"));
    #endif
  	spi_end();
  	return;
  }
  sr_inputs_1_new = ~SPDR;
  if (sr_inputs_1_new == sr_inputs_1_old){
    sr_inputs_1 = sr_inputs_1_new;
  }
  sr_inputs_1_old = sr_inputs_1_new;
  
	// 3. Byte vom SR
	SPDR = 0; // dummy to start rx
  if (spi_wait_to(SPI_TIMEOUT_FAST)) {    // TRUE wenn kurzes Timeout erreicht
  	#ifdef debug_spi
    	printPgmString(PSTR("[MSG:SPI RX2 TIMEOUT]\r\n"));
    #endif
  	spi_end();
  	return;
  }
  sr_inputs_2_new = ~SPDR;
  if (sr_inputs_2_new == sr_inputs_2_old){
    sr_inputs_2 = sr_inputs_2_new;
  }
  sr_inputs_2_old = sr_inputs_2_new;
  
	// 4. Byte vom SR
	SPDR = 0; // dummy to start rx
  if (spi_wait_to(SPI_TIMEOUT_FAST)) {    // TRUE wenn kurzes Timeout erreicht
  	#ifdef debug_spi
    	printPgmString(PSTR("[MSG:SPI RX3 TIMEOUT]\r\n"));
    #endif
  	spi_end();
  	return;
  }
  sr_inputs_3_new = ~SPDR;
  if (sr_inputs_3_new == sr_inputs_3_old){
    sr_inputs_3 = sr_inputs_3_new;
  }
  sr_inputs_3_old = sr_inputs_3_new;

	spi_end();
}

#ifdef SPI_DISP

  void spi_tx_mwpos(uint8_t axis_idx){
  // Positionsdaten an Display senden, 2 Floats einer Achse = 8 Bytes
    uint8_t i;
    int32_t current_position[N_AXIS]; 
    union float_bytes {
       float val;
       unsigned char bytes[sizeof(float)];
    } data;
  
  	// Copy current state of the system position variable
    memcpy(current_position, sys_position, sizeof(sys_position)); // in steps
    data.val = system_convert_axis_steps_to_mpos(current_position, axis_idx); // dauert ca. 8,5 µs
    
  	// Report machine position
  	// LSB first, Mantisse zuletzt, siehe http://www.h-schmidt.net/FloatConverter/IEEE754.html
  	for (i=0; i<4; i++) {
		  if (spi_wait_to(SPI_TIMEOUT_SLOW)) {    // TRUE wenn Timeout erreicht
		  	#ifdef debug_jog
		    	printPgmString(PSTR("[MSG:SPI LCD TIMEOUT]\r\n"));
		    #endif
		  	spi_end();
		  	return;
		  }
    	spi_wait_to(SPI_TIMEOUT_SLOW); // wartet bis gesendet oder Timeout
      SPDR = data.bytes[i];
  	}	
    
    // Report work position
    data.val -= gc_state.coord_system[axis_idx]+gc_state.coord_offset[axis_idx];
    if (axis_idx == TOOL_LENGTH_OFFSET_AXIS) { data.val -= gc_state.tool_length_offset; } 
    	
  	// LSB first, Mantisse zuletzt, siehe http://www.h-schmidt.net/FloatConverter/IEEE754.html
  	for (i=0; i<4; i++) {
		  if (spi_wait_to(SPI_TIMEOUT_SLOW)) {    // TRUE wenn Timeout erreicht
		  	#ifdef debug_jog
		    	printPgmString(PSTR("[MSG:SPI LCD TIMEOUT]\r\n"));
		    #endif
		  	spi_end();
		  	return;
		  }
      SPDR = data.bytes[i];
  	}	
  }
  
  void spi_tx_axis(uint8_t axis_idx) {
  // Achsenpositionen an Display senden. Dauer pro Übertragung ca. 150 µs
  	spi_start_disp();
    SPDR = (255);    // 4 Bytes Startsequenz $FF, $AA, $55, Achsen-#
	  if (spi_wait_to(SPI_TIMEOUT_SLOW)) {    // TRUE wenn Timeout erreicht
	  	#ifdef debug_spi
	    	printPgmString(PSTR("[MSG:SPI xFF TIMEOUT]\r\n"));
	    #endif
	  	spi_end();
	  	return;
	  }
    SPDR = (170);
	  if (spi_wait_to(SPI_TIMEOUT_SLOW)) {    // TRUE wenn Timeout erreicht
	  	#ifdef debug_spi
	    	printPgmString(PSTR("[MSG:SPI xAA TIMEOUT]\r\n"));
	    #endif
	  	spi_end();
	  	return;
	  }
    SPDR = (85);
	  if (spi_wait_to(SPI_TIMEOUT_SLOW)) {    // TRUE wenn Timeout erreicht
	  	#ifdef debug_spi
	    	printPgmString(PSTR("[MSG:SPI x55 TIMEOUT]\r\n"));
	    #endif
	  	spi_end();
	  	return;
	  }
    SPDR = (axis_idx);
    
    spi_tx_mwpos(axis_idx);  // wartet und sendet 4 Positionsbytes
  
	  if (spi_wait_to(SPI_TIMEOUT_SLOW)) {    // TRUE wenn Timeout erreicht
	  	#ifdef debug_spi
	    	printPgmString(PSTR("[MSG:SPI IDX TIMEOUT]\r\n"));
	    #endif
	  	spi_end();
	  	return;
	  }
    SPDR = (sr_dispstate_1);
	  if (spi_wait_to(SPI_TIMEOUT_SLOW)) {    // TRUE wenn Timeout erreicht
	  	#ifdef debug_spi
	    	printPgmString(PSTR("[MSG:SPI ST1 TIMEOUT]\r\n"));
	    #endif
	  	spi_end();
	  	return;
	  }
    SPDR = (sr_dispstate_0);			 // LEDs von sr_outputs_0 ohne blinkmask senden
	  if (spi_wait_to(SPI_TIMEOUT_SLOW)) {    // TRUE wenn Timeout erreicht
	  	#ifdef debug_spi
	    	printPgmString(PSTR("[MSG:SPI ST0 TIMEOUT]\r\n"));
	    #endif
	  }
  	spi_end();
  }
  
  void spi_tx_axis_roundrobin() {
  // Alle 5 ms eine der Achsenpositionen an Display senden. Dauer pro Übertragung ca. 150 µs
  // nach 3 x 5 = 15 ms sind alle Achsen gesendet
    static uint8_t idx_count;
    static uint8_t idx;
  
    idx_count++;
  	if (idx_count == 0) {
  		spi_tx_axis(idx);		  
  	  idx++; 
  	  if (idx > N_AXIS) idx = 0;
  	}    	   
  }
  
#endif

#endif

