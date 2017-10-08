The child function blinkString translates and blinks string (const char *, null terminated).
It uses PORTB5 (led port) to blink.
To change it to any other port, you need to modify rigth side of PORTB assignment statement in these functions:
dotOn(), dashOn(), pauseInLetter(), newChar(), newWord().
