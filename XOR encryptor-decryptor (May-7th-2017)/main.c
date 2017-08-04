#include <stdlib.h>
#include <stdio.h>
#include <time.h>
extern int keylength(const char * x);
int keylengthInC(const char * x){
    int i;
for(i = 0; x[i] != '\0'; ++i);
return i;
}

extern char encryption(const char * key, char character);
char encryptionInC(const char * key, char character){
    int length = keylength(key);
    int i = 0;
    while(i < length){
            character = character ^ key[i++];
    }
    return character;
}

extern int randChar(unsigned long seed);
int randCharInC(unsigned long seed){
    unsigned long rand = seed;
    int character;
    rand ^= rand << 13;
	rand ^= rand >> 17;
	rand ^= rand << 5;
	rand = (rand % 42) + 48 ; // I just chose this ASCII char range because I am not sure about behaviour of some of the other chars.
	character = rand;
	return character;
}


extern void randKeyGenerator(char * key, unsigned long seed);
void randKeyGeneratorinC(char * key, unsigned long seed){
    int counter = 0;
    char newChar;
    while(counter < 10){
        newChar = randChar(seed);
        key[counter] = newChar;
        seed -= 100;
        counter++;
    }
    key[counter] = '\0';
    return;
}

extern void instructions(char * choice);
int main(){
    unsigned long seed = time(0);
    char key[20], choice;
    char character;
    int counter = 0;

    FILE * filepointer = fopen("file.txt", "r");
    if (filepointer == NULL) {
        perror("Error");
    }
    FILE * filepointer2;
    printf("Do you want random cipher or your own? Type R for Random key, T for your own key.\n\n");
    printf("Note: Encryption and decryption is basically same process, so if you want to decrypt\nfollow the same steps and enter the key with which you want to decipher.\n");
    scanf("%c", &choice);
    if(choice == 'R' || choice == 'r'){
        randKeyGenerator(key, seed);
    }else{
        printf("Enter your own key(1-20 characters)\n");
        fflush(stdin);
        gets(key);
    }

    filepointer2 = fopen("encryptedtext.txt", "w");
    if (filepointer2 == NULL) {
        perror("Error");
    }
   character = getc(filepointer);
   while(!feof(filepointer)){ // While new character from file is not EOF (end of file) or -1
          character = encryption(key, character); // Encrypt character.
          putc(character, filepointer2);          // Store in new file
          character = getc(filepointer);
    }
    return 0;
}
