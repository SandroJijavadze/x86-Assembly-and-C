#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// I will use some global variables because some variables are used by few functions and it would be a hassle to pass it to each one.
int errors;
char word[20];
// I could have put more here but There is a requirement to show that I know how to pass by value and reference.



void wasted(){
    printf("________  \n");
    printf(" |    |   \n");
    printf(" |    0   \n");
    printf(" |   /|\\  \n");
    printf(" |   / \\ \n");
    printf(" |        \n");
    printf("---------\n");
    printf("WASTED! YOU LOST!\n\n");
}
void printHangman(char * test){ // Prints appropriate hangman according to which
    switch(errors){
        case 0:
            printf("\n");
            printf("\n");
            printf("\n");
            printf("\n");
            printf("\n");
            printf("\n");
            printf("---------\n\n");
            break;
        case 1:
            printf("\n");
            printf(" |   \n");
            printf(" |\n");
            printf(" |\n");
            printf(" |\n");
            printf(" |\n");
            printf("---------\n\n");
            break;
        case 2:
            printf("_______\n");
            printf(" |   \n");
            printf(" |\n");
            printf(" |\n");
            printf(" |\n");
            printf(" |\n");
            printf("---------\n\n");
            break;
        case 3:
            printf("_______\n");
            printf(" |   |\n");
            printf(" |\n");
            printf(" |\n");
            printf(" |\n");
            printf(" |\n");
            printf("---------\n\n");
            break;
        case 4:
            printf("________\n");
            printf(" |    |\n");
            printf(" |    0\n");
            printf(" |\n");
            printf(" |\n");
            printf(" |\n");
            printf("---------\n\n");
            break;
        case 5:
            printf("________  \n");
            printf(" |    |   \n");
            printf(" |    0   \n");
            printf(" |    |   \n");
            printf(" |        \n");
            printf(" |        \n");
            printf("---------\n\n");
            break;
        case 6:
            printf("________  \n");
            printf(" |    |   \n");
            printf(" |    0   \n");
            printf(" |    |  \n");
            printf(" |       \n");
            printf(" |        \n");
            printf("---------\n");
            break;
        case 7:
            printf("________  \n");
            printf(" |    |   \n");
            printf(" |    0   \n");
            printf(" |    |\\  \n");
            printf(" |       \n");
            printf(" |        \n");
            printf("---------\n");
            break;
        case 8:
            printf("________  \n");
            printf(" |    |   \n");
            printf(" |    0   \n");
            printf(" |   /|\\ \n");
            printf(" |       \n");
            printf(" |        \n");
            printf("---------\n");
            break;
        case 9:
            printf("________  \n");
            printf(" |    |   \n");
            printf(" |    0   \n");
            printf(" |   /|\\\n");
            printf(" |   /   \n");
            printf(" |        \n");
            printf("---------\n");
            break;
}

    printf("\nThe Word :%s\n", test);
}
void guessesRemaining(int lastGuess){ // Prints if guess was correct or not and amount of guesses that remain
    if(lastGuess == 0){
        printf("\nYour Guess was incorrect!");
    }else if(lastGuess == 1){
        printf("\nYou Guessed Right!");
    }
    printf("\nGuesses remaining: %d out of %d \n", 10 - (errors), 10);
}
int checkWin(char test[]){ // If all characters are guessed it prints appropriate string and returns (if 1 is returned, we break form game loop)
    int i;
    int won = 1;
    for(i = 0; test[i] != '\0'; i++){ // If any character is equal to - then won = 0, not won yet.
        if(test[i] == '-'){
            won = 0;
        }
    }
    if(won == 1)
        return 1;
}
int numLines(){ // Reads and returns number of lines so that we can get word from random line
    FILE *filePointer = fopen("dictionary.txt", "r");  // word list from https://github.com/first20hours/google-10000-english/blob/master/google-10000-english-no-swears.txt
    int  c = 0; // EOF is signed, so int is used
    int lines = 0   ;
    c = fgetc(filePointer);
    while(!feof(filePointer)){
        c = fgetc(filePointer);
        if(c == '\n'){
            lines++;
        }
    }
    if(lines !=  0) //     The last line does not have newline
        lines ++;
    fclose(filePointer);
    return lines;
}
void randomWord(char * word){ // Gets the word from appropriate(random) line.
    int l=0;
    int randLine = rand() % numLines(); // Makes sure random is in scope 0 to amount of lines in our file.
    FILE* file = fopen("dictionary.txt", "r"); // word list from : https://github.com/first20hours/google-10000-english/blob/master/google-10000-english-no-swears.txt
    while(l++ < randLine)// Gets to the desired line
        fgets(word, 20, file);

    word[strlen(word)-1] = '\0';
    return;
}
void getLegalInput(char * guess, char guesses[]){ // Recursive function that calls itself to get new input while current input is illegal.
    while ((*guess = tolower(getchar())) == '\n'){} // Gets new input while input equals '\n'
    if(isalpha(*guess) == 0){
        printf("You have to enter alphabetic character, please enter another one.\n");
        getLegalInput(guess, guesses);
    } else if (strchr(guesses, *guess) != NULL){ // if strchr returns pointer then it exists and user has to enter new one.
        printf("You have already tried that letter, try another \n");
        getLegalInput(guess, guesses);
    }
    return;
}
void revealIfFound(char guess, char guesses[], char test[],int* lastGuess){ // Adds the input to guesses and reveals the character if found.
    int i;
    int length = strlen(guesses);
    guesses[length] = guess;
    guesses[length+1] = '\0';
    *lastGuess = 0;
    for(i = 0; test[i] != '\0'; i++){
        if(test[i] == '-'){                         // I added or condition to not count entering the same correct chars as mistake.
            if(tolower(word[i]) == tolower(guess)){ // tolower makes it work even for capital letters
                test[i] = guess;
                *lastGuess = 1;
            }
        }
    }
    if((*lastGuess) != 1){ // If last guess was incorrect amount of errors is incremented.
        errors++;
    }
    return;
}
void game(){
    randomWord(word);
    errors = 0;
    int n;
    char test[strlen(word)];
    char guess;
    char guesses[20];
    int lastGuess;
// This is used to remember if last guess was correct or not.
    guesses [0] = '\0';
    for(n = 0; n < strlen(word); n++)
        test[n] = '-';
    test[n] = '\0';

    while(1){ // runs before won or lost then breaks from loop.
        system("cls");
        printHangman(test);
        guessesRemaining(lastGuess);
        printf("Guesses you already made: %s\n", guesses);
        printf("Enter an alphabetic character or few of them to guess! \n");
        getLegalInput(&guess, guesses);
        revealIfFound(guess, guesses, test, &lastGuess);
        if(checkWin(test) == 1){ // IF all letters are guessed then:
            system("cls");
            printHangman(test);
            guessesRemaining(lastGuess);
            printf("Congratulations, you won!\n");
            break;
        }
        if (errors == 10){ // if lost then:
            system("cls");
            wasted();
            guessesRemaining(lastGuess);
            printf("\n The Word was %s\n", word);
            break;
        }
    }
}
int main(){
    srand(time(NULL));
    char playagain;

    do{
        game();
        printf("Do you want to play again? Enter Y if yes anything else if not.\n");
        playagain = getch();

    }while(tolower(playagain) == 'y');


    return 0;
}
