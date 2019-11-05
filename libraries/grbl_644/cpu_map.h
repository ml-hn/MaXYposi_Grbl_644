/*
  cpu_map.h - CPU and pin mapping configuration file
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

/* The cpu_map.h files serve as a central pin mapping selection file for different
   processor types or alternative pin layouts. This version of Grbl officially supports
   only the Arduino Mega328p. */


#ifndef cpu_map_h
#define cpu_map_h

#ifdef CPU_MAP_644P_SR

//#################################################################################################
//################################## AVR IN/OUT MAPPING ###########################################
//############################# GRBL-Jog neue Version 2/2017 ######################################
//#################################################################################################

// Serial port pins
#define SERIAL_RX USART0_RX_vect
#define SERIAL_UDRE USART0_UDRE_vect

// Increase Buffers to make use of extra SRAM
#define RX_BUFFER_SIZE		128
#define TX_BUFFER_SIZE		128
#define BLOCK_BUFFER_SIZE	32	// normal 16
#define LINE_BUFFER_SIZE	80	// normal 80

// Define step pulse output pins. NOTE: All step bit pins must be on the same port.
#define STEP_DDR      DDRC
#define STEP_PORT     PORTC
#define STEP_PIN      PINC
#define X_STEP_BIT    0 // 
#define Y_STEP_BIT    2 // 
#define Z_STEP_BIT    4 // 
#ifdef AXIS_C_ENABLE
	#define C_STEP_BIT    6 // 
	#define STEP_MASK ((1<<X_STEP_BIT)|(1<<Y_STEP_BIT)|(1<<Z_STEP_BIT)|(1<<C_STEP_BIT)) // All step bits
#else
	#define STEP_MASK ((1<<X_STEP_BIT)|(1<<Y_STEP_BIT)|(1<<Z_STEP_BIT)) // All step bits
#endif

// Define step direction output pins. NOTE: All direction pins must be on the same port.
#define DIRECTION_DDR     DDRC
#define DIRECTION_PORT    PORTC
#define DIRECTION_PIN     PINC
#define X_DIRECTION_BIT   1 // 
#define Y_DIRECTION_BIT   3 // 
#define Z_DIRECTION_BIT   5 // 
#ifdef AXIS_C_ENABLE
	#define C_DIRECTION_BIT   7 // 
	#define DIRECTION_MASK ((1<<X_DIRECTION_BIT)|(1<<Y_DIRECTION_BIT)|(1<<Z_DIRECTION_BIT)|(1<<C_DIRECTION_BIT)) // All direction bits
#else
	#define DIRECTION_MASK ((1<<X_DIRECTION_BIT)|(1<<Y_DIRECTION_BIT)|(1<<Z_DIRECTION_BIT)) // All direction bits
#endif
// Define stepper driver enable/disable output pin.
#define STEPPERS_DISABLE_DDR   DDRD
#define STEPPERS_DISABLE_PORT  PORTD
#define STEPPERS_DISABLE_BIT   5 // 
#define STEPPERS_DISABLE_MASK (1<<STEPPERS_DISABLE_BIT)

// Define user-control controls (cycle start, reset, feed hold) input pins.
// NOTE: All CONTROLs pins must be on the same port and not on a port with other input pins (limits).
#define CONTROL_DDR       DDRB
#define CONTROL_PIN       PINB
#define CONTROL_PORT      PORTB

#define CONTROL_RESET_BIT         0  // Uno Analog Pin 0
#define CONTROL_FEED_HOLD_BIT     1  // Uno Analog Pin 1
#define CONTROL_CYCLE_START_BIT   2  // Uno Analog Pin 2
#define CONTROL_SAFETY_DOOR_BIT   1  // Uno Analog Pin 1 NOTE: Safety door is shared with feed hold. Enabled by config define.

#define CONTROL_INT       PCIE1  // Pin change interrupt enable pin
#define CONTROL_INT_vect  PCINT1_vect
#define CONTROL_PCMSK     PCMSK1 // Pin change interrupt register
#define CONTROL_MASK      ((1<<CONTROL_RESET_BIT)|(1<<CONTROL_FEED_HOLD_BIT)|(1<<CONTROL_CYCLE_START_BIT)|(1<<CONTROL_SAFETY_DOOR_BIT))
#define CONTROL_INVERT_MASK   CONTROL_MASK // May be re-defined to only invert certain control pins.
  
