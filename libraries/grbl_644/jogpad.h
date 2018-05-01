/*
  jogging.h - code pertaining to jog switches
  Part of Grbl

  Copyright (c) 2014 Carsten Meyer

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
  
  Jogging Q&D additions by cm, Make: magazin Deutschland
  
*/

#ifndef jogpad_h
#define jogpad_h 

bool spindle_on;
bool flood_on;
bool mist_on;
bool atc_on;
bool aux1_on;
bool aux2_on;
bool aux3_on;
uint8_t msg_to_display;
uint16_t step_idle_timeout;

uint8_t jog_zero_request_flag;  // Report ZERO request

#ifdef DIAL_ENABLED
  // Limi pin change ISR hook. First check Encoder Wheel on same pins.
  void check_encoder_hook(uint8_t dial_pin);
#endif

// initialize the jogging module
void jogpad_init();
// void set_activity_led();
void set_led_status();

// TODO: document, used in protocol.c
void set_led_disp_status();

// perform the jogging cycle
void jogpad_check();


#endif
