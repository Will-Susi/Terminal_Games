// Copyright 2024 William Susi

#include "Mordle.hpp"

Mordle::Mordle(int wordLength, int numGuesses) {
    _wordLength = wordLength;
    _numGuesses = numGuesses;
    _guessesRemaining = numGuesses;

    // Open dictionary file
    fstream dictionary;
    dictionary.open("dictionary.txt", fstream::in);
    if (!dictionary.good()) {
        cerr << "Unable to open dictionary file." << endl;
        exit(-1);
    }

    // Read out word tokens and add them to list of possible words if they are the user's chosen length
    string word;
    while (getline(dictionary, word)) {
        word.erase(word.find_last_not_of(" \t\n\r") + 1);
        if (_wordLength == static_cast<int>(word.length())) {
            _wordsOfRightLength.push_back(word);
        }
    }
    dictionary.close();

    // Create seed for random number generator and generate a random word answer for the game
    srand(time(NULL));
    _answer = _wordsOfRightLength[rand() % _wordsOfRightLength.size()]; // Choose a random word from the list of possible words
    transform(_answer.begin(), _answer.end(), _answer.begin(), ::toupper); // Make the word all uppercase

    // Creates a blank board
    Space defaultValue = {'_', WHITE};
    vector<vector<Space>> board(_numGuesses, vector<Space>(_wordLength, defaultValue));
    _board = board;

    _answerMap = getLetterOccurrencesInWord(_answer);

    // Initialize letters in order of how the appear on keyboard
    _lettersUsed.push_back({'Q', WHITE});
    _lettersUsed.push_back({'W', WHITE});
    _lettersUsed.push_back({'E', WHITE});
    _lettersUsed.push_back({'R', WHITE});
    _lettersUsed.push_back({'T', WHITE});
    _lettersUsed.push_back({'Y', WHITE});
    _lettersUsed.push_back({'U', WHITE});
    _lettersUsed.push_back({'I', WHITE});
    _lettersUsed.push_back({'O', WHITE});
    _lettersUsed.push_back({'P', WHITE});

    _lettersUsed.push_back({'A', WHITE});
    _lettersUsed.push_back({'S', WHITE});
    _lettersUsed.push_back({'D', WHITE});
    _lettersUsed.push_back({'F', WHITE});
    _lettersUsed.push_back({'G', WHITE});
    _lettersUsed.push_back({'H', WHITE});
    _lettersUsed.push_back({'J', WHITE});
    _lettersUsed.push_back({'K', WHITE});
    _lettersUsed.push_back({'L', WHITE});

    _lettersUsed.push_back({'Z', WHITE});
    _lettersUsed.push_back({'X', WHITE});
    _lettersUsed.push_back({'C', WHITE});
    _lettersUsed.push_back({'V', WHITE});
    _lettersUsed.push_back({'B', WHITE});
    _lettersUsed.push_back({'N', WHITE});
    _lettersUsed.push_back({'M', WHITE});
}

// Prints the current game state
void Mordle::printBoard() {
    for (int r = 0; r < _numGuesses; r++) {
        for (int c = 0; c < _wordLength; c++) {
            Space space = _board[r][c];
            cout << space.color << space.letter << WHITE << " ";
        }  
        cout << endl;
    }
    cout << endl;
}

// Prints the keyboard of letters
void Mordle::printUsedLetters() {
    
    for (int i = 0; i < MAX_WORD_LENGTH; i++) {
        if (i == 10) {
            cout << endl << " ";
        }
        if (i == 19) {
            cout << endl << "   ";
        }
        Space space = _lettersUsed[i];
        cout << space.color << space.letter << WHITE << " ";
    }
    cout << endl << endl;
}

// Returns the answer (for testing)
string Mordle::getAnswer() {
    return _answer;
}

// Print the list of words of the user's chosen length
void Mordle::printList() {
    for (string word : _wordsOfRightLength) {
        cout << word << endl;
    }
}

// Create a map of letters to their occurrences for a given word
unordered_map<char, int> Mordle::getLetterOccurrencesInWord(string word) {
    unordered_map<char, int> lettersToOccurrences;
    for (char letter : word) {
        lettersToOccurrences[letter]++;
    }
    return lettersToOccurrences;
}

// Prints the letters to occurances map of a the answer 
void Mordle::printOccuranceMap() {
    for (auto pair : _answerMap) {
        cout << pair.first << ": " << pair.second << endl;
    }
}

// Gets a valid guess from the user
string Mordle::getGuess() {
    string guess;
    do {
        cout << "Please guess a word of length " << _wordLength << ": ";
        cin >> guess;
        cin.clear();
        cin.ignore(256,'\n');
    } while (find(_wordsOfRightLength.begin(), _wordsOfRightLength.end(), guess) == _wordsOfRightLength.end());

    transform(guess.begin(), guess.end(), guess.begin(), ::toupper);
    return guess;
}

// Rates the correctness of a guess and adds it to the board
void Mordle::rateGuess(string guess) {
    unordered_map<char, int> answerMap = _answerMap;

    // Right letter, right place
    for (int i = 0; i < _wordLength; i++) {
        if (guess[i] == _answer[i]) {
            (_board[_numGuesses - _guessesRemaining][i]).color = GREEN;
            answerMap[guess[i]]--;
            updateKeyboard(guess[i], GREEN);
        }  
    }

    for (int i = 0; i < _wordLength; i++) {
        if (guess[i] != _answer[i]) {
            // Wrong letter, wrong place
            if (answerMap.find(guess[i]) == answerMap.end() || answerMap[guess[i]] == 0) { // Symbol does not exist in answer
                (_board[_numGuesses - _guessesRemaining][i]).color = GRAY;
                updateKeyboard(guess[i], GRAY);
            } else { // Right letter, wrong place
                answerMap[guess[i]]--;
                (_board[_numGuesses - _guessesRemaining][i]).color = YELLOW;
                updateKeyboard(guess[i], YELLOW);
            }
        }
        // Add current letter to board
        (_board[_numGuesses - _guessesRemaining][i]).letter = (guess[i]);
    }
}

// Update keyboard with color
void Mordle::updateKeyboard(char letter, string color) {
    for (vector<Space>::iterator it = _lettersUsed.begin(); it != _lettersUsed.end(); ++it) {
        if (letter == it->letter && (it->color == WHITE || (it->color == YELLOW && color == GREEN))) {
            it->color = color;
        }
    }
}

// Subtracts a guess from the remaining number of guesses
void Mordle::useGuess() {
    _guessesRemaining--;
}

// Checks if the plaeyr has lost (Run out of guesses)
bool Mordle::isLost() {
    return _guessesRemaining == 0;
}

// Checks if the player has won (Guessed the word correctly)
bool Mordle::isWon(string guess) {
    return guess == _answer;
}
