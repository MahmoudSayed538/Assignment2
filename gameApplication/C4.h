
#ifndef _C4_H
#define _C4_H

#include "BoardGame_Classes.h"

template <typename T>
class connectFourBoard:public Board<T> {
public:
    connectFourBoard ();
    bool update_board (int x , int y , T symbol);
    void display_board () ;
    bool is_win() ;
    bool is_draw();
    bool game_is_over();

};

template <typename T>
class connectFourPlayer : public Player<T> {
public:
    connectFourPlayer (string name, T symbol);
    void getmove(int& x, int& y) ;

};

template <typename T>
class connectFourRPlayer : public RandomPlayer<T>{
    int dimension2;
public:
    connectFourRPlayer (T symbol);
    void getmove(int &x, int &y) ;
};





//--------------------------------------- IMPLEMENTATION

#include <iostream>
#include <iomanip>
#include <cctype>  // for toupper()

using namespace std;

// Constructor for X_O_Board
template <typename T>
connectFourBoard<T>::connectFourBoard() {
    this->rows = 6;
    this->columns=7;
    this->board = new char*[this->rows];
    for (int i = 0; i < this->rows; i++) {
        this->board[i] = new char[this->columns];
        for (int j = 0; j < this->columns; j++) {
            this->board[i][j] = 0;
        }
    }
    this->n_moves = 0;
}

template <typename T>
bool connectFourBoard<T>::update_board(int x, int y, T mark) {
    // Only update if move is valid
    if (!(x < 0 || x >= this->rows || y < 0 || y >= this->columns || (x!=5 && this->board[x+1][y]==0)) && (this->board[x][y] == 0|| mark == 0)) {
        if (mark == 0){
            this->n_moves--;
            this->board[x][y] = 0;
        }
        else {
            this->n_moves++;
            this->board[x][y] = toupper(mark);
        }

        return true;
    }
    return false;
}

// Display the board and the pieces on it
template <typename T>
void connectFourBoard<T>::display_board() {
    for (int i = 0; i < this->rows; i++) {
        cout << "\n| ";
        for (int j = 0; j <this->columns; j++) {
            cout << "(" << i << "," << j << ")";
            cout << setw(2) << this->board[i][j] << " |";
        }
        cout << "\n----------------------------------------------------------";
    }
    cout << endl;
}

// Returns true if there is any winner
template <typename T>
bool connectFourBoard<T>::is_win() {
    // Check rows.
    for(int i =0 ; i< this->rows ; i++)
    {
        for(int j = 0 ; j<4 ; j++)
        {
            if(this->board[i][j]==this->board[i][j+1] && this->board[i][j+1] == this->board[i][j+2] && this->board[i][j+2]==this->board[i][j+3] && this->board[i][j]!=0)
            {
                return true;
            }
        }
    }
    // check columns
    for(int i = 0 ; i<this->columns; i++)
    {
        for(int j =0 ; j<3 ; j++)
        {
            if(this->board[j][i]==this->board[j+1][i] && this->board[j+1][i] == this->board[j+2][i] && this->board[j+2][i] == this->board[j+3][i] && this->board[j][i]!=0)
            {
                return true;
            }
        }
    }
    // check diagonal top to bottom
    for (int i = 0; i <= this->rows - 4; ++i) {
        for (int j = 0; j <= this->columns - 4; ++j) {
            if (this->board[i][j] == this->board[i+1][j+1] && this->board[i+1][j+1]==this->board[i+2][j+2] && this->board[i+2][j+2] == this->board[i+3][j+3] && this->board[i][j]!=0)
            {
                return true;
            }
        }
    }

    // Check diagonal bottom to top
    for (int i = 3; i <this->rows; ++i) {
        for (int j = 0; j <= this->columns - 4; ++j) {
            if (this->board[i][j]==this->board[i-1][j+1] && this->board[i-1][j+1]==this->board[i-2][j+2] && this->board[i-2][j+2]==this->board[i-3][j+3] && this->board[i][j]!=0) {
                return true;
            }
        }
    }

    return false;
}

// Return true if 42 moves are done and no winner
template <typename T>
bool connectFourBoard<T>::is_draw() {
    return (this->n_moves == 42 && !is_win());
}

template <typename T>
bool connectFourBoard<T>::game_is_over() {
    return is_win() || is_draw();
}

//--------------------------------------

// Constructor for X_O_Player
template <typename T>
connectFourPlayer<T>::connectFourPlayer(string name, T symbol) : Player<T>(name, symbol) {}

template <typename T>
void connectFourPlayer<T>::getmove(int& x, int& y) {
    cout << "\nPlease enter your move x and y (0 to 5 for x and 0 to 6 for y) separated by spaces: ";
    cin >> x >> y;
}

// Constructor for X_O_Random_Player
template <typename T>
connectFourRPlayer<T>::connectFourRPlayer(T symbol) : RandomPlayer<T>(symbol) {
    this->dimension = 6;
    this->dimension2 = 7;
    this->name = "Random Computer Player";
    srand(static_cast<unsigned int>(time(0)));  // Seed the random number generator
}

template <typename T>
void connectFourRPlayer<T>::getmove(int& x, int& y) {
    x = rand() % this->dimension;  // Random number between 0 and 5
    y = rand() % this->dimension2;  // Random number between 0 and 6;
}







#endif //_C4_H

