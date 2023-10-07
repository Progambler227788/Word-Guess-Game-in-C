// PART 1  WORD GUESSING GAME
// These are libraries that will help me to code my logic
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>

// Global variables for holding number of guesses and length of word, will vary according to input from 
// command line args
int maximumWordLength = 5;
int maximumGuesses =  5;

// function to ignore words like aba,decc,fgf,dehh etc
int noRepetitiveCharacters(const char *word) {
    int len = strlen(word);

    for (int i = 0; i < len; i++) {
        for (int indexGuess = i + 1; indexGuess < len; indexGuess++) {
            if (word[i] == word[indexGuess]) {
                return 0; // Found a repetitive character
            }
        }
    }

    return 1; // No repetitive characters found
}

// Function to suretyCheck if a letter has been guessed
int hasGuessed(const char* guessedLetters, char letter) {
    for (int i = 0; guessedLetters[i] != '\0'; i++) {
        if (guessedLetters[i] == letter) {
            return 1; // Letter has been guessed
        }
    }
    return 0; // Letter has not been guessed
}

// function to countCorrectNess those words that are lefted
int tellCount(char*** words, int wordCount) {
	int countLeft = 0;

    for (int i = 0; i < wordCount; i++) {
        if (strcmp((*words)[i], "-1") != 0) {
            countLeft++;
        }
		
    }

    return countLeft;
}

// Function to mark words that will be no more useable
int leftWords(char*** words, char guess, int index, int wordCount) {
   int countCorrectNess = 0;
   for (int i = 0; i < wordCount; i++) {
        if (index == -1) {
            char* currentWord = (*words)[i];
            for (int indexGuess = 0; currentWord[indexGuess] != '\0'; indexGuess++) {
                if (currentWord[indexGuess] == guess) {
                    // Replace the entire string with "-1"
                    free((*words)[i]);
                    (*words)[i] = strdup("-1");
                    break;
                }
            }

			countCorrectNess = tellCount(words,wordCount);
        } else if (index >= 0) {
            if ((*words)[i][index] == guess && strcmp((*words)[i], "-1") != 0 ) {
              
				countCorrectNess++;

            }
			else {
				free((*words)[i]);
                (*words)[i] = strdup("-1");
			}
        }
    }
  
    return countCorrectNess;
}

// Function to print word that is guessed by user
void printWord(const char* secretWord, const char* guessedLetters) {
    char displayWord[maximumWordLength + 1];  // Create a copy of the word

    // Initialize displayWord with underscores
    for (int i = 0; secretWord[i] != '\0'; i++) {
        displayWord[i] = '_';
    }
    displayWord[strlen(secretWord)] = '\0';

    // Update displayWord with correctly guessed letters
    for (int i = 0; secretWord[i] != '\0'; i++) {
        if (hasGuessed(guessedLetters, secretWord[i])) {
            for (int indexGuess = 0; indexGuess < strlen(secretWord); indexGuess++) {
                if (secretWord[indexGuess] == secretWord[i]) {
                    displayWord[indexGuess] = secretWord[i];
                }
            }
        }
    }

    // Print the displayWord
    printf("%s", displayWord);
}



// Function to load words from the dictionary file
int loadWords(char* filename, char*** words, int wordLength) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        return -1; // Error opening file
    }

    char word[maximumWordLength];
    int wordCount = 0;
    int maxWords = 32730; // Assuming a maximum of 10 words

    *words = (char**)malloc(maxWords * sizeof(char*));

    while (fscanf(file, "%s", word) != EOF) {
        if (strlen(word) == wordLength && noRepetitiveCharacters(word) ) {
            (*words)[wordCount] = strdup(word);
            wordCount++;
        }
    }

    fclose(file);
//	printf("Words : %d",wordCount);
    return wordCount;
}



// Function to suretyCheck if a letter is in the secret word
int isInWord(const char* word, char letter) {
   // printf("%c is letter.\n", letter);
   // printf("%s is word.\n", word);
    
    for (int i = 0; word[i] != '\0'; i++) {
        if (word[i] == letter) {
            return i; // Letter is in the word
        }
    }
    return -1; // Letter is not in the word
}

