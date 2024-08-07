// Copyright 2024 William Susi

#include "MasterMind.hpp"

int main() {
    system("clear");
    MasterMind game; // Start game

    while (game.getGuessesRemaining() != 0) {
        system("clear");
        game.printGameState(); // Print blank game state

        string guess = game.getGuess(); // Get a valid user guess
        
        game.rateCorrectness(guess); // Rate the correctness of the pattern

        // Check if the user guessed correctly
        if (guess == game.getAnswer()) {
            system("clear");
            game.printGameState(); // Print blank game state
            cout << "You guessed correctly and won!" << endl;
            return 0;
        }
    }

    // Ran out of guesses
    cout << "Unfortunately you ran out of guesses and lost!" << endl;
    cout << "The correct patter was: " << game.getAnswer() << endl;
    
    return 0;
}