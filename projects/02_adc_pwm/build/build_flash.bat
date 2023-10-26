avr-gcc -mmcu=attiny85 -o output.elf ../adc_pwm.c
avr-objcopy -j .text -j .data -O ihex output.elf adc_pwm.hex

REM I'll just leave High Fuse as it is since: http://eleccelerator.com/fusecalc/fusecalc.php?chip=attiny85
REM Clock Sources: doc page 25/234
set LOW_FUSE=0b01100011

setlocal enabledelayedexpansion

REM Run the 'where' command and capture its output into a variable
for /f %%i in ('where avrdude.conf') do (
    set avrdude_conf_path=%%i
)

avrdude -C %avrdude_conf_path% -v -p attiny85 -c stk500v1 -P COM3 -b 19200 -U flash:w:adc_pwm.hex:i -u -U lfuse:w:%LOW_FUSE%:m