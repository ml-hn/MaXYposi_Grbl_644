This repo is forked from heise/MaXYposi_Grbl_644
***

### MaXYposi-Schrittmotorsteuerung 

![Picture](https://github.com/heise/MaXYposi_Grbl_644/blob/master/maxyposi_pcb/platine_ausschnitt.JPG)

Aus dem Originaltext:
Das auf GRBL basierende CNC-Steuerungs-Projekt für **4 Achsen und vielen 
I/Os** auf einer speziell für CNC-Zwecke ausgelegten Platine. Natürlich wäre als 
Bahnsteuerung auch ein normaler Arduino-328 mit dem Standard-GRBL geeignet - wir 
haben unser GRBL-644 allerdings auf 4 Achsen erweitert und 32 I/Os hinzugefügt, 
außerdem einen Handrad- und Joystick-Jog-Anschluss sowie eine Echtzeit-
Positionsanzeige mit LCD 16x2 auf einem (optionalen) Bedienfeld. 

Die mit allen SMD-Bauteilen vorbestückte Platine wird mit einem programmierten 
ATmega644A (Optiboot-Bootloader und GRBL 1.1f4 ohne Kontrollpult-Unterstützung) geliefert und kann 
im [Heise Shop](https://shop.heise.de/sonstiges/make-projekte/maxyposi) bestellt werden. Weitere Hinweise
finden Sie auf der [MaXYPosi-Projektseite](http://www.make-magazin.de/maxyposi). 

**Wichtig:** Für den Einsatz des MaXYpulti-Kontrollpults müssen Sie den Arduino-Sketch neu kompilieren und hochladen 
(Hinweise dazu im Unterverzeichnis **[MaXYpulti PCB](https://github.com/heise/MaXYposi_Grbl_644/tree/master/maxypulti_pcb)**).

Dokumentationen zu verschiedenen Treiberkarten finden Sie im **[TB6560-BOARDS-Repository](https://github.com/heise/TB6560-BOARDS)**. 

Bitte beachten Sie unbedingt: 

* den Artikel in **[Make: 2/2017](https://shop.heise.de/katalog/make-2-2017)**
* unsere **[MaXYPosi-Projektseite](http://www.make-magazin.de/maxyposi)**
* die ständig aktualisierte **[FAQ-Seite](https://heise.de/-3676050)** und das zugehörige Forum.
* die Hinweise zur Bestückung der Steuerungsplatine **[im Unterverzeichnis MaXYposy PCB](https://github.com/heise/MaXYposi_Grbl_644/tree/master/maxyposi_pcb)**
* die Hinweise zur Bestückung der Kontrollpult-Platine **[im Unterverzeichnis MaXYpulti PCB](https://github.com/heise/MaXYposi_Grbl_644/tree/master/maxypulti_pcb)**
* das Programm für den Kontrollpult-Display-Prozessor **[im Unterverzeichnis GRBL Display](https://github.com/heise/MaXYposi_Grbl_644/tree/master/grbl_display)**

Optional:

* Sketch SD-Card-Sender für Arduino Uno/Nano **[im Unterverzeichnis SDcard Sender](https://github.com/heise/MaXYposi_Grbl_644/tree/master/sdcard_sender)**
* Alter Schrittmotor als Dreh-Encoder/Handrad **[im Unterverzeichnis Step Encoder](https://github.com/heise/MaXYposi_Grbl_644/tree/master/step_encoder)**


Der Sketch "grblUpload_644.ino" kompiliert GRBL-644 und lädt ihn auf die MaXYposi-Platine. Bitte 
richten Sie die Arduino-IDE folgendermaßen ein:

* Laden Sie sich das [GRBL-644-Repository](https://github.com/heise/MaXYposi_Grbl_644/archive/master.zip) herunter und entpacken sie es auf der lokalen Festplatte.
* Verschieben Sie das Verzeichnis "grblUpload_644" vom Github-Download in Ihren "Arduino"-Sketch-Ordner.
* Verschieben Sie das Verzeichnis "hardware" vom Github-Download in Ihren "Arduino"-Sketch-Ordner.
* Verschieben Sie das Verzeichnis "libraries\grbl_644" vom Github-Download nach "Arduino\libraries\grbl_644".
* Öffnen Sie den Sketch "..\Arduino\grblUpload_644\grblUpload_644.ino"
* Wählen Sie im Menü "Werkzeuge:Board" den Eintrag "MaXYposi".
* Wählen Sie im Menü "Werkzeuge:Prozessor" den Eintrag "ATmega644A" oder "ATmega644P", je nachdem, welche Variante Sie verwenden.

Sie können nun GRBL mit der Arduino-IDE kompilieren und auch auf das Board 
hochladen; die mit der Platine gelieferten Prozessoren sind bereits mit einem 
Sanguino-Optiboot-kompatiblen Bootloader ausgestattet. Die hier verfügbaren HEX-
Dateien sind für einen ATmega644A (für den ausgelieferten Bausatz) kompiliert.

### Version history

### Grbl 1.1f5 Version for ATmega644(p) build 02/24/2018 (english)

 * Fixed issue with $I (GRBL info command; additional info separated with ":"), build date format now VERSION.MM/DD/YYYY
 * Fixed "Jog crash after G38.2 Probing" bug
 * Fixed "M104..M107 not accepted while running" bug (build 02/24/2018)
 * MaXYpulti control panel defined in **config.h** by default

### Grbl 1.1f4 Version for ATmega644(p) build 05.11.2017 (english)

 * Fixed compile errors when C axis disabled
 * Fixed erraneous behaviour when M100 to M107 commands are used
 
### Grbl 1.1f3 Version for ATmega644(p) build 20.06.2017 (english)

 * Fixed pin assignment for SR inputs (joystick)
 * Laser Mode disables Z homing (prevents alarm if no Z axis limit switch connected)

### Grbl 1.1f2 Version for ATmega644(p) build 18.03.2017 (english)

GRBL firmware with multiple additions, suited for MaXYposi board (german Make: magazine, issue 2/2017). Additions by Carsten Meyer, Make Magazin Deutschland.

* 4th C axis per #define in config.h, settings configured to C360 = 1 complete turn for PNP machine or robot head @ 1/16 steps driver
* 16 Output ports for LEDs and relays, via HC595 SRs on SPI (may left unconnected)
* 32 Input ports for buttons/swiches, via HC165 SRs on SPI (may left unconnected)
* SPI transfer of realtime position data (floats), for external LCD (needs extra ATmega168/328)
* Support for dial/handwheel, direct connection to Grbl CPU. Updates machine/work position in realtime.
* Support for analog joystick with variable speed, direct connection to Grbl CPU. Updates machine/work position in realtime.
* Handwheel A/B phase on 2 port pins, must be same as LIMIT port
* Joystick on SR inputs, speed on ADC7
* Optional button panel with coordinate LCD 16x2 and up to 32 buttons, connected via SPI
* Button functions and enables defined in cpu_map.h
* M commands for additional relay switches M100/101..M106/M107 (even numbers turn on, odd turn off relays)
* Additional $I fields and build info
* New files: spi_sr.c and jogpad.c to handle SPI Rx/Tx and joystick/buttons/dial
* some additions to other filed to handle 4th axis and display/LED update

Please note ATmega644 output pin onfiguration in cpu_map.h, which heavily differs from Arduino pinout.

Put in your Arduino Sketchbook folder and select board "MaXYposi" and CPU ATmega644 or 644p.

WORK IN PROGRESS. STAY TUNED.

![Grbl Logo](https://github.com/gnea/gnea-Media/blob/master/Grbl%20Logo/Grbl%20Logo%20250px.png?raw=true)

* [Licensing](https://github.com/gnea/grbl/wiki/Licensing): Grbl is free software, released under the GPLv3 license.
* For more information and help, check the Grbl **[Wiki pages!](https://github.com/gnea/grbl/wiki)**!
* Lead Developer: Sungeun "Sonny" Jeon, Ph.D. (USA) aka @chamnit
* Built on the wonderful Grbl v0.6 (2011) firmware written by Simen Svale Skogsrud (Norway).

-------------
Grbl is an open-source project and fueled by the free-time of our intrepid administrators and altruistic users. If you'd like to donate, all proceeds will be used to help fund supporting hardware and testing equipment. Thank you!

