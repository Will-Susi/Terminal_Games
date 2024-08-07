// Copyright 2024 William Susi

#include "Battleship.hpp"

int main(int argc, char** argv) {
    // Get whether the user wants to play another local player or the computer
    system("clear");
    char in;
    do {
        cout << "Enter 'P' to play another PLAYER or 'C' to play the COMPUTER: ";
        cin >> in;
        cin.clear();
        cin.ignore(256,'\n');
    } while (in != 'p' && in != 'P' && in != 'c' && in != 'C'); 

    // Create game based off the above response
    string p1, p2;
    if (toupper(in) == 'P') {
        p2 = "PLAYER2";
    } else {
        p2 = "COMPUTER";
    }
    Battleship game("PLAYER1", p2);

    // Game loop
    while (1) {
        if (game.getCurPlayer()->name == "COMPUTER") {
            game.computerShoot(*game.getOppPlayer()); // Ask player to take a shot
        } else {
            game.printGame(); // Print game for current player
            game.playerShoot(*game.getOppPlayer()); // Ask player to take a shot
            game.printGame(); // Print game for current player
            if (game.getOppPlayer()->name != "COMPUTER") {
                game.waitForPlayer();
            }
        }

        // Check if the current player's opponent's boats are all sunk
        if (game.isWon(*game.getOppPlayer())) {
            game.printGame(); // Print game for current player
            cout << game.getCurPlayer()->name << " has sunk all the opponents ship and has won!\n";
            return 0;
        }

        game.takeTurn(); // Switch players turn
    }
}
