#define F_CPU 16000000UL // Initialize clock
#include <asf.h>
#include <util/delay.h>
static const char *alpha[] = {
	".-",   //A
	"-...", //B
	"-.-.", //C
	"-..",  //D
	".",    //E
	"..-.", //F
	"--.",  //G
	"....", //H
	"..",   //I
	".---", //J
	"-.-",  //K
	".-..", //L
	"--",   //M
	"-.",   //N
	"---",  //O
	".--.", //P
	"--.-", //Q
	".-.",  //R
	"...",  //S
	"-",    //T
	"..-",  //U
	"...-", //V
	".--",  //W
	"-..-", //X
	"-.--", //Y
	"--..", //Z
};
static const char *num[] = {
	"-----", //0
	".----", //1
	"..---", //2
	"...--", //3
	"....-", //4
	".....", //5
	"-....", //6
	"--...", //7
	"---..", //8
	"----." //9
};


void dotOn(void){ // One unit of light (200 ms) for Dot
	PORTB |= (1<<5);
	_delay_ms(200);
	PORTB &= 0; // Off
}

void dashOn(void){
	PORTB |= (1<<5); // 3 units of light(600 ms) for dash
	_delay_ms(600);
	PORTB &= (0<<5); // Off
}

void pauseInLetter(void){
	PORTB &= (0<<5); //Turn led off
	_delay_ms(200); // Delay for one unit of time ( 200ms)
}

void newChar(void){
	PORTB &= 0; //Off
	_delay_ms(600); // Delay
}

void newWord(void){
	PORTB &= 0; //Off
	_delay_ms(1400); // Delay
	
}
// Represents character as morse sequence by blinking led.
void blinkCharacter(const char * charInMorse){
	int i = 0;
	
	while(charInMorse[i] != '\0'){// While null terminator not reached, If .(dot) then turn led on for 200ms, else if - (dash) turn it on for 600ms.
		if(charInMorse[i] == '.'){
			dotOn();
		}
		else if(charInMorse[i] == '-'){
			dashOn();
		}
		
		if(charInMorse[++i] != '\0')  // If not followed by NULL then add pause for new dash/dot.
			pauseInLetter();
	}
}

// Goes through the string and makes pauses, powers led on and off in appropriate situations.
void blinkString(const char * someString){
	for (int i = 0; someString[i] != "\0"; i++){
		// Pause for each new letter.
		if(someString[i] == 32){ // If character is whitespace, make pause for new word.
			newWord();
		}
		else if(someString[i] <= 57 && someString[i] > 47){  // If numeric, subtract 48 to get index from array given in assignment.
			blinkCharacter(num[someString[i] - 48]);
			newChar(); // Pause for new 
		}
		else if (someString[i] <= 90 && someString[i] > 64){ // If a-z,  subtract 65 to get index.
			blinkCharacter(alpha[someString[i] - 65]);
			newChar();
		}
		else if (someString[i] <= 122 && someString[i] > 96){ // If A-Z, subtract 97 to get index.
			blinkCharacter(alpha[someString[i] - 97]);
			newChar();
		}
		//newChar makes pause for new character.
	}
}

int main (void)
{
	board_init();
	blinkString("Some arbitrary text");

	
}
