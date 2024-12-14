#include "BoardGame_Classes.h"
#include <string>
#include <vector>
#include <iostream>
#include <iomanip>
#include <cctype>  
using namespace std;

// Ultimate_board: Represents the 9x9 Ultimate Tic-Tac-Toe board.
template <typename T>
class Ultimate_board:public Board<T> {
public:
    Ultimate_board();  // Constructor
    bool update_board (int x , int y , T symbol);  // Updates the board with a symbol
    void display_board () ;  // Displays the current board state
    bool is_win() ;  // Checks if there's a winner in the game
    bool is_draw();  // Checks if the game is a draw
    bool game_is_over();  // Checks if the game has ended
};

// X_O_Player: Represents a human player in Tic-Tac-Toe
template <typename T>
class X_O_Player : public Player<T> {
public:
    X_O_Player (string name, T symbol);  // Constructor
    void getmove(int& x, int& y) ;  // Gets the player's move
};

// X_O_Random_Player: Represents a computer player making random moves
template <typename T>
class X_O_Random_Player : public RandomPlayer<T>{
public:
    X_O_Random_Player (T symbol);  // Constructor
    void getmove(int &x, int &y) ;  // Gets a random move
};

// Implementation of Ultimate_board methods

// Constructor initializes a 9x9 board
template <typename T>
Ultimate_board<T>::Ultimate_board() {
    this->rows = this->columns = 9;
    this->board = new char*[this->rows];
    for (int i = 0; i < this->rows; i++) {
        this->board[i] = new char[this->columns];
        for (int j = 0; j < this->columns; j++) {
            this->board[i][j] = 0;  // Initialize all cells to 0 (empty)
        }
    }
    this->n_moves = 0;  // Initialize move count
}

// Updates the board with the given symbol at (x, y)
template <typename T>
bool Ultimate_board<T>::update_board(int x, int y, T mark) {
    // Ensure the move is valid
    if (!(x < 0 || x >= this->rows || y < 0 || y >= this->columns) && (this->board[x][y] == 0 || mark == 0)) {
        if (mark == 0) {  // If mark is 0, undo the move
            this->n_moves--;
            this->board[x][y] = 0;
        } else {  // Place the mark
            this->n_moves++;
            this->board[x][y] = toupper(mark);  // Convert to uppercase for consistency
        }
        return true;  // Successful update
    }
    return false;  // Invalid move
}

// Displays the board state
template <typename T>
void Ultimate_board<T>::display_board() {
    for (int i = 0; i < this->rows; i++) {
        cout << "\n| ";
        for (int j = 0; j < this->columns; j++) {
            cout << "(" << i << "," << j << ")";  // Show coordinates
            cout << setw(2) << this->board[i][j] << " |";  // Display the cell value
        }
        cout << "\n-----------------------------";  // Row separator
    }
    cout << endl;
}

// Checks for a winner in the grand game
template <typename T>
bool Ultimate_board<T>::is_win() {
    T grandBoard[3][3] = {0}; // 3x3 board representing the grand game state

    // Analyze each 3x3 subgrid
    for (int subGridRow = 0; subGridRow < 3; ++subGridRow) {
        for (int subGridCol = 0; subGridCol < 3; ++subGridCol) {
            int baseRow = subGridRow * 3;
            int baseCol = subGridCol * 3;

            // Check for a win in the current subgrid
            for (int i = 0; i < 3; ++i) {
                if ((this->board[baseRow + i][baseCol] == this->board[baseRow + i][baseCol + 1] &&
                     this->board[baseRow + i][baseCol + 1] == this->board[baseRow + i][baseCol + 2] &&
                     this->board[baseRow + i][baseCol] != 0) || // Row check
                    (this->board[baseRow][baseCol + i] == this->board[baseRow + 1][baseCol + i] &&
                     this->board[baseRow + 1][baseCol + i] == this->board[baseRow + 2][baseCol + i] &&
                     this->board[baseRow][baseCol + i] != 0)) { // Column check
                    grandBoard[subGridRow][subGridCol] = this->board[baseRow + i][baseCol + i];
                    break;
                }
            }

            // Check diagonals of the subgrid
            if ((this->board[baseRow][baseCol] == this->board[baseRow + 1][baseCol + 1] &&
                 this->board[baseRow + 1][baseCol + 1] == this->board[baseRow + 2][baseCol + 2] &&
                 this->board[baseRow][baseCol] != 0) ||
                (this->board[baseRow][baseCol + 2] == this->board[baseRow + 1][baseCol + 1] &&
                 this->board[baseRow + 1][baseCol + 1] == this->board[baseRow + 2][baseCol] &&
                 this->board[baseRow][baseCol + 2] != 0)) {
                grandBoard[subGridRow][subGridCol] = this->board[baseRow + 1][baseCol + 1];
            }
        }
    }

    // Check for a win in the grand board
    for (int i = 0; i < 3; ++i) {
        if ((grandBoard[i][0] == grandBoard[i][1] && grandBoard[i][1] == grandBoard[i][2] && grandBoard[i][0] != 0) || // Row
            (grandBoard[0][i] == grandBoard[1][i] && grandBoard[1][i] == grandBoard[2][i] && grandBoard[0][i] != 0)) { // Column
            return true;
        }
    }

    // Check diagonals of the grand board
    if ((grandBoard[0][0] == grandBoard[1][1] && grandBoard[1][1] == grandBoard[2][2] && grandBoard[0][0] != 0) || 
        (grandBoard[0][2] == grandBoard[1][1] && grandBoard[1][1] == grandBoard[2][0] && grandBoard[0][2] != 0)) { 
        return true;
    }

    return false;  // No winner found
}

// Returns true if all 81 moves are made and there's no winner
template <typename T>
bool Ultimate_board<T>::is_draw() {
    return (this->n_moves == 81 && !is_win());
}

// Checks if the game is over (win or draw)
template <typename T>
bool Ultimate_board<T>::game_is_over() {
    return is_win() || is_draw();
}

// X_O_Player implementation

// Constructor initializes player name and symbol
template <typename T>
X_O_Player<T>::X_O_Player(string name, T symbol) : Player<T>(name, symbol) {}

// Gets the move coordinates from the player
template <typename T>
void X_O_Player<T>::getmove(int& x, int& y) {
    cout << "\nPlease enter your move x and y (0 to 2) separated by spaces: ";
    cin >> x >> y;
}

// X_O_Random_Player implementation

// Constructor initializes random player symbol
template <typename T>
X_O_Random_Player<T>::X_O_Random_Player(T symbol) : RandomPlayer<T>(symbol) {
    this->dimension = 9;  // Dimension of the subgrid
    this->name = "Random Computer Player";
    srand(static_cast<unsigned int>(time(0)));  // Seed the random number generator
}

// Gets a random move for the player
template <typename T>
void X_O_Random_Player<T>::getmove(int& x, int& y) {
    x = rand() % this->dimension;  // Random number between 0 and 8
    y = rand() % this->dimension;
}


