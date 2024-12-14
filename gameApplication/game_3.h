#include "BoardGame_Classes.h"
#include <string>
#include <utility>
#include <vector>
using namespace std;

template <typename T>
class Five_XO:public Board<T> {
public:
    Five_XO (); // Constructor
    bool update_board (int x , int y , T symbol); 
    void display_board (); 
    bool is_win(); 
    bool is_draw(); 
    bool game_is_over(); 
};

template <typename T>
class Five_XO_Player : public Player<T> {
public:
    Five_XO_Player (string name, T symbol); 
    void getmove(int& x, int& y); 
};

template <typename T>
class Five_XO_Random : public RandomPlayer<T>{
public:
    Five_XO_Random (T symbol); 
    void getmove(int &x, int &y); 
};

//--------------------------------------- IMPLEMENTATION

#include <iostream>
#include <iomanip>
#include <cctype>  // for toupper()

using namespace std;

// Constructor for Five_XO
// Initializes the game board with a 5x5 grid and sets all cells to 0.
template <typename T>
Five_XO<T>::Five_XO() {
    this->rows = this->columns = 5;
    this->board = new char*[this->rows];
    for (int i = 0; i < this->rows; i++) {
        this->board[i] = new char[this->columns];
        for (int j = 0; j < this->columns; j++) {
            this->board[i][j] = 0; // Initialize all cells to 0
        }
    }
    this->n_moves = 0; 
}

// Updates the board with a move and increments/decrements move count based on the input.
template <typename T>
bool Five_XO<T>::update_board(int x, int y, T mark) {
    if (!(x < 0 || x >= this->rows || y < 0 || y >= this->columns) && (this->board[x][y] == 0 || mark == 0)) {
        if (mark == 0){
            this->n_moves--; // Decrease move count if mark is 0
            this->board[x][y] = 0;
        } else {
            this->n_moves++; // Increase move count for a valid mark
            this->board[x][y] = toupper(mark); 
        }
        return true;
    }
    return false; // Return false if the move is invalid
}

// Displays the board with coordinates and values in a formatted grid.
template <typename T>
void Five_XO<T>::display_board() {
    cout << "\n------------------------------------------------";
    for (int i = 0; i < this->rows; i++) {
        cout << "\n|| ";
        for (int j = 0; j < this->columns; j++) {
            cout << "(" << i << "," << j << ")";
            cout << setw(2) << this->board[i][j] << " ||";
        }
        cout << "\n------------------------------------------------";
    }
    cout << endl;
}

// Static variables to track wins for player 1 and player 2
static int p1;
static int p2;

// Checks if a player has won based on various conditions.
template <class T>
bool Five_XO<T>::is_win() {
    if (this->n_moves == 23) { // Check conditions for Player 1
        int temp = 0;
        for (int i = 0; i < 5; i++) {
            for (int j = 0; j < 5; j++) {
                // Check vertical, horizontal, and diagonal lines of 3
                if (i + 2 < 5 && this->board[i][j] == this->board[i + 1][j] &&
                    this->board[i + 1][j] == this->board[i + 2][j] && this->board[i][j] != 0) {
                    temp++;
                }

                if (j + 2 < 5 && this->board[i][j] == this->board[i][j + 1] &&
                    this->board[i][j + 1] == this->board[i][j + 2] && this->board[i][j] != 0) {
                    temp++;
                }

                if (i + 2 < 5 && j + 2 < 5 && this->board[i][j] == this->board[i + 1][j + 1] &&
                    this->board[i + 1][j + 1] == this->board[i + 2][j + 2] && this->board[i][j] != 0) {
                    temp++;
                }

                if (i + 2 < 5 && j - 2 >= 0 && this->board[i][j] == this->board[i + 1][j - 1] &&
                    this->board[i + 1][j - 1] == this->board[i + 2][j - 2] && this->board[i][j] != 0) {
                    temp++;
                }
            }
        }
        p1 = temp;

    } else if (this->n_moves == 24) { // Check conditions for Player 2
        int temp = 0;
        for (int i = 0; i < 5; i++) {
            for (int j = 0; j < 5; j++) {
                // Same checks as above for Player 2
                if (i + 2 < 5 && this->board[i][j] == this->board[i + 1][j] &&
                    this->board[i + 1][j] == this->board[i + 2][j] && this->board[i][j] != 0) {
                    temp++;
                }

                if (j + 2 < 5 && this->board[i][j] == this->board[i][j + 1] &&
                    this->board[i][j + 1] == this->board[i][j + 2] && this->board[i][j] != 0) {
                    temp++;
                }

                if (i + 2 < 5 && j + 2 < 5 && this->board[i][j] == this->board[i + 1][j + 1] &&
                    this->board[i + 1][j + 1] == this->board[i + 2][j + 2] && this->board[i][j] != 0) {
                    temp++;
                }

                if (i + 2 < 5 && j - 2 >= 0 && this->board[i][j] == this->board[i + 1][j - 1] &&
                    this->board[i + 1][j - 1] == this->board[i + 2][j - 2] && this->board[i][j] != 0) {
                    temp++;
                }
            }
        }
        p2 = temp;
    }

    if (p2 > p1) {
        return true; // Player 2 wins
    } else if (p1 == p2) {
        return false; // Tie
    } else {
        if(this->n_moves == 25)
        {
            return true; // win condition for player 2
        } 
    }

    return false; 
}
  

// Checks if the game is a draw.
template <typename T>
bool Five_XO<T>::is_draw() {
    return (this->n_moves == 24 && !is_win());
}

// Determines if the game is over (either win or draw).
template <typename T>
bool Five_XO<T>::game_is_over() {
    return is_win() || is_draw();
}

//--------------------------------------

// Constructor for Five_XO_Player
// Initializes the player with a name and symbol.
template <typename T>
Five_XO_Player<T>::Five_XO_Player(string name, T symbol) : Player<T>(name, symbol) {}

// Prompts the player to enter their move.
template <typename T>
void Five_XO_Player<T>::getmove(int& x, int& y) {
    cout << "\nPlease enter your move x and y (0 to 2) separated by spaces: ";
    cin >> x >> y;
    
}

// Constructor for Five_XO_Random
// Initializes the random player with a symbol and sets a random seed.
template <typename T>
Five_XO_Random<T>::Five_XO_Random(T symbol) : RandomPlayer<T>(symbol) {
    this->dimension = 5;
    this->name = "Random Computer Player";
    srand(static_cast<unsigned int>(time(0)));  
}

// Generates a random move for the AI player.
template <typename T>
void Five_XO_Random<T>::getmove(int& x, int& y) {
    x = rand() % this->dimension;  
    y = rand() % this->dimension;
}

