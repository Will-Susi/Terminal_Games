// Copyright 2024 William Susi

#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include <random>
#include <unordered_map>

using namespace std;

#define ANSWER_LENGTH 4
#define NUM_GUESSES 10

class MasterMind {
    public:
        MasterMind();
        int getGuessesRemaining(); 
        void printGameState();
        string getGuess();
        void rateCorrectness(string guess);
        string getSymbols();
        string getAnswer(); 
    private:
        string symbols;
        string answer;
        vector<string> gameState;
        vector<string> correctness;
        int guessesRemaining;
};