// Define probe switch input pin.
#define PROBE_DDR       DDRA
#define PROBE_PIN       PINA
#define PROBE_PORT      PORTA
#define PROBE_BIT       3
#define PROBE_MASK      (1<<PROBE_BIT)


// Define spindle enable and spindle direction output pins.
#define SPINDLE_ENABLE_DDR    DDRD
#define SPINDLE_ENABLE_PORT   PORTD
// Z Limit pin and spindle PWM/enable pin swapped to access hardware PWM on Pin 11.
#ifdef VARIABLE_SPINDLE 
  #ifdef USE_SPINDLE_DIR_AS_ENABLE_PIN
    // If enabled, spindle direction pin now used as spindle enable, while PWM remains on D11.
    #define SPINDLE_ENABLE_BIT    6
  #else
    #define SPINDLE_ENABLE_BIT    7
  #endif
#else
  #define SPINDLE_ENABLE_BIT    7
#endif
#ifndef USE_SPINDLE_DIR_AS_ENABLE_PIN
  #define SPINDLE_DIRECTION_DDR   DDRD
  #define SPINDLE_DIRECTION_PORT  PORTD
  #define SPINDLE_DIRECTION_BIT   6
#endif
  
// Define flood and mist coolant enable output pins.
// NOTE: Uno analog pins 4 and 5 are reserved for an i2c interface, and may be installed at
// a later date if flash and memory space allows.
#define COOLANT_FLOOD_DDR   DDRD
#define COOLANT_FLOOD_PORT  PORTD
#define COOLANT_FLOOD_BIT   5

#ifdef ENABLE_M7 // Mist coolant disabled by default. See config.h to enable/disable.
  #define COOLANT_MIST_DDR   DDRD
  #define COOLANT_MIST_PORT  PORTD
  #define COOLANT_MIST_BIT   5
#endif  

// Start of PWM & Stepper Enabled Spindle
#ifdef VARIABLE_SPINDLE
  // Advanced Configuration Below You should not need to touch these variables
  #define PWM_MAX_VALUE    255.0
  #define TCCRA_REGISTER	 TCCR2A
  #define TCCRB_REGISTER	 TCCR2B
  #define OCR_REGISTER     OCR2A
  
  #define COMB_BIT	     	 COM2A1
  #define WAVE0_REGISTER	 WGM20
  #define WAVE1_REGISTER	 WGM21
  #define WAVE2_REGISTER	 WGM22
  #define WAVE3_REGISTER	 WGM23
      
  // NOTE: On the 328p, these must be the same as the SPINDLE_ENABLE settings.
  #define SPINDLE_PWM_DDR	  DDRD
  #define SPINDLE_PWM_PORT	PORTD
  #define SPINDLE_PWM_BIT	7
  // Variable spindle configuration below. Do not change unless you know what you are doing.
  // NOTE: Only used when variable spindle is enabled.
  #define SPINDLE_PWM_MAX_VALUE     255 // Don't change. 328p fast PWM mode fixes top value as 255.
  #ifndef SPINDLE_PWM_MIN_VALUE
    #define SPINDLE_PWM_MIN_VALUE   1   // Must be greater than zero.
  #endif
  #define SPINDLE_PWM_OFF_VALUE     0
  #define SPINDLE_PWM_RANGE         (SPINDLE_PWM_MAX_VALUE-SPINDLE_PWM_MIN_VALUE)
  #define SPINDLE_TCCRA_REGISTER	  TCCR2A
  #define SPINDLE_TCCRB_REGISTER	  TCCR2B
  #define SPINDLE_OCR_REGISTER      OCR2A
  #define SPINDLE_COMB_BIT	        COM2A1

  // Prescaled, 8-bit Fast PWM mode.
  #define SPINDLE_TCCRA_INIT_MASK   ((1<<WGM20) | (1<<WGM21))  // Configures fast PWM mode.
  // #define SPINDLE_TCCRB_INIT_MASK   (1<<CS20)               // Disable prescaler -> 62.5kHz
  // #define SPINDLE_TCCRB_INIT_MASK   (1<<CS21)               // 1/8 prescaler -> 7.8kHz (Used in v0.9)
  // #define SPINDLE_TCCRB_INIT_MASK   ((1<<CS21) | (1<<CS20)) // 1/32 prescaler -> 1.96kHz
  #define SPINDLE_TCCRB_INIT_MASK      (1<<CS22)               // 1/64 prescaler -> 0.98kHz (J-tech laser)
  
