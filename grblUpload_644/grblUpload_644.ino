#include <config.h>
#include <coolant_control.h>
#include <cpu_map.h>
#include <defaults.h>
#include <eeprom.h>
#include <gcode.h>
#include <grbl_644.h>
#include <jog.h>
#include <jogpad.h>
#include <limits.h>
#include <motion_control.h>
#include <nuts_bolts.h>
#include <planner.h>
#include <print.h>
#include <probe.h>
#include <protocol.h>
#include <report.h>
#include <serial.h>
#include <settings.h>
#include <spindle_control.h>
#include <spi_sr.h>
#include <stepper.h>
#include <system.h>

/***************************************************************************

Dieser Sketch kompiliert GRBL-644 und l�dt es auf die MaXYposi-Platine. Bitte 
richten Sie die Arduino-IDE folgenderma�en ein:

- Verschieben Sie das Verzeichnis "grblUpload_644" vom Github-Download in Ihren "Arduino"-Sketch-Ordner.
- Verschieben Sie das Verzeichnis "hardware" vom Github-Download in Ihren "Arduino"-Sketch-Ordner.
- Verschieben Sie das Verzeichnis "libraries\grbl_644" vom Github-Download nach "Arduino\libraries\grbl_644".
- �ffnen Sie den Sketch "..\Arduino\grblUpload_644\grblUpload_644.ino"
- W�hlen Sie im Men� "Werkzeuge:Board" den Eintrag "MaXYposi".
- W�hlen Sie im Men� "Werkzeuge:Prozessor" den Eintrag "ATmega644A" oder "ATmega644P", je nachdem, welche Variante Sie verwenden.

Sie k�nnen nun GRBL mit der Arduino-IDE kompilieren und auch auf das Board 
hochladen; die mit der Platine gelieferten prozessoren sind bereits mit einem 
Sanguino-Optiboot-kompatiblen Bootloader ausgestattet.

****************************************************************************

This sketch compiles and uploads Grbl_644 to your 644p-based MaXYposi Board!

GrblUpload changed by -cm to explicitely use grbl_644 library

To use:
- Copy enclosed "hardware" directory into your Arduino directory.
- Copy entire "grbl_644" directory into "libraries" inside your Arduino directory.
- Select "MaXYiposi" board.
- Check if your CPU is ATmega644A or ATmega644P. Select CPU menu accordingly.
- FTDI device's Serial Port in the Tools drop-down menu.

- Then just click 'Upload'. That's it!

For advanced users:

  If you'd like to see what else Grbl can do, there are some additional
  options for customization and features you can enable or disable. 
  Navigate your file system to where the Arduino IDE has stored the Grbl 
  source code files, open the 'config.h' file in your favorite text 
  editor. Inside are dozens of feature descriptions and #defines. Simply
  comment or uncomment the #defines or alter their assigned values, save
  your changes, and then click 'Upload' here. 

Copyright (c) 2015 Sungeun K. Jeon
Released under the MIT-license. See license.txt for details.
***************************************************************************/

#include <grbl_644.h>

// Do not alter this file!

