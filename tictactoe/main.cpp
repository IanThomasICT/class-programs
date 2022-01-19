// Name: Ian Thomas
// Date: 2/25/21
// Description: Write a program that uses 2D vector to play tic-tac-toe

#include <iostream>
#include "tictactoe.h"

int main()
{
    
    // Build the Board
    Board Game;
    Game.addMoves();

    // Game Header
    cout << "== Tic-Tac-Toe! ==" << endl 
         << "Enter a number to make your move." << endl; 
    Game.printBoard();
    
    // Begin Game
    int i = 0;
    bool win = false;
    int player;

    while (!win){
        player = (i % 2)+1;
        int status = Game.turn(i % 2); // Checks for error
        Game.printBoard();

        // cout << "Move: " << i << ", Status: " << status << endl;
        // Checks for all combination of wins
        if (i > 4) { 
            switch(0){
            case 0 : if (Game.horizontalCheck() == true) { win = true; break; };
            case 1 : if (Game.verticalCheck() == true) { win = true; break; };
            case 2 : if (Game.diagonalCheck() == true) { win = true; break; };
            default: break;
            }
        } 
        
        if (status == 0) // If there is no error, move to next player's turn
            i++;
        
        if (i > 8 && win != true){
            cout << "It's a tie!" << endl;
            return 1;
        }

    }

    cout << "Player " << player << " wins!" << endl;
    
    return 0;
}
