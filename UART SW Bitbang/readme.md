<h1>Software-only UART transmitter.</h1>
</br>
Baud Rate used here is 9600. </br>
Can be changed by changing delays in SET LOW and SET HIGH functions from 104uS to corresponding value (1s/BAUDRATE).</br>
The configuration is 8n1, 8 data bits, no parity bit and 1 stop bit.</br>
PORTD5 is used as transfer pin. If you want to use other port, set it in set_high() and set_low() functions instead of PORTB5, and set that port instead of DDD5 in main(), on line containing: "DDRD |=....... <u>DDD5</u>);" </br>
