# ATTiny Programming with Arduino Nano
## Prerequisites
Arduino Nano means an [Atmega328P](https://ww1.microchip.com/downloads/en/DeviceDoc/Atmel-7810-Automotive-Microcontrollers-ATmega328P_Datasheet.pdf) micro-controller which is flash-able through [CH340C](https://www.mpja.com/download/35227cpdata.pdf) USB2.0 to serial chip with a specific board I/O layout.  
Note that it only support USB version 2.0!

## Content
This documentation is about setting up an Arduino Nano with as an In-System Programmer or ISP for [ATTiny85](https://ww1.microchip.com/downloads/en/devicedoc/atmel-2586-avr-8-bit-microcontroller-attiny25-attiny45-attiny85_datasheet.pdf) ([ATTiny13](https://ww1.microchip.com/downloads/en/DeviceDoc/ATtiny13A-Data-Sheet-DS40002307A.pdf) is not tested yet).

## Using Arduino IDE
You can follow the steps of many documentations [[1](http://solosodium.github.io/2017-08-07-program-attint85-with-arduino-nano), [2](https://www.youtube.com/watch?app=desktop&v=R9yn-6HVyTQ), [3](https://www.instructables.com/How-to-Program-an-Attiny85-From-an-Arduino-Uno/)] to do this through Arduino IDE.  
Options worked for my board:  
![](./images/01_setting_up_blinker.png)  

For now I will just do it as follows:

## Flashing hex-files directly (Windows steps)
1. **Turn your Arduino Nano into an ISP**
   1. You can flash ("Upload") `nano_isp.hex` to your Arduino Nano (having an ATmega328P MCU on it) by downloading [XLoader](https://github.com/binaryupdates/xLoader) and by setting up the following options:  
    ![](./images/xloader_flash_atmega328p.png)  

    2. Hex will be in `hexes` in project root.  
    3. Chose the correct **COM port** and make sure that this port, used by Arduino, is **type of 2.0**)  
    4. Make sure it had been flashed correctly. If not, find another cable or choose an other COM port or Arduino board.

2. **Set up AvrDude**  
   1. [Download](https://github.com/mariusgreuel/avrdude/releases) the AvrDude version which aligns with your platform and system architecture.  
    E.g.: I have an Intel processor running a Windows 10 instance. For that [this is the link](https://github.com/mariusgreuel/avrdude/releases/download/v7.1-windows/avrdude-v7.1-windows-windows-x64.zip).  
    But, you can find every information on the official github repositories of AvrDude:
        - [Windows](https://github.com/mariusgreuel/avrdude)
        - [Linux](https://github.com/avrdudes/avrdude)
   2. Create a `AvrDude` folder at `C:\Users\`< **USERNAME** > and a `bin` folder in `AvrDude`.
   3. Unzip the downloaded `.zip` file in the `bin` folder.
   4. Add "`C:\Users\`< **USERNAME** >`\AvrDude\bin`" to your environmental variable called "`Path`".
   5. Open a brand-new CommandPrompt and check if it recognizes the command:  
        ```bash
        avrdude
        ```
        If yes, you can continue with the next step, if not, double check your environmental variable.

3. Assembly the flashing setup accordingly:
    ![](./images/pin_map.png)  
4. Navigate to the root folder of this project in cmd and run the following command by replacing < **USERNAME** > to yours:
   ```bash
    avrdude -C C:/Users/< USERNAME >/AvrDude/bin/avrdude.conf -v -p attiny85 -c stk500v1 -P COM3 -b 19200 -U flash:w:hexes/blink_attiny85.hex:i
   ```
5. It must blink now!

## Build & Flask blinker.c
1. [install avr-gcc](https://blog.zakkemble.net/avr-gcc-builds/) (By installing [Arduino IDE](https://www.arduino.cc/en/software) or [AVR Studio](https://tinusaur.com/guides/avr-gcc-toolchain/) you can also get it)
2. Add bin folder of AVR GCC to you environmental variable called "`Path`"
3. `cd` to `projects` and to `build`
4. Run:
    ```bash
    avr-gcc -mmcu=attiny85 -o blinker.elf ../blinker.c
    avr-objcopy -j .text -j .data -O ihex blinker.elf blinker.hex
    avrdude -C C:/Users/< USERNAME >/AvrDude/bin/avrdude.conf -v -p attiny85 -c stk500v1 -P COM3 -b 19200 -U flash:w:blinker.hex:i
    ```