#define F_CPU 16000000
#include <avr/io.h>
#include <asf.h>
#include <avr/interrupt.h>

void set_timer0_up()
{ // Reset the counter
	TIMSK0 = 1<<OCIE0A; // enable timer interrupt.
	TCCR0B |= (1 << CS02)|(1 << CS00);// prescaler set to 1024
	OCR0A = 78;// 78 ticks is 5 mS at 1024 prescaler
	TCCR0A = 0b01000000;   // Set compare output match mode on.
}

ISR(TIMER0_COMPA_vect)
{
	ADMUX |= (1<<ADLAR); // Right-adjust the ADC result.
	ADCSRA |= (1<<ADSC); // Start ADC conversion
	
	while(ADCSRA & (1<<ADSC)); // While adc not transmitted, wait
	OCR2A = ADCH;				// Place the ADC result in OCR2A for PWM
}
void set_timer2_up() // PWM timer
{
	TCCR2A |= (1 << COM2A1);   // set none-inverting mode
	TCCR2A |= (1 << WGM21) | (1 << WGM20);   // set fast PWM Mode
	TCCR2B |= (1 << CS21);// Prescaler = 8, + activate the timer
}


int main (void)
{
	set_timer0_up(); // This one is used for keypad scan, does this every 5 mS.
	set_timer2_up(); // For PWM.
	OCR2A = 0; //Initial compare value = 0;
	DDRB |= (1 << 3);// Set pin B3 as out for external led, PWM.
	PORTD = 0xff;       // Set all pullups high
	sei(); // Enable global interrupts.
	ADMUX = (1<<REFS0);
	ADCSRA |= (1<<ADEN) | (1<<ADPS2)|(1<<ADPS1)|(1<<ADPS0);// | 7; // Enable (ADEN)

	while(1)
	{
		
	}
	
	
}
