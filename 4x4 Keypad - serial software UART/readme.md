<h>Keypad MUX + bitbang UART</h>

This code uses pins PD0 through PD7  for 4x4 keypad pins.
Pin PB0 is used for UART serial communication, configuration 8n1. 8 data bits, no parity bits, 1 stop bit.</br>
Instead of using onboard hardware for UART,
this code uses "bitbang", software backed UART.</br>BAUD rate in this case is 9600, so delay between UART bits is 104uS.</br>
Setup/code was tested on atmega328p.
