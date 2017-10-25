  #define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>

char keypad[] = "123A456B789C*0#D";
void UART_Transmit(unsigned char dataByte)
{
	// Start Bit
	PORTB &= (0<<PORTB0);
	_delay_us(104);
	
	//Data Bits
	for(int i = 0; i<8 ; i++){
		if((dataByte & 1) == 1){
			PORTB|= (1<<PORTB0);
			_delay_us(104);
			}else{
			PORTB &= (0<<PORTB0);
			_delay_us(104);
		}
		dataByte = dataByte >> 1;
	}
	// Stop Bit
	PORTB|= (1<<PORTB0);
	_delay_us(104);
}
// To char
char scan_keypad(){	
	for(int i = 0; i < 4; i++){     // For every output pin with index 0> i <4
		PORTD = 0xFF;     // Restore PORTD
		PORTD &= ~(1<<i); // Set only i th pin as 0
		for(int j = 0; j <4 ; j++)  //For every input pin.   4 5 6 7
		{
		int a = PIND;
			if (!(PIND & (1<<j+4)))  //Check if input pin j is low. 4> j+4 <8;
			{
				return keypad[i*4+j];
			}
		}
	}
	return '\0';
}


int main(void)
{
	char key;
	char prevkey;
	DDRB |= (1<<DDB0); // set B0 as output for UART
	DDRD = 0b00001111;  // 0-3 output, 4-7 input
	PORTD = 0b11111111;	// set input pullups, set all outputs high.
	int a;
	while(1){
		/*a = PIND;
		for(int i = 0; i < 8; i++){
			(a & (1 << (7-i)))?	UART_Transmit('1'):UART_Transmit('0');
		}*/
		if ((key = scan_keypad()) != prevkey){
			UART_Transmit(key);
			if(key != '\0'){
			UART_Transmit('\n');
			UART_Transmit('\r');
			}
		}
		prevkey = key;
		
	}

}
