
#ifndef _SUS_H
#define _SUS_H

#include "BoardGame_Classes.h"
#include <unordered_set>
#include <vector>
#include<algorithm>
#include<set>

template <typename T>
class S_U_Board:public Board<T> {
    int score1,score2;
    char lastSymbol;
    unordered_set <int> checked;

public:
    S_U_Board ();
    bool update_board (int x , int y , T symbol);
    void display_board () ;
    bool is_win() ;
    bool is_draw();
    bool game_is_over();

};

template <typename T>
class S_U_Player : public Player<T> {
public:
    S_U_Player (string name, T symbol);
    void getmove(int& x, int& y) ;

};

template <typename T>
class S_U_Random_Player : public RandomPlayer<T>{
public:
    S_U_Random_Player (T symbol);
    void getmove(int &x, int &y) ;
};





//--------------------------------------- IMPLEMENTATION

#include <iostream>
#include <iomanip>
#include <cctype>  // for toupper()

using namespace std;

// Constructor for X_O_Board
template <typename T>
S_U_Board<T>::S_U_Board() {
    this->rows = this->columns = 3;
    this->board = new char*[this->rows];
    for (int i = 0; i < this->rows; i++) {
        this->board[i] = new char[this->columns];
        for (int j = 0; j < this->columns; j++) {
            this->board[i][j] = 0;
        }
    }
    this->n_moves = 0;
    this->score1 = 0;
    this->score2 = 0;
}

template <typename T>
bool S_U_Board<T>::update_board(int x, int y, T mark) {
    // Only update if move is valid
    if (!(x < 0 || x >= this->rows || y < 0 || y >= this->columns) && (this->board[x][y] == 0|| mark == 0)) {
        if (mark == 0){
            this->n_moves--;
            this->board[x][y] = 0;
        }
        else {
            this->n_moves++;
            this->board[x][y] = toupper(mark);
            this->lastSymbol = toupper(mark);
        }

        return true;
    }
    return false;
}

// Display the board and the pieces on it
template <typename T>
void S_U_Board<T>::display_board() {
    for (int i = 0; i < this->rows; i++) {
        cout << "\n| ";
        for (int j = 0; j < this->columns; j++) {
            cout << "(" << i << "," << j << ")";
            cout << setw(2) << this->board[i][j] << " |";
        }
        cout << "\n-----------------------------";
    }
    cout<<"\nMove number: "<<this->n_moves;
    cout<<"\nScore1: "<<this->score1<<'\n'<<"Score2: "<<this->score2<<'\n';
    cout << endl;
}

// Returns true if there is any winner
template <typename T>
bool S_U_Board<T>::is_win() {
        // Check rows and columns
    unordered_set <int> checked;
    for (int i = 0; i < this->rows; i++) 
    {
        if (this->board[i][0] == 'S' && this->board[i][1] == 'U' && this->board[i][2] == 'S' && count(this->checked.begin(),this->checked.end(),i)==0 ) 
        {
            if(this->n_moves%2!=0)
            {
                this->score1 += 1-checked.size();
                
                this->checked.insert(i);
            }else
            {
                this->score2 += 1-checked.size();
                this->checked.insert(i);
            }
        }
    }

    for(int j = 0 ; j<this->columns ; j++)
    {
        if(this->board[0][j]== 'S' && this->board[1][j] == 'U' && this->board[2][j] == 'S' && count(this->checked.begin(),this->checked.end(),j+3)==0 )
        {
            if(this->n_moves%2!=0)
            {
                this->score1 += 1-checked.size();
                this->checked.insert(j+3);
            }else
            {
                this->score2 += 1-checked.size();
                this->checked.insert(j+3);
            }
        }
    }

    // Check diagonals
    if (this->board[0][0] == 'S' && this->board[1][1] == 'U' && this->board[2][2] == 'S' && count(this->checked.begin(),this->checked.end(),6)==0 )
    {
           if(this->n_moves%2!=0)
            {
                this->score1 += 1-checked.size();
                this->checked.insert(6);
            }else
            {
                this->score2 += 1-checked.size();
                this->checked.insert(6);
            }
    }

    if(this->board[0][2] == 'S' && this->board[1][1] == 'U' && this->board[2][0] == 'S' && count(this->checked.begin(),this->checked.end(),7)==0 )
    {
        if(this->n_moves%2!=0)
            {
                this->score1 += 1-checked.size();
                this->checked.insert(7);
            }else
            {
                this->score2 += 1-checked.size();
                this->checked.insert(7);
            }
    } 
    if((this->n_moves==9) && this->score1 != this->score2)
    {
        return true;
    }

    return false;

}

// Return true if 9 moves are done and no winner
template <typename T>
bool S_U_Board<T>::is_draw() {
    return (this->n_moves == 9 && !is_win());
}

template <typename T>
bool S_U_Board<T>::game_is_over() {
    return is_win() || is_draw();
}

//--------------------------------------

// Constructor for X_O_Player
template <typename T>
S_U_Player<T>::S_U_Player(string name, T symbol) : Player<T>(name, symbol) {}

template <typename T>
void S_U_Player<T>::getmove(int& x, int& y) {
    cout << "\nPlease enter your move x and y (0 to 2) separated by spaces: ";
    cin >> x >> y;
}

// Constructor for X_O_Random_Player
template <typename T>
S_U_Random_Player<T>::S_U_Random_Player(T symbol) : RandomPlayer<T>(symbol) {
    this->dimension = 3;
    this->name = "Random Computer Player";
    srand(static_cast<unsigned int>(time(0)));  // Seed the random number generator
}

template <typename T>
void S_U_Random_Player<T>::getmove(int& x, int& y) {
    x = rand() % this->dimension;  // Random number between 0 and 2
    y = rand() % this->dimension;
}







#endif //_SUS_H

