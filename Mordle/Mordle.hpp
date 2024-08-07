// Copyright 2024 William Susi

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <random>
#include <algorithm>
#include <unordered_map>

using namespace std;

#define WHITE "\033[37m"
#define GRAY "\033[90m"
#define RED "\033[31m"
#define YELLOW "\033[33m"
#define GREEN "\033[32m"

#define MAX_WORD_LENGTH 26
#define MIN_WORD_LENGTH 3

#define MAX_NUM_GUESSES 25
#define MIN_NUM_GUESSES 1

struct Space {
   char letter;
   string color; // RED/GRAY = Wrong letter, wrong place | YELLOW = Right letter, wrong place | GREEN = Right letter, right place
}; 

class Mordle {
 public:
   Mordle(int wordLength, int numGuesses);

   void printBoard();
   void printUsedLetters();
   string getAnswer();
   void printList();
   unordered_map<char, int> getLetterOccurrencesInWord(string word);
   void printOccuranceMap();
   string getGuess();
   void rateGuess(string guess);
   void updateKeyboard(char letter, string color);
   void useGuess();
   bool isLost();
   bool isWon(string guess);

 private:
   int _wordLength;
   int _numGuesses;
   int _guessesRemaining;
   vector<string> _wordsOfRightLength;
   string _answer;
   vector<vector<Space>> _board;
   unordered_map<char, int> _answerMap;
   vector<Space> _lettersUsed;
};