// function to get index of random word of given length
int getRandomNumber(int min, int max) {
    // Seed the random number generator with the current time
    if(max == min)   return max;
    else if( max == 1) 
    return max;
 
    srand(time(NULL));

    // Generate a random number between min and max
    int randomNumber = rand() % (max - min + 1) + min;

    return randomNumber;
}

// Function to play the game
void playGame(char** words, int wordCount,  int wordLength, int maxGuesses) {
    char guessedLetters[maximumGuesses+1];
    int remainingGuesses = maxGuesses;

 

    for (int i = 0; i <= maximumGuesses +1 ; i++) {
        guessedLetters[i] = '\0';
    }
    
    char secretWord[maximumWordLength+1];
    strcpy(secretWord, words[getRandomNumber(0,wordCount)]); // Choose a random word
	// strcpy(secretWord, "confer");
    
    char myData[maximumWordLength+1];
    strcpy(myData,secretWord);
    
  
    
    int indexGuess = 0;
    int countCorrectNess = 0;
    int suretyCheck = 0;
 

    // Game loop
    while (remainingGuesses > 0) {

		printf("\n\nWord: ");
     
        printWord(secretWord, guessedLetters);
     
      
        printf("  Enter a letter: ");
        char guess;
        scanf(" %c", &guess); // Read a single character
        guess = tolower(guess);

        if (!isalpha(guess)) {
            printf("%c is not a letter.\n", guess);
            continue;
        }

        if (hasGuessed(guessedLetters, guess)) {
            printf("%c already used.\n", guess);
            continue;
        }
        guessedLetters[indexGuess] = guess;
        indexGuess++;
        guessedLetters[indexGuess] = '\0';
        
        printf("Guesses: %d/%d, ", maximumGuesses - remainingGuesses + 1, maximumGuesses);
      
      
        // decrement countCorrectNess of guesses
        remainingGuesses--;

          
      int data = isInWord(secretWord, guess);
	  int leftWord = leftWords(&words, guess, data , wordCount);
      
      printf("Words left: %d, ",leftWord );
	  printf("Letters used: %s, ", guessedLetters);
      
   

        if (data != -1) {
            printf("Correct guess!\n");
            countCorrectNess++;
            
        } else {
            printf("Incorrect guess.\n");
            
        }
        
          if(countCorrectNess == maximumWordLength){
            suretyCheck = 1;
            printf("Congratulations, you guessed the word: %s\n", myData);
           // printf("Game over");
            break;
        }
        
         if(indexGuess == maximumGuesses && countCorrectNess != maximumWordLength){
            // printf("Congratulations, you guessed the word: %s\n", myData);
            printf("Game over !!!  ");
            break;
        }
      
        
        
    }

    if (remainingGuesses == 0 && suretyCheck == 0) {
        printf("You're out of guesses. The word was: %s\n", myData);
    }
}


// Driver code 
int main(int argc, char* argv[]) {
    
    if (argc != 4) {
        printf("Usage: %s dictionary.txt word_length max_guesses\n", argv[0]);
        return 1;
    }


    char* dictionaryFile = argv[1];
    int wordLength = atoi(argv[2]);
    int maxGuesses = atoi(argv[3]);
    
    
    maximumWordLength = wordLength;
    maximumGuesses = maxGuesses;

    char** words;
    int wordCount = loadWords(dictionaryFile, &words, wordLength);
    printf("Word :%s",words[0]);

    if (wordCount == -1) {
        printf("Error opening dictionary file.\n");
        return 1;
    } else if (wordCount == 0) {
        printf("No valid words found in the dictionary for the specified word length.\n");
        return 1;
    }

    playGame(words, wordCount, wordLength, maxGuesses);

    // Free memory , releasing memory 
    for (int i = 0; i < wordCount; i++) {
        free(words[i]);
    }
    free(words);

    return 0;
}
// Ending of Code