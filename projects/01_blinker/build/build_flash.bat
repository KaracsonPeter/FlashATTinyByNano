avr-gcc -mmcu=attiny85 -o output.elf ../blinker.c
avr-objcopy -j .text -j .data -O ihex output.elf blinker.hex

REM Enable external reset, disable debug, SPI programming enabled, WDT not always on, EEPROM not preserved, Brown-out Detector trigger level
set HIGH_FUSE=0b00001111
REM Clock Sources: doc page 25/234
set LOW_FUSE=0b01100011

setlocal enabledelayedexpansion

REM Run the 'where' command and capture its output into a variable
for /f %%i in ('where avrdude.conf') do (
    set avrdude_conf_path=%%i
)

avrdude -C %avrdude_conf_path% -v -p attiny85 -c stk500v1 -P COM3 -b 19200 -U flash:w:blinker.hex:i -u -U lfuse:w:%LOW_FUSE%:m