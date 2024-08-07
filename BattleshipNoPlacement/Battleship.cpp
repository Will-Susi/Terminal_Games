// Copyright 2024 William Susi

#include "Battleship.hpp"

Battleship::Battleship(string p1Name, string p2Name) {
    srand(time(NULL)); // Create seed for random generated answer
    
    p1.name = p1Name, p2.name = p2Name;

    // Start board as unshot water
    for (int row = 0; row < GAME_SIZE; row++) {
        for (int col = 0; col < GAME_SIZE; col++) {
            p1.board[row][col].spaceNum = row * GAME_SIZE + col, p2.board[row][col].spaceNum = row * GAME_SIZE + col;
            p1.board[row][col].status = '.', p2.board[row][col].status = '.';
            p1.board[row][col].color = CYAN, p2.board[row][col].color = CYAN;
        }
    }

    // Randomly place ships on both players boards
    placeShips(p1);
    placeShips(p2);

    // Player 1 starts first
    curPlayer = &p1;
    oppPlayer = &p2;
}

// Randomly places a players ships to start the game
void Battleship::placeShips(Player &p) {
    for (int i = 0; i < NUM_SHIPS; i++) {
        int row, col, dir;
        bool valid = false;
        while (!valid) {
            valid = true;
            row = rand() % (GAME_SIZE + 1 - shipSizes[i]), col = rand() % (GAME_SIZE + 1 - shipSizes[i]), dir = rand() % 2; // Random ship starting point
            for (int n = 0; n < shipSizes[i]; n++) { // Check if spots in picked direction are free and inbound
                int newRow = row + ((directions[dir]).second * n), newCol = col + ((directions[dir]).first * n);
                if (newRow < 0 || newRow > GAME_SIZE - 1 || newCol < 0 || newCol > GAME_SIZE - 1) { // Ship placement runs off board
                    valid = false;
                    break;
                } else {
                    if (p.board[newRow][newCol].status != '.' || p.board[newRow][newCol].color != CYAN) { // Ship is already located there
                        valid = false;
                        break;
                    } 
                }
            }
        }

        // Place new ship on board and in players ships
        for (int n = 0; n < shipSizes[i]; n++) {
            int newRow = row + ((directions[dir]).second * n), newCol = col + ((directions[dir]).first * n);
            p.board[newRow][newCol].status = 'O';
            p.board[newRow][newCol].color = GRAY;
            p.ships[i].spaces.push_back(Space{newRow * GAME_SIZE + newCol, 'O', GRAY});
        }

        // Name new ship
        switch(i) {           
            case 0:
                p.ships[i].name = "Aircraft Carrier";
                break;
            case 1:
                p.ships[i].name = "Battleship";
                break;
            case 2:
                p.ships[i].name = "Submarine";
                break;
            case 3:
                p.ships[i].name = "Cruiser";
                break;
            case 4:
                p.ships[i].name = "Destroyer";
                break;
        }
    }
}

// Prints the current player's board
void Battleship::printPlayerBoard(const Player p) {
    cout << "    1 2 3 4 5 6 7 8 9 10\n";
	cout << "   -------" << p.name << "-------\n";
    for (int row = 0; row < GAME_SIZE; row++) {
        printf("%c | ", 'A' + row);
        for (int col = 0; col < GAME_SIZE; col++) {
            cout << p.board[row][col].color << p.board[row][col].status << WHITE << " ";
        }
        cout << "|\n";
    }
    cout << "   --------BOARD--------\n";
}

// Prints the opponent player's board
void Battleship::printOppBoard(const Player p) {
    cout << "    1 2 3 4 5 6 7 8 9 10\n";
	cout << "   ---------OPP---------\n";
    for (int row = 0; row < GAME_SIZE; row++) {
        printf("%c | ", 'A' + row);
        for (int col = 0; col < GAME_SIZE; col++) {
            if (p.board[row][col].color == GRAY && p.board[row][col].status == 'O') { // There is a unhit ship replace it with water
                cout <<  CYAN << "." << WHITE << " ";
            } else { // Spot is empty but shot at or ship is hit or sunk and can thus just print opp view
                cout << p.board[row][col].color << p.board[row][col].status << WHITE << " ";
            }
        }
        cout << "|\n";
    }
    cout << "   --------BOARD--------\n";
}

// Prints the game state for the current player
void Battleship::printGame() {
    //system("clear");
    if (getCurPlayer()->name == "PLAYER1") {
        printOppBoard(p2);
        cout << "\n";
        printPlayerBoard(p1);
    } else {
        printOppBoard(p1);
        cout << "\n";
        printPlayerBoard(p2);
    }
}

// Returns the current player
Player* Battleship::getCurPlayer() {
    return curPlayer;
}

// Returns the opponent player
Player* Battleship::getOppPlayer() {
    return oppPlayer;
}

// Takes a valid space and updates the board/ships accordingly
void Battleship::shoot(Player &opp, int row, int col) {
    int spaceNum = row * GAME_SIZE + col;
    for (int ship = 0; ship < NUM_SHIPS; ship++) {
        for (int space = 0; space < shipSizes[ship]; space++) {
            if (opp.ships[ship].spaces[space].spaceNum == spaceNum) { // Check if there is a boat at that space
                // Update ship/board with shot/hit
                opp.ships[ship].spaces[space].status = 'X';
                opp.ships[ship].spaces[space].color = RED; 
                opp.board[row][col].status = 'X';
                opp.board[row][col].color = RED;

                // If every space in ship is 'X'/RED change every space to purple (sunk)
                if(all_of(opp.ships[ship].spaces.cbegin(), opp.ships[ship].spaces.cend(), [](const Space &s) { return (s.color == RED && s.status == 'X'); })) {
                    for (Space &s : opp.ships[ship].spaces) {
                        s.color = PURPLE;
                        opp.board[s.spaceNum / GAME_SIZE][s.spaceNum % GAME_SIZE].color = PURPLE;
                    }
                }

                // Safe to exit because shot was made
                return;
            }
        }
    }

    // Shot was a miss
    opp.board[row][col].status = 'X';
    opp.board[row][col].color = CYAN;
}

