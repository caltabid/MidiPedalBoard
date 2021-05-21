# MidiPedalBoard

## Overview

This repository contains a USB Midi Pedal board based on a STM32F407G-DISC1 with 10 buttons, 8 potentiometers and 2 expression pedals

It is USB MIDI class-compliant, so you can add MIDI port without drivers(Windows, iOS, Android, etc...)

![Sample Image](./Documents/04_assembled.jpeg)

The USB-MIDI Class Driver is based on [mimuz-tuch](https://github.com/mimuz/mimuz-tuch) project (c) [D.F.Mac. @TripArts Music](https://github.com/tadfmac).

I got great inspiration from 2 open source projects:
* [USB-MIDI Interface 8IN/8OUT for STM32 CureMIDI8](https://github.com/keshikan/CureMIDI8)
* [Arduino MIDI Footswitch](https://github.com/Hecsall/arduino-midi-footswitch) 

## Specifications

### Features
* 10 buttons (9 general purpose + Page2)
* 8 potentiometers (7 general purpose + Mode)
* 2 expression pedals
* USB MIDI class-compliant

### How to use it
* Page2/Looper Btn
  * When activated (Led on) use second page for other buttons
  * No CC is sent when pressed
* Mode potentiometer (#8, the last one)
  * Left => Normal mode: Btn sends 127 when activated (Led On) and 0 on deactivation
  * Right => Bypass mode: Btn sends 0 when activated (Led On) and 127 on deactivation
  * Half => Disable potentiometers CC
  * No CC is sent when rotated
* Button CC values (excluded Looper/Page2 Btn)
  * {51, 52, 53, 54, 55, 56, 57, 58, 59}
  * {61, 62, 63, 64, 65, 66, 67, 68, 69}
* Potentiometers CC values (excluded Mode Pot)
  * {18, 19, 20, 21, 22, 23, 24};
* Expression pedal CC values
  * {16, 17};

## Building Information

### Making hardware

See [Presentation](./Documents/STM32pedalStomps.pdf)

Basically you should work some wood:

![Sample Image](./Documents/02_wood_cut.jpeg)

And connect about 30 wires:

![Sample Image](./Documents/03_cabling.jpeg)

### Building software

Install [STM32CubeIDE](https://www.st.com/en/development-tools/stm32cubeide.html), import [Project files](./stm32/).
When building the binary file will be created in /stm32/Debug/ or /stm32/Release/ 

## File Location

* [Binary file for STM32F407G-DISC1](./Documents/Disc407.bin)
* [STM32CubeIDE Project file](./stm32/)
* [Documentation](./Documents/STM32pedalStomps.pdf)

## NOTICE

### VID/PID

Vendor ID(VID) and Product ID(PID) in <usbd_desc.c> should be unique pair for each USB devices.
Default VID 0x1209 and PID 0xDACA is experimental IDs from [http://pid.codes](http://pid.codes) .
When distributing or selling, you must get your own IDs, and change to your own IDs in order to avoid conflicting to other USB devices.

## Copyrights

* USB MIDI Class Driver by [D.F.Mac. @TripArts Music](http://ta-music.strikingly.com/)
* STM32Cube by [STMicroelectronics](https://www.st.com/en/development-tools/stm32cubeide.html)
* USB buffer libs by Keshikan (http://www.keshikan.net/)

## Author

(c) 2021 Daniele Caltabiano ( [Website](https://www.danielecaltabiano.com/) )

## License

* USB MIDI Class Driver: [CC BY 4.0](https://creativecommons.org/licenses/by/4.0/)
* STM32 CubeF4: BSD-3-Clause based.
* USB buffer libs: [GPLv3](https://www.gnu.org/licenses/gpl-3.0.html)
* Other Codes, Hardware, Schematic: [MIT](https://opensource.org/licenses/mit-license.php)

See also [LICENSE.md](./LICENSE.md)

## Update History

* (2021/05/21)
  * Added documentation in pdf format, improved readme and fixed code structure.
* (2021/05/19)
  * Initial Release.
