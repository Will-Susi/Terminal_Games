// Copyright 2024 William Susi

#include "MasterMind.hpp"

// Constructor for MasterMind game
MasterMind::MasterMind() {
    symbols = "XO#$%*"; // Default game symbols, can change

    string blankAnswer = "";
    string blank = "";
    
    srand(time(NULL)); // Create seed for random generated answer

    for (int i = 0; i < ANSWER_LENGTH; i++) { // Create random answer key and blanks for users guesses
        answer += symbols[rand() % symbols.length()];
        blankAnswer += "_";
    }

    for (int i = 0; i < NUM_GUESSES; i++) { // Create a blank game to start
        gameState.push_back(blankAnswer);
        correctness.push_back(blank);
    }

    guessesRemaining = NUM_GUESSES; // Default number of guesses to start
}

// Returns the number of guesses remaining for the player
int MasterMind::getGuessesRemaining() {
    return guessesRemaining;
}

// Prints out the current status of the game
void MasterMind::printGameState() {
    cout << "Guesses: \tResponse: " << endl << endl;
    for (int i = 0; i < NUM_GUESSES; i++) {
        string guess = gameState[i];
        for (int j = 0; j < ANSWER_LENGTH; j++) {
            cout << guess[j] << " ";
        }
        cout << "\t" << correctness[i] << endl;
    }
    cout << endl;
}

// Gets a valid user guess and returns it
string MasterMind::getGuess() {
    cout << "Please guess a " << ANSWER_LENGTH << "-symbol patter using the following symbols: " << symbols << endl;

    bool isGuessValid = true;
    do {
        // Change response based on if they are re-guessing
        if (isGuessValid) {
            cout << "Guess:";
        } else {
            cout << "That was not a valid guess. Please re-guess: ";
        }
        
        // Get guess
        string guess;
        cin >> guess;

        // Check if guess is valid
        if (guess.length() == ANSWER_LENGTH && guess.find_first_not_of(symbols) == guess.npos) {
            gameState.at(NUM_GUESSES - guessesRemaining) = guess; // Add guess to game
            guessesRemaining--; // Decrement remaining guesses
            return guess;
        } else {
            isGuessValid = false;
        }
    }
    while (1);
}

// Dictates if each symbol in a player's guess is in right place, is in the wrong place but in the answer, or is not in the answer at all.
void MasterMind::rateCorrectness(string guess) {
    int fullRight = 0, halfRight = 0, wrong = 0;

    // Create map of symbols to their number of occurrences in the pattern
    unordered_map<char, int>  freqOfSymInAnswer;

    // Count frequencies of characters in both guess and answer
    for (int i = 0; i < ANSWER_LENGTH; i++) {
        //freqOfSymInGuess[guess[i]]++;
        freqOfSymInAnswer[answer[i]]++;
    }

    // Right symbol, right place
    for (int i = 0; i < ANSWER_LENGTH; ++i) {
        if (guess[i] == answer[i]) {
            fullRight++;
            freqOfSymInAnswer[guess[i]]--;
        }  
    }

    for (int i = 0; i < ANSWER_LENGTH; ++i) {
        if (guess[i] != answer[i]) {
            if (freqOfSymInAnswer.find(guess[i]) == freqOfSymInAnswer.end() || freqOfSymInAnswer[guess[i]] == 0) { // Symbol does not exist in answer
                wrong++;
            } else { // Remaining matches are Right Symbol, Wrong Place
                freqOfSymInAnswer[guess[i]]--; // Subtract an occurrence from answer map
                halfRight++;
            }
        }
    }

    string response = to_string(fullRight) + " " + to_string(halfRight);
    correctness.at(NUM_GUESSES - guessesRemaining - 1) = response; // Add rating to game
}

// Returns a string containing the symbols in the game
string MasterMind::getSymbols() {
    return symbols;
}

// Returns the answer to the game
string MasterMind::getAnswer() {
    return answer;
}