# simon-says
Simon Says game running on a ATTINY84 with capacitive touch

# Hardware
## Capacitive touch sensing
### Hardware guidelines:
* QtouchADC-pin is any analog input pin
* when using ground plane:
  * on same layer as touchpad
  * keep it 5mm away from touchpad
* keep other traces as far apart as possible from a touchpad trace
* keep enough distance between touchpad traces.
### Links
* [Atmel Qtouch](http://www.atmel.com/products/TouchSolutions/touchsoftware/default.aspx?tab=documents)
## Component choice
For sake of fast and cheap assembly and to make the finished product fit in an envelope, all components are placed on the same side of the PCB.
### Reset button
This button will start the game when the MCU is in eternal sleep mode.

Component name | Order code | Price | Remark
-------------- | ---------- | ----- | ------
EVQ-P7C01P | RS 811-3353 | €0.23 | 2 pegs, (2.2N)
EVQ-P7C01K | Farnell 2459549 | €0.77 |
EVQ-P7L01P | RS 811-3369 | €0.23 | 2 pegs, (1.6N)
EVQ-P7A01P | RS 811-3359 | €0.23 | no pegs
EVQ-P7J01P | RS 811-3365 | €0.23 | no pegs
MCIPTG14K-V | Farnell 1605469 | €0.491 | probably compatible with EVQ-P7, no pegs
KMS231G LFS | Farnell 1201409 |  €0.81 | version without pegs compatible with EVQ-P7 from Panasonic

### Battery clip
The original battery clip was one for a CR2032 battery.  It's much easier to get than one for a CR2016, but the downside is that it's 4mm high.
A CR2016 battery clip is only 2mm high.
The battery capacity for a CR2016 is also half that of a CR2032 (i.e. 75mAh-90mAh versus 190-230mAh).
* [MPD BK-5067](http://www.digikey.be/product-detail/en/BK-5067/BK-5067-ND/1033686)
* [Keystone 3026](http://www.digikey.be/product-detail/en/3026/3026K-ND/2137847)

### Speaker
The cheapest speaker I could find, should do.  I opted for a bare piezo transducer element.  It's much cheaper than such an element in a housing,
but it's harder to mount.  The solution I have now is not suited for automatic placement.
* [7BB-12-9](http://benl.rs-online.com/web/p/piezo-buzzer-components/7214947/)
* [MCABT-456-RC](http://be.farnell.com/multicomp/mcabt-456-rc/audio-element-piezo-9-5khz-12mm/dp/2433032) 

### LEDs
The original idea was to put bottom side entry LEDs.  Unfortunately there is no blue color in that version available.  The LEDs should be placed
in holes in the capacitive touch pads.  I was reluctant to that because it has a negative influence on the presence detection.
Side entry LEDs were a good alternative.  Many colors are available and they're relatively cheap.

Color | Order code | Price | Remark
----- | ---------- | ----- | ------
Green | [kpa-3010zgck](http://be.farnell.com/kingbright/kpa-3010zgck/led-3mm-green-300mcd-525nm/dp/2373514) | €0.223 | (300mcd @20mA)
Red | [LTST-S321KRKT](http://benl.rs-online.com/web/p/visible-leds/6921256/) | €0.08 | 180 mcd 130°
Yellow | [LTST-S321KSKT](http://benl.rs-online.com/web/p/visible-leds/6921259/)	| €0.1 | 180 mcd 130°
Blue | [LTST-S321TBKT](http://benl.rs-online.com/web/p/visible-leds/6921253/) | €0.17 | 180 mcd 130°, Vf for 20mA = 2.8V to 3.8V
Blue | [LTST-S110TBKT](http://benl.rs-online.com/web/p/visible-leds/6921168/) | €0.27 | (Mouser & Digikey ++€)

### MCU
The ATTiny84A has been chosen as microcontroller for this project because:
* availability of Qtouch code
* earlier programming experience with the ATTiny family
* cheap
* more pins than ATTiny45.
* low current consumption in sleep mode

## PCB
### Manufacturer
[PCBShopper](http://pcbshopper.com/) allows to select a PCB manufacturer based on several parameters.
### Artwork
#### Images
Images on the touch pads have been downloaded from [MegaIcons](http://megaicons.net/tag/365/).
The baby in the center is taken from the [Mario & Luigi TrueTypeFont](http://www.fontspace.com/24hourfonts/mario-and-luigi)
#### Text
The font for the text is [Super Mario 256](http://www.mariomayhem.com/downloads/super_mario_fonts/super_mario_256.zip).
With LibreOffice Draw, the text has been fit to an arch.

Finally, the black/white image can be added to Altium PCB using a DelphiScript in the Examples directory.

# Firmware
## Library
The [arduino-tiny](https://code.google.com/p/arduino-tiny/) library is by far the most useful when working with an ATTiny MCU.
[This page](http://www.forkrobotics.com/2012/04/run-arduino-code-on-an-attiny/) demonstrates how to get started.
## Capacitive touch sensing
* [this code has been used as reference](http://wiki.sgmk-ssam.ch/index.php/CapSense_%28QTouchADC%29)
* [nice explanation about working principle](http://tuomasnylund.fi/drupal6/content/capacitive-touch-sensing-avr-and-single-adc-pin)
* [Arduino code for QtouchADC](https://github.com/jgeisler0303/QTouchADCArduino)
## Simon Says application
The main program is based on [this Sparkfun design](https://www.sparkfun.com/products/10935).
## Serial debug port
Debugging can be quite hard when you don't know what's happening inside the device. [This code](http://www.ernstc.dk/arduino/tinycom.html) shows how to implement a simple send-only serial port.
## Tone
There are libraries available to generate tones with the ATTiny, but none of them seemed to work correctly, so I ended up writing my own.
## Melody
There's an easter egg.  When you hit the correct touch pad when resetting the board, you'll hear the Arduino Overworld theme, written by Kenji Kodo.
The music here is based on [this music score](http://www.mariopiano.com/mario-sheet-music-overworld-main-theme.html).
