/*
  defaults.h - defaults settings configuration file
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

/* The defaults.h file serves as a central default settings selector for different machine
   types, from DIY CNC mills to CNC conversions of off-the-shelf machines. The settings
   files listed here are supplied by users, so your results may vary. However, this should
   give you a good starting point as you get to know your machine and tweak the settings for
   your nefarious needs.
   NOTE: Ensure one and only one of these DEFAULTS_XXX values is defined in config.h */

#ifndef defaults_h

#ifdef DEFAULTS_GENERIC
  // Grbl generic default settings. Should work across different machines.
  #define DEFAULT_X_STEPS_PER_MM 100.0
  #define DEFAULT_Y_STEPS_PER_MM 100.0
  #define DEFAULT_Z_STEPS_PER_MM 80.0
  #define DEFAULT_X_MAX_RATE 4000.0 // mm/min
  #define DEFAULT_Y_MAX_RATE 4000.0 // mm/min
  #define DEFAULT_Z_MAX_RATE 4000.0 // mm/min
  #define DEFAULT_X_ACCELERATION (50.0*60*60) // 10*60*60 mm/min^2 = 10 mm/sec^2
  #define DEFAULT_Y_ACCELERATION (50.0*60*60) // 10*60*60 mm/min^2 = 10 mm/sec^2
  #define DEFAULT_Z_ACCELERATION (50.0*60*60) // 10*60*60 mm/min^2 = 10 mm/sec^2
  #define DEFAULT_X_MAX_TRAVEL 370.0 // mm NOTE: Must be a positive value.
  #define DEFAULT_Y_MAX_TRAVEL 740.0 // mm NOTE: Must be a positive value.
  #define DEFAULT_Z_MAX_TRAVEL 160.0 // mm NOTE: Must be a positive value.
  #define DEFAULT_SPINDLE_RPM_MAX 1000.0 // rpm
  #define DEFAULT_SPINDLE_RPM_MIN 0.0 // rpm
  #define DEFAULT_STEP_PULSE_MICROSECONDS 6
  #define DEFAULT_STEPPING_INVERT_MASK 0
  #define DEFAULT_DIRECTION_INVERT_MASK 0
  #define DEFAULT_STEPPER_IDLE_LOCK_TIME 25 // msec (0-254, 255 keeps steppers enabled)
  #define DEFAULT_STATUS_REPORT_MASK 1 // MPos enabled
  #define DEFAULT_JUNCTION_DEVIATION 0.01 // mm
  #define DEFAULT_ARC_TOLERANCE 0.002 // mm
  #define DEFAULT_REPORT_INCHES 0 // false
  #define DEFAULT_INVERT_ST_ENABLE 0 // false
  #define DEFAULT_INVERT_LIMIT_PINS 0 // false
  #define DEFAULT_SOFT_LIMIT_ENABLE 1 // false
  #define DEFAULT_HARD_LIMIT_ENABLE 0  // false
  #define DEFAULT_INVERT_PROBE_PIN 0 // false
  #define DEFAULT_LASER_MODE 0 // false
  #define DEFAULT_HOMING_ENABLE 1  // false
  #define DEFAULT_HOMING_DIR_MASK 2 // move positive dir
  #define DEFAULT_HOMING_FEED_RATE 25.0 // mm/min
  #define DEFAULT_HOMING_SEEK_RATE 500.0 // mm/min
  #define DEFAULT_HOMING_DEBOUNCE_DELAY 0 // msec (0-65k)
  #define DEFAULT_HOMING_PULLOFF 5.0 // mm
#endif


#ifdef DEFAULTS_MAXYPOSI
  // Grbl MaXYposi default settings
  #define DEFAULT_STEP_PULSE_MICROSECONDS 5  // $0, usec
  #define DEFAULT_STEPPER_IDLE_LOCK_TIME 255   // $1, msec (0-254, 255 keeps steppers enabled)
  #define DEFAULT_STEPPING_INVERT_MASK 0      // $2, 0000CZYX
  #define DEFAULT_DIRECTION_INVERT_MASK 0     // $3, 0000CZYX
  #define DEFAULT_INVERT_ST_ENABLE 0          // $4
  #define DEFAULT_INVERT_LIMIT_PINS 0         // $5, false
  #define DEFAULT_INVERT_PROBE_PIN 0          // $6, false
  #define DEFAULT_STATUS_REPORT_MASK 1        // $10, MPos enabled
  #define DEFAULT_JUNCTION_DEVIATION 0.01     // $11 mm
  #define DEFAULT_ARC_TOLERANCE 0.05          // $12 mm
  #define DEFAULT_REPORT_INCHES 0             // $13 false
  #define DEFAULT_SOFT_LIMIT_ENABLE 1         // $20 false
  #define DEFAULT_HARD_LIMIT_ENABLE 0         // $21 false
  #define DEFAULT_HOMING_ENABLE 1             // $22 true
  #define DEFAULT_HOMING_DIR_MASK 2           // $23, 0000CZYX, 3 = move XY in negative direction
  #define DEFAULT_HOMING_FEED_RATE 25.0      // $24 mm/min
  #define DEFAULT_HOMING_SEEK_RATE 500.0     // $25 mm/min
  #define DEFAULT_HOMING_DEBOUNCE_DELAY 0    // $26 msec (0-65k)
  #define DEFAULT_HOMING_PULLOFF 5.0          // $27 mm
  #define DEFAULT_SPINDLE_RPM_MAX 24000.0      // $30 rpm
  #define DEFAULT_SPINDLE_RPM_MIN 8000.0         // $31 rpm
  #define DEFAULT_LASER_MODE 0                // $32 false
  #define DEFAULT_X_STEPS_PER_MM 100.0         // $100, = 1600imp/20,  20 mm Vorschub pro Umdrehung 
  #define DEFAULT_Y_STEPS_PER_MM 100.0         // $101, = 1600imp/20,  20 mm Vorschub pro Umdrehung
  #define DEFAULT_Z_STEPS_PER_MM 80.0       // $102, zöllige Spindel
  #define DEFAULT_C_STEPS_PER_MM 8.888        // $103, 360° = 3200 steps, = 3200/360 -cm
  #define DEFAULT_X_MAX_RATE 4000.0          // $110 in mm/min
  #define DEFAULT_Y_MAX_RATE 4000.0          // $111 in mm/min
  #define DEFAULT_Z_MAX_RATE 4000.0          // $112 in mm/min
  #define DEFAULT_C_MAX_RATE 100000.0         // $113 in deg/min
  #define DEFAULT_X_ACCELERATION (60.0*60*60) // $120, 1000*60*60 mm/min^2 = 10 mm/sec^2
  #define DEFAULT_Y_ACCELERATION (60.0*60*60) // $121, 1000*60*60 mm/min^2 = 10 mm/sec^2
  #define DEFAULT_Z_ACCELERATION (60.0*60*60)  // $122, 800*60*60 mm/min^2 = 10 mm/sec^2

  #define DEFAULT_C_ACCELERATION (15000.0*60*60)// $123, 15000*60*60 mm/min^2 = 150000 deg/sec^2
  
  #define DEFAULT_X_MAX_TRAVEL 370.0          // $130 in mm NOTE: Must be a positive value.
  #define DEFAULT_Y_MAX_TRAVEL 740.0          // $131 in mm NOTE: Must be a positive value.
  #define DEFAULT_Z_MAX_TRAVEL 160.0           // $132 in mm NOTE: Must be a positive value.
  #define DEFAULT_C_MAX_TRAVEL 360.0          // $133 in Degrees NOTE: Must be a positive value.
#endif

#endif
