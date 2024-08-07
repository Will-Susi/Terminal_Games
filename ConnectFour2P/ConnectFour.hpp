// Copyright 2024 William Susi

#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include <random>

using namespace std;

#define WIDTH 7
#define HEIGHT 6

#define RED "\033[31m"
#define YELLOW "\033[33m"
#define WHITE "\033[37m"

enum Turn {
    PLAYER1,
    PLAYER2
};

struct Piece {
    char disk;
    string color;
};

class ConnectFour {
    public:
        ConnectFour();
        void printGameSmall();
        void printGameBig();
        Turn getTurn();
        void takeTurn();
        string getTurnColor();
        string getPrevTurnColor();
        string colorAsString();
        string turnAsString();
        void addChip();
        bool isWon();
    private:
        vector<vector<Piece>> board;
        Turn turn;
        vector<pair<int, int>> directions;
};

