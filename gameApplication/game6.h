
#ifndef _GAME6_H
#define _GAME6_H


#include "BoardGame_Classes.h"
#include <string>
#include <vector>
using namespace std;

// Template class for Missere_Board inheriting from Board
// Represents the game board for Missere Tic Tac Toe
template<class  T>
class Missere_Board: public Board<T>{
  public:
 
    Missere_Board(); // Constructor to initialize the board
    bool update_board(int x, int y, T symbol); // Updates the board with a player's move
    void display_board(); // Displays the current state of the board
    bool is_win(); // Checks if there's a winning condition
    bool is_draw(); // Checks if the game is a draw
    bool game_is_over(); // Checks if the game is over
};

// Template class for Missere_player inheriting from Player
// Represents a human player in the game
template <class T>
class Missere_player: public Player<T>
{
  public:

  Missere_player(string name, T symbol); // Constructor to initialize a player
  void getmove(int &x, int &y); // Gets the player's move from input
  T getsymbol(); // Gets the player's symbol
};

// Template class for Missere_comp inheriting from RandomPlayer
// Represents a computer player with random moves
template <typename T>
class Missere_comp : public RandomPlayer<T>{
public:
    Missere_comp(T symbol); // Constructor to initialize the computer player
    void getmove(int &x, int &y); // Generates a random move for the computer
};

// Static variables to track if a player has won
static bool x_flag = 0; // Indicates if player X has won
static bool o_flag = 0; // Indicates if player O has won

///////////////////////////////////////////////Implementation

// Constructor for Missere_Board template
// Initializes a 3x3 game board
template <class T>
Missere_Board<T>::Missere_Board() {
  this->rows = this->columns = 3;
  this->board = new char*[3];

  for(int i = 0; i < 3; i++) {
    this->board[i] = new char[this->columns];
    for(int j = 0; j < 3; j++) {
      this->board[i][j] = 0; // Initialize all board cells to 0
    }
  }
  this->n_moves = 0; // Initialize move count to 0
}

// Updates the board with a player's move or undoes a move
template <class T>
bool Missere_Board<T>::update_board(int x, int y, T symbol) {
    if(x_flag == true) return true; // If player X has already won, return
    if(o_flag == true) return true ; // If player O has already won, return

    // Check if the move is valid
    if(!(x < 0 || x >= this->rows || y < 0 || y >= this->columns) && (this->board[x][y] == 0 || symbol == 0)) {
        if(symbol == 0) { // Undo a move if symbol is 0
            this->n_moves--;
            this->board[x][y] = 0;
        } else { // Add a move
            this->n_moves++;
            this->board[x][y] = toupper(symbol);
        }
        return true;
    }
    return false; // Invalid move
}

// Displays the current board state
template <class T>
void Missere_Board<T>::display_board() {
    for (int i = 0; i < this->rows; i++) {
        cout << "\n|| ";
        for (int j = 0; j < this->columns; j++) {
            cout << "(" << i << "," << j << ")"; // Display cell coordinates
            cout << this->board[i][j] << " ||";
        }
        cout << "\n-----------------------------";
    }
    cout << endl;
}

// Checks if there's a winning condition
template <class T>
bool Missere_Board<T>::is_win() {
    if(x_flag == true) return true; // Player X has already won
    if(o_flag == true) return true; // Player O has already won
       
    // Check rows and columns for a win
    for (int i = 0; i < this->rows; i++) {
        if (this->board[i][0] == this->board[i][1] && this->board[i][1] == this->board[i][2] && this->board[i][0] != 0) {
            if (this->board[i][0] == 'X') x_flag = true;
            if (this->board[i][0] == 'O') o_flag = true;
        }

        if (this->board[0][i] == this->board[1][i] && this->board[1][i] == this->board[2][i] && this->board[0][i] != 0) {
            if (this->board[0][i] == 'X') x_flag = true;
            if (this->board[0][i] == 'O') o_flag = true;
        }
    }

    // Check diagonals for a win
    if (this->board[0][0] == this->board[1][1] && this->board[1][1] == this->board[2][2] && this->board[0][0] != 0) {
        if (this->board[0][0] == 'X') x_flag = true;
        if (this->board[0][0] == 'O') o_flag = true;
    }
    if (this->board[0][2] == this->board[1][1] && this->board[1][1] == this->board[2][0] && this->board[0][2] != 0) {
        if (this->board[0][2] == 'X') x_flag = true;
        if (this->board[0][2] == 'O') o_flag = true;
    }

    return false;
}

// Checks if the game is a draw
template <class T>
bool Missere_Board<T>::is_draw() {
    return (this->n_moves == 9 && !is_win());
}

// Checks if the game is over
template <class T>
bool Missere_Board<T>::game_is_over() {
    return (is_draw() || is_win());
}

// Constructor for Missere_player
template <class T>
Missere_player<T>::Missere_player(string name, T symbol) : Player<T>(name, symbol) {};

// Gets the player's move from input
template <typename T>
void Missere_player<T>::getmove(int& x, int& y) {
    cout << "\nPlease enter your move x and y (0 to 2) separated by spaces: ";
    cin >> x >> y;
}

// Constructor for Missere_comp
// Initializes a random computer player
template <typename T>
Missere_comp<T>::Missere_comp(T symbol) : RandomPlayer<T>(symbol) {
    this->dimension = 3;
    this->name = " Computer Player";
    srand(static_cast<unsigned int>(time(0)));  // Seed for random number generation
}

// Generates a random move for the computer player
template <typename T>
void Missere_comp<T>::getmove(int& x, int& y) {
    x = rand() % this->dimension; 
    y = rand() % this->dimension;
}





#endif //_GAME6_H

