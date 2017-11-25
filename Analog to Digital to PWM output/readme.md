<h1>Analog to Digital to PWM</h1>

This code reads the analog input on PC0 (ADC0) pin on Atmega328P/ Atmega328PB.</br>
The analog input is left adjusted, so resolution is 8 bit only. </br>
The 8 bit value read from PC0 is then output as PWM signal using AVR 8 bit timer's PWM mode through pin B3</br>
Interrupt, which occurs every 5mS, scans for analog input on PC0</br>
and assigns the scanned value to the timer's  output compare register.</br>