#endif // End of VARIABLE_SPINDLE

// for continuous transmitting position data to SPI -cm
#define SPI_PORT  PORTB
#define SPI_DDR   DDRB
#define SPI_MOSI  5		// für ATmega644!
#define SPI_MISO  6
#define SPI_SCK   7
#define SPI_SS    4   // Display-Einheit, immer Ausgang!

#define JOG_POT_ADC 7		// PA7 ADC7

#endif

//#################################################################################################
//################################## SPI IN/OUT MAPPING ###########################################
//#################################################################################################
/*

	16 Ausgänge und bis zu 32 Eingänge an SPI-Schieberegistern 74HC165 (Inputs) 
	und 74HC595 (Outputs) können gesetzt und abgefragt werden. Diese sind am SPI 
	des ATmega644 angeschlossen. Die Funktionen sind in Gruppen geordnet. Jede 
	Gruppe kann einem beliebigen SR zugeordnet werden, indem man das SR-INP/OUT-
	#define der Gruppe auf ein bestimmtes SR setzt. Innerhalb einer Gruppe kann 
	die Bit-Zuweisung beliebig geändert werden. Wenn eine Gruppe nicht verwendet 
	wird, auf "sr_output_unused" resp. "sr_input_unused" zuweisen; diese sind 
	niemals aktiv.
  sr_inputs_0 ist das erste gelesene SR, also direkt an MISO vom AVR
  sr_outputs_0 ist das zuletzt geschriebene SR, also direkt an MOSI vom AVR
*/

//#define debug_jog	  // für Testzwecke, wirft zusätzliche Statusmeldungen aus
//#define debug_spi	  // für Testzwecke, wirft Timeout-Meldungen aus
//#define debug_dial_isr	// für Testzwecke, zeigt Aktivitäten auf DIAL-Phasen-Pins

#ifdef SPI_SR                  // in config.h definiert
  #define STROBE_PORT   PORTB	 // SPI slave selects PORT
  #define STROBE_DDR    DDRB	 // SPI slave selects DDR
  #define STROBE_INP    SPI_SS // SPI slave selects, 74HC165 pin 1, INPUTS, also SPI_SS for display.
  #define STROBE_OUT    3	     // SPI slave selects, 74HC595 pin 12, OUTPUTS 
	// Output Enable of relay port
	#define SR_ENA_DDR      DDRD
	#define SR_ENA_PORT     PORTD
	#define SR_ENA_BIT      2
#endif

// ---------------------------- OUTPUT SRs ------------------------------------
// Assign unused/nonexisting SRs to "sr_outputs_unused"
// ----------------------------------------------------------------------------

// Bits im MACHINE_OUT_SR-Byte (Relais)
// Relais-Schaltausgänge. Zusätzliche LEDs können parallel den 
// Schaltzustand anzeigen.
//
#define MACHINE_OUT_SR         sr_outputs_0
//
#define SPINDLE_ENABLE_SR      0    // SR MSB
#define SPINDLE_DIRECTION_SR   1    // SR MSB
#define COOLANT_FLOOD_SR       2		// M8, switched off by M9
#define COOLANT_MIST_SR        3		// M7, switched off by M9
#define ATC_SR                 4		// M100, switched off by M101					
#define AUX1_SR                5					
#define AUX2_SR                6						
#define AUX3_SR                7    // M106, switched off by M107	

// STATUS_LED_SR Bits
// NOTE: Multiple statii may be mapped to one LED.
// Comment unused LEDs.
// LED_ALARM, LED_HOLD, LED_HOMING will blink if engaged
//
#define STATUS_LED_OUT_SR      sr_outputs_1
//
#define LED_ALARM              0
#define LED_RUN                1
#define LED_JOG                1
#define LED_HOMING             1
#define LED_HOLD               2
//  #define LED_SPINDLE            7 
//  #define LED_FLOOD              7
//  #define LED_MIST               7
#define LED_DIAL_FAST          3
#define LED_DIAL_SELECT_X      4
#define LED_DIAL_SELECT_Y      5
#define LED_DIAL_SELECT_Z      6
#define LED_DIAL_SELECT_C      7


