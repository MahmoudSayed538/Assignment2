
#ifndef _NUMTIC_H
#define _NUMTIC_H

#include "BoardGame_Classes.h"
#include <vector>
using namespace std;

template <typename T>
class NT_Board:public Board<T> {
    vector<int> odd = {1,3,5,7,9};
    vector<int> even = {2,4,6,8};
public:
    NT_Board ();
    bool update_board (int x , int y , T symbol);
    void display_board () ;
    bool is_win() ;
    bool is_draw();
    bool game_is_over();

};

template <typename T>
class NT_Player : public Player<T> {
public:
    NT_Player (string name, T number);
    void getmove(int& x, int& y) ;
};

template <typename T>
class NT_Random_Player : public RandomPlayer<T>{
    int order;
public:
    NT_Random_Player (T symbol,int order);
    void getmove(int &x, int &y) ;
};





//--------------------------------------- IMPLEMENTATION

#include <iostream>
#include <iomanip>
#include <cctype>  // for toupper()

using namespace std;

// Constructor for X_O_Board
template <typename T>
NT_Board<T>::NT_Board() {
    this->rows = this->columns = 3;
    this->board = new int*[this->rows];
    for (int i = 0; i < this->rows; i++) {
        this->board[i] = new int[this->columns];
        for (int j = 0; j < this->columns; j++) {
            this->board[i][j] = 0;
        }
    }
    this->n_moves = 0;
}

template <typename T>
bool NT_Board<T>::update_board(int x, int y, T number) {
    // Only update if move is valid
    bool valid;
    valid = (this->n_moves % 2 == 0) && (count(this->odd.begin(),this->odd.end(),number)!=0) || ((this->n_moves % 2 != 0) && (count(this->even.begin(),this->even.end(),number)!=0));
    if (!(x < 0 || x >= this->rows || y < 0 || y >= this->columns || !valid) && (this->board[x][y] == 0 || number == 0)) {
        if (number == 0){
            this->n_moves--;
            this->board[x][y] = 0;
        }
        else {
            this->n_moves++;
            this->board[x][y] = number;
            if(number%2 == 0)
            {
                 even.erase(remove(even.begin(), even.end(), number), even.end());
            }else
            {
                 odd.erase(remove(odd.begin(), odd.end(), number), odd.end());
            }
        }

        return true;
    }
    return false;
}

// Display the board and the pieces on it
template <typename T>
void NT_Board<T>::display_board() {
    for (int i = 0; i < this->rows; i++) {
        cout << "\n| ";
        for (int j = 0; j < this->columns; j++) {
            cout << "(" << i << "," << j << ")";
            cout << setw(2) << this->board[i][j] << " |";
        }
        cout << "\n-----------------------------";
    }
    cout << endl;
}

// Returns true if there is any winner
template <typename T>
bool NT_Board<T>::is_win() {
    // Check rows and columns
    for (int i = 0; i < this->rows; i++) {
        if ((this->board[i][0] + this->board[i][1] + this->board[i][2] == 15) ||
            (this->board[0][i] + this-> board[1][i] + this->board [2][i] == 15)) {
            return true;
        }
    }

    // Check diagonals
    if ((this->board[0][0] + this->board[1][1] + this->board[2][2] == 15) ||
        (this->board[0][2] + this->board[1][1] + this->board[2][0] == 15)) {
        return true;
    }

    return false;
}

// Return true if 9 moves are done and no winner
template <typename T>
bool NT_Board<T>::is_draw() {
    return (this->n_moves == 9 && !is_win());
}

template <typename T>
bool NT_Board<T>::game_is_over() {
    return is_win() || is_draw();
}

//--------------------------------------

// Constructor for NT_Player
template <typename T>
NT_Player<T>::NT_Player(string name, T order) : Player<T>(name, order) {}

template <typename T>
void NT_Player<T>::getmove(int& x, int& y) {
    cout << "\nPlease enter your move x and y (0 to 2) separated by spaces: ";
    cin>>x>>y;
    cout <<"\nPlease enter your number: ";
    int n;
    cin>>n;
    this->symbol=n;
}

// Constructor for X_O_Random_Player
template <typename T>
NT_Random_Player<T>::NT_Random_Player(T symbol,int number) : RandomPlayer<T>(symbol) {
    this->dimension = 3;
    this->name = "Random Computer Player";
    this->order = number;
    srand(static_cast<unsigned int>(time(0)));  // Seed the random number generator
}

template <typename T>
void NT_Random_Player<T>::getmove(int& x, int& y) {
    x = rand() % this->dimension;  // Random number between 0 and 2
    y = rand() % this->dimension;
    int n;
    if(this->order==1)
    {
        n=rand() % 5;
        int arr[5]={1,3,5,7,9};
        this->symbol=arr[n];
    }else
    {
        n=rand() % 4;
        int arr[4]={2,4,6,8};
        this->symbol=arr[n];
    }
}







#endif //_NUMTIC_H

