Encrypts and decrypts file using XOR cipher.
Bugs: 
The condition to stop iterating through file and encrypting it char by char is EOF character (value -1),
for some reason, it stops before reaching EOF(end of file) although every character before EOF is in ACII character range and not -1(EOF).