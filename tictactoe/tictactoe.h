#pragma once

// Name: Ian Thomas
// Date: 2/25/21
// Description: Write a program that uses 2D vector to play tic-tac-toe

#include <iostream>
#include <vector>

using std::endl;
using std::cout;
using std::cin;
using std::vector;
using std::string;

class Board {
    public:
        Board() : field{vector<vector<char>> (3, vector<char> (3,'_'))}, moves{vector<vector<string>> (3, vector<string> (3))} {}
        void addMoves();
        void printBoard() const;
        int turn(int player);
        bool horizontalCheck();
        bool verticalCheck();
        bool diagonalCheck();

    private:
        vector<vector<char>> field;
        vector<vector<string>> moves;

};

// Adds all moves to the 2D moves vector
void Board::addMoves() {
    int a = '0';
    for (int i = 0; i < 3; ++i)
        for (int j = 0; j < 3; ++j)
            moves[i][j] = a++;
}

/*
 * Prints the 3x3 Tic-Tac-Toe board and Move Pad (with available moves)
 * 
 * Parameters:
 *      fields: vector<vector<char>>, 2D vector that stores characters 'X' and 'O'
 *       moves: vector<vector<string>>, 2D vector that stores numbers and blank spaces '_'
 */
void Board::printBoard() const {
    for (int i = 0; i < 3; ++i){
        for (int j = 0; j < 3; ++j){
            cout << field[i][j] << " ";
        }

        cout << " | ";

        for (int j = 0; j < 3; ++j)
            cout << moves[i][j] << " ";


        cout << endl;
    }
}

/*
 * Prompts the given player to make a valid move, and updates the board accordingly
 * 
 * Parameters:
 *      player: int, Player number - 0 or 1
 *      fields: vector<vector<char>>, 2D vector to store characters 'X' and 'O'
 *       moves: vector<vector<string>>, 2D vector to replace moves with blank spaces '_'
 */
int Board::turn(int player){
    int choice;
    if (player == 0){
        cout << "Player 1: ";
        cin >> choice;

        // Validates move
        bool validated = false;
        for (int i = 0; i < 3; ++i){
            for (int j = 0; j < 3; ++j){
                if (std::to_string(choice) == moves[i][j])
                    validated = true;
            }
        }

        if (!validated){
            std::cerr << "Invalid choice. Try again." << endl; 
            return 1;
        }

        // Places 'X' on board and replaces move with blank space
        if (choice >= 0 && choice < 3) { field[0][choice % 3] = 'X'; moves[0][choice % 3] = '_';}
        else if (choice > 2 && choice < 6) { field[1][choice % 3] = 'X'; moves[1][choice % 3] = '_';}
        else if (choice > 5 && choice < 9) { field[2][choice % 3] = 'X'; moves[2][choice % 3] = '_';}
        else { std::cerr << "Invalid choice. Try Again." << endl; return 1;}

    } else {
        cout << "Player 2: ";
        cin >> choice;

        // Validates move
        bool validated = false;
        for (int i = 0; i < 3; ++i){
            for (int j = 0; j < 3; ++j){
                if (std::to_string(choice) == moves[i][j])
                    validated = true;
            }
        }

        if (!validated){
            std::cerr << "Invalid choice. Try again." << endl; 
            return 1;
        }

        // Places 'O' on board and replaces move with blank space
        if (choice >= 0 && choice < 3) { field[0][choice % 3] = 'O'; moves[0][choice % 3] = '_';}
        else if (choice > 2 && choice < 6) { field[1][choice % 3] = 'O'; moves[1][choice % 3] = '_';}
        else if (choice > 5 && choice < 9) { field[2][choice % 3] = 'O'; moves[2][choice % 3] = '_';}
        else { std::cerr << "Invalid choice. Try Again." << endl; return 1;}
    }

    return 0;
}

// Checks from horizontal matches of 3 in the 3x3 passed 2D vector
bool Board::horizontalCheck() {
    for (int i = 0; i < 3; ++i){
        if (field[i][0] == field[i][1] && field[i][1] == field[i][2] && field[i][0] != '_'){
            return true;
        }
    }

    return false;
}

// Checks for vertical matches of 3 in the passed 3x3 2D vector
bool Board::verticalCheck() {
    for (int i = 0; i < 3; ++i){
        if (field[0][i] == field[1][i] && field[1][i] == field[2][i] && field[0][i] != '_'){
            return true;
        }
    }

    return false;

}

// Checks for diagonal matches of 3 in the passed 3x3 2D vector
bool Board::diagonalCheck() {
    if (field[0][0] == field[1][1] && field[1][1] == field[2][2] && field[0][0] != '_')
        return true;
    else if (field[2][0] == field[1][1] && field[1][1] == field[0][2] && field[0][2] != '_')
        return true;
    else { return false; }
}
