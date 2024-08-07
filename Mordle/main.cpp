// Copyright 2024 William Susi

#include "Mordle.hpp"

int main() {
    system("clear");

    // Get length of word user would like to play witoh
    int wordLength;
    do {
        cout << "What length word would you like to play with? (" << MIN_WORD_LENGTH << "-" << MAX_WORD_LENGTH << "): ";
        cin >> wordLength;
        cin.clear();
        cin.ignore(256,'\n');
    } while (wordLength < MIN_WORD_LENGTH || wordLength > MAX_WORD_LENGTH);

    // Get number of guesses the user would like to have
    int numGuesses;
    do {
        cout << "How many guesses would you like to have? (" << MIN_NUM_GUESSES << "-" << MAX_NUM_GUESSES << "): ";
        cin >> numGuesses;
        cin.clear();
        cin.ignore(256,'\n');
    } while (numGuesses < MIN_NUM_GUESSES || numGuesses > MAX_NUM_GUESSES);

    Mordle game(wordLength, numGuesses);

    // Loops until the player runs out of guesses or they guess the word correctly 
    while (!game.isLost()) {
        //cout << game.getAnswer() << endl;
        system("clear");
        game.printBoard();
        game.printUsedLetters();
        string guess = game.getGuess();
        game.rateGuess(guess);
        if (game.isWon(guess)) {
            break;
        }
        game.useGuess();
    }

    // End of game reached
    game.printBoard();
    if (game.isLost()) {
        cout << "Sorry, you ran out of guesses! The word was: " << game.getAnswer() << endl;
    } else {
        cout << "You guesses correctly! The word was: " << game.getAnswer() << endl;
    }

    return 0;
}