// ---------------------------- INPUT SRs -------------------------------------
// Assign unused/nonexisting SRs to "sr_inputs_unused"!
// ----------------------------------------------------------------------------
// All button/joystick inputs are momentary contact to low (ground).
// Pull-Up resistors on HC165 SRs ensure high level when not active.

// ----------------------------------------------------------------------------
// MACHINE_INP_SR: Buttons, wartet auf Loslassen
// ----------------------------------------------------------------------------
//
#define MACHINE_INP_SR sr_inputs_0
//
#define HOME_SW          7		// performs homing cycle
#define CLEAR_ALARM_SW   6		// clear alarm state manually
#define FEED_FASTER_SW   5		// Manual feed override
#define FEED_SLOWER_SW   4		// Manual feed override
#define ZERO_C_SW        3		// sets C work position to zero
#define ZERO_Z_SW        2		// sets Z work position to zero
#define ZERO_Y_SW        1		// sets Y work position to zero
#define ZERO_X_SW        0		// sets X work position to zero
// #define ZERO_ALL_SW      0	// unused
// #define ZERO_XY_SW      0	// unused

// ----------------------------------------------------------------------------
// ACCESSORY_INP_SR: Buttons, wartet auf Loslassen
// ----------------------------------------------------------------------------
//
#ifdef USER_PANEL_SMALL
  #define ACCESSORY_INP_SR sr_inputs_2
#else
  #define ACCESSORY_INP_SR sr_inputs_1
#endif
//
#define SPINDLE_FASTER_SW 7		// Manual spindle override 
#define SPINDLE_SLOWER_SW 6		// Manual spindle override
#define AUX3_ON_SW        5		// M100/104 override toggles
#define AUX2_ON_SW        4
#define AUX1_ON_SW        3
#define ATC_ON_SW         2
#define MIST_ON_SW        1		// M7/8/9 overrides toggles
#define FLOOD_ON_SW       0

// ----------------------------------------------------------------------------
// JOY_INP_SR, Momentan-Schalter vom Joystick
// ----------------------------------------------------------------------------
// 
// NOTE: Jog speed controlled by ADC7 value. Only one may be actice at a time.
//
#ifdef USER_PANEL_SMALL
  #define JOY_INP_SR		sr_inputs_1  // Shift register used as joystick port
#else
  #define JOY_INP_SR		sr_inputs_2  // Shift register used as joystick port
#endif

#define REV_C_SW			7			// Joystick momentary reverse switches
#define FWD_C_SW			6			// Joystick momentary forward switches
#define REV_Z_SW			5
#define FWD_Z_SW			4			
                                    // Um die Jog-Tasten f. x & y um -90 Grad (im UZS) 
                                    // zu drehen ist die Pin-Zuordnung zu ändern:
                                    //    normal:                 -90°:
#define REV_Y_SW            1       //          3                     1	
#define FWD_Y_SW            0       //          2        /y+/         0       /x-/
#define REV_X_SW            2       //          1    /x-/  /x+/       2	  /y-/  /y+/
#define FWD_X_SW            3       //          0      /y-/           3     /x+/

// ----------------------------------------------------------------------------
// DIAL_INP_SR: Schalter DIAL-Richtung
// ----------------------------------------------------------------------------
// 
#define DIAL_INP_SR   sr_inputs_3    // Shift register used as dial port
//
#define DIAL_SPINDLE_TOGGLE 7
// #define NC1_SW        6	// not connected
#define DIAL_ZERO_ALL_SW	5 	// Zero XYZC from dial SR, waits for btn release
//#define DIAL_ZERO_XY_SW	5 	// Zero XY from dial SR, waits for btn release
#define DIAL_FAST_SW  4		// Toggles dial FAST mode
#define DIAL_DIR_C_SW 3		// momentary contact button.
#define DIAL_DIR_Z_SW 2
#define DIAL_DIR_Y_SW 1
#define DIAL_DIR_X_SW 0
 

