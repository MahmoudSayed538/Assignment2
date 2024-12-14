#include "BoardGame_Classes.h"
#include <string>
#include <vector>
using namespace std;


template<class T>
class Missere_Board: public Board<T>{
  public:
    Missere_Board(); 
    bool update_board(int x, int y, T symbol); 
    void display_board(); 
    bool is_win(); 
    bool is_draw(); 
    bool game_is_over(); 
};

template <class T>
class Missere_player: public Player<T>
{
  public:
    Missere_player(string name, T symbol); 
    void getmove(int &x, int &y); 
    T getsymbol(); 
};

template <typename T>
class Missere_comp : public RandomPlayer<T>{
public:
    Missere_comp(T symbol); 
    void getmove(int &x, int &y); 
};

// Static flags to track win states
static bool flag = 0;

///////////////////////////////////////////////// Implementation

// Constructor: Initializes a 3x3 board with all cells empty
template <class T>
Missere_Board<T>::Missere_Board() {
  this->rows = this->columns = 3;
  this->board = new char*[3];
  for(int i = 0; i < 3; i++) {
    this->board[i] = new char[this->columns];
    for(int j = 0; j < 3; j++) {
      this->board[i][j] = 0;
    }
  }
  this->n_moves = 0;
}

// Updates the board at position (x, y) with the given symbol
// Returns true if the update is successful
template <class T>
bool Missere_Board<T>::update_board(int x, int y, T symbol) {

    // Check for valid coordinates and empty cell
    if (!(x < 0 || x >= this->rows || y < 0 || y >= this->columns) && (this->board[x][y] == 0 || symbol == 0)) {
        if (symbol == 0) {
            this->n_moves--; // Undo move
            this->board[x][y] = 0;
        } else {
            this->n_moves++; // Place new symbol
            this->board[x][y] = toupper(symbol);
        }
        return true;
    }
    return false; // Invalid move
}

// Displays the current state of the board
template <class T>
void Missere_Board<T>::display_board() {
    for (int i = 0; i < this->rows; i++) {
        cout << "\n|| ";
        for (int j = 0; j < this->columns; j++) {
            cout << "(" << i << "," << j << ")";
            cout << this->board[i][j] << " ||";
        }
        cout << "\n-----------------------------";
    }
    cout << endl;
}

// Checks if there's a win condition
template <class T>
bool Missere_Board<T>::is_win() {
    if (flag == true ) return true; //returns a win in the second turn

    // Check rows and columns
    for (int i = 0; i < this->rows; i++) {
        if (this->board[i][0] == this->board[i][1] && this->board[i][1] == this->board[i][2] && this->board[i][0] != 0) {
            flag = true;
        }

        if (this->board[0][i] == this->board[1][i] && this->board[1][i] == this->board[2][i] && this->board[0][i] != 0) {
            flag = true;

        }
    }

    // Check diagonals
    if (this->board[0][0] == this->board[1][1] && this->board[1][1] == this->board[2][2] && this->board[0][0] != 0) {
            flag = true;

    }
    if (this->board[0][2] == this->board[1][1] && this->board[1][1] == this->board[2][0] && this->board[0][2] != 0) {
            flag = true;

    }

    return false; // No win condition met
}

// Checks if the game is a draw
template <class T>
bool Missere_Board<T>::is_draw() {
    return (this->n_moves == 9 && !is_win());
}

// Checks if the game is over (win or draw)
template <class T>
bool Missere_Board<T>::game_is_over() {
    return (is_draw() || is_win());
}

// Missere Player constructor: initializes player with name and symbol
template <class T>
Missere_player<T>::Missere_player(string name, T symbol) : Player<T>(name, symbol) {}

// Gets move input from the human player
template <typename T>
void Missere_player<T>::getmove(int& x, int& y) {
    if (flag == true) return ; // if one of the players have won it doesn't update the second player's move
    cout << "\nPlease enter your move x and y (0 to 2) separated by spaces: ";
    cin >> x >> y;
}

// Missere Computer Player constructor: initializes with random move generation
template <typename T>
Missere_comp<T>::Missere_comp(T symbol) : RandomPlayer<T>(symbol) {
    this->dimension = 3;
    this->name = " Computer Player";
    srand(static_cast<unsigned int>(time(0)));  // Seed for randomness
}

// Generates a random move for the computer player
template <typename T>
void Missere_comp<T>::getmove(int& x, int& y) {
    x = rand() % this->dimension; 
    y = rand() % this->dimension;
}

