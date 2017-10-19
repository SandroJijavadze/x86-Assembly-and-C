#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#define BAUD 9600
#define UBRRVALUE (F_CPU/BAUD/16)-1
/*                      ONBOARD HARDWARE UART CODE
void initializeUart()
{
	UBRR0H = (UBRRVALUE>>8);   // Setting high bits.
	UBRR0L = UBRRVALUE;		   // Setting low bits.
	//Enable receiver and transmitter
	UCSR0B |= (1<<RXEN0)|(1<<TXEN0);
	UCSR0C |= (1<<UCSZ00)|(1<<UCSZ01);  // Set config registers
}
void UART_Transmit(unsigned char oneByte)
{
	while (( UCSR0A & 0x20)== 0);   // Wait while transmit buffer is not empty.
	UDR0 = oneByte;					// Put the character in transmit buffer.
}

void UART_String(const char * uartstring)
{
	int i = 0;
	while(uartstring[i] != '\0')
	UART_Transmit(uartstring[i++]);
	_delay_ms(500);
}

*/

// Software UART functions start here
void set_high(){
	PORTD|= (1<<PORTD5);
	_delay_us(104);
}

void set_low(){
	PORTD &= (0<<PORTD5);
	_delay_us(104);
}

void uart_trans(char dataByte){
	set_low();  // Start bit
	for(int i = 0; i<8 ; i++){
		if((dataByte & 1) == 1){
			set_high();
		}else{
			set_low();
		}
		dataByte = dataByte >> 1;
	
	}

	// Stop Bit
	set_high();
	
}

void sw_UART_String(const char * stringToSend){
	for(int i=0; stringToSend[i] != '\0'; i++)
		uart_trans(stringToSend[i]);
	_delay_ms(100);
}

int main(void)
{
	DDRD |= (1<<DDD5);
	while(1){
		sw_UART_String("Text To be transmitted.r\n");
		/*
		set_low();
		
		set_high();
		set_low();
		set_low();
		set_low();
		set_low();
		set_low();
		set_high();
		set_low();
		
		
		set_high();*/
		//uart_trans('B');
	}

}


