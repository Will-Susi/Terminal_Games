// Copyright 2024 William Susi

#include "ConnectFour.hpp"

// Constructor for game
ConnectFour::ConnectFour() {
    for (int h = 0; h < HEIGHT; h++) {
        vector<Piece> row;
        for (int w = 0; w < WIDTH; w++) {
            row.push_back(Piece{' ', WHITE});
        }
        board.push_back(row);
    }
    directions = {{1,0}, {1,1}, {0,1}, {-1,1}, {-1,0}, {-1,-1}, {0,-1}, {1,-1}};
    turn = PLAYER1;
}

// Prints the current game state
void ConnectFour::printGameSmall() {
    system("clear");
    cout << "  1 2 3 4 5 6 7\n";
	cout << " ---------------\n";
    for (int h = 0; h < HEIGHT; h++) {
        cout << "| ";
        for (int w = 0; w < WIDTH; w++) {
            Piece piece = board[h][w];
            cout << piece.color << piece.disk << WHITE << " ";
        }
        cout << "|\n";
    }
    cout << " ---------------\n";
}

// Prints the current game state in a different way (larger)
void ConnectFour::printGameBig() {
    system("clear");
    cout << "  1   2   3   4   5   6   7\n";
	cout << "-----------------------------\n";
    for (int h = 0; h < HEIGHT; h++) {
        cout << "| ";
        for (int w = 0; w < WIDTH; w++) {
            Piece piece = board[h][w];
            cout << piece.color << piece.disk << WHITE << " | ";
        }
        cout << "\n-----------------------------\n";
    }
}

// Returns who's turn it currently is
Turn ConnectFour::getTurn() {
    return turn;
}

// Changes the who's turn it is
void ConnectFour::takeTurn() {
    if (turn == PLAYER1) {
        turn = PLAYER2;
    } else {
        turn = PLAYER1;
    }
}

// Returns the color associated with the respective player
string ConnectFour::getTurnColor() {
    if (turn == PLAYER1) {
        return RED;
    }
    return YELLOW;
}

// Gets the previos players color
string ConnectFour::getPrevTurnColor() {
    if (turn == PLAYER1) {
        return YELLOW;
    }
    return RED;
}


// Returns the name of the color corresponding to each player
string ConnectFour::colorAsString() {
    if (turn == PLAYER1) {
        return "Red";
    }
    return "Yellow";
}

// Returns a string of whose turn it is
string ConnectFour::turnAsString() {
    if (turn == PLAYER1) {
        return "Player 1";
    } else {
        return "Player 2";
    }
}

// Gets a valid chip placement from the current player and adds it to the board
void ConnectFour::addChip() {
    bool isValid = true;
    int col;
    do {
        // Change response based on if they are re-placeing
        if (isValid) {
            cout << turnAsString() << " (" << colorAsString() << "), please pick a column to add your chip (1-7): ";
        } else {
            cout << "That was not a valid placement. " << turnAsString() << " (" << colorAsString() << "), please pick a column to add your chip (1-7): ";
        }
        
        // Get placement
        int placement;
        cin >> placement;

        // Check if placement is valid (in the game space)
        if (placement >= 1 && placement <= 7 && board[0][placement - 1].disk != 'O' && !(cin.fail())) {
            col = placement - 1;
            break;
        } else {
            cin.clear();
            cin.ignore(256,'\n');
            isValid = false;
        }
    }
    while (1);

    // Add piece to board
    for (int h = HEIGHT - 1; h >= 0; h--) {
        if (board[h][col].disk != 'O') {
            board[h][col].disk = 'O';
            board[h][col].color = getTurnColor();
            break;
        }
    }
}

// Checks all possible winning combinations to see if a player has won
bool ConnectFour::isWon() {
    string color = getPrevTurnColor();
    for (int h = HEIGHT - 1; h >= 0; h--) {
        for (int w = 0; w < WIDTH; w++) {
            if (board[h][w].color == color) {
                for (int i = 0; i < 8; i++) {
                    int x = directions[i].first, y = directions[i].second;
                    if (w + x * 3 >= 0 && w + x * 3 < WIDTH && h + y * 3 >= 0 && h + y * 3 < HEIGHT) {
                        if (board[h + y][w + x].color == color && board[h + y * 2][w + x * 2].color == color&& board[h + y * 3][w + x * 3].color == color) {
                            return true;  
                        }
                    }
                }
            }
        }
    }
    return false;
}