//#################################################################################################
//################################### DEVICE ADDRESSING ###########################################
//#################################################################################################
/*

	Mit zwei Jumpern an DEVICE_ADDR_PORT kann eine Adresse zwischen 0 (kein 
	Jumper) und 3 (beide Jumper) eingestellt werden. Wenn ein Adress-Befehl (real 
	time command, 0xD0 to 0xD3) empfangen wurde, der nicht der eingestellten 
	Adresse entspricht, wird GRBL ab sofort alle  Befehle (G-Codes sowie Realtime-
	Befehle, außer natürlich einem Adress-Befehl) ignorieren, Erst wenn GRBL wieder 
	ein zur eingestellten Adresse passenden Adress-Befehl (0xD0 to 0xD3) empfängt, 
	wird die Sperre aufgehoben. Nach einem Hardware-Reset ist die Sperre nicht aktiv.
  
  Dies ermöglicht es, mehr als eine GRBL-Board an einem seriellen Anschluss zu 
  betreiben, z.B. für Maschinen mit mehr als drei Achsen. Sobald ein Adress-
  Befehl gesendet wurde, ist nur noch ein Board aktiv.
  
  Voraussetzung: TX des ATmega muss über Diode und Pull-Up "wired-or"-fähig 
  sein.
  
	With DEVICE_ADDR_ENABLE defined, GRBL is enabled on startup and if address 
	select 0xD0 to 0xD3 (real time command) is received and address select (data 
	AND 0x03) is equal to address jumper setting. GRBL is disabled when other 
	addresses in range 0xD0 to 0xD3 are issued by host. 0xD0 enables device 
	address 0, 0xD1 enables device address 1 etc. Jumpered divice address is shown 
	on $I info string.

	See cpu_map.h to enable/disable device addressing at all.   
	
	-cm
  
*/

#ifdef DEVICE_ADDR_ENABLE
  #define DEVICE_ADDR_PORT  PORTD
  #define DEVICE_ADDR_PIN  PIND
  #define DEVICE_ADDR_DDR  DDRD
  #define DEVICE_ADDR_JP1  3
  #define DEVICE_ADDR_JP2  4
#endif


//#################################################################################################
//##################################### LIMITS/ENCODER ############################################
//#################################################################################################
/* 
	
	An zwei der noch freien Pins des LIMIT-Ports kann ein handelsübliches CNC-
	Handrad mit zwei Phasen A/B angeschlossen werden. Im Ruhezustand sollten diese 
	Pins auf LOW liegen. Falls Richtung nicht stimmt, einfach die beiden A/B-Pins 
	vertauschen.
	
	Die ISR für den LIMIT-PinChange-Interrupt führt mit einem Sprung in jogpad.c,
	falls die Aktivitäten am Port nicht von den eigentlichen LIMIT-Pins stammen.
	
	CNC Handwheel/dial may be connected to two otherwise unused pins on LIMIT 
	port. LIMIT pin change ISR has new hook to jogpad.c which detects fast pin 
	changes on wheel phase A/B. Any CNC encoder with two phases A/B may be used. 
	If it moves in wrong direction, swap A/B wires.
	
	-cm
	
*/

// Define homing/hard limit switch input pins and limit interrupt vectors. 
// NOTE: All limit bit pins must be on the same port
// Encoder Wheel must be on same Port as Limits! -cm
#define LIMIT_DDR       DDRA
#define LIMIT_PORT      PORTA
#define LIMIT_PIN       PINA
#define X_LIMIT_BIT     0 // 
#define Y_LIMIT_BIT     1 // 
#define Z_LIMIT_BIT     2 // 
#define C_LIMIT_BIT     4 // PA4 on LIMIT_PIN
#ifdef DIAL_ENABLED 	// -cm
  #define DIAL_0_BIT       5 // PA5
  #define DIAL_1_BIT       6 // PA6
  #define DIAL_MASK ((1<<DIAL_0_BIT)|(1<<DIAL_1_BIT))
#endif
#define LIMIT_INT         PCIE0  // Pin change interrupt enable pin Port A
#define LIMIT_INT_vect    PCINT0_vect 
#define LIMIT_PCMSK       PCMSK0 // Pin change interrupt register Port A
#define LIMIT_MASK ((1<<X_LIMIT_BIT)|(1<<Y_LIMIT_BIT)|(1<<Z_LIMIT_BIT)|(1<<C_LIMIT_BIT)) // All limit bits


#endif
