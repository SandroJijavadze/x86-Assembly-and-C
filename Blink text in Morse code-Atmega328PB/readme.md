The child function blinkString translates and blinks string (const char *, null terminated).</br>
It uses PORTB5 (led port) to blink.</br>
To change it to any other port, you need to modify rigth side of PORTB assignment statement in these functions:</br>
dotOn(), dashOn(), pauseInLetter(), newChar(), newWord().</br>
