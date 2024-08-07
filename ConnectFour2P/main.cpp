// Copyright 2024 William Susi

#include "ConnectFour.hpp"

int main() {
    system("clear");
    ConnectFour game;

    // Game loop
    while(!game.isWon()) {
        game.printGameBig(); // Can swap for game.printGameSmall()
        game.addChip();
        game.takeTurn();
    }

    game.printGameBig(); // Can swap for game.printGameSmall()
    game.takeTurn();
    cout << game.turnAsString() << " (" << game.colorAsString() << ") has won!" << endl;
    
    return 0;
}