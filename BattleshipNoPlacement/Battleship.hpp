// Copyright 2024 William Susi

#include <iostream>
#include <algorithm>
#include <string>
#include <vector>

using namespace std;

#define WHITE "\033[37m"
#define GRAY "\033[90m"
#define CYAN "\033[36m"
#define RED "\033[31m"
#define PURPLE "\033[35m"

#define GAME_SIZE 10
#define NUM_SHIPS 5

struct Space {
    int spaceNum; // 0 - 99
    char status; // '.' = Unshot, 'O' = Unshot Boat, 'X' = Shot, 
    string color; // CYAN = Unshot or Miss, GRAY = Boat, RED = Boat Hit, PURPLE = Boat Sunk
};

struct Ship {
    string name; // Aircraft Carrier, Battleship, Submarine, Cruiser, Destroyer
    vector<Space> spaces;
};

struct Player {
    string name; // PLAYER1, PLAYER2, COMPUTER
    Ship ships [NUM_SHIPS];
    Space board [GAME_SIZE][GAME_SIZE];
};

class Battleship {
 public:
    Battleship(string p1Name, string p2Name);
    void placeShips(Player &p);
    void printPlayerBoard(const Player p);
    void printOppBoard(const Player p);
    void printGame();
    Player* getCurPlayer();
    Player* getOppPlayer();
    void shoot(Player &opp, int row, int col);
    void playerShoot(Player &opp);
    void computerShoot(Player &opp);
    bool isWon(const Player opp);
    void takeTurn();
    void waitForPlayer();

 private:
    int shipSizes [NUM_SHIPS] = {5, 4, 3, 3, 2};
    pair<int, int> directions[4] = {{1,0}, {0,-1}, {-1,0}, {0,1}};
    Player *curPlayer;
    Player *oppPlayer;
    Player p1;
    Player p2;
};
