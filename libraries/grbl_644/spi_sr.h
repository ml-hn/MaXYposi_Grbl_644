/*
  spi_txpos.c - Low level functions for sending and recieving coordinates via the SPI
	by -cm 7/2016  (not a Part of Grbl)
*/

#ifdef SPI_SR


uint8_t sr_inputs_0, sr_inputs_1, sr_inputs_2, sr_inputs_3;     // SR inputs
uint8_t sr_inputs_0_old, sr_inputs_1_old, sr_inputs_2_old, sr_inputs_3_old;     // SR inputs, last state for debounce
uint8_t sr_inputs_0_new, sr_inputs_1_new, sr_inputs_2_new, sr_inputs_3_new;     // SR inputs, last state for debounce
uint8_t sr_outputs_0, sr_outputs_1; 														// SR output 
uint8_t sr_dispstate_0, sr_dispstate_1;													// SPI Display
uint8_t sr_outputs_unused, sr_inputs_unused;										// SPI Display

#ifndef spi_sr_h
	#define spi_sr_h
	
	// initialize ports used for SPI
	void spi_init();
	
	// transmit/receive 1 byte of data from sr_outputs
	uint8_t spi_transmit(uint8_t data);
	
	// schiebt 16 Bit aus sr_outpus_0/_1 in Hardware-SR
	// und holt 16 Bit aus Hardware-SRs in sr_inputs_0/_1
	void spi_txrx_inout();

	// TODO: document function. being used in spi_sr.c and jogpad.c
	void spi_tx_axis(uint8_t axis_idx);
	
	// Achsenpositionen senden
	void spi_tx_axis_roundrobin();
	#endif

#endif
