/*
  coolant_control.c - coolant control methods
  Part of Grbl

  Copyright (c) 2012-2016 Sungeun K. Jeon for Gnea Research LLC

  Grbl is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  Grbl is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with Grbl.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "grbl_644.h"

void coolant_init()
{
  #ifdef ENABLE_M7
    COOLANT_MIST_DDR |= (1 << COOLANT_MIST_BIT) | (1 << COOLANT_FLOOD_BIT);
  #else
  	COOLANT_FLOOD_DDR |= (1 << COOLANT_FLOOD_BIT); // Configure as output pin
  #endif
  coolant_stop();
  coolant_set_state(ATC_DISABLE);
  coolant_set_state(AUX1_DISABLE);
  coolant_set_state(AUX2_DISABLE);
  coolant_set_state(AUX3_DISABLE);
}


// Returns current coolant output state. Overrides may alter it from programmed state.
uint8_t coolant_get_state()
{
  uint8_t cl_state = COOLANT_STATE_DISABLE;
  if (flood_on) cl_state |= COOLANT_STATE_FLOOD;	// used tracked info
  if (mist_on) cl_state |= COOLANT_STATE_MIST;
  #ifdef SPI_SR
    if (atc_on) cl_state |= COOLANT_STATE_ATC;
    if (aux1_on) cl_state |= COOLANT_STATE_AUX1;
    if (aux2_on) cl_state |= COOLANT_STATE_AUX2;
    if (aux3_on) cl_state |= COOLANT_STATE_AUX3;
  #endif
  return(cl_state);
}


// Directly called by coolant_init(), coolant_set_state(), and mc_reset(), which can be at
// an interrupt-level. No report flag set, but only called by routines that don't need it.
void coolant_stop()
{
  #ifdef INVERT_COOLANT_FLOOD_PIN
    COOLANT_FLOOD_PORT |= (1 << COOLANT_FLOOD_BIT);
  #else
    COOLANT_FLOOD_PORT &= ~(1 << COOLANT_FLOOD_BIT);
  #endif
  #ifdef ENABLE_M7
    #ifdef INVERT_COOLANT_MIST_PIN
      COOLANT_MIST_PORT |= (1 << COOLANT_MIST_BIT);
    #else
      COOLANT_MIST_PORT &= ~(1 << COOLANT_MIST_BIT);
    #endif
  #endif
  MACHINE_OUT_SR &= ~((1 << COOLANT_FLOOD_SR) | (1 << COOLANT_MIST_SR));
  mist_on = false;	// track for panel buttons -cm
  flood_on = false;
  spi_txrx_inout();
}

// Main program only. Immediately sets flood coolant running state and also mist coolant, 
// if enabled. Also sets a flag to report an update to a coolant state.
// Called by coolant toggle override, parking restore, parking retract, sleep mode, g-code
// parser program end, and g-code parser coolant_sync().
void coolant_set_state(uint8_t mode)
{
  if (sys.abort) { return; } // Block during abort.
	
  if (mode & COOLANT_FLOOD_ENABLE) {
    #ifdef INVERT_COOLANT_FLOOD_PIN
      COOLANT_FLOOD_PORT &= ~(1 << COOLANT_FLOOD_BIT);
      spi_txrx_inout();
    #else
      COOLANT_FLOOD_PORT |= (1 << COOLANT_FLOOD_BIT);
      spi_txrx_inout();
    #endif
  } else {
    #ifdef INVERT_COOLANT_FLOOD_PIN
      COOLANT_FLOOD_PORT |= (1 << COOLANT_FLOOD_BIT);
      spi_txrx_inout();
    #else
      COOLANT_FLOOD_PORT &= ~(1 << COOLANT_FLOOD_BIT);
      spi_txrx_inout();
    #endif
  }  

  #ifdef ENABLE_M7
    if (mode & COOLANT_MIST_ENABLE) {
      #ifdef INVERT_COOLANT_MIST_PIN
        COOLANT_MIST_PORT &= ~(1 << COOLANT_MIST_BIT);
        spi_txrx_inout();
      #else
        COOLANT_MIST_PORT |= (1 << COOLANT_MIST_BIT);
        spi_txrx_inout();
      #endif
    } else {
        #ifdef INVERT_COOLANT_MIST_PIN
        COOLANT_MIST_PORT |= (1 << COOLANT_MIST_BIT);
        spi_txrx_inout();
      #else
        COOLANT_MIST_PORT &= ~(1 << COOLANT_MIST_BIT);
        spi_txrx_inout();
      #endif
    }
  #endif

  if (mode == ATC_ENABLE) {
    MACHINE_OUT_SR |= (1 << ATC_SR);	// -cm
    atc_on = true;	// track for panel buttons
  } else if (mode == ATC_DISABLE) {
    MACHINE_OUT_SR &= ~(1 << ATC_SR);	// -cm
    atc_on = false;	// track for panel buttons
  } else if (mode == AUX1_ENABLE) {
    MACHINE_OUT_SR |= (1 << AUX1_SR);	// -cm
    aux1_on = true;	// track for panel buttons
  } else if (mode == AUX1_DISABLE) {
    MACHINE_OUT_SR &= ~(1 << AUX1_SR);	// -cm    
    aux1_on = false;	// track for panel buttons
  } else if (mode == AUX2_ENABLE) {
    MACHINE_OUT_SR |= (1 << AUX2_SR);	// -cm
    aux2_on = true;	// track for panel buttons
  } else if (mode == AUX2_DISABLE) {
    MACHINE_OUT_SR &= ~(1 << AUX2_SR);	// -cm    
    aux2_on = false;	// track for panel buttons
  } else if (mode == AUX3_ENABLE) {
    MACHINE_OUT_SR |= (1 << AUX3_SR);	// -cm
    aux3_on = true;	// track for panel buttons
  } else if (mode == AUX3_DISABLE) {
    MACHINE_OUT_SR &= ~(1 << AUX3_SR);	// -cm
    aux3_on = false;	// track for panel buttons
  }
  spi_txrx_inout();
  sys.report_ovr_counter = 0; // Set to report change immediately
}


// G-code parser entry-point for setting coolant state. Forces a planner buffer sync and bails 
// if an abort or check-mode is active.
void coolant_sync(uint8_t mode)
{
  if (sys.state == STATE_CHECK_MODE) { return; }
  protocol_buffer_synchronize(); // Ensure coolant turns on when specified in program.
  coolant_set_state(mode);
}

