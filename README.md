**Word Guessing Game**

**Libraries Used:**

Standard I/O functions (stdio.h).
Standard library functions (stdlib.h).
String manipulation functions (string.h).
Time-related functions (time.h).
Character type functions (ctype.h).
**Global Variables:**

maximumWordLength: Specifies the maximum length of the word to be guessed.
maximumGuesses: Specifies the maximum number of guesses allowed.
**Functions:**

noRepetitiveCharacters(const char *word): Checks if a word has repetitive characters.
hasGuessed(const char* guessedLetters, char letter): Checks if a letter has already been guessed.
tellCount(char*** words, int wordCount): Counts the number of valid words left.
leftWords(char*** words, char guess, int index, int wordCount): Marks words that aren't usable anymore based on the guessed letter and returns the number of valid words.
printWord(const char* secretWord, const char* guessedLetters): Prints the current state of the word being guessed, with underscores for unguessed letters.
loadWords(char* filename, char*** words, int wordLength): Loads words from a dictionary file that match the given length and don't have repetitive characters.
isInWord(const char* word, char letter): Checks if a letter is in the word being guessed.
getRandomNumber(int min, int max): Returns a random number between the given range.
playGame(char** words, int wordCount, int wordLength, int maxGuesses): The main gameplay logic where the user guesses letters until they either guess the word or run out of attempts.
main(int argc, char* argv[]): The main function that initializes the game, loads the dictionary, and starts the game. It expects three command-line arguments: the dictionary file's name, the desired word length, and the maximum number of guesses.
**Gameplay Overview:**

The game initializes by loading words of a specified length from a dictionary file.
A secret word is randomly selected.
The player guesses letters one by one.
After each guess, the game provides feedback about the guess's correctness and displays the current state of the word.
The game continues until the player guesses the word or exhausts all allowed guesses.
**How to Run:**
To play the game, you need to run it from the command line and provide three arguments: the dictionary file's name, the desired word length, and the maximum number of guesses.

**Example:**

**Copy code**
./game_program dictionary.txt 5 10
Where game_program is the name of the compiled executable, dictionary.txt is the name of the dictionary file, 5 is the word length, and 10 is the maximum number of guesses.

This description provides an overview of the code and its functionalities. If you'd like more details or have specific questions about any part of the code, feel free to ask!