// Asks for a valid space for the player to shoot
void Battleship::playerShoot(Player &opp) {
    char r;
    int col, row;
    do {
        cout << getCurPlayer()->name << ", please enter the row character followed by the column number you would like to shoot at (Exp: 'A 10'): ";
        cin >> r >> col;
        cin.clear();
        cin.ignore(256,'\n');
        row = toupper(r) - 'A';
        col--;
    } while (row < 0 || row > GAME_SIZE - 1 || col < 0 || col > GAME_SIZE - 1 || opp.board[row][col].status == 'X'); // Keep polling for valid input until its on the board and hasn't already been shot at

    shoot(opp, row, col);
}

void Battleship::computerShoot(Player &opp) {
    // First looks for already hit ship
    for (int ship = 0; ship < NUM_SHIPS; ship++) {
        for (int space = 0; space < shipSizes[ship]; space++) {
            // Go for a calculated shot since a boat has already been hit
            if (opp.ships[ship].spaces[space].status == 'X' && opp.ships[ship].spaces[space].color == RED) {
                int row = opp.ships[ship].spaces[space].spaceNum / GAME_SIZE, col = opp.ships[ship].spaces[space].spaceNum % GAME_SIZE;
                for (pair<int, int> dir : directions) {
                    // Check for surrounding hits
                    int x = dir.first, y = dir.second;
                    int scaledRow = row + y, scaledCol = col + x;
                    if (scaledRow >= 0 && scaledRow <= GAME_SIZE - 1 && scaledCol >= 0 && scaledCol <= GAME_SIZE - 1) {
                        if (opp.board[scaledRow][scaledCol].status == 'X' && opp.board[scaledRow][scaledCol].color == RED) {
                            // OPTION 1: Adjacent hits encountered, shoot in line with hits
                            int reverses = 0, scale = 1;
                            while (reverses <= 4) {
                                scaledRow = row + y * scale, scaledCol = col + x * scale;
                                if (scaledRow >= 0 && scaledRow <= GAME_SIZE - 1 && scaledCol >= 0 && scaledCol <= GAME_SIZE - 1) {
                                    if (reverses == 2) { // If there have been 2 reverses, go back to the original hit, and look in the perpendicular directions
                                        cout << "\nCHANGE DIRECTION\n";
                                        int temp = x;
                                        x = y;
                                        y = temp;
                                        scale = 1;
                                        continue;
                                    }

                                    // Next spot is a hit, so continue in that direction
                                    if (opp.board[scaledRow][scaledCol].status == 'X' && opp.board[scaledRow][scaledCol].color == RED) {
                                        cout << "\nHit at: " << scaledRow << "," << scaledCol << "\n";
                                        scale++;
                                        continue;
                                    } else if (opp.board[scaledRow][scaledCol].status != 'X') { // Next spot is unshot, so shoot
                                        cout << "\nShooting at: " << scaledRow << "," << scaledCol  << "\n"; 
                                        shoot(opp, scaledRow, scaledCol);
                                        return;
                                    }
                                }
                                // Next spot is either a miss, a sunk boat, or out of bounds where the only option is to reverse direction
                                cout << "\nOUT OF BOUNDS or Miss at: " << scaledRow << "," << scaledCol  << "\n"; 
                                cout << "\nREVERSE\n";
                                scale = -1;
                                reverses++;
                            }

                            // SHOULD NOT GET HERE
                            cout << "\nREVERSED TOO MANY TIMES\n";
                            exit(-1);
                        }
                    }  
                }

                // OPTION 2: Shoot randomly around the hit if there were not multiple adjacent hits
                pair<int, int> dir;
                int newRow, newCol;
                do {
                    dir = directions[rand() % 4];
                    newRow = row + dir.second, newCol = col + dir.first;
                    if (newRow >= 0 && newRow <= GAME_SIZE - 1 && newCol >= 0 && newCol <= GAME_SIZE - 1) {
                        if (opp.board[newRow][newCol].status != 'X') {
                            break;
                        }
                    }
                } while (1);
                
                shoot(opp, newRow, newCol);
                return;
            }
        }
    }

    // OPTION 3: Random shot
    int row = rand() % GAME_SIZE, col = rand() % GAME_SIZE;
    while (opp.board[row][col].status == 'X' || (row + col) % 2 == 0) {
        row = rand() % GAME_SIZE, col = rand() % GAME_SIZE;
    }

    shoot(opp, row, col);
}

// Checks if all boats are hit and sunk
bool Battleship::isWon(const Player opp) {
    int hits = 0;
    for (int row = 0; row < GAME_SIZE; row++) {
        for (int col = 0; col < GAME_SIZE; col++) {
            if (opp.board[row][col].status == 'X' && opp.board[row][col].color == PURPLE) {
                hits++;
            }
        }
    }

    return (hits == 17);
}

// Changes the turn to the opponent player
void Battleship::takeTurn() {
    if (curPlayer->name == "PLAYER1") {
        curPlayer = &p2;
        oppPlayer = &p1;
    } else {
        curPlayer = &p1;
        oppPlayer = &p2;
    }
}

// Gives time for the players to swap out
void Battleship::waitForPlayer() {
    cout << "It is the other players turn. Press any key followed by 'enter' to continue...";
    cin.ignore();
    cin.get();
}