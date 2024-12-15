
#ifndef _SUS_H
#define _SUS_H

#include "BoardGame_Classes.h"
#include <set>
#include <algorithm>
template <typename T>
class SUS_Board:public Board<T> {
    int scoreS;
    int scoreU;
    set <int> counted;
public:
    SUS_Board ();
    bool update_board (int x , int y , T symbol);
    void display_board () ;
    bool is_win() ;
    bool is_draw();
    bool game_is_over();

};

template <typename T>
class SUS_Player : public Player<T> {
public:
    SUS_Player (string name, T symbol);
    void getmove(int& x, int& y) ;

};

template <typename T>
class SUS_Random_Player : public RandomPlayer<T>{
public:
    SUS_Random_Player (T symbol);
    void getmove(int &x, int &y) ;
};





//--------------------------------------- IMPLEMENTATION

#include <iostream>
#include <iomanip>
#include <cctype>  // for toupper()

using namespace std;

// Constructor for X_O_Board
template <typename T>
SUS_Board<T>::SUS_Board() {
    this->rows = this->columns = 3;
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
bool SUS_Board<T>::update_board(int x, int y, T mark) {
    // Only update if move is valid
    if (!(x < 0 || x >= this->rows || y < 0 || y >= this->columns) && (this->board[x][y] == 0|| mark == 0)) {
        if (mark == 0){
            this->n_moves--;
            this->board[x][y] = 0;
        }
        else {
            this->n_moves++;
            this->board[x][y] = toupper(mark);
            //checking rows.
            for(int i = 0 ; i<this->rows ; i++)
            {
                if(count(counted.begin(),counted.end(),i) != 0)
                {
                    continue;
                }
                else if(this->board[i][0]=='S' && this->board[i][1]=='U' && this->board[i][2]=='S')
                {
                   if(mark == 'S')
                   {
                       scoreS++;
                       counted.insert(i);
                   }else
                   {
                       scoreU++;
                       counted.insert(i);
                   }
                       
                }
            }
            //checking columns.
            for(int j = 0 ; j<this->columns ; j++)
            {
                if(count(counted.begin(),counted.end(),j+3)!=0)
                {
                    continue;
                }else if(this->board[0][j]=='S' && this->board[1][j] == 'U' && this->board[2][j]=='S')
                {
                    if(mark=='S')
                    {
                        scoreS++;
                        counted.insert(j+3);
                    }else
                    {
                        scoreU++;
                        counted.insert(j+3);
                    }
                }
            }
            //checking diagonals.
            if(this->board[0][0]=='S' && this->board[1][1] =='U' && this->board[2][2]=='S' && count(counted.begin(),counted.end(),6) == 0)
            {
                if(mark == 'S')
                {
                    scoreS++;
                    counted.insert(6);
                }else
                {
                    scoreU++;
                    counted.insert(6);
                }
            }if(this->board[0][2]=='S' && this->board[1][1]=='U' && this->board[2][0]=='S' && count(counted.begin(),counted.end(),7)==0)
            {
                if(mark=='S')
                {
                    scoreS++;
                    counted.insert(7);
                }else
                {
                    scoreU++;
                    counted.insert(7);
                }
            }
        }

        return true;
    }
    return false;
}

// Display the board and the pieces on it
template <typename T>
void SUS_Board<T>::display_board() {
    for (int i = 0; i < this->rows; i++) {
        cout << "\n| ";
        for (int j = 0; j < this->columns; j++) {
            cout << "(" << i << "," << j << ")";
            cout << setw(2) << this->board[i][j] << " |";
        }
        cout << "\n-----------------------------";
    }
    cout<<"\nnumber of moves: "<<this->n_moves;
    cout<<"\nScore for player S: "<<this->scoreS;
    cout<<"\nScore for player U: "<<this->scoreU;
    cout << endl;
}

// Returns true if there is any winner
template <typename T>
bool SUS_Board<T>::is_win() {
    if((this->scoreS != this->scoreU)&& this->n_moves == 9)
    {
        return true;
    }
    return false;
}

// Return true if 9 moves are done and no winner
template <typename T>
bool SUS_Board<T>::is_draw() {
    return (this->n_moves == 9 && !is_win());
}

template <typename T>
bool SUS_Board<T>::game_is_over() {
    return is_win() || is_draw();
}

//--------------------------------------

// Constructor for X_O_Player
template <typename T>
SUS_Player<T>::SUS_Player(string name, T symbol) : Player<T>(name, symbol) {}

template <typename T>
void SUS_Player<T>::getmove(int& x, int& y) {
    cout << "\nPlease enter your move x and y (0 to 2) separated by spaces: ";
    cin >> x >> y;
}

// Constructor for X_O_Random_Player
template <typename T>
SUS_Random_Player<T>::SUS_Random_Player(T symbol) : RandomPlayer<T>(symbol) {
    this->dimension = 3;
    this->name = "Random Computer Player";
    srand(static_cast<unsigned int>(time(0)));  // Seed the random number generator
}

template <typename T>
void SUS_Random_Player<T>::getmove(int& x, int& y) {
    x = rand() % this->dimension;  // Random number between 0 and 2
    y = rand() % this->dimension;
}

#endif //_SUS_